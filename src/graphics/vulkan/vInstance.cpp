//
// Created by kisly on 06.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vInstance.hpp"
#include "vResource.hpp"
#include "../../util/types.hpp"
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
        VkApplicationInfo applicationInfo = {};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = info.appName.c_str();
        applicationInfo.applicationVersion = VK_MAKE_VERSION(
                info.APP_VERSION.MAJOR,
                info.APP_VERSION.MINOR,
                info.APP_VERSION.PATCH);
        applicationInfo.apiVersion = VK_MAKE_API_VERSION(
                0,
                info.VULKAN_VERSION.MAJOR,
                info.VULKAN_VERSION.MINOR,
                info.VULKAN_VERSION.PATCH);
        applicationInfo.pEngineName = nullptr;
        applicationInfo.engineVersion = VK_VERSION_1_0;

        VkInstanceCreateInfo instanceInfo = {};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pNext = nullptr;
        instanceInfo.flags = 0;
        instanceInfo.pApplicationInfo = &applicationInfo;

        uint32_t countLayer = 0;
        std::vector<VkLayerProperties> layer = {};
        vkEnumerateInstanceLayerProperties(&countLayer, nullptr);
        layer.resize(countLayer);
        vkEnumerateInstanceLayerProperties(&countLayer, layer.data());

        std::vector<const char*> nameValidationLayer = {};
        if (CORE_INFO) nameValidationLayer.push_back("VK_LAYER_KHRONOS_validation");
        if (info.debugApiDump) nameValidationLayer.push_back("VK_LAYER_LUNARG_api_dump");
        instanceInfo.enabledLayerCount = static_cast<uint32_t>(nameValidationLayer.size());
        instanceInfo.ppEnabledLayerNames = nameValidationLayer.data();

        uint32_t countExt = 0;
        instanceInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&countExt);
        instanceInfo.enabledExtensionCount = countExt;

        VkResult result = vkCreateInstance(
                &instanceInfo,
                nullptr,
                &cnt->instance);
        coders::vulkanProcessingError(result);

        if (CORE_INFO)
        {
            console::printTime();
            std::cout << "Ok: create vulkan instance" << std::endl;
        }
    }
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
