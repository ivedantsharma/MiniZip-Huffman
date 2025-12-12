#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f, Node* l = nullptr, Node* r = nullptr) 
        : ch(c), freq(f), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

class Huffman {
public:
    void run(std::string text);

private:
    void generateCodes(Node* root, std::string code);

    std::unordered_map<char, int> freqMap;

    std::unordered_map<char, std::string> huffmanCodes;
};

#endif