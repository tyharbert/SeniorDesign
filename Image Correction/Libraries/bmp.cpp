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

// FAST corner detection algorithm
void BMP::fast() {
    for (int y=3; y < this->height()-3; y++)
        for (int x=3; x < this->width()-3; x++) {
            if (this->is_corner(x,y))
                this->rows[y].pixels[x] = Pixel(0);
        }
}

// if the luminance of n of the 16 surrounding pixels
// are above or below the threshold luminance then a
// corner is detected.
bool BMP::is_corner(int x, int y) {
    // threshold of luminance value
    const static float threshold = 70;
    // number of contiguous pixels required
    const static int n = 10;
    
    // luminances limits for selected pixels
    float lum = this->rows[y].pixels[x].luminance();
    float max_lum = lum + threshold;
    float min_lum = lum - threshold;
    float temp_lum = 0;
    
    // count of pixels below or above
    int cnt = 0;
    // this is used to keep track of the first
    // count we get to add it back to the last
    // count we get to keep continuity around the
    // ends of the loop
    int begin_cnt = 0;
    
    y -= 3; // start with top center pixel
    for (int i=0; i<16; i++){
        
        // if it is outside of bounds count it, otherwise reset count
        temp_lum = this->rows[y].pixels[x].luminance();
        if (temp_lum < min_lum || temp_lum > max_lum) {
            if (i == 0)
                begin_cnt--;
            cnt++;
        } else {
            if (begin_cnt == -1)
                begin_cnt = cnt;
            cnt = 0;
        }
        
        // corner detected
        if (cnt >= n)
            return true;
        
        // these rules follow a pattern to make a cirlce
        // of 16 pixels around the selected pixel
        if (i < 3 || i > 12)
            x++;
        if (i > 4 && i < 11)
            x--;
        if (i > 8)
            y--;
        if (i > 0 && i < 7)
            y++;
    }
    
    // if no corner at this point, see if there
    // are enough contiguous from end and begining
    if ((begin_cnt + cnt) >= n)
        return true;
    
    return false;
}