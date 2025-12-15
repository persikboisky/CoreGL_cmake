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
    protected:
        friend class Window;

    private:
        GLFWwindow* window = nullptr;

        bool* key = nullptr;
        bool* saveKey = nullptr;
        bool* mouseKey = nullptr;
        bool* mouseSaveKey = nullptr;

        bool stateKey(int key);
        bool downKey(int key);
        bool upKey(int key);
        bool stateMouseKey(int key);
        bool downMouseKey(int key);
        bool upMouseKey(int key);

        explicit Event(GLFWwindow& addrWindow);
        explicit Event(Window& window);

    public:
        ~Event();

        /// @brief обновляет список событий
        void update();

        /// @brief событие закрытия окна
        /// @return true, если нажат крестик, завершена задача или вызвана команда Window::close()
        [[nodiscard]] bool close();

        /// @brief проверяет нажата ли левая кнопка мыши
        /// @return true если нажата
        [[nodiscard]] bool GetMouseLeftButton();

        /// @brief проверяет нажата ли правая кнопка мыши
        /// @return true если нажата
        [[nodiscard]] bool GetMouseRightButton();

        /// @brief получает состояние клавиши
        /// @param key имя клавиши(пример: core::KEY::LEFT_SHIFT, core::KEY::W)
        /// @return true - зажата, false - отпущена
        [[nodiscard]] bool stateKey(const core::KEY& key);

        /// @brief отлавливает момент нажатия клавиши
        /// @param key имя клавиши(пример: core::KEY::LEFT_SHIFT, core::KEY::W)
        /// @return true - в момент нажатия, false - в остальных случаях
        [[nodiscard]] bool downKey(const core::KEY& key);

        /// @brief
        /// @param key 
        /// @return 
        [[nodiscard]] bool upKey(const core::KEY& key);
        [[nodiscard]] bool stateMouseKey(const core::MOUSE_KEY& key);
        [[nodiscard]] bool downMouseKey(const core::MOUSE_KEY& key);
        [[nodiscard]] bool upMouseKey(const core::MOUSE_KEY& key);
    };
}

#endif //EVENT_HPP
