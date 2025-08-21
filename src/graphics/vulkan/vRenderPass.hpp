//
// Created by kisly on 21.08.2025.
//

#ifndef VRENDERPASS_HPP
#define VRENDERPASS_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core::vulkan
{
    struct apiContainer;
    struct piplineContainer;
    struct renderPass
    {
        static void create(piplineContainer* rCnt, apiContainer& cnt);
        static void destroy(piplineContainer* rCnt, const apiContainer& cnt);
    };
} // core::vulkan

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VRENDERPASS_HPP
