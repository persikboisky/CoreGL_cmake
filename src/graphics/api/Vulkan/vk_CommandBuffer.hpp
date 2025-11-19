//
// Created by kisly on 06.09.2025.
//

#ifndef VK_COMMANDBUFFER_HPP
#define VK_COMMANDBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include "../../../util/types.hpp"

namespace core
{
	namespace vulkan
	{
		struct BeginRenderPassInfo
		{
			class RenderPass* ptrRenderPass = nullptr;
			class FrameBuffer* ptrFrameBuffer = nullptr;
			uint32_t indexFrameBuffer = 0;
			size2ui renderAreaExtent = {0, 0};
			pos2i renderAreaPos = {0, 0};

			color::RGBA clearColor = color::COLOR::BLACK;
			float clearDepth = 1.0f;
			uint32_t clearStencil = 0;
		};

		class CommandBuffer
		{
		protected:
			friend class Queue;

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
		};
	} // vulkan
}// core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDBUFFER_HPP
