//
// Created by kisly on 06.09.2025.
//

#ifndef VK_COMMANDBUFFER_HPP
#define VK_COMMANDBUFFER_HPP

#include "../../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../../types/apiTypes.hpp"
#include "../../../../types/color.hpp"
#include "../../../../types/pos.hpp"
#include "../../../../types/size.hpp"

#include <vector>
#include <vulkan/vulkan.h>

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
	    class IndexBuffer;
	    struct ImageSubresourceRange;

	    struct ClearColor
	    {
	        color::RGBA clearColor = {-1, -1, -1, 1};
	        uint32_t clearStencil = UINT32_MAX;
	        float clearDepth = 75255612928197552291392660701184.0f;
	    };

		struct BeginRenderPassInfo
		{
			RenderPass* ptrRenderPass = nullptr;
			FrameBuffer* ptrFrameBuffer = nullptr;
			Size2ui renderAreaExtent = {0, 0};
			Pos2i renderAreaPos = {0, 0};
		    std::vector<ClearColor> clearAttachments = {};
		};

		struct PushConstantsInfo
		{
			uint32_t offset = 0;
			uint32_t size = 0;
			SHADER_STAGES shaderStages = VERTEX_STAGE;
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

	    // struct PushDescriptorSetInfo
	    // {
     //        PipelineLayout* ptrPipelineLayout = nullptr;
	    //     PIPELINE_BIND_POINT pipelineBindPoint = PIPELINE_BIND_POINT::GRAPHICS;
	    // };

		class CommandBuffer
		{
		protected:
			friend class Queue;
			friend class vk_VertexBuffer;
			friend class ElementBuffer;

		private:
			VkCommandBuffer commandBuffer = {};
			VkDevice* ptrDevice = nullptr;
			VkCommandPool* ptrCommandPool = nullptr;

			explicit CommandBuffer(CommandPool& commandPool);

		public:
			~CommandBuffer();

			static CommandBuffer create(CommandPool& commandPool);
			static CommandBuffer* ptrCreate(CommandPool& commandPool);

			void begin() const;
			void end() const;

			void beginRenderPass(const BeginRenderPassInfo& info) const;
			void endRenderPass() const;

		    void nextSubpass() const;

			void bindGraphicsPipeline(const GraphicsPipeline& pipeline) const;

			void draw(
					uint32_t firstVertex,
					uint32_t vertexCount,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1) const;

			void pushConstants(const PushConstantsInfo& info) const;
		    // void pushDescriptorSet(const PushDescriptorSetInfo& info);

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

		    void bindIndexBuffer(const Buffer& buffer, const INDEX_TYPE& type = INDEX_TYPE::UINT32) const;
			void bindIndexBuffer(const IndexBuffer& buffer, const INDEX_TYPE& type = INDEX_TYPE::UINT32) const;

			void drawIndexed(
					uint32_t firstIndex,
					uint32_t indexCount,
					int32_t vertexOffset = 0,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1) const;

			void copyBuffer(const Buffer* ptrSrcBuffer, const Buffer* ptrDstBuffer, uint64_t size) const;
		    void copyBufferToImage(const ImageBufferCopyInfo& info) const;

			void bindDescriptorSet(const DescriptorSet& set, const PipelineLayout& layout) const;

			void setCullMode(const CULL_MODE& cullMode) const;
			void setScissor(const Rect2D& rect2d) const;
			void setPrimitiveTopology(const vulkan::PRIMITIVE& primitive) const;

            void pipelineImageMemoryBarrier(const PipelineImageMemoryBarrier& info) const;
		};
	} // vulkan
}// core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDBUFFER_HPP
