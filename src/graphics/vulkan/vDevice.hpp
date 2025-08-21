//
// Created by kisly on 19.08.2025.
//

#ifndef VDEVICE_HPP
#define VDEVICE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core::vulkan
{

    struct container;
    class Devices;

    struct device
    {
        static void create(container* cnt, Devices &devices, uint32_t id = 0);
        static void destroy(container* cnt);
    };
}

#endif //!VRESOURCE_HPP
#endif //VDEVICE_HPP
