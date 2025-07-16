//
// Created by kisly on 14.07.2025.
//

#ifndef MONITOR_HPP
#define MONITOR_HPP

struct GLFWmonitor;
struct GLFWvidmode;

namespace core
{
    struct size2i;
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

        [[nodiscard]] size2i getPhysicalSize();
        [[nodiscard]] size2i getSize();
        [[nodiscard]]  color::RGB getBITS();

        [[nodiscard]] GLFWmonitor* getGLFWObj();
    };
}

#endif //MONITOR_HPP
