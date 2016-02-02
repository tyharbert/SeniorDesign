#ifndef BMP_HPP
#define BMP_HPP

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

// holds xyz of color in specified color space
struct CIEXYZ {
    // 2 integer bits 30 fraction bits
    DWord x;
    DWord y;
    DWord z;
};

// holds CIEXYZ coords for each color
struct CIEXYZTripple {
    CIEXYZ red;
    CIEXYZ green;
    CIEXYZ blue;
};

// BMP header class
struct BMPHead {
    Word _type;
    DWord _size;
    Word _unused1;
    Word _unused2;
    DWord _offset;
};

// Windows DIB header class, V5
struct DIBHead {
    DWord _size;
    DWord _width;
    DWord _height;
    Word _planes;
    Word _bitsPerPixel;
    DWord _compression;
    DWord _sizeOfBMP;
    DWord _xPixelsPerMeter;
    DWord _yPixelsPerMeter;
    DWord _clrUsed;
    DWord _clrImportant;
    DWord _redMask;
    DWord _greenMask;
    DWord _blueMask;
    DWord _alphaMask;
    DWord _csType;
    CIEXYZTripple _endpoints;
    DWord _gammaRed;
    DWord _gammaGreen;
    DWord _gammaBlue;
    DWord _intent;
    DWord _profileData;
    DWord _profileSize;
    DWord _reserved;
};

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct Row {
    Pixel* pixels;
    unsigned char padding;
};

// BMP class
class BMP {
private:
    BMPHead _bmpHead;
    DIBHead _dibHead;
    
public:
    Row* rows;
    BMP(FILE*);
    int32_t width() { return _dibHead._width.be(); }
    int32_t height() { return _dibHead._height.be(); }
    
};

inline BMP::BMP(FILE* f) {
    fread(&_bmpHead, sizeof(BMPHead), 1, f);
    fread(&_dibHead, sizeof(DIBHead), 1, f);
    
    uint32_t height = _dibHead._height.be();
    uint32_t width = _dibHead._width.be();
    
    rows = new Row[height];
    for(uint32_t i = 0; i < height; i++) {
        rows[i].pixels = new Pixel[width];
        fread(rows[i].pixels, sizeof(Pixel), width, f);
        fread(&rows[i].padding, sizeof(unsigned char), 1, f);
    }
}

#endif