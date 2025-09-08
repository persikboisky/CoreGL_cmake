//
// Created by kisly on 07.09.2025.
//

#include "vk_frameBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_renderPass.hpp"
#include "vk_swapChain.hpp"

namespace core::vulkan
{
	FrameBuffer::FrameBuffer(SwapChain& swapChain, RenderPass& renderPass)
	{
		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass.getVkRenderPass();
		framebufferInfo.attachmentCount = 1;
//		framebufferInfo.pAttachments = &image;
//		framebufferInfo.width = surfaceCapabilities.currentExtent.width;
//		framebufferInfo.height = surfaceCapabilities.currentExtent.height;
		framebufferInfo.layers = 1;
	}
}

#endif //defined(CORE_INCLUDE_VULKAN)