#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <iostream>

void heapify(int *&array, const int &size, int i)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;

    if ((left < size) && (array[left] > array[largest]))
        largest = left;

    if ((right < size) && (array[right] > array[largest]))
        largest = right;

    if (largest != i)
    {
        std::swap(array[i], array[largest]);
        heapify(array, size, largest);
    }
}

void HeapSort(int *&array, const int &size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    for (int i = size - 1; i > 0; i--)
    {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

void heapify(int *&array, const int &size, int i, unsigned long long &count_comparisons)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;

    if ((++count_comparisons && left < size) && (++count_comparisons && array[left] > array[largest]))
        largest = left;

    if ((++count_comparisons && right < size) && (++count_comparisons && array[right] > array[largest]))
        largest = right;

    if (largest != i)
    {
        std::swap(array[i], array[largest]);
        heapify(array, size, largest, count_comparisons);
    }
}

void HeapSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    for (int i = size / 2 - 1; ++count_comparisons && i >= 0; i--)
        heapify(array, size, i, count_comparisons);

    for (int i = size - 1; ++count_comparisons && i > 0; i--)
    {
        std::swap(array[0], array[i]);
        heapify(array, i, 0, count_comparisons);
    }
}

#endif