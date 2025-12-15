//
// Created by kisly on 22.11.2025.
//

#ifndef VK_BUFFER_HPP
#define VK_BUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../types/apiTypes.hpp"
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		enum class TYPE_USAGE_BUFFER : int
		{
			VERTEX,
			INDEX,
			UNIFORM,
			STORAGE,
			TRANSFER_SRC,
			TRANSFER_DST,
			INDIRECT,
			VERTEX_TRANSFER_DST,
			INDEX_TRANSFER_DST
		};

		struct BufferCreateInfo
		{
			class Device* ptrDevice = nullptr;

			TYPE_MEMORY typeMemory = TYPE_MEMORY::HOST;
			TYPE_USAGE_BUFFER typeBuffer = TYPE_USAGE_BUFFER::VERTEX;
			bool exclusiveMode = true;

			uint64_t size = 0;
			void* data = nullptr;
		};

		class Buffer
		{
		protected:
			friend class VertexBuffer;
			friend class CommandBuffer;
			friend class DescriptorSet;

		private:
			VkDevice* ptrDevice = nullptr;
			VkBuffer buffer = nullptr;
			VkDeviceMemory memory = nullptr;
			uint64_t size = 0;

			Buffer(const BufferCreateInfo& info);

		public:
			static Buffer create(const BufferCreateInfo& info);
			static Buffer *ptrCreate(const BufferCreateInfo& info);

			~Buffer();

			void copy(void* data, uint64_t size);

			uint64_t getSzie() const;
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_BUFFER_HPP
