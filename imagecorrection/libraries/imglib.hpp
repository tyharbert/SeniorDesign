#ifndef IMGLIB_HPP
#define IMGLIB_HPP

#include "bmp.hpp"
#include "matrix.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

void transformGusset(const char*, const char*, bool = false);
void JPEG_to_BMP(std::string, std::string);
void BMP_to_JPEG(std::string, std::string);

#endif