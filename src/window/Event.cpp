//
// Created by kisly on 13.07.2025.
//

#include "Event.hpp"
#include "Window.hpp"
#include "../util/coders.hpp"
#include <GLFW/glfw3.h>
#include <cstring>


bool Key[MAX_KEY_CODE];
bool MouseKey[MAX_MOUSE_KEY_CODE];

static inline void setCallbackKey(GLFWwindow* window, int key, int scancode, int action, int mods)
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

static inline void setCallbackMouseKey(GLFWwindow* window, int key, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        MouseKey[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        MouseKey[key] = false;
    }
}

core::Event::Event(core::Window &window) : window(window.getWindowOBJ()), key(new bool[MAX_KEY_CODE]),
    saveKey(new bool[MAX_KEY_CODE]), mouseKey(new bool[MAX_MOUSE_KEY_CODE]), mouseSaveKey(new bool[MAX_MOUSE_KEY_CODE])
{
    memset(this->saveKey, false, MAX_KEY_CODE);
    glfwSetKeyCallback(window.getWindowOBJ(), setCallbackKey);
    glfwSetMouseButtonCallback(window.getWindowOBJ(), setCallbackMouseKey);
}

core::Event::Event(GLFWwindow &addrWindow) : window(&addrWindow), key(new bool[MAX_KEY_CODE]),
    saveKey(new bool[MAX_KEY_CODE]), mouseKey(new bool[MAX_MOUSE_KEY_CODE]), mouseSaveKey(new bool[MAX_MOUSE_KEY_CODE])
{
    memset(this->saveKey, false, MAX_KEY_CODE);
    glfwSetKeyCallback(window, setCallbackKey);
    glfwSetMouseButtonCallback(window, setCallbackMouseKey);
}

core::Event::~Event()
{
    delete[] this->key;
    delete[] this->saveKey;
    delete[] this->mouseKey;
    delete[] this->mouseSaveKey;
}

void core::Event::update()
{
    memcpy(this->saveKey, this->key, MAX_KEY_CODE);
    memcpy(this->mouseSaveKey, this->mouseKey, MAX_MOUSE_KEY_CODE);
    glfwPollEvents();
    memcpy(this->key, Key, MAX_KEY_CODE);
    memcpy(this->mouseKey, MouseKey, MAX_MOUSE_KEY_CODE);
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

bool core::Event::stateMouseKey(int key)
{
    if (key >= MAX_MOUSE_KEY_CODE || key < 0)
    {
        throw core::coders(4, "Function: core::Event::stateMouseKey(int key)");
    }

    else return this->mouseKey[key];
}

bool core::Event::stateMouseKey(const core::MOUSE_KEY_CODE& key)
{
    return stateMouseKey(convertMouseKeyCode(key));
}

bool core::Event::downMouseKey(int key)
{
    if (this->mouseKey[key] && this->mouseSaveKey[key] == false)
    {
        return true;
    }
    return false;
}

bool core::Event::downMouseKey(const core::MOUSE_KEY_CODE& key)
{
    return downMouseKey(convertMouseKeyCode(key));
}

bool core::Event::upMouseKey(int key)
{
    if (this->mouseKey[key] && this->mouseSaveKey[key] == false)
    {
        return true;
    }
    return false;
}

bool core::Event::upMouseKey(const core::MOUSE_KEY_CODE& key)
{
    return upMouseKey(convertMouseKeyCode(key));
}

