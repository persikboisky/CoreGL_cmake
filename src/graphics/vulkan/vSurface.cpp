//
// Created by kisly on 19.08.2025.
//

#include "vSurface.hpp"
#include "vResource.hpp"
#include "../../window/Window.hpp"
#include "../../util/coders.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace core
{
    namespace vulkan
    {
        void surface::create(container *cnt, Window& window)
        {
            VkResult result = glfwCreateWindowSurface(cnt->instance, window.getWindowOBJ(), nullptr, &cnt->surface);
            coders::vulkanProcessingError(result);
        }
    } // vulkan
} // core