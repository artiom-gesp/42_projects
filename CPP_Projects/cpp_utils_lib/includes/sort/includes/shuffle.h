//
// Created by Artiom GESP on 10/14/19.
//

#ifndef MY_UTILS_LIB_SHUFFLE_H
#define MY_UTILS_LIB_SHUFFLE_H

#include "utils.h"
#include <random>

size_t random_index(size_t low, size_t high, std::mt19937 e)
{
    std::uniform_int_distribution<> dist(low, high); // define the range
    return dist(e);
}

template <typename T>
void shuffle(T *arr, size_t size)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    for (size_t i = 0; i < size; i++) {
        swap(arr, i, random_index(i, size - 1, eng));
    }
}

#endif //MY_UTILS_LIB_SHUFFLE_H
