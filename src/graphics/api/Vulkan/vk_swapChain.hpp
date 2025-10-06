//
// Created by kisly on 04.09.2025.
//

#ifndef VK_SWAPCHAIN_HPP_
#define VK_SWAPCHAIN_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_image.hpp"
#include <vector>

namespace core
{
	namespace vulkan
	{
		struct SwapChainInfo
		{
			class Surface *ptrSurface = nullptr;
			class Device *ptrDevice = nullptr;

			uint32_t countFrameBuffers = 3;

			bool V_sync = true;
			bool clipped = true;
		};

		class SwapChain
		{
		private:
			SwapChain(const SwapChainInfo &info);

			VkSwapchainKHR swapChain = {};
			VkDevice *ptrDevice = nullptr;

			std::vector<image> swapChainImages = {};

		public:
			static SwapChain create(const SwapChainInfo &info);
			static SwapChain *ptrCreate(const SwapChainInfo &info);

			~SwapChain();

			std::vector<image> getImages();
			uint32_t getCountImage();

			uint32_t getNextImageIndex(class Semaphore& semaphore);
			uint32_t getNextImageIndex(class Fence& fence);
			uint32_t getNextImageIndex(class Semaphore& semaphore, class Fence& fence);

			VkSwapchainKHR getVkSwapchainKHR();
			VkSwapchainKHR *getVkPtrSwapchainKHR();
		};
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif // VK_SWAPCHAIN_HPP_
