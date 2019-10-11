//
// Created by Artiom GESP on 10/10/19.
//

#ifndef MY_UTILS_LIB_UTILS_H
#define MY_UTILS_LIB_UTILS_H

#include <iostream>

template <typename T>
void swap(T *arr, size_t i, size_t j)
{
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

#endif //MY_UTILS_LIB_UTILS_H
