//
// Created by kisly on 14.07.2025.
//

#include "Vectors.hpp"
#include <cmath>

using namespace core::math;

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::Vec3(const Vec4& vec4) : x(vec4.x), y(vec4.y), z(vec4.z) {}

Vec3 Vec3::operator+(const Vec3& vec3)
{
    return Vec3(
            this->x + vec3.x,
            this->y + vec3.y,
            this->z + vec3.z
    );
}

Vec3 Vec3::operator-(const Vec3& vec3)
{
    return Vec3(
            this->x - vec3.x,
            this->y - vec3.y,
            this->z - vec3.z
    );
}

Vec3 Vec3::operator*(const Vec3& vec3)
{
    return Vec3(
            this->x * vec3.x,
            this->y * vec3.y,
            this->z * vec3.z
    );
}

Vec3 Vec3::operator/(const Vec3& vec3)
{
    return Vec3(
            this->x / vec3.x,
            this->y / vec3.y,
            this->z / vec3.z);
}

Vec3 Vec3::operator*(const float& value)
{
    return Vec3(
            this->x * value,
            this->y * value,
            this->z * value);
}

Vec3 Vec3::operator/(const float& value)
{
    return Vec3(
            this->x / value,
            this->y / value,
            this->z / value);
}

void Vec3::operator+=(const Vec3& vec3)
{
    this->x += vec3.x;
    this->y += vec3.y;
    this->z += vec3.z;
}

void Vec3::operator-=(const Vec3& vec3)
{
    this->x -= vec3.x;
    this->y -= vec3.y;
    this->z -= vec3.z;
}

void Vec3::operator*=(const Vec3& vec3)
{
    this->x *= vec3.x;
    this->y *= vec3.y;
    this->z *= vec3.z;
}

void Vec3::operator/=(const Vec3& vec3)
{
    this->x /= vec3.x;
    this->y /= vec3.y;
    this->z /= vec3.z;
}

bool Vec3::operator==(const Vec3& vec3)
{
    return this->length() == vec3.length();
}

bool Vec3::operator>(const Vec3& vec3)
{
    return this->length() > vec3.length();
}

bool Vec3::operator<(const Vec3& vec3)
{
    return this->length() < vec3.length();
}

bool Vec3::operator>=(const Vec3& vec3)
{
    return this->length() >= vec3.length();
}

bool Vec3::operator<=(const Vec3& vec3)
{
    return this->length() <= vec3.length();
}

void Vec3::operator=(const Vec3& vec3)
{
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
}

Vec3 Vec3::normalize(const Vec3& vec3)
{
    const float length = Vec3::length(vec3);
    return Vec3(
            vec3.x / length,
            vec3.y / length,
            vec3.z / length);
}

Vec3 Vec3::cross(const Vec3& vec3_1, const Vec3& vec3_2)
{
    return Vec3(
            vec3_1.y * vec3_2.z - vec3_2.y * vec3_1.z,
            vec3_1.z * vec3_2.x - vec3_2.z * vec3_1.x,
            vec3_1.x * vec3_2.y - vec3_2.x * vec3_1.y);
}

float Vec3::length(const Vec3& vec3)
{
    return sqrtf(powf(vec3.x, 2) + powf(vec3.y, 2) + powf(vec3.z, 2));
}

float Vec3::dot(const Vec3& vec3_1, const Vec3& vec3_2)
{
    return vec3_1.x * vec3_2.x + vec3_1.y * vec3_2.y + vec3_1.z * vec3_2.z;
}

float Vec3::distance(const Vec3& vec3_1, const Vec3& vec3_2)
{
    return sqrtf(
            powf(vec3_1.x - vec3_2.x, 2) +
            powf(vec3_1.y - vec3_2.y, 2) +
            powf(vec3_1.z - vec3_2.z, 2));
}

Vec3 Vec3::normalize()
{
    const float LENGTH = this->length();
    return Vec3(
            this->x / LENGTH,
            this->y / LENGTH,
            this->z / LENGTH);
}

void Vec3::normal()
{
    const float LENGTH = this->length();
    this->x /= LENGTH;
    this->y /= LENGTH;
    this->z /= LENGTH;
}

float Vec3::length() const
{
    return sqrtf(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
}

float Vec3::dot(const Vec3& vec3) const
{
    return this->x * vec3.x + this->y * vec3.y + this->z * vec3.z;
}

float Vec3::distance(const Vec3& vec3) const
{
    return sqrtf(
            powf(this->x - vec3.x, 2) +
            powf(this->y - vec3.y, 2) +
            powf(this->z - vec3.z, 2));
}