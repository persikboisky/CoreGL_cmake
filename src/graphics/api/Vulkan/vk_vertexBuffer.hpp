//
// Created by kisly on 14.09.2025.
//

#ifndef VK_VERTEXBUFFER_HPP
#define VK_VERTEXBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		enum FORMAT_VARIABLE : int;

		struct VertexBufferInfo
		{
			class Device* ptrDevice = nullptr;
			float* arrayVertices = nullptr;
			uint64_t lengthArray = 0;
			uint32_t binding = 0;
			uint32_t countElementForVertex = 0;
		};

		class VertexBuffer
		{
		private:
			VkBuffer buffer;
			VkDeviceMemory bufferMemory;
			VkDevice* ptrDevice = nullptr;

			uint64_t sizeOfBytes = 0;
			uint32_t binding = 0;
			uint8_t nByteToOneElement = 0;

			VkVertexInputBindingDescription bindingDescription = {};
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {};

			VertexBuffer(VertexBufferInfo& info);

		public:
			static VertexBuffer create(VertexBufferInfo& info);
			static VertexBuffer* ptrCreate(VertexBufferInfo& info);

			~VertexBuffer();

			uint64_t getSizeOfBytes() const;

			void addAttribute(uint32_t location, const FORMAT_VARIABLE& format, uint32_t offset);

			VkVertexInputBindingDescription getVkVertexInputBindingDescription();
			std::vector<VkVertexInputAttributeDescription> getVkVertexInputAttributeDescriptions();

			VkBuffer getVkBuffer();
			VkBuffer *getPtrVkBuffer();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_VERTEXBUFFER_HPP
