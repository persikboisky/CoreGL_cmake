//
// Created by kisly on 21.11.2025.
//

#ifndef RENDER_VK_ELEMENTBUFFER_HPP
#define RENDER_VK_ELEMENTBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct ElementBufferInfo
		{
			class Device* ptrDevice = nullptr;
			uint64_t size = 0;
			void* data = nullptr;
		};

		class ElementBuffer
		{
		protected:
			friend class CommandBuffer;

		private:
			VkDevice *ptrDevice = nullptr;
			VkBuffer buffer = nullptr;
			VkDeviceMemory memory = nullptr;

			ElementBuffer(const ElementBufferInfo& info);

		public:
			~ElementBuffer();

			static ElementBuffer create(const ElementBufferInfo& info);
			static ElementBuffer *ptrCreate(const ElementBufferInfo& info);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //RENDER_VK_ELEMENTBUFFER_HPP
