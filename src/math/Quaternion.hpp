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
		class Quaternion
		{
		public:
			float x;
			float y;
			float z;
			float w;

			explicit Quaternion(const Vector3& axis = {}, float angle = 0);
			explicit Quaternion(const Vector4& vec4);

			Matrix4 getMatrix();

			Quaternion operator* (const Quaternion& quaternion);
			void operator*= (const Quaternion& quaternion);
			float &operator[] (unsigned int index);
		};
	} // math
} // core

#endif //QUATERNION_HPP
