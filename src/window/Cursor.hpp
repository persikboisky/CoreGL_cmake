//
// Created by kisly on 14.07.2025.
//

#ifndef CURSOR_HPP
#define CURSOR_HPP

struct GLFWwindow;
struct GLFWcursor;

namespace core
{
    class Window;

    class CustomCursor
    {
    private:
        GLFWcursor* cursor_objs;
        GLFWwindow& addrWindow;

    public:
        CustomCursor(const char* pathToImg, int x, int y, GLFWwindow* window);
        ~CustomCursor();

        void use();
        void unUse();
    };

    class Cursor
    {
    private:
        GLFWwindow* window;

    public:
        Cursor(GLFWwindow& addrWindow);
        Cursor(Window& window);
        ~Cursor();

        void setCursorMode(int mode);
        void showCursor(bool flag);
        void disableCursor(bool flag);
        void setPosition(double x, double y);

        double getCordCursorX();
        double getCordCursorY();

        void getCordCursor(double& x, double& y);

        CustomCursor create(const char* pathToPng, int posXimg = 0, int posYimg = 0);
    };
}

#endif //CURSOR_HPP
