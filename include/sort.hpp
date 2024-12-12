#ifndef SORT_HPP
#define SORT_HPP

#include <iostream>
#include <vector>
#include <math.h>

namespace Sort
{
    void SelectionSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void InsertionSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void BubbleSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void ShakerSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void ShellSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void heapify(int *&array, const int &size, int i, unsigned long long &count_comparisons);

    void HeapSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void merge(int *&array, const int left, const int mid, int right, unsigned long long &count_comparisons);

    void MergeSort(int *&array, const int left, const int right, unsigned long long &count_comparisons);

    void MergeSort(int *&array, const int &size, unsigned long long &count_comparisons);

    int partition(int *&array, const int low, const int high, unsigned long long &count_comparisons);

    void QuickSort(int *&array, const int low, const int high, unsigned long long &count_comparisons);

    void QuickSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void CountingSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void CountingSort(int *&array, const int &size, const int exponentiation, const int base, unsigned long long &count_comparisons);

    void RadixSort(int *&array, const int &size, unsigned long long &count_comparisons);

    void FlashSort(int *&array, const int &size, unsigned long long &count_comparisons);

}
#endif