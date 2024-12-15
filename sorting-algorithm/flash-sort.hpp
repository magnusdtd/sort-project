#ifndef FLASH_SORT_HPP
#define FLASH_SORT_HPP

#include <vector>

void FlashSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    int m = 0.43 * size;
    std::vector<int> L(m);
    int minA = array[0], maxA = array[0];
    for (int i = 1; ++count_comparisons && i < size; i++) {
        if (++count_comparisons && minA > array[i]) minA = array[i];
        if (++count_comparisons && maxA < array[i]) maxA = array[i];
    }
    // parse 1: classification
    for (int i = 0; ++count_comparisons && i < size; ++i) {
        int k = 1ll * (m - 1) * (array[i] - minA) / (maxA - minA);
        ++L[k];
    }
    for (int i = 1; ++count_comparisons && i < m; ++i)
        L[i] += L[i - 1];
    // parse 2: permutation cycle
    int cnt = 0, i = 0, k = m - 1;
    while (++count_comparisons && cnt < size) {
        while (++count_comparisons && i > L[k] - 1) {
            ++i;
            k = 1ll * (m - 1) * (array[i] - minA) / (maxA - minA);
        }
        int x = array[i]; //bat dau chu trinh
        while (++count_comparisons && i < L[k]) {
            k = 1ll * (m - 1) * (x - minA) / (maxA - minA); 
            int y = array[L[k] - 1];
            array[L[k] - 1] = x;
            x = y;
            --L[k];
            ++cnt;
        }
    }
    //parse 3: sorting each block with insertion sort   
    for (int j = 0; ++count_comparisons && ++j < size;) {
        int value = array[j];
        i = j;
        while (++count_comparisons && (--i >= 0) && (++count_comparisons && (k = array[i]) > value))
            array[i + 1] = k;
        array[i + 1] = value;
    }

}


#endif