//
// Created by kisly on 14.07.2025.
//

#include "vector.hpp"
#include <vector>

using namespace core;

int vector::searchIndexFromValue(std::vector<int> vec, int value)
{
    int index;
    bool flag = false;

    for (int i = 0; i < vec.size(); i++)
    {

        if (vec[i] == value)
        {
            index = i;
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        return -1;
    }

    return index;
}

int vector::searchIndexFromValue(std::vector<unsigned int> vec, unsigned int value)
{
    int index;
    bool flag = false;

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == value)
        {
            index = i;
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        return -1;
    }

    return index;
}

int vector::searchIndexFromValue(std::vector<unsigned short> vec, unsigned short value)
{
    int index;
    bool flag = false;

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == value)
        {
            index = i;
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        return -1;
    }

    return index;
}

std::vector<float> vector::arrayToVector_float(float* array, unsigned int size_array)
{
    std::vector<float> new_vector;

    for (unsigned int index = 0; index < size_array; index++)
    {
        new_vector.push_back(array[index]);
    }

    return new_vector;
}

std::vector<int> vector::arrayToVector_int(int* array, unsigned int size_array)
{
    std::vector<int> new_vector;

    for (unsigned int index = 0; index < size_array; index++)
    {
        new_vector.push_back(array[index]);
    }

    return new_vector;
}

std::vector<char> vector::arrayToVector_char(char* array, unsigned int size_array)
{
    std::vector<char> new_vector;

    for (unsigned int index = 0; index < size_array; index++)
    {
        new_vector.push_back(array[index]);
    }

    return new_vector;
}

std::vector<unsigned char> vector::arrayToVector_uchar(unsigned char* array, unsigned int size_array)
{
    std::vector<unsigned char> new_vector;

    for (unsigned int index = 0; index < size_array; index++)
    {
        new_vector.push_back(array[index]);
    }

    return new_vector;
}