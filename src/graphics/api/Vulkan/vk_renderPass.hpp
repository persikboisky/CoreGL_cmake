//
// Created by kisly on 05.09.2025.
//

#ifndef VK_RENDERPASS_HPP_
#define VK_RENDERPASS_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct RenderPassInfo
		{
			class Device* ptrDevice = nullptr;
			bool depthTest = false;
			bool clearBuffers = true;
		};

		class RenderPass
		{
		 private:
			VkRenderPass renderPass;
			VkDevice* device = nullptr;
			bool depthAttachment = false;
			bool clearBuffers = true;

			RenderPass(const RenderPassInfo& info);

		 public:
			~RenderPass();

			static RenderPass create(const RenderPassInfo& info);
			static RenderPass *ptrCreate(const RenderPassInfo& info);

			VkRenderPass getVkRenderPass();
			VkRenderPass *getVkPtrRenderPass();

			bool getStateDepth() const;
			bool getStateClear() const;
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_RENDERPASS_HPP_
