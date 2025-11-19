//
// Created by kisly on 15.10.2025.
//

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vectors.hpp"
#include "Matrix4.hpp"

namespace core
{
	namespace math
	{
		enum class QUATERNION_EULER_ORDER : int
		{
			QUATERNION_EULER_ZXY,
			QUATERNION_EULER_ZYX,
			QUATERNION_EULER_XYZ,
			QUATERNION_EULER_XZY,
			QUATERNION_EULER_YXZ,
			QUATERNION_EULER_YZX,
			QUATERNION_EULER_ZYZ,
			QUATERNION_EULER_ZXZ,
			QUATERNION_EULER_YXY,
			QUATERNION_EULER_YZY,
			QUATERNION_EULER_XYX,
			QUATERNION_EULER_XZX
		};

		class Quaternion
		{
		public:
			float w;
			float x;
			float y;
			float z;

			Quaternion(float w, float x, float y, float z);

			Quaternion &operator=(const Quaternion &rhs);
			Quaternion &operator+=(const Quaternion &q);
			Quaternion &operator-=(const Quaternion &q);
			Quaternion &operator*=(float scale);
			Quaternion &operator*=(const Quaternion &q);

			Quaternion operator-() const;
			Quaternion operator*(const Quaternion &q) const;
			Quaternion operator*(float scale) const;
			Quaternion operator+(const Quaternion &q2) const;
			Quaternion operator-(const Quaternion &q2) const;

			bool operator==(const Quaternion &v) const;
			bool operator!=(const Quaternion &v) const;

			float dot(const Quaternion &q) const;
			float normSq() const;
			float norm() const;

			Quaternion &normalize();
			static Quaternion fromEuler(float x, float y, float z, const QUATERNION_EULER_ORDER& topology);
			static Quaternion fromAxisAngle(float x, float y, float z, float angle);

			void rotateVector(float &vx, float &vy, float &vz) const;
		};
	} // math
} // core

#endif //QUATERNION_HPP
