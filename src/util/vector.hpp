//
// Created by kisly on 14.07.2025.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>
#include <vector>

namespace core
{
    namespace vector
    {
        int searchIndexFromValue(std::vector<int> vec, int value);
        int searchIndexFromValue(std::vector<unsigned int> vec, unsigned int value);
        int searchIndexFromValue(std::vector<unsigned short> vec, unsigned short value);
        int searchIndexFromValue(std::vector<std::string> vec, std::string value);

        std::vector<float> arrayToVector_float(float* array, unsigned int size_array);
        std::vector<int> arrayToVector_int(int* array, unsigned int size_array);
        std::vector<char> arrayToVector_char(char* array, unsigned int size_array);
        std::vector<unsigned char> arrayToVector_uchar(unsigned char* array, unsigned int size_array);
    }
}

#endif //VECTOR_HPP
