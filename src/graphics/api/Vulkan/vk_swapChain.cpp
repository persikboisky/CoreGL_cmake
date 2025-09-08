//
// Created by kisly on 04.09.2025.
//

#include "vk_swapChain.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_surface.hpp"
#include "vk_device.hpp"
#include "vk_imageView.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
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
			vkDestroySwapchainKHR(
				*this->device,
				this->swapChain,
				nullptr);
		}

		std::vector<VkImage> SwapChain::getVkImages()
		{
			uint32_t count = 0;
			std::vector<VkImage> swapChainImages = {};
			VkResult result = vkGetSwapchainImagesKHR(
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

			return swapChainImages;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)у