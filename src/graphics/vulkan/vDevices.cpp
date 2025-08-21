//
// Created by kisly on 06.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vDevices.hpp"
#include "vResource.hpp"
#include "../../util/coders.hpp"
#include "../../config.hpp"
#include "../../util/console.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

namespace core
{
    namespace vulkan
    {
        Devices::Devices(const apiContainer& cnt)
        {
            uint32_t count = 0;
            VkResult result = vkEnumeratePhysicalDevices(
                    cnt.instance,
                    &count,
                    nullptr);
            coders::vulkanProcessingError(result);

            this->devices.resize(count);
            result = vkEnumeratePhysicalDevices(
                    cnt.instance,
                    &count,
                    this->devices.data());
            coders::vulkanProcessingError(result);

            if (CORE_INFO)
            {
                console::printTime();
                std::cout << "Ok: get list GPU, count = " << count << std::endl;

                uint32_t id = 0;
                for (VkPhysicalDevice_T* dev : this->devices)
                {
                    VkPhysicalDeviceProperties prop = {};
                    vkGetPhysicalDeviceProperties(dev, &prop);
                    console::printTime();
                    std::cout << "GPU [id = " << id << "] name: " << prop.deviceName << std::endl;
                    id++;
                }
            }
        }

        Devices Devices::get(const apiContainer &cnt)
        {
            return Devices(cnt);
        }

        Devices *Devices::ptGet(const apiContainer &cnt)
        {
            return new Devices(cnt);
        }

        VkPhysicalDevice Devices::getDevice(uint32_t id)
        {
            return this->devices[id];
        }
    } // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
