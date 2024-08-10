#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class HuffmanNode {
public:
    char ch;
    int freq;
    std::shared_ptr<HuffmanNode> left, right;

    HuffmanNode(char ch, int freq);
};

class Huffman {
public:
    std::unordered_map<char, std::string> huffmanCodes;
    std::shared_ptr<HuffmanNode> root;

    void buildTree(const std::string &input);
    std::string compress(const std::string &input);
    std::string decompress(const std::string &compressedData);
    
private:
    void buildFrequencyTable(const std::string &input);
    void generateCodes(const std::shared_ptr<HuffmanNode> &node, const std::string &code);
    std::unordered_map<char, int> frequencyTable;
};

#endif // HUFFMAN_H
