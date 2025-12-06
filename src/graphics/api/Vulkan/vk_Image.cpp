//
// Created by kisly on 27.11.2025.
//

#include "vk_Image.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		static inline VkFormat convertFormat(const IMAGE_FORMAT& format)
		{
			switch (format)
			{
			case IMAGE_FORMAT::B8G8R8_SRGB:
				return VK_FORMAT_B8G8R8_SRGB;
			case IMAGE_FORMAT::B8G8R8A8_SRGB:
				return VK_FORMAT_B8G8R8A8_SRGB;
			case IMAGE_FORMAT::B8G8R8A8_UINT:
				return VK_FORMAT_B8G8R8A8_UINT;
			case IMAGE_FORMAT::B8G8R8_UINT:
				return VK_FORMAT_B8G8R8_UINT;
			case IMAGE_FORMAT::D24_UNORM_S8_UINT:
				return VK_FORMAT_D24_UNORM_S8_UINT;
			default:
				return VK_FORMAT_D32_SFLOAT;
			}
		}

		static inline VkImageUsageFlags convertUsage(const TYPE_USAGE_IMAGE& typeUsageImage)
		{
			switch (typeUsageImage)
			{
			case TYPE_USAGE_IMAGE::TRANSFER_DST:
				return VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			case TYPE_USAGE_IMAGE::STORAGE:
				return VK_IMAGE_USAGE_STORAGE_BIT;
			case TYPE_USAGE_IMAGE::TRANSFER_SRC:
				return VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			case TYPE_USAGE_IMAGE::COLOR_ATTACHMENT:
				return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			case TYPE_USAGE_IMAGE::SAMPLED:
				return VK_IMAGE_USAGE_SAMPLED_BIT;
			case TYPE_USAGE_IMAGE::DEPTH_STENCIL_ATTACHMENT:
			default:
				return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			}
		}

		Image::Image(const ImageCreateInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			VkImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageCreateInfo.extent.height = info.extent.height;
			imageCreateInfo.extent.width = info.extent.width;
			imageCreateInfo.extent.depth = info.extent.depth;
			imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
			imageCreateInfo.pNext = nullptr;
			imageCreateInfo.flags = 0;
			imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			imageCreateInfo.queueFamilyIndexCount = 0;
			imageCreateInfo.pQueueFamilyIndices = nullptr;
			imageCreateInfo.format = VK_FORMAT_B8G8R8A8_SRGB;
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.mipLevels = info.mipLevels;
			imageCreateInfo.usage = convertUsage(info.ptrImageType->usage);
			imageCreateInfo.arrayLayers = 1;
			imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

			VkResult result = vkCreateImage(
					info.ptrDevice->device,
					&imageCreateInfo,
					nullptr,
					&this->image);
			coders::vulkanProcessingError(result);

			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(
					info.ptrDevice->device,
					this->image,
					&memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = info.ptrDevice->findMemoryType(
					memRequirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			result = vkAllocateMemory(
					info.ptrDevice->device,
					&allocInfo,
					nullptr,
					&this->memory);
			coders::vulkanProcessingError(result);
			vkBindImageMemory(info.ptrDevice->device, this->image, this->memory, 0);

			if (info.typeMemory != TYPE_MEMORY::DEVICE_LOCAL && info.data != nullptr)
			{
				this->copy(info.data, info.size);
			}
		}

		Image::~Image()
		{
			vkFreeMemory(*this->ptrDevice, this->memory, nullptr);
			vkDestroyImage(*this->ptrDevice, this->image, nullptr);
		}

		Image Image::create(const ImageCreateInfo& info)
		{
			return Image(info);
		}

		Image* Image::ptrCreate(const ImageCreateInfo& info)
		{
			return new Image(info);
		}

		void Image::copy(void* data, uint64_t size)
		{
			void* ptrMemory;
			vkMapMemory(*this->ptrDevice, this->memory, 0, size, 0, &ptrMemory);
			memcpy(ptrMemory, data, size);
			vkUnmapMemory(*this->ptrDevice, this->memory);
		}

		ImageView::ImageView(const ImageViewCreateInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = info.ptrImage->image;
			createInfo.viewType = (info.ptrImageType->image == IMAGE_TYPE::IMG_1D) ?
					VK_IMAGE_VIEW_TYPE_1D : (info.ptrImageType->image == IMAGE_TYPE::IMG_2D) ?
					VK_IMAGE_VIEW_TYPE_2D : VK_IMAGE_VIEW_TYPE_3D;
			createInfo.format = convertFormat(info.ptrImageType->format);
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = info.ptrImageType->usage == TYPE_USAGE_IMAGE::COLOR_ATTACHMENT ?
					VK_IMAGE_ASPECT_COLOR_BIT : info.ptrImageType->usage == TYPE_USAGE_IMAGE::DEPTH_STENCIL_ATTACHMENT ?
					VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT :
					throw coders(35, "Failed: The image usage is not intended to create a image view");

			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;
			if (info.ptrSubresourceInfo != nullptr)
			{
				createInfo.subresourceRange.baseMipLevel = info.ptrSubresourceInfo->baseMipLevel;
				createInfo.subresourceRange.levelCount = info.ptrSubresourceInfo->levelCount;
				createInfo.subresourceRange.baseArrayLayer = info.ptrSubresourceInfo->baseArrayLayer;
				createInfo.subresourceRange.layerCount = info.ptrSubresourceInfo->layerCount;
			}

			VkResult result = vkCreateImageView(
					info.ptrDevice->device,
					&createInfo,
					nullptr,
					&this->imageView);
			coders::vulkanProcessingError(result);
		}

		ImageView ImageView::create(const ImageViewCreateInfo& info)
		{
			return ImageView(info);
		}

		ImageView* ImageView::ptrCreate(const ImageViewCreateInfo& info)
		{
			return new ImageView(info);
		}

		ImageView::~ImageView()
		{
			vkDestroyImageView(*this->ptrDevice, this->imageView, nullptr);
		}

		static inline VkSamplerAddressMode convertAddressMode(const ADDRESS_MODE& mode)
		{
			switch (mode)
			{
			case ADDRESS_MODE::CLAMP_TO_BORDER:
				return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
			case ADDRESS_MODE::MIRRORED_REPEAT:
				return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
			case ADDRESS_MODE::MIRROR_CLAMP_TO_EDGE:
				return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
			case ADDRESS_MODE::CLAMP_TO_EDGE:
				return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			case ADDRESS_MODE::REPEAT:
			default:
				return VK_SAMPLER_ADDRESS_MODE_REPEAT;
			}
		}

		static inline VkBorderColor convertBorderColor(const BORDER_COLOR& borderColor)
		{
			switch (borderColor)
			{
			case BORDER_COLOR::FLOAT_OPAQUE_WHITE:
				return VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
			case BORDER_COLOR::INT_OPAQUE_WHITE:
				return VK_BORDER_COLOR_INT_OPAQUE_WHITE;
			case BORDER_COLOR::INT_TRANSPARENT_BLACK:
				return VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
			case BORDER_COLOR::FLOAT_TRANSPARENT_BLACK:
				return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
			case BORDER_COLOR::INT_OPAQUE_BLACK:
				return VK_BORDER_COLOR_INT_OPAQUE_WHITE;
			case BORDER_COLOR::FLOAT_OPAQUE_BLACK:
				return VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
			}
		}

		Sampler::Sampler(const SamplerCreateInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			VkSamplerCreateInfo samplerCreateInfo = {};
			samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			samplerCreateInfo.magFilter = (info.magFilter == FILTER::NEAREST) ?
					VK_FILTER_NEAREST : (info.magFilter == FILTER::LINEAR) ?
					VK_FILTER_LINEAR : VK_FILTER_CUBIC_EXT;
			samplerCreateInfo.minFilter = (info.magFilter == FILTER::NEAREST) ?
					VK_FILTER_NEAREST : (info.magFilter == FILTER::LINEAR) ?
					VK_FILTER_LINEAR : VK_FILTER_CUBIC_EXT;
			samplerCreateInfo.mipmapMode = info.mipmapMode == MIPMAP_MODE::NEAREST ?
					VK_SAMPLER_MIPMAP_MODE_LINEAR : VK_SAMPLER_MIPMAP_MODE_NEAREST;
			samplerCreateInfo.addressModeU = convertAddressMode(info.addressModeU);
			samplerCreateInfo.addressModeV = convertAddressMode(info.addressModeV);
			samplerCreateInfo.addressModeW = convertAddressMode(info.addressModeW);
			samplerCreateInfo.mipLodBias = 0.0f;
			samplerCreateInfo.minLod = 0.0f;
			samplerCreateInfo.maxLod = VK_LOD_CLAMP_NONE;
			samplerCreateInfo.compareEnable = VK_FALSE;
			samplerCreateInfo.compareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
			samplerCreateInfo.borderColor = convertBorderColor(info.borderColor);
			samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;

			VkResult result = vkCreateSampler(
					info.ptrDevice->device,
					&samplerCreateInfo,
					nullptr,
					&this->sampler);
			coders::vulkanProcessingError(result);
		}

		Sampler Sampler::create(const SamplerCreateInfo& info)
		{
			return Sampler(info);
		}

		Sampler* Sampler::ptrCreate(const SamplerCreateInfo& info)
		{
			return new Sampler(info);
		}

		Sampler::~Sampler()
		{
			vkDestroySampler(*this->ptrDevice, this->sampler, nullptr);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
