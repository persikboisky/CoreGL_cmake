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
		struct pipelineInfo
		{
			class Device* device = nullptr;
			class ShaderModule* shaderModule = nullptr;
			class RenderPass* renderPass = nullptr;

			const size2i sizeViewport = {600, 600};
			const pos2i posViewport = {0, 0};

			const float maxDepth = 1.0f;
			const float minDepth = 0.0;
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
		};

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PIPELINE_HPP_
