#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdexcept>

// Opens the file passed in
FILE* openFile(const char*, const char*);

// This asures that the first element is
// less than or equal to the second
void assert_le(int& first, int& second);

#endif