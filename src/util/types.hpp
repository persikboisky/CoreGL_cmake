//
// Created by kisly on 13.07.2025.
//

#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include "../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#endif //defined(CORE_INCLUDE_VULKAN)

namespace core
{
    enum KEY_CODE : int 
    {
        K_F1,
        K_F2,
        K_F3,
        K_F4,
        K_F5,
        K_F6,
        K_F7,
        K_F8,
        K_F9,
        K_F10,
        K_F11,
        K_F12,
        K_PRINT_SCREEN,
        K_SCROLL_LOCK,
        K_PAUSE,
        K_1,
        K_2,
        K_3,
        K_4,
        K_5,
        K_6,
        K_7,
        K_8,
        K_9,
        K_0,
        K_Q,
        K_W,
        K_E,
        K_R,
        K_T,
        K_Y,
        K_U,
        K_I,
        K_O,
        K_P,
        K_A,
        K_S,
        K_D,
        K_F,
        K_G,
        K_H,
        K_J,
        K_K,
        K_L,
        K_Z,
        K_X,
        K_C,
        K_V,
        K_B,
        K_N,
        K_M,
        K_SPACE,
        K_ESCAPE,
        K_LEFT_SHIFT,
        K_LEFT_CONTROL
    };
    enum POSITION : int
    {
        CENTER,
        UP_CENTER_SIDE,
        DOWN_CENTER_SIDE,
        LEFT_UP_CORNER,
        LEFT_CENTER_SIDE,
        LEFT_DOWN_CORNER,
        RIGHT_UP_CORNER,
        RIGHT_CENTER_SIDE,
        RIGHT_DOWN_CORNER
    };
    enum CAM_MODE : int
    {
        CAM_DYNAMIC,

        CAM_STATIC,

        CAM_PLAYER
    };
    enum PRIMITIVE : int
    {
        POINTS,
        LINES,
        LINE_STRIP,
        LINE_LOOP,
        TRIANGLES,
        TRIANGLES_FAN,
        TRIANGLES_STRIP
    };

#if defined(CORE_INCLUDE_VULKAN)
	namespace vulkan
	{
		enum PRIMITIVE : int
		{
			POINT_LIST,
			LINE_LIST,
			LINE_STRIP,
			TRIANGLE_LIST,
			TRIANGLE_STRIP,
			TRIANGLE_FAN
		};
		enum SHADER_STAGES : int
		{
			VERTEX_STAGE,
			FRAGMENT_STAGE,
			GEOMETRY_STAGE,
			VERTEX_FRAGMENT_STAGES,
			VERTEX_GEOMETRY_FRAGMENT_STAGES
		};
		enum FORMAT_VARIABLE : int
		{
			FLOAT,
			VEC2,
			VEC3,
			VEC4,
			UINT,
			INT
		};

		VkFormat convertFormat(const FORMAT_VARIABLE& format);
	}
#endif //defined(CORE_INCLUDE_VULKAN)

    enum TYPE_SHADER : int
    {
        FRAGMENT,
        GEOMETRY,
        VERTEX
    };
    enum TYPE_CULL_FACE : int 
    {
        CULL_BACK,
        CULL_FRONT,
        CULL_FRONT_AND_BACK,
        CULL_NONE
    };
    enum FRONT_FACE : int
    {
		FRONT_FACE_COUNTER_CLOCKWISE,
		FRONT_FACE_CLOCKWISE
    };
    enum TYPE_WRAPPING_TEXTURE : int
    {
        TEXTURE_REPEAT,
        TEXTURE_MIRRORED_REPEAT,
        TEXTURE_CLAMP_TP_EDGE,
        TEXTURE_CLAMP_TO_BORDER
    };
    enum POLYGON_MODE : int 
    {
        POLYGON_POINT,
        POLYGON_LINE,
        POLYGON_FILL
    };
    enum POLYGONS : int
    {
        POLYGON_FRONT,
        POLYGON_BACK,
        POLYGON_FRONT_AND_BACK
    };
    enum TYPES_COORD : int
    {
        POSITIVE_RELATIVE_COORD,
        RELATIVE_COORD,
        POSITIVE_WINDOW_COORD,
        WINDOW_COORD
    };
	enum BUFFER : int
	{
		COLOR_BUFFER = 1,
		DEPTH_BUFFER = 2,
		NONE = 0
	};
	enum VALUE_TYPE : int
	{
		INT,
		UNSIGNED_INT,
		FLOAT,
		DOUBLE
	};

    int convertKeyCode(const KEY_CODE& keyCode);
    int convertPrimitive(const PRIMITIVE& primitive);

    namespace color
    {
        enum COLOR : int
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
            BURTLY_WOOD,
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

        struct RGB
        {
            float red;
            float green;
            float blue;

            RGB(const COLOR& color);
            RGB(float red = 0, float green = 0, float blue = 0);

            void operator=(const COLOR& color);
            void operator=(const RGB &color);

            void normalize();
        };

        RGB stringToRGB(std::string str);

        struct RGBA
        {
            float red;
            float green;
            float blue;
            float alpha;

            RGBA(const COLOR& color);
            RGBA(const RGB& color);
            RGBA(float red = 0, float green = 0, float blue = 0, float alpha = 255);

            void operator=(const RGB& color);
            void operator=(const RGBA &color);
            void operator=(const COLOR &color);

            void normalize();
        };

        RGB convertColor(const COLOR& color);

		RGBA normalize(const RGBA& color);
		RGB normalize(const RGB& color);
		RGB normalize(const COLOR& color);
    }

    struct pos2f final
    {
        float x = 0;
        float y = 0;

        pos2f() {}
        pos2f(float x, float y) : x(x), y(y) {}

        void operator = (const pos2f& pos);
    };

    struct pos2i final
    {
        int x = 0;
        int y = 0;

        pos2i() {}
        pos2i(int x, int y) : x(x), y(y) {}

        void operator = (const pos2i& pos);
    };

    struct pos3f final
    {
        float x = 0;
        float y = 0;
        float z = 0;

        pos3f() {}
        pos3f(float x, float y, float z) : x(x), y(y), z(z) {}

        void operator = (const pos3f& pos);
    };

    struct size2f final
    {
        float width = 0;
        float height = 0;

        size2f() {}
        size2f(float width, float height) : width(width), height(height)
        {
        }

        void operator = (const size2f& size);
    };

    struct size2i final
    {
        int width = 0;
        int height = 0;

        size2i() {}
        size2i(int width, int height) : width(width), height(height)
        {
        }

        void operator = (const size2i& size);
    };

    struct size3f final
    {
        float width = 0;
        float height = 0;
        float length = 0;

        size3f() {}
        size3f(float width, float height, float length) :
                width(width), height(height), length(length)
        {
        }

        void operator = (const size3f& size);
    };

    struct version2
    {
        int MAJOR;
        int MINOR;

        version2(int MAJOR, int MINOR) : MINOR(MINOR), MAJOR(MAJOR) {}
        void operator = (const version2& v2);
    };

    struct version3
    {
        int MAJOR;
        int MINOR;
        int PATCH;

        version3(int MAJOR, int MINOR, int PATCH) : MINOR(MINOR), MAJOR(MAJOR), PATCH(PATCH) {}
        void operator = (const version3& v3);
    };

	struct DepthSize
	{
		float depth;
		float stencil;

		DepthSize(float depth = 1.0, float stencil = 0.0);
		void operator = (const DepthSize& ds);
	};
}

#endif //TYPES_HPP
