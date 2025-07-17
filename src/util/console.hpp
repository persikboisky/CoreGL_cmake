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

    namespace console
    {
        void init();

        void printTime();
        void clear();

        void setPosCursor(int x, int y);
        void setPosCursor(const pos2i& pos);

        void print(math::Matrix4& matrix);
    };
}


#endif //CONSOLE_HPP
