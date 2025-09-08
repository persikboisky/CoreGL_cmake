//
// Created by kisly on 07.09.2025.
//

#include "vk_imageView.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_swapChain.hpp"
#include "vk_device.hpp"

namespace core
{
	namespace vulkan
	{
		ImageViews::ImageViews(Device& device, SwapChain& swapChain) : ptrDevice(device.getPtrDevice())
		{
			for (const VkImage &image : swapChain.getVkImages())
			{
				VkImageViewCreateInfo viewInfo = {};
				viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				viewInfo.image = image;
				viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
				viewInfo.format = device.getVkSurfaceFormat().format;

				// Компоненты - можно делать swizzle (переназначать каналы)
				viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

				// Subresource range - какая часть изображения используется
				viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				viewInfo.subresourceRange.baseMipLevel = 0; // Начинаем с 0-го уровня мипмаппинга
				viewInfo.subresourceRange.levelCount = 1; // Сколько уровней мипмаппинга использовать
				viewInfo.subresourceRange.baseArrayLayer = 0; // Начинаем с 0-го слоя
				viewInfo.subresourceRange.layerCount = 1; // Сколько слоев использовать (1 для 2D текстур)
			}
		}

		ImageViews::~ImageViews()
		{
			for (const VkImageView &image : this->image) {
				vkDestroyImageView(
					*this->ptrDevice,
					image,
					nullptr);
			}
		}

		ImageViews ImageViews::create(Device& device, SwapChain& swapChain)
		{
			return ImageViews(device, swapChain);
		}

		ImageViews* ImageViews::ptrCreate(Device& device, SwapChain& swapChain)
		{
			return new ImageViews(device, swapChain);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
