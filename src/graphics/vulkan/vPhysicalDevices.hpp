//
// Created by kisly on 04.08.2025.
//

#ifndef VPHYSICALDEVICES_HPP
#define VPHYSICALDEVICES_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
    namespace vulkan
    {
        class Instance;
        class PhysicalDevices
        {
        private:
            std::vector<VkPhysicalDevice> listPhysicalDevices = {};

            PhysicalDevices(Instance& instance);

        public:
            static PhysicalDevices get(Instance& instance);
            static PhysicalDevices *ptrGet(Instance& instance);
        };
    }
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VPHYSICALDEVICES_HPP
