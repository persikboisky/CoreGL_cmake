//
// Created by kisly on 07.09.2025.
//

#include "vk_frameBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_renderPass.hpp"
#include "vk_imageView.hpp"
#include "vk_device.hpp"

namespace core::vulkan
{
	FrameBuffers::FrameBuffers(Device& device, RenderPass& renderPass, ImageViews& swapchainImageViews) :
		device(device.getPtrDevice())
	{
		for (const VkImageView& image : swapchainImageViews.getVkImagesView())
		{
			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPass.getVkRenderPass();
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = &image;
			framebufferInfo.width = device.getVkSurfaceCapabilities().currentExtent.width;
			framebufferInfo.height = device.getVkSurfaceCapabilities().currentExtent.height;
			framebufferInfo.layers = 1;

			VkFramebuffer framebuffer;
			vkCreateFramebuffer(
				device.getDevice(),
				&framebufferInfo,
				nullptr,
				&framebuffer);
			this->fbo.push_back(framebuffer);
		}
	}

	FrameBuffers::~FrameBuffers()
	{
		for (const VkFramebuffer& frameBuffer : this->fbo)
		{
			vkDestroyFramebuffer(
				*this->device,
				frameBuffer,
				nullptr);
		}
	}


	FrameBuffers FrameBuffers::create(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews)
	{
		return FrameBuffers(device, renderPass, swapchainImageViews);
	}

	FrameBuffers* FrameBuffers::ptrCreate(Device& device, RenderPass& renderPass, ImageViews& swapchainImageViews)
	{
		return new FrameBuffers(device, renderPass, swapchainImageViews);
	}
}

#endif //defined(CORE_INCLUDE_VULKAN)