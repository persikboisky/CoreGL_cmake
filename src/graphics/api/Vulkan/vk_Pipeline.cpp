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
#include "../../../util/Coders.hpp"
#include "vk_Descriptor.hpp"
#include "vk_Device.hpp"
#include "vk_RenderPass.hpp"
#include "vk_ShaderStage.hpp"
#include <bits/ios_base.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		PipelineLayout::PipelineLayout(const PipelineLayoutInfo& info) : ptrDevice(&info.ptrDevice->device)
		{
			uint32_t index = 0;
			auto pushConstantRanges = new VkPushConstantRange[info.vecPushConstantInfos.size()];
			for (const auto &pushConstInfo : info.vecPushConstantInfos)
			{
				pushConstantRanges[index].size = pushConstInfo.size;
				pushConstantRanges[index].offset = pushConstInfo.offset;
				pushConstantRanges[index].stageFlags = ShaderModule::convertStage(pushConstInfo.shaderStages);
				index++;
			}

			auto setLayouts = new VkDescriptorSetLayout[info.vecPtrDescriptorSetsLayouts.size()];
			for (index = 0; index < info.vecPtrDescriptorSetsLayouts.size(); index++)
			{
				setLayouts[index] = info.vecPtrDescriptorSetsLayouts[index]->layout;
			}

			VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
			pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutCreateInfo.pNext = nullptr;
			pipelineLayoutCreateInfo.pSetLayouts = setLayouts;
			pipelineLayoutCreateInfo.setLayoutCount = static_cast<uint32_t>(info.vecPtrDescriptorSetsLayouts.size());
			pipelineLayoutCreateInfo.pPushConstantRanges = pushConstantRanges;
			pipelineLayoutCreateInfo.pushConstantRangeCount = static_cast<uint32_t>(info.vecPushConstantInfos.size());
			VkResult result = vkCreatePipelineLayout(
					info.ptrDevice->device,
					&pipelineLayoutCreateInfo,
					nullptr,
					&this->layout);
			Coders::vulkanProcessingError(result);

			delete[] pushConstantRanges;
			delete[] setLayouts;
		}

		PipelineLayout::~PipelineLayout()
		{
			vkDestroyPipelineLayout(*this->ptrDevice, this->layout, nullptr);
		}

		PipelineLayout PipelineLayout::create(const PipelineLayoutInfo& info)
		{
			return PipelineLayout(info);
		}

		PipelineLayout* PipelineLayout::ptrCreate(const PipelineLayoutInfo& info)
		{
			return new PipelineLayout(info);
		}

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

			VkVertexInputBindingDescription* ptrBindingDescription = nullptr;
			VkVertexInputAttributeDescription* ptrAttributeDescription = nullptr;
			VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
			vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertexInputInfo.vertexBindingDescriptionCount = 0;
			vertexInputInfo.pVertexBindingDescriptions = nullptr;
			vertexInputInfo.vertexAttributeDescriptionCount = 0;
			vertexInputInfo.pVertexAttributeDescriptions = nullptr;
			if (info.ptrPipelineVertexInputInfo != nullptr)
			{
				ptrBindingDescription = new VkVertexInputBindingDescription[info.ptrPipelineVertexInputInfo->vecVertexBindingDescriptions.size()];
				ptrAttributeDescription = new VkVertexInputAttributeDescription[info.ptrPipelineVertexInputInfo->vecVertexAttributeDescriptions.size()];

				for (uint32_t index = 0; index < info.ptrPipelineVertexInputInfo->vecVertexBindingDescriptions.size(); index++)
				{
					ptrBindingDescription[index].binding = info.ptrPipelineVertexInputInfo->vecVertexBindingDescriptions[index].binding;
					ptrBindingDescription[index].stride = info.ptrPipelineVertexInputInfo->vecVertexBindingDescriptions[index].sizeVertex;
					ptrBindingDescription[index].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
				}

				for (uint32_t index = 0; index < info.ptrPipelineVertexInputInfo->vecVertexAttributeDescriptions.size(); index++)
				{
					ptrAttributeDescription[index].location = info.ptrPipelineVertexInputInfo->vecVertexAttributeDescriptions[index].location;
					ptrAttributeDescription[index].binding = info.ptrPipelineVertexInputInfo->vecVertexAttributeDescriptions[index].binding;
					ptrAttributeDescription[index].offset = info.ptrPipelineVertexInputInfo->vecVertexAttributeDescriptions[index].offset;
					ptrAttributeDescription[index].format = convertFormat(
							info.ptrPipelineVertexInputInfo->vecVertexAttributeDescriptions[index].format);
				}

				vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				vertexInputInfo.vertexBindingDescriptionCount = info.ptrPipelineVertexInputInfo->vecVertexBindingDescriptions.size();
				vertexInputInfo.pVertexBindingDescriptions = ptrBindingDescription;
				vertexInputInfo.vertexAttributeDescriptionCount = info.ptrPipelineVertexInputInfo->vecVertexAttributeDescriptions.size();
				vertexInputInfo.pVertexAttributeDescriptions = ptrAttributeDescription;
			}

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
			rasterizer.polygonMode = (info.polygonMode == POLYGON_MODE::FILL) ?
					VK_POLYGON_MODE_FILL : (info.polygonMode == POLYGON_MODE::LINE) ?
					VK_POLYGON_MODE_LINE : VK_POLYGON_MODE_POINT;

			rasterizer.cullMode = info.cullFace == CULL_MODE::NONE ?
					VK_CULL_MODE_NONE : info.cullFace == CULL_MODE::BACK ?
					VK_CULL_MODE_BACK_BIT : info.cullFace == CULL_MODE::FRONT ?
					VK_CULL_MODE_FRONT_BIT : VK_CULL_MODE_FRONT_AND_BACK;

			rasterizer.frontFace = info.frontFace == FRONT_FACE::COUNTER_CLOCKWISE ?
					VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE;
			rasterizer.depthBiasEnable = VK_FALSE;
			rasterizer.lineWidth = 1.0f;

			VkPipelineMultisampleStateCreateInfo multisampling = {};
			multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampling.sampleShadingEnable = VK_FALSE;
			multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

			VkPipelineDepthStencilStateCreateInfo depthStencil = {};
			depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			depthStencil.depthTestEnable = info.flagDepthTest ? VK_TRUE : VK_FALSE;
			depthStencil.depthWriteEnable = info.flagDepthTest ? VK_TRUE : VK_FALSE;
			depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
			depthStencil.depthBoundsTestEnable = VK_FALSE;
			depthStencil.stencilTestEnable = VK_FALSE;

			auto ptrDynamicStates = new VkDynamicState[info.dynamicState.size()];
			for (size_t index = 0; index < info.dynamicState.size(); index++)
			{
				ptrDynamicStates[index] = info.dynamicState[index] == DYNAMIC_STATE::CULL_MODE ?
					VK_DYNAMIC_STATE_CULL_MODE : info.dynamicState[index] == DYNAMIC_STATE::SCISSOR ?
					VK_DYNAMIC_STATE_SCISSOR : VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY;
			}

			VkPipelineDynamicStateCreateInfo dynamicState = {};
			dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicState.dynamicStateCount = static_cast<uint32_t>(info.dynamicState.size());
			dynamicState.pDynamicStates = ptrDynamicStates;

			VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
			pipelineCreateInfo.pNext = VK_NULL_HANDLE;
			pipelineCreateInfo.flags = 0;
			pipelineCreateInfo.renderPass = info.ptrRenderPass->renderPass;
			pipelineCreateInfo.subpass = 0;
			pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
			pipelineCreateInfo.basePipelineIndex = -1;
			pipelineCreateInfo.layout = info.ptrPipelineLayout->layout;
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

			VkResult result = vkCreateGraphicsPipelines(
					info.ptrDevice->device,
					VK_NULL_HANDLE,
					1,
					&pipelineCreateInfo,
					VK_NULL_HANDLE,
					&this->pipeline);
			Coders::vulkanProcessingError(result);

			delete[] ptrDynamicStates;
			delete[] ptrBindingDescription;
			delete[] ptrAttributeDescription;
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
			vkDestroyPipeline(*this->ptrDevice, this->pipeline, nullptr);
		}

        ComputePipeline::ComputePipeline(const ComputePipelineCreateInfo &info) : ptrDevice(&info.ptrDevice->device)
        {
            VkComputePipelineCreateInfo createInfo = {};
		    createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		    createInfo.basePipelineHandle = VK_NULL_HANDLE;
		    createInfo.basePipelineIndex = -1;
		    createInfo.flags = 0;
		    createInfo.pNext = nullptr;
		    createInfo.stage = info.ptrShaderModule->stage;
		    createInfo.layout = info.ptrPipelineLayout->layout;

		    const VkResult result = vkCreateComputePipelines(
		        info.ptrDevice->device,
		        VK_NULL_HANDLE,
		        1,
		        &createInfo,
		        VK_NULL_HANDLE,
		        &this->pipeline);
		    Coders::vulkanProcessingError(result);
        }

        ComputePipeline::~ComputePipeline()
        {
		    vkDestroyPipeline(*this->ptrDevice, this->pipeline, nullptr);
        }

        ComputePipeline ComputePipeline::create(const ComputePipelineCreateInfo &info)
        {
		    return ComputePipeline(info);
        }

        ComputePipeline *ComputePipeline::ptrCreate(const ComputePipelineCreateInfo &info)
        {
		    return new ComputePipeline(info);
        }

	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
