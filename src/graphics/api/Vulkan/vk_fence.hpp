//
// Created by kisly on 06.10.2025.
//

#ifndef VK_FENCE_HPP
#define VK_FENCE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct WaitForFencesInfo
		{
			class Device* ptrDevice = nullptr;
			class Fence** ptrFences = nullptr;
			uint32_t countFences = 0;
			bool waitAllFences = true;
		};

		class Fence
		{
		protected:
			friend class SwapChain;
			friend class Queue;

		private:
			VkFence fence = {};
			VkDevice* ptrDevice = nullptr;

			explicit Fence(class Device& device);

		public:
			static Fence create(class Device& device);
			static Fence* ptrCreate(class Device& device);

			~Fence();

			static void wait(WaitForFencesInfo& info);
			void wait();
			void resetFence();
		};
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif //VK_FENCE_HPP
