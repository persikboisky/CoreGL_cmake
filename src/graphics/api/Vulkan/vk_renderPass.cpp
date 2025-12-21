//
// Created by kisly on 05.09.2025.
//

#include "vk_RenderPass.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/Coders.hpp"
#include "vk_Attachments.hpp"
#include "vk_Device.hpp"

namespace core
{
	namespace vulkan
	{
		static inline VkAttachmentLoadOp convertAttachmentLoadOp(const LOAD_OP& loadOp)
		{
			return (loadOp == LOAD_OP::LOAD_OP_LOAD) ? VK_ATTACHMENT_LOAD_OP_LOAD : VK_ATTACHMENT_LOAD_OP_CLEAR;
		}

		RenderPass::RenderPass(const RenderPassInfo& info) : ptrDevice(&info.ptrDevice->device)
		{

			VkAttachmentDescription colorAttachment = {};
			VkAttachmentReference colorRef = {};
				// Формат
				colorAttachment.format = info.ptrDevice->surfaceFormat.format;
				// Без мультисэмплинга
				colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
				// Очистить при начале прохода
				colorAttachment.loadOp = convertAttachmentLoadOp(info.ptrColorAttachment->loadOp);
				// Сохранить для отображения
				colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				colorAttachment.initialLayout = Convert::convert(info.ptrColorAttachment->initLayout);
				colorAttachment.finalLayout = Convert::convert(info.ptrColorAttachment->finalLayout);

				colorRef.attachment = 0;
				colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			VkAttachmentDescription depthAttachment = {};
			VkAttachmentReference depthRef = {};
			if (info.ptrDepthStencilAttachment != nullptr)
			{

				depthAttachment.format = info.ptrDevice->depthFormat;
				depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
				depthAttachment.loadOp = convertAttachmentLoadOp(info.ptrDepthStencilAttachment->loadOp);
				depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				depthAttachment.initialLayout = Convert::convert(info.ptrDepthStencilAttachment->initLayout);
				depthAttachment.finalLayout = Convert::convert(info.ptrDepthStencilAttachment->finalLayout);

				depthRef.attachment = 1;
				depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			}

			std::vector<VkAttachmentDescription> attachmentsDescription = {};
			attachmentsDescription.resize(
					(info.ptrColorAttachment != nullptr && info.ptrDepthStencilAttachment != nullptr) ?
					2 :
					1);

			if (info.ptrColorAttachment != nullptr && info.ptrDepthStencilAttachment != nullptr)
			{
				attachmentsDescription[0] = colorAttachment;
				attachmentsDescription[1] = depthAttachment;
			}
			else
				attachmentsDescription[0] = colorAttachment;

			VkSubpassDescription subpass = {};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;    // Графический pipeline
			subpass.colorAttachmentCount = 1;                               // Один аттачмент цвета
			subpass.pColorAttachments = (info.ptrColorAttachment != nullptr) ?
										&colorRef : nullptr;
			subpass.pDepthStencilAttachment =  (info.ptrDepthStencilAttachment != nullptr) ?
										&depthRef : nullptr;
			// Дополнительные типы аттачментов (если нужны):
			// - pInputAttachments: аттачменты для чтения в шейдере
			// - pResolveAttachments: для мультисэмплинга
			// - pPreserveAttachments: аттачменты которые сохраняются между подпроходами

			VkRenderPassCreateInfo renderPassCreateInfo = {};
			renderPassCreateInfo.flags = 0;
			renderPassCreateInfo.pNext = nullptr;
			renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachmentsDescription.size());
			renderPassCreateInfo.pAttachments = attachmentsDescription.data();
			renderPassCreateInfo.dependencyCount = 0;
			renderPassCreateInfo.pDependencies = nullptr;
			renderPassCreateInfo.pSubpasses = &subpass;
			renderPassCreateInfo.subpassCount = 1;

			VkResult result = vkCreateRenderPass(
					*ptrDevice,
					&renderPassCreateInfo,
					nullptr,
					&this->renderPass);
			Coders::vulkanProcessingError(result);
		}

		RenderPass RenderPass::create(const RenderPassInfo& info)
		{
			return RenderPass(info);
		}

		RenderPass* RenderPass::ptrCreate(const RenderPassInfo& info)
		{
			return new RenderPass(info);
		}

		RenderPass::~RenderPass()
		{
			vkDestroyRenderPass(*this->ptrDevice, this->renderPass, nullptr);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

