//
// Created by kisly on 27.11.2025.
//

#include "vk_Image.hpp"
#if defined(CORE_INCLUDE_VULKAN)

namespace core
{
	namespace vulkan
	{
		Image::Image(const ImageCreateinfo& info)
		{
			VkImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageCreateInfo.extent.height = info.extent.height;
			imageCreateInfo.extent.width = info.extent.width;
			imageCreateInfo.extent.depth = info.extent.depth;
			imageCreateInfo.imageType = (info.imageType == IMAGE_TYPE::IMG_1D) ?
					VK_IMAGE_TYPE_1D : (info.imageType == IMAGE_TYPE::IMG_2D) ?
					VK_IMAGE_TYPE_2D : VK_IMAGE_TYPE_3D;
			imageCreateInfo.pNext = nullptr;
			imageCreateInfo.flags = 0;
			imageCreateInfo.sharingMode = info.exclusiveMode ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT;
			imageCreateInfo.queueFamilyIndexCount = 0;
			imageCreateInfo.pQueueFamilyIndices = nullptr;
			imageCreateInfo.format = VK_FORMAT_B8G8R8A8_SRGB;
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.mipLevels = 1;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
