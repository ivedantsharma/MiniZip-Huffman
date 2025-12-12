#include "Huffman.h"

void Huffman::run(std::string text) {
    for (char ch : text) {
        freqMap[ch]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    generateCodes(root, "");

    std::cout << "--- Huffman Codes ---\n";
    for (auto pair : huffmanCodes) {
        std::cout << pair.first << " : " << pair.second << "\n";
    }

    std::cout << "\nOriginal String: " << text << "\n";
    std::cout << "Encoded String: ";
    for (char ch : text) {
        std::cout << huffmanCodes[ch];
    }
    std::cout << "\n";
}

void Huffman::generateCodes(Node* root, std::string code) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}