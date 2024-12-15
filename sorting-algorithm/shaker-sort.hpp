#ifndef SHAKER_SORT_HPP
#define SHAKER_SORT_HPP

#include <iostream>

void ShakerSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    bool swapped = true;
    int start = 0, end = size - 1;
    while ((++count_comparisons && start < end) && (++count_comparisons && swapped))
    {
        swapped = false;
        for (int i = start; ++count_comparisons && i < end; ++i)
        {
            if (++count_comparisons && array[i] > array[i + 1])
            {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }

        if (++count_comparisons && !swapped)
            break;
        swapped = false;
        --end;

        for (int i = end - 1; ++count_comparisons && i >= start; i--)
        {
            if (++count_comparisons && array[i] > array[i + 1])
            {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }

        ++start;
    }
}

#endif