//
// Created by kisly on 14.07.2025.
//

#ifndef VECTORS_HPP
#define VECTORS_HPP

namespace core
{
    namespace math
    {
        class Vector2;
        class Vector3;
        class Vector4;
        class Matrix4;
        
        /// @brief класс двух мерного вектора
        class Vector2 final
        {
        public:
            float x;
            float y;

            Vector2();
            Vector2(float x, float y = 0);
            Vector2(const Vector2 &vec2);

            Vector2 operator+(const Vector2 &vec2);
            Vector2 operator-(const Vector2 &vec2);
            Vector2 operator*(const Vector2 &vec2);
            Vector2 operator/(const Vector2 &vec2);

            Vector2 operator*(const float &value);
            Vector2 operator/(const float &value);

            void operator+=(const Vector2 &vec2);
            void operator-=(const Vector2 &vec2);
            void operator*=(const Vector2 &vec2);
            void operator/=(const Vector2 &vec2);

            bool operator==(const Vector2 &vec2);
            bool operator>(const Vector2 &vec2);
            bool operator<(const Vector2 &vec2);
            bool operator>=(const Vector2 &vec2);
            bool operator<=(const Vector2 &vec2);

            void operator=(const Vector2 &vec2);

            static Vector2 normalize(const Vector2 &vec2);

            static float length(const Vector2 &vec2);
            static float dot(const Vector2 &vec2_1, const Vector2 &vec2_2);
            static float distance(const Vector2 &vec2_1, const Vector2 &vec2_2);

            Vector2 normalize();

            void normal();

            float length() const;
            float dot(const Vector2 &vec2) const;
            float distance(const Vector2 &vec2) const;

            static bool sloped(const Vector2 &vec2_1, const Vector2 &vec2);
            bool sloped(const Vector2 &vec2) const;
        };

        class Vector3 final
        {
        public:
            float x;
            float y;
            float z;

            Vector3();
            Vector3(float x, float y = 0.0f, float z = 0.0f);
            explicit Vector3(const Vector4 &vec4);

            Vector3 operator+(const Vector3 &vec3);
            Vector3 operator-(const Vector3 &vec3);
            Vector3 operator*(const Vector3 &vec3);
            Vector3 operator/(const Vector3 &vec3);

            Vector3 operator*(const float &value);
            Vector3 operator/(const float &value);

            void operator+=(const Vector3 &vec3);
            void operator-=(const Vector3 &vec3);
            void operator*=(const Vector3 &vec3);
            void operator/=(const Vector3 &vec3);

            bool operator==(const Vector3 &vec3);
            bool operator>(const Vector3 &vec3);
            bool operator<(const Vector3 &vec3);
            bool operator>=(const Vector3 &vec3);
            bool operator<=(const Vector3 &vec3);

            void operator=(const Vector3 &vec3);

            static Vector3 normalize(const Vector3 &vec3);
            static Vector3 cross(const Vector3 &vec3_1, const Vector3 &vec3_2);

            static float length(const Vector3 &vec3);
            static float dot(const Vector3 &vec3_1, const Vector3 &vec3_2);
            static float distance(const Vector3 &vec3_1, const Vector3 &vec3_2);

            Vector3 normalize();

            void normal();

            float length() const;
            float dot(const Vector3 &vec3) const;
            float distance(const Vector3 &vec3) const;
        };

        class Vector4 final
        {
        public:
            float x;
            float y;
            float z;
            float w;

            Vector4();
            Vector4(const Vector4 &vec4);
            Vector4(float x, float y = 0.0f, float z = 0.0f, float w = 1.0f);
            Vector4(const Vector3 &vec3, float w = 1.0f);

            Vector4 operator+(const Vector4 &vec4);
            Vector4 operator-(const Vector4 &vec4);
            Vector4 operator*(const Vector4 &vec4);
            Vector4 operator/(const Vector4 &vec4);

            Vector4 operator*(const float &value);
            Vector4 operator/(const float &value);

            void operator+=(const Vector4 &vec4);
            void operator-=(const Vector4 &vec4);
            void operator*=(const Vector4 &vec4);
            void operator/=(const Vector4 &vec4);

            bool operator==(const Vector4 &vec4);
            bool operator>(const Vector4 &vec4);
            bool operator<(const Vector4 &vec4);
            bool operator>=(const Vector4 &vec4);
            bool operator<=(const Vector4 &vec4);

            void operator=(const Vector4 &vec4);

            static Vector4 normalize(const Vector4 &vec4);
            static float length(const Vector4 &vec4);
            static float dot(const Vector4 &vec4_1, const Vector4 &vec4_2);
            static float distance(const Vector4 &vec4_1, const Vector4 &vec4_2);

            Vector4 normalize();

            void normal();
            float length() const;
            float dot(const Vector4 &vec4) const;
            float distance(const Vector4 &vec4) const;

            auto operator*(Matrix4 mat4) -> Vector4;
        };
    }
}

#endif //VECTORS_HPP
