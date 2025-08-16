//
// Created by kisly on 06.08.2025.
//

#ifndef VINSTANCE_HPP
#define VINSTANCE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../util/types.hpp"
#include <vulkan/vulkan.h>
#include <string>

namespace core::vulkan
{
    struct container;
    struct instanceInfo
    {
        version3 VULKAN_VERSION = {1, 0, 0};
        version3 APP_VERSION = {1, 0, 0};
        std::string appName = "CoreGL";
        bool debugApiDump = false;
    };

    struct instance
    {
        static void create(container* cnt, const instanceInfo& info = {});
    };
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VINSTANCE_HPP
