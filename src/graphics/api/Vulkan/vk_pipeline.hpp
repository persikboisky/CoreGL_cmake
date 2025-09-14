//
// Created by kisly on 05.09.2025.
//

#ifndef VK_PIPELINE_HPP_
#define VK_PIPELINE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/types.hpp"
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct pushConstantInfo
		{
			SHADER_STAGES shaderStages = VERTEX_FRAGMENT_STAGES;
			uint32_t sizeOfBytes = 0;
			uint32_t offset = 0;
		};

		struct pipelineInfo
		{
			class Device* device = nullptr;
			class ShaderModule* shaderModule = nullptr;
			class RenderPass* renderPass = nullptr;

			size2i sizeViewport = {600, 600};
			pos2i posViewport = {0, 0};

			float maxDepth = 1.0f;
			float minDepth = 0.0;

			vulkan::PRIMITIVE primirive = vulkan::TRIANGLE_STRIP;

			uint32_t pushConstantCount = 0;
			pushConstantInfo *pushConstants = nullptr;
		};

		class Pipeline
		{
		 private:
			VkPipeline pipeline;
			VkPipelineLayout pipelineLayout;

			VkDevice *ptrDevice = nullptr;

			explicit Pipeline(const pipelineInfo& info);

		 public:
			static Pipeline create(const pipelineInfo& info);
			static Pipeline *ptrCreate(const pipelineInfo& info);

			~Pipeline();

			VkPipeline getVkPipeline();
			VkPipeline *getVkPtrPipeline();

			VkPipelineLayout getVkPipelineLayout();
			VkPipelineLayout *getVkPtrPipelineLayout();
		};

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PIPELINE_HPP_
