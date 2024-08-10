#include "huffman.h"
#include <queue>
#include <bitset>
#include <sstream>
#include <iostream>

// HuffmanNode constructor
HuffmanNode::HuffmanNode(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}

// Build frequency table
void Huffman::buildFrequencyTable(const std::string &input) {
    for (char ch : input) {
        frequencyTable[ch]++;
    }
}

// Build the Huffman Tree
void Huffman::buildTree(const std::string &input) {
    buildFrequencyTable(input);

    auto compare = [](std::shared_ptr<HuffmanNode> left, std::shared_ptr<HuffmanNode> right) {
        return left->freq > right->freq;
    };

    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, decltype(compare)> pq(compare);

    for (auto &entry : frequencyTable) {
        pq.push(std::make_shared<HuffmanNode>(entry.first, entry.second));
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto sumNode = std::make_shared<HuffmanNode>('\0', left->freq + right->freq);
        sumNode->left = left;
        sumNode->right = right;
        pq.push(sumNode);
    }

    root = pq.top();
    generateCodes(root, "");
}

// Generate Huffman Codes
void Huffman::generateCodes(const std::shared_ptr<HuffmanNode> &node, const std::string &code) {
    if (!node) return;

    if (node->ch != '\0') {
        huffmanCodes[node->ch] = code;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

// Compress input string using Huffman coding
std::string Huffman::compress(const std::string &input) {
    buildTree(input);

    std::stringstream bitStream;
    for (char ch : input) {
        bitStream << huffmanCodes[ch];
    }

    std::string compressedData;
    while (bitStream.str().size() % 8 != 0) {
        bitStream << '0';  // Padding to make the bitstream a multiple of 8
    }

    std::string bits = bitStream.str();
    for (size_t i = 0; i < bits.size(); i += 8) {
        std::bitset<8> byte(bits.substr(i, 8));
        compressedData += static_cast<char>(byte.to_ulong());
    }

    return compressedData;
}

// Decompress the compressed data
std::string Huffman::decompress(const std::string &compressedData) {
    std::string bitString;
    for (char byte : compressedData) {
        bitString += std::bitset<8>(byte).to_string();
    }

    std::string decompressedData;
    auto currentNode = root;
    for (char bit : bitString) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        if (!currentNode->left && !currentNode->right) {
            decompressedData += currentNode->ch;
            currentNode = root;
        }
    }

    return decompressedData;
}
