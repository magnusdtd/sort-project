#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <iostream>

int partition(int *&array, const int low, const int high)
{
    int mid = low + (high - low) / 2;
    int pivot = array[mid];
    std::swap(array[mid], array[high]);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return i + 1;
}

void QuickSort(int *&array, const int low, const int high)
{
    if (low < high)
    {
        int position = partition(array, low, high);

        QuickSort(array, low, position - 1);
        QuickSort(array, position + 1, high);
    }
}

void QuickSort(int *&array, const int &size)
{
    QuickSort(array, 0, size - 1);
}


int partition(int *&array, const int low, const int high, unsigned long long &count_comparisons)
{
    int mid = low + (high - low) / 2;
    int pivot = array[mid];
    std::swap(array[mid], array[high]);
    int i = low - 1;

    for (int j = low; ++count_comparisons && j <= high - 1; j++)
    {
        if (++count_comparisons && array[j] < pivot)
        {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return i + 1;
}

void QuickSort(int *&array, const int low, const int high, unsigned long long &count_comparisons)
{
    if (++count_comparisons && low < high)
    {
        int position = partition(array, low, high, count_comparisons);

        QuickSort(array, low, position - 1, count_comparisons);
        QuickSort(array, position + 1, high, count_comparisons);
    }
}

void QuickSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    QuickSort(array, 0, size - 1, count_comparisons);
}


#endif