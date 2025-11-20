//
// Created by kisly on 07.09.2025.
//
//[Входные данные] (вершины, индексы)
//|
//v
//[Input Assembler] - Сборка примитивов (треугольники, линии)
//|
//v
//[Vertex Shader]   - Программируемая стадия (позиция, нормали, UV)
//|
//v
//[Tessellation]    - (Опционально) Разбиение геометрии
//|
//v
//[Geometry Shader] - (Опционально) Создание/удаление примитивов
//|
//v
//[Rasterization]   - Растеризация (преобразование в фрагменты)
//|
//v
//[Fragment Shader] - Программируемая стадия (цвет пикселя)
//|
//v
//[Color Blending]  - Смешивание цвета с содержимым фреймбуфера
//|
//v
//[Фреймбуфер]

#include "vk_Pipeline.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_ShaderStage.hpp"
#include "vk_RenderPass.hpp"
#include "vk_Device.hpp"
#include "../../../util/coders.hpp"

namespace core
{
	namespace vulkan
	{
		GraphicsPipeline::GraphicsPipeline(const GraphicsPipelineInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			std::vector<VkPipelineShaderStageCreateInfo> shaderStages = {};
			shaderStages.resize(info.ptrShaderModules.size());
			for (size_t index = 0; index < info.ptrShaderModules.size(); index++)
				shaderStages[index] = info.ptrShaderModules[index]->stage;

			VkPipelineColorBlendAttachmentState colorBlendAttachment{};
			colorBlendAttachment.colorWriteMask =
					VK_COLOR_COMPONENT_R_BIT |
					VK_COLOR_COMPONENT_G_BIT |
					VK_COLOR_COMPONENT_B_BIT |
					VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

			VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo = {};
			pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			pipelineColorBlendStateCreateInfo.pNext = nullptr;
			pipelineColorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
			pipelineColorBlendStateCreateInfo.attachmentCount = 1;
			pipelineColorBlendStateCreateInfo.pAttachments = &colorBlendAttachment;

			VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
			vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertexInputInfo.vertexBindingDescriptionCount = 0;
			vertexInputInfo.pVertexBindingDescriptions = nullptr;
			vertexInputInfo.vertexAttributeDescriptionCount = 0;
			vertexInputInfo.pVertexAttributeDescriptions = nullptr;

			VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
			inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			inputAssembly.primitiveRestartEnable = VK_FALSE;
			switch (info.primitive)
			{
			case TRIANGLE_STRIP:
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
				break;
			case TRIANGLE_LIST:
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				break;
			case TRIANGLE_FAN:
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
				break;
			case LINE_STRIP:
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
				break;
			case POINT_LIST:
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
				break;
			default:
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
				break;
			}

			VkRect2D scissor = {};
			scissor.offset.x = info.scissor.x;
			scissor.offset.y = info.scissor.y;
			scissor.extent.width = info.scissor.width;
			scissor.extent.height = info.scissor.height;

			VkViewport viewport = {};
			viewport.x = info.viewport.x;
			viewport.y = info.viewport.y;
			viewport.width = info.viewport.width;
			viewport.height = info.viewport.height;
			viewport.minDepth = info.viewport.minDepth;
			viewport.maxDepth = info.viewport.maxDepth;

			VkPipelineViewportStateCreateInfo viewportState = {};
			viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportState.viewportCount = 1;
			viewportState.pViewports = &viewport;
			viewportState.scissorCount = 1;
			viewportState.pScissors = &scissor;

			VkPipelineRasterizationStateCreateInfo rasterizer = {};
			rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			rasterizer.depthClampEnable = VK_FALSE;
			rasterizer.rasterizerDiscardEnable = VK_FALSE;
			rasterizer.polygonMode = (info.polygonMode == POLYGON_FILL) ?
					VK_POLYGON_MODE_FILL : (info.polygonMode == POLYGON_LINE) ?
					VK_POLYGON_MODE_LINE : VK_POLYGON_MODE_POINT;

			rasterizer.cullMode = (info.cullFace == CULL_NONE) ?
					VK_CULL_MODE_NONE : (info.cullFace == CULL_BACK) ?
					VK_CULL_MODE_BACK_BIT : (info.cullFace == CULL_FRONT) ?
					VK_CULL_MODE_FRONT_BIT : VK_CULL_MODE_FRONT_AND_BACK;

			rasterizer.frontFace = (info.frontFace == FRONT_FACE_COUNTER_CLOCKWISE) ?
					VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE;
			rasterizer.depthBiasEnable = VK_FALSE;
			rasterizer.lineWidth = 1.0f;

			VkPipelineMultisampleStateCreateInfo multisampling = {};
			multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampling.sampleShadingEnable = VK_FALSE;
			multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

			VkPipelineDepthStencilStateCreateInfo depthStencil = {};
			depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			depthStencil.depthTestEnable = VK_TRUE;
			depthStencil.depthWriteEnable = VK_TRUE;
			depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
			depthStencil.depthBoundsTestEnable = VK_FALSE;
			depthStencil.stencilTestEnable = VK_FALSE;

			VkPipelineDynamicStateCreateInfo dynamicState = {};
			dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicState.dynamicStateCount = 0;
			dynamicState.pDynamicStates = nullptr;

			VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
			pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutCreateInfo.pNext = nullptr;
			pipelineLayoutCreateInfo.pSetLayouts = nullptr;
			pipelineLayoutCreateInfo.setLayoutCount = 0;
			pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
			pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
			VkResult result = vkCreatePipelineLayout(
					info.ptrDevice->device,
					&pipelineLayoutCreateInfo,
					nullptr,
					&this->layout);
			coders::vulkanProcessingError(result);

			VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
			pipelineCreateInfo.pNext = VK_NULL_HANDLE;
			pipelineCreateInfo.flags = 0;
			pipelineCreateInfo.renderPass = info.ptrRenderPass->renderPass;
			pipelineCreateInfo.subpass = 0;
			pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
			pipelineCreateInfo.basePipelineIndex = -1;
			pipelineCreateInfo.layout = this->layout;
			pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
			pipelineCreateInfo.pStages = shaderStages.data();
			pipelineCreateInfo.pColorBlendState = &pipelineColorBlendStateCreateInfo;
			pipelineCreateInfo.pDepthStencilState = &depthStencil;
			pipelineCreateInfo.pDynamicState = &dynamicState;
			pipelineCreateInfo.pInputAssemblyState = &inputAssembly;
			pipelineCreateInfo.pTessellationState = VK_NULL_HANDLE;
			pipelineCreateInfo.pVertexInputState = &vertexInputInfo;
			pipelineCreateInfo.pMultisampleState = &multisampling;
			pipelineCreateInfo.pRasterizationState = &rasterizer;
			pipelineCreateInfo.pViewportState = &viewportState;

			result = vkCreateGraphicsPipelines(
					info.ptrDevice->device,
					VK_NULL_HANDLE,
					1,
					&pipelineCreateInfo,
					VK_NULL_HANDLE,
					&this->pipeline);
			coders::vulkanProcessingError(result);
		}

		GraphicsPipeline GraphicsPipeline::create(const GraphicsPipelineInfo& info)
		{
			return GraphicsPipeline(info);
		}

		GraphicsPipeline* GraphicsPipeline::ptrCreate(const GraphicsPipelineInfo& info)
		{
			return new GraphicsPipeline(info);
		}

		GraphicsPipeline::~GraphicsPipeline()
		{
			vkDestroyPipelineLayout(*this->ptrDevice, this->layout, nullptr);
			vkDestroyPipeline(*this->ptrDevice, this->pipeline, nullptr);
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
