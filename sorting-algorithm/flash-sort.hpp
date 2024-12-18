#ifndef FLASH_SORT_HPP
#define FLASH_SORT_HPP

#include <vector>

void FlashSort(int *&array, const int &size)
{
    int m = 0.43 * size;
    std::vector<int> L(m);
    int minValue = array[0], maxValue = array[0];
    for (int i = 1; i < size; i++) {
        if (minValue > array[i]) minValue = array[i];
        if (maxValue < array[i]) maxValue = array[i];
    }

    // Parse 1: classification
    for (int i = 0; i < size; ++i) {
        int k = 1ll * (m - 1) * (array[i] - minValue) / (maxValue - minValue);
        ++L[k];
    }
    for (int i = 1; i < m; ++i)
        L[i] += L[i - 1];

    // Parse 2: permutation cycle
    int cnt = 0, i = 0, k = m - 1;
    while (cnt < size) {
        while (i > L[k] - 1) {
            ++i;
            k = 1ll * (m - 1) * (array[i] - minValue) / (maxValue - minValue);
        }
        int x = array[i]; //bat dau chu trinh
        while (i < L[k]) {
            k = 1ll * (m - 1) * (x - minValue) / (maxValue - minValue); 
            int y = array[L[k] - 1];
            array[L[k] - 1] = x;
            x = y;
            --L[k];
            ++cnt;
        }
    }

    // Parse 3: sorting each block with insertion sort   
    for (int j = 0; ++j < size;) {
        int value = array[j];
        i = j;
        while ((--i >= 0) && ((k = array[i]) > value))
            array[i + 1] = k;
        array[i + 1] = value;
    }

}

void FlashSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    int m = 0.43 * size;
    std::vector<int> L(m);
    int minValue = array[0], maxValue = array[0];
    for (int i = 1; ++count_comparisons && i < size; i++) {
        if (++count_comparisons && minValue > array[i]) minValue = array[i];
        if (++count_comparisons && maxValue < array[i]) maxValue = array[i];
    }

    // Parse 1: classification
    for (int i = 0; ++count_comparisons && i < size; ++i) {
        int k = 1ll * (m - 1) * (array[i] - minValue) / (maxValue - minValue);
        ++L[k];
    }
    for (int i = 1; ++count_comparisons && i < m; ++i)
        L[i] += L[i - 1];

    // Parse 2: permutation cycle
    int cnt = 0, i = 0, k = m - 1;
    while (++count_comparisons && cnt < size) {
        while (++count_comparisons && i > L[k] - 1) {
            ++i;
            k = 1ll * (m - 1) * (array[i] - minValue) / (maxValue - minValue);
        }
        int x = array[i]; //bat dau chu trinh
        while (++count_comparisons && i < L[k]) {
            k = 1ll * (m - 1) * (x - minValue) / (maxValue - minValue); 
            int y = array[L[k] - 1];
            array[L[k] - 1] = x;
            x = y;
            --L[k];
            ++cnt;
        }
    }

    // Parse 3: sorting each block with insertion sort   
    for (int j = 0; ++count_comparisons && ++j < size;) {
        int value = array[j];
        i = j;
        while (++count_comparisons && (--i >= 0) && (++count_comparisons && (k = array[i]) > value))
            array[i + 1] = k;
        array[i + 1] = value;
    }

}


#endif