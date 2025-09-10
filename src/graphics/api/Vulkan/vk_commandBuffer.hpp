//
// Created by kisly on 08.09.2025.
//

#ifndef VK_COMMANDBUFFER_HPP_
#define VK_COMMANDBUFFER_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include "vk_frameBuffer.hpp"
#include "../../../util/types.hpp"

namespace core
{
	namespace vulkan
	{
		struct beginRenderPassInfo
		{
			class RenderPass* renderPass = nullptr;
			FrameBuffer frameBuffer = {};

			pos2i offset = {0, 0};
			size2i extent = {0, 0};

			color::RGBA clearColor = color::BLACK;
		};

		class CommandBuffer
		{
		 private:
			VkCommandBuffer commandBuffer = {};
			VkDevice *ptrDevice = nullptr;
			VkCommandPool *ptrCommandPool = nullptr;

			bool flagFuncBegin = true;

			explicit CommandBuffer(class Device& device);

		 public:
			~CommandBuffer();

			static CommandBuffer create(class Device& device);
			static CommandBuffer *ptrCreate(class Device& device);

			void beginRenderPass(beginRenderPassInfo& brpi);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDBUFFER_HPP_
