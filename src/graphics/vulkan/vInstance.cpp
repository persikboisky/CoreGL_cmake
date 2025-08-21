//
// Created by kisly on 06.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vInstance.hpp"
#include "vResource.hpp"
#include "../../util/coders.hpp"
#include "../../util/console.hpp"
#include "../../config.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace core::vulkan
{
    void instance::create(container* cnt, const instanceInfo& info)
    {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_MAKE_API_VERSION(
                0,
                info.VULKAN_MAJOR_VERSION,
                info.VULKAN_MINOR_VERSION,
                info.VULKAN_PATCH_VERSION);
        appInfo.pApplicationName = info.appName;
        appInfo.pEngineName = nullptr;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        uint32_t extensionCount = 0;
        instanceCreateInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&extensionCount);
        instanceCreateInfo.enabledExtensionCount = extensionCount;

        std::vector<const char*> nameValidationLayer = {};
        if (CORE_INFO) nameValidationLayer.push_back("VK_LAYER_KHRONOS_validation");
        if (info.debugApiDump) nameValidationLayer.push_back("VK_LAYER_LUNARG_api_dump");
        instanceCreateInfo.ppEnabledLayerNames = nameValidationLayer.data();
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(nameValidationLayer.size());

        instanceCreateInfo.pApplicationInfo = &appInfo;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pNext = nullptr;

        VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &cnt->instance);
        coders::vulkanProcessingError(result);

        if (CORE_INFO)
        {
            console::printTime();
            std::cout << "Ok: create vulkan instance" << std::endl;
        }
    }

    void instance::destroy(container* cnt)
    {
        vkDestroyInstance(cnt->instance, nullptr);
    }
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
