#include "./helper/test-function.hpp"

#include "./sorting-algorithm/selection-sort.hpp"
#include "./sorting-algorithm/insertion-sort.hpp"
#include "./sorting-algorithm/bubble-sort.hpp"
#include "./sorting-algorithm/shaker-sort.hpp"
#include "./sorting-algorithm/shell-sort.hpp"
#include "./sorting-algorithm/heap-sort.hpp"
#include "./sorting-algorithm/merge-sort.hpp"
#include "./sorting-algorithm/quick-sort.hpp"
#include "./sorting-algorithm/counting-sort.hpp"
#include "./sorting-algorithm/radix-sort.hpp"
#include "./sorting-algorithm/flash-sort.hpp"

std::unordered_map<std::string, void (*)(int *&, const int &, unsigned long long &)> algorithms = {
    {"selection-sort", SelectionSort},
    {"insertion-sort", InsertionSort},
    {"bubble-sort", BubbleSort},
    {"shaker-sort", ShakerSort},
    {"shell-sort", ShellSort},
    {"heap-sort", HeapSort},
    {"merge-sort", MergeSort},
    {"quick-sort", QuickSort},
    {"counting-sort", CountingSort},
    {"radix-sort", RadixSort},
    {"flash-sort", FlashSort}};

std::unordered_map<std::string, std::string> inputOrderName = {
    {"-rand", "Randomize"},
    {"-nsorted", "Nearly sorted"},
    {"-sorted", "Sorted"},
    {"-rev", "Reversed"}
};

std::unordered_map<std::string, int> inputOrderType = {
    {"-rand", RANDOM_DATA},
    {"-nsorted", NEARLY_SORTED_DATA},
    {"-sorted", SORTED_DATA},
    {"-rev", REVERSE_DATA}
};

int main(int argc, char *argv[])
{
    if (argc < 4 || argc > 7)
    {
        std::cerr << "Usage:\n";
        std::cerr << argv[0] << " -a [Algorithm] [Input file] [Output parameter(s)]\n";
        std::cerr << argv[0] << " -a [Algorithm] [Input size] [Input order] [Output parameter(s)]\n";
        std::cerr << argv[0] << " -a [Algorithm] [Input size] [Output parameter(s)]\n";
        std::cerr << argv[0] << " -a [Algorithm] [Output parameter(s)]\n";
        std::cerr << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Input file]\n";
        std::cerr << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]\n";
        return 1;
    }

    std::string mode = argv[1], algorithm1, algorithm2;
    bool outputTime = false, outputComparisons = false;
    for (int i = 3; i < argc; ++i)
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
        if (algorithms.find(algorithm) == algorithms.end()) {
            std::cerr << "Error: Unknown algorithm " << algorithm << "\n";
            return 2;
        }
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
            int dataType = 0;
            if (inputOrderType.find(inputOrder) == inputOrderType.end()) {
                std::cerr << "Error: Invalid input order\n";
                exit(4);
            } else {
                dataType = inputOrderType[inputOrder];
            }
            ProcessAlgorithmMode(algorithms[algorithm], algorithm, size, dataType, inputOrderName[inputOrder], outputTime, outputComparisons);
        }
        else if (argc == 5 && std::isdigit(argv[3][0]))
        { // Command 3: Run algorithm on different orders
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
        else if (argc == 4)
        { // Command 3: Run algorithm on different sizes and orders
            std::vector<int> sizes = {10000, 30000, 50000, 100000, 300000, 500000};
            for (const int &size : sizes)
                RunAlgorithmOnDifferentOrders(algorithms[algorithm], algorithm, size, outputTime, outputComparisons);
        }
        else
        { // Command 1
            readArrayFromFile(argv[3], array, size);
            std::cout << "ALGORITHM MODE\n";
            std::cout << "Algorithm: " << algorithm << "\n";
            std::cout << "Input file: " << argv[3] << "\n";
            std::cout << "Input size: " << size << "\n";
            std::cout << "--------------------------------\n";
            unsigned long long comparisons = 0;
            double time = 0;
            TestSortAlgorithm(algorithms[algorithm], array, size, comparisons, time, outputTime, outputComparisons);
            writeArrayToFile("./output.txt", array, size);
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
        if (algorithms.find(algorithm1) == algorithms.end()) {
            std::cerr << "Error: Unknown algorithm " << algorithm1 << "\n";
            return 2;
        } else if (algorithms.find(algorithm2) == algorithms.end()) {
            std::cerr << "Error: Unknown algorithm " << algorithm2 << "\n";
            return 2;            
        }
        if (argc == 5)
        { // Command 4
            // Validate the input path
            std::ifstream file(argv[4]);
            if (!file) {
                std::cerr << "Error: Invalid file path " << argv[4] << "\n";
                return 5;
            }
            file.close();
            readArrayFromFile(argv[4], array, size);
            CompareAlgorithms(algorithms[algorithm1], algorithms[algorithm2], algorithm1, algorithm2, array, size, argv[4], "");
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
            if (inputOrderType.find(inputOrder) == inputOrderType.end()) {
                std::cerr << "Error: Invalid input order\n";
                exit(4);
            } else {
                dataType = inputOrderType[inputOrder];
            }
            array = new int[size];
            if (!array) {
                std::cerr << "Error: Can not allocate new memory\n";
                exit(1);
            }
            GenerateData(array, size, dataType);

            CompareAlgorithms(algorithms[algorithm1], algorithms[algorithm2], algorithm1, algorithm2, array, size, "", inputOrderName[inputOrder]);
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

