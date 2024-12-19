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

void TestSortAlgorithm( void (*elapsedTimeSortFunction)(int *&, const int &),
                        void (*countComparisonSortFunction)(int *&, const int &, unsigned long long &),
                        int *array, 
                        const int &size, 
                        unsigned long long &comparisons, 
                        double &time, 
                        const bool &outputTime, 
                        const bool &outputComparisons)
{
    comparisons = 0, time = 0.f;
    if (outputTime && outputComparisons) {

        auto start = std::chrono::high_resolution_clock::now();
        elapsedTimeSortFunction(array, size);
        auto end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double, std::milli>(end - start).count();

        countComparisonSortFunction(array, size, comparisons);

    } else if (!outputTime && outputComparisons) {
        countComparisonSortFunction(array, size, comparisons);
    } else if (outputTime && !outputComparisons) {
        auto start = std::chrono::high_resolution_clock::now();
        elapsedTimeSortFunction(array, size);
        auto end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double, std::milli>(end - start).count();
    }

}

void RunAndLog( void (*elapsedTimeSortFunction)(int *&, const int &),
                void (*countComparisonSortFunction)(int *&, const int &, unsigned long long &), 
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
    TestSortAlgorithm(elapsedTimeSortFunction, countComparisonSortFunction, array, size, comparisons, time, outputTime, outputComparisons);
    if (outputTime)
        std::cout << "Running time: " << time << " milliseconds\n";
    if (outputComparisons)
        std::cout << "Comparisons: " << comparisons << "\n";
    std::cout << "\n";
}

void RunAlgorithmOnDifferentOrders( void (*elapsedTimeSortFunction)(int *&, const int &),
                                    void (*countComparisonSortFunction)(int *&, const int &, unsigned long long &), 
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

    RunAndLog(elapsedTimeSortFunction, countComparisonSortFunction, array, size, "Randomize", RANDOM_DATA, outputTime, outputComparisons, defaultInputFilePath_1);
    RunAndLog(elapsedTimeSortFunction, countComparisonSortFunction, array, size, "Nearly sorted", NEARLY_SORTED_DATA, outputTime, outputComparisons, defaultInputFilePath_2);
    RunAndLog(elapsedTimeSortFunction, countComparisonSortFunction, array, size, "Sorted", SORTED_DATA, outputTime, outputComparisons, defaultInputFilePath_3);
    RunAndLog(elapsedTimeSortFunction, countComparisonSortFunction, array, size, "Reversed", REVERSE_DATA, outputTime, outputComparisons, defaultInputFilePath_4);

    delete[] array;
}

void CompareAlgorithms( void (*elapsedTimeSortFunction1)(int *&, const int &),
                        void (*countComparisonSortFunction1)(int *&, const int &, unsigned long long &), 
                        void (*elapsedTimeSortFunction2)(int *&, const int &),
                        void (*countComparisonSortFunction2)(int *&, const int &, unsigned long long &),  
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
    TestSortAlgorithm(  elapsedTimeSortFunction1, 
                        countComparisonSortFunction1, 
                        arrayCopy, 
                        size, 
                        comparisons1, 
                        time1, 
                        true, 
                        true
    );

    std::copy(array, array + size, arrayCopy);
    TestSortAlgorithm(  elapsedTimeSortFunction2, 
                        countComparisonSortFunction2, 
                        arrayCopy, 
                        size, 
                        comparisons2, 
                        time2, 
                        true, 
                        true
    );

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

void ProcessAlgorithmMode(  void (*elapsedTimeSortFunction)(int *&, const int &),
                            void (*countComparisonSortFunction)(int *&, const int &, unsigned long long &), 
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
    TestSortAlgorithm(elapsedTimeSortFunction, countComparisonSortFunction, array, size, comparisons, time, outputTime, outputComparisons);
    writeArrayToFile(defaultOutputFilePath, array, size);

    if (outputTime)
        std::cout << "Running time: " << time << " milliseconds\n";
    if (outputComparisons)
        std::cout << "Comparisons: " << comparisons << "\n";

    delete[] array;
}

void runAlgorithmWithDifferentOrdersAndSizes(void (*elapsedTimeFunc)(int *&, const int &), 
                                             void (*countComparisonFunc)(int *&, const int &, unsigned long long &), 
                                             const std::string &algorithm, 
                                             bool outputTime, 
                                             bool outputComparisons) 
{
    std::vector<int> orders = {RANDOM_DATA, NEARLY_SORTED_DATA, SORTED_DATA, REVERSE_DATA};
    std::vector<int> sizes = {10000, 30000, 50000, 100000, 300000, 500000};
    std::vector<std::string> orderName = {"Randomize", "Nearly sorted", "Sorted", "Reversed"};

    for (int i = 0; i < orders.size(); i++) {
        for (const auto &size : sizes) {
            int *array = new int[size];
            GenerateData(array, size, orders[i]);
            ProcessAlgorithmMode(elapsedTimeFunc, countComparisonFunc, algorithm, size, orders[i], orderName[i],outputTime, outputComparisons);
            std::cout << "\n";
            delete[] array;
        }
    }
}

void compareAlgorithmsWithDifferentOrdersAndSizes(void (*elapsedTimeFunc1)(int *&, const int &), 
                                                  void (*countComparisonFunc1)(int *&, const int &, unsigned long long &), 
                                                  void (*elapsedTimeFunc2)(int *&, const int &), 
                                                  void (*countComparisonFunc2)(int *&, const int &, unsigned long long &), 
                                                  const std::string &algorithm1, 
                                                  const std::string &algorithm2, 
                                                  bool outputTime, 
                                                  bool outputComparisons) 
{
    std::vector<int> orders = {RANDOM_DATA, NEARLY_SORTED_DATA, SORTED_DATA, REVERSE_DATA};
    std::vector<int> sizes = {10000, 30000, 50000, 100000, 300000, 500000};
    std::vector<std::string> orderName = {"Randomize", "Nearly sorted", "Sorted", "Reversed"};
    
    for (int i = 0; i < orders.size(); i++) {
        for (const auto &size : sizes) {
            int *array = new int[size];
            GenerateData(array, size, orders[i]);
            CompareAlgorithms(elapsedTimeFunc1, countComparisonFunc1, elapsedTimeFunc2, countComparisonFunc2, algorithm1, algorithm2, array, size, "", orderName[i]);
            delete[] array;
        }
    }
}

#endif