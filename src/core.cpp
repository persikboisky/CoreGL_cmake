//
// Created by kisly on 13.07.2025.
//

#include "../include/core.hpp"
#include "config.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace core::Core
{
    void Init()
    {
        int code = glfwInit();
        if (code == GLFW_FALSE)
        {
            throw core::Coders(0);
        }

        if (CORE_INFO)
        {
            int major;
            int minor;
            int rev;
            glfwGetVersion(&major, &minor, &rev);

            core::console::printTime();
            std::cout << "Ok: init GLFW v";
            std::cout << major << "." << minor << "." << rev << std::endl;
        }
    }

    void Terminate()
    {
        glfwTerminate();
    }

    double getTime()
    {
        return glfwGetTime();
    }
}