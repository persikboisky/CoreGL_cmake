//
// Created by kisly on 13.07.2025.
//

#include "Event.hpp"
#include "Window.hpp"
#include "../util/coders.hpp"
#include "../util/types.hpp"
#include <GLFW/glfw3.h>
#include <cstring>
#include <iostream>

bool Key[MAX_KEY_CODE];

static void key_callbac(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        Key[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        Key[key] = false;
    }
}

void core::Event::setCallbackKey(GLFWkeyfun callback)
{
    glfwSetKeyCallback(this->window, callback);

    for (unsigned int index = 0; index < MAX_KEY_CODE; index++)
    {
        this->key[index] = Key[index];
    }
}

core::Event::Event(core::Window &window) : window(window.getWindowOBJ())
{
    this->setCallbackKey(key_callbac);
    memset(this->saveKey, false, MAX_KEY_CODE);
}

core::Event::Event(GLFWwindow &addrWindow) : window(&addrWindow)
{
    this->setCallbackKey(key_callbac);
    memset(this->saveKey, false, MAX_KEY_CODE);
}

core::Event::~Event()
{
    delete[] this->key;
    delete[] this->saveKey;
}

void core::Event::update()
{
    for (unsigned int index = 0; index < MAX_KEY_CODE; index++)
    {
        this->saveKey[index] = this->key[index];
    }
    this->setCallbackKey(key_callbac);
    glfwPollEvents();
}

bool core::Event::close()
{
    return glfwWindowShouldClose(this->window);
}

bool core::Event::GetMouseLeftButton()
{
    return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT);
}

bool core::Event::GetMouseRightButton()
{
    return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT);
}

bool core::Event::stateKey(int key)
{
    if (key >= MAX_KEY_CODE || key < 0)
    {
        throw core::coders(4, "Function: core::Event::stateKey(int key)");
    }

    else return this->key[key];
}

bool core::Event::stateKey(const core::KEY_CODE& key)
{
    return this->stateKey(convertKeyCode(key));
}

bool core::Event::downKey(int key)
{
    if (this->key[key] && this->saveKey[key] == false)
    {
        return true;
    }
    return false;
}

bool core::Event::downKey(const core::KEY_CODE& key)
{
    return this->downKey(convertKeyCode(key));
}

bool core::Event::upKey(int key)
{
    if (this->key[key] == false && this->saveKey[key])
    {
        return true;
    }
    return false;
}

bool core::Event::upKey(const core::KEY_CODE& key)
{
    return this->upKey(convertKeyCode(key));
}