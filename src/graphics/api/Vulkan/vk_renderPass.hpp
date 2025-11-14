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
			std::vector<struct AttachmentsInfo*> ptrArrayAttachmentsInfo = {};
		};

		class RenderPass
		{
		private:
			VkRenderPass renderPass = nullptr;
			VkDevice* ptrDevice = nullptr;

			RenderPass(const RenderPassInfo& info);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_RENDERPASS_HPP_
