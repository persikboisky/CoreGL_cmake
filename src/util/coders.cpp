//
// Created by kisly on 13.07.2025.
//

#include "coders.hpp"
#include "console.hpp"
#include <string>
#include <iostream>
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#endif //defined(CORE_INCLUDE_VULKAN)

const std::string INFO_CODERS[] = {             
    //          информация                          // код
        "FAILED_INIT_GLFW",                     // 0
        "FAILED_INIT_WINDOW",                   // 1
        "FAILED_INIT_GLEW",                     // 2
        "FAILED_LOAD_IMAGE",                    // 3
        "FAILED_CHECK_KEY",                     // 4
        "FAILED_CREATE_CUSTOM_CURSOR",          // 5
        "FAILED_OPEN_FILE",                     // 6
        "FAILED_CREATE_VERTEX_SHADER",          // 7
        "FAILED_CREATE_FRAGMENT_SHADER",        // 8
        "FAILED_CREATE_SHADER_PROGRAM",         // 9
        "FAILED_CREATE_GEOMETRY_SHADER",        // 10
        "FAILED_LOCATE_UNIFORM_VARIABLE",       // 11
        "FAILED_BIND_VAO",                      // 12
        "FAILED_CREATE_VAO",                    // 13
        "FAILED_CREATE_VBO_FOR_VAO",            // 14
        "FAILED_ADD_ATTRIBUTE_TO_VAO",          // 15
        "FAILED_CREATE_TEXTURE",                // 16
        "FAILED_BIND_TEXTURE",                  // 17
        "FAILED_SET_SAMPLER_TEXTURE_ON_BIND",   // 18
        "FAILED_BIND_EBO",                      // 19
        "FAILED_CREATE_EBO",                    // 20
        "FAILED_BIND_FBO",                      // 21
        "FAILED_CREATE_FBO",                    // 22
        "FAILED_CREATE_TEXTURE_ON_FBO",         // 23
        "FAILED_INIT_AUDIO_DEVICE",             // 24
        "FAILED_CREATE_AUDIO_CONTEXT",          // 25
        "FAILED_SET_AUDIO_CONTEXT",             // 26
        "FAILED_OPEN_FILE",                     // 27
        "FAILED_SEARCH_NAME_CHUNK_TO_RIFF",     // 28
        "THIS_ISN'T_WAVE_FORMAT",               // 29
        "THIS_ISN'T_FMT_CHUNK",                 // 30
        "FAILED_SEARCH_BLOCK_DATA",             // 31
        "FAILED_CREATE_AUDIO_BUFFER",           // 32
        "FAILED_CREATE_SOURCE",                 // 33
        "FAILED_SEARCH_MTL_FILE_NAME_TO_OBJ",   // 34
        "",                                     // 35
        "VK_FAILED_YOUR_GPU_NOT_HOLDS_SURFACE_KHR", // 36
        "VK_FAILED_TO_CREATE_IMAGE_VIEW!",          // 37
        "VK_FAILED_SEARCH_SURFACE_FORMATS",         // 38
        "VK_FAILED_SEARCH_PRESENT_MODE",            // 39
        "VK_FAILED_TO_CREATE_IMAGE_VIEW!",          // 40
        "VK_FAILED_SEARCH_IMAGE_FORMAT",            // 41
        "VK_DIDN'T_SEARCH_FRAG_OR_VERT_SHADER",     // 42
        "FAILED_SEARCH_TAG_HEAD_TO_TTF_FILE",       // 43
        "FAILED_THIS_FILE_DON'T_BE_TO_TTF",         // 44
        "VK_FAILED_YOUR_GPU_DON'T_HOLDING_VULKAN_API",	//45
		"VK_FAILED_SEARCH_DEVICE_TYPE_MEMORY",  // 46
		"VK_FAILED_INIT_GLSLang",				 // 47
		""
};

core::coders::coders(int codeError, std::string addInfo)
{
    this->code = codeError;
    this->info = addInfo;
}

int core::coders::getCode() const
{
    return this->code;
}

std::string core::coders::getInfo()
{
    return {
        INFO_CODERS[this->code] +
        "\n" +
        this->info
    };
}

void core::coders::print()
{
    console::printTime();
    std::cout << "code: " << this->getCode() << std::endl;
    console::printTime();
    std::cout << this->getInfo() << std::endl;
}

#if defined(CORE_INCLUDE_VULKAN)
    void core::coders::vulkanProcessingError(const VkResult& result)
    {
        switch (result)
        {
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                throw core::coders(35, "VK_ERROR_EXTENSION_NOT_PRESENT");
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                throw core::coders(35, "VK_ERROR_INCOMPATIBLE_DRIVER");
            case VK_ERROR_INITIALIZATION_FAILED:
                throw core::coders(35, "VK_ERROR_INITIALIZATION_FAILED");
            case VK_ERROR_LAYER_NOT_PRESENT:
                throw core::coders(35, "VK_ERROR_LAYER_NOT_PRESENT");
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                throw core::coders(35, "VK_ERROR_OUT_OF_DEVICE_MEMORY");
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                throw core::coders(35, "VK_ERROR_OUT_OF_HOST_MEMORY");
            case VK_ERROR_UNKNOWN:
                throw core::coders(35, "VK_ERROR_UNKNOWN");
            case VK_ERROR_VALIDATION_FAILED_EXT:
                throw core::coders(35, "VK_ERROR_VALIDATION_FAILED_EXT");
            default:
                break;
        }
    }
#endif //defined(CORE_INCLUDE_VULKAN)

