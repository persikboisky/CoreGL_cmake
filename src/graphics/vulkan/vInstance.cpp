//
// Created by kisly on 04.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vInstance.hpp"
#include "../../config.hpp"
#include "../../util/types.hpp"
#include "../../util/coders.hpp"
#include "../../util/console.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace core
{
    namespace vulkan
    {
        Instance::Instance(const InstanceInfo &instInfo)
        {
            VkApplicationInfo appInfo = {};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = instInfo.appName;
            appInfo.applicationVersion = VK_MAKE_VERSION(
                instInfo.appVersion.MAJOR,
                instInfo.appVersion.MINOR,
                instInfo.appVersion.PATCH
            );
            appInfo.pEngineName = nullptr;
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_MAKE_API_VERSION(
                0,
                instInfo.vulkanVersion.MAJOR,
                instInfo.vulkanVersion.MINOR,
                instInfo.vulkanVersion.PATCH
            );

            VkInstanceCreateInfo instanceCreateInfo = {};
            instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            instanceCreateInfo.pApplicationInfo = &appInfo;

            if (instInfo.glfw)
            {
                uint32_t count = 0;
                instanceCreateInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&count);
                instanceCreateInfo.enabledExtensionCount = count;
            }
            else
            {
                instanceCreateInfo.enabledExtensionCount = 0;
                instanceCreateInfo.ppEnabledExtensionNames = nullptr;
            }

            if (CORE_INFO)
            {
                std::vector<const char*> VALIDATION_LAYERS = {};

                instanceCreateInfo.enabledLayerCount = VALIDATION_LAYERS.size();
                instanceCreateInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
            }
            else
            {
                instanceCreateInfo.enabledLayerCount = 0;
                instanceCreateInfo.ppEnabledLayerNames = nullptr;
            }

            VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &this->instance);
            coders::vulkanProcessingError(result);

            if (CORE_INFO)
            {
                console::printTime();
                std::cout << "Ok: create vulkan instance" << std::endl;
                console::printTime();
                std::cout << "Vulkan v" << instInfo.vulkanVersion.MAJOR << "." <<  instInfo.vulkanVersion.MINOR
                << "." << instInfo.vulkanVersion.PATCH << std::endl;
            }
        }

        Instance::~Instance()
        {
            vkDestroyInstance(this->instance, nullptr);
        }

        Instance Instance::create(const InstanceInfo &instInfo)
        {
            return Instance(instInfo);
        }

        Instance *Instance::ptrCreate(const InstanceInfo &instInfo)
        {
            return new Instance(instInfo);
        }

        VkInstance Instance::getVkInstance()
        {
            return this->instance;
        }
    }
} // core

#endif //defined(CORE_INCLUDE_VULKAN)