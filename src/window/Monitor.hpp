//
// Created by kisly on 14.07.2025.
//

#ifndef MONITOR_HPP
#define MONITOR_HPP

struct GLFWmonitor;
struct GLFWvidmode;

namespace core
{
    struct Size2i;
    namespace color
    {
        struct RGB;
    }

    class Monitor
    {
    private:
        GLFWmonitor* monitor;
        const GLFWvidmode* vidMode;

    public:
        Monitor();
        ~Monitor();

        [[nodiscard]] Size2i getPhysicalSize();
        [[nodiscard]] Size2i getSize();
        [[nodiscard]] color::RGB getBITS();

        [[nodiscard]] GLFWmonitor* getGLFWObj();
    };
}

#endif //MONITOR_HPP
