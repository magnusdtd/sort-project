#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> inputOrderType = {
    {"-rand", "Randomize"}, 
    {"-nsorted", "Nearly sorted"}, 
    {"-sorted", "Sorted"}, 
    {"-rev", "Reversed"}
};

std::string runCommand(const std::string &command) {
    std::string result;
    std::string tempFile = "temp_output.txt";
    std::string fullCommand = command + " > " + tempFile;

    int ret = std::system(fullCommand.c_str());
    if (ret != 0) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }

    std::ifstream file(tempFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            result += line + "\n";
        }
        file.close();
    }

    std::remove(tempFile.c_str());
    return result;
}

int main() {
    int buildCommand = system("g++ main.cpp ./helper/DataGenerator.hpp ./helper/ReadWriteData.hpp ./helper/test-function.hpp ./sorting-algorithm/selection-sort.hpp ./sorting-algorithm/insertion-sort.hpp ./sorting-algorithm/bubble-sort.hpp ./sorting-algorithm/shaker-sort.hpp ./sorting-algorithm/shell-sort.hpp ./sorting-algorithm/heap-sort.hpp ./sorting-algorithm/merge-sort.hpp ./sorting-algorithm/quick-sort.hpp ./sorting-algorithm/counting-sort.hpp ./sorting-algorithm/radix-sort.hpp ./sorting-algorithm/flash-sort.hpp -std=c++17 -o main");
    if (buildCommand) {
        std::cerr << "Building file failed\n";
        exit(1);
    } else {
        std::cout << "Building file completed\n";
    }

    std::vector<std::string> dataOrders = {"-rand", "-nsorted", "-sorted", "-rev"};
    std::vector<int> dataSizes = {10000, 30000, 50000, 100000, 300000, 500000};
    std::vector<std::string> sortingAlgorithms = {
        "selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", 
        "shell-sort", "heap-sort", "merge-sort", "quick-sort", 
        "counting-sort", "radix-sort", 
        "flash-sort"
    };

    std::ofstream outFile("result.csv");
    if (!outFile) {
        std::cerr << "Failed to open result.csv for writing\n";
        return 1;
    }

    // Write CSV header
    outFile << "Data Order,Data Size,Algorithm,Running Time (ms),Comparisons\n";

    for (const auto &dataOrder : dataOrders) {
        std::cout << "Data Order: " << dataOrder << "\n";
        for (const auto &dataSize : dataSizes) {
            std::cout << "\tData Size: " << dataSize << "\n";
            for (const auto &algorithm : sortingAlgorithms) {
                std::cout << "\t\tAlgorithm: " << algorithm << "\n";
                std::string command = ".\\main.exe -a " + algorithm + " " + std::to_string(dataSize) + " " + dataOrder + " -both";
                std::cout << "\t\t\tRunning command: " << command << "\n";
                std::string output = runCommand(command);

                // Parse the output to extract running time and comparisons
                std::istringstream outputStream(output);
                std::string line;
                std::string runningTime, comparisons;
                while (std::getline(outputStream, line)) {
                    if (line.find("Running time:") != std::string::npos) {
                        runningTime = line.substr(line.find(":") + 2);
                        // Remove " milliseconds" from running time
                        size_t pos = runningTime.find(" milliseconds");
                        if (pos != std::string::npos) {
                            runningTime = runningTime.substr(0, pos);
                        }
                    } else if (line.find("Comparisons:") != std::string::npos) {
                        comparisons = line.substr(line.find(":") + 2);
                    }
                }

                // Write to CSV file
                outFile << inputOrderType[dataOrder] << "," << dataSize << "," << algorithm << "," << runningTime << "," << comparisons << "\n";

                std::cout << "\t\t\tFinished running command: " << command << "\n";
            }
        }
    }

    outFile.close();
    std::cout << "Results written to result.csv\n";
    return 0;
}