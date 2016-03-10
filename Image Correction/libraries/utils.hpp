#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdexcept>
#include <cstring>

// Opens the file passed in
FILE* openFile(const char*, const char*);

// This asures that the first element is
// less than or equal to the second
void assert_le(int& first, int& second);

// round to an integer
template<typename T>
inline int int_round(T val) {
	int temp = (int)val;
	T d = val - temp;
	if (d < 0.5)
		return temp;
	else
		return temp+1;
}

// void jpeg_to_bmp(const char*, const char *);

// void bmp_to_jpeg(const char*, const char *);

#endif