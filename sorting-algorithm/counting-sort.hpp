#ifndef COUNTING_SORT_HPP
#define COUNTING_SORT_HPP

#include <vector>

void CountingSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    int maxElement = array[0];
    for (int i = 1; ++count_comparisons && i < size; i++)
        if (++count_comparisons && array[i] > maxElement)
            maxElement = array[i];

    std::vector<int> count(maxElement + 1, 0);
    for (int i = 0; ++count_comparisons && i < size; i++)
        count[array[i]]++;

    int index = 0;
    for (int i = 0; ++count_comparisons && i <= maxElement; i++)
    {
        while (++count_comparisons && count[i] > 0)
        {
            array[index++] = i;
            count[i]--;
        }
    }
}

#endif