//
// Created by kisly on 07.09.2025.
//

#include "vk_frameBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_renderPass.hpp"
#include "vk_SwapChainImageView.hpp"
#include "vk_device.hpp"
#include "vk_image.hpp"
#include "vk_depthImageView.hpp"
#include "../../../util/coders.hpp"
#include <iostream>

namespace core::vulkan
{
	FrameBuffer::FrameBuffer(Device &device, RenderPass &renderPass, ImageView &img, DepthImageView *ptrDIW) : ptrDevice(&device.device)
	{
		std::vector<VkImageView> Attachments = {};
		if (renderPass.getStateDepth() && ptrDIW != nullptr)
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
		framebufferInfo.width = device.surfaceCapabilitiesFormat.currentExtent.width;
		framebufferInfo.height = device.surfaceCapabilitiesFormat.currentExtent.height;
		framebufferInfo.layers = 1;
		framebufferInfo.pNext = nullptr;
		framebufferInfo.flags = 0;

		VkResult result = vkCreateFramebuffer(
			device.device,
			&framebufferInfo,
			nullptr,
			&this->fbo);
		coders::vulkanProcessingError(result);
	}

	FrameBuffer FrameBuffer::create(Device &device, RenderPass &renderPass, ImageView &image, DepthImageView *ptrDIW)
	{
		return FrameBuffer(device, renderPass, image, ptrDIW);
	}

	FrameBuffer *FrameBuffer::ptrCreate(Device &device, RenderPass &renderPass, ImageView &image, DepthImageView *ptrDIW)
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

	VkFramebuffer *FrameBuffer::getVkPtrFramebuffer()
	{
		return &this->fbo;
	}

	FrameBuffers::FrameBuffers(FrameBuffersInfo &info) : device(&info.ptrDevice->device)
	{
		uint32_t i = 0;
		for (ImageView *image : info.ptrSwapchainImageViews->getPtrImagesView())
		{
			this->fbos.push_back(FrameBuffer::ptrCreate(
				*info.ptrDevice, 
				*info.ptrRenderPass, 
				*image,
				(info.ptrRenderPass->getStateDepth() == true && info.ptrDepthImageViews != nullptr) ? 
					info.ptrDepthImageViews->getDepthImageViewsPtr()[i] : nullptr));
			i++;
		}
	}

	FrameBuffers::~FrameBuffers()
	{
		for (FrameBuffer *fbo : this->fbos)
		{
			delete fbo;
		}
		this->fbos.clear();
	}

	FrameBuffers FrameBuffers::create(FrameBuffersInfo &info)
	{
		return FrameBuffers(info);
	}

	FrameBuffers *FrameBuffers::ptrCreate(FrameBuffersInfo &info)
	{
		return new FrameBuffers(info);
	}

	std::vector<FrameBuffer *> FrameBuffers::getPtrFramebuffers()
	{
		return this->fbos;
	}

}

#endif // defined(CORE_INCLUDE_VULKAN)