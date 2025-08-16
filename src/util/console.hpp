//
// Created by kisly on 13.07.2025.
//

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

namespace core
{
    struct pos2i;

    namespace math
    {
        class Matrix4;
    }

    namespace color
    {
        struct RGB;
    }

    namespace console
    {
        void printTime();
        void clear();

        void setPosCursor(int x, int y);
        void setPosCursor(const pos2i& pos);

        void print(math::Matrix4& matrix);
        void print(color::RGB color);

        void getPosCursor(int &x, int &y);
        pos2i getPosCursor();

        void printProgressBar(unsigned int length, unsigned int percent);
    };
}


#endif //CONSOLE_HPP
