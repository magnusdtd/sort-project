#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <iostream>

void BubbleSort(int* &array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    bool swapped = false;
    for (int i = 0; ++count_comparisons && i < size - 1; i++)
    {
        swapped = false;
        for (int j = 0; ++count_comparisons && j < size - i - 1; j++)
        {
            if (++count_comparisons && array[j] > array[j + 1])
            {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (++count_comparisons && !swapped)
            break;
    }
}

#endif