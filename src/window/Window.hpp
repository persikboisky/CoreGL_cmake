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
    struct windowInfo
    {
        const char *title = "CoreGL";
        const char *pathToIcon = nullptr;
        int width = 800;
        int height = 800;
        bool VerticalSynchronization = true;
        bool resizable = false;
        int posX = 100;
        int posY = 100;
        bool fullScreen = false;
#if defined(CORE_INCLUDE_VULKAN)
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

        explicit Window(const windowInfo &winInfo = {});
        Window(int width, int height, const char *title, bool resizable, bool vkAPI);

        void setMonitor(Monitor& monitor);
        void resetMonitor();

    public:
        Event *event;
        Cursor *cursor;
        Monitor *monitor;

        [[nodiscard]] static Window create(const windowInfo &winInfo = {});
        [[nodiscard]] static Window create(int width, int height, const char *title = "", bool resizable = false, bool vkAPI = false);

        [[nodiscard]] GLFWwindow *getWindowOBJ();
        [[nodiscard]] bool isContext();

        ~Window();

        void setContext();
        void swapBuffers();

        void setClearColor(const color::RGBA &color);
        void clearFrameBuffer();
        void clearZBuffer();

        void setSizeFrameBuffer(int width, int height);
        void setSizeFrameBuffer(const size2i &size);

        void setPosFrameBuffer(int posX, int posY);
        void setPosFrameBuffer(const pos2i &pos);

        void setIcon(const char *pathToImg);

        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] size2i getSize() const;
        [[nodiscard]] float getAspect();

        void VerticalSynchronization(bool flag);

        void setPos(int posX, int posY);

        void setPos(const pos2i &pos);
        void setPos(const POSITION &pos);

        void setSize(int width, int height);
        void setSize(const size2i &size);

        void fullScreen(bool flag = true);

        [[nodiscard]] double getDeltaTime() const;
    };
}

#endif // WINDOW_HPP
