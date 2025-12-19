//
// Created by kisly on 09.09.2025.
//

#ifndef VK_SYNC_HPP
#define VK_SYNC_HPP

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
		VkDevice device = nullptr;

		Semaphore(const class Device& device);

	public:
		~Semaphore();

		static Semaphore create(const class Device& device);
		static Semaphore *ptrCreate(const class Device& device);
	};

    class Fence
    {
    protected:
        friend class SwapChain;
        friend class Queue;

    private:
        VkFence fence = nullptr;
        VkDevice device = nullptr;

        Fence(const class Device& device, bool signaled);

    public:
        ~Fence();

        static Fence create(const class Device& device, bool signaled = false);
        static Fence* ptrCreate(const class Device& device, bool signaled = false);

        void reset() const;
        void wait(bool flagWait = true, uint64_t timeout = UINT64_MAX) const;
    };
}// core::vulkan

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_SYNC_HPP
