#include "sort.hpp"

void Sort::SelectionSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    for (int i = 0; ++count_comparisons && i < size - 1; i++)
    {
        int positionMin = i;
        for (int j = i + 1; ++count_comparisons && j < size; j++)
            if (++count_comparisons && array[j] < array[positionMin])
            {
                positionMin = j;
            }
        std::swap(array[i], array[positionMin]);
    }
}

void Sort::InsertionSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
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

void Sort::BubbleSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
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

void Sort::ShakerSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
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

void Sort::ShellSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
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

void Sort::heapify(int *&array, const int &size, int i, unsigned long long &count_comparisons)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;

    if ((++count_comparisons && left < size) && (++count_comparisons && array[left] > array[largest]))
        largest = left;

    if ((++count_comparisons && right < size) && (++count_comparisons && array[right] > array[largest]))
        largest = right;

    if (largest != i)
    {
        std::swap(array[i], array[largest]);
        heapify(array, size, largest, count_comparisons);
    }
}

void Sort::HeapSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    for (int i = size / 2 - 1; ++count_comparisons && i >= 0; i--)
        heapify(array, size, i, count_comparisons);

    for (int i = size - 1; ++count_comparisons && i > 0; i--)
    {
        std::swap(array[0], array[i]);
        heapify(array, i, 0, count_comparisons);
    }
}

void Sort::merge(int *&array, const int left, const int mid, int right, unsigned long long &count_comparisons)
{
    int size1 = mid - left + 1, size2 = right - mid;

    int *leftArray, *rightArray;
    leftArray = new int[size1];
    rightArray = new int[size2];

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

    delete[] leftArray;
    delete[] rightArray;
}

void Sort::MergeSort(int *&array, const int left, const int right, unsigned long long &count_comparisons)
{
    if (++count_comparisons && left >= right)
        return;

    int mid = left + (right - left) / 2;
    MergeSort(array, left, mid, count_comparisons);
    MergeSort(array, mid + 1, right, count_comparisons);
    merge(array, left, mid, right, count_comparisons);
}

void Sort::MergeSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    MergeSort(array, 0, size - 1, count_comparisons);
}

int Sort::partition(int *&array, const int low, const int high, unsigned long long &count_comparisons)
{
    int pivot = array[high], i = low - 1;

    for (int j = low; ++count_comparisons && j <= high - 1; j++)
    {
        if (++count_comparisons && array[j] < pivot)
        {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return i + 1;
}

void Sort::QuickSort(int *&array, const int low, const int high, unsigned long long &count_comparisons)
{
    if (++count_comparisons && low < high)
    {
        int position = partition(array, low, high, count_comparisons);

        QuickSort(array, low, position - 1, count_comparisons);
        QuickSort(array, position + 1, high, count_comparisons);
    }
}

void Sort::QuickSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    QuickSort(array, 0, size - 1, count_comparisons);
}

void Sort::CountingSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
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

void Sort::CountingSort(int *&array, const int &size, const int exponentiation, const int base, unsigned long long &count_comparisons)
{
    std::vector<int> count(base, 0), output(size, 0);

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
}

void Sort::RadixSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    int base = 10, maxElement = array[0];
    for (int i = 1; ++count_comparisons && i < size; i++)
        if (++count_comparisons && array[i] > maxElement)
            maxElement = array[i];

    for (int exp = 1; ++count_comparisons && (maxElement / exp) > 0; exp *= base)
        CountingSort(array, size, exp, base, count_comparisons);
}

void Sort::FlashSort(int *&array, const int &size, unsigned long long &count_comparisons)
{
    if (++count_comparisons && size <= 1)
        return;

    int minVal = array[0], maxVal = array[0];
    for (int i = 1; ++count_comparisons && i < size; i++)
    {
        if (++count_comparisons && minVal > array[i])
            minVal = array[i];
        if (++count_comparisons && maxVal < array[i])
            maxVal = array[i];
    }

    int m = static_cast<int>(0.4 * size);
    std::vector<int> L(m, 0);

    for (int i = 0; ++count_comparisons && i < size; i++)
    {
        int classIdx = std::floor((array[i] - minVal) * (m - 1) / (maxVal - minVal));
        L[classIdx]++;
    }

    for (int i = 1; ++count_comparisons && i < m; i++)
        L[i] += L[i - 1];

    std::vector<int> output(size);
    for (int i = size - 1; ++count_comparisons && i >= 0; i--)
    {
        int classIdx = (array[i] - minVal) * (m - 1) / (maxVal - minVal);
        output[L[classIdx] - 1] = array[i];
        L[classIdx]--;
    }

    for (int i = 0; ++count_comparisons && i < size; i++)
        array[i] = output[i];

    InsertionSort(array, size, count_comparisons);
}
