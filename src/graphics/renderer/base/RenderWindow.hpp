//
// Created by kisly on 25.12.2025.
//

#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

namespace core
{
    class Window;
    class Event;
    namespace opengl
    {
        class ShaderProgram;
    }

    struct RenderWindowCreateInfo
    {
        int width = 600;
        int height = 600;
        const char* title = "";
        bool resizable = false;
        bool vsync = true;
    };

    class RenderWindow
    {
    protected:
        friend class Rect;

    private:
        Window* ptrWindow = nullptr;
        opengl::ShaderProgram* ptrProgram = nullptr;

        RenderWindow(const RenderWindowCreateInfo& info = {});

    public:
        Event *event = nullptr;

        static RenderWindow create(const RenderWindowCreateInfo& info = {});
        static RenderWindow *ptrCreate(const RenderWindowCreateInfo& info = {});

        ~RenderWindow();

        void display() const;
        void clear() const;
    };
} // namespace core

#endif // RENDERWINDOW_HPP
