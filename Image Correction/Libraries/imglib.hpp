#ifndef IMGLIB_HPP
#define IMGLIB_HPP

#include <stdio.h>
#include <stdint.h>

// 2-Bytes
struct Word {
    unsigned char b1;
    unsigned char b2;
    
    // little endian (the way microsoft documents)
    uint16_t le() { return b1 << 8 | b2; }
    // big endian
    uint16_t be() { return b2 << 8 | b1; }
};

// 4-Bytes
struct DWord : Word {
    unsigned char b3;
    unsigned char b4;
    
    // little endian (the way microsoft documents)
    uint32_t le() { return Word::le() << 16 | b3 << 8 | b4; }
    // big endian
    uint32_t be() { return b4 << 24 | b3 << 16 | Word::be(); }
};

// BMP header class
class BMPHead {
private:
    Word _type;
    DWord _size;
    Word _unused1;
    Word _unused2;
    DWord _offset;

public:
    uint16_t type() { return _type.le(); }
    uint32_t size() { return _size.be(); }
    uint16_t unused1() { return _unused1.be(); }
    uint16_t unused2() { return _unused2.be(); }
    uint32_t offset() { return _offset.be(); }
};

// Windows DIB header class
class DIBHead {
private:
    DWord _size;
    DWord _width;
    DWord _height;
    Word _colorPlanes;
    Word _bitsPerPixel;
    DWord _compression;
    DWord _sizeOfBMP;

public:
    uint32_t size() { return _size.be(); }
    uint32_t width() { return _width.be(); }
    uint32_t height() { return _height.be(); }
    uint16_t colorPlanes() { return _colorPlanes.be(); }
    uint16_t bitsPerPixel() { return _bitsPerPixel.be(); }
    uint32_t compression() { return _compression.be(); }
    uint32_t sizeOfBMP() { return _sizeOfBMP.be(); }
};

// Opens the file passed in
FILE* openFile(char*);

// prints the files data as Hex
void readBMP(FILE*);

#endif