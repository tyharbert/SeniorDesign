#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdexcept>

// these are based on the reference rectangle
// ratio from height to width
const double rr_height_cm = 40.79875; // centimeters
const double rr_width_cm = 53.49875; // centimeters

// Opens the file passed in
FILE* openFile(const char*, const char*);

// gets a character and pushes it
// back into the stream so it is available for
// the next read
char fpeek(FILE*);

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

#endif