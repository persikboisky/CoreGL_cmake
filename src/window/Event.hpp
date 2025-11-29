//
// Created by kisly on 13.07.2025.
//

#ifndef EVENT_HPP
#define EVENT_HPP

#define MAX_KEY_CODE 360
#define MAX_MOUSE_KEY_CODE 12

struct GLFWwindow;

namespace core
{
    enum class KEY : int;
    enum class MOUSE_KEY : int;

    class Window;
    class Event
    {
    private:
        GLFWwindow* window = nullptr;

        bool* key = nullptr;
        bool* saveKey = nullptr;
        bool* mouseKey = nullptr;
        bool* mouseSaveKey = nullptr;

    public:
        explicit Event(GLFWwindow& addrWindow);
        explicit Event(Window& window);

        ~Event();

        /// @brief обновляет список событий
        void update();

        /// @brief событие закрытия окна
        /// @return 
        [[nodiscard]] bool close();

        [[nodiscard]] bool GetMouseLeftButton();
        [[nodiscard]] bool GetMouseRightButton();

        [[nodiscard]] bool stateKey(int key);
        [[nodiscard]] bool stateKey(const core::KEY& key);

        [[nodiscard]] bool downKey(int key);
        [[nodiscard]] bool downKey(const core::KEY& key);

        [[nodiscard]] bool upKey(int key);
        [[nodiscard]] bool upKey(const core::KEY& key);

        [[nodiscard]] bool stateMouseKey(int key);
        [[nodiscard]] bool stateMouseKey(const core::MOUSE_KEY& key);

        [[nodiscard]] bool downMouseKey(int key);
        [[nodiscard]] bool downMouseKey(const core::MOUSE_KEY& key);

        [[nodiscard]] bool upMouseKey(int key);
        [[nodiscard]] bool upMouseKey(const core::MOUSE_KEY& key);
    };
}

#endif //EVENT_HPP
