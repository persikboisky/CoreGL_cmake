//
// Created by kisly on 07.09.2025.
//

#ifndef VK_PIPELINE_HPP
#define VK_PIPELINE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>
#include "../../../util/types.hpp"

namespace core
{
	namespace vulkan
	{
		struct GraphicsPipelineInfo
		{
			class Device* ptrDevice = nullptr;
			class RenderPass* ptrRenderPass = nullptr;
			std::vector<class ShaderModule*> ptrShaderModules = {};
			vulkan::PRIMITIVE primitive = PRIMITIVE::TRIANGLE_LIST;
			Rect2D scissor = {};
			Viewport viewport = {};
			POLYGON_MODE polygonMode = POLYGON_FILL;
			TYPE_CULL_FACE cullFace = CULL_NONE;
			FRONT_FACE frontFace = FRONT_FACE_COUNTER_CLOCKWISE;
		};

		class GraphicsPipeline
		{
		protected:
			friend class CommandBuffer;

		private:
			VkDevice* ptrDevice = nullptr;
			VkPipeline pipeline = {};
			VkPipelineLayout layout = {};

			GraphicsPipeline(const GraphicsPipelineInfo& info);

		public:
			static GraphicsPipeline create(const GraphicsPipelineInfo& info);
			static GraphicsPipeline *ptrCreate(const GraphicsPipelineInfo& info);

			~GraphicsPipeline();
		};

//		class ComputerPipeline
//		{
//
//		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_PIPELINE_HPP
