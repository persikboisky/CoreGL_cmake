//
// Created by kisly on 14.07.2025.
//

#include "Vectors.hpp"
#include "Matrix4.hpp"
#include <cmath>
#include <array>

using namespace core;
using namespace core::math;

Matrix4::Matrix4(float diagonal)
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

Matrix4::Matrix4(float mat4[16])
{
    for (unsigned int element = 0; element < 16; element++)
    {
        this->mat[element] = mat4[element];
    }
}

float* Matrix4::getArray()
{
    return *&this->mat;
}

std::array<float, 16> Matrix4::multiply(float mat1[16], float mat2[16])
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

Vector4 Matrix4::multiply(Vector4 vec, float mat[16])
{
    return Vector4(
            vec.x * mat[0] + vec.y * mat[1] + vec.z * mat[2] + vec.w * mat[3],
            vec.x * mat[4] + vec.y * mat[5] + vec.z * mat[6] + vec.w * mat[7],
            vec.x * mat[8] + vec.y * mat[9] + vec.z * mat[10] + vec.w * mat[11],
            vec.x * mat[12] + vec.y * mat[13] + vec.z * mat[14] + vec.w * mat[15]
    );
}

auto Matrix4::operator*(Matrix4 mat4) -> Matrix4
{
    return Matrix4(Matrix4::multiply(this->mat, mat4.getArray()).data());
}

auto Matrix4::operator*(Vector4 vec4) -> Vector4
{
    return Matrix4::multiply(vec4, this->mat);
}

void Matrix4::operator*=(Matrix4 mat4)
{
    Matrix4 mat = mat4 * Matrix4(this->mat);
    for (unsigned int index = 0; index < 16; index++)
    {
        this->mat[index] = mat.getArray()[index];
    }
}

void Matrix4::operator=(Matrix4 mat4)
{
    for (unsigned int element = 0; element < 16; element++)
    {
        this->mat[element] = mat4.getArray()[element];
    }
}

void Matrix4::operator=(float mat4[16])
{
    for (unsigned int element = 0; element < 16; element++)
    {
        this->mat[element] = mat4[element];
    }
}

Matrix4 Matrix4::getScale(const Vector3& vecScale, const Matrix4& mat4)
{
    float ScaleMat[16] = {
            vecScale.x, 0, 0, 0,
            0, vecScale.y, 0, 0,
            0, 0, vecScale.z, 0,
            0, 0, 0, 1
    };

    return Matrix4(ScaleMat) * mat4;
}

Matrix4 Matrix4::getTranslate(const Vector3& vecTranslate, const Matrix4& mat4)
{
    float TranslateMat[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            vecTranslate.x, vecTranslate.y, vecTranslate.z, 1
    };

    return Matrix4(TranslateMat) * mat4;
}

Matrix4 Matrix4::getRotate(float angle, const Vector3& axises, const Matrix4& mat4)
{
    float s = sin(angle);
    float c = cos(angle);
    float t = 1.0f - c;

    float tx = t * axises.x;
    float ty = t * axises.y;
    float tz = t * axises.z;
    float sx = s * axises.x;
    float sy = s * axises.y;
    float sz = s * axises.z;

    float rot[16] = {
            tx * axises.x + c, tx * axises.y - sz, tx * axises.z + sy, 0.0f,
            tx * axises.y + sz, ty * axises.y + c, ty * axises.z - sx, 0.0f,
            tx * axises.z - sy, ty * axises.z + sx, tz * axises.z + c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    return Matrix4(rot) * mat4;
}

Matrix4 Matrix4::getPerspective(float fovToRadians, float aspect, float near, float far)
{
    const float TAN = tan(fovToRadians / 2.0f);

    float perspective[16] = {
            1.0f / (aspect * TAN), 0, 0, 0,
            0, 1.0f / TAN, 0, 0,
            0, 0, -((far + near) / (far - near)), -1,
            0, 0, -((2.0f * far * near) / (far - near)), 0
    };

    return Matrix4(perspective);
}

Matrix4 Matrix4::getLookAt(Vector3 pos, Vector3 target, Vector3 up)
{
    Vector3 zaxis = Vector3::normalize(pos - target);
    Vector3 xaxis = Vector3::normalize(Vector3::cross(up, zaxis));
    Vector3 yaxis = Vector3::cross(zaxis, xaxis);

    float lookAT[16] = {
            xaxis.x, yaxis.x, zaxis.x, 0,
            xaxis.y, yaxis.y, zaxis.y, 0,
            xaxis.z, yaxis.z, zaxis.z, 0,
            -Vector3::dot(xaxis, pos),
            -Vector3::dot(yaxis, pos),
            -Vector3::dot(zaxis, pos),
            1
    };

    return Matrix4(lookAT);
}