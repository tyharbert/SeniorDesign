#ifndef IMGLIB_HPP
#define IMGLIB_HPP

#include "bmp.hpp"

#include <stdexcept>

// Opens the file passed in
FILE* openFile(char*, char*);

// prints the files data as Hex
void readBMP(char*);

#endif