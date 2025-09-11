//
// Created by kisly on 08.09.2025.
//

#include "vk_commandBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "vk_renderPass.hpp"
#include "vk_frameBuffer.hpp"
#include "vk_pipeline.hpp"
#include "../../../util/coders.hpp"

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

		void CommandBuffer::begin()
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			VkResult result = vkBeginCommandBuffer(this->commandBuffer, &beginInfo);
			coders::vulkanProcessingError(result);
		}

		void CommandBuffer::end()
		{
			VkResult result = vkEndCommandBuffer(this->commandBuffer);
			coders::vulkanProcessingError(result);
		}

		void CommandBuffer::beginRenderPass(beginRenderPassInfo& brpi)
		{
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = brpi.renderPass->getVkRenderPass();
			renderPassInfo.framebuffer = brpi.frameBuffer->getVkFramebuffer();
			renderPassInfo.renderArea.offset = {0, 0};
			renderPassInfo.renderArea.extent.width =  brpi.extent.width;
			renderPassInfo.renderArea.extent.height = brpi.extent.height;

			// Настройка значений очистки
			std::vector<VkClearValue> clearValues = {};

			VkClearValue clearValue = {};
			clearValue.color = {{
				brpi.clearColor.red,
				brpi.clearColor.green,
				brpi.clearColor.blue,
				brpi.clearColor.alpha}};
			clearValue.depthStencil.depth = brpi.depth.depth;
			clearValue.depthStencil.depth = brpi.depth.stencil;

			clearValues.push_back(clearValue);

			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

//			// Начало render pass
			vkCmdBeginRenderPass(
				this->commandBuffer,
				&renderPassInfo,
				VK_SUBPASS_CONTENTS_INLINE  // Команды будут записываться непосредственно
			);


		}

		void CommandBuffer::endRenderPas()
		{
			vkCmdEndRenderPass(this->commandBuffer);
		}

		void CommandBuffer::bindPipeline(Pipeline& pipeline)
		{
			vkCmdBindPipeline(
				this->commandBuffer,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				pipeline.getVkPipeline());
		}

		void CommandBuffer::draw(
			uint32_t firstVertex,
			uint32_t vertexCount,
			uint32_t instanceCount,
			uint32_t firstInstance)
		{
			vkCmdDraw(this->commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
		}

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

