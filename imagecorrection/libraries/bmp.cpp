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
    fread(&_dibHead, sizeof(char), fpeek(f), f); // dib header size can vary
    
    if (_dibHead._bitsPerPixel.be() != 24) {
        std::runtime_error("need 24 bits per pixel");
    }
    
    int height = _dibHead._height.be();
    int width = _dibHead._width.be();
    
    // if a row is not divisible by 32 bits padding is added on
    _rowPadding = 4 - width*3%4;
    if (_rowPadding == 4) // padding can only be 0 to 3
        _rowPadding = 0;

    // dynamically allocate rows
    rows = new Row[height];
    for(int i = 0; i < height; i++) {
        // dynamically allocate pixels and read them in
        rows[i].pixels = new Pixel[width];
        fread(rows[i].pixels, sizeof(Pixel), width, f);
        // dynamically allocate row padding and read it in
        if (_rowPadding > 0) {
            rows[i].padding = new unsigned char[_rowPadding];
            fread(rows[i].padding, sizeof(unsigned char), _rowPadding, f);
        }
    }
    
    fclose(f);
}

// destructor
BMP::~BMP() {
    for (int r=0; r < _dibHead._height.be(); r++) {
        delete rows[r].pixels;
        delete rows[r].padding;
    }
    delete rows;
}

// writes to a BMP class to a BMP file
void BMP::write(const char* path) {
    FILE* f = openFile(path, "w");
    
    fwrite(&_bmpHead, sizeof(BMPHead), 1, f);
    fwrite(&_dibHead, sizeof(char), _dibHead._size.be(), f); // dib header size can vary
    
    int height = _dibHead._height.be();
    int width = _dibHead._width.be();
    
    for(int i = 0; i < height; i++) {
        fwrite(rows[i].pixels, sizeof(Pixel), width, f);
        if (_rowPadding > 0)
            fwrite(rows[i].padding, sizeof(unsigned char), _rowPadding, f);
    }
    
    fclose(f);
}

// averages the surrounding pixels that are not the default color
void BMP::average_surrounding(int x, int y) {
    uint32_t count = 0;
    uint32_t red_sum = 0;
    uint32_t green_sum = 0;
    uint32_t blue_sum = 0;

    y++; // start with pixel above current

    for (int i=0; i < 8; i++) {
        // must be within image
        if (x >= 0 && x < width() && y >= 0 && y < height()) {
            // if it is not the default color add it to the average
            if (this->rows[y].pixels[x].to_uint32() != DEFAULT_COLOR) {
                count++;
                red_sum += this->rows[y].pixels[x]._red;
                green_sum += this->rows[y].pixels[x]._green;
                blue_sum += this->rows[y].pixels[x]._blue;
            }
        }

        // these rules follow a pattern to make a cirlce
        // of 8 pixels around the selected pixel
        if (i < 1 || i > 6)
            x++;
        if (i > 2 && i < 5)
            x--;
        if (i > 0 && i < 3)
            y--;
        if (i > 4 && i < 7)
            y++;
    }

    y--; // set back to current pixel
    
    this->rows[y].pixels[x] = Pixel(int_round(((float)red_sum)/count), int_round(((float)green_sum)/count), int_round(((float)blue_sum)/count));
}

// FAST corner detection algorithm
Corners BMP::fast() {
    int corners[4][2] = {{0}}; // intialized to 0
    
    int min_x = 13;
    int max_x = this->width() - 13;
    int min_y = 13;
    int max_y = this->height() - 13;
        
    this->fast(min_x, max_x/2, min_y, max_y/2, corners[0], &BMP::fast_sw);
    this->fast(min_x, max_x/2, max_y/2, max_y, corners[1], &BMP::fast_nw);
    this->fast(max_x/2, max_x, max_y/2, max_y, corners[2], &BMP::fast_ne);
    this->fast(max_x/2, max_x, min_y, max_y/2, corners[3], &BMP::fast_se);

    // return the Corners object
    return Corners(corners);
}

// FAST corner detection for quadrants of the image
void BMP::fast(int x_min, int x_max, int y_min, int y_max, int* corner, bool(BMP::*condit)(int,int,int,int)){
    for (int y=y_min; y < y_max; y++)
        for (int x=x_min; x < x_max; x++) {
            if (this->is_corner(x,y)) {
                if ((!corner[0] && !corner[1]) || (this->*condit)(x, y, corner[0], corner[1])) {
                    corner[0] = x;
                    corner[1] = y;
                }
            }
        }
}

// SW quadrant condition to compare current corner
bool BMP::fast_sw(int x, int y, int xCorner, int yCorner) {    
    return (x+y) < (xCorner+yCorner);
}

// NW quadrant condition to compare current corner
bool BMP::fast_nw(int x, int y, int xCorner, int yCorner) {
    return (y-x) > (yCorner-xCorner);
}

// NE quadrant condition to compare current corner
bool BMP::fast_ne(int x, int y, int xCorner, int yCorner) {
    return (x+y) > (xCorner+yCorner);
}

// SE quadrant condition to compare current corner
bool BMP::fast_se(int x, int y, int xCorner, int yCorner) {
    return (x-y) > (xCorner-yCorner);
}

// if the luminance of n contiguous of the 16 surrounding pixels
// are above or below the threshold luminance then a
// corner is detected.
bool BMP::is_corner(int x, int y) {
    // luminances limits for selected pixels
    float lum = this->rows[y].pixels[x].luminance();
    float max_lum = lum + FAST_THRESHOLD;
    float min_lum = lum - FAST_THRESHOLD;
    float temp_lum = 0;
    
    // count of pixels below or above
    int cnt = 0;
    // this is used to keep track of the first
    // count we get to add it back to the last
    // count we get to keep continuity around the
    // ends of the circle
    int begin_cnt = 0;
    
    y -= 3; // start with bottom center pixel
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
        if (cnt >= FAST_CONTIG)
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
    if ((begin_cnt + cnt) >= FAST_CONTIG)
        return true;
    
    return false;
}
