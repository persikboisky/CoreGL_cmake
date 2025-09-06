//
// Created by kisly on 05.09.2025.
//

#ifndef VK_PIPELINE_HPP_
#define VK_PIPELINE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct pipelineInfo
		{

		};

		class Pipeline
		{
		 private:
			VkPipeline pipeline;
		};

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PIPELINE_HPP_
