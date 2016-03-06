#ifndef BMP_HPP
#define BMP_HPP

#include <stdint.h>

#include "utils.hpp"
#include "corner.hpp"
#include "matrix.hpp"

// 2-Bytes
struct Word {
    unsigned char b1;
    unsigned char b2;
    
    // little endian (the way microsoft documents)
    uint16_t le() const { return b1 << 8 | b2; }
    // big endian
    uint16_t be() const { return b2 << 8 | b1; }
};

// 4-Bytes
struct DWord : Word {
    unsigned char b3;
    unsigned char b4;
    
    // little endian (the way microsoft documents)
    uint32_t le() const { return Word::le() << 16 | b3 << 8 | b4; }
    // big endian
    uint32_t be() const { return b4 << 24 | b3 << 16 | Word::be(); }
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

// Holds pixel data
struct Pixel {
    unsigned char _red;
    unsigned char _green;
    unsigned char _blue;
    
    Pixel() { }
    Pixel(uint32_t);
    uint32_t to_uint32() { return 0 << 24 | _blue << 16 | _green << 8 | _red; }
    float luminance() { return 0.299f*(float)_red + 0.587f*(float)_green + 0.114f*(float)_blue; }
};

// Holds a row of pixels
struct Row {
    Pixel* pixels;
    unsigned char* padding;
};

// BMP class
class BMP {
private:
    BMPHead _bmpHead;
    DIBHead _dibHead;
    int _rowPadding;
    Row* rows;
    bool is_corner(int,int);
    void fast(int,int,int,int,int*,bool(BMP::*)(int,int,int,int));
    bool fast_sw(int,int,int,int);
    bool fast_nw(int,int,int,int);
    bool fast_ne(int,int,int,int);
    bool fast_se(int,int,int,int);
    
public:
    BMP(const char*);
    template<typename T>
    BMP(BMP*, Matrix<T>&, Corners, Corners);
    ~BMP();
    int32_t width() const { return _dibHead._width.be(); }
    int32_t height() const { return _dibHead._height.be(); }
    void write(const char*);
    Corners fast();
};

// constructor for BMP created during transform
template<typename T>
inline BMP::BMP(BMP* bmp, Matrix<T>& H, Corners orig, Corners dest) {
    // copy the headers before updating them
    _bmpHead = bmp->_bmpHead;
    _dibHead = bmp->_dibHead;

    int width = dest._nw._x - dest._ne._x;
    int height = dest._nw._y - dest._sw._y;

    // // if a row is not divisible by 32 bits padding is added on
    // _rowPadding = 4 - width*3%4;
    // if (_rowPadding == 4) // padding can only be 0 to 3
    //     _rowPadding = 0;
    
    // // dynamically allocate rows
    // rows = new Row[height];
    // for(int i = 0; i < height; i++) {
    //     // dynamically allocate pixels and read them in
    //     rows[i].pixels = new Pixel[width];
    //     //fread(rows[i].pixels, sizeof(Pixel), width, f);
    //     // dynamically allocate row padding and read it in
    //     if (_rowPadding > 0) {
    //         rows[i].padding = new unsigned char[_rowPadding];
    //         //fread(rows[i].padding, sizeof(unsigned char), _rowPadding, f);
    //     }
    // }
}

#endif