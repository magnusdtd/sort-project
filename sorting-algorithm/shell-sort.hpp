#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

void ShellSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    int gap = size / 2;
    while (++count_comparisons && gap > 0)
    {
        for (int i = gap; ++count_comparisons && i < size; i++)
        {
            int temp = array[i], j = i;
            while ((++count_comparisons && j >= gap) && (++count_comparisons && array[j - gap] > temp))
            {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
        gap /= 2;
    }
}

#endif