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
			imageCreateInfo.imageType = (info.image == IMAGE_TYPE::IMG_1D) ?
					VK_IMAGE_TYPE_1D : (info.image == IMAGE_TYPE::IMG_2D) ?
					VK_IMAGE_TYPE_2D : VK_IMAGE_TYPE_3D;
			imageCreateInfo.pNext = nullptr;
			imageCreateInfo.flags = 0;
			imageCreateInfo.sharingMode = info.exclusiveMode ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT;
			imageCreateInfo.queueFamilyIndexCount = 0;
			imageCreateInfo.pQueueFamilyIndices = nullptr;
			imageCreateInfo.format = convertFormat(info.format);
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.mipLevels = info.mipLevels;
			imageCreateInfo.usage = convertUsage(info.usage);
			imageCreateInfo.arrayLayers = 1;
			imageCreateInfo.tiling = info.typeMemory == TYPE_MEMORY::HOST ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;

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
					(info.typeMemory == TYPE_MEMORY::HOST) ?
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT :
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
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
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
