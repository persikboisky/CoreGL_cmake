#ifndef SIZE_INL
#define SIZE_INL

#include "size.hpp"

namespace core
{
	inline Size2i::Size2i(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	inline Size3i::Size3i(int width, int height, int depth)
	{
		this->width = width;
		this->height = height;
		this->depth = depth;
	}

	inline Size2ui::Size2ui(unsigned int width, unsigned int height)
	{
		this->width = width;
		this->height = height;
	}

	inline Size3ui::Size3ui(unsigned int width, unsigned int height, unsigned int depth)
	{
		this->width = width;
		this->height = height;
		this->depth = depth;
	}

	inline Size2f::Size2f(float width, float height)
	{
		this->width = width;
		this->height = height;
	}

	inline Size3f::Size3f(float width, float height, float depth)
	{
		this->width = width;
		this->height = height;
		this->depth = depth;
	}
}

#endif //SIZE_INL
