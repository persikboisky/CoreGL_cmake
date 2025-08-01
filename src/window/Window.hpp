//
// Created by kisly on 13.07.2025.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../util/types.hpp"

struct GLFWwindow;

namespace core
{
    struct windowInfo
    {
        const char* title = "CoreGL";
        const char* pathToIcon = nullptr;
        int width = 1280;
        int height = 720;
        bool VerticalSynchronization = true;
        bool resizable = false;
        int posX = -1;
        int posY = -1;
        bool fullScreen = false;
    };

    class Event;
    class Cursor;
    class Monitor;
    class Window
    {
    private:
        GLFWwindow* window;
        static bool flagGladInit;

        int width;
        int height;

        int saveWidth;
        int saveHeight;

        int posX;
        int posY;

        bool VSfps = true;
        bool flagFullScreen = false;

        double time = 0.0;
        double deltaTime = 0.0;

        void getSizeWindow();
        void Init();

        Window(const windowInfo& winInfo);
        Window(int width, int height, const char* title, bool resizable);

        void setMonitor(Monitor monitor);
        void resetMonitor();

    public:
        Event* event;
        Cursor* cursor;
        Monitor* monitor;

        [[nodiscard]] static Window create(const windowInfo& winInfo);
        [[nodiscard]] static Window create(int width, int height, const char* title = "", bool resizable = false);

        [[nodiscard]] GLFWwindow* getWindowOBJ();
        [[nodiscard]] bool isContext();

        ~Window();

        void setContext();
        void swapBuffers();

        void enableZBuffer();
        void setClearColor(const color::RGBA& color);
        void clearFrameBuffer();
        void clearZBuffer();

        void setSizeFrameBuffer(int width, int height);
        void setSizeFrameBuffer(const size2i& size);

        void setPosFrameBuffer(int posX, int posY);
        void setPosFrameBuffer(const pos2i& pos);

        void setIcon(const char* pathToImg);

        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] size2i getSize() const;
        [[nodiscard]] float getAspect();

        void VerticalSynchronization(bool flag);

        void setPos(int posX, int posY);

        void setPos(const pos2i& pos);
        void setPos(const POSITION& pos);

        void setSize(int width, int height);
        void setSize(const size2i& size);

        void fullScreen(bool flag = true);

        [[nodiscard]] double getDeltaTime() const;
    };
}

#endif //WINDOW_HPP
