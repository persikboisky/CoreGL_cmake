//
// Created by kisly on 19.08.2025.
//

#include "vSurface.hpp"
#include "vResource.hpp"
#include "vDevice.hpp"
#include "../../window/Window.hpp"
#include "../../util/coders.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace core
{
    namespace vulkan
    {
        void surface::create(apiContainer* cnt, Window& window)
        {
            VkResult result = glfwCreateWindowSurface(
                    cnt->instance,
                    window.getWindowOBJ(),
                    nullptr,
                    &cnt->surface);
            coders::vulkanProcessingError(result);
        }

        void surface::destroy(apiContainer* cnt)
        {
            device::destroy(cnt);
            vkDestroySurfaceKHR(cnt->instance, cnt->surface, nullptr);
        }
    } // vulkan
} // core