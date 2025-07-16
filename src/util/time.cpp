//
// Created by kisly on 16.07.2025.
//

#include "time.hpp"
#include <GLFW/glfw3.h>

using namespace core;

Timer::Timer() : time(0.0), interval(0.0)
{
}

Timer Timer::create()
{
    return Timer();
}

Timer::~Timer()
{
}

void Timer::start()
{
    this->time = glfwGetTime();
}

void Timer::stop()
{
    this->interval += glfwGetTime() - this->time;
}

void Timer::reset()
{
    this->interval = 0.0;
    this->time = glfwGetTime();
}

[[nodiscard]] double core::Timer::getTime() const
{
    return this->interval + (glfwGetTime() - this->time);
}

void Timer::setTime(double time)
{
    this->interval = time;
}

void Timer::addTime(double time)
{
    this->interval += time;
}

void Timer::difTime(double time)
{
    this->interval -= time;
}