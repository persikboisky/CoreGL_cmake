//
// Created by kisly on 04.09.2025.
//

#include "vk_swapChain.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_surface.hpp"
#include "vk_device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		static VkImageView createImageView(
			VkDevice device,
			VkImage image,
			VkFormat format,
			VkImageAspectFlags aspectFlags,
			uint32_t mipLevels)
		{
			VkImageViewCreateInfo viewInfo{};
			viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewInfo.image = image;
			viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewInfo.format = format;

			viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			viewInfo.subresourceRange.aspectMask = aspectFlags;
			viewInfo.subresourceRange.baseMipLevel = 0;
			viewInfo.subresourceRange.levelCount = mipLevels;
			viewInfo.subresourceRange.baseArrayLayer = 0;
			viewInfo.subresourceRange.layerCount = 1;

			VkImageView imageView;
			VkResult result = vkCreateImageView(device, &viewInfo, nullptr, &imageView);
			coders::vulkanProcessingError(result);

			return imageView;
		}

		SwapChain::SwapChain(const swapChainInfo& info) : device(info.ptrDevice->getPtrDevice())
		{
			uint32_t FamilyIndices = info.ptrDevice->getPresentQueueFamilyIndex();

			//--------------------------------------------------------------------------------------------------------
			VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
			swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			swapchainCreateInfo.surface = info.ptrSurface->getVkSurfaceKHR();
			swapchainCreateInfo.flags = 0;
			swapchainCreateInfo.pNext = nullptr;
			swapchainCreateInfo.presentMode = (info.V_sync) ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR;
			swapchainCreateInfo.preTransform = info.ptrDevice->getVkSurfaceCapabilities().currentTransform;
			swapchainCreateInfo.minImageCount = info.countFrameBuffers;
			swapchainCreateInfo.imageUsage = info.ptrDevice->getVkSurfaceCapabilities().supportedUsageFlags;
			swapchainCreateInfo.imageFormat = info.ptrDevice->getVkSurfaceFormat().format;
			swapchainCreateInfo.imageExtent = info.ptrDevice->getVkSurfaceCapabilities().currentExtent;
			swapchainCreateInfo.clipped = (info.clipped) ? VK_TRUE : VK_FALSE;
			swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
			swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			swapchainCreateInfo.imageArrayLayers = 1;
			swapchainCreateInfo.imageColorSpace = info.ptrDevice->getVkSurfaceFormat().colorSpace;
			swapchainCreateInfo.pQueueFamilyIndices = &FamilyIndices;
			swapchainCreateInfo.queueFamilyIndexCount = 1;

			//--------------------------------------------------------------------------------------------------------
			if (info.ptrDevice->getPresentQueueFamilyIndex() == info.ptrDevice->getGraphicsQueueFamilyIndex())
				swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			else
				swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;

			VkResult result = vkCreateSwapchainKHR(
				info.ptrDevice->getDevice(),
				&swapchainCreateInfo,
				nullptr,
				&this->swapChain);
			coders::vulkanProcessingError(result);

			//--------------------------------------------------------------------------------------------------------
			uint32_t count = 0;
			std::vector<VkImage> swapChainImages = {};
			result = vkGetSwapchainImagesKHR(
				*this->device,
				swapChain,
				&count,
				nullptr);
			coders::vulkanProcessingError(result);

			swapChainImages.resize(count);
			result = vkGetSwapchainImagesKHR(
				*this->device,
				swapChain,
				&count,
				swapChainImages.data());
			coders::vulkanProcessingError(result);

			for (const VkImage& image : swapChainImages)
			{
				this->imagesView.push_back(createImageView(
					*this->device,
					image,
					info.ptrDevice->getVkSurfaceFormat().format,
					VK_IMAGE_ASPECT_COLOR_BIT,
					1));
			}
		}

		SwapChain SwapChain::create(const swapChainInfo& info)
		{
			return SwapChain(info);
		}

		SwapChain* SwapChain::ptrCreate(const swapChainInfo& info)
		{
			return new SwapChain(info);
		}

		SwapChain::~SwapChain()
		{
			for (const VkImageView& image : this->imagesView)
			{
				vkDestroyImageView(*this->device, image, nullptr);
			}

			vkDestroySwapchainKHR(
				*this->device,
				this->swapChain,
				nullptr);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)у