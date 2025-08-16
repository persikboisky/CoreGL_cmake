//
// Created by kisly on 06.08.2025.
//

#ifndef DEVICES_HPP
#define DEVICES_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
    namespace vulkan
    {
        struct container;
        class Devices
        {
        private:
            std::vector<VkPhysicalDevice> devices;

            Devices(const container& cnt);

        public:
            static Devices get(const container& cnt);
            static Devices *ptrGet(const container& cnt);
        };
    } // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //DEVICES_HPP
