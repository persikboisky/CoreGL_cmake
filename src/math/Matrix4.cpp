#include "Matrix4.hpp"
#include "Matrix4.hpp"
#include "Matrix4.hpp"
#include "Matrix4.hpp"
#include "Matrix4.hpp"
#include "Matrix4.hpp"
//
// Created by kisly on 14.07.2025.
//

#include "Vectors.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include <cmath>
#include <array>

namespace core::math
{

	Mat4::Mat4(float diagonal)
	{
		for (unsigned int element = 0; element < 16; element++)
		{
			this->mat[element] = 0;
		}

		this->mat[0] = diagonal;
		this->mat[5] = diagonal;
		this->mat[10] = diagonal;
		this->mat[15] = 1.0f;
	}

	Mat4::Mat4(float mat4[16])
	{
		for (unsigned int element = 0; element < 16; element++)
		{
			this->mat[element] = mat4[element];
		}
	}

	Mat4::Mat4(Quat& quat)
	{
		const float qxx = quat.x * quat.x;
		const float qyy = quat.y * quat.y;
		const float qzz = quat.z * quat.z;
		const float qxz = quat.x * quat.z;
		const float qxy = quat.x * quat.y;
		const float qyz = quat.y * quat.z;
		const float qwx = quat.w * quat.x;
		const float qwy = quat.w * quat.y;
		const float qwz = quat.w * quat.z;

		mat[0] = 1.0f - 2.0f * (qyy +  qzz);
		mat[1] = 2.0f * (qxy - qwz);
		mat[2] = 2.0f * (qxz + qwy);
		mat[3] = 0.0f;

		mat[4] = 2.0f * (qxy + qwz);
		mat[5] = 1.0f - 2.0f * (qxx +  qzz);
		mat[6] = 2.0f * (qyz + qwx);
		mat[7] = 0.0f;

		mat[8] = 2.0f * (qxz - qwy);
		mat[9] = 2.0f * (qyz - qwx);
		mat[10] = 1.0f - 2.0f * (qxx +  qyy);
		mat[11] = 0.0f;

		mat[12] = 0.0f;
		mat[13] = 0.0f;
		mat[14] = 0.0f;
		mat[15] = 1.0f;
	}

	float* Mat4::getArray()
	{
		return *&this->mat;
	}

	std::array<float, 16> Mat4::multiply(float mat1[16], float mat2[16])
	{
		std::array<float, 16> newMat = {
				mat1[0] * mat2[0] + mat1[1] * mat2[4] + mat1[2] * mat2[8] + mat1[3] * mat2[12],
				mat1[0] * mat2[1] + mat1[1] * mat2[5] + mat1[2] * mat2[9] + mat1[3] * mat2[13],
				mat1[0] * mat2[2] + mat1[1] * mat2[6] + mat1[2] * mat2[10] + mat1[3] * mat2[14],
				mat1[0] * mat2[3] + mat1[1] * mat2[7] + mat1[2] * mat2[11] + mat1[3] * mat2[15],

				mat1[4] * mat2[0] + mat1[5] * mat2[4] + mat1[6] * mat2[8] + mat1[7] * mat2[12],
				mat1[4] * mat2[1] + mat1[5] * mat2[5] + mat1[6] * mat2[9] + mat1[7] * mat2[13],
				mat1[4] * mat2[2] + mat1[5] * mat2[6] + mat1[6] * mat2[10] + mat1[7] * mat2[14],
				mat1[4] * mat2[3] + mat1[5] * mat2[7] + mat1[6] * mat2[11] + mat1[7] * mat2[15],

				mat1[8] * mat2[0] + mat1[9] * mat2[4] + mat1[10] * mat2[8] + mat1[11] * mat2[12],
				mat1[8] * mat2[1] + mat1[9] * mat2[5] + mat1[10] * mat2[9] + mat1[11] * mat2[13],
				mat1[8] * mat2[2] + mat1[9] * mat2[6] + mat1[10] * mat2[10] + mat1[11] * mat2[14],
				mat1[8] * mat2[3] + mat1[9] * mat2[7] + mat1[10] * mat2[11] + mat1[11] * mat2[15],

				mat1[12] * mat2[0] + mat1[13] * mat2[4] + mat1[14] * mat2[8] + mat1[15] * mat2[12],
				mat1[12] * mat2[1] + mat1[13] * mat2[5] + mat1[14] * mat2[9] + mat1[15] * mat2[13],
				mat1[12] * mat2[2] + mat1[13] * mat2[6] + mat1[14] * mat2[10] + mat1[15] * mat2[14],
				mat1[12] * mat2[3] + mat1[13] * mat2[7] + mat1[14] * mat2[11] + mat1[15] * mat2[15]
		};

		return newMat;
	}

	Vec4 Mat4::multiply(Vec4 vec, float mat[16])
	{
		return Vec4(
				vec.x * mat[0] + vec.y * mat[1] + vec.z * mat[2] + vec.w * mat[3],
				vec.x * mat[4] + vec.y * mat[5] + vec.z * mat[6] + vec.w * mat[7],
				vec.x * mat[8] + vec.y * mat[9] + vec.z * mat[10] + vec.w * mat[11],
				vec.x * mat[12] + vec.y * mat[13] + vec.z * mat[14] + vec.w * mat[15]
		);
	}

	auto Mat4::operator*(Mat4 mat4) -> Mat4
	{
		return Mat4(Mat4::multiply(this->mat, mat4.getArray()).data());
	}

	auto Mat4::operator*(Vec4 vec4) -> Vec4
	{
		return Mat4::multiply(vec4, this->mat);
	}

	void Mat4::operator*=(Mat4 mat4)
	{
		Mat4 mat = mat4 * Mat4(this->mat);
		for (unsigned int index = 0; index < 16; index++)
		{
			this->mat[index] = mat.getArray()[index];
		}
	}

	void Mat4::operator=(Mat4 mat4)
	{
		for (unsigned int element = 0; element < 16; element++)
		{
			this->mat[element] = mat4.getArray()[element];
		}
	}

	void Mat4::operator=(float mat4[16])
	{
		for (unsigned int element = 0; element < 16; element++)
		{
			this->mat[element] = mat4[element];
		}
	}

	Mat4 Mat4::getScale(const Vec3& vecScale, const Mat4& mat4)
	{
		float ScaleMat[16] = {
				vecScale.x, 0, 0, 0,
				0, vecScale.y, 0, 0,
				0, 0, vecScale.z, 0,
				0, 0, 0, 1
		};

		return Mat4(ScaleMat) * mat4;
	}

	Mat4 Mat4::getTranslate(const Vec3& vecTranslate, const Mat4& mat4)
	{
		float TranslateMat[16] = {
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				vecTranslate.x, vecTranslate.y, vecTranslate.z, 1
		};

		return Mat4(TranslateMat) * mat4;
	}

	Mat4 Mat4::getRotate(float angle, const Vec3& axises, const Mat4& mat4)
	{
		const float s = sin(angle);
		const float c = cos(angle);
		const float t = 1.0f - c;

		const float tx = t * axises.x;
		const float ty = t * axises.y;
		const float tz = t * axises.z;
		const float sx = s * axises.x;
		const float sy = s * axises.y;
		const float sz = s * axises.z;

		float rot[16] = {
				tx * axises.x + c, tx * axises.y - sz, tx * axises.z + sy, 0.0f,
				tx * axises.y + sz, ty * axises.y + c, ty * axises.z - sx, 0.0f,
				tx * axises.z - sy, ty * axises.z + sx, tz * axises.z + c, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
		};

		return Mat4(rot) * mat4;
	}

	Mat4 Mat4::getPerspective(float fovToRadians, float aspect, float near, float far)
	{
		const float TAN = tan(fovToRadians / 2.0f);

		float perspective[16] = {
				1.0f / (aspect * TAN), 0, 0, 0,
				0, 1.0f / TAN, 0, 0,
				0, 0, -((far + near) / (far - near)), -1,
				0, 0, -((2.0f * far * near) / (far - near)), 0
		};

		return Mat4(perspective);
	}

	Mat4 Mat4::getLookAt(Vec3 pos, Vec3 target, Vec3 up)
	{
		Vec3 zaxis = Vec3::normalize(pos - target);
		Vec3 xaxis = Vec3::normalize(Vec3::cross(up, zaxis));
		Vec3 yaxis = Vec3::cross(zaxis, xaxis);

		float lookAT[16] = {
				xaxis.x, yaxis.x, zaxis.x, 0,
				xaxis.y, yaxis.y, zaxis.y, 0,
				xaxis.z, yaxis.z, zaxis.z, 0,
				-Vec3::dot(xaxis, pos),
				-Vec3::dot(yaxis, pos),
				-Vec3::dot(zaxis, pos),
				1
		};

		return Mat4(lookAT);
	}

	Mat4 Mat4::getRotateX(float angle, const Mat4& mat4)
	{
		return getRotate(angle, { 1, 0, 0 }, mat4);
	}

	Mat4 Mat4::getRotateY(float angle, const Mat4& mat4)
	{
		return getRotate(angle, { 0, 1, 0 }, mat4);
	}

	Mat4 Mat4::getRotateZ(float angle, const Mat4& mat4)
	{
		return getRotate(angle, { 0, 0, 1 }, mat4);
	}

	void core::math::Mat4::scale(const Vec3& vecScale)
	{
		*this = Mat4::getScale(vecScale, *this);
	}

	void core::math::Mat4::translate(const Vec3& vecTranslate)
	{
		*this = Mat4::getTranslate(vecTranslate, *this);
	}

	void core::math::Mat4::rotateX(float angle)
	{
		*this = Mat4::getRotateX(angle, *this);
	}

	void core::math::Mat4::rotateY(float angle)
	{
		*this = Mat4::getRotateY(angle, *this);
	}

	void core::math::Mat4::rotateZ(float angle)
	{
		*this = Mat4::getRotateZ(angle, *this);
	}

	void core::math::Mat4::perspective(float fovToRadians, float aspect, float near, float far)
	{
		*this = Mat4::getPerspective(fovToRadians, aspect, near, far) * *this;
	}

	void core::math::Mat4::lookAt(Vec3 pos, Vec3 target, Vec3 up)
	{
		*this = Mat4::getLookAt(pos, target, up) * *this;
	}

	void core::math::Mat4::reset()
	{
		*this = Mat4(1.0);
	}
}
