//
// Created by kisly on 08.09.2025.
//

#ifndef VK_COMMANDBUFFER_HPP_
#define VK_COMMANDBUFFER_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include "../../../util/types.hpp"

namespace core
{
	namespace vulkan
	{
		struct beginRenderPassInfo
		{
			class RenderPass* renderPass = nullptr;
			class FrameBuffer* frameBuffer = nullptr;

			pos2i offset = {0, 0};
			size2i extent = {0, 0};
			DepthSize depth = {1.0, 0.0};

			color::RGBA clearColor = color::BLACK;
		};

		class CommandBuffer
		{
		 private:
			VkCommandBuffer commandBuffer = {};
			VkDevice *ptrDevice = nullptr;
			VkCommandPool *ptrCommandPool = nullptr;

			explicit CommandBuffer(class Device& device, class CommandPool &commandPool);

		 public:
			~CommandBuffer();

			static CommandBuffer create(class Device& device, class CommandPool &commandPool);
			static CommandBuffer *ptrCreate(class Device& device, class CommandPool &commandPool);

			void begin();
			void end();

			void beginRenderPass(beginRenderPassInfo& brpi);
			void endRenderPas();

			void bindPipeline(class Pipeline& pipeline);

			void draw(uint32_t firstVertex, uint32_t vertexCount, uint32_t instanceCount = 1, uint32_t firstInstance = 0);

			VkCommandBuffer getVkCommandBuffer();
			VkCommandBuffer *getVkPtrCommandBuffer();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDBUFFER_HPP_
