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
		int temp = second;
		second = first;
		first = temp;
	}
}
