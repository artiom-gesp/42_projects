#ifndef CPPLIB_MERGE_SORT_H
#define CPPLIB_MERGE_SORT_H

#include "insertion_sort.h"

template <typename T>
void merge(T *arr, T *tmp, int low, int mid, int high)
{
    int tmp_index = low;
    int tmp_low = low;
    int tmp_mid = mid;
    static int inv = 0;

    while (low < tmp_mid && mid < high)
    {
        if (arr[low] <= arr[mid])
            tmp[tmp_index++] = arr[low++];
        else
            tmp[tmp_index++] = arr[mid++];
    }
    while (low < tmp_mid)
        tmp[tmp_index++] = arr[low++];
    while (mid < high)
        tmp[tmp_index++] = arr[mid++];
    for (int i = tmp_low; i < high; ++i)
        arr[i] = tmp[i];
}

template <typename T>
void merge_sort(T *arr, T *tmp, int low, int mid, int high)
{
    int mid1;
    int mid2;
    if (high - low < 10) {
        insertion_sort(arr + low, high - low);
        return ;
    }
    mid1 = (low + mid) / 2;
    mid2 = (mid + high) / 2;

    merge_sort(arr, tmp, low, mid1, mid);
    merge_sort(arr, tmp, mid, mid2, high);

    if (arr[mid - 1] > arr[mid])
        merge(arr, tmp, low, mid, high);
}

template <typename T>
void merge_sort(T *arr, size_t size)
{
    if (size < 10)
    {
        insertion_sort(arr, size);
        return ;
    }
    T *tmp = new T[size];
    merge_sort(arr, tmp, 0, size / 2, size);
    delete[] tmp;
}

#endif