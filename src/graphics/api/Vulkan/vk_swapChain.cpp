//
// Created by kisly on 04.09.2025.
//

#include "vk_swapChain.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "vk_Surface.hpp"
#include "../../../util/coders.hpp"
#include <vector>

namespace core
{
	namespace vulkan
	{
		SwapChain::SwapChain(const SwapChainInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			uint32_t FamilyIndices = info.ptrDevice->getPresentQueueFamilyIndex();

			VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
			swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			swapchainCreateInfo.surface = info.ptrSurface->surface;
			swapchainCreateInfo.flags = 0;
			swapchainCreateInfo.pNext = nullptr;
			swapchainCreateInfo.presentMode = (info.V_sync) ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR;
			swapchainCreateInfo.preTransform = info.ptrDevice->surfaceCapabilitiesFormat.currentTransform;
			swapchainCreateInfo.minImageCount = info.countImage;
			swapchainCreateInfo.imageUsage = info.ptrDevice->surfaceCapabilitiesFormat.supportedUsageFlags;
			swapchainCreateInfo.imageFormat = info.ptrDevice->surfaceFormat.format;
			swapchainCreateInfo.imageExtent = info.ptrDevice->surfaceCapabilitiesFormat.currentExtent;
			swapchainCreateInfo.clipped = (info.clipped) ? VK_TRUE : VK_FALSE;
			swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
			swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			swapchainCreateInfo.imageArrayLayers = 1;
			swapchainCreateInfo.imageColorSpace = info.ptrDevice->surfaceFormat.colorSpace;
			swapchainCreateInfo.pQueueFamilyIndices = &FamilyIndices;
			swapchainCreateInfo.queueFamilyIndexCount = 1;

			if (info.ptrDevice->getPresentQueueFamilyIndex() == info.ptrDevice->getGraphicsQueueFamilyIndex())
				swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			else
				swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;

			VkResult result = vkCreateSwapchainKHR(
					info.ptrDevice->device,
					&swapchainCreateInfo,
					nullptr,
					&this->swapChain);
			coders::vulkanProcessingError(result);

			uint32_t count = 0;
			std::vector<VkImage> swapChainImages = {};
			result = vkGetSwapchainImagesKHR(
					*this->ptrDevice,
					this->swapChain,
					&count,
					nullptr);
			coders::vulkanProcessingError(result);

			swapChainImages.resize(count);
			result = vkGetSwapchainImagesKHR(
					*this->ptrDevice,
					this->swapChain,
					&count,
					swapChainImages.data());
			coders::vulkanProcessingError(result);

			this->imagesView.resize(swapChainImages.size());
			uint32_t index = 0;

			for (const VkImage& image : swapChainImages)
			{
				VkImageViewCreateInfo viewInfo = {};
				viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				viewInfo.image = image;
				viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
				viewInfo.format = info.ptrDevice->surfaceFormat.format;
				viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
				viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				viewInfo.subresourceRange.baseMipLevel = 0; // Начинаем с 0-го уровня мипмаппинга
				viewInfo.subresourceRange.levelCount = 1; // Сколько уровней мипмаппинга использовать
				viewInfo.subresourceRange.baseArrayLayer = 0; // Начинаем с 0-го слоя
				viewInfo.subresourceRange.layerCount = 1; // Сколько слоев использовать (1 для 2D текстур)

				VkResult result = vkCreateImageView(
						*this->ptrDevice,
						&viewInfo,
						nullptr,
						&this->imagesView[index]);
				coders::vulkanProcessingError(result);
				index++;
			}
		}

		SwapChain SwapChain::create(const SwapChainInfo& info)
		{
			return SwapChain(info);
		}

		SwapChain* SwapChain::ptrCreate(const SwapChainInfo& info)
		{
			return new SwapChain(info);
		}

		SwapChain::~SwapChain()
		{
			for (const VkImageView& img : this->imagesView)
			{
				vkDestroyImageView(*this->ptrDevice, img, nullptr);
			}
			vkDestroySwapchainKHR(*this->ptrDevice, this->swapChain, nullptr);
		}
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
