//
// Created by kisly on 04.09.2025.
//

#ifndef VK_SWAPCHAIN_HPP
#define VK_SWAPCHAIN_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		struct SwapChainInfo
		{
			bool V_sync = true;
			bool clipped = true;

			uint32_t countImage = 3;

			class Surface *ptrSurface = nullptr;
			class Device *ptrDevice = nullptr;
		};

		class SwapChain
		{
		protected:
			friend class FrameBuffer;

		private:
			VkSwapchainKHR swapChain = {};
			VkDevice *ptrDevice = nullptr;

			std::vector<VkImageView> imagesView = {};

			SwapChain(const SwapChainInfo& info);

		public:
			static SwapChain create(const SwapChainInfo &info);
			static SwapChain *ptrCreate(const SwapChainInfo &info);

			~SwapChain();
		};
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif // VK_SWAPCHAIN_HPP
