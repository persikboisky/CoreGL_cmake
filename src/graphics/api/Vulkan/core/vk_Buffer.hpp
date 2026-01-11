//
// Created by kisly on 22.11.2025.
//

#ifndef VK_BUFFER_HPP
#define VK_BUFFER_HPP

#include "../../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../../types/apiTypes.hpp"
#include <vector>
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
		    VERTEX_TRANSFER_SRC,
			INDEX_TRANSFER_DST,
		    INDEX_TRANSFER_SRC
		};

		struct BufferCreateInfo
		{
			class Device* ptrDevice = nullptr;

			TYPE_MEMORY typeMemory = TYPE_MEMORY::HOST;
			TYPE_USAGE_BUFFER typeBuffer = TYPE_USAGE_BUFFER::VERTEX;

		    /// @brief предназначена ли цепочка показа для одной очереди(использование для одной очереди более производительное)
		    bool exclusiveMode = true;

		    /// @brief список индексов семейств(нужно если выключен exclusiveMode)
		    std::vector<uint32_t> queueFamilyIndices = {};

			uint64_t size = 0;
			void* data = nullptr;
		};

		class Buffer
		{
		protected:
			friend class vk_VertexBuffer;
			friend class CommandBuffer;
			friend class DescriptorSet;

		private:
			VkDevice* ptrDevice = nullptr;
			VkBuffer buffer = nullptr;
			VkDeviceMemory memory = nullptr;
			uint64_t size = 0;

			explicit Buffer(const BufferCreateInfo& info);

		public:
			static Buffer create(const BufferCreateInfo& info);
			static Buffer *ptrCreate(const BufferCreateInfo& info);

			~Buffer();

			void copy(const void * data, uint64_t size, uint64_t offset = 0) const;

			uint64_t getSize() const;
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_BUFFER_HPP
