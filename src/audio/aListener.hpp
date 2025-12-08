//
// Created by kisly on 08.12.2025.
//

#ifndef ALISTENER_HPP
#define ALISTENER_HPP

namespace core
{
	struct Pos3f;
	namespace math
	{
		struct Vec3;
	}

	namespace audio::listener
	{
		void setPos(float x, float y, float z);
		void setPos(const Pos3f& pos);
		void setPos(const math::Vec3& pos);

		void setVel(float x, float y, float z);
		void setVel(const Pos3f& pos);

		void setOrientation(
				float tX, float tY, float tZ,
				float upX, float upY, float upZ);
		void setOrientation(const math::Vec3& target, const math::Vec3& up);

	} // audio::listener
}// core

#endif //ALISTENER_HPP
