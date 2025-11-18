//
// Created by kisly on 05.09.2025.
//

#include "vk_FrameBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_RenderPass.hpp"
#include "vk_SwapChain.hpp"
#include "vk_Device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{

//		FrameBuffer::FrameBuffer(const FrameBufferInfo& info)
//		{
//			VkFramebufferCreateInfo framebufferInfo = {};
//			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
//			framebufferInfo.renderPass = info.ptrRenderPass->renderPass;
//			framebufferInfo.layers = 1;
//			framebufferInfo.width = info.width;
//			framebufferInfo.height = info.height;
//
//			for (uint32_t index = 0; index < info.countImage; index++)
//			{
//
//			}
//		}

		FrameBuffer::FrameBuffer(const FrameBufferInfo& info, const SwapChain& swapChain) :
			count(static_cast<uint32_t>(swapChain.imagesView.size())),
			ptrDevice(&info.ptrDevice->device)
		{
			this->frameBuffers = new VkFramebuffer[swapChain.imagesView.size()];
			if (info.flagDepthStencilAttachment)
				this->depthImagesView = new VkImageView[swapChain.imagesView.size()];

			VkFramebufferCreateInfo framebufferCreateInfo = {};
			framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferCreateInfo.renderPass = info.ptrRenderPass->renderPass;
			framebufferCreateInfo.layers = 1;
			framebufferCreateInfo.width = info.width;
			framebufferCreateInfo.height = info.height;
			framebufferCreateInfo.attachmentCount = (info.flagDepthStencilAttachment) ? 2 : 1;

			if (info.flagDepthStencilAttachment)
			{
				this->depthImages = new VkImage[swapChain.imagesView.size()];
				this->depthImagesView = new VkImageView[swapChain.imagesView.size()];
				this->depthImageMemory = new VkDeviceMemory[swapChain.imagesView.size()];
			}

			for (uint32_t index = 0; index < swapChain.imagesView.size(); index++)
			{
				auto imagesView = new VkImageView[framebufferCreateInfo.attachmentCount];
				imagesView[0] = swapChain.imagesView[index];
				if (info.flagDepthStencilAttachment)
				{
					info.ptrDevice->createImage(
							info.width,
							info.height,
							info.ptrDevice->depthFormat,
							VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
							this->depthImages[index],
							this->depthImageMemory[index]);

					this->depthImagesView[index] = info.ptrDevice->createImageView(
							this->depthImages[index],
							info.ptrDevice->depthFormat,
							VK_IMAGE_ASPECT_DEPTH_BIT);
					imagesView[1] = this->depthImagesView[index];
				}
				framebufferCreateInfo.pAttachments = imagesView;
				VkResult result = vkCreateFramebuffer(
						info.ptrDevice->device,
						&framebufferCreateInfo,
						nullptr,
						&this->frameBuffers[index]);
				coders::vulkanProcessingError(result);
				delete[] imagesView;
			}
		}

		FrameBuffer::~FrameBuffer()
		{
			for (uint32_t index = 0; index < this->count; index++)
			{
				vkDestroyFramebuffer(*this->ptrDevice, this->frameBuffers[index], nullptr);

				if (this->depthImagesView != nullptr)
					vkDestroyImageView(
							*this->ptrDevice,
							this->depthImagesView[index],
							nullptr);

				if (this->depthImages != nullptr)
					vkDestroyImage(*this->ptrDevice, this->depthImages[index], nullptr);

				if (this->depthImageMemory != nullptr)
					vkFreeMemory(
							*this->ptrDevice,
							this->depthImageMemory[index],
							nullptr);
			}

			delete[] this->frameBuffers;

			if (this->depthImagesView != nullptr)
				delete[] this->depthImagesView;

			if (this->depthImages != nullptr)
				delete[] this->depthImages;

			if (this->depthImageMemory != nullptr)
				delete[] this->depthImageMemory;
		}

		FrameBuffer FrameBuffer::create(const FrameBufferInfo& info, const SwapChain& swapChain)
		{
			return FrameBuffer(info, swapChain);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
