#ifndef TEST_FUNCTION_HPP
#define TEST_FUNCTION_HPP

#include "./DataGenerator.hpp"
#include "./ReadWriteData.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <unordered_map>

#define defaultInputFilePath "./input.txt"
#define defaultInputFilePath_1 "./input_1.txt"
#define defaultInputFilePath_2 "./input_2.txt"
#define defaultInputFilePath_3 "./input_3.txt"
#define defaultInputFilePath_4 "./input_4.txt"
#define defaultOutputFilePath "./output.txt"

void TestSortAlgorithm( void (*sortFunction)(int *&, const int &, unsigned long long &), 
                        int *array, 
                        const int &size, 
                        unsigned long long &comparisons, 
                        double &time, 
                        const bool &outputTime, 
                        const bool &outputComparisons)
{
    comparisons = 0, time = 0.f;
    if (outputTime) {
        auto start = std::chrono::high_resolution_clock::now();
        sortFunction(array, size, comparisons);
        auto end = std::chrono::high_resolution_clock::now();

        time = std::chrono::duration<double, std::milli>(end - start).count();
    } else if (!outputTime && outputComparisons) {
        sortFunction(array, size, comparisons);
    }

}

void RunAndLog( void (*sortFunction)(int *&, const int &, unsigned long long &), 
                int *array, 
                const int &size, 
                const std::string &dataOrderName, 
                const int &dataOrderType,
                const bool &outputTime, 
                const bool &outputComparisons, 
                const std::string &outputFilePath)
{
    unsigned long long comparisons = 0;
    double time = 0.0;

    GenerateData(array, size, dataOrderType);
    if (!array) {
        std::cerr << "Error: Can't allocate new memory\n";
        exit(1);
    }
    writeArrayToFile(outputFilePath, array, size);

    std::cout << "Input order: " << dataOrderName << "\n";
    std::cout << "--------------------------------\n";
    TestSortAlgorithm(sortFunction, array, size, comparisons, time, outputTime, outputComparisons);
    if (outputTime)
        std::cout << "Running time: " << time << " milliseconds\n";
    if (outputComparisons)
        std::cout << "Comparisons: " << comparisons << "\n";
    std::cout << "\n";
}

void RunAlgorithmOnDifferentOrders(   void (*sortFunction)(int *&, const int &, unsigned long long &), 
                                            const std::string &algorithmName, 
                                            int size, 
                                            const bool &outputTime, 
                                            const bool &outputComparisons)
{
    int *array = new int[size];
    if (!array) {
        std::cerr << "Error: Can not allocate new memory\n";
        exit(1);
    }

    std::cout << "ALGORITHM MODE\n";
    std::cout << "Algorithm: " << algorithmName << "\n";
    std::cout << "Input size: " << size << "\n\n";

    RunAndLog(sortFunction, array, size, "Randomize", RANDOM_DATA, outputTime, outputComparisons, defaultInputFilePath_1);
    RunAndLog(sortFunction, array, size, "Nearly sorted", NEARLY_SORTED_DATA, outputTime, outputComparisons, defaultInputFilePath_2);
    RunAndLog(sortFunction, array, size, "Sorted", SORTED_DATA, outputTime, outputComparisons, defaultInputFilePath_3);
    RunAndLog(sortFunction, array, size, "Reversed", REVERSE_DATA, outputTime, outputComparisons, defaultInputFilePath_4);

    delete[] array;
}

void CompareAlgorithms( void (*sortFunction1)(int *&, const int &, unsigned long long &), 
                        void (*sortFunction2)(int *&, const int &, unsigned long long &), 
                        const std::string &algorithm1Name, 
                        const std::string &algorithm2Name, 
                        int *array, 
                        const int &size, 
                        const std::string &inputFilePath, 
                        const std::string &inputOrder)
{
    unsigned long long comparisons1 = 0, comparisons2 = 0;
    double time1 = 0.0, time2 = 0.0;

    int *arrayCopy = new int[size];
    std::copy(array, array + size, arrayCopy);
    TestSortAlgorithm(sortFunction1, arrayCopy, size, comparisons1, time1, true, true);

    std::copy(array, array + size, arrayCopy);
    TestSortAlgorithm(sortFunction2, arrayCopy, size, comparisons2, time2, true, true);

    std::cout << "COMPARE MODE\n";
    std::cout << "Algorithm: " << algorithm1Name << " | " << algorithm2Name << "\n";
    if (!inputFilePath.empty())
        std::cout << "Input file: " << inputFilePath << "\n";
    std::cout << "Input size: " << size << "\n";
    if (!inputOrder.empty())
        std::cout << "Input order: " << inputOrder << "\n";
    std::cout << "--------------------------------\n";
    std::cout << "Running time: " << time1 << " | " << time2 << " milliseconds\n";
    std::cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << "\n";
    std::cout << "\n";

    delete[] arrayCopy;
}

void ProcessAlgorithmMode(  void (*sortFunction)(int *&, const int &, unsigned long long &), 
                            const std::string &algorithmName,
                            const int &size, 
                            const int &dataOrderType, 
                            const std::string &dataOrderName, 
                            const bool &outputTime,
                            const bool &outputComparisons)
{
    int *array = new int[size];
    if (!array) {
        std::cerr << "Error: Can not allocate new memory\n";
        exit(1);
    }
    GenerateData(array, size, dataOrderType);

    writeArrayToFile(defaultInputFilePath, array, size);

    std::cout << "ALGORITHM MODE\n";
    std::cout << "Algorithm: " << algorithmName << "\n";
    std::cout << "Input size: " << size << "\n";
    std::cout << "Input order: " << dataOrderName << "\n";
    std::cout << "--------------------------------\n";

    unsigned long long comparisons = 0;
    double time = 0.0;
    TestSortAlgorithm(sortFunction, array, size, comparisons, time, outputTime, outputComparisons);
    writeArrayToFile(defaultOutputFilePath, array, size);

    if (outputTime)
        std::cout << "Running time: " << time << " milliseconds\n";
    if (outputComparisons)
        std::cout << "Comparisons: " << comparisons << "\n";

    delete[] array;
}


#endif