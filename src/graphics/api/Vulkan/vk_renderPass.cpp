//
// Created by kisly on 05.09.2025.
//

#include "vk_renderPass.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "../../../util/coders.hpp"
#include <vector>
#include <iostream>
#include <array>

namespace core
{
	namespace vulkan
	{
		RenderPass::RenderPass(const RenderPassInfo& info) :
				device(&info.ptrDevice->device), depthAttachment(info.depthTest),
				clearBuffers(info.clearBuffers)
		{
			// Цветовой attachment
			VkAttachmentDescription colorAttachment = {};
			colorAttachment.format = info.ptrDevice->surfaceFormat.format;
			colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
			colorAttachment.loadOp = {
					(info.clearBuffers) ?
					VK_ATTACHMENT_LOAD_OP_CLEAR :
					VK_ATTACHMENT_LOAD_OP_LOAD
			};
			colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			colorAttachment.initialLayout = {
					(info.clearBuffers) ?
					VK_IMAGE_LAYOUT_UNDEFINED :
					VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			};
			colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

			// Depth attachment
			VkAttachmentDescription depthAttachment = {};
			depthAttachment.format = VK_FORMAT_D32_SFLOAT;
			depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
			depthAttachment.loadOp = {
					(info.clearBuffers) ?
					VK_ATTACHMENT_LOAD_OP_CLEAR :
					VK_ATTACHMENT_LOAD_OP_LOAD
			};
			depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			depthAttachment.initialLayout = {
					(info.clearBuffers) ?
					VK_IMAGE_LAYOUT_UNDEFINED :
					VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL
			};
			depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			// Attachment references
			VkAttachmentReference colorAttachmentRef = {};
			colorAttachmentRef.attachment = 0;
			colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			VkAttachmentReference depthAttachmentRef = {};
			depthAttachmentRef.attachment = 1;
			depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			// Subpass
			VkSubpassDescription subpass = {};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = &colorAttachmentRef;
			if (info.depthTest)
				subpass.pDepthStencilAttachment = &depthAttachmentRef;
			else
				subpass.pDepthStencilAttachment = VK_NULL_HANDLE;

			// Создание render pass
			std::vector<VkAttachmentDescription> attachments = {};
			if (info.depthTest)
			{
				attachments.resize(2);
				attachments[1] = depthAttachment;
			}
			else
				attachments.resize(1);
			attachments[0] = colorAttachment;

			// 4. Создание render pass
			VkRenderPassCreateInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			renderPassInfo.pAttachments = attachments.data();
			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpass; // Массив subpass'ов
			// RenderPassInfo.pDependencies = dependencies.data();
			// RenderPassInfo.dependencyCount = 2;

			VkResult result = vkCreateRenderPass(
					info.ptrDevice->device,
					&renderPassInfo,
					nullptr,
					&renderPass);
			coders::vulkanProcessingError(result);
		}

		RenderPass::~RenderPass()
		{
			vkDestroyRenderPass(
					*this->device,
					this->renderPass,
					nullptr);
		}

		RenderPass RenderPass::create(const RenderPassInfo& info)
		{
			return RenderPass(info);
		}

		RenderPass* RenderPass::ptrCreate(const RenderPassInfo& info)
		{
			return new RenderPass(info);
		}

		VkRenderPass RenderPass::getVkRenderPass()
		{
			return this->renderPass;
		}

		VkRenderPass* RenderPass::getVkPtrRenderPass()
		{
			return &this->renderPass;
		}

		bool RenderPass::getStateDepth() const
		{
			return this->depthAttachment;
		}

		bool RenderPass::getStateClear() const
		{
			return this->clearBuffers;
		}
	}// vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
