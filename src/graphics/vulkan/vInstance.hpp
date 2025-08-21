//
// Created by kisly on 06.08.2025.
//

#ifndef VINSTANCE_HPP
#define VINSTANCE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <string>

namespace core::vulkan
{
    struct container;

    struct instanceInfo
    {
        const int VULKAN_MAJOR_VERSION = 1;
        const int VULKAN_MINOR_VERSION = 2;
        const int VULKAN_PATCH_VERSION = 0;
        const char* appName = "CoreGL";
        const bool debugApiDump = false;
    };

    struct instance
    {
        static void create(container* cnt, const instanceInfo& info = {});
        static void destroy(container* cnt);
    };
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VINSTANCE_HPP
