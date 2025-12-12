#ifndef BIT_HELPER_H
#define BIT_HELPER_H

#include <iostream>
#include <fstream>

class BitWriter {
public:
    BitWriter(const std::string& filename) {
        file.open(filename, std::ios::binary); 
        buffer = 0;
        bitCount = 0;
    }

    ~BitWriter() {
        flush(); 
        if(file.is_open()) file.close();
    }

    void writeByte(unsigned char byte) {
        if (bitCount != 0) flush();
        file.put(byte);
    }

    void writeInt(int i) {
        if (bitCount != 0) flush();
        file.write(reinterpret_cast<const char*>(&i), sizeof(int));
    }

    void writeBit(int bit) {
        buffer = (buffer << 1) | bit;
        bitCount++;
        if (bitCount == 8) {
            file.put(buffer);
            buffer = 0;
            bitCount = 0;
        }
    }

    void flush() {
        if (bitCount > 0) {
            buffer = buffer << (8 - bitCount);
            file.put(buffer);
            buffer = 0;
            bitCount = 0;
        }
    }

private:
    std::ofstream file;
    unsigned char buffer;
    int bitCount;
};

class BitReader {
public:
    BitReader(const std::string& filename) {
        file.open(filename, std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
        }
        buffer = 0;
        bitCount = 0;
    }

    ~BitReader() {
        if(file.is_open()) file.close();
    }

    bool readInt(int& val) {
        return (bool)file.read(reinterpret_cast<char*>(&val), sizeof(int));
    }

    bool readByte(char& val) {
        return (bool)file.read(&val, 1);
    }

    int readBit() {
        if (bitCount == 0) {
            char c;
            if (!file.get(c)) return -1;
            buffer = (unsigned char)c;
            bitCount = 8;
        }

        int bit = (buffer >> (bitCount - 1)) & 1;
        bitCount--;
        return bit;
    }

private:
    std::ifstream file;
    unsigned char buffer;
    int bitCount;
};

#endif