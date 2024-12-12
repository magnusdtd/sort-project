#include <gtest/gtest.h>
#include "./../include/sort.hpp"

void ValidateSortedArray(int *array, int size) {
    for (int i = 1; i < size; ++i) {
        ASSERT_LE(array[i - 1], array[i]);
    }
}

void TestSortFunction(void (*sortFunction)(int *&, const int &, unsigned long long &)) {
    int size = 10;
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    unsigned long long comparisons = 0;

    int *arrayPtr = array;
    sortFunction(arrayPtr, size, comparisons);
    ValidateSortedArray(arrayPtr, size);
}

TEST(SortTest, SelectionSort) {
    TestSortFunction(Sort::SelectionSort);
}

TEST(SortTest, InsertionSort) {
    TestSortFunction(Sort::InsertionSort);
}

TEST(SortTest, BubbleSort) {
    TestSortFunction(Sort::BubbleSort);
}

TEST(SortTest, ShakerSort) {
    TestSortFunction(Sort::ShakerSort);
}

TEST(SortTest, ShellSort) {
    TestSortFunction(Sort::ShellSort);
}

TEST(SortTest, HeapSort) {
    TestSortFunction(Sort::HeapSort);
}

TEST(SortTest, MergeSort) {
    TestSortFunction(Sort::MergeSort);
}

TEST(SortTest, QuickSort) {
    TestSortFunction(Sort::QuickSort);
}

TEST(SortTest, CountingSort) {
    TestSortFunction(Sort::CountingSort);
}

TEST(SortTest, RadixSort) {
    TestSortFunction(Sort::RadixSort);
}

TEST(SortTest, FlashSort) {
    TestSortFunction(Sort::FlashSort);
}