//
// Created by kisly on 06.08.2025.
//

#ifndef DEVICES_HPP
#define DEVICES_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
    struct container;
    class Devices
    {
    private:
        std::vector<VkPhysicalDevice> devices;

        explicit Devices(const container& cnt);

    public:
        static Devices get(const container& cnt);
        static Devices *ptGet(const container& cnt);

        ~Devices() = default;

        VkPhysicalDevice getDevice(uint32_t id);
    };
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //DEVICES_HPP
