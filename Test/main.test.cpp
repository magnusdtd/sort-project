#include <gtest/gtest.h>
#include <fstream>

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

TEST(MainTest, Build) {
    // Build main.exe
    int buildCommand = system("g++ ./main.cpp ./include/DataGenerator.hpp ./include/sort.hpp ./include/sort.cpp -std=c++17 -o main");
    ASSERT_EQ(buildCommand, 0) << "Building main.exe failed";   
}

TEST(MainTest, Command_1) {
    std::string command = ".\\main.exe -a selection-sort input.txt -both";
    std::string output = runCommand(command);

    ASSERT_NE(output.find("ALGORITHM MODE"), std::string::npos);
    ASSERT_NE(output.find("Algorithm: selection-sort"), std::string::npos);
    ASSERT_NE(output.find("Input file: input.txt"), std::string::npos);
    ASSERT_NE(output.find("Running time:"), std::string::npos);
    ASSERT_NE(output.find("Comparisons:"), std::string::npos);
}

TEST(MainTest, Command_2) {
    std::string command = ".\\main.exe -a selection-sort 5000 -rand -time";
    std::string output = runCommand(command);

    ASSERT_NE(output.find("ALGORITHM MODE"), std::string::npos);
    ASSERT_NE(output.find("Algorithm: selection-sort"), std::string::npos);
    ASSERT_NE(output.find("Input size: 5000"), std::string::npos);
    ASSERT_NE(output.find("Input order: Randomize"), std::string::npos);
    ASSERT_NE(output.find("Running time:"), std::string::npos);
}

TEST(MainTest, Command_3) {
    std::string command = ".\\main.exe -a insertion-sort 7000 -comp";
    std::string output = runCommand(command);

    ASSERT_NE(output.find("ALGORITHM MODE"), std::string::npos);
    ASSERT_NE(output.find("Algorithm: insertion-sort"), std::string::npos);
    ASSERT_NE(output.find("Input size: 7000"), std::string::npos);
    ASSERT_NE(output.find("Comparisons:"), std::string::npos);
}

TEST(MainTest, Command_4) {
    std::string command = ".\\main.exe -c selection-sort insertion-sort input.txt";
    std::string output = runCommand(command);

    ASSERT_NE(output.find("COMPARE MODE"), std::string::npos);
    ASSERT_NE(output.find("Algorithm: selection-sort | insertion-sort"), std::string::npos);
    ASSERT_NE(output.find("Input file: input.txt"), std::string::npos);
    ASSERT_NE(output.find("Input size:"), std::string::npos);
    ASSERT_NE(output.find("Running time:"), std::string::npos);
    ASSERT_NE(output.find("Comparisons:"), std::string::npos);
}

TEST(MainTest, Command_5) {
    std::string command = ".\\main.exe -c selection-sort insertion-sort 1000 -nsorted";
    std::string output = runCommand(command);

    ASSERT_NE(output.find("COMPARE MODE"), std::string::npos);
    ASSERT_NE(output.find("Algorithm: selection-sort | insertion-sort"), std::string::npos);
    ASSERT_NE(output.find("Input size: 1000"), std::string::npos);
    ASSERT_NE(output.find("Input order: Nearly sorted"), std::string::npos);
    ASSERT_NE(output.find("Running time:"), std::string::npos);
    ASSERT_NE(output.find("Comparisons:"), std::string::npos);
}

