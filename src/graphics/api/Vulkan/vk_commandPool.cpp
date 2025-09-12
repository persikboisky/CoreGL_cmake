//
// Created by kisly on 12.09.2025.
//

#include "vk_commandPool.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		CommandPool::CommandPool(struct Device& device) : ptrDevice(device.getPtrDevice())
		{
			VkCommandPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.queueFamilyIndex = device.getGraphicsQueueFamilyIndex();
			poolInfo.pNext = nullptr;
			poolInfo.flags = 0;

			VkResult result = vkCreateCommandPool(
				device.getDevice(),
				&poolInfo,
				nullptr,
				&this->commandPool);
			coders::vulkanProcessingError(result);
		}

		CommandPool::~CommandPool()
		{
			vkDestroyCommandPool(*this->ptrDevice, this->commandPool, nullptr);
		}

		CommandPool CommandPool::create(Device& device)
		{
			return CommandPool(device);
		}

		CommandPool* CommandPool::ptrCreate(Device& device)
		{
			return new CommandPool(device);
		}

		VkCommandPool CommandPool::getVkCommandPool()
		{
			return this->commandPool;
		}

		VkCommandPool* CommandPool::getVkPtrCommandPool()
		{
			return &this->commandPool;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

