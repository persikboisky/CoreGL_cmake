//
// Created by kisly on 07.09.2025.
//

#ifndef VK_FRAMEBUFFER_HPP_
#define VK_FRAMEBUFFER_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
	class FrameBuffers
	{
	 private:
		std::vector<VkFramebuffer> fbo = {};
		VkDevice *device = nullptr;

		FrameBuffers(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews);

	 public:
		~FrameBuffers();

		static FrameBuffers create(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews);
		static FrameBuffers *ptrCreate(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews);
	};

//	class FrameBuffer
//	{
//	 private:
//		VkFramebuffer fbo;
//
//		FrameBuffer(class SwapChain& swapChain, class RenderPass& renderPass);
//	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_FRAMEBUFFER_HPP_
