#include "vGraphicsPipeline.hpp"
#include "../../util/coders.hpp"
#include "vResource.hpp"
#include "../../config.hpp"
#include "../../util/console.hpp"
#include <fstream>
#include <iostream>

inline std::vector<char> core::vulkan::graphicsPipeline::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw coders(6, filename);
    }

    const size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    if (CORE_INFO)
    {
        console::printTime();
        std::cout << "Ok: read file: " << filename << std::endl;
    }

    return buffer;
}

inline VkShaderModule core::vulkan::graphicsPipeline::createShaderModule(
        const std::vector<char> &code,
        const apiContainer& cnt)
{
    VkShaderModuleCreateInfo shader_module_create_info{};
    shader_module_create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shader_module_create_info.pNext = nullptr;
    shader_module_create_info.codeSize = code.size();
    shader_module_create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    VkResult result = vkCreateShaderModule(
            cnt.logicalDevice,
            &shader_module_create_info,
            nullptr,
            &shaderModule);
    coders::vulkanProcessingError(result);

    return shaderModule;
}
