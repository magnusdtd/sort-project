#include "./include/sort.hpp"
#include "./include/DataGenerator.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <chrono>

const std::string defaultInputFilePath = "./input.txt";
const std::string defaultInputFilePath_1 = "./input_1.txt";
const std::string defaultInputFilePath_2 = "./input_2.txt";
const std::string defaultInputFilePath_3 = "./input_3.txt";
const std::string defaultInputFilePath_4 = "./input_4.txt";
const std::string defaultOutputFilePath = "./output.txt";

std::unordered_map<std::string, void (*)(int *&, const int &, unsigned long long &)> algorithms = {
    {"selection-sort", Sort::SelectionSort},
    {"insertion-sort", Sort::InsertionSort},
    {"bubble-sort", Sort::BubbleSort},
    {"shaker-sort", Sort::ShakerSort},
    {"shell-sort", Sort::ShellSort},
    {"heap-sort", Sort::HeapSort},
    {"merge-sort", Sort::MergeSort},
    {"quick-sort", Sort::QuickSort},
    {"counting-sort", Sort::CountingSort},
    {"radix-sort", Sort::RadixSort},
    {"flash-sort", Sort::FlashSort}};

std::unordered_map<std::string, std::string> inputOrderType = {
    {"-rand", "Randomize"},
    {"-nsorted", "Nearly sorted"},
    {"-sorted", "Sorted"},
    {"-rev", "Reversed"}};

void TestSortAlgorithm(void (*sortFunction)(int *&, const int &, unsigned long long &),
                       int *array,
                       const int &size,
                       unsigned long long &comparisons,
                       double &time)
{
    comparisons = 0;

    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(array, size, comparisons);
    auto end = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration<double, std::milli>(end - start).count();
}

void LoadArrayFromFile(const std::string &filePath, int *&array, int &size)
{
    std::ifstream inputBuffer(filePath);
    if (!inputBuffer)
    {
        std::cerr << "Error: Can't' open file " << filePath << "\n";
        exit(1);
    }
    inputBuffer >> size;
    array = new int[size];
    for (int i = 0; i < size; ++i)
        inputBuffer >> array[i];
    inputBuffer.close();
}

void WriteArrayToFile(const std::string &filePath, int *&array, const int &size)
{
    std::ofstream outputBuffer(filePath);
    if (!outputBuffer)
    {
        std::cerr << "Error: Can't open file" << filePath << "\n";
        exit(1);
    }
    outputBuffer << size << "\n";
    for (int i = 0; i < size; ++i)
        outputBuffer << array[i] << " ";
    outputBuffer << "\n";
    outputBuffer.close();
}

void RunAndLog(void (*sortFunction)(int *&, const int &, unsigned long long &),
               int *array,
               int size,
               const std::string &orderName,
               void (*generateData)(int *, int),
               bool outputTime,
               bool outputComparisons,
               const std::string &outputFilePath)
{
    unsigned long long comparisons = 0;
    double time = 0.0;

    generateData(array, size);
    if (!array) {
        std::cerr << "Array is null\n";
        exit(1);
    }
    WriteArrayToFile(outputFilePath, array, size);

    std::cout << "Input order: " << orderName << "\n";
    std::cout << "--------------------------------\n";
    TestSortAlgorithm(sortFunction, array, size, comparisons, time);
    if (outputTime)
        std::cout << "Running time: " << time << " milliseconds\n";
    if (outputComparisons)
        std::cout << "Comparisons: " << comparisons << "\n";
    std::cout << "\n";
}

void RunAlgorithmOnDifferentOrders(void (*sortFunction)(int *&, const int &, unsigned long long &), 
                                   const std::string &algorithmName, 
                                   int size, 
                                   bool outputTime, 
                                   bool outputComparisons)
{
    int *array = new int[size];
    if (!array) {
        std::cerr << "Array is null\n";
        exit(1);
    }

    std::cout << "ALGORITHM MODE\n";
    std::cout << "Algorithm: " << algorithmName << "\n";
    std::cout << "Input size: " << size << "\n\n";

    RunAndLog(sortFunction, array, size, "Randomize", GenerateRandomData, outputTime, outputComparisons, defaultInputFilePath_1);
    RunAndLog(sortFunction, array, size, "Nearly sorted", GenerateNearlySortedData, outputTime, outputComparisons, defaultInputFilePath_2);
    RunAndLog(sortFunction, array, size, "Sorted", GenerateSortedData, outputTime, outputComparisons, defaultInputFilePath_3);
    RunAndLog(sortFunction, array, size, "Reversed", GenerateReverseData, outputTime, outputComparisons, defaultInputFilePath_4);

    delete[] array;
}

void CompareAlgorithms(void (*sortFunction1)(int *&, const int &, unsigned long long &), 
                       void (*sortFunction2)(int *&, const int &, unsigned long long &), 
                       const std::string &algorithm1, 
                       const std::string &algorithm2, 
                       int *array, 
                       int size, 
                       const std::string &inputOrder = "")
{
    unsigned long long comparisons1 = 0, comparisons2 = 0;
    double time1 = 0.0, time2 = 0.0;

    int *arrayCopy = new int[size];
    std::copy(array, array + size, arrayCopy);
    TestSortAlgorithm(sortFunction1, arrayCopy, size, comparisons1, time1);

    std::copy(array, array + size, arrayCopy);
    TestSortAlgorithm(sortFunction2, arrayCopy, size, comparisons2, time2);

    std::cout << "COMPARE MODE\n";
    std::cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << "\n";
    if (!inputOrder.empty())
    {
        std::cout << "Input order: " << inputOrderType[inputOrder] << "\n";
    }
    std::cout << "Input size: " << size << "\n";
    std::cout << "--------------------------------\n";
    std::cout << "Running time: " << time1 << " | " << time2 << " milliseconds\n";
    std::cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << "\n";
    std::cout << "\n";

    delete[] arrayCopy;
}

void ProcessAlgorithmMode(const std::string &algorithm, 
                          int size, 
                          const std::string &inputOrder, 
                          bool outputTime, 
                          bool outputComparisons)
{
    int dataType = 0;
    if (inputOrder == "-rand")
        dataType = 0;
    else if (inputOrder == "-sorted")
        dataType = 1;
    else if (inputOrder == "-rev")
        dataType = 2;
    else if (inputOrder == "-nsorted")
        dataType = 3;
    else
    {
        std::cerr << "Error: Unknown input order " << inputOrder << "\n";
        exit(4);
    }

    int *array = new int[size];
    if (!array) {
        std::cerr << "Array is null\n";
        exit(1);
    }
    GenerateData(array, size, dataType);

    WriteArrayToFile(defaultInputFilePath, array, size);

    std::cout << "ALGORITHM MODE\n";
    std::cout << "Algorithm: " << algorithm << "\n";
    std::cout << "Input size: " << size << "\n";
    std::cout << "Input order: " << inputOrderType[inputOrder] << "\n";
    std::cout << "--------------------------------\n";

    unsigned long long comparisons = 0;
    double time = 0.0;
    TestSortAlgorithm(algorithms[algorithm], array, size, comparisons, time);
    WriteArrayToFile(defaultOutputFilePath, array, size);

    if (outputTime)
        std::cout << "Running time: " << time << " milliseconds\n";
    if (outputComparisons)
        std::cout << "Comparisons: " << comparisons << "\n";

    delete[] array;
}

