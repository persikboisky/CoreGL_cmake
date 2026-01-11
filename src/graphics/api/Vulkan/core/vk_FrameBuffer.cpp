//
// Created by kisly on 05.09.2025.
//

#include "vk_FrameBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../../util/Coders.hpp"
#include "vk_Device.hpp"
#include "vk_Image.hpp"
#include "vk_RenderPass.hpp"
#include "vk_SwapChain.hpp"

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

		FrameBuffer::FrameBuffer(const FrameBufferInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
            auto* pAttachments = new VkImageView[info.vecPtrImageViews.size()];
		    for (uint32_t i = 0; i < info.vecPtrImageViews.size(); i++)
		        pAttachments[i] = info.vecPtrImageViews[i]->imageView;

		    VkFramebufferCreateInfo framebufferCreateInfo = {};
		    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		    framebufferCreateInfo.renderPass = info.ptrRenderPass->renderPass;
		    framebufferCreateInfo.layers = 1;
		    framebufferCreateInfo.width = info.width;
		    framebufferCreateInfo.height = info.height;
		    framebufferCreateInfo.attachmentCount = static_cast<uint32_t>(info.vecPtrImageViews.size());
		    framebufferCreateInfo.pAttachments = pAttachments;
		    VkResult result = vkCreateFramebuffer(
                    info.ptrDevice->device,
                    &framebufferCreateInfo,
                    nullptr,
                    &frameBuffer);
		    Coders::vulkanProcessingError(result);

		    delete [] pAttachments;
		}

		FrameBuffer::~FrameBuffer()
		{
		    vkDestroyFramebuffer(*ptrDevice, frameBuffer, nullptr);
		}

        FrameBuffer FrameBuffer::create(const FrameBufferInfo &info)
        {
		    return FrameBuffer(info);
        }

        FrameBuffer *FrameBuffer::ptrCreate(const FrameBufferInfo &info)
        {
		    return new FrameBuffer(info);
        }
    } // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
