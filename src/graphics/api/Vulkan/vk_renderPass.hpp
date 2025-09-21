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
		struct renderPassInfo
		{
			class Device* device = nullptr;
			bool depthTest = false;
		};

		class RenderPass
		{
		 private:
			VkRenderPass renderPass;
			VkDevice* device = nullptr;
			bool depthAttachment = false;

			RenderPass(const renderPassInfo& info);

		 public:
			~RenderPass();

			static RenderPass create(const renderPassInfo& info);
			static RenderPass *ptrCreate(const renderPassInfo& info);

			VkRenderPass getVkRenderPass();
			VkRenderPass *getVkPtrRenderPass();

			bool getStateDepth() const;
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_RENDERPASS_HPP_
