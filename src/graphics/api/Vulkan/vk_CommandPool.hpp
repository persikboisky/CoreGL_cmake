//
// Created by kisly on 06.09.2025.
//

#ifndef VK_COMMANDPOOL_HPP
#define VK_COMMANDPOOL_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct CommandPoolInfo
		{
			class Device* ptrDevice = nullptr;
			uint32_t queueFamilyIndex = 0;
			bool flagAllowResetBuffer = false;
		};

		class CommandPool
		{
		protected:
			friend class CommandBuffer;

		private:
			VkDevice* ptrDevice = nullptr;
			VkCommandPool commandPool = {};

			CommandPool(const CommandPoolInfo& info);

		public:
			~CommandPool();

			static CommandPool create(const CommandPoolInfo& info);
			static CommandPool *ptrCreate(const CommandPoolInfo& info);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //RENDER_VK_COMMANDPOOL_HPP
