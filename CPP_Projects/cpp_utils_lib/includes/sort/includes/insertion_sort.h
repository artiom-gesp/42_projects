#ifndef CPPLIB_INSERTION_SORT_H
#define CPPLIB_INSERTION_SORT_H

#include "utils.h"

template <typename T>
void insertion_sort(T *arr, size_t size) {
    int tmp;
    for(size_t i = 0; i < size; ++i) {
        tmp = i;
        while (tmp > 0 && arr[tmp] < arr[tmp - 1]) {
            swap(arr, tmp, tmp - 1);
            --tmp;
        }
    }
}

#endif