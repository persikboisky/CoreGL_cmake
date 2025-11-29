//
// Created by kisly on 14.07.2025.
//

#include "Monitor.hpp"
#include "../util/coders.hpp"
#include "../config.hpp"
#include "../util/console.hpp"
#include "../types/size.hpp"
#include "../types/color.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace core;

GLFWmonitor *Monitor::getGLFWObj()
{
    return this->monitor;
}

Monitor::Monitor()
{
    this->monitor = glfwGetPrimaryMonitor();
    if (this->monitor == nullptr)
    {
        throw coders(0x11);
    }

    this->vidMode = glfwGetVideoMode(this->monitor);
    if (this->vidMode == nullptr)
    {
        throw coders(0x12);
    }

    if (CORE_INFO)
    {
        console::printTime();
        std::cout << "Ok: init monitor: " << glfwGetMonitorName(this->monitor) << std::endl;
    }
}

Monitor::~Monitor()
{
}

Size2i Monitor::getPhysicalSize()
{
    int width;
    int height;

    glfwGetMonitorPhysicalSize(this->monitor, &width, &height);

    return Size2i(width, height);
}

Size2i Monitor::getSize()
{
    return Size2i(
            this->vidMode->width,
            this->vidMode->height
    );
}

color::RGB Monitor::getBITS()
{
    return color::RGB(
            this->vidMode->redBits,
            this->vidMode->greenBits,
            this->vidMode->blueBits
    );
}