//
// Created by kisly on 09.09.2025.
//

#ifndef VK_SEMAPHORE_HPP
#define VK_SEMAPHORE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core::vulkan
{
	class Semaphore
	{
	protected:
		friend class Queue;
		friend class SwapChain;

	private:
		VkSemaphore semaphore = {};
		VkDevice* ptrDevice = nullptr;

		Semaphore(class Device& device);

	public:
		~Semaphore();

		static Semaphore create(class Device& device);
		static Semaphore *ptrCreate(class Device& device);
	};
}// core::vulkan

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //RENDER_VK_SEMAPHORE_HPP
