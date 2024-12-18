#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include <iostream>

void SelectionSort(int *&array, const int &size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int positionMin = i;
        for (int j = i + 1; j < size; j++)
            if (array[j] < array[positionMin])
                positionMin = j;
        std::swap(array[i], array[positionMin]);
    }
}

void SelectionSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    for (int i = 0; ++count_comparisons && i < size - 1; i++)
    {
        int positionMin = i;
        for (int j = i + 1; ++count_comparisons && j < size; j++)
            if (++count_comparisons && array[j] < array[positionMin])
                positionMin = j;
        std::swap(array[i], array[positionMin]);
    }
}

#endif