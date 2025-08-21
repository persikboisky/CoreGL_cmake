//
// Created by kisly on 19.08.2025.
//

#ifndef VSURFACE_HPP
#define VSURFACE_HPP

namespace core
{
    class Window;

    namespace vulkan
    {
        struct container;
        struct surface
        {
            static void create(container* cnt, Window& window);
            static void destroy(container* cnt);
        };
    } // vulkan
} // core

#endif //VSURFACE_HPP
