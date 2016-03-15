#ifndef BMP_HPP
#define BMP_HPP

#include <stdint.h>

#include "utils.hpp"
#include "corner.hpp"
#include "matrix.hpp"

// default color for empty pixel
const uint32_t DEFAULT_COLOR = 0xFF69B4;
const char DEFAULT_RED = (DEFAULT_COLOR) & 0xFF;
const char DEFAULT_GREEN = (DEFAULT_COLOR >> 8) & 0xFF;
const char DEFAULT_BLUE = (DEFAULT_COLOR >> 16) & 0xFF;

// 2-Bytes
struct Word {
    unsigned char b1;
    unsigned char b2;
    
    Word() { }
    Word(uint16_t d): b1(d), b2(d >> 8) { }
    // little endian (the way microsoft documents)
    uint16_t le() const { return b1 << 8 | b2; }
    // big endian
    uint16_t be() const { return b2 << 8 | b1; }
};

// 4-Bytes
struct DWord : Word {
    unsigned char b3;
    unsigned char b4;
    
    DWord(): Word() { }
    DWord(uint32_t d): Word(d), b3(d >> 16), b4(d >> 24) { }
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
    
    Pixel(): _red(DEFAULT_RED), _green(DEFAULT_GREEN), _blue(DEFAULT_BLUE) { }
    Pixel(char r, char g, char b): _red(r), _green(g), _blue(b) { }
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
    template<typename T>
    void transform(const BMP*, const Matrix<T>&, const Corners&, const Corners&);
    void average_surrounding(int, int);
    void fast(int,int,int,int,int*,bool(BMP::*)(int,int,int,int));
    bool fast_sw(int,int,int,int);
    bool fast_nw(int,int,int,int);
    bool fast_ne(int,int,int,int);
    bool fast_se(int,int,int,int);
    
public:
    BMP(const char*);
    template<typename T>
    BMP(const BMP*, const Matrix<T>&, const Corners&, const Corners&);
    ~BMP();
    int32_t width() const { return _dibHead._width.be(); }
    int32_t height() const { return _dibHead._height.be(); }
    void write(const char*);
    Corners fast();
};

// constructor for BMP created during transform
template<typename T>
inline BMP::BMP(const BMP* bmp, const Matrix<T>& H, const Corners& orig, const Corners& dest) {
    // calculate destination height and width
    int width = 1 + (dest._ne._x - dest._nw._x);
    int height = 1 + (dest._nw._y - dest._sw._y);

    // if a row is not divisible by 32 bits padding is added on
    _rowPadding = 4 - width*3%4;
    if (_rowPadding == 4) // padding can only be 0 to 3
        _rowPadding = 0;

    // calculating the size of the image in bytes
    int pixels_size = height * (width * 3 + _rowPadding);
    int total_size = 14 + bmp->_dibHead._size.be() + pixels_size;

    // copy headers
    _bmpHead = bmp->_bmpHead;
    _dibHead = bmp->_dibHead;

    // update headers
    _bmpHead._size = total_size;
    _dibHead._width = width;
    _dibHead._height = height;
    _dibHead._sizeOfBMP = pixels_size;
    _dibHead._xPixelsPerMeter = int_round(width/(rr_width_cm/100));
    _dibHead._yPixelsPerMeter = int_round(height/(rr_height_cm/100));
    
    // dynamically allocate rows
    rows = new Row[height];
    for(int i = 0; i < height; i++) {
        // dynamically allocate pixels
        rows[i].pixels = new Pixel[width];
        // dynamically allocate row padding
        if (_rowPadding > 0) {
            rows[i].padding = new unsigned char[_rowPadding];
        }
    }

    transform(bmp, H, orig, dest);
}

// executes the image transform using the transformation matrix
template<typename T>
void BMP::transform(const BMP* bmp, const Matrix<T>& H, const Corners& orig, const Corners& dest) {
    // get min and max positions in original image to search
    int min_x = (orig._nw._x < orig._sw._x ? orig._nw._x : orig._sw._x);
    int max_x = (orig._ne._x > orig._se._x ? orig._ne._x : orig._se._x);
    int min_y = (orig._sw._y < orig._se._y ? orig._sw._y : orig._se._y);
    int max_y = (orig._nw._y > orig._ne._y ? orig._nw._y : orig._ne._y);

    Matrix<T>* p;
    Point p_prime;

    for (int y = min_y; y <= max_y; y++)
        for (int x = min_x; x <= max_x; x++) {
            p = new Matrix<T>((T)x, (T)y);
            p_prime = (H*(*p)).get_3v_point();

            if (dest.inBounds(p_prime))
                this->rows[p_prime._y].pixels[p_prime._x] = bmp->rows[y].pixels[x];

            delete p;
        }

    for (int x = 0; x < width(); x++)
        for (int y = 0; y < height(); y++) {
            if (this->rows[y].pixels[x].to_uint32() == DEFAULT_COLOR)
                average_surrounding(x, y);
        }
}

#endif