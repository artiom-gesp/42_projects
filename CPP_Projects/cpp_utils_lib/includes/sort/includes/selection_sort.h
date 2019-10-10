
#ifndef CPPLIB_SELECTION_SORT_H
#define CPPLIB_SELECTION_SORT_H

#include "utils.h"

template <typename T>
void selection_sort(T *arr, size_t size)
{
    size_t min;
    for (size_t i = 0; i < size; i++) {
        min = i;
        for (size_t j = i + 1; j < size; j++) {
            min = arr[j] < arr[min] ? j : min;
        }
        if (min >= 0 && arr[min] < arr[i])
            swap(arr, i , min);
    }
}

#endif