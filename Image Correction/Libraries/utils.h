#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

// dynamically allocates a 2-d double matrix initialized to zero
// a double** must be passed by reference from main to keep it
// from being allocated into the stack memory
void zeros(double***, int, int);

// deallocate a matrix
void dalloc(double***, int);

#endif