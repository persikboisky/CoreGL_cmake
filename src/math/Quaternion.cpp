//
// Created by kisly on 15.10.2025.
//

#include "Quaternion.hpp"
#include <cmath>
#include <glm/ext.hpp>

namespace core
{
	namespace math
	{
		Quaternion::Quaternion(const Vector3& axis, float angle)
		{
			float result = static_cast<float>(sin(angle / 2.0f));
			this->w = static_cast<float>(cos(angle / 2.0f));
			this->x = static_cast<float>(axis.x * result);
			this->y = static_cast<float>(axis.y * result);
			this->z = static_cast<float>(axis.z * result);
		}

		Quaternion::Quaternion(const Vector4& vec4) :
			x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.z)
		{}

		Matrix4 Quaternion::getMatrix()
		{
			float mat4[16] = {};
//			mat4[0] = 1.0f - 2.0f * ( this->y * this->y + this->z * this->z );
//			mat4[1] = 2.0f * (this->x * this->y + this->z * this->w);
//			mat4[2] = 2.0f * (this->x * this->z - this->y * this->w);
//			mat4[3] = 0.0f;
//
//			mat4[4] = 2.0f * ( this->x * this->y - this->z * this->w );
//			mat4[5] = 1.0f - 2.0f * ( this->x * this->x + this->z * this->z );
//			mat4[6] = 2.0f * (this->z * this->y + this->x * this->w );
//			mat4[7] = 0.0f;
//
//			mat4[8] = 2.0f * ( this->x * this->z + this->y * this->w );
//			mat4[9] = 2.0f * ( this->y * this->z - this->x * this->w );
//			mat4[10] = 1.0f - 2.0f * ( this->x * this->x + this->y * this->y );
//			mat4[11] = 0.0f;

			mat4[0] = static_cast<float>(1.0 - 2.0 * pow((*this)[2], 2) - 2.0f * pow((*this)[3], 2));
			mat4[1] = static_cast<float>(2.0 * (*this)[1] * (*this)[2] + 2.0 * (*this)[0] * (*this)[3]);
			mat4[2] = static_cast<float>(2.0 * (*this)[1] * (*this)[3] - 2.0 * (*this)[0] * (*this)[2]);
			mat4[3] = 0;

			mat4[4] = static_cast<float>(2.0 * (*this)[1] * (*this)[2] - 2.0 * (*this)[0] * (*this)[3]);
			mat4[5] = static_cast<float>(1.0 - 2.0 * pow((*this)[1], 2) - 2.0f * pow((*this)[3], 2));
			mat4[6] =  static_cast<float>(2.0 * (*this)[2] * (*this)[3] + 2.0 * (*this)[0] * (*this)[1]);
			mat4[7] = 0;

			mat4[8] = static_cast<float>(2.0 * (*this)[1] * (*this)[3] + 2.0 * (*this)[0] * (*this)[2]);
			mat4[9] = static_cast<float>(2.0 * (*this)[2] * (*this)[3] - 2.0 * (*this)[0] * (*this)[1]);
			mat4[10] = static_cast<float>(1.0 - 2.0 * pow((*this)[1], 2) - 2.0f * pow((*this)[2], 2));
			mat4[11] = 0;

			mat4[12] = 0;
			mat4[13] = 0;
			mat4[14] = 0;
			mat4[15] = 1;

			return Matrix4(mat4);
		}

		Quaternion Quaternion::operator*(const Quaternion& quaternion)
		{
			Vector4 r = {};

			r.w = quaternion.w*this->w - quaternion.x*this->x - quaternion.y*this->y - quaternion.z*this->z;
			r.x = quaternion.w*this->x + quaternion.x*this->w + quaternion.y*this->z - quaternion.z*this->y;
			r.y = quaternion.w*this->y + quaternion.y*this->w + quaternion.z*this->x - quaternion.x*this->z;
			r.z = quaternion.w*this->z + quaternion.z*this->w + quaternion.x*this->y - quaternion.y*this->x;

			return Quaternion(r);
		}

		void Quaternion::operator*=(const Quaternion& quaternion)
		{
			this->w = quaternion.w*this->w - quaternion.x*this->x - quaternion.y*this->y - quaternion.z*this->z;
			this->x = quaternion.w*this->x + quaternion.x*this->w + quaternion.y*this->z - quaternion.z*this->y;
			this->y = quaternion.w*this->y + quaternion.y*this->w + quaternion.z*this->x - quaternion.x*this->z;
			this->z = quaternion.w*this->z + quaternion.z*this->w + quaternion.x*this->y - quaternion.y*this->x;
		}

		float &Quaternion::operator[](unsigned int index)
		{
			switch (index)
			{
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			default:
				return this->w;
			}
		}
	} // math
} // core