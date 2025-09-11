//
// Created by kisly on 07.09.2025.
//

#include "vk_frameBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_renderPass.hpp"
#include "vk_imageView.hpp"
#include "vk_device.hpp"
#include "vk_image.hpp"
#include "../../../util/coders.hpp"

namespace core::vulkan
{
	FrameBuffer::FrameBuffer(Device& device, RenderPass& renderPass, class ImageView& img) :
		ptrDevice(device.getPtrDevice())
	{
		VkImageView Attachments[1] = { img.getVkImageView() };
		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass.getVkRenderPass();
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = Attachments;
		framebufferInfo.width = device.getVkSurfaceCapabilities().currentExtent.width;
		framebufferInfo.height = device.getVkSurfaceCapabilities().currentExtent.height;
		framebufferInfo.layers = 1;

		VkResult result = vkCreateFramebuffer(
			device.getDevice(),
			&framebufferInfo,
			nullptr,
			&this->fbo);
		coders::vulkanProcessingError(result);
	}

	FrameBuffer FrameBuffer::create(Device& device, RenderPass& renderPass, ImageView& image)
	{
		return FrameBuffer(device, renderPass, image);
	}

	FrameBuffer* FrameBuffer::ptrCreate(Device& device, RenderPass& renderPass, ImageView& image)
	{
		return new FrameBuffer(device, renderPass, image);
	}

	FrameBuffer::~FrameBuffer()
	{
		vkDestroyFramebuffer(
			*this->ptrDevice,
			this->fbo,
			nullptr);
	}

	VkFramebuffer FrameBuffer::getVkFramebuffer()
	{
		return this->fbo;
	}

	VkFramebuffer* FrameBuffer::getVkPtrFramebuffer()
	{
		return &this->fbo;
	}

	FrameBuffers::FrameBuffers(Device& device, RenderPass& renderPass, ImageViews& swapchainImageViews) :
		device(device.getPtrDevice())
	{
		for (ImageView* image : swapchainImageViews.getPtrImagesView())
		{
			this->fbos.push_back(FrameBuffer::ptrCreate(device, renderPass, *image));
		}
	}

	FrameBuffers::~FrameBuffers()
	{
		for (FrameBuffer* fbo : this->fbos)
		{
			delete fbo;
		}
		this->fbos.clear();
	}

	FrameBuffers FrameBuffers::create(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews)
	{
		return FrameBuffers(device, renderPass, swapchainImageViews);
	}

	FrameBuffers* FrameBuffers::ptrCreate(Device& device, RenderPass& renderPass, ImageViews& swapchainImageViews)
	{
		return new FrameBuffers(device, renderPass, swapchainImageViews);
	}

	std::vector<FrameBuffer*> FrameBuffers::getPtrFramebuffers()
	{
		return this->fbos;
	}

}

#endif //defined(CORE_INCLUDE_VULKAN)