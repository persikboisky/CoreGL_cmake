//
// Created by kisly on 14.07.2025.
//

#ifndef CURSOR_HPP
#define CURSOR_HPP

struct GLFWwindow;
struct GLFWcursor;
struct GLFWimage;

namespace core
{
    class Window;
    class Image;

    /// @brief класс кастомного курсора
    class CustomCursor
    {
    private:
        GLFWcursor* cursor_objs;
        GLFWwindow* ptrWindow;
        GLFWimage* ptrImg = nullptr;

        CustomCursor(const char* pathToImg, const Window& window, int x, int y);
        CustomCursor(Image& image, int x, int y, const Window& window);

    public:
        /// @brief создаёт кастомный курсор и возвращает объект core::CustomCursor
        /// @param pathToImg путь к изображению (форматы: JPEG, PNG, TGA, BMP, PSD, GIF (без анимации), HDR, PIC, PNM)
        /// @param x координата положения изображения в колизии курсора
        /// @param y координата положения изображения в колизии курсора
        /// @param window объект окна
        /// @return объект core::CustomCursor
        static CustomCursor create(const char* pathToImg, int x, int y, const  Window& window);

        /// @brief создаёт кастомный курсор и возвращает объект core::CustomCursor
        /// @param image объект класса core::Image
        /// @param x координата положения изображения в колизии курсора
        /// @param y координата положения изображения в колизии курсора
        /// @param window объект окна
        /// @return объект core::CustomCursor
        static CustomCursor create(Image& image, int x, int y, const  Window& window);

        ~CustomCursor();

        /// @brief установить курсор
        void use();

        /// @brief вернуть дефолтный курсор
        void unUse();
    };

    class Cursor
    {
    protected:
        friend class Window;

    private:
        GLFWwindow* window;

        Cursor(GLFWwindow& addrWindow);
        Cursor(Window& window);

    public:
        ~Cursor();

        void setCursorMode(int mode);
        void showCursor(bool flag);
        void disableCursor(bool flag);
        void setPosition(double x, double y);

        double getCordCursorX();
        double getCordCursorY();

        void getCordCursor(double& x, double& y);
    };
}

#endif //CURSOR_HPP
