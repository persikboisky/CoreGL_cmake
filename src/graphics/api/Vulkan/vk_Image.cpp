//
// Created by kisly on 27.11.2025.
//

#include "vk_Image.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/Coders.hpp"
#include "vk_Device.hpp"

namespace core
{
	namespace vulkan
	{
        static VkFormat convertFormat(const IMAGE_FORMAT& format)
        {
            switch (format)
            {
            case IMAGE_FORMAT::R8G8B8A8_UNORM:
                return VK_FORMAT_R8G8B8A8_UNORM;
            case IMAGE_FORMAT::R8G8B8_SRGB:
                return VK_FORMAT_R8G8B8_SRGB;
            case IMAGE_FORMAT::R8G8B8A8_SRGB:
                return VK_FORMAT_R8G8B8A8_SRGB;
            case IMAGE_FORMAT::R8G8B8_UNORM:
                return VK_FORMAT_R8G8B8_UNORM;
            case IMAGE_FORMAT::B8G8R8A8_UNORM:
                return VK_FORMAT_B8G8R8A8_UNORM;
            case IMAGE_FORMAT::D16_UNORM:
                return VK_FORMAT_D16_UNORM;
            case IMAGE_FORMAT::D24_UNORM_S8_UINT:
                return VK_FORMAT_D24_UNORM_S8_UINT;
            case IMAGE_FORMAT::A8_UNORM:
                return VK_FORMAT_A8_UNORM;
            case IMAGE_FORMAT::D32_SFLOAT:
                return VK_FORMAT_D32_SFLOAT;
            case IMAGE_FORMAT::D32_SFLOAT_S8_UINT:
                return VK_FORMAT_D32_SFLOAT_S8_UINT;
            case IMAGE_FORMAT::R16G16B16A16_SFLOAT:
                return VK_FORMAT_R16G16B16A16_SFLOAT;
            case IMAGE_FORMAT::R16_SFLOAT:
                return VK_FORMAT_R16_SFLOAT;
            case IMAGE_FORMAT::R16G16_SFLOAT:
                return VK_FORMAT_R16G16_SFLOAT;
            case IMAGE_FORMAT::R32G32B32_SFLOAT:
                return VK_FORMAT_R32G32B32_SFLOAT;
            case IMAGE_FORMAT::R32G32B32A32_SFLOAT:
            default:
                return VK_FORMAT_R32G32B32A32_SFLOAT;
            }
        }

	    static VkImageUsageFlags convertUsageFlags(const IMAGE_USAGE& usage)
        {
            switch (usage)
            {
            case IMAGE_USAGE::SAMPLED:
                return VK_IMAGE_USAGE_SAMPLED_BIT;
            case IMAGE_USAGE::TRANSFER_DST:
                return VK_IMAGE_USAGE_TRANSFER_DST_BIT;
            case IMAGE_USAGE::TRANSFER_SRC:
                return VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
            case IMAGE_USAGE::SAMPLED_TRANSFER_DST:
                return VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
            case IMAGE_USAGE::SAMPLED_TRANSFER_SRC:
            default:
                return VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
            }
        }

        Image::Image(const ImageCreateInfo &info) : device(info.ptrDevice->device)
        {
            VkImageCreateInfo imageCreateInfo = {};
            imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageCreateInfo.extent.height = info.extent.height;
            imageCreateInfo.extent.width = info.extent.width;
            imageCreateInfo.extent.depth = info.extent.depth;
            imageCreateInfo.imageType =
                info.type == IMAGE_TYPE::IMG_1D ? VK_IMAGE_TYPE_1D :
                info.type == IMAGE_TYPE::IMG_2D ? VK_IMAGE_TYPE_2D : VK_IMAGE_TYPE_3D;
            imageCreateInfo.pNext = nullptr;
            imageCreateInfo.flags = 0;
            imageCreateInfo.sharingMode = info.exclusiveMode ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT;
            imageCreateInfo.queueFamilyIndexCount = info.queueFamilyIndices.size();
            imageCreateInfo.pQueueFamilyIndices = info.queueFamilyIndices.data();
            imageCreateInfo.format = convertFormat(info.format);
            imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageCreateInfo.mipLevels = info.mipLevels;
            imageCreateInfo.usage = convertUsageFlags(info.usage);
            imageCreateInfo.arrayLayers = 1;
            imageCreateInfo.tiling = info.typeMemory == TYPE_MEMORY::HOST ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;

            VkResult result = vkCreateImage(
                    info.ptrDevice->device,
                    &imageCreateInfo,
                    nullptr,
                    &image);
            Coders::vulkanProcessingError(result);

            VkMemoryRequirements memRequirements = {};
            vkGetImageMemoryRequirements(
                    info.ptrDevice->device,
                    image,
                    &memRequirements);

            VkMemoryAllocateInfo allocInfo = {};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memRequirements.size;
            allocInfo.memoryTypeIndex = info.ptrDevice->findMemoryType(
                    memRequirements.memoryTypeBits,
                    info.typeMemory == TYPE_MEMORY::HOST ?
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT :
                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            result = vkAllocateMemory(
                    info.ptrDevice->device,
                    &allocInfo,
                    nullptr,
                    &this->memory);
            Coders::vulkanProcessingError(result);
            vkBindImageMemory(info.ptrDevice->device, this->image, this->memory, 0);

            if (info.typeMemory != TYPE_MEMORY::DEVICE_LOCAL && info.ptrImageData != nullptr)
            {
                copy(info.ptrImageData, info.size);
            }
        }

        Image Image::create(const ImageCreateInfo &info)
        {
            return Image(info);
        }

        Image *Image::ptrCreate(const ImageCreateInfo &info)
        {
            return new Image(info);
        }

        Image::~Image()
        {
            vkFreeMemory(device, memory, nullptr);
            vkDestroyImage(device, image, nullptr);
        }

        void Image::copy(void *data, uint64_t size, uint64_t offset)
        {
            void* ptrMemory;
            vkMapMemory(device, memory, offset, size, 0, &ptrMemory);
            memcpy(ptrMemory, data, size);
            vkUnmapMemory(device, memory);
        }

        ImageView::ImageView(const ImageViewCreateInfo &info) : device(info.ptrDevice->device)
        {
            VkImageViewCreateInfo viewCreateInfo = {};
            viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewCreateInfo.image = info.ptrImage->image;
            viewCreateInfo.viewType =
                info.type == IMAGE_TYPE::IMG_1D ? VK_IMAGE_VIEW_TYPE_1D :
                info.type == IMAGE_TYPE::IMG_2D ? VK_IMAGE_VIEW_TYPE_2D : VK_IMAGE_VIEW_TYPE_3D;
            viewCreateInfo.format = convertFormat(info.format);
            viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewCreateInfo.subresourceRange.aspectMask = Convert::convert(info.ptrSubresourceRange->aspect);
            viewCreateInfo.subresourceRange.baseMipLevel = info.ptrSubresourceRange->baseMipLevel;
            viewCreateInfo.subresourceRange.levelCount = info.ptrSubresourceRange->levelCount;
            viewCreateInfo.subresourceRange.baseArrayLayer = info.ptrSubresourceRange->baseArrayLayer;
            viewCreateInfo.subresourceRange.layerCount = info.ptrSubresourceRange->layerCount;

            const VkResult result = vkCreateImageView(device, &viewCreateInfo, nullptr, &imageView);
            Coders::vulkanProcessingError(result);
        }

        ImageView ImageView::create(const ImageViewCreateInfo &info)
        {
            return ImageView(info);
        }

        ImageView *ImageView::ptrCreate(const ImageViewCreateInfo &info)
        {
            return new ImageView(info);
        }

        ImageView::~ImageView()
        {
            vkDestroyImageView(device, imageView, nullptr);
        }

        static VkFilter convertFilter(const TEXTURE_FILTER& filter)
        {
            switch (filter)
            {
            case TEXTURE_FILTER::NEAREST:
                return VK_FILTER_NEAREST;
            case TEXTURE_FILTER::LINEAR:
                return VK_FILTER_LINEAR;
            case TEXTURE_FILTER::CUBIC_EXT:
                return VK_FILTER_CUBIC_EXT;
            case TEXTURE_FILTER::CUBIC_IMG:
            default:
                return VK_FILTER_CUBIC_IMG;
            }
        }

	    static VkSamplerAddressMode convertAddressMode(const vulkan::TEXTURE_WRAP& addres)
        {
            switch (addres)
            {
                case vulkan::TEXTURE_WRAP::REPEAT:
                    return VK_SAMPLER_ADDRESS_MODE_REPEAT;
                case vulkan::TEXTURE_WRAP::MIRRORED_REPEAT:
                    return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
                case vulkan::TEXTURE_WRAP::CLAMP_TO_EDGE:
                    return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
                case vulkan::TEXTURE_WRAP::CLAMP_TO_BORDER:
                default:
                    return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
            }
        }

        Sampler::Sampler(const SamplerCreateInfo &info) : device(info.ptrDevice->device)
        {
            VkSamplerCreateInfo samplerCreateInfo = {};
            samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            samplerCreateInfo.pNext = nullptr;
            samplerCreateInfo.flags = 0;

            // 1. ФИЛЬТРАЦИЯ (магнификация и минификация)
            samplerCreateInfo.magFilter = convertFilter(info.filter.magFilter);
            samplerCreateInfo.minFilter = convertFilter(info.filter.minFilter);

            // 2. АДРЕСАЦИЯ (что делать за пределами [0, 1])
            samplerCreateInfo.addressModeU = convertAddressMode(info.addressMode.addressModeU);
            samplerCreateInfo.addressModeV = convertAddressMode(info.addressMode.addressModeV);
            samplerCreateInfo.addressModeW = convertAddressMode(info.addressMode.addressModeW);

            // 3. АНИЗОТРОПНАЯ ФИЛЬТРАЦИЯ
            samplerCreateInfo.anisotropyEnable = VK_TRUE;
            samplerCreateInfo.maxAnisotropy = 16.0f;  // Максимальный уровень (1-16)

            // 4. MIP-МАППИНГ
            samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;  // Линейная интерполяция между mip-уровнями
            samplerCreateInfo.minLod = 0.0f;     // Минимальный mip-уровень
            samplerCreateInfo.maxLod = VK_LOD_CLAMP_NONE;  // Использовать все mip-уровни
            samplerCreateInfo.mipLodBias = 0.0f; // Смещение для выбора mip-уровня

            // 5. ЦВЕТ границы (если используется CLAMP_TO_BORDER)
            samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;

            // 6. НОРМАЛИЗОВАННЫЕ КООРДИНАТЫ
            samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;  // true для координат в пикселях

            // 7. ФУНКЦИЯ СРАВНЕНИЯ (для теней)
            samplerCreateInfo.compareEnable = VK_FALSE;  // true для depth сравнения
            samplerCreateInfo.compareOp = VK_COMPARE_OP_ALWAYS;

            const VkResult result = vkCreateSampler(device, &samplerCreateInfo, nullptr, &sampler);
            Coders::vulkanProcessingError(result);
        }

        Sampler::~Sampler()
        {
            vkDestroySampler(device, sampler, nullptr);
        }

        Sampler Sampler::create(const SamplerCreateInfo &info)
        {
            return Sampler(info);
        }

        Sampler *Sampler::ptrCreate(const SamplerCreateInfo &info)
        {
            return new Sampler(info);
        }

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
