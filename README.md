# MiniZip: Huffman File Compressor (C++)

![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![Type](https://img.shields.io/badge/type-Lossless%20Compression-green.svg)

## ⚡ Overview

**MiniZip** is a command-line file compression tool built from scratch in C++. It implements the **Huffman Coding** algorithm to reduce file sizes by assigning shorter binary codes to frequent characters and longer codes to rare ones.

Unlike standard libraries that hide the complexity, this project implements the core **Bit-Packing Engine** manually, allowing for true bit-level I/O operations.

## 🚀 Key Features

### 1. Custom Bit-Packing Engine

Standard C++ `fstream` can only write bytes (8 bits). To achieve compression, I built a custom **BitWriter/BitReader** class that uses bitwise operators (`<<`, `>>`, `|`, `&`) to buffer individual bits and flush them to disk only when a full byte is formed.

### 2. Deterministic Tree Construction

- **Problem:** If two characters have the same frequency, standard priority queues might process them in random order, causing the Compressor and Decompressor to build different trees.
- **Solution:** I implemented a custom `Comparator` with a **tie-breaker mechanism** based on ASCII values. This guarantees mathematically identical trees every single time.

### 3. Header Metadata Handling

The compressed file includes a serialized Header containing the Frequency Table, allowing the decompressor to reconstruct the exact Huffman Tree needed for decoding without needing the original file.

## 🛠️ How It Works

1.  **Frequency Analysis:** Scans the input file to count character occurrences.
2.  **Build Tree (Greedy Algo):** Uses a `std::priority_queue` (Min-Heap) to iteratively combine the two smallest nodes until a binary tree is formed.
3.  **Generate Codes:** Traverses the tree (Left=`0`, Right=`1`) to generate unique prefix codes.
4.  **Bit Packing:** Compresses the data and writes it to a `.huff` binary file.

## 💻 How to Run

```bash
# Compile
g++ main.cpp Huffman.cpp -o minizip

# Run
./minizip
```

## Performance

- Original File: input.txt (ASCII encoding, 8 bits per char)
- Compressed File: output.huff (Variable-length encoding)
- Result: Typically achieves 40-50% compression on text-heavy files.
