#include "huffman.h"
#include <iostream>
#include <fstream>

std::string readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &filename, const std::string &data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(data.c_str(), data.size());
}

int main() {
    Huffman huffman;
    
    std::string inputFile = "input.txt";
    std::string compressedFile = "compressed.bin";
    std::string decompressedFile = "decompressed.txt";
    
    // Read input file
    std::string input = readFile(inputFile);
    
    // Compress the input file
    std::string compressedData = huffman.compress(input);
    writeFile(compressedFile, compressedData);
    std::cout << "File compressed and saved as " << compressedFile << std::endl;
    
    // Decompress the file
    std::string decompressedData = huffman.decompress(compressedData);
    writeFile(decompressedFile, decompressedData);
    std::cout << "File decompressed and saved as " << decompressedFile << std::endl;
    
    return 0;
}
