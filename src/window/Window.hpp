//
// Created by kisly on 13.07.2025.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../util/types.hpp"
#include "../modules.hpp"

struct GLFWwindow;
struct GLFWmonitor;

namespace core
{
    /// @brief структура описывающая openGL контекст
    struct WindowApiGlInfo
    {
        bool VerticalSynchronization = true;
        version2 OpenGlVersion = {3, 3};
    };

    /// @brief структура описывающая параметры для создания окна
    struct WindowInfo
    {
        /// @brief если выключен vulkan, то этот указатель указывает н аобъект структуры core::WindowApiGlInfo
        WindowApiGlInfo* ptrApiGlInfo = nullptr;

        /// @brief ширина окна
        int width = 800;

        /// @brief позиция окна по y
        int posY = 100;

        /// @brief позиция окна по x
        int posX = 100;

        /// @brief высота окна
        int height = 800;

        /// @brief заголовок окна
        const char *title = "CoreGL";

        /// @brief путь к иконке окна(не обязательно),
        /// @brief форматы JPEG, PNG, TGA, BMP, PSD, GIF (без анимации), HDR, PIC, PNM
        const char *pathToIcon = nullptr;

        /// @brief при создание окна ОС фокусируется на нём
        bool windowFocus = true;

        /// @brief окно c кнопоками заимодействия
        bool windowDecorate = true;

        /// @brief разрешить изменение размера окна
        bool resizable = false;

        /// @brief полноэкранный режим
        bool fullScreen = false;
#if defined(CORE_INCLUDE_VULKAN)

        /// @brief режим vulkan(opengl не работает в этом режиме для данного окна)
        bool VulkanAPI = false;
#endif // defined(CORE_INCLUDE_VULKAN)
    };

    class Event;
    class Cursor;
    class Monitor;
    class Window
    {
    private:
        GLFWwindow *window;
        static bool flagGladInit;

        int width;
        int height;

        int saveWidth;
        int saveHeight;

        int posX;
        int posY;

        bool VSfps = true;
        bool flagFullScreen = false;

#if defined(CORE_INCLUDE_VULKAN)
        bool VulknanAPI = false;
#endif // defined(CORE_INCLUDE_VULKAN)

        double time = 0.0;
        double deltaTime = 0.0;

        void createWindow(int width, int height, const char *title, bool resizable, bool vkAPI, GLFWmonitor* ptrMon);
        void getSizeWindow();
        void Init();

        explicit Window(const WindowInfo &winInfo = {});
        Window(int width, int height, const char *title, bool resizable, bool vkAPI);

        void setMonitor(Monitor& monitor);
        void resetMonitor();

    public:
        /// @brief указатель на объект событий данного окна
        Event *event = nullptr;

        /// @brief указатель на объект курсора данного окна
        Cursor *cursor = nullptr;

        /// @brief указатель на монитор данного окна
        Monitor *monitor = nullptr;

        GLFWwindow* getWindowOBJ();

        /// @brief функйция создания окна
        /// @param winInfo объект структуры core::WindowInfo
        /// @return объект класса core::Window
        [[nodiscard]] static Window create(const WindowInfo &winInfo = {});

        /// @brief функйция создания окна
        /// @param width ширина окна
        /// @param height высота окна
        /// @param title заголовок окна
        /// @param resizable разрешить изменять размер окна
        /// @param vkAPI режим vulkan(opengl не работает в этом режиме для данного окна)
        /// @return объект класса core::Window
        [[nodiscard]] static Window create(int width, int height, const char *title = "", bool resizable = false, bool vkAPI = false);

        
        /// @brief проверяет является ли окно контекстом(работает только когда выключен vulkan)
        /// @return флаг
        [[nodiscard]] bool isContext();

        /// @brief удаляет окно и все его ресурсы
        ~Window();

        /// @brief делает окно текущим контекстом(работает только когда выключен vulkan)
        void setGlContext();

        /// @brief сменяет буферы кадра встроенные в окно(работает только когда выключен vulkan)
        void swapBuffers();

        /// @brief устанавливает иконку
        /// @param pathToImg путь к иконке (форматы: JPEG, PNG, TGA, BMP, PSD, GIF (без анимации), HDR, PIC, PNM)
        void setIcon(const char *pathToImg);

        /// @brief получает ширину окна
        /// @return ширина
        [[nodiscard]] int getWidth() const;

        /// @brief получает высоту окна
        /// @return высота
        [[nodiscard]] int getHeight() const;

        /// @brief получает размер окна
        /// @return объект структуры core::size2i
        [[nodiscard]] size2i getSize() const;

        /// @brief получает коэффициент соотношение сторон
        /// @return коэффициент
        [[nodiscard]] float getAspect();

        /// @brief включает вертикальную синхронизация(работает только когда выключен vulkan)
        /// @param flag влаг
        void VerticalSynchronization(bool flag);

        /// @brief устанавливает позиция окна
        /// @param posX позиция по x
        /// @param posY позиция по y
        void setPos(int posX, int posY);

        /// @brief устанавливает позиция окна
        /// @param pos объект структуры core::size2i
        void setPos(const pos2i &pos);

        /// @brief устанавливает позиция окна
        /// @param pos POSITION::DOWN_CENTER_SIDE(внизу посередине), POSITION::CENTER(по центру), и т.д.
        void setPos(const POSITION &pos);

        /// @brief устанавливает размер окна
        /// @param width ширина
        /// @param height высота
        void setSize(int width, int height);

        /// @brief устанавливает размер окна
        /// @param size объект структуры core::size2i
        void setSize(const size2i &size);

        /// @brief устанавливает или выключает полноэкранный режим
        /// @param flag флаг
        void fullScreen(bool flag = true);

        /// @brief возвращает время пройденное с последнего вызова Window::update()
        /// @return время в секундах
        [[nodiscard]] double getDeltaTime() const;

        /// @brief создаёт сигнал на закрытие окна(окно не закрывает)
        void close();

        /// @brief обновляет все состовляющее объекта окна
        void update();
    };
}

#endif // WINDOW_HPP
