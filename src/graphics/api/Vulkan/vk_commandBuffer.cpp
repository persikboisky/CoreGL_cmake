//
// Created by kisly on 08.09.2025.
//

#include "vk_commandBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "vk_renderPass.hpp"
#include "vk_frameBuffer.hpp"
#include "vk_pipeline.hpp"
#include "vk_commandPool.hpp"
#include "vk_vertexBuffer.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		CommandBuffer::CommandBuffer(struct Device& device, class CommandPool &commandPool) :
			ptrDevice(device.getPtrDevice()), ptrCommandPool(commandPool.getVkPtrCommandPool())
		{
			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = commandPool.getVkCommandPool();
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

		CommandBuffer CommandBuffer::create(Device& device, class CommandPool &commandPool)
		{
			return CommandBuffer(device, commandPool);
		}

		CommandBuffer* CommandBuffer::ptrCreate(Device& device, class CommandPool &commandPool)
		{
			return new CommandBuffer(device, commandPool);
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

		VkCommandBuffer CommandBuffer::getVkCommandBuffer()
		{
			return this->commandBuffer;
		}

		VkCommandBuffer* CommandBuffer::getVkPtrCommandBuffer()
		{
			return &this->commandBuffer;
		}

		void CommandBuffer::pushConstants(Pipeline& pipeline, pushConstantInfo& pci, void *push)
		{
			VkShaderStageFlags shaderStageFlagBits;
			switch (pci.shaderStages)
			{
			case VERTEX_STAGE:
				shaderStageFlagBits = VK_SHADER_STAGE_VERTEX_BIT;
				break;
			case FRAGMENT_STAGE:
				shaderStageFlagBits = VK_SHADER_STAGE_FRAGMENT_BIT;
				break;
			case GEOMETRY_STAGE:
				shaderStageFlagBits = VK_SHADER_STAGE_GEOMETRY_BIT;
				break;
			case VERTEX_FRAGMENT_STAGES:
				shaderStageFlagBits = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;
				break;
			case VERTEX_GEOMETRY_FRAGMENT_STAGES:
				shaderStageFlagBits =
						VK_SHADER_STAGE_FRAGMENT_BIT |
						VK_SHADER_STAGE_VERTEX_BIT |
						VK_SHADER_STAGE_GEOMETRY_BIT;
				break;
			default:
				shaderStageFlagBits = VK_SHADER_STAGE_ALL;
				break;
			}

			vkCmdPushConstants(
					this->commandBuffer,
					pipeline.getVkPipelineLayout(),
					shaderStageFlagBits,
					pci.offset,
					pci.sizeOfBytes,
					push);
		}

		void CommandBuffer::bindVertexBuffers(const bindVertexBuffersInfo& info)
		{
			std::vector<VkBuffer*> ptrVkBuffer = {};

			for (uint32_t index = 0; index < info.bindingCount; index++)
			{
				ptrVkBuffer.push_back(info.ptrVertexBuffers->getPtrVkBuffer());
			}

			vkCmdBindVertexBuffers(
					this->commandBuffer,
					info.firstBinding,
					info.bindingCount,
					*ptrVkBuffer.data(),
					info.ptrOffsets);
		}

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

