#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

void merge(int *&array, const int left, const int mid, int right)
{
    int size1 = mid - left + 1, size2 = right - mid;

    int* leftArray = new int[size1];
    int* rightArray = new int[size2];

    for (int i = 0; i < size1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < size2; j++)
        rightArray[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while ((i < size1) && (j < size2))
        if (leftArray[i] <= rightArray[j])
            array[k++] = leftArray[i++];
        else
            array[k++] = rightArray[j++];

    while (i < size1)
        array[k++] = leftArray[i++];

    while (j < size2)
        array[k++] = rightArray[j++];

    delete[] leftArray, rightArray;

}

void MergeSort(int *&array, const int left, const int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    MergeSort(array, left, mid);
    MergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

void MergeSort(int *&array, const int &size)
{
    MergeSort(array, 0, size - 1);
}

void merge(int *&array, const int left, const int mid, int right, unsigned long long &count_comparisons)
{
    int size1 = mid - left + 1, size2 = right - mid;

    int* leftArray = new int[size1];
    int* rightArray = new int[size2];

    for (int i = 0; ++count_comparisons && i < size1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; ++count_comparisons && j < size2; j++)
        rightArray[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while ((++count_comparisons && i < size1) && (++count_comparisons && j < size2))
        if (++count_comparisons && leftArray[i] <= rightArray[j])
            array[k++] = leftArray[i++];
        else
            array[k++] = rightArray[j++];

    while (++count_comparisons && i < size1)
        array[k++] = leftArray[i++];

    while (++count_comparisons && j < size2)
        array[k++] = rightArray[j++];

    delete[] leftArray, rightArray;
}

void MergeSort(int *&array, const int left, const int right, unsigned long long &count_comparisons)
{
    if (++count_comparisons && left >= right)
        return;

    int mid = left + (right - left) / 2;
    MergeSort(array, left, mid, count_comparisons);
    MergeSort(array, mid + 1, right, count_comparisons);
    merge(array, left, mid, right, count_comparisons);
}

void MergeSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    count_comparisons = 0;
    MergeSort(array, 0, size - 1, count_comparisons);
}

#endif