//
// Created by kisly on 13.07.2025.
//

#include "Event.hpp"
#include "Window.hpp"
#include "../util/coders.hpp"
#include "../types/key.hpp"
#include <GLFW/glfw3.h>
#include <cstring>

bool Key[MAX_KEY_CODE];
bool MouseKey[MAX_MOUSE_KEY_CODE];

static int convertKeyCode(const core::KEY& keyCode);
static int convertMouseKeyCode(const core::MOUSE_KEY& keyCode);

static inline void setCallbackKey(GLFWwindow *window, int key, int scancode, int action, int mods)
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

static inline void setCallbackMouseKey(GLFWwindow *window, int key, int action, int mods)
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

core::Event::Event(core::Window &window) : 
    window(window.getWindowOBJ()), 
    key(new bool[MAX_KEY_CODE]),
    saveKey(new bool[MAX_KEY_CODE]), 
    mouseKey(new bool[MAX_MOUSE_KEY_CODE]), 
    mouseSaveKey(new bool[MAX_MOUSE_KEY_CODE])
{
    memset(this->saveKey, false, MAX_KEY_CODE);
    memset(this->mouseKey, false, MAX_MOUSE_KEY_CODE);
    memset(key, false, MAX_KEY_CODE);
    memset(mouseKey, false, MAX_MOUSE_KEY_CODE);
    glfwSetKeyCallback(window.getWindowOBJ(), setCallbackKey);
    glfwSetMouseButtonCallback(window.getWindowOBJ(), setCallbackMouseKey);
}

core::Event::Event(GLFWwindow &addrWindow) : 
    window(&addrWindow), 
    key(new bool[MAX_KEY_CODE]),                                 
    saveKey(new bool[MAX_KEY_CODE]), 
    mouseKey(new bool[MAX_MOUSE_KEY_CODE]), 
    mouseSaveKey(new bool[MAX_MOUSE_KEY_CODE])
{
    memset(this->saveKey, false, MAX_KEY_CODE);
    memset(this->mouseKey, false, MAX_MOUSE_KEY_CODE);
    memset(key, false, MAX_KEY_CODE);
    memset(mouseKey, false, MAX_MOUSE_KEY_CODE);
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

    else
        return this->key[key];
}

bool core::Event::stateKey(const core::KEY &key)
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

bool core::Event::downKey(const core::KEY &key)
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

bool core::Event::upKey(const core::KEY &key)
{
    return this->upKey(convertKeyCode(key));
}

bool core::Event::stateMouseKey(int key)
{
    if (key >= MAX_MOUSE_KEY_CODE || key < 0)
    {
        throw core::coders(4, "Function: core::Event::stateMouseKey(int key)");
    }

    else
        return this->mouseKey[key];
}

bool core::Event::stateMouseKey(const core::MOUSE_KEY &key)
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

bool core::Event::downMouseKey(const core::MOUSE_KEY &key)
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

bool core::Event::upMouseKey(const core::MOUSE_KEY &key)
{
    return upMouseKey(convertMouseKeyCode(key));
}

