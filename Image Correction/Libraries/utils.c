#include "utils.h"

// dynamically allocates a 2-d double matrix initialized to zero
// a double** must be passed by reference from main to keep it
// from being allocated into the stack memory
void zeros(double*** m, int rows, int cols){
    // allocate rows
    (*m) = (double**)calloc(rows,sizeof(double));

    // allocate columns
    for (int i=0; i<rows; i++)
        (*m)[i] = (double*)calloc(cols,sizeof(double));
}

// deallocate a matrix
void dalloc(double*** m, int rows){
    for (int i=0; i<rows; i++)
        free((*m)[i]);
    
    free((*m));
    (*m) = NULL;
}