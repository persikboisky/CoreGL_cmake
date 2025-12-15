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
			ZXY,
			ZYX,
			XYZ,
			XZY,
			YXZ,
			YZX,
			ZYZ,
			ZXZ,
			YXY,
			YZY,
			XYX,
			XZX
		};

		class Quat
		{
		private:
			float normSq() const;
			float norm() const;

		public:
			float w;
			float x;
			float y;
			float z;

			Quat(float x = 0, float y = 0, float z = 0, float w = 1);

			void operator=(const Quat &rhs);
			Quat operator+=(const Quat &q);
			Quat operator-=(const Quat &q);
			Quat operator*=(float scale);
			Quat operator*=(const Quat &q);

			Quat operator-() const;
			Quat operator*(const Quat &q) const;
			Quat operator*(float scale) const;
			Quat operator+(const Quat &q2) const;
			Quat operator-(const Quat &q2) const;

			bool operator==(const Quat &v) const;
			bool operator!=(const Quat &v) const;

			float dot(const Quat &q) const;

			Quat normalize();
			static Quat fromEuler(float x, float y, float z, const QUATERNION_EULER_ORDER& topology);
			static Quat fromAxisAngle(float x, float y, float z, float angle);

			void rotateVector(float &vx, float &vy, float &vz) const;
		};
	} // math
} // core

#endif //QUATERNION_HPP
