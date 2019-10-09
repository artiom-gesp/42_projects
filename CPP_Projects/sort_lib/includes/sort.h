//
// Created by Artiom GESP on 10/4/19.
//

#ifndef CPPLIB_SELECTION_SORT_H
#define CPPLIB_SELECTION_SORT_H

#include <iostream>


template <typename T>
void swap(T *arr, size_t i, size_t j)
{
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

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

#endif //CPPLIB_SELECTION_SORT_H