int main(int argc, char *argv[])
{
    if (argc < 5 || argc > 7)
    {
        std::cerr << "Usage:\n";
        std::cerr << argv[0] << " -a [Algorithm] [Input file] [Output parameter(s)]\n";
        std::cerr << argv[0] << " -a [Algorithm] [Input size] [Input order] [Output parameter(s)]\n";
        std::cerr << argv[0] << " -a [Algorithm] [Input size] [Output parameter(s)]\n";
        std::cerr << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Input file]\n";
        std::cerr << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]\n";
        return 1;
    }

    std::string mode = argv[1], algorithm1, algorithm2;
    bool outputTime = false, outputComparisons = false;
    for (int i = 4; i < argc; ++i)
    {
        std::string param = argv[i];
        if (param == "-time")
            outputTime = true;
        else if (param == "-comp")
            outputComparisons = true;
        else if (param == "-both")
        {
            outputTime = true;
            outputComparisons = true;
        }
    }

    int *array = nullptr;
    int size = 0;

    if (mode == "-a")
    {
        std::string algorithm = argv[2];
        if (argc == 6)
        { // Command 2
            std::string inputOrder = argv[4];
            try
            {
                size = std::atoi(argv[3]);
            }
            catch (...)
            {
                std::cerr << "Error: argv[3] is not a number\n";
                exit(6);
            }
            if (size == 0)
                std::cerr << "Error: argv[3] is 0\n";
            ProcessAlgorithmMode(algorithm, size, inputOrder, outputTime, outputComparisons);
        }
        else if (argc == 5 && std::isdigit(argv[3][0]))
        { // Command 3
            try
            {
                size = std::atoi(argv[3]);
            }
            catch (...)
            {
                std::cerr << "Error: argv[3] is not a number\n";
                exit(6);
            }
            if (size == 0)
                std::cerr << "Error: argv[3] is 0\n";
            if (algorithms.find(algorithm) != algorithms.end())
                RunAlgorithmOnDifferentOrders(algorithms[algorithm], algorithm, size, outputTime, outputComparisons);
            else
            {
                std::cerr << "Error: Unknown algorithm " << algorithm << "\n";
                return 2;
            }
        }
        else
        { // Command 1
            LoadArrayFromFile(argv[3], array, size);
            std::cout << "ALGORITHM MODE\n";
            std::cout << "Algorithm: " << algorithm << "\n";
            std::cout << "Input file: " << argv[3] << "\n";
            std::cout << "Input size: " << size << "\n";
            std::cout << "--------------------------------\n";
            unsigned long long comparisons = 0;
            double time = 0;
            TestSortAlgorithm(algorithms[algorithm], array, size, comparisons, time);
            WriteArrayToFile("./output.txt", array, size);
            if (outputTime)
                std::cout << "Running time: " << time << " milliseconds\n";
            if (outputComparisons)
                std::cout << "Comparisons: " << comparisons << "\n";
            delete[] array;
        }
    }
    else if (mode == "-c")
    {
        algorithm1 = argv[2], algorithm2 = argv[3];
        if (argc == 5)
        { // Command 4
            LoadArrayFromFile(argv[4], array, size);
            CompareAlgorithms(algorithms[algorithm1], algorithms[algorithm2], algorithm1, algorithm2, array, size);
            delete[] array;
        }
        else if (argc == 6)
        { // Command 5
            try
            {
                size = std::atoi(argv[4]);
            }
            catch (...)
            {
                std::cerr << "Error: argv[3] is not a number\n";
                exit(6);
            }
            if (size == 0)
                std::cerr << "Error: argv[3] is 0\n";
            std::string inputOrder = argv[5];
            int dataType = 0;
            if (inputOrder == "-rand")
                dataType = 0;
            else if (inputOrder == "-sorted")
                dataType = 1;
            else if (inputOrder == "-rev")
                dataType = 2;
            else if (inputOrder == "-nsorted")
                dataType = 3;
            else
            {
                std::cerr << "Error: Unknown input order " << inputOrder << "\n";
                return 4;
            }
            array = new int[size];
            if (!array) {
                std::cerr << "Array is null\n";
                exit(1);
            }
            GenerateData(array, size, dataType);

            CompareAlgorithms(algorithms[algorithm1], algorithms[algorithm2], algorithm1, algorithm2, array, size, inputOrder);
            delete[] array;
        }
        else
        {
            std::cerr << "Error: Invalid number of arguments for compare mode\n";
            return 3;
        }
    }
    else
    {
        std::cerr << "Error: Unknown mode " << mode << "\n";
        return 1;
    }

    return 0;
}