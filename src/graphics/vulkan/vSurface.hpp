//
// Created by kisly on 19.08.2025.
//

#ifndef VSURFACE_HPP
#define VSURFACE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)

namespace core
{
    class Window;

    namespace vulkan
    {
        struct apiContainer;
        struct surface
        {
            static void create(apiContainer* cnt, Window& window);
            static void destroy(apiContainer* cnt);
        };
    } // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VSURFACE_HPP
