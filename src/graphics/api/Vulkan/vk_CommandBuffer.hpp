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
		struct BeginRenderPassInfo
		{
			class RenderPass* ptrRenderPass = nullptr;
			class FrameBuffer* ptrFrameBuffer = nullptr;
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

	    struct PipelineImageMemoryBarrier
	    {

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

			CommandBuffer(class CommandPool& commandPool);

		public:
			~CommandBuffer();

			static CommandBuffer create(class CommandPool& commandPool);
			static CommandBuffer* ptrCreate(class CommandPool& commandPool);

			void begin() const;
			void end() const;

			void beginRenderPass(const BeginRenderPassInfo& info) const;
			void endRenderPass() const;

			void bindGraphicsPipeline(const class GraphicsPipeline& pipeline) const;

			void draw(
					uint32_t firstVertex,
					uint32_t vertexCount,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1) const;

			void pushConstants(const PushConstantsInfo& info) const;

			void bindVertexBuffers(
					const uint32_t firstBinding,
					const uint32_t bindingCount,
					const class VertexBuffer* ptrBuffers,
					const uint64_t* ptrOffset = nullptr) const;

			void bindVertexBuffers(
					uint32_t firstBinding,
					uint32_t bindingCount,
					const class Buffer* ptrBuffers,
					const uint64_t* ptrOffset = nullptr) const;

			void bindElementBuffer(const class ElementBuffer& buffer) const;

			void drawElements(
					uint32_t firstIndex,
					uint32_t indexCount,
					int32_t vertexOffset = 0,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1) const;

			void copyBuffer(const class Buffer* ptrSrcBuffer, const class Buffer* ptrDstBuffer, uint64_t size) const;
            // void copyImage(class Image* ptrSrcBuffer, class Image* ptrDstBuffer, uint64_t size);

			void bindDescriptorSet(const class DescriptorSet& set, const class PipelineLayout& layout) const;

			void setCullMode(const CULL_MODE& cullMode) const;
			void setScissor(const Rect2D& rect2d) const;
			void setPrimitiveTopology(const vulkan::PRIMITIVE& primitive) const;

            void pipelineImageMemoryBarrier(const PipelineImageMemoryBarrier& info);
		};
	} // vulkan
}// core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDBUFFER_HPP
