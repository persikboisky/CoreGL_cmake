//
// Created by kisly on 13.07.2025.
//

#include "console.hpp"
#include "types.hpp"
#include "../math/Matrix4.hpp"
#include <windows.h>
#include <string>
#include <iostream>
#include <fcntl.h>

void core::console::init()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
}

void core::console::printTime()
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    std::cout << '[';
    std::cout << st.wHour << ':';
    std::cout << st.wMinute << ':';
    std::cout << st.wSecond << "] -> ";
}

void core::console::clear()
{
    system("cls");
}

void core::console::setPosCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void core::console::setPosCursor(const core::pos2i &pos)
{
    core::console::setPosCursor(pos.x, pos.y);
}

static void drawlineForTable(int len, int nNode, int nAir)
{
    for (int x = 0; x < nNode + nAir * len; x++)
    {
        if(x % (len + 1) == 0)
        {
            std::cout << u_char(206);
            continue;
        }
        std::cout << u_char(205);
    }
    std::cout << std::endl;
}

void core::console::print(core::math::Matrix4 &matrix)
{
    drawlineForTable(9, 6, 5);

    const int elementForSymbol = 9;
    float* arr = matrix.getArray();

    std::string c[5] = {
            "         ",
            "    x    ",
            "    y    ",
            "    z    ",
            "    w    "

    };
    for (int x = 0; x < 5; x++)
    {
        std::cout << u_char(186) << c[x];
    }
    std::cout << u_char(186) << std::endl;

    for (int y = 0; y < 4; y++)
    {
        drawlineForTable(9, 6, 5);

        for (int x = 0; x < 5; x++)
        {
            if(x == 0)
            {
                std::cout << u_char(186) << c[y + 1];
                continue;
            }
            std::string element = std::to_string(arr[(x - 1) + 4 * y]);
            for (unsigned int iter = element.size(); iter != elementForSymbol; iter++)
            {
                element += " ";
            }
            std::cout << u_char(186) << element;
        }
        std::cout << u_char(186) << std::endl;
    }
    drawlineForTable(9, 6, 5);
    std::cout << std::endl;
}
