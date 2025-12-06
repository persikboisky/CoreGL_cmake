//
// Created by kisly on 14.07.2025.
//

#include "Vectors.hpp"
#include "Matrix4.hpp"
#include <cmath>

using namespace core::math;

Vec4::Vec4() : x(0), y(0), z(0), w(1.0f) {}

Vec4::Vec4(const Vec4& vec4) : x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.w) {}

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vec4::Vec4(const Vec3& vec3, float w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

Vec4 Vec4::operator+(const Vec4& vec4)
{
    return Vec4(
            this->x + vec4.x,
            this->y + vec4.y,
            this->z + vec4.z,
            this->w + vec4.w);
}

Vec4 Vec4::operator-(const Vec4& vec4)
{
    return Vec4(
            this->x - vec4.x,
            this->y - vec4.y,
            this->z - vec4.z,
            this->w - vec4.w);
}

Vec4 Vec4::operator*(const Vec4& vec4)
{
    return Vec4(
            this->x * vec4.x,
            this->y * vec4.y,
            this->z * vec4.z,
            this->w * vec4.w);
}

Vec4 Vec4::operator/(const Vec4& vec4)
{
    return Vec4(
            this->x / vec4.x,
            this->y / vec4.y,
            this->z / vec4.z,
            this->w / vec4.w);
}

Vec4 Vec4::operator*(const float& value)
{
    return Vec4(
            this->x * value,
            this->y * value,
            this->z * value,
            this->w * value);
}

Vec4 Vec4::operator/(const float& value)
{
    return Vec4(
            this->x / value,
            this->y / value,
            this->z / value,
            this->w / value);
}

void Vec4::operator+=(const Vec4& vec4)
{
    this->x += vec4.x;
    this->y += vec4.y;
    this->z += vec4.z;
    this->w += vec4.w;
}

void Vec4::operator-=(const Vec4& vec4)
{
    this->x -= vec4.x;
    this->y -= vec4.y;
    this->z -= vec4.z;
    this->w -= vec4.w;
}

void Vec4::operator*=(const Vec4& vec4)
{
    this->x *= vec4.x;
    this->y *= vec4.y;
    this->z *= vec4.z;
    this->w *= vec4.w;
}

void Vec4::operator/=(const Vec4& vec4)
{
    this->x /= vec4.x;
    this->y /= vec4.y;
    this->z /= vec4.z;
    this->w /= vec4.w;
}

bool Vec4::operator==(const Vec4& vec4)
{
    return this->length() == vec4.length();
}

bool Vec4::operator>(const Vec4& vec4)
{
    return this->length() > vec4.length();
}

bool Vec4::operator<(const Vec4& vec4)
{
    return this->length() < vec4.length();
}

bool Vec4::operator>=(const Vec4& vec4)
{
    return this->length() >= vec4.length();
}

bool Vec4::operator<=(const Vec4& vec4)
{
    return this->length() <= vec4.length();
}

void Vec4::operator=(const Vec4& vec4)
{
    this->x = vec4.x;
    this->y = vec4.y;
    this->z = vec4.z;
    this->w = vec4.w;
}

Vec4 Vec4::normalize(const Vec4& vec4)
{
    const float LENGTH = Vec4::length(vec4);
    return Vec4(
            vec4.x / LENGTH,
            vec4.y / LENGTH,
            vec4.z / LENGTH,
            vec4.w / LENGTH);
}

float Vec4::length(const Vec4& vec4)
{
    return sqrtf(
            powf(vec4.x, 2) +
            powf(vec4.y, 2) +
            powf(vec4.z, 2) +
            powf(vec4.w, 2));
}

float Vec4::dot(const Vec4& vec4_1, const Vec4& vec4_2)
{
    return vec4_1.x * vec4_2.x + vec4_1.y * vec4_2.y +
           vec4_1.z * vec4_2.z + vec4_1.w * vec4_2.w;
}

float Vec4::distance(const Vec4& vec4_1, const Vec4& vec4_2)
{
    return sqrtf(
            powf(vec4_1.x - vec4_2.x, 2) +
            powf(vec4_1.y - vec4_2.y, 2) +
            powf(vec4_1.z - vec4_2.z, 2) +
            powf(vec4_1.w - vec4_2.w, 2));
}

Vec4 Vec4::normalize()
{
    const float LENGTH = this->length();
    return Vec4(
            this->x / LENGTH,
            this->y / LENGTH,
            this->z / LENGTH,
            this->w / LENGTH);
}

void Vec4::normal()
{
    const float LENGTH = this->length();
    this->x /= LENGTH;
    this->y /= LENGTH;
    this->z /= LENGTH;
    this->w /= LENGTH;
}

float Vec4::length() const
{
    return sqrtf(
            powf(this->x, 2) +
            powf(this->y, 2) +
            powf(this->z, 2) +
            powf(this->w, 2));
}

float Vec4::dot(const Vec4& vec4) const
{
    return this->x * vec4.x + this->y * vec4.y +
           this->z * vec4.z + this->w * vec4.w;
}

float Vec4::distance(const Vec4& vec4) const
{
    return sqrt(
            powf(this->x - vec4.x, 2) +
            powf(this->y - vec4.y, 2) +
            powf(this->z - vec4.z, 2) +
            powf(this->w - vec4.w, 2));
}

auto Vec4::operator*(Mat4 mat4) -> Vec4
{
    return Mat4::multiply(Vec4(this->x, this->y, this->z, this->w), mat4.getArray());
}