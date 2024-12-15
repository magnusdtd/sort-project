#ifndef READ_WRITE_DATA
#define READ_WRITE_DATA

#include <iostream>
#include <fstream>

void readArrayFromFile(const std::string &filePath, int *&array, int &size)
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

void writeArrayToFile(const std::string &filePath, int *&array, const int &size)
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

#endif