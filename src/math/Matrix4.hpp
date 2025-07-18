//
// Created by kisly on 14.07.2025.
//

#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <array>

namespace core
{
    namespace math
    {
        class Vector4;
        class Vector3;

        class Matrix4 final
        {
        private:
            float mat[16];

        public:
            Matrix4(float diagonal = 1.0f);
            Matrix4(float mat4[16]);

            [[nodiscard]] float* getArray();
            [[nodiscard]] static std::array<float, 16> multiply(float mat1[16], float mat2[16]);
            [[nodiscard]] static Vector4 multiply(Vector4 vec, float mat[16]);

            [[nodiscard]] auto operator * (Matrix4 mat4) -> Matrix4;
            [[nodiscard]] auto operator * (Vector4 vec4) -> Vector4;

            void operator *= (Matrix4 mat4);
            void operator = (Matrix4 mat4);
            void operator = (float mat4[16]);

            [[nodiscard]] static Matrix4 getScale(const Vector3& vecScale, const Matrix4& mat4 = Matrix4(1.0f));
            [[nodiscard]] static Matrix4 getTranslate(const Vector3& vecTranslate, const Matrix4& mat4 = Matrix4(1.0f));
            [[nodiscard]] static Matrix4 getRotate(float angle, const Vector3& axises, const Matrix4& mat4 = Matrix4(1.0f));
            [[nodiscard]] static Matrix4 getPerspective(float fovToRadians, float aspect, float near, float far);
            [[nodiscard]] static Matrix4 getLookAt(Vector3 pos, Vector3 target, Vector3 up);
        };
    }
}

#endif //MATRIX4_HPP
