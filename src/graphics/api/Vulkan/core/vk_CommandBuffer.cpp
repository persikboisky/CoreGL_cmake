//
// Created by kisly on 06.09.2025.
//

#include "vk_CommandBuffer.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../../util/Coders.hpp"
#include "vk_CommandPool.hpp"
#include "vk_Descriptor.hpp"
#include "vk_Device.hpp"
// #include "vk_ElementBuffer.hpp"
#include "../vk_IndexBuffer.hpp"
#include "../vk_VertexBuffer.hpp"
#include "vk_Buffer.hpp"
#include "vk_FrameBuffer.hpp"
#include "vk_Image.hpp"
#include "vk_Pipeline.hpp"
#include "vk_RenderPass.hpp"

namespace core
{
	namespace vulkan
	{
		static VkShaderStageFlags convertShaderStage(const SHADER_STAGES &stages)
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

		CommandBuffer::CommandBuffer(CommandPool &commandPool) :
	        ptrDevice(commandPool.ptrDevice), ptrCommandPool(&commandPool.commandPool)
		{
			VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
			commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandBufferAllocateInfo.commandPool = commandPool.commandPool;
			commandBufferAllocateInfo.pNext = nullptr;
			commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandBufferAllocateInfo.commandBufferCount = 1;

            const VkResult result = vkAllocateCommandBuffers(
				*ptrDevice,
				&commandBufferAllocateInfo,
				&this->commandBuffer);
			Coders::vulkanProcessingError(result);
		}

		CommandBuffer::~CommandBuffer()
		{
			vkFreeCommandBuffers(
				*this->ptrDevice,
				*this->ptrCommandPool,
				1,
				&this->commandBuffer);
		}

		CommandBuffer CommandBuffer::create(CommandPool &commandPool)
		{
			return CommandBuffer(commandPool);
		}

		CommandBuffer *CommandBuffer::ptrCreate( CommandPool &commandPool)
		{
			return new CommandBuffer(commandPool);
		}

		void CommandBuffer::begin() const
        {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = 0;				  // Опциональные флаги
			beginInfo.pInheritanceInfo = nullptr; // Только для вторичных буферов

            const VkResult result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
			Coders::vulkanProcessingError(result);
		}

		void CommandBuffer::end() const
        {
            const VkResult result = vkEndCommandBuffer(commandBuffer);
			Coders::vulkanProcessingError(result);
		}

