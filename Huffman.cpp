#include "Huffman.h"
#include "BitHelper.h"

void Huffman::compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open input file\n";
        return;
    }

    std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    freqMap.clear();
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
    huffmanCodes.clear();
    generateCodes(root, "");

    BitWriter writer(outputFile);

    writer.writeInt(freqMap.size());
    for(auto pair : freqMap) {
        writer.writeByte(pair.first);
        writer.writeInt(pair.second);
    }

    for (char ch : text) {
        std::string code = huffmanCodes[ch];
        for (char bit : code) {
            writer.writeBit(bit - '0');
        }
    }
    
    std::cout << "Compression Complete! Saved to " << outputFile << "\n";
}

void Huffman::decompress(const std::string& inputFile, const std::string& outputFile) {
    BitReader reader(inputFile);
    
    int uniqueChars;
    if (!reader.readInt(uniqueChars)) {
        std::cerr << "Error: File is empty or invalid format.\n";
        return;
    }

    freqMap.clear();
    for (int i = 0; i < uniqueChars; ++i) {
        char ch;
        int freq;
        reader.readByte(ch);
        reader.readInt(freq);
        freqMap[ch] = freq;
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
    
    std::ofstream out(outputFile, std::ios::binary);
    Node* curr = root;
    
    int totalChars = root->freq; 
    
    while (totalChars > 0) {
        int bit = reader.readBit();
        if (bit == -1) break;

        if (bit == 0) curr = curr->left;
        else          curr = curr->right;

        if (!curr->left && !curr->right) {
            out.put(curr->ch);
            curr = root;
            totalChars--;
        }
    }

    std::cout << "Decompression Complete! Restored to " << outputFile << "\n";
    out.close();
}

void Huffman::generateCodes(Node* root, std::string code) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }
    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}