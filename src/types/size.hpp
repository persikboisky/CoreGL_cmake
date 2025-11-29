//
// Created by kisly on 28.11.2025.
//

#ifndef SIZE_HPP
#define SIZE_HPP

namespace core
{
	class Size2i
	{
	public:
		int width = 0;
		int height = 0;

		Size2i() = default;
		inline Size2i(int width, int height);
	};

	struct Size3i
	{
		int width = 0;
		int height = 0;
		int depth = 0;

		Size3i() = default;
		inline Size3i(int width, int height, int depth);
	};

	struct Size2ui
	{
		unsigned int width = 0;
		unsigned int height = 0;

		Size2ui() = default;
		inline Size2ui(unsigned int width, unsigned int height);
	};

	struct Size3ui
	{
		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;

		Size3ui() = default;
		inline Size3ui(unsigned int width, unsigned int height, unsigned int depth);
	};

	struct Size2f
	{
		float width = 0;
		float height = 0;

		Size2f() = default;
		inline Size2f(float width, float height);
	};

	struct Size3f
	{
		float width = 0;
		float height = 0;
		float depth = 0;

		Size3f() = default;
		inline Size3f(float width, float height, float depth);
	};
} // core

#include "size.inl"
#endif //SIZE_HPP
