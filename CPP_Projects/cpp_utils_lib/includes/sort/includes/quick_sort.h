//
// Created by Artiom GESP on 10/11/19.
//

#ifndef MY_UTILS_LIB_QUICK_SORT_H
#define MY_UTILS_LIB_QUICK_SORT_H

#include "insertion_sort.h"
#include "shuffle.h"

//size_t median_of_three(size_t a, size_t b, size_t c)
//{
//    if (a > b) {
//        if (b > c)
//            return b;
//        else
//            return c;
//    }
//    else {
//        if (a > c)
//            return a;
//        else
//            return c;
//    }
//}

template <typename T>
void _quick_sort(T *arr, int low, int high)
{
    int i = low;
    int j = high - 1;
    T pivot = arr[(i + j) / 2];

    if (high - low < 10)
    {
        insertion_sort(arr + low, high - low);
        return;
    }
    while (i <= j)
    {
        while (arr[i] < pivot)
            ++i;
        while (arr[j] > pivot)
            --j;
        if (i <= j)
        {
            swap(arr, i++, j--);
        }
    }
    if (low < i)
        _quick_sort(arr, low, j + 1);
    if (i < high - 1)
        _quick_sort(arr, i, high);
}

template <typename T>
void quick_sort(T *arr, size_t size)
{
//    shuffle(arr, size);
    _quick_sort(arr, 0, size);
}


#endif //MY_UTILS_LIB_QUICK_SORT_H
