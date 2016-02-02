#include "imglib.hpp"

// Opens the file passed in
FILE* openFile(char* f, char* setting){
    // variable declarations and initializations
    FILE* in_f;

    // open image file
    in_f = fopen(f,setting);
    if (!in_f){
        throw std::runtime_error("Error opening file...");
    }
    
    return in_f;
}

// Opens BMP and returns data structure
void readBMP (char* f) {
    BMP bmp(openFile(f, "r"));
    
    for (int i=0; i < bmp.height(); i++)
        for (int j=0; j < bmp.width(); j++)
            printf("pixels[%d][%d]\t0x%06x\n",i,j,bmp.rows[i].pixels[j]);
}