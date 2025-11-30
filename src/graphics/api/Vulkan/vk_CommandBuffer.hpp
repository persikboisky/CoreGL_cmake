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

			CommandBuffer(class Device& device, class CommandPool& commandPool);

		public:
			~CommandBuffer();

			static CommandBuffer create(class Device& device, class CommandPool& commandPool);
			static CommandBuffer* ptrCreate(class Device& device, class CommandPool& commandPool);

			void begin();
			void end();

			void beginRenderPass(const BeginRenderPassInfo& info);
			void endRenderPass();

			void bindGraphicsPipeline(const class GraphicsPipeline& pipeline);

			void draw(
					uint32_t firstVertex,
					uint32_t vertexCount,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1);

			void pushConstants(const PushConstantsInfo& info);

			void bindVertexBuffers(
					uint32_t firstBinding,
					uint32_t bindingCount,
					class VertexBuffer* ptrBuffers,
					uint64_t* ptrOffset);

			void bindElementBuffer(class ElementBuffer& buffer);

			void drawElements(
					uint32_t firstIndex,
					uint32_t indexCount,
					int32_t vertexOffset = 0,
					uint32_t firstInstance = 0,
					uint32_t instanceCount = 1);

			void copyBuffer(class Buffer* ptrSrcBuffer, class Buffer* ptrDstBuffer, uint64_t size);
			void copyImage(class Image* ptrSrcBuffer, class Image* ptrDstBuffer, uint64_t size);

			void bindDescriptorSet(class DescriptorSet& set, class PipelineLayout& layout);

			void setCullMode(const CULL_FACE& cullMode);
			void setScissor(const Rect2D& rect2d);
			void setPrimitiveTopology(const vulkan::PRIMITIVE& primitive);
		};
	} // vulkan
}// core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDBUFFER_HPP
