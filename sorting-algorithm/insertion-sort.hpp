#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

void InsertionSort(int *&array, const int &size)
{
    for (int i = 0; i < size; i++)
    {
        int current = array[i], j = i - 1;
        while ((j >= 0) && (array[j] > current))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = current;
    }
}


void InsertionSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    for (int i = 0; ++count_comparisons && i < size; i++)
    {
        int current = array[i], j = i - 1;
        while ((++count_comparisons && j >= 0) && (++count_comparisons && array[j] > current))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = current;
    }
}

#endif