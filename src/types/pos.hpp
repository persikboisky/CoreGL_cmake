//
// Created by kisly on 29.11.2025.
//

#ifndef POS_HPP
#define POS_HPP

namespace core
{
	struct Pos2i
	{
		int x = 0;
		int y = 0;
	};

	struct Pos3i
	{
		int x = 0;
		int y = 0;
		int z = 0;
	};

	struct Pos4i
	{
		int x = 0;
		int y = 0;
		int z = 0;
		int w = 0;
	};

	struct Pos2f
	{
		float x = 0;
		float y = 0;
	};

	struct Pos3f
	{
		float x = 0;
		float y = 0;
		float z = 0;
	};

	struct Pos4f
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};

	enum class POSITION : int
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
}

#endif //POS_HPP
