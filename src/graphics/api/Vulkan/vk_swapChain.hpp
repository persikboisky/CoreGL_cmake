//
// Created by kisly on 04.09.2025.
//

#ifndef VK_SWAPCHAIN_HPP_
#define VK_SWAPCHAIN_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		struct swapChainInfo
		{
			class Surface* ptrSurface = nullptr;
			class Device* ptrDevice = nullptr;

			uint32_t countFrameBuffers = 3;

			bool V_sync = true;
			bool clipped = true;
		};

		class SwapChain
		{
		 private:
			SwapChain(const swapChainInfo& info);

			VkSwapchainKHR swapChain = {};
			std::vector<VkImageView> imagesView = {};

			VkDevice *device = nullptr;

		 public:
			static SwapChain create(const swapChainInfo& info);
			static SwapChain *ptrCreate(const swapChainInfo& info);

			~SwapChain();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SWAPCHAIN_HPP_
