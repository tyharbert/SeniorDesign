#include "utils.hpp"

// Opens the file passed in
FILE* openFile(const char* f, const char* setting){
    // variable declarations and initializations
    FILE* in_f;

    // open image file
    in_f = fopen(f,setting);
    if (!in_f){
        throw std::runtime_error("Error opening file...");
    }
    
    return in_f;
}

// This asures that the first element is
// less than or equal to the second
void assert_le(int& first, int& second) {
	if (first > second) {
        std::swap(first, second);
	}
}

// void jpeg_to_bmp(const char* src, const char* dest) {
//     char buffer[256];
//     buffer = std::strcpy("djpeg ");
//     buffer = std::strcat(src);
//     buffer = std::strcat(" > ");
//     buffer = std::strcat(dest);
//     system(buffer);
// }

// void bmp_to_jpeg(const char* src, const char* dest) {
//     char buffer[256];
//     buffer = std::strcpy("cjpeg ");
//     buffer = std::strcat(src);
//     buffer = std::strcat(" > ");
//     buffer = std::strcat(dest);
//     system(buffer);
// }
