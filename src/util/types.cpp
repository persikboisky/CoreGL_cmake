//
// Created by kisly on 13.07.2025.
//

#include "types.hpp"
#include <GLFW/glfw3.h>
#include <string>

using namespace core;

#if defined(CORE_INCLUDE_VULKAN)
VkFormat vulkan::convertFormat(const FORMAT_VARIABLE& format)
{
	switch (format)
	{
	case vulkan::FLOAT:
		return VK_FORMAT_R32_SFLOAT;
	case vulkan::INT:
		return VK_FORMAT_R32_SINT;
	case vulkan::UINT:
		return VK_FORMAT_R32_UINT;
	case vulkan::VEC2:
		return VK_FORMAT_R32G32_SFLOAT;
	case vulkan::VEC3:
		return VK_FORMAT_R32G32B32_SFLOAT;
	case vulkan::VEC4:
		return VK_FORMAT_R32G32B32A32_SFLOAT;
	default:
		return VK_FORMAT_R32_SFLOAT;
	}
}
#endif //defined(CORE_INCLUDE_VULKAN)

int core::convertKeyCode(const KEY_CODE& keyCode)
{
    switch (keyCode)
    {
        case core::K_F1:
            return GLFW_KEY_F1;
        case core::K_F2:
            return GLFW_KEY_F2;
        case core::K_F3:
            return GLFW_KEY_F3;
        case core::K_F4:
            return GLFW_KEY_F4;
        case core::K_F5:
            return GLFW_KEY_F5;
        case core::K_F6:
            return GLFW_KEY_F6;
        case core::K_F7:
            return GLFW_KEY_F7;
        case core::K_F8:
            return GLFW_KEY_F8;
        case core::K_F9:
            return GLFW_KEY_F9;
        case core::K_F10:
            return GLFW_KEY_F10;
        case core::K_F11:
            return GLFW_KEY_F11;
        case core::K_F12:
            return GLFW_KEY_F12;
        case core::K_PRINT_SCREEN:
            return GLFW_KEY_PRINT_SCREEN;
        case core::K_SCROLL_LOCK:
            return GLFW_KEY_SCROLL_LOCK;
        case core::K_PAUSE:
            return GLFW_KEY_PAUSE;
        case core::K_1:
            return GLFW_KEY_1;
        case core::K_2:
            return GLFW_KEY_2;
        case core::K_3:
            return GLFW_KEY_3;
        case core::K_4:
            return GLFW_KEY_4;
        case core::K_5:
            return GLFW_KEY_5;
        case core::K_6:
            return GLFW_KEY_6;
        case core::K_7:
            return GLFW_KEY_7;
        case core::K_8:
            return GLFW_KEY_8;
        case core::K_9:
            return GLFW_KEY_9;
        case core::K_0:
            return GLFW_KEY_0;
        case core::K_Q:
            return GLFW_KEY_Q;
        case core::K_W:
            return GLFW_KEY_W;
        case core::K_E:
            return GLFW_KEY_E;
        case core::K_R:
            return GLFW_KEY_R;
        case core::K_T:
            return GLFW_KEY_T;
        case core::K_Y:
            return GLFW_KEY_Y;
        case core::K_U:
            return GLFW_KEY_U;
        case core::K_I:
            return GLFW_KEY_I;
        case core::K_O:
            return GLFW_KEY_O;
        case core::K_P:
            return GLFW_KEY_P;
        case core::K_A:
            return GLFW_KEY_A;
        case core::K_S:
            return GLFW_KEY_S;
        case core::K_D:
            return GLFW_KEY_D;
        case core::K_F:
            return GLFW_KEY_F;
        case core::K_G:
            return GLFW_KEY_G;
        case core::K_H:
            return GLFW_KEY_H;
        case core::K_J:
            return GLFW_KEY_H;
        case core::K_K:
            return GLFW_KEY_K;
        case core::K_L:
            return GLFW_KEY_L;
        case core::K_Z:
            return GLFW_KEY_Z;
        case core::K_X:
            return GLFW_KEY_X;
        case core::K_C:
            return GLFW_KEY_C;
        case core::K_V:
            return GLFW_KEY_V;
        case core::K_B:
            return GLFW_KEY_B;
        case core::K_N:
            return GLFW_KEY_N;
        case core::K_M:
            return GLFW_KEY_M;
        case core::K_SPACE:
            return GLFW_KEY_SPACE;
        case core::K_ESCAPE:
            return GLFW_KEY_ESCAPE;
        case core::K_LEFT_SHIFT:
            return GLFW_KEY_LEFT_SHIFT;
        case core::K_LEFT_CONTROL:
            return GLFW_KEY_LEFT_CONTROL;
        default:
            return 0;
    }
}

int core::convertPrimitive(const PRIMITIVE& primitive)
{
    switch (primitive)
    {
        case POINTS:
            return GL_POINTS;

        case TRIANGLES:
            return GL_TRIANGLES;

        case LINES:
            return GL_LINES;

        case LINE_STRIP:
            return GL_LINE_STRIP;

        case LINE_LOOP:
            return GL_LINE_LOOP;

        case TRIANGLES_FAN:
            return GL_TRIANGLE_FAN;

        case TRIANGLES_STRIP:
            return GL_TRIANGLE_STRIP;

        default:
            return 0;
    }
}

core::color::RGB::RGB(const core::color::COLOR &color)
{
    RGB c = color::convertColor(color);
    this->red = c.red;
    this->green = c.green;
    this->blue = c.blue;
}

core::color::RGB::RGB(float red, float green, float blue) :
    red(red), green(green), blue(blue)
{}

void core::color::RGB::operator=(const core::color::COLOR &color)
{
    RGB c = color::convertColor(color);
    this->red = c.red;
    this->green = c.green;
    this->blue = c.blue;
}

void core::color::RGB::operator=(const core::color::RGB &color)
{
    this->red = color.red;
    this->green = color.green;
    this->blue = color.blue;
}

constexpr char keySymbol[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
core::color::RGB core::color::stringToRGB(std::string str)
{
    color::RGB col = {};
    int colorChannel = 0;
    std::string colorChannelsValueToStr = "";

    for (unsigned int index = 0; index < str.size(); index++)
    {
        bool flag = false;
        for (unsigned int indexKeySymbol = 0; indexKeySymbol < 11; indexKeySymbol++)
        {
            if (str[index] != keySymbol[indexKeySymbol])
            {
                flag = false;
            }
            else
            {
                flag = true;
                colorChannelsValueToStr += str[index];
                break;
            }
        }

        if (flag == false || index == str.size() - 1)
        {
            if (colorChannelsValueToStr != "")
            {
                if (colorChannel == 0) col.red = float(std::stod(colorChannelsValueToStr));
                else if (colorChannel == 1) col.blue = float(std::stod(colorChannelsValueToStr));
                else if (colorChannel == 2) col.green = float(std::stod(colorChannelsValueToStr));

                colorChannelsValueToStr = "";
                colorChannel += 1;
            }
        }
    }

    return col;
}

void core::color::RGB::normalize()
{
    this->red /= 255.0f;
    this->green /= 255.0f;
    this->blue /= 255.0f;
}

core::color::RGBA::RGBA(const core::color::COLOR &color)
{
    RGB c = color::convertColor(color);
    this->red = c.red;
    this->green = c.green;
    this->blue = c.blue;
    this->alpha = 255;
}

core::color::RGBA::RGBA(const core::color::RGB &color) :
        red(color.red), green(color.green), blue(color.blue), alpha(255)
{}

core::color::RGBA::RGBA(float red, float green, float blue, float alpha) :
        red(red), green(green), blue(blue), alpha(alpha)
{}

void core::color::RGBA::operator=(const core::color::RGB &color)
{
    this->red = color.red;
    this->green = color.green;
    this->blue = color.blue;
    this->alpha = 255;
}

void core::color::RGBA::operator=(const core::color::RGBA &color)
{
    this->red = color.red;
    this->green = color.green;
    this->blue = color.blue;
    this->alpha = color.alpha;
}

void core::color::RGBA::operator=(const core::color::COLOR &color)
{
    RGB c = color::convertColor(color);
    this->red = c.red;
    this->green = c.green;
    this->blue = c.blue;
    this->alpha = 255;
}

void core::color::RGBA::normalize()
{
    this->red /= 255.0f;
    this->green /= 255.0f;
    this->blue /= 255.0f;
    this->alpha /= 255.0f;
}

core::color::RGB core::color::convertColor(const core::color::COLOR &color)
{
    switch (color)
    {
        case color::ALICE_BLUE:
            return color::RGB(240, 248, 255);
        case color::ANTIQUE_WHITE:
            return color::RGB(250, 235, 215);
        case color::AQUA:
            return color::RGB(0, 255, 255);
        case color::AQUAMARINE:
            return color::RGB(127, 255, 212);
        case color::AZURE:
            return color::RGB(240, 255, 255);
        case color::BEIGE:
            return color::RGB(245, 245, 220);
        case color::BISQUE:
            return color::RGB(255, 228, 196);
        case color::BLACK:
            return color::RGB(0, 0, 0);
        case color::BLANCHED_ALMOND:
            return color::RGB(255, 235, 205);
        case color::BLUE:
            return color::RGB(0, 0, 255);
        case color::BLUE_VIOLET:
            return color::RGB(138, 43, 226);
        case color::BROWN:
            return color::RGB(165, 42, 42);
        case color::BURTLY_WOOD:
            return color::RGB(222, 184, 135);
        case color::CADET_BLUE:
            return color::RGB(95, 158, 160);
        case color::CHARTREUSE:
            return color::RGB(127, 255, 0);
        case color::CHOCOLATE:
            return color::RGB(210, 105, 30);
        case color::CORAL:
            return color::RGB(255, 127, 80);
        case color::CORNFLOWER_BLUE:
            return color::RGB(100, 149, 237);
        case color::CORNSILK:
            return color::RGB(255, 248, 220);
        case color::CRIMSON:
            return color::RGB(220, 20, 60);
        case color::CYAN:
            return color::RGB(0, 255, 255);
        case color::DARK_BLUE:
            return color::RGB(0, 0, 139);
        case color::DARK_CYAN:
            return color::RGB(0, 139, 139);
        case color::DARK_GOLDEN_ROD:
            return color::RGB(184, 134, 11);
        case color::DARK_GREY:
            return color::RGB(169, 169, 169);
        case color::DARK_GREEN:
            return color::RGB(0, 100, 0);
        case color::DARK_KHAKI:
            return color::RGB(189, 183, 107);
        case color::DARK_MAGENTA:
            return color::RGB(139, 0, 139);
        case color::DARK_OLIVE_GREEN:
            return color::RGB(85, 107, 47);
        case color::DARK_ORANGE:
            return color::RGB(255, 140, 0);
        case color::DARK_ORCHID:
            return color::RGB(153, 50, 204);
        case color::DARK_RED:
            return color::RGB(139, 0, 0);
        case color::DARK_SALMON:
            return color::RGB(143, 188, 143);
        case color::DARK_SLATE_BLUE:
            return color::RGB(72, 61, 139);
        case color::DARK_SLATE_GREY:
            return color::RGB(47, 79, 79);
        case color::DARK_TURQUOISE:
            return color::RGB(0, 206, 209);
        case color::DARK_VIOLET:
            return color::RGB(148, 0, 211);
        case color::DEEP_PINK:
            return color::RGB(255, 20, 147);
        case color::DEEP_SKY_BLUE:
            return color::RGB(0, 191, 255);
        case color::DIM_GREY:
            return color::RGB(105, 105, 105);
        case color::DODGER_BLUE:
            return color::RGB(30, 144, 255);
        case color::FIRE_BRICK:
            return color::RGB(178, 34, 34);
        case color::FLORAL_WHITE:
            return color::RGB(255, 250, 240);
        case color::FOREST_GREEN:
            return color::RGB(34, 139, 34);
        case color::FUCHSIA:
            return color::RGB(255, 0, 255);
        case color::GAINSBORO:
            return color::RGB(220, 220, 220);
        case color::GHOST_WHITE:
            return color::RGB(248, 248, 255);
        case color::GOLD:
            return color::RGB(255, 215, 0);
        case color::GOLDEN_ROD:
            return color::RGB(218, 165, 32);
        case color::GREY:
            return color::RGB(128, 128, 128);
        case color::GREEN:
            return color::RGB(0, 128, 0);
        case color::GREEN_YELLOW:
            return color::RGB(173, 255, 47);
        case color::HONEY_DEW:
            return color::RGB(240, 255, 240);
        case color::HOT_PINK:
            return color::RGB(255, 105, 180);
        case color::INDIAN_RED:
            return color::RGB(205, 92, 92);
        case color::INDIGO:
            return color::RGB(75, 0, 130);
        case color::IVORY:
            return color::RGB(255, 255, 240);
        case color::KHAKI:
            return color::RGB(240, 230, 140);
        case color::LAVENDER:
            return color::RGB(230, 230, 250);
        case color::LAVENDER_BLUSH:
            return color::RGB(255, 240, 245);
        case color::LAWN_GREEN:
            return color::RGB(124, 252, 0);
        case color::LEMON_CHIFFON:
            return color::RGB(255, 250, 205);
        case color::LIGHT_BLUE:
            return color::RGB(173, 216, 230);
        case color::LIGHT_CORAL:
            return color::RGB(240, 128, 128);
        case color::LIGHT_CYAN:
            return color::RGB(224, 255, 255);
        case color::LIGHT_GOLDEN_ROD_YELLOW:
            return color::RGB(250, 250, 210);
        case color::LIGHT_GREY:
            return color::RGB(211, 211, 211);
        case color::LIGHT_GREEN:
            return color::RGB(144, 238, 144);
        case color::LIGHT_PINK:
            return color::RGB(255, 182, 193);
        case color::LIGHT_SALMON:
            return color::RGB(255, 160, 122);
        case color::LIGHT_SEA_GREEN:
            return color::RGB(32, 178, 170);
        case color::LIGHT_SKY_BLUE:
            return color::RGB(135, 206, 250);
        case color::LIGHT_SLATE_GREY:
            return color::RGB(119, 136, 153);
        case color::LIGHT_STEEL_BLUE:
            return color::RGB(176, 196, 222);
        case color::LIGHT_YELLOW:
            return color::RGB(255, 255, 224);
        case color::LIME:
            return color::RGB(0, 255, 0);
        case color::LIME_GREEN:
            return color::RGB(50, 205, 50);
        case color::LINEN:
            return color::RGB(250, 240, 230);
        case color::MAGENTA:
            return color::RGB(255, 0, 255);
        case color::MAROON:
            return color::RGB(128, 0, 0);
        case color::MEDIUM_AQUA_MARINE:
            return color::RGB(102, 205, 170);
        case color::MEDIUM_BLUE:
            return color::RGB(0, 0, 205);
        case color::MEDIUM_ORCHID:
            return color::RGB(186, 85, 211);
        case color::MEDIUM_PURPLE:
            return color::RGB(147, 112, 219);
        case color::MEDIUM_SEA_GREEN:
            return color::RGB(60, 179, 113);
        case color::MEDIUM_SLATE_BLUE:
            return color::RGB(123, 104, 238);
        case color::MEDIUM_SPRING_GREEN:
            return color::RGB(0, 250, 154);
        case color::MEDIUM_TURQUOISE:
            return color::RGB(72, 209, 204);
        case color::MEDIUM_VIOLET_RED:
            return color::RGB(199, 21, 133);
        case color::MIDNIGHT_BLUE:
            return color::RGB(25, 25, 112);
        case color::MINT_CREAM:
            return color::RGB(245, 255, 250);
        case color::MISTY_ROSE:
            return color::RGB(255, 228, 225);
        case color::MOCCASIN:
            return color::RGB(255, 228, 181);
        case color::NAVAJO_WHITE:
            return color::RGB(255, 222, 173);
        case color::NAVY:
            return color::RGB(0, 0, 128);
        case color::OLD_LACE:
            return color::RGB(253, 245, 230);
        case color::OLIVE:
            return color::RGB(128, 128, 0);
        case color::OLIVE_DRAB:
            return color::RGB(107, 142, 35);
        case color::ORANGE:
            return color::RGB(255, 165, 0);
        case color::ORANGE_RED:
            return color::RGB(255, 69, 0);
        case color::ORCHID:
            return color::RGB(218, 112, 214);
        case color::PALE_GOLDEN_ROD:
            return color::RGB(238, 232, 170);
        case color::PALE_GREEN:
            return color::RGB(152, 251, 152);
        case color::PALE_TURQUOISE:
            return color::RGB(175, 238, 238);
        case color::PALE_VIOLET_RED:
            return color::RGB(219, 112, 147);
        case color::PAPAYA_WHIP:
            return color::RGB(255, 239, 213);
        case color::PEACH_PUFF:
            return color::RGB(255, 218, 185);
        case color::PERU:
            return color::RGB(205, 133, 63);
        case color::PINK:
            return color::RGB(255, 192, 203);
        case color::PLUM:
            return color::RGB(221, 160, 221);
        case color::POWDER_BLUE:
            return color::RGB(176, 224, 230);
        case color::PURPLE:
            return color::RGB(128, 0, 128);
        case color::REBECCA_PURPLE:
            return color::RGB(102, 51, 153);
        case color::RED:
            return color::RGB(255, 0, 0);
        case color::ROSY_BROWN:
            return color::RGB(188, 143, 143);
        case color::ROYAL_BLUE:
            return color::RGB(65, 105, 225);
        case color::SADDLE_BROWN:
            return color::RGB(139, 69, 19);
        case color::SALMON:
            return color::RGB(250, 128, 114);
        case color::SANDY_BROWN:
            return color::RGB(244, 164, 96);
        case color::SEA_GREEN:
            return color::RGB(46, 139, 87);
        case color::SEA_SHELL:
            return color::RGB(255, 245, 238);
        case color::SIENNA:
            return color::RGB(160, 82, 45);
        case color::SILVER:
            return color::RGB(192, 192, 192);
        case color::SKY_BLUE:
            return color::RGB(135, 206, 235);
        case color::SLATE_BLUE:
            return color::RGB(106, 90, 205);
        case color::SLATE_GREY:
            return color::RGB(112, 128, 144);
        case color::SNOW:
            return color::RGB(255, 250, 250);
        case color::SPRING_GREEN:
            return color::RGB(0, 255, 127);
        case color::STEEL_BLUE:
            return color::RGB(70, 130, 180);
        case color::TAN:
            return color::RGB(210, 180, 140);
        case color::TEAL:
            return color::RGB(0, 128, 128);
        case color::THISTLE:
            return color::RGB(216, 191, 216);
        case color::TOMATO:
            return color::RGB(255, 99, 71);
        case color::TURQUOISE:
            return color::RGB(64, 224, 208);
        case color::VIOLET:
            return color::RGB(238, 130, 238);
        case color::WHEAT:
            return color::RGB(245, 222, 179);
        case color::WHITE:
            return color::RGB(255, 255, 255);
        case color::WHITE_SMOKE:
            return color::RGB(245, 245, 245);
        case color::YELLOW:
            return color::RGB(255, 255, 0);
        case color::YELLOW_GREEN:
            return color::RGB(154, 205, 50);
        default:
            return color::RGB(0, 0, 0);
    }
}

color::RGBA color::normalize(const color::RGBA& color)
{
	return color::RGBA(
		color.red / 255.0f,
		color.green / 255.0f,
		color.blue / 255.0f,
		color.alpha / 255.0f
		);
}

color::RGB color::normalize(const color::RGB& color)
{
	return color::RGB(
		color.red / 255.0f,
		color.green / 255.0f,
		color.blue / 255.0f
	);
}

color::RGB color::normalize(const color::COLOR& color)
{
	return color::normalize(color::convertColor(color));
}

void core::pos2f::operator=(const pos2f& pos)
{
    this->x = pos.x;
    this->y = pos.y;
}

void core::pos2i::operator=(const pos2i& pos)
{
    this->x = pos.x;
    this->y = pos.y;
}

void core::pos3f::operator=(const pos3f& pos)
{
    this->x = pos.x;
    this->y = pos.y;
    this->z = pos.z;
}

void core::size2f::operator=(const size2f& size)
{
    this->width = size.width;
    this->height = size.height;
}

void core::size2i::operator=(const size2i& size)
{
    this->width = size.width;
    this->height = size.height;
}

void core::size3f::operator=(const size3f& size)
{
    this->width = size.width;
    this->height = size.height;
    this->length = size.length;
}

void version2::operator=(const version2 &v2)
{
    this->MAJOR = v2.MAJOR;
    this->MINOR = v2.MINOR;
}

void version3::operator=(const version3 &v3)
{
    this->MAJOR = v3.MAJOR;
    this->MINOR = v3.MINOR;
    this->PATCH = v3.PATCH;
}

DepthSize::DepthSize(float depth, float stencil) : depth(depth), stencil(stencil)
{
}

void DepthSize::operator=(const DepthSize& ds)
{
	this->depth = ds.depth;
	this->stencil = ds.stencil;
}
