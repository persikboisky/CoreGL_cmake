//
// Created by kisly on 03.08.2025.
//

#include "vInstance.hpp"
#include "../../util/coders.hpp"
#include "../../util/console.hpp"
#include "../../config.hpp"
#include <vulkan/vulkan.h>
#include <iostream>

namespace core
{
    namespace vulkan
    {
        Instance::Instance(const instanceInfo& instInfo)
        {
            VkApplicationInfo appInfo = {};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.apiVersion = VK_MAKE_API_VERSION(
                0,
                instInfo.VULKAN_VERSION_MAJOR,
                instInfo.VULKAN_VERSION_MINOR,
                instInfo.VULKAN_VERSION_PATCH
            );
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = nullptr;
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pApplicationName = instInfo.applicationName;

            VkInstanceCreateInfo instanceCreateInfo = {};
            instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            instanceCreateInfo.enabledExtensionCount = 0;
            instanceCreateInfo.ppEnabledExtensionNames = nullptr;
            instanceCreateInfo.pApplicationInfo = &appInfo;
            instanceCreateInfo.enabledLayerCount = 0;
            instanceCreateInfo.ppEnabledLayerNames = nullptr;

            VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &this->instance);
            switch (result)
            {
                case VK_ERROR_EXTENSION_NOT_PRESENT:
                    throw coders(35, "VK_ERROR_EXTENSION_NOT_PRESENT");
                    break;
                case VK_ERROR_INCOMPATIBLE_DRIVER:
                    throw coders(35, "VK_ERROR_INCOMPATIBLE_DRIVER");
                    break;
                case VK_ERROR_INITIALIZATION_FAILED:
                    throw coders(35, "VK_ERROR_INITIALIZATION_FAILED");
                    break;
                case VK_ERROR_LAYER_NOT_PRESENT:
                    throw coders(35, "VK_ERROR_LAYER_NOT_PRESENT");
                    break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    throw coders(35, "VK_ERROR_OUT_OF_DEVICE_MEMORY");
                    break;
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    throw coders(35, "VK_ERROR_OUT_OF_HOST_MEMORY");
                    break;
                case VK_ERROR_UNKNOWN:
                    throw coders(35, "VK_ERROR_UNKNOWN");
                    break;
                case VK_ERROR_VALIDATION_FAILED_EXT:
                    throw coders(35, "VK_ERROR_VALIDATION_FAILED_EXT");
                    break;
                default:
                    break;
            }

            if (CORE_INFO)
            {
                console::printTime();
                std::cout << "Ok: create Vulkan instance" << std::endl;
            }
        }

        Instance::~Instance()
        {
            vkDestroyInstance(this->instance, nullptr);
        }

        Instance Instance::create(const instanceInfo& instInfo)
        {
            return Instance(instInfo);
        }

        Instance *Instance::ptrCreate(const instanceInfo& instInfo)
        {
            return new Instance(instInfo);
        }
    }
} // core

