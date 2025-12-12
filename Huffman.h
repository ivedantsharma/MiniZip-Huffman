#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include "BitHelper.h"

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f, Node* l = nullptr, Node* r = nullptr) 
        : ch(c), freq(f), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        if (l->freq != r->freq) return l->freq > r->freq;
        return l > r;
    }
};

class Huffman {
public:
    void compress(const std::string& inputFile, const std::string& outputFile);
    void decompress(const std::string& inputFile, const std::string& outputFile);

private:
    void generateCodes(Node* root, std::string code);
    
    std::map<char, int> freqMap;
    std::map<char, std::string> huffmanCodes;
};

#endif