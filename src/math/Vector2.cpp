//
// Created by kisly on 14.07.2025.
//

#include "Vectors.hpp"
#include <cmath>

using namespace core::math;

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}
Vec2::Vec2(const Vec2& vec2) : x(vec2.x), y(vec2.y) {}

Vec2 Vec2::operator+(const Vec2& vec2)
{
    return Vec2(
            this->x + vec2.x,
            this->y + vec2.y);
}

Vec2 Vec2::operator-(const Vec2& vec2)
{
    return Vec2(
            this->x - vec2.x,
            this->y - vec2.y);
}

Vec2 Vec2::operator*(const Vec2& vec2)
{
    return Vec2(
            this->x * vec2.x,
            this->y * vec2.y);
}

Vec2 Vec2::operator/(const Vec2& vec2)
{
    return Vec2(
            this->x / vec2.x,
            this->y / vec2.y);
}

Vec2 Vec2::operator*(const float& value)
{
    return Vec2(
            this->x * value,
            this->y * value);
}

Vec2 Vec2::operator/(const float& value)
{
    return Vec2(
            this->x / value,
            this->y / value);
}

void Vec2::operator+=(const Vec2& vec2)
{
    this->x += vec2.x;
    this->y += vec2.y;
}

void Vec2::operator-=(const Vec2& vec2)
{
    this->x -= vec2.x;
    this->y -= vec2.y;
}

void Vec2::operator*=(const Vec2& vec2)
{
    this->x *= vec2.x;
    this->y *= vec2.y;
}

void Vec2::operator/=(const Vec2& vec2)
{
    this->x /= vec2.x;
    this->y /= vec2.y;
}

bool Vec2::operator==(const Vec2& vec2)
{
    return this->length() == vec2.length();
}

bool Vec2::operator>(const Vec2& vec2)
{
    return (this->length() > vec2.length());
}

bool Vec2::operator<(const Vec2& vec2)
{
    return (this->length() < vec2.length());
}

bool Vec2::operator>=(const Vec2& vec2)
{
    return (this->length() >= vec2.length());
}

bool Vec2::operator<=(const Vec2& vec2)
{
    return (this->length() <= vec2.length());
}

void Vec2::operator=(const Vec2& vec2)
{
    this->x = vec2.x;
    this->y = vec2.y;
}

Vec2 Vec2::normalize(const Vec2& vec2)
{
    const float LENGTH = Vec2::length(vec2);
    return Vec2(
            vec2.x / LENGTH,
            vec2.y / LENGTH);
}

float Vec2::length(const Vec2& vec2)
{
    return sqrtf(powf(vec2.x, 2) + powf(vec2.y, 2));
}

float Vec2::dot(const Vec2& vec2_1, const Vec2& vec2_2)
{
    return vec2_1.x * vec2_2.x + vec2_1.y * vec2_2.y;
}

float Vec2::distance(const Vec2& vec2_1, const Vec2& vec2_2)
{
    return sqrtf(powf(vec2_1.x - vec2_2.x, 2) + powf(vec2_1.y - vec2_2.y, 2));
}

Vec2 Vec2::normalize()
{
    const float LENGTH = this->length();
    return Vec2(
            this->x / LENGTH,
            this->y / LENGTH);
}

void Vec2::normal()
{
    const float LENGTH = this->length();
    this->x /= LENGTH;
    this->y /= LENGTH;
}

float Vec2::length() const
{
    return sqrtf(powf(this->x, 2) + powf(this->y, 2));
}

float Vec2::dot(const Vec2& vec2) const
{
    return this->x * vec2.x + this->y * vec2.y;
}

float Vec2::distance(const Vec2& vec2) const
{
    return sqrtf(powf(this->x - vec2.x, 2) + powf(this->y - vec2.y, 2));
}

bool Vec2::sloped(const Vec2& vec2_1, const Vec2& vec2_2)
{
    return (vec2_1.x / vec2_1.y) == (vec2_2.x / vec2_2.y);
}

bool Vec2::sloped(const Vec2& vec2) const
{
    return (vec2.x / vec2.y) == (this->x / this->y);
}
