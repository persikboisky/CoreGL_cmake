//
// Created by kisly on 12.09.2025.
//

#ifndef VK_COMMANDPOOL_HPP_
#define VK_COMMANDPOOL_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		class CommandPool
		{
		 private:
			VkCommandPool commandPool;
			VkDevice* ptrDevice = nullptr;

			explicit CommandPool(class Device& device, bool flagMayReset);

		 public:
			~CommandPool();

			static CommandPool create(class Device& device, bool flagMayReset = false);
			static CommandPool *ptrCreate(class Device& device, bool flagMayReset = false);

			VkCommandPool getVkCommandPool();
			VkCommandPool *getVkPtrCommandPool();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_COMMANDPOOL_HPP_
