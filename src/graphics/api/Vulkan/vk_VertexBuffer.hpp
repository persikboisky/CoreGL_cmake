//
// Created by kisly on 11.09.2025.
//

#ifndef RENDER_VK_VERTEXBUFFER_HPP
#define RENDER_VK_VERTEXBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct VertexBufferInfo
		{
			class Device* ptrDevice = nullptr;
			void* data = nullptr;
			uint64_t size = 0;
		};

		class VertexBuffer
		{
		protected:
			friend class CommandBuffer;

		private:
			class Buffer* buffer = nullptr;

			VertexBuffer(const VertexBufferInfo& info);

		public:
			~VertexBuffer();

			static VertexBuffer create(const VertexBufferInfo& info);
			static VertexBuffer *ptrCreate(const VertexBufferInfo& info);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //RENDER_VK_VERTEXBUFFER_HPP
