//
// Created by kisly on 07.09.2025.
//

#ifndef VK_FRAMEBUFFER_HPP_
#define VK_FRAMEBUFFER_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core::vulkan
{
	class FrameBuffer
	{
	 private:
		VkFramebuffer fbo;

		FrameBuffer(class SwapChain& swapChain, class RenderPass& renderPass);
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_FRAMEBUFFER_HPP_
