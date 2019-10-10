
#ifndef CPPLIB_SHELL_SORT_H
#define CPPLIB_SHELL_SORT_H

#include "utils.h"

template <typename T>
void gap_sort(T *arr, size_t size, int gap) {
    int tmp;
    for(size_t i = 0; i < size - gap; ++i) {
        if (i + gap < size && arr[i + gap] < arr[i]) {
            swap(arr, i, i + gap);
        }
        tmp = i;
        while (tmp - gap >= 0 && arr[tmp] < arr[tmp - gap]) {
            swap(arr, tmp, tmp - gap);
            tmp -= gap;
        }
    }
}

template <typename T>
void shell_sort(T *arr, size_t size)
{
    int ciura_gap_length = 8;
    int gap_break;
    int ciura_gap[] = {1, 4, 10, 23, 57, 132, 301, 701};

    if (size < 4) {
        insertion_sort(arr, size);
        return;
    }
    for (gap_break = ciura_gap_length - 1; gap_break > 0 && size < ciura_gap[gap_break]; gap_break--)
    {}
    for (int i = 0; i <= gap_break; i++) {
        gap_sort(arr, size, ciura_gap[gap_break - i]);
    }
}

#endif