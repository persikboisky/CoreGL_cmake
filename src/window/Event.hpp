//
// Created by kisly on 13.07.2025.
//

#ifndef EVENT_HPP
#define EVENT_HPP

#define MAX_KEY_CODE 360

struct GLFWwindow;
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);

namespace core
{
    enum KEY_CODE : int;
    class Window;
    class Event
    {
    private:
        GLFWwindow* window;

        void setCallbackKey(GLFWkeyfun callback);
        bool* key = new bool[MAX_KEY_CODE];
        char* saveKey = new char[MAX_KEY_CODE];

    public:
        Event(GLFWwindow& addrWindow);
        Event(Window& window);

        ~Event();

        void update();

        [[nodiscard]] bool close();

        [[nodiscard]] bool GetMouseLeftButton();
        [[nodiscard]] bool GetMouseRightButton();

        [[nodiscard]] bool stateKey(int key);
        [[nodiscard]] bool stateKey(const core::KEY_CODE& key);

        [[nodiscard]] bool downKey(int key);
        [[nodiscard]] bool downKey(const core::KEY_CODE& key);

        [[nodiscard]] bool upKey(int key);
        [[nodiscard]] bool upKey(const core::KEY_CODE& key);
    };
}

#endif //EVENT_HPP
