//
// Created by kisly on 14.07.2025.
//

#ifndef MATH_HPP
#define MATH_HPP

namespace core
{
    namespace math
    {
        constexpr double PI = 3.14159265358979323846;

        template<class T>
        T radians(T degrees)
        {
            return T(PI) / T(180) * degrees;
        }

        template<class T>
        T degrees(T radians)
        {
            return T(180) / T(PI) * radians;
        }
    }
} // core

#endif //MATH_HPP
