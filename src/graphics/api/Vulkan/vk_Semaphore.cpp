//
// Created by kisly on 09.09.2025.
//

#include "vk_Semaphore.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Device.hpp"
#include "../../../util/coders.hpp"

namespace core::vulkan
{
	Semaphore::Semaphore(Device& device) : ptrDevice(&device.device)
	{
		VkSemaphoreCreateInfo semaphoreCreateInfo = {};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreCreateInfo.pNext = nullptr;
		semaphoreCreateInfo.flags = 0;

			VkResult result = vkCreateSemaphore(
					device.device,
					&semaphoreCreateInfo,
					nullptr,
					&this->semaphore);
			coders::vulkanProcessingError(result);
	}

	Semaphore::~Semaphore()
	{
		vkDestroySemaphore(*this->ptrDevice, this->semaphore, nullptr);
	}

	Semaphore Semaphore::create(Device& device)
	{
		return Semaphore(device);
	}

	Semaphore *Semaphore::ptrCreate(Device& device)
	{
		return new Semaphore(device);
	}
} // vulkan::corre

#endif //defined(CORE_INCLUDE_VULKAN)

