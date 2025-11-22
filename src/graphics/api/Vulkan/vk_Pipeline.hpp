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
			class PipelineLayout* ptrPipelineLayout = nullptr;
			struct PipelineVertexInputInfo* ptrPipelineVertexInputInfo = nullptr;

			std::vector<class ShaderModule*> ptrShaderModules = {};

			Rect2D scissor = {};
			Viewport viewport = {};

			vulkan::PRIMITIVE primitive = PRIMITIVE::TRIANGLE_LIST;
			POLYGON_MODE polygonMode = POLYGON_FILL;
			TYPE_CULL_FACE cullFace = CULL_NONE;
			FRONT_FACE frontFace = FRONT_FACE_COUNTER_CLOCKWISE;

			bool flagDepthTest = false;
		};

		struct PipelinePushConstantInfo
		{
			uint32_t offset = 0;
			uint32_t size = 0;
			vulkan::SHADER_STAGES shaderStages = VERTEX_STAGE;
		};

		struct PipelineLayoutInfo
		{
			class Device* ptrDevice = nullptr;
			std::vector<PipelinePushConstantInfo> vecPushConstantInfos = {};
		};

		struct PipelineVertexAttributeDescription
		{
			uint32_t binding = 0;
			uint32_t offset = 0;
			uint32_t location = 0;
			vulkan::FORMAT_VARIABLE format = FLOAT;
		};

		struct PipelineVertexBindingDescriptions
		{
			uint32_t binding = 0;
			uint32_t sizeVertex = 0;
		};

		struct PipelineVertexInputInfo
		{
			std::vector<PipelineVertexAttributeDescription> vecVertexAttributeDescriptions = {};
			std::vector<PipelineVertexBindingDescriptions> vecVertexBindingDescriptions = {};
		};

		class PipelineLayout
		{
		protected:
			friend class GraphicsPipeline;
			friend class CommandBuffer;

		private:
			VkPipelineLayout layout = {};
			VkDevice* ptrDevice = nullptr;

			PipelineLayout(const PipelineLayoutInfo& info);

		public:
			~PipelineLayout();

			static PipelineLayout create(const PipelineLayoutInfo& info);
			static PipelineLayout *ptrCreate(const PipelineLayoutInfo& info);
		};

		class GraphicsPipeline
		{
		protected:
			friend class CommandBuffer;

		private:
			VkDevice* ptrDevice = nullptr;
			VkPipeline pipeline = {};

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
