#include "bmp.hpp"

// constructor for Pixel class
Pixel::Pixel(uint32_t p) {
    _red = p & 255;
    _green = (p >> 8) & 255;
    _blue = (p >> 16) & 255;
}

// constructor for BMP class
BMP::BMP(const char* path) {
    FILE* f = openFile(path, "r");
    
    fread(&_bmpHead, sizeof(BMPHead), 1, f);
    fread(&_dibHead, sizeof(DIBHead), 1, f);
    
    int height = _dibHead._height.be();
    int width = _dibHead._width.be();
    
    rows = new Row[height];
    for(int i = 0; i < height; i++) {
        rows[i].pixels = new Pixel[width];
        fread(rows[i].pixels, sizeof(Pixel), width, f);
        fread(&rows[i].padding, sizeof(unsigned char), 1, f);
    }
    
    fclose(f);
}

// writes to a BMP class to a BMP file
void BMP::write(const char* path) {
    FILE* f = openFile(path, "w");
    
    fwrite(&_bmpHead, sizeof(BMPHead), 1, f);
    fwrite(&_dibHead, sizeof(DIBHead), 1, f);
    
    int height = _dibHead._height.be();
    int width = _dibHead._width.be();
    
    for(int i = 0; i < height; i++) {
        fwrite(rows[i].pixels, sizeof(Pixel), width, f);
        fwrite(&rows[i].padding, sizeof(unsigned char), 1, f);
    }
    
    fclose(f);
}

// test function inverts
void BMP::invert() {
    uint32_t height = _dibHead._height.be();
    uint32_t width = _dibHead._width.be();
    
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++) {
            rows[i].pixels[j] = Pixel(0xFFFFFFFF - rows[i].pixels[j].to_uint32());
        }
}