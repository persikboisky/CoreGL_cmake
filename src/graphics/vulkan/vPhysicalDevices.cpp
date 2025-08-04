//
// Created by kisly on 04.08.2025.
//

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vPhysicalDevices.hpp"
#include "vInstance.hpp"
#include "../../util/coders.hpp"
#include "../../util/console.hpp"
#include "../../config.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

namespace core
{
    namespace vulkan
    {
        PhysicalDevices::PhysicalDevices(Instance& instance)
        {
            uint32_t count = 0;
            VkResult result = vkEnumeratePhysicalDevices(instance.getVkInstance(), &count, nullptr);
            coders::vulkanProcessingError(result);
            this->listPhysicalDevices.resize(count);
            result = vkEnumeratePhysicalDevices(instance.getVkInstance(), &count, this->listPhysicalDevices.data());
            coders::vulkanProcessingError(result);

            if (CORE_INFO)
            {
                console::printTime();
                std::cout << "Ok: get list physic devices" << std::endl;

                size_t number = 0;
                for (VkPhysicalDevice_T* device : this->listPhysicalDevices)
                {
                    VkPhysicalDeviceProperties prop = {};
                    vkGetPhysicalDeviceProperties(device, &prop);

                    console::printTime();
                    std::cout << "GPU [id : " << number << "] " << prop.deviceName << std::endl;
                    number++;
                }
            }
        }

        PhysicalDevices PhysicalDevices::get(Instance& instance)
        {
            return PhysicalDevices(instance);
        }

        PhysicalDevices *PhysicalDevices::ptrGet(Instance& instance)
        {
            return new PhysicalDevices(instance);
        }
    }
} // core

#endif //defined(CORE_INCLUDE_VULKAN)

