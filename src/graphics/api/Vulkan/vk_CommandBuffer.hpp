//
// Created by kisly on 06.09.2025.
//

#ifndef VK_COMMANDBUFFER_HPP
#define VK_COMMANDBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include "../../../types/size.hpp"
#include "../../../types/pos.hpp"
#include "../../../types/color.hpp"
#include "../../../types/apiTypes.hpp"

namespace core
{
	namespace vulkan
	{
	    class Image;
	    class Buffer;
	    class RenderPass;
	    class FrameBuffer;
	    class CommandPool;
	    class VertexBuffer;
	    class GraphicsPipeline;
	    class DescriptorSet;
	    class ElementBuffer;
	    struct ImageSubresourceRange;

		struct BeginRenderPassInfo
		{
			RenderPass* ptrRenderPass = nullptr;
			FrameBuffer* ptrFrameBuffer = nullptr;
			uint32_t indexFrameBuffer = 0;
			Size2ui renderAreaExtent = {0, 0};
			Pos2i renderAreaPos = {0, 0};

			color::RGBA clearColor = color::RGB();
			float clearDepth = 1.0f;
			uint32_t clearStencil = 0;
		};

		struct PushConstantsInfo
		{
			uint32_t offset = 0;
			uint32_t size = 0;
			vulkan::SHADER_STAGES shaderStages = VERTEX_STAGE;
			class PipelineLayout* ptrPipelineLayout = nullptr;
			const void* data = nullptr;
		};

	    struct ImageSubresourceLayers
	    {
	        IMAGE_ASPECT aspect = IMAGE_ASPECT::COLOR;
	        uint32_t mipLevel = 0;
	        uint32_t baseArrayLayer = 0;
	        uint32_t layerCount = 1;
	    };

	    struct PipelineImageMemoryBarrier
	    {
            IMAGE_LAYOUT oldLayout = IMAGE_LAYOUT::UNDEFINED;
	        IMAGE_LAYOUT newLayout = IMAGE_LAYOUT::UNDEFINED;
	        Image* ptrImage = nullptr;

	        bool QueueFamilyIgnored = true;
	        uint32_t srcQueueFamilyIndex = 0;
	        uint32_t dstQueueFamilyIndex = 0;

	        ImageSubresourceRange* ptrImageSubresourceRange = nullptr;

	        ACCESS srcAccessMask = ACCESS::NONE;
	        ACCESS dstAccessMask = ACCESS::NONE;

	        PIPELINE_STAGE srcStageMask = PIPELINE_STAGE::NONE;
            PIPELINE_STAGE dstStageMask = PIPELINE_STAGE::NONE;
	    };

	    struct ImageBufferCopyInfo
	    {
            uint64_t bufferOffset = 0;
	        uint32_t bufferRowLength = 0;
	        uint32_t bufferImageHeight = 0;
	        ImageSubresourceLayers* ptrImageSubresourceRange = nullptr;
	        Pos3i imageOffset = {0, 0, 0};
	        Size3ui imageExtent = {0, 0, 0};

	        Buffer* ptrSrcBuffer = nullptr;
	        Image* ptrDstImage = nullptr;
	        IMAGE_LAYOUT layout = IMAGE_LAYOUT::TRANSFER_DST_OPTIMAL;
	    };

		class CommandBuffer
		{
		protected:
			friend class Queue;
			friend class VertexBuffer;
			friend class ElementBuffer;

		private:
			VkCommandBuffer commandBuffer = {};
			VkDevice* ptrDevice = nullptr;
			VkCommandPool* ptrCommandPool = nullptr;

			CommandBuffer(CommandPool& commandPool);

		public:
			~CommandBuffer();

			static CommandBuffer create(CommandPool& commandPool);
			static CommandBuffer* ptrCreate(CommandPool& commandPool);

			void begin() const;
			void end() const;

			void beginRenderPass(const BeginRenderPassInfo& info) const;
			void endRenderPass() const;

			void bindGraphicsPipeline(const GraphicsPipeline& pipeline) const;

			void draw(
					uint32_t firstVertex,
					uint32_t vertexCount,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1) const;

			void pushConstants(const PushConstantsInfo& info) const;

			void bindVertexBuffers(
					uint32_t firstBinding,
					uint32_t bindingCount,
					const VertexBuffer* ptrBuffers,
					const uint64_t* ptrOffset = nullptr) const;

			void bindVertexBuffers(
					uint32_t firstBinding,
					uint32_t bindingCount,
					const Buffer* ptrBuffers,
					const uint64_t* ptrOffset = nullptr) const;

			void bindElementBuffer(const ElementBuffer& buffer) const;

			void drawElements(
					uint32_t firstIndex,
					uint32_t indexCount,
					int32_t vertexOffset = 0,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1) const;

			void copyBuffer(const Buffer* ptrSrcBuffer, const Buffer* ptrDstBuffer, uint64_t size) const;
		    void copyBufferToImage(const ImageBufferCopyInfo& info);

			void bindDescriptorSet(const DescriptorSet& set, const PipelineLayout& layout) const;

			void setCullMode(const CULL_MODE& cullMode) const;
			void setScissor(const Rect2D& rect2d) const;
			void setPrimitiveTopology(const vulkan::PRIMITIVE& primitive) const;

            void pipelineImageMemoryBarrier(const PipelineImageMemoryBarrier& info);
		};
	} // vulkan
}// core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDBUFFER_HPP
