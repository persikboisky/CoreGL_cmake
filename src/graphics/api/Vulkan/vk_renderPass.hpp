//
// Created by kisly on 05.09.2025.
//

#ifndef VK_RENDERPASS_HPP_
#define VK_RENDERPASS_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		struct RenderPassInfo
		{
			class Device* ptrDevice = nullptr;
			struct AttachmentsInfo* ptrColorAttachment = nullptr;
			struct AttachmentsInfo* ptrDepthStencilAttachment = nullptr;
		};

		class RenderPass
		{
		protected:
			friend class FrameBuffer;
			friend class CommandBuffer;
			friend class GraphicsPipeline;

		private:
			VkRenderPass renderPass = nullptr;
			VkDevice* ptrDevice = nullptr;

			explicit RenderPass(const RenderPassInfo& info);

		public:
			static RenderPass create(const RenderPassInfo& info);
			static RenderPass *ptrCreate(const RenderPassInfo& info);

			~RenderPass();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_RENDERPASS_HPP_
