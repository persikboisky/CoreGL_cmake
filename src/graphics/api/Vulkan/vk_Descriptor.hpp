//
// Created by kisly on 23.11.2025.
//

#ifndef VK_DESCRIPTORPOOL_HPP
#define VK_DESCRIPTORPOOL_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../types/apiTypes.hpp"
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		enum class DESCRIPTOR_TYPE : int
		{
			UNIFORM_BUFFER,
			SAMPLER
		};

		struct DescriptorPoolSize
		{
			DESCRIPTOR_TYPE type = DESCRIPTOR_TYPE::UNIFORM_BUFFER;
			uint32_t count = 0;
		};

		struct DescriptorPoolCreateInfo
		{
			class Device* ptrDevice = nullptr;
			std::vector<DescriptorPoolSize*> vecPtrDescriptorPoolSize = {};
			uint32_t maxSets = 0;
		};

		struct DescriptorSetLayoutBinding
		{
			uint32_t binding = 0;

			/// для передачи массивов указывается значение больше 1
			uint32_t count = 0;
			DESCRIPTOR_TYPE type = DESCRIPTOR_TYPE::UNIFORM_BUFFER;
			SHADER_STAGES shaderStages = VERTEX_STAGE;
		};

		struct DescriptorSetLayoutCreateInfo
		{
			class Device* ptrDevice = nullptr;
			std::vector<DescriptorSetLayoutBinding> layoutBinding = {};
		};

		class DescriptorPool
		{
		protected:
			friend class DescriptorSet;

		private:
			VkDevice *prtDevice = nullptr;
			VkDescriptorPool descriptorPool = nullptr;

			DescriptorPool(const DescriptorPoolCreateInfo& info);

		public:
			static DescriptorPool create(const DescriptorPoolCreateInfo& info);
			static DescriptorPool *ptrCreate(const DescriptorPoolCreateInfo& info);

			~DescriptorPool();
		};

		class DescriptorSetLayout
		{
		protected:
			friend class DescriptorSet;
			friend class PipelineLayout;

		private:
			VkDevice *prtDevice = nullptr;
			VkDescriptorSetLayout layout = nullptr;

			DescriptorSetLayout(const DescriptorSetLayoutCreateInfo& info);

		public:
			~DescriptorSetLayout();

			static DescriptorSetLayout create(const DescriptorSetLayoutCreateInfo& info);
			static DescriptorSetLayout* ptrCreate(const DescriptorSetLayoutCreateInfo& info);
		};

		struct DescriptorSetCreateInfo
		{
			class Device* ptrDevice = nullptr;
			DescriptorPool* ptrDescriptorPool = nullptr;
			std::vector<DescriptorSetLayout*> vecPtrLayouts = {};
		};

		struct DescriptorSetUpdateInfo
		{
			uint32_t binding = 0;
			uint64_t offset = 0;
			class Buffer *ptrBuffer = nullptr;
			class ImageView *ptrImageView = nullptr;
			class Sampler *ptrSampler = nullptr;
		};

		class DescriptorSet
		{
		protected:
			friend class CommandBuffer;

		private:
			VkDevice *ptrDevice = nullptr;
			VkDescriptorPool* ptrDescriptorPool = nullptr;
			VkDescriptorSet descriptorSet = nullptr;

			DescriptorSet(const DescriptorSetCreateInfo& info);

		public:
			~DescriptorSet();

			static DescriptorSet create(const DescriptorSetCreateInfo& info);
			static DescriptorSet* ptrCreate(const DescriptorSetCreateInfo& info);

			void update(const DescriptorSetUpdateInfo& info);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_DESCRIPTORPOOL_HPP
