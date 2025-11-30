//
// Created by kisly on 06.09.2025.
//

#include "vk_CommandBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "vk_CommandPool.hpp"
#include "vk_RenderPass.hpp"
#include "vk_FrameBuffer.hpp"
#include "vk_Pipeline.hpp"
#include "vk_VertexBuffer.hpp"
#include "vk_ElementBuffer.hpp"
#include "vk_Buffer.hpp"
#include "vk_Descriptor.hpp"
#include "vk_Image.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		static inline VkShaderStageFlags convertShaderStage(const SHADER_STAGES &stages)
		{
			switch (stages)
			{
			case GEOMETRY_STAGE:
				return VK_SHADER_STAGE_GEOMETRY_BIT;
			case FRAGMENT_STAGE:
				return VK_SHADER_STAGE_FRAGMENT_BIT;
			case VERTEX_STAGE:
				return VK_SHADER_STAGE_VERTEX_BIT;
			case VERTEX_FRAGMENT_STAGES:
				return VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
			default:
				return VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_GEOMETRY_BIT;
			}
		}

		CommandBuffer::CommandBuffer(Device &device, CommandPool &commandPool) : ptrDevice(&device.device),
																				 ptrCommandPool(&commandPool.commandPool)
		{
			VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
			commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandBufferAllocateInfo.commandPool = commandPool.commandPool;
			commandBufferAllocateInfo.pNext = nullptr;
			commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandBufferAllocateInfo.commandBufferCount = 1;

			VkResult result = vkAllocateCommandBuffers(
				device.device,
				&commandBufferAllocateInfo,
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

		CommandBuffer CommandBuffer::create(Device &device, CommandPool &commandPool)
		{
			return CommandBuffer(device, commandPool);
		}

		CommandBuffer *CommandBuffer::ptrCreate(Device &device, CommandPool &commandPool)
		{
			return new CommandBuffer(device, commandPool);
		}

		void CommandBuffer::begin()
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = 0;				  // Опциональные флаги
			beginInfo.pInheritanceInfo = nullptr; // Только для вторичных буферов

			VkResult result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
			coders::vulkanProcessingError(result);
		}

		void CommandBuffer::end()
		{
			VkResult result = vkEndCommandBuffer(commandBuffer);
			coders::vulkanProcessingError(result);
		}

		void CommandBuffer::beginRenderPass(const BeginRenderPassInfo &info)
		{
			VkRenderPassBeginInfo renderPassBeginInfo = {};
			renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassBeginInfo.renderPass = info.ptrRenderPass->renderPass;
			renderPassBeginInfo.renderArea.offset = {info.renderAreaPos.x, info.renderAreaPos.y};
			renderPassBeginInfo.renderArea.extent = {info.renderAreaExtent.width, info.renderAreaExtent.height};
			renderPassBeginInfo.framebuffer = info.ptrFrameBuffer->frameBuffers[info.indexFrameBuffer];
			renderPassBeginInfo.clearValueCount = (info.ptrFrameBuffer->depthImagesView != nullptr) ? 2 : 1;

			std::vector<VkClearValue> clearValues = {};
			if (info.ptrFrameBuffer->depthImagesView != nullptr)
			{
				clearValues.resize(2);

				clearValues[0].color.float32[0] = info.clearColor.red;
				clearValues[0].color.float32[1] = info.clearColor.green;
				clearValues[0].color.float32[2] = info.clearColor.blue;
				clearValues[0].color.float32[3] = info.clearColor.alpha;

				clearValues[1].depthStencil.depth = info.clearDepth;
				clearValues[1].depthStencil.stencil = info.clearStencil;
			}
			else
			{
				clearValues.resize(1);

				clearValues[0].color.float32[0] = info.clearColor.red;
				clearValues[0].color.float32[1] = info.clearColor.green;
				clearValues[0].color.float32[2] = info.clearColor.blue;
				clearValues[0].color.float32[3] = info.clearColor.alpha;
			}

			renderPassBeginInfo.pClearValues = clearValues.data();
			vkCmdBeginRenderPass(this->commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
		}

		void CommandBuffer::endRenderPass()
		{
			vkCmdEndRenderPass(this->commandBuffer);
		}

		void CommandBuffer::bindGraphicsPipeline(const GraphicsPipeline &pipeline)
		{
			vkCmdBindPipeline(this->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
		}

		void CommandBuffer::draw(
			uint32_t firstVertex,
			uint32_t vertexCount,
			uint32_t firstInstance,
			uint32_t instanceCount)
		{
			vkCmdDraw(
				this->commandBuffer,
				vertexCount,
				instanceCount,
				firstVertex,
				firstInstance);
		}

		void CommandBuffer::pushConstants(const PushConstantsInfo &info)
		{
			vkCmdPushConstants(
				this->commandBuffer,
				info.ptrPipelineLayout->layout,
				convertShaderStage(info.shaderStages),
				info.offset,
				info.size,
				info.data);
		}

		void
		CommandBuffer::bindVertexBuffers(
			uint32_t firstBinding,
			uint32_t bindingCount,
			VertexBuffer *ptrBuffers,
			uint64_t *ptrOffset)
		{
			auto buffer = new VkBuffer[bindingCount];
			for (uint32_t index = 0; index < bindingCount; index++)
				buffer[index] = ptrBuffers[index].buffer->buffer;
			vkCmdBindVertexBuffers(
				this->commandBuffer,
				firstBinding,
				bindingCount,
				buffer,
				ptrOffset);
			delete[] buffer;
		}

		void CommandBuffer::bindElementBuffer(struct ElementBuffer &buffer)
		{
			vkCmdBindIndexBuffer(
				this->commandBuffer,
				buffer.buffer,
				0,
				VK_INDEX_TYPE_UINT32);
		}

		void CommandBuffer::drawElements(
			uint32_t firstIndex,
			uint32_t indexCount,
			int32_t vertexOffset,
			uint32_t firstInstance,
			uint32_t instanceCount)
		{
			vkCmdDrawIndexed(
				this->commandBuffer,
				indexCount,
				instanceCount,
				firstIndex,
				vertexOffset,
				firstInstance);
		}

		void CommandBuffer::copyBuffer(Buffer *ptrSrcBuffer, Buffer *ptrDstBuffer, uint64_t size)
		{
			VkBufferCopy copyRegion{};
			copyRegion.srcOffset = 0;
			copyRegion.dstOffset = 0;
			copyRegion.size = size;
			vkCmdCopyBuffer(
				this->commandBuffer,
				ptrSrcBuffer->buffer,
				ptrDstBuffer->buffer,
				1,
				&copyRegion);
		}

		void CommandBuffer::copyImage(Image* ptrSrcBuffer, Image* ptrDstBuffer, uint64_t size)
		{
//			VkImageCopy copyRegion{};
//			copyRegion.srcOffset = 0;
//			copyRegion.dstOffset = 0;
//			copyRegion.size = size;
//			vkCmdCopyImage(
//					this->commandBuffer,
//					ptrSrcBuffer->buffer,
//					ptrDstBuffer->buffer,
//					1,
//					&copyRegion);
		}

		void CommandBuffer::bindDescriptorSet(DescriptorSet &set, PipelineLayout &layout)
		{
			vkCmdBindDescriptorSets(
				this->commandBuffer,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				layout.layout,
				0,
				1,
				&set.descriptorSet,
				0,
				nullptr);
		}

		void CommandBuffer::setCullMode(const CULL_FACE &cullFace)
		{
			vkCmdSetCullMode(this->commandBuffer,
							 (cullFace == CULL_FACE::NONE) ? VK_CULL_MODE_NONE :
							 (cullFace == CULL_FACE::BACK) ? VK_CULL_MODE_BACK_BIT :
							 (cullFace == CULL_FACE::FRONT) ? VK_CULL_MODE_FRONT_BIT :
							 VK_CULL_MODE_FRONT_AND_BACK);
		}

		void CommandBuffer::setScissor(const Rect2D& rect2d)
		{
			VkRect2D rect2D = {};
			rect2D.offset.x = rect2d.x;
			rect2D.offset.y = rect2d.y;
			rect2D.extent.width = rect2d.width;
			rect2D.extent.height = rect2d.height;
			vkCmdSetScissor(this->commandBuffer, 0, 1, &rect2D);
		}

		void CommandBuffer::setPrimitiveTopology(const PRIMITIVE& primitive)
		{
			VkPrimitiveTopology topology;
			switch (primitive)
			{
			case TRIANGLE_STRIP:
				topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
				break;
			case TRIANGLE_LIST:
				topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				break;
			case TRIANGLE_FAN:
				topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
				break;
			case LINE_STRIP:
				topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
				break;
			case POINT_LIST:
				topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
				break;
			default:
				topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
				break;
			}

			vkCmdSetPrimitiveTopology(this->commandBuffer, topology);
		}


	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
