//
// Created by kisly on 14.07.2025.
//

#ifndef VECTORS_HPP
#define VECTORS_HPP

namespace core
{
    namespace math
    {
        class Vec2;
        class Vec3;
        class Vec4;
        class Mat4;
        
        /// @brief класс двух мерного вектора
        class Vec2 final
        {
        public:
            float x;
            float y;

            Vec2();
            Vec2(float x, float y = 0);
            Vec2(const Vec2 &vec2);

            Vec2 operator+(const Vec2 &vec2);
            Vec2 operator-(const Vec2 &vec2);
            Vec2 operator*(const Vec2 &vec2);
            Vec2 operator/(const Vec2 &vec2);

            Vec2 operator*(const float &value);
            Vec2 operator/(const float &value);

            void operator+=(const Vec2 &vec2);
            void operator-=(const Vec2 &vec2);
            void operator*=(const Vec2 &vec2);
            void operator/=(const Vec2 &vec2);

            bool operator==(const Vec2 &vec2);
            bool operator>(const Vec2 &vec2);
            bool operator<(const Vec2 &vec2);
            bool operator>=(const Vec2 &vec2);
            bool operator<=(const Vec2 &vec2);

            void operator=(const Vec2 &vec2);

            static Vec2 normalize(const Vec2 &vec2);

            static float length(const Vec2 &vec2);
            static float dot(const Vec2 &vec2_1, const Vec2 &vec2_2);
            static float distance(const Vec2 &vec2_1, const Vec2 &vec2_2);

            Vec2 normalize();

            void normal();

            float length() const;
            float dot(const Vec2 &vec2) const;
            float distance(const Vec2 &vec2) const;

            static bool sloped(const Vec2 &vec2_1, const Vec2 &vec2);
            bool sloped(const Vec2 &vec2) const;
        };

        class Vec3 final
        {
        public:
            float x;
            float y;
            float z;

            Vec3();
            Vec3(float x, float y = 0.0f, float z = 0.0f);
            explicit Vec3(const Vec4 &vec4);

            Vec3 operator+(const Vec3 &vec3);
            Vec3 operator-(const Vec3 &vec3);
            Vec3 operator*(const Vec3 &vec3);
            Vec3 operator/(const Vec3 &vec3);

            Vec3 operator*(const float &value);
            Vec3 operator/(const float &value);

            void operator+=(const Vec3 &vec3);
            void operator-=(const Vec3 &vec3);
            void operator*=(const Vec3 &vec3);
            void operator/=(const Vec3 &vec3);

            bool operator==(const Vec3 &vec3);
            bool operator>(const Vec3 &vec3);
            bool operator<(const Vec3 &vec3);
            bool operator>=(const Vec3 &vec3);
            bool operator<=(const Vec3 &vec3);

            void operator=(const Vec3 &vec3);

            static Vec3 normalize(const Vec3 &vec3);
            static Vec3 cross(const Vec3 &vec3_1, const Vec3 &vec3_2);

            static float length(const Vec3 &vec3);
            static float dot(const Vec3 &vec3_1, const Vec3 &vec3_2);
            static float distance(const Vec3 &vec3_1, const Vec3 &vec3_2);

            Vec3 normalize();

            void normal();

            float length() const;
            float dot(const Vec3 &vec3) const;
            float distance(const Vec3 &vec3) const;
        };

        class Vec4 final
        {
        public:
            float x;
            float y;
            float z;
            float w;

            Vec4();
            Vec4(const Vec4 &vec4);
            Vec4(float x, float y = 0.0f, float z = 0.0f, float w = 1.0f);
            Vec4(const Vec3 &vec3, float w = 1.0f);

            Vec4 operator+(const Vec4 &vec4);
            Vec4 operator-(const Vec4 &vec4);
            Vec4 operator*(const Vec4 &vec4);
            Vec4 operator/(const Vec4 &vec4);

            Vec4 operator*(const float &value);
            Vec4 operator/(const float &value);

            void operator+=(const Vec4 &vec4);
            void operator-=(const Vec4 &vec4);
            void operator*=(const Vec4 &vec4);
            void operator/=(const Vec4 &vec4);

            bool operator==(const Vec4 &vec4);
            bool operator>(const Vec4 &vec4);
            bool operator<(const Vec4 &vec4);
            bool operator>=(const Vec4 &vec4);
            bool operator<=(const Vec4 &vec4);

            void operator=(const Vec4 &vec4);

            static Vec4 normalize(const Vec4 &vec4);
            static float length(const Vec4 &vec4);
            static float dot(const Vec4 &vec4_1, const Vec4 &vec4_2);
            static float distance(const Vec4 &vec4_1, const Vec4 &vec4_2);

            Vec4 normalize();

            void normal();
            float length() const;
            float dot(const Vec4 &vec4) const;
            float distance(const Vec4 &vec4) const;

            auto operator*(Mat4 mat4) -> Vec4;
        };
    }
}

#endif //VECTORS_HPP
