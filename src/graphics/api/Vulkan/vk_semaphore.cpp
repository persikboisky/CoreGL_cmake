//
// Created by kisly on 10.09.2025.
//

#include "vk_semaphore.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
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

		Semaphore Semaphore::create(Device& device)
		{
			return Semaphore(device);
		}

		Semaphore* Semaphore::ptrCreate(Device& device)
		{
			return new Semaphore(device);
		}

		Semaphore::~Semaphore()
		{
			vkDestroySemaphore(*this->ptrDevice, this->semaphore, nullptr);
		}

		VkSemaphore Semaphore::getVkSemaphore()
		{
			return this->semaphore;
		}

		VkSemaphore* Semaphore::getVkPtrSemaphore()
		{
			return &this->semaphore;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

