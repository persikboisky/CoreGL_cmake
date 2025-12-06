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
        class Vec4;
        class Vec3;

        class Mat4 final
        {
        private:
            float mat[16];

        public:
            explicit Mat4(float diagonal = 1.0f);
            explicit Mat4(float mat4[16]);

            [[nodiscard]] float* getArray();
            [[nodiscard]] static std::array<float, 16> multiply(float mat1[16], float mat2[16]);
            [[nodiscard]] static Vec4 multiply(Vec4 vec, float mat[16]);

            [[nodiscard]] auto operator * (Mat4 mat4) -> Mat4;
            [[nodiscard]] auto operator * (Vec4 vec4) -> Vec4;

            void operator *= (Mat4 mat4);
            void operator = (Mat4 mat4);
            void operator = (float mat4[16]);

            [[nodiscard]] static Mat4 getScale(const Vec3& vecScale, const Mat4& mat4 = Mat4(1.0f));
            [[nodiscard]] static Mat4 getTranslate(const Vec3& vecTranslate, const Mat4& mat4 = Mat4(1.0f));
            [[nodiscard]] static Mat4 getRotate(float angle, const Vec3& axises, const Mat4& mat4 = Mat4(1.0f));
            [[nodiscard]] static Mat4 getPerspective(float fovToRadians, float aspect, float near, float far);
            [[nodiscard]] static Mat4 getLookAt(Vec3 pos, Vec3 target, Vec3 up);

			static Mat4 getRotateX(float angle, const Mat4& mat4 = Mat4(1.0f));
			static Mat4 getRotateY(float angle, const Mat4& mat4 = Mat4(1.0f));
			static Mat4 getRotateZ(float angle, const Mat4& mat4 = Mat4(1.0f));

            void scale(const Vec3& vecScale);
            void translate(const Vec3& vecTranslate);
            void rotateX(float angle);
            void rotateY(float angle);
            void rotateZ(float angle);
            void perspective(float fovToRadians, float aspect, float near, float far);
            void lookAt(Vec3 pos, Vec3 target, Vec3 up);

            void reset();
        };
    }
}
#endif //MATRIX4_HPP