		void CommandBuffer::beginRenderPass(const BeginRenderPassInfo &info) const
        {
			VkRenderPassBeginInfo renderPassBeginInfo = {};
			renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassBeginInfo.renderPass = info.ptrRenderPass->renderPass;
			renderPassBeginInfo.renderArea.offset = {info.renderAreaPos.x, info.renderAreaPos.y};
			renderPassBeginInfo.renderArea.extent = {info.renderAreaExtent.width, info.renderAreaExtent.height};
			renderPassBeginInfo.framebuffer = info.ptrFrameBuffer->frameBuffer;

            auto* pClearValues = new VkClearValue[info.clearAttachments.size()];
            uint32_t i = 0;
            for (const auto& value : info.clearAttachments)
            {
                if (value.clearColor.red >= 0 &&
                    value.clearColor.green >= 0 &&
                    value.clearColor.blue >= 0)
                {
                    pClearValues[i].color.float32[0] = value.clearColor.red;
                    pClearValues[i].color.float32[1] = value.clearColor.green;
                    pClearValues[i].color.float32[2] = value.clearColor.blue;
                    pClearValues[i].color.float32[3] = value.clearColor.alpha;
                }

                if (value.clearDepth < 75255612928197552291392660701184.0f)
                    pClearValues[i].depthStencil.depth = value.clearDepth;

                if (value.clearStencil < UINT32_MAX)
                    pClearValues[i].depthStencil.stencil = value.clearStencil;

                i++;
            }

		    renderPassBeginInfo.clearValueCount = info.clearAttachments.size();
			renderPassBeginInfo.pClearValues = pClearValues;
			vkCmdBeginRenderPass(this->commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

		    delete[] pClearValues;
		}

		void CommandBuffer::endRenderPass() const
        {
			vkCmdEndRenderPass(this->commandBuffer);
		}

        void CommandBuffer::nextSubpass() const
        {
		    vkCmdNextSubpass(commandBuffer, VK_SUBPASS_CONTENTS_INLINE);
        }

        void CommandBuffer::bindGraphicsPipeline(const GraphicsPipeline &pipeline) const
        {
			vkCmdBindPipeline(this->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
		}

		void CommandBuffer::draw(
			uint32_t firstVertex,
			uint32_t vertexCount,
			uint32_t firstInstance,
			uint32_t instanceCount) const
        {
			vkCmdDraw(
				this->commandBuffer,
				vertexCount,
				instanceCount,
				firstVertex,
				firstInstance);
		}

		void CommandBuffer::pushConstants(const PushConstantsInfo &info) const
        {
			vkCmdPushConstants(
				this->commandBuffer,
				info.ptrPipelineLayout->layout,
				convertShaderStage(info.shaderStages),
				info.offset,
				info.size,
				info.data);
		}

      //   void CommandBuffer::pushDescriptorSet(const PushDescriptorSetInfo &info)
      //   {
		    // VkWriteDescriptorSet writeDescriptorSet = {};
		    // writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
      //
		    // vkCmdPushDescriptorSet(
		    //     commandBuffer,
		    //     Convert::convert(info.pipelineBindPoint),
		    //     info.ptrPipelineLayout->layout,
		    //     0,
		    //     1,
		    //     &writeDescriptorSet);
      //   }

        void
		CommandBuffer::bindVertexBuffers(
			uint32_t firstBinding,
			uint32_t bindingCount,
			const VertexBuffer *ptrBuffers,
			const uint64_t *ptrOffset) const
        {
		    uint64_t offset = 0;
            const auto buffer = new VkBuffer[bindingCount];
			for (uint32_t index = 0; index < bindingCount; index++)
				buffer[index] = ptrBuffers[index].ptrBuffer->buffer;
			vkCmdBindVertexBuffers(
				this->commandBuffer,
				firstBinding,
				bindingCount,
				buffer,
				ptrOffset == nullptr ? &offset : ptrOffset);
			delete[] buffer;
		}

		void
		CommandBuffer::bindVertexBuffers(
		    const uint32_t  firstBinding,
		    const uint32_t  bindingCount,
		    const Buffer   *ptrBuffers,
		    const uint64_t *ptrOffset) const
        {
            const uint64_t offset = 0;

			auto buffer = new VkBuffer[bindingCount];
			for (uint32_t index = 0; index < bindingCount; index++)
				buffer[index] = ptrBuffers[index].buffer;
			vkCmdBindVertexBuffers(
					this->commandBuffer,
					firstBinding,
					bindingCount,
					buffer,
					ptrOffset == nullptr ? &offset : ptrOffset);
			delete[] buffer;
		}

        void CommandBuffer::bindIndexBuffer(const Buffer &buffer, const INDEX_TYPE& type) const
		{
		    vkCmdBindIndexBuffer(
                this->commandBuffer,
                buffer.buffer,
                0,
                Convert::convert(type));
		}

        void CommandBuffer::bindIndexBuffer(const IndexBuffer &buffer, const INDEX_TYPE& type) const
        {
			vkCmdBindIndexBuffer(
				this->commandBuffer,
				buffer.ptrBuffer->buffer,
				0,
				Convert::convert(type));
		}

		void CommandBuffer::drawIndexed(
			uint32_t firstIndex,
			uint32_t indexCount,
			int32_t vertexOffset,
			uint32_t firstInstance,
			uint32_t instanceCount) const
        {
			vkCmdDrawIndexed(
				this->commandBuffer,
				indexCount,
				instanceCount,
				firstIndex,
				vertexOffset,
				firstInstance);
		}

		void CommandBuffer::copyBuffer(const Buffer *ptrSrcBuffer, const Buffer *ptrDstBuffer, uint64_t size) const
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

        void CommandBuffer::copyBufferToImage(const ImageBufferCopyInfo &info) const
        {
		    VkBufferImageCopy region = {};
		    region.bufferOffset = info.bufferOffset;
		    region.bufferRowLength = info.bufferRowLength;
		    region.bufferImageHeight = info.bufferImageHeight;
		    region.imageSubresource.aspectMask = Convert::convert(info.ptrImageSubresourceRange->aspect);
		    region.imageSubresource.mipLevel = info.ptrImageSubresourceRange->mipLevel;
		    region.imageSubresource.baseArrayLayer = info.ptrImageSubresourceRange->baseArrayLayer;
		    region.imageSubresource.layerCount = info.ptrImageSubresourceRange->layerCount;
		    region.imageOffset.x = info.imageOffset.x;
            region.imageOffset.y = info.imageOffset.y;
		    region.imageOffset.z = info.imageOffset.z;
		    region.imageExtent.width = info.imageExtent.width;
		    region.imageExtent.height = info.imageExtent.height;
		    region.imageExtent.depth = info.imageExtent.depth;

		    vkCmdCopyBufferToImage(
                commandBuffer,
                info.ptrSrcBuffer->buffer,
                info.ptrDstImage->image,
                Convert::convert(info.layout),
                1,
                &region
            );
        }

		void CommandBuffer::bindDescriptorSet(const DescriptorSet &set, const PipelineLayout &layout) const
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

		void CommandBuffer::setCullMode(const CULL_MODE &cullMode) const
        {
			vkCmdSetCullMode(this->commandBuffer,
							 (cullMode == CULL_MODE::NONE) ? VK_CULL_MODE_NONE :
							 (cullMode == CULL_MODE::BACK) ? VK_CULL_MODE_BACK_BIT :
							 (cullMode == CULL_MODE::FRONT) ? VK_CULL_MODE_FRONT_BIT :
							 VK_CULL_MODE_FRONT_AND_BACK);
		}

		void CommandBuffer::setScissor(const Rect2D& rect2d) const
        {
			VkRect2D rect2D = {};
			rect2D.offset.x = rect2d.x;
			rect2D.offset.y = rect2d.y;
			rect2D.extent.width = rect2d.width;
			rect2D.extent.height = rect2d.height;
			vkCmdSetScissor(this->commandBuffer, 0, 1, &rect2D);
		}

		void CommandBuffer::setPrimitiveTopology(const PRIMITIVE& primitive) const
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

        void CommandBuffer::pipelineImageMemoryBarrier(const PipelineImageMemoryBarrier &info) const
        {
            VkImageMemoryBarrier imageMemoryBarrier = {};
		    imageMemoryBarrier.pNext = nullptr;
		    imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		    imageMemoryBarrier.newLayout = Convert::convert(info.newLayout);
		    imageMemoryBarrier.oldLayout = Convert::convert(info.oldLayout);
		    imageMemoryBarrier.image = info.ptrImage->image;
		    imageMemoryBarrier.dstQueueFamilyIndex = info.QueueFamilyIgnored ? VK_QUEUE_FAMILY_IGNORED : info.dstQueueFamilyIndex;
		    imageMemoryBarrier.srcQueueFamilyIndex = info.QueueFamilyIgnored ? VK_QUEUE_FAMILY_IGNORED : info.srcQueueFamilyIndex;
		    imageMemoryBarrier.subresourceRange.aspectMask = Convert::convert(info.ptrImageSubresourceRange->aspect);
		    imageMemoryBarrier.subresourceRange.baseMipLevel = info.ptrImageSubresourceRange->baseMipLevel;
		    imageMemoryBarrier.subresourceRange.baseArrayLayer = info.ptrImageSubresourceRange->baseArrayLayer;
		    imageMemoryBarrier.subresourceRange.layerCount = info.ptrImageSubresourceRange->layerCount;
		    imageMemoryBarrier.subresourceRange.levelCount = info.ptrImageSubresourceRange->levelCount;
		    imageMemoryBarrier.srcAccessMask = Convert::convert(info.srcAccessMask);
		    imageMemoryBarrier.dstAccessMask = Convert::convert(info.dstAccessMask);
		    vkCmdPipelineBarrier(
		        commandBuffer,
		        Convert::convert(info.srcStageMask),
		        Convert::convert(info.dstStageMask),
		        0,
		        0,
		        nullptr,
		        0,
		        nullptr,
		        1,
		        &imageMemoryBarrier);
        }

	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