static int convertKeyCode(const core::KEY& keyCode)
{
    switch (keyCode)
    {
    case core::KEY::F1:
        return GLFW_KEY_F1;
    case core::KEY::F2:
        return GLFW_KEY_F2;
    case core::KEY::F3:
        return GLFW_KEY_F3;
    case core::KEY::F4:
        return GLFW_KEY_F4;
    case core::KEY::F5:
        return GLFW_KEY_F5;
    case core::KEY::F6:
        return GLFW_KEY_F6;
    case core::KEY::F7:
        return GLFW_KEY_F7;
    case core::KEY::F8:
        return GLFW_KEY_F8;
    case core::KEY::F9:
        return GLFW_KEY_F9;
    case core::KEY::F10:
        return GLFW_KEY_F10;
    case core::KEY::F11:
        return GLFW_KEY_F11;
    case core::KEY::F12:
        return GLFW_KEY_F12;
    case core::KEY::PRINT_SCREEN:
        return GLFW_KEY_PRINT_SCREEN;
    case core::KEY::SCROLL_LOCK:
        return GLFW_KEY_SCROLL_LOCK;
    case core::KEY::PAUSE:
        return GLFW_KEY_PAUSE;
    case core::KEY::K_1:
        return GLFW_KEY_1;
    case core::KEY::K_2:
        return GLFW_KEY_2;
    case core::KEY::K_3:
        return GLFW_KEY_3;
    case core::KEY::K_4:
        return GLFW_KEY_4;
    case core::KEY::K_5:
        return GLFW_KEY_5;
    case core::KEY::K_6:
        return GLFW_KEY_6;
    case core::KEY::K_7:
        return GLFW_KEY_7;
    case core::KEY::K_8:
        return GLFW_KEY_8;
    case core::KEY::K_9:
        return GLFW_KEY_9;
    case core::KEY::K_0:
        return GLFW_KEY_0;
    case core::KEY::Q:
        return GLFW_KEY_Q;
    case core::KEY::W:
        return GLFW_KEY_W;
    case core::KEY::E:
        return GLFW_KEY_E;
    case core::KEY::R:
        return GLFW_KEY_R;
    case core::KEY::T:
        return GLFW_KEY_T;
    case core::KEY::Y:
        return GLFW_KEY_Y;
    case core::KEY::U:
        return GLFW_KEY_U;
    case core::KEY::I:
        return GLFW_KEY_I;
    case core::KEY::O:
        return GLFW_KEY_O;
    case core::KEY::P:
        return GLFW_KEY_P;
    case core::KEY::A:
        return GLFW_KEY_A;
    case core::KEY::S:
        return GLFW_KEY_S;
    case core::KEY::D:
        return GLFW_KEY_D;
    case core::KEY::F:
        return GLFW_KEY_F;
    case core::KEY::G:
        return GLFW_KEY_G;
    case core::KEY::H:
        return GLFW_KEY_H;
    case core::KEY::J:
        return GLFW_KEY_H;
    case core::KEY::K:
        return GLFW_KEY_K;
    case core::KEY::L:
        return GLFW_KEY_L;
    case core::KEY::Z:
        return GLFW_KEY_Z;
    case core::KEY::X:
        return GLFW_KEY_X;
    case core::KEY::C:
        return GLFW_KEY_C;
    case core::KEY::V:
        return GLFW_KEY_V;
    case core::KEY::B:
        return GLFW_KEY_B;
    case core::KEY::N:
        return GLFW_KEY_N;
    case core::KEY::M:
        return GLFW_KEY_M;
    case core::KEY::SPACE:
        return GLFW_KEY_SPACE;
    case core::KEY::ESCAPE:
        return GLFW_KEY_ESCAPE;
    case core::KEY::LEFT_SHIFT:
        return GLFW_KEY_LEFT_SHIFT;
    case core::KEY::LEFT_CONTROL:
        return GLFW_KEY_LEFT_CONTROL;
    default:
        return 0;
    }
}

static int convertMouseKeyCode(const core::MOUSE_KEY& keyCode)
{
    switch (keyCode)
    {
    case core::MOUSE_KEY::BUTTON_1:
        return GLFW_MOUSE_BUTTON_1;
    case core::MOUSE_KEY::BUTTON_2:
        return GLFW_MOUSE_BUTTON_2;
    case core::MOUSE_KEY::BUTTON_3:
        return GLFW_MOUSE_BUTTON_3;
    case core::MOUSE_KEY::BUTTON_4:
        return GLFW_MOUSE_BUTTON_4;
    case core::MOUSE_KEY::BUTTON_5:
        return GLFW_MOUSE_BUTTON_5;
    case core::MOUSE_KEY::BUTTON_6:
        return GLFW_MOUSE_BUTTON_6;
    case core::MOUSE_KEY::BUTTON_7:
        return GLFW_MOUSE_BUTTON_7;
    case core::MOUSE_KEY::BUTTON_8:
        return GLFW_MOUSE_BUTTON_8;
    case core::MOUSE_KEY::BUTTON_LAST:
        return GLFW_MOUSE_BUTTON_LAST;
    case core::MOUSE_KEY::BUTTON_LEFT:
        return GLFW_MOUSE_BUTTON_LEFT;
    case core::MOUSE_KEY::BUTTON_RIGHT:
        return GLFW_MOUSE_BUTTON_RIGHT;
    case core::MOUSE_KEY::BUTTON_MIDDLE:
        return GLFW_MOUSE_BUTTON_MIDDLE;
    }
}