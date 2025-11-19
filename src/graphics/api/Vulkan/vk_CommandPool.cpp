//
// Created by kisly on 06.09.2025.
//

#include "vk_CommandPool.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		CommandPool::CommandPool(const CommandPoolInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			VkCommandPoolCreateInfo commandPoolCreateInfo = {};
			commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			commandPoolCreateInfo.pNext = nullptr;
			commandPoolCreateInfo.flags = (!info.flagAllowResetBuffer) ?
										  VK_COMMAND_POOL_CREATE_TRANSIENT_BIT :
										  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			commandPoolCreateInfo.queueFamilyIndex = info.queueFamilyIndex;
			VkResult result = vkCreateCommandPool(
					info.ptrDevice->device,
					&commandPoolCreateInfo,
					nullptr,
					&this->commandPool);
			coders::vulkanProcessingError(result);
		}

		CommandPool::~CommandPool()
		{
			vkDestroyCommandPool(*this->ptrDevice, this->commandPool, nullptr);
		}

		CommandPool CommandPool::create(const CommandPoolInfo& info)
		{
			return CommandPool(info);
		}

		CommandPool* CommandPool::ptrCreate(const CommandPoolInfo& info)
		{
			return new CommandPool(info);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
