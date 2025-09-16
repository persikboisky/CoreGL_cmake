//
// Created by kisly on 07.09.2025.
//

#include "vk_frameBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_renderPass.hpp"
#include "vk_imageView.hpp"
#include "vk_device.hpp"
#include "vk_image.hpp"
#include "vk_depthImageView.hpp"
#include "../../../util/coders.hpp"
#include <iostream>

namespace core::vulkan
{
	FrameBuffer::FrameBuffer(Device& device, RenderPass& renderPass, ImageView& img, DepthImageView* ptrDIW) :
		ptrDevice(device.getPtrDevice())
	{
		std::vector<VkImageView> Attachments = {};
		if (ptrDIW != nullptr && renderPass.getStateDepth())
		{
			Attachments.resize(2);
			Attachments[1] = ptrDIW->getVkImageView();
		}
		else Attachments.resize(1);
		Attachments[0] = img.getVkImageView();

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass.getVkRenderPass();
		framebufferInfo.attachmentCount = static_cast<uint32_t>(Attachments.size());
		framebufferInfo.pAttachments = Attachments.data();
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

	FrameBuffer FrameBuffer::create(Device& device, RenderPass& renderPass, ImageView& image, DepthImageView* ptrDIW)
	{
		return FrameBuffer(device, renderPass, image, ptrDIW);
	}

	FrameBuffer* FrameBuffer::ptrCreate(Device& device, RenderPass& renderPass, ImageView& image, DepthImageView* ptrDIW)
	{
		return new FrameBuffer(device, renderPass, image, ptrDIW);
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

	FrameBuffers::FrameBuffers(Device& device, RenderPass& renderPass, ImageViews& swapchainImageViews, DepthImageViews* ptrDIWS) :
		device(device.getPtrDevice())
	{
		uint32_t i = 0;
		for (ImageView* image : swapchainImageViews.getPtrImagesView())
		{
			if (ptrDIWS != nullptr && renderPass.getStateDepth())
			{
				this->fbos.push_back(FrameBuffer::ptrCreate(device, renderPass, *image, ptrDIWS->getDepthImageViewsPtr()[i]));
			}
			else
			{
				this->fbos.push_back(FrameBuffer::ptrCreate(device, renderPass, *image));
			}
			i++;
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

	FrameBuffers FrameBuffers::create(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews, DepthImageViews* ptrDIWS)
	{
		return FrameBuffers(device, renderPass, swapchainImageViews, ptrDIWS);
	}

	FrameBuffers* FrameBuffers::ptrCreate(Device& device, RenderPass& renderPass, ImageViews& swapchainImageViews, DepthImageViews* ptrDIWS)
	{
		return new FrameBuffers(device, renderPass, swapchainImageViews, ptrDIWS);
	}

	std::vector<FrameBuffer*> FrameBuffers::getPtrFramebuffers()
	{
		return this->fbos;
	}

}

#endif //defined(CORE_INCLUDE_VULKAN)