#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

#define RANDOM_DATA 0
#define SORTED_DATA 1
#define REVERSE_DATA 2
#define NEARLY_SORTED_DATA 3

template <class T>
void HoanVi(T &a, T &b)
{
    T x = a;
    a = b;
    b = x;
}

//-------------------------------------------------

// Function to generate an array with random data
void GenerateRandomData(int *a, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);

    for (int i = 0; i < n; i++)
    {
        a[i] = dis(gen);
    }
}

// Function to generate an array with sorted data
void GenerateSortedData(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

// Function to generate an array with reverse sorted data
void GenerateReverseData(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = n - 1 - i;
    }
}

// Function to generate an array with nearly sorted data
void GenerateNearlySortedData(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);

    for (int i = 0; i < 10; i++)
    {
        int r1 = dis(gen);
        int r2 = dis(gen);
        HoanVi(a[r1], a[r2]);
    }
}

// Function to generate data based on the specified type
void GenerateData(int *a, int n, int dataType)
{
    switch (dataType)
    {
    case RANDOM_DATA:    // Random data
        GenerateRandomData(a, n);
        break;
    case SORTED_DATA:    // Sorted data
        GenerateSortedData(a, n);
        break;
    case REVERSE_DATA:   // Reverse sorted data
        GenerateReverseData(a, n);
        break;
    case NEARLY_SORTED_DATA:  // Nearly sorted data
        GenerateNearlySortedData(a, n);
        break;
    default:
        std::cout << "Error: unknown data type!\n";
    }
}

#endif // DATA_GENERATOR_HPP