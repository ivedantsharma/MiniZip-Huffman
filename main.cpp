#include "Huffman.h"

int main() {
    Huffman huff;
    
    std::string testText = "abbcccddddeeeee";

    huff.run(testText);

    return 0;
}