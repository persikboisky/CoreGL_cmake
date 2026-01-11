//
// Created by kisly on 14.07.2025.
//

#ifndef MATH_HPP
#define MATH_HPP

namespace core
{
    namespace math
    {
        /// @brief число PI :)
        constexpr double PI = 3.14159265358979323846;

        /// @brief функция перевода градусов в радианы
        /// @tparam T тип
        /// @param degrees значение в градусах
        /// @return значение в радианах
        template<class T>
        T radians(T degrees)
        {
            return T(PI) / T(180) * degrees;
        }

        /// @brief функция перевода радиан в градусы
        /// @tparam T тип
        /// @param radians значение в радианах
        /// @return значение в градусах
        template<class T>
        T degrees(T radians)
        {
            return T(180) / T(PI) * radians;
        }

        void setSeedRandom(unsigned int seed);

        // double random();
        // bool randomB(float chanceToTrue = 0.5f);
    }
} // core

#endif //MATH_HPP
