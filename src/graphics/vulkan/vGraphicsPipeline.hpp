//
// Created by kisly on 21.08.2025.
//

#ifndef VGRAPHICSPIPELINE_HPP
#define VGRAPHICSPIPELINE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../util/types.hpp"
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace core::vulkan
{
    struct apiContainer;
    struct piplineContainer;

    struct shaderInfo
    {
        TYPE_SHADER type;
        const char* path = nullptr;
        const char* name = "main";
    };

    struct graphicsPipelineInfo {
        shaderInfo* VertexShaderInfo = nullptr;
        shaderInfo* GeometryShaderInfo = nullptr;
        shaderInfo* FragmentShaderInfo = nullptr;
    };

    struct graphicsPipeline
    {
    private:
        static inline std::vector<char> readFile(const std::string& filename);
        static inline VkShaderModule createShaderModule(const std::vector<char>& code, const apiContainer& cnt);

    public:
        static void create(const graphicsPipelineInfo& info, piplineContainer* pCnt, const apiContainer* cnt);
        static void destroy(piplineContainer* pCnt, const apiContainer* cnt);
    };
} // core::vulkan

#include "vGraphicsPipeline.inl"

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VGRAPHICSPIPELINE_HPP
