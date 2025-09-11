//
// Created by kisly on 10.09.2025.
//

#ifndef VK_SEMAPHORE_HPP_
#define VK_SEMAPHORE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		class Semaphore
		{
		 private:
			VkSemaphore semaphore;
			VkDevice* ptrDevice = nullptr;

			explicit Semaphore(class Device& device);

		 public:
			static Semaphore create(class Device& device);
			static Semaphore *ptrCreate(class Device& device);

			~Semaphore();

			VkSemaphore getVkSemaphore();
			VkSemaphore *getVkPtrSemaphore();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SEMAPHORE_HPP_
