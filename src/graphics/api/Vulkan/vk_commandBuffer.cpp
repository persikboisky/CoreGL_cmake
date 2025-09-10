//
// Created by kisly on 08.09.2025.
//

#include "vk_commandBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "vk_renderPass.hpp"
#include "vk_frameBuffer.hpp"
#include "../../../util/coders.hpp"
#include <array>

namespace core
{
	namespace vulkan
	{
		CommandBuffer::CommandBuffer(struct Device& device) :
			ptrDevice(device.getPtrDevice()), ptrCommandPool(device.getVkPtrCommandPool())
		{
			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = device.getVkCommandPool();
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = 1;

			VkResult result = vkAllocateCommandBuffers(
				device.getDevice(),
				&allocInfo,
				&this->commandBuffer);
			coders::vulkanProcessingError(result);
		}

		CommandBuffer::~CommandBuffer()
		{
			vkFreeCommandBuffers(
				*this->ptrDevice,
				*this->ptrCommandPool,
				1,
				&this->commandBuffer);
		}

		CommandBuffer CommandBuffer::create(Device& device)
		{
			return CommandBuffer(device);
		}

		CommandBuffer* CommandBuffer::ptrCreate(Device& device)
		{
			return new CommandBuffer(device);
		}

		void CommandBuffer::beginRenderPass(beginRenderPassInfo& brpi)
		{
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = brpi.renderPass->getVkRenderPass();
			renderPassInfo.framebuffer = brpi.frameBuffer.getVkFramebuffer();
			renderPassInfo.renderArea.offset = {0, 0};
			renderPassInfo.renderArea.extent.width =  brpi.extent.width;
			renderPassInfo.renderArea.extent.height = brpi.extent.height;

			// Настройка значений очистки
			std::array<VkClearValue, 2> clearValues = {};
			color::RGBA color = brpi.clearColor;
			color.normalize();

			clearValues[0].color = {{
				color.red,
				color.green,
				color.blue,
				color.alpha
			}};    // Цвет фона (RGB)
			clearValues[1].depthStencil = {1.0f, 0};              // Depth значение

			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			// Начало render pass
			vkCmdBeginRenderPass(
				this->commandBuffer,
				&renderPassInfo,
				VK_SUBPASS_CONTENTS_INLINE  // Команды будут записываться непосредственно
			);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

