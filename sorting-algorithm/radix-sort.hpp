#ifndef RADIX_SORT_HPP
#define RADIX_SORT_HPP

void CountingSort(int *&array, const int &size, const int exponentiation, const int base)
{
    int* count = new int[base]{0};
    int* output = new int[size]{0};

    for (int i = 0; i < size; i++)
        count[(array[i] / exponentiation) % base]++;
    for (int i = 1; i < base; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / exponentiation) % base] - 1] = array[i];
        count[(array[i] / exponentiation) % base]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];

    delete[] count, output;
}

void RadixSort(int *&array, const int &size)
{
    int base = 10, maxElement = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > maxElement)
            maxElement = array[i];

    for (int exp = 1; (maxElement / exp) > 0; exp *= base)
        CountingSort(array, size, exp, base);
}

void CountingSort(int *&array, const int &size, const int exponentiation, const int base, unsigned long long &count_comparisons)
{
    int* count = new int[base]{0};
    int* output = new int[size]{0};

    for (int i = 0; ++count_comparisons && i < size; i++)
        count[(array[i] / exponentiation) % base]++;
    for (int i = 1; ++count_comparisons && i < base; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; ++count_comparisons && i >= 0; i--)
    {
        output[count[(array[i] / exponentiation) % base] - 1] = array[i];
        count[(array[i] / exponentiation) % base]--;
    }

    for (int i = 0; ++count_comparisons && i < size; i++)
        array[i] = output[i];

    delete[] count, output;
}

void RadixSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    int base = 10, maxElement = array[0];
    for (int i = 1; ++count_comparisons && i < size; i++)
        if (++count_comparisons && array[i] > maxElement)
            maxElement = array[i];

    for (int exp = 1; ++count_comparisons && (maxElement / exp) > 0; exp *= base)
        CountingSort(array, size, exp, base, count_comparisons);
}

#endif
