//
// Created by kisly on 04.09.2025.
//

#include "vk_physicalDevices.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../config.hpp"
#include "../../../util/Coders.hpp"
#include "../../../util/console.hpp"
#include "vk_Surface.hpp"
#include "vk_Instance.hpp"
#include <iostream>
#include <format>

namespace core
{
    namespace vulkan
    {
    PhysicalDeviceInfo::PhysicalDeviceInfo(VkPhysicalDevice physicalDevice) : physicalDevice(physicalDevice)
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        queueFamilies.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    }

    uint32_t PhysicalDeviceInfo::getQueueFamilyCount() const
    {
        return queueFamilies.size();
    }

    uint32_t PhysicalDeviceInfo::getQueueCount(uint32_t queueFamilyIndex) const
    {
        return queueFamilies[queueFamilyIndex].queueCount;
    }

    void PhysicalDeviceInfo::printQueueFamilyInfo()
    {
        std::cout << "--------QueueFamiliesInfo--------" << std::endl;
        std::cout << "QueueFamiliesCount: " << queueFamilies.size() << std::endl;
        for (uint32_t i = 0; i < queueFamilies.size(); i++)
        {
            std::cout << std::format("-------QueueFamily: {} Info-------", i) << std::endl;
            std::cout << "QueueCount: " << queueFamilies[i].queueCount << std::endl;
            std::cout << "OperateTypes: ";
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                std::cout << "Graphics ";
            if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
                std::cout << "Computer ";
            if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
                std::cout << "Transfer ";
            if (queueFamilies[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
                std::cout << "SparseBinding ";
            if (queueFamilies[i].queueFlags & VK_QUEUE_PROTECTED_BIT)
                std::cout << "Protected ";
            if (queueFamilies[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
                std::cout << "VideoDecode ";
            if (queueFamilies[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)
                std::cout << "VideoEncode ";
            std::cout << "\n\n";
        }
    }

    uint32_t PhysicalDeviceInfo::minImageCount(const Surface& surface) const
    {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface.surface, &surfaceCapabilities);
        return surfaceCapabilities.minImageCount;
    }

    uint32_t PhysicalDeviceInfo::maxImageCount(const Surface& surface) const
    {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface.surface, &surfaceCapabilities);
        return surfaceCapabilities.maxImageCount;
    }

    bool PhysicalDeviceInfo::checkOperationSupport(uint32_t queueFamilyIndex, const OPERATES_TYPE &type) const
    {
        switch (type)
        {
            case OPERATES_TYPE::GRAPHICS:
                return queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT;
            case OPERATES_TYPE::COMPUTER:
                return queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT;
            case OPERATES_TYPE::TRANSFER:
                return queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_TRANSFER_BIT;
            case OPERATES_TYPE::SPARSE_BINDING:
                return queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_PROTECTED_BIT;
            case OPERATES_TYPE::PROTECTED:
                return queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_PROTECTED_BIT;
            case OPERATES_TYPE::VIDEO_DECODE:
                return queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR;
            case OPERATES_TYPE::VIDEO_ENCODE:
            default:
                return queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR;
        }
    }

    bool PhysicalDeviceInfo::checkPresentOperationSupport(uint32_t queueFamilyIndex, const Surface &surface) const
    {
        VkBool32 presentSupport = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface.surface, &presentSupport);
        if (presentSupport == VK_TRUE)
            return true;
        return false;
    }

    uint32_t PhysicalDeviceInfo::getQueueFamilyIndex(const OPERATES_TYPE &type)
    {
        for (uint32_t i = 0; i < queueFamilies.size(); i++)
        {
            switch (type)
            {
            case OPERATES_TYPE::COMPUTER:
                if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) return i;
                break;
            case OPERATES_TYPE::TRANSFER:
                if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) return i;
                break;
            case OPERATES_TYPE::SPARSE_BINDING:
                if (queueFamilies[i].queueFlags & VK_QUEUE_PROTECTED_BIT) return i;
                break;
            case OPERATES_TYPE::PROTECTED:
                if (queueFamilies[i].queueFlags & VK_QUEUE_PROTECTED_BIT) return i;
                break;
            case OPERATES_TYPE::VIDEO_DECODE:
                if (queueFamilies[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR) return i;
                break;
            case OPERATES_TYPE::VIDEO_ENCODE:
                if (queueFamilies[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) return i;
                break;
            case OPERATES_TYPE::GRAPHICS:
            default:
                if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) return i;
                break;
            }
        }

        throw Coders(NONE_CODERS,
            "Failed[Vulkan error]: Your graphics device" +
            std::string(deviceProperties.deviceName) +
            "does not support operations");
    }

    uint32_t PhysicalDeviceInfo::getPresentQueueFamilyIndex(const class Surface &surface)
    {
        for (uint32_t i = 0; i < queueFamilies.size(); i++)
        {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                VkBool32 presentSupport = VK_FALSE;
                vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface.surface, &presentSupport);
                if (presentSupport == VK_TRUE)
                    return i;
            }
        }

        throw Coders(NONE_CODERS,
            "Failed[Vulkan error]: Your graphics device" +
            std::string(deviceProperties.deviceName) +
            " does not support Present operations");
    }

    PhysicalDevices::PhysicalDevices(Instance& instance)
        {
            uint32_t count = 0;
            VkResult result = vkEnumeratePhysicalDevices(
                    instance.instance,
                    &count,
                    nullptr);
            Coders::vulkanProcessingError(result);

            this->devices.resize(count);

            result = vkEnumeratePhysicalDevices(
                    instance.instance,
                    &count,
                    this->devices.data());
            Coders::vulkanProcessingError(result);

            if (CORE_INFO)
            {
                count = 0;
                for (const VkPhysicalDevice& device : this->devices)
                {
                    VkPhysicalDeviceProperties prop = {};
                    vkGetPhysicalDeviceProperties(device, &prop);

                    console::printTime();
                    std::cout << "GPU [id: " << count << "] " << prop.deviceName << std::endl;

                    count++;
                }
            }
        }

        PhysicalDevices PhysicalDevices::get(Instance& instance)
        {
            return PhysicalDevices(instance);
        }

        PhysicalDevices* PhysicalDevices::ptrGet(Instance& instance)
        {
            return new PhysicalDevices(instance);
        }

        PhysicalDeviceInfo PhysicalDevices::getDeviceInfo(uint32_t index) const
        {
            return PhysicalDeviceInfo(devices[index]);
        }
        } // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)