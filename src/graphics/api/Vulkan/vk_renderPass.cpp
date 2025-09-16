//
// Created by kisly on 05.09.2025.
//

#include "vk_renderPass.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "../../../util/coders.hpp"
#include <vector>
#include <iostream>

namespace core
{
	namespace vulkan
	{
		RenderPass::RenderPass(const renderPassInfo& info) :
			device(info.device->getPtrDevice()), depthAttachment(info.depthAttachment)
		{
			// 1. Описание attachment (цветового буфера)
			VkAttachmentDescription colorAttachment{};
			colorAttachment.format = info.device->getVkSurfaceFormat().format;
			colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;   					// Без мультисэмплинга
			colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;     			// Очищаем перед рендером
			colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;   			// Сохраняем после рендера
			colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;   	// Не используем станциль
			colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE; 	// Не используем станциль
			colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;         	// Начальное состояние не важно
			colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;     	// Для отображения в swapchain

			// 2. Ссылка на attachment (для subpass)
			VkAttachmentReference colorAttachmentRef{};
			colorAttachmentRef.attachment = 0;  // Индекс attachment'а в массиве
			colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;  // Оптимальный layout для рендера

			// 3. Описание subpass
			VkSubpassDescription subpass{};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;  // Графический pipeline
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = &colorAttachmentRef;  // Цветовые attachment'ы
			subpass.pDepthStencilAttachment = VK_NULL_HANDLE;

			std::vector<VkAttachmentDescription> attachments = {
				colorAttachment
			};

			// атачмент для теста глубины
			if (info.depthAttachment)
			{
				VkAttachmentDescription depthAttachment{};
				depthAttachment.format = VK_FORMAT_D32_SFLOAT;
				depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
				depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
				depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
				depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

				VkAttachmentReference depthAttachmentRef{};
				depthAttachmentRef.attachment = 1; // Индекс после color attachment
				depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

				subpass.pDepthStencilAttachment = &depthAttachmentRef;

				attachments.push_back(depthAttachment);
			}

			// 4. Создание render pass
			VkRenderPassCreateInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			renderPassInfo.pAttachments = attachments.data();
			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpass;           // Массив subpass'ов

			VkResult result = vkCreateRenderPass(
				info.device->getDevice(),
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

		RenderPass RenderPass::create(const renderPassInfo& info)
		{
			return RenderPass(info);
		}

		RenderPass* RenderPass::ptrCreate(const renderPassInfo& info)
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
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
