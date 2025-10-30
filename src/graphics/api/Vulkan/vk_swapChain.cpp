//
// Created by kisly on 04.09.2025.
//

#include "vk_swapChain.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_surface.hpp"
#include "vk_device.hpp"
#include "vk_SwapChainImageView.hpp"
#include "vk_image.hpp"
#include "vk_semaphore.hpp"
#include "vk_fence.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		SwapChain::SwapChain(const SwapChainInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			uint32_t FamilyIndices = info.ptrDevice->getPresentQueueFamilyIndex();

			//--------------------------------------------------------------------------------------------------------
			VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
			swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			swapchainCreateInfo.surface = info.ptrSurface->getVkSurfaceKHR();
			swapchainCreateInfo.flags = 0;
			swapchainCreateInfo.pNext = nullptr;
			swapchainCreateInfo.presentMode = (info.V_sync) ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR;
			swapchainCreateInfo.preTransform = info.ptrDevice->surfaceCapabilitiesFormat.currentTransform;
			swapchainCreateInfo.minImageCount = info.countFrameBuffers;
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

			//--------------------------------------------------------------------------------------------------------
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

			//--------------------------------------------------------------------------------------------------------
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

			for (VkImage& img : swapChainImages)
			{
				this->swapChainImages.push_back(image(img));
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
			vkDestroySwapchainKHR(
				*this->ptrDevice,
				this->swapChain,
				nullptr);
		}

		std::vector<image> SwapChain::getImages()
		{
			return this->swapChainImages;
		}

		uint32_t SwapChain::getCountImage()
		{
			return static_cast<uint32_t>(this->swapChainImages.size());
		}

		uint32_t SwapChain::getNextImageIndex(class Semaphore& semaphore)
		{
			uint32_t index = 0;
			VkResult result = vkAcquireNextImageKHR(
					*this->ptrDevice,
					this->swapChain,
					UINT64_MAX,
					semaphore.getVkSemaphore(),
					VK_NULL_HANDLE,
					&index);
			coders::vulkanProcessingError(result);
			return index;
		}

		uint32_t SwapChain::getNextImageIndex(Fence& fence)
		{
			uint32_t index = 0;
			VkResult result = vkAcquireNextImageKHR(
					*this->ptrDevice,
					this->swapChain,
					UINT64_MAX,
					VK_NULL_HANDLE,
					fence.fence,
					&index);
			coders::vulkanProcessingError(result);
			return index;
		}

		uint32_t SwapChain::getNextImageIndex(Semaphore& semaphore, Fence& fence)
		{
			uint32_t index = 0;
			VkResult result = vkAcquireNextImageKHR(
				*this->ptrDevice,
				this->swapChain,
				UINT64_MAX,
				semaphore.getVkSemaphore(),
					fence.fence,
				&index);
			coders::vulkanProcessingError(result);
			return index;
		}

		VkSwapchainKHR SwapChain::getVkSwapchainKHR()
		{
			return this->swapChain;
		}

		VkSwapchainKHR* SwapChain::getVkPtrSwapchainKHR()
		{
			return &this->swapChain;
		}

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)у