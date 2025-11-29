//
// Created by kisly on 29.11.2025.
//

#ifndef COLOR_HPP
#define COLOR_HPP

namespace core::color
{
	enum class COLOR : int
	{
		ALICE_BLUE,
		ANTIQUE_WHITE,
		AQUA,
		AQUAMARINE,
		AZURE,
		BEIGE,
		BISQUE,
		BLACK,
		BLANCHED_ALMOND,
		BLUE,
		BLUE_VIOLET,
		BROWN,
		BURLY_WOOD,
		CADET_BLUE,
		CHARTREUSE,
		CHOCOLATE,
		CORAL,
		CORNFLOWER_BLUE,
		CORNSILK,
		CRIMSON,
		CYAN,
		DARK_BLUE,
		DARK_CYAN,
		DARK_GOLDEN_ROD,
		DARK_GREY,
		DARK_GREEN,
		DARK_KHAKI,
		DARK_MAGENTA,
		DARK_OLIVE_GREEN,
		DARK_ORANGE,
		DARK_ORCHID,
		DARK_RED,
		DARK_SALMON,
		DARK_SLATE_BLUE,
		DARK_SLATE_GREY,
		DARK_TURQUOISE,
		DARK_VIOLET,
		DEEP_PINK,
		DEEP_SKY_BLUE,
		DIM_GREY,
		DODGER_BLUE,
		FIRE_BRICK,
		FLORAL_WHITE,
		FOREST_GREEN,
		FUCHSIA,
		GAINSBORO,
		GHOST_WHITE,
		GOLD,
		GOLDEN_ROD,
		GREY,
		GREEN,
		GREEN_YELLOW,
		HONEY_DEW,
		HOT_PINK,
		INDIAN_RED,
		INDIGO,
		IVORY,
		KHAKI,
		LAVENDER,
		LAVENDER_BLUSH,
		LAWN_GREEN,
		LEMON_CHIFFON,
		LIGHT_BLUE,
		LIGHT_CORAL,
		LIGHT_CYAN,
		LIGHT_GOLDEN_ROD_YELLOW,
		LIGHT_GREY,
		LIGHT_GREEN,
		LIGHT_PINK,
		LIGHT_SALMON,
		LIGHT_SEA_GREEN,
		LIGHT_SKY_BLUE,
		LIGHT_SLATE_GREY,
		LIGHT_STEEL_BLUE,
		LIGHT_YELLOW,
		LIME,
		LIME_GREEN,
		LINEN,
		MAGENTA,
		MAROON,
		MEDIUM_AQUA_MARINE,
		MEDIUM_BLUE,
		MEDIUM_ORCHID,
		MEDIUM_PURPLE,
		MEDIUM_SEA_GREEN,
		MEDIUM_SLATE_BLUE,
		MEDIUM_SPRING_GREEN,
		MEDIUM_TURQUOISE,
		MEDIUM_VIOLET_RED,
		MIDNIGHT_BLUE,
		MINT_CREAM,
		MISTY_ROSE,
		MOCCASIN,
		NAVAJO_WHITE,
		NAVY,
		OLD_LACE,
		OLIVE,
		OLIVE_DRAB,
		ORANGE,
		ORANGE_RED,
		ORCHID,
		PALE_GOLDEN_ROD,
		PALE_GREEN,
		PALE_TURQUOISE,
		PALE_VIOLET_RED,
		PAPAYA_WHIP,
		PEACH_PUFF,
		PERU,
		PINK,
		PLUM,
		POWDER_BLUE,
		PURPLE,
		REBECCA_PURPLE,
		RED,
		ROSY_BROWN,
		ROYAL_BLUE,
		SADDLE_BROWN,
		SALMON,
		SANDY_BROWN,
		SEA_GREEN,
		SEA_SHELL,
		SIENNA,
		SILVER,
		SKY_BLUE,
		SLATE_BLUE,
		SLATE_GREY,
		SNOW,
		SPRING_GREEN,
		STEEL_BLUE,
		TAN,
		TEAL,
		THISTLE,
		TOMATO,
		TURQUOISE,
		VIOLET,
		WHEAT,
		WHITE,
		WHITE_SMOKE,
		YELLOW,
		YELLOW_GREEN
	};
	class RGB
	{
	public:
		float red = 0;
		float green = 0;
		float blue = 0;

		RGB() = default;
		RGB(float red, float green, float blue);
		RGB(const COLOR& color);

		void operator=(const COLOR& color);
		void operator=(const RGB& color);

		void normalize();
	};
	class RGBA
	{
	public:
		float red = 0;
		float green = 0;
		float blue = 0;
		float alpha = 1;

		RGBA() = default;
		RGBA(float red, float green, float blue, float alpha = 1);
		RGBA(const RGB& color);
		RGBA(const COLOR& color);

		void operator=(const COLOR& color);
		void operator=(const RGB& color);
		void operator=(const RGBA& color);

		void normalize();
	};

	RGB convert(const COLOR& color);

	RGB normalize(const RGB& color);
	RGBA normalize(const RGBA& color);
	RGB normalize(const COLOR& color);
}

#endif //COLOR_HPP
