//
// Created by kisly on 21.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vGraphicsPipeline.hpp"
#include "../../util/coders.hpp"
#include <vulkan/vulkan.h>

namespace core::vulkan
{
    void graphicsPipeline::create(const graphicsPipelineInfo& info, piplineContainer *pCnt, const apiContainer *cnt)
    {
////////////////////////////////////////////////////////////
// создаём шейдеры
////////////////////////////////////////////////////////////
        std::vector<VkPipelineShaderStageCreateInfo> shaderStages = {};
        if (
                info.FragmentShaderInfo->path == nullptr ||
                info.VertexShaderInfo->path == nullptr ||
                info.FragmentShaderInfo->name == nullptr ||
                info.VertexShaderInfo->name == nullptr)
            coders(42);


        const std::vector<char> vertShaderCode = readFile(info.VertexShaderInfo->path);
        const std::vector<char> fragShaderCode = readFile(info.FragmentShaderInfo->path);

        VkShaderModule shaderModuleVert = createShaderModule(vertShaderCode, *cnt);
        VkShaderModule shaderModuleFrag = createShaderModule(fragShaderCode, *cnt);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.pNext = nullptr;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = shaderModuleVert;
        vertShaderStageInfo.pName = info.VertexShaderInfo->name;
        vertShaderStageInfo.pSpecializationInfo = nullptr;
        shaderStages.push_back(vertShaderStageInfo);

        VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.pNext = nullptr;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = shaderModuleFrag;
        fragShaderStageInfo.pName = info.FragmentShaderInfo->name;
        fragShaderStageInfo.pSpecializationInfo = nullptr;
        shaderStages.push_back(fragShaderStageInfo);

        VkShaderModule shaderModuleGeom = nullptr;
        if (info.GeometryShaderInfo != nullptr)
        {
            if (
                    info.GeometryShaderInfo->path != nullptr &&
                    info.GeometryShaderInfo->name != nullptr)
            {
                const std::vector<char> geomShaderCode = readFile(info.GeometryShaderInfo->path);
                shaderModuleGeom = createShaderModule(geomShaderCode, *cnt
                );
                VkPipelineShaderStageCreateInfo geomShaderStageInfo = {};
                geomShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                geomShaderStageInfo.pNext = nullptr;
                geomShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                geomShaderStageInfo.module = shaderModuleGeom;
                geomShaderStageInfo.pName = info.GeometryShaderInfo->name;
                geomShaderStageInfo.pSpecializationInfo = nullptr;
                shaderStages.push_back(geomShaderStageInfo);
            }
        }


////////////////////////////////////////////////////////////
// входные данные в шейдер
////////////////////////////////////////////////////////////
        VkPipelineVertexInputStateCreateInfo vertInputInfo = {};
        vertInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertInputInfo.pNext = nullptr;
        vertInputInfo.vertexBindingDescriptionCount = 0;
        vertInputInfo.pVertexBindingDescriptions = nullptr;
        vertInputInfo.vertexAttributeDescriptionCount = 0;
        vertInputInfo.pVertexAttributeDescriptions = nullptr;

////////////////////////////////////////////////////////////
// устанавливаем вид примитива
////////////////////////////////////////////////////////////
        VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.pNext = nullptr;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

////////////////////////////////////////////////////////////
// настраиваем область рисования
////////////////////////////////////////////////////////////
        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(cnt->swapChainExtent.width);
        viewport.height = static_cast<float>(cnt->swapChainExtent.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor = {};
        scissor.offset = {0, 0};
        scissor.extent = cnt->swapChainExtent;

        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.pNext = nullptr;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

////////////////////////////////////////////////////////////
// растеризация
////////////////////////////////////////////////////////////
        VkPipelineRasterizationStateCreateInfo rasterizer = {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.pNext = nullptr;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

////////////////////////////////////////////////////////////
// мульти сэмплинг
////////////////////////////////////////////////////////////
        VkPipelineMultisampleStateCreateInfo multiSample = {};
        multiSample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multiSample.pNext = nullptr;
        multiSample.sampleShadingEnable = VK_FALSE;
        multiSample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;   // СТЕПЕНЬ ЗГЛАЖИВАНИЯ

        // Stencil/Depth state
        //
        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
                                              VK_COLOR_COMPONENT_G_BIT |
                                              VK_COLOR_COMPONENT_B_BIT |
                                              VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;                // СМЕШИАНИЕ ЦВЕТОВ

        VkPipelineColorBlendStateCreateInfo colorBlendState = {};
        colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlendState.pNext = nullptr;
        colorBlendState.logicOpEnable = VK_FALSE;                   // СМЕШИАНИЕ ЦВЕТОВ
        colorBlendState.attachmentCount = 1;
        colorBlendState.pAttachments = &colorBlendAttachment;

        VkPipelineDepthStencilStateCreateInfo depthState = {};
        depthState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthState.pNext = nullptr;
        depthState.depthTestEnable = VK_TRUE;
        depthState.depthWriteEnable = VK_TRUE;
        depthState.depthCompareOp = VK_COMPARE_OP_LESS;
        depthState.depthBoundsTestEnable = VK_FALSE;
        depthState.minDepthBounds = 0.0f;
        depthState.maxDepthBounds = 1.0f;
        depthState.stencilTestEnable = VK_FALSE;
        depthState.front = {};
        depthState.back = {};

        // Pipeline layout
        VkPipelineLayoutCreateInfo pipeLineLayoutInfo = {};
        pipeLineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeLineLayoutInfo.flags = 0;
        pipeLineLayoutInfo.pNext = nullptr;
        pipeLineLayoutInfo.setLayoutCount = 0;
        pipeLineLayoutInfo.pSetLayouts = nullptr;
        pipeLineLayoutInfo.pushConstantRangeCount = 0;
        pipeLineLayoutInfo.pPushConstantRanges = nullptr;

        VkResult result = vkCreatePipelineLayout(
                cnt->logicalDevice,
                &pipeLineLayoutInfo,
                nullptr,
                &pCnt->pipelineLayout);
        coders::vulkanProcessingError(result);

        // Pipeline
////////////////////////////////////////////////////////////
        VkGraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.pNext = nullptr;
        pipelineInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
        pipelineInfo.pStages = shaderStages.data();
////////////////////////////////////////////////////////////
        pipelineInfo.pVertexInputState = &vertInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multiSample;
        pipelineInfo.pColorBlendState = &colorBlendState;
        pipelineInfo.pDepthStencilState = &depthState;
        pipelineInfo.pDynamicState = nullptr;
////////////////////////////////////////////////////////////
        pipelineInfo.layout = pCnt->pipelineLayout;
        pipelineInfo.renderPass = pCnt->renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;   // наследования графического контейнера
        pipelineInfo.basePipelineIndex = -1;

        result = vkCreateGraphicsPipelines(
                cnt->logicalDevice,
                nullptr,
                1,
                &pipelineInfo,
                nullptr,
                &pCnt->graphicsPipeline);
        coders::vulkanProcessingError(result);

        vkDestroyShaderModule(cnt->logicalDevice, shaderModuleVert, nullptr);
        vkDestroyShaderModule(cnt->logicalDevice, shaderModuleFrag, nullptr);
        if (shaderModuleGeom != nullptr) vkDestroyShaderModule(cnt->logicalDevice, shaderModuleGeom,
                                                               nullptr);
    }

    void graphicsPipeline::destroy(piplineContainer *pCnt, const apiContainer *cnt)
    {
        vkDestroyPipeline(cnt->logicalDevice, pCnt->graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(cnt->logicalDevice, pCnt->pipelineLayout, nullptr);
    }
} // core

#endif //defined(CORE_INCLUDE_VULKAN)