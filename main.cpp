#include "Huffman.h"
#include <iostream>

int main() {
    Huffman huff;
    
    std::string inputFile = "input.txt";
    std::string compressedFile = "output.huff";
    std::string restoredFile = "restored.txt";

    std::cout << "1. Compressing " << inputFile << "...\n";
    huff.compress(inputFile, compressedFile);

    std::cout << "2. Decompressing " << compressedFile << "...\n";
    huff.decompress(compressedFile, restoredFile);

    std::cout << "3. Verification:\n";
    std::string command = "diff " + inputFile + " " + restoredFile;
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "SUCCESS! Files match perfectly.\n";
    } else {
        std::cout << "FAILURE! Files are different.\n";
    }

    return 0;
}