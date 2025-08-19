//
// Created by kisly on 19.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include "vDevice.hpp"
#include "vResource.hpp"
#include "vDevices.hpp"
#include "../../util/coders.hpp"

namespace core
{
    namespace vulkan
    {
        void device::create(container* cnt, Devices &devices, uint32_t id)
        {
            cnt->physicalDevice = devices.getDevice(id);

            uint32_t queueFamilyCount;
            std::vector<VkQueueFamilyProperties> queueFamilyProperties;

            vkGetPhysicalDeviceQueueFamilyProperties(
                    cnt->physicalDevice,
                    &queueFamilyCount,
                    nullptr);
            queueFamilyProperties.resize(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(
                    cnt->physicalDevice,
                    &queueFamilyCount,
                    queueFamilyProperties.data());

            auto *pSupport = new VkBool32[queueFamilyCount];
            for (uint32_t i = 0; i < queueFamilyCount; i++)
            {
                vkGetPhysicalDeviceSurfaceSupportKHR(
                        cnt->physicalDevice,
                        i,
                        cnt->surface,
                        &pSupport[i]);
            }

            cnt->graphicQueueFamilyIndex = UINT32_MAX;
            cnt->presentQueueFamilyIndex = UINT32_MAX;

            for (uint32_t i = 0; i < queueFamilyCount; i++)
            {
                if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    if (cnt->graphicQueueFamilyIndex == UINT32_MAX)
                        cnt->graphicQueueFamilyIndex = i;


                    if (pSupport[i] == VK_TRUE)
                    {
                        cnt->graphicQueueFamilyIndex = i;
                        cnt->presentQueueFamilyIndex = i;
                        break;
                    }
                }
            }

            if (cnt->presentQueueFamilyIndex == UINT32_MAX)
                for (size_t i = 0; i < queueFamilyCount; ++i)
                    if (pSupport[i] == VK_TRUE)
                    {
                        cnt->presentQueueFamilyIndex = i;
                        break;
                    }

            delete[] pSupport;

            std::vector<const char*> s_deviceExtensionNames;
            s_deviceExtensionNames.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

            VkDeviceQueueCreateInfo deviceQueueInfo = {};
            deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            deviceQueueInfo.pNext = nullptr;
            deviceQueueInfo.pQueuePriorities = new float[1]{0.0};
            deviceQueueInfo.queueCount = 1;
            deviceQueueInfo.queueFamilyIndex = cnt->graphicQueueFamilyIndex;

            VkDeviceCreateInfo deviceInfo = {};
            deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            deviceInfo.pNext = nullptr;
            deviceInfo.queueCreateInfoCount = 1;
            deviceInfo.pQueueCreateInfos = &deviceQueueInfo;
            deviceInfo.enabledExtensionCount = s_deviceExtensionNames.size();
            deviceInfo.ppEnabledExtensionNames = s_deviceExtensionNames.data();
            deviceInfo.enabledLayerCount = 0;
            deviceInfo.ppEnabledLayerNames = nullptr;

            VkResult result = vkCreateDevice(
                    cnt->physicalDevice,
                    &deviceInfo,
                    nullptr,
                    &cnt->logicalDevice);
            coders::vulkanProcessingError(result);

            vkGetDeviceQueue(
                    cnt->logicalDevice,
                    deviceQueueInfo.queueFamilyIndex,
                    0,
                    &cnt->graphicsQueue);
        }
    }
}

#endif //!VRESOURCE_HPP