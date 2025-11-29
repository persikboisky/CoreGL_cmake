//
// Created by kisly on 29.11.2025.
//

#include "color.hpp"

namespace core::color
{
	RGB::RGB(const COLOR& color) : red(0), green(0), blue(0)
	{
		*this = convert(color);
	}

	RGB::RGB(float red, float green, float blue)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	void RGB::operator=(const COLOR& color)
	{
		*this = convert(color);
	}

	void RGB::operator=(const RGB& color)
	{
		*this = color;
	}

	void RGB::normalize()
	{
		this->red /= 255.0f;
		this->green /= 255.0f;
		this->blue /= 255.0f;
	}

	RGBA::RGBA(float red, float green, float blue, float alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	RGBA::RGBA(const RGB& color)
	{
		this->red = color.red;
		this->green = color.green;
		this->blue = color.blue;
	}

	RGBA::RGBA(const COLOR& color)
	{
		RGB c = convert(color);
		this->red = c.red;
		this->green = c.green;
		this->blue = c.blue;
	}

	void RGBA::operator=(const COLOR& color)
	{
		RGB c = convert(color);
		this->red = c.red;
		this->green = c.green;
		this->blue = c.blue;
	}

	void RGBA::operator=(const RGB& color)
	{
		this->red = color.red;
		this->green = color.green;
		this->blue = color.blue;
	}

	void RGBA::operator=(const RGBA& color)
	{
		this->red = color.red;
		this->green = color.green;
		this->blue = color.blue;
		this->alpha = color.alpha;
	}

	void RGBA::normalize()
	{
		this->red /= 255.0f;
		this->green /= 255.0f;
		this->blue /= 255.0f;
		this->alpha /= 255.0f;
	}

	RGB convert(const COLOR& color)
	{
		switch (color)
		{
		case color::COLOR::ALICE_BLUE:
			return color::RGB(240, 248, 255);
		case color::COLOR::ANTIQUE_WHITE:
			return color::RGB(250, 235, 215);
		case color::COLOR::AQUA:
			return color::RGB(0, 255, 255);
		case color::COLOR::AQUAMARINE:
			return color::RGB(127, 255, 212);
		case color::COLOR::AZURE:
			return color::RGB(240, 255, 255);
		case color::COLOR::BEIGE:
			return color::RGB(245, 245, 220);
		case color::COLOR::BISQUE:
			return color::RGB(255, 228, 196);
		case color::COLOR::BLACK:
			return color::RGB(0, 0, 0);
		case color::COLOR::BLANCHED_ALMOND:
			return color::RGB(255, 235, 205);
		case color::COLOR::BLUE:
			return color::RGB(0, 0, 255);
		case color::COLOR::BLUE_VIOLET:
			return color::RGB(138, 43, 226);
		case color::COLOR::BROWN:
			return color::RGB(165, 42, 42);
		case color::COLOR::BURLY_WOOD:
			return color::RGB(222, 184, 135);
		case color::COLOR::CADET_BLUE:
			return color::RGB(95, 158, 160);
		case color::COLOR::CHARTREUSE:
			return color::RGB(127, 255, 0);
		case color::COLOR::CHOCOLATE:
			return color::RGB(210, 105, 30);
		case color::COLOR::CORAL:
			return color::RGB(255, 127, 80);
		case color::COLOR::CORNFLOWER_BLUE:
			return color::RGB(100, 149, 237);
		case color::COLOR::CORNSILK:
			return color::RGB(255, 248, 220);
		case color::COLOR::CRIMSON:
			return color::RGB(220, 20, 60);
		case color::COLOR::CYAN:
			return color::RGB(0, 255, 255);
		case color::COLOR::DARK_BLUE:
			return color::RGB(0, 0, 139);
		case color::COLOR::DARK_CYAN:
			return color::RGB(0, 139, 139);
		case color::COLOR::DARK_GOLDEN_ROD:
			return color::RGB(184, 134, 11);
		case color::COLOR::DARK_GREY:
			return color::RGB(169, 169, 169);
		case color::COLOR::DARK_GREEN:
			return color::RGB(0, 100, 0);
		case color::COLOR::DARK_KHAKI:
			return color::RGB(189, 183, 107);
		case color::COLOR::DARK_MAGENTA:
			return color::RGB(139, 0, 139);
		case color::COLOR::DARK_OLIVE_GREEN:
			return color::RGB(85, 107, 47);
		case color::COLOR::DARK_ORANGE:
			return color::RGB(255, 140, 0);
		case color::COLOR::DARK_ORCHID:
			return color::RGB(153, 50, 204);
		case color::COLOR::DARK_RED:
			return color::RGB(139, 0, 0);
		case color::COLOR::DARK_SALMON:
			return color::RGB(143, 188, 143);
		case color::COLOR::DARK_SLATE_BLUE:
			return color::RGB(72, 61, 139);
		case color::COLOR::DARK_SLATE_GREY:
			return color::RGB(47, 79, 79);
		case color::COLOR::DARK_TURQUOISE:
			return color::RGB(0, 206, 209);
		case color::COLOR::DARK_VIOLET:
			return color::RGB(148, 0, 211);
		case color::COLOR::DEEP_PINK:
			return color::RGB(255, 20, 147);
		case color::COLOR::DEEP_SKY_BLUE:
			return color::RGB(0, 191, 255);
		case color::COLOR::DIM_GREY:
			return color::RGB(105, 105, 105);
		case color::COLOR::DODGER_BLUE:
			return color::RGB(30, 144, 255);
		case color::COLOR::FIRE_BRICK:
			return color::RGB(178, 34, 34);
		case color::COLOR::FLORAL_WHITE:
			return color::RGB(255, 250, 240);
		case color::COLOR::FOREST_GREEN:
			return color::RGB(34, 139, 34);
		case color::COLOR::FUCHSIA:
			return color::RGB(255, 0, 255);
		case color::COLOR::GAINSBORO:
			return color::RGB(220, 220, 220);
		case color::COLOR::GHOST_WHITE:
			return color::RGB(248, 248, 255);
		case color::COLOR::GOLD:
			return color::RGB(255, 215, 0);
		case color::COLOR::GOLDEN_ROD:
			return color::RGB(218, 165, 32);
		case color::COLOR::GREY:
			return color::RGB(128, 128, 128);
		case color::COLOR::GREEN:
			return color::RGB(0, 128, 0);
		case color::COLOR::GREEN_YELLOW:
			return color::RGB(173, 255, 47);
		case color::COLOR::HONEY_DEW:
			return color::RGB(240, 255, 240);
		case color::COLOR::HOT_PINK:
			return color::RGB(255, 105, 180);
		case color::COLOR::INDIAN_RED:
			return color::RGB(205, 92, 92);
		case color::COLOR::INDIGO:
			return color::RGB(75, 0, 130);
		case color::COLOR::IVORY:
			return color::RGB(255, 255, 240);
		case color::COLOR::KHAKI:
			return color::RGB(240, 230, 140);
		case color::COLOR::LAVENDER:
			return color::RGB(230, 230, 250);
		case color::COLOR::LAVENDER_BLUSH:
			return color::RGB(255, 240, 245);
		case color::COLOR::LAWN_GREEN:
			return color::RGB(124, 252, 0);
		case color::COLOR::LEMON_CHIFFON:
			return color::RGB(255, 250, 205);
		case color::COLOR::LIGHT_BLUE:
			return color::RGB(173, 216, 230);
		case color::COLOR::LIGHT_CORAL:
			return color::RGB(240, 128, 128);
		case color::COLOR::LIGHT_CYAN:
			return color::RGB(224, 255, 255);
		case color::COLOR::LIGHT_GOLDEN_ROD_YELLOW:
			return color::RGB(250, 250, 210);
		case color::COLOR::LIGHT_GREY:
			return color::RGB(211, 211, 211);
		case color::COLOR::LIGHT_GREEN:
			return color::RGB(144, 238, 144);
		case color::COLOR::LIGHT_PINK:
			return color::RGB(255, 182, 193);
		case color::COLOR::LIGHT_SALMON:
			return color::RGB(255, 160, 122);
		case color::COLOR::LIGHT_SEA_GREEN:
			return color::RGB(32, 178, 170);
		case color::COLOR::LIGHT_SKY_BLUE:
			return color::RGB(135, 206, 250);
		case color::COLOR::LIGHT_SLATE_GREY:
			return color::RGB(119, 136, 153);
		case color::COLOR::LIGHT_STEEL_BLUE:
			return color::RGB(176, 196, 222);
		case color::COLOR::LIGHT_YELLOW:
			return color::RGB(255, 255, 224);
		case color::COLOR::LIME:
			return color::RGB(0, 255, 0);
		case color::COLOR::LIME_GREEN:
			return color::RGB(50, 205, 50);
		case color::COLOR::LINEN:
			return color::RGB(250, 240, 230);
		case color::COLOR::MAGENTA:
			return color::RGB(255, 0, 255);
		case color::COLOR::MAROON:
			return color::RGB(128, 0, 0);
		case color::COLOR::MEDIUM_AQUA_MARINE:
			return color::RGB(102, 205, 170);
		case color::COLOR::MEDIUM_BLUE:
			return color::RGB(0, 0, 205);
		case color::COLOR::MEDIUM_ORCHID:
			return color::RGB(186, 85, 211);
		case color::COLOR::MEDIUM_PURPLE:
			return color::RGB(147, 112, 219);
		case color::COLOR::MEDIUM_SEA_GREEN:
			return color::RGB(60, 179, 113);
		case color::COLOR::MEDIUM_SLATE_BLUE:
			return color::RGB(123, 104, 238);
		case color::COLOR::MEDIUM_SPRING_GREEN:
			return color::RGB(0, 250, 154);
		case color::COLOR::MEDIUM_TURQUOISE:
			return color::RGB(72, 209, 204);
		case color::COLOR::MEDIUM_VIOLET_RED:
			return color::RGB(199, 21, 133);
		case color::COLOR::MIDNIGHT_BLUE:
			return color::RGB(25, 25, 112);
		case color::COLOR::MINT_CREAM:
			return color::RGB(245, 255, 250);
		case color::COLOR::MISTY_ROSE:
			return color::RGB(255, 228, 225);
		case color::COLOR::MOCCASIN:
			return color::RGB(255, 228, 181);
		case color::COLOR::NAVAJO_WHITE:
			return color::RGB(255, 222, 173);
		case color::COLOR::NAVY:
			return color::RGB(0, 0, 128);
		case color::COLOR::OLD_LACE:
			return color::RGB(253, 245, 230);
		case color::COLOR::OLIVE:
			return color::RGB(128, 128, 0);
		case color::COLOR::OLIVE_DRAB:
			return color::RGB(107, 142, 35);
		case color::COLOR::ORANGE:
			return color::RGB(255, 165, 0);
		case color::COLOR::ORANGE_RED:
			return color::RGB(255, 69, 0);
		case color::COLOR::ORCHID:
			return color::RGB(218, 112, 214);
		case color::COLOR::PALE_GOLDEN_ROD:
			return color::RGB(238, 232, 170);
		case color::COLOR::PALE_GREEN:
			return color::RGB(152, 251, 152);
		case color::COLOR::PALE_TURQUOISE:
			return color::RGB(175, 238, 238);
		case color::COLOR::PALE_VIOLET_RED:
			return color::RGB(219, 112, 147);
		case color::COLOR::PAPAYA_WHIP:
			return color::RGB(255, 239, 213);
		case color::COLOR::PEACH_PUFF:
			return color::RGB(255, 218, 185);
		case color::COLOR::PERU:
			return color::RGB(205, 133, 63);
		case color::COLOR::PINK:
			return color::RGB(255, 192, 203);
		case color::COLOR::PLUM:
			return color::RGB(221, 160, 221);
		case color::COLOR::POWDER_BLUE:
			return color::RGB(176, 224, 230);
		case color::COLOR::PURPLE:
			return color::RGB(128, 0, 128);
		case color::COLOR::REBECCA_PURPLE:
			return color::RGB(102, 51, 153);
		case color::COLOR::RED:
			return color::RGB(255, 0, 0);
		case color::COLOR::ROSY_BROWN:
			return color::RGB(188, 143, 143);
		case color::COLOR::ROYAL_BLUE:
			return color::RGB(65, 105, 225);
		case color::COLOR::SADDLE_BROWN:
			return color::RGB(139, 69, 19);
		case color::COLOR::SALMON:
			return color::RGB(250, 128, 114);
		case color::COLOR::SANDY_BROWN:
			return color::RGB(244, 164, 96);
		case color::COLOR::SEA_GREEN:
			return color::RGB(46, 139, 87);
		case color::COLOR::SEA_SHELL:
			return color::RGB(255, 245, 238);
		case color::COLOR::SIENNA:
			return color::RGB(160, 82, 45);
		case color::COLOR::SILVER:
			return color::RGB(192, 192, 192);
		case color::COLOR::SKY_BLUE:
			return color::RGB(135, 206, 235);
		case color::COLOR::SLATE_BLUE:
			return color::RGB(106, 90, 205);
		case color::COLOR::SLATE_GREY:
			return color::RGB(112, 128, 144);
		case color::COLOR::SNOW:
			return color::RGB(255, 250, 250);
		case color::COLOR::SPRING_GREEN:
			return color::RGB(0, 255, 127);
		case color::COLOR::STEEL_BLUE:
			return color::RGB(70, 130, 180);
		case color::COLOR::TAN:
			return color::RGB(210, 180, 140);
		case color::COLOR::TEAL:
			return color::RGB(0, 128, 128);
		case color::COLOR::THISTLE:
			return color::RGB(216, 191, 216);
		case color::COLOR::TOMATO:
			return color::RGB(255, 99, 71);
		case color::COLOR::TURQUOISE:
			return color::RGB(64, 224, 208);
		case color::COLOR::VIOLET:
			return color::RGB(238, 130, 238);
		case color::COLOR::WHEAT:
			return color::RGB(245, 222, 179);
		case color::COLOR::WHITE:
			return color::RGB(255, 255, 255);
		case color::COLOR::WHITE_SMOKE:
			return color::RGB(245, 245, 245);
		case color::COLOR::YELLOW:
			return color::RGB(255, 255, 0);
		case color::COLOR::YELLOW_GREEN:
			return color::RGB(154, 205, 50);
		default:
			return color::RGB(0, 0, 0);
		}
	}

	RGB normalize(const RGB& color)
	{
		RGB c = color;
		return {
			c.red / 255.0f,
			c.green / 255.0f,
			c.blue / 255.0f
		};
	}

	RGBA normalize(const RGBA& color)
	{
		RGBA c = color;
		return {
				c.red / 255.0f,
				c.green / 255.0f,
				c.blue / 255.0f,
				c.alpha / 255.0f
		};
	}

	RGB normalize(const COLOR& color)
	{
		return normalize(color::convert(color));
	}
}