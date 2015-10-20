#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256


/*
This function is used to realixe the h vector below from the 8 equations shown:

(x0 y0 1  0   0  0  -x0*x'0 -y0*x'0)   (h11)   (x'0)
(x1 y1 1  0   0  0  -x1*x'1 -y1*x'1)   (h12)   (x'1)
(x2 y2 1  0   0  0  -x2*x'2 -y2*x'2)   (h13)   (x'2)
(x3 y3 1  0   0  0  -x3*x'3 -y3*x'3) * (h21) = (x'3)
(0  0  0  x0  y0 1  -x0*y'0 -y0*y'0)   (h22)   (y'0)
(0  0  0  x1  y1 1  -x1*y'1 -y1*y'1)   (h23)   (y'1)
(0  0  0  x2  y2 1  -x2*y'2 -y2*y'2)   (h31)   (y'2)
(0  0  0  x3  y3 1  -x3*y'3 -y3*y'3)   (h32)   (y'3)

*/

// dynamically allocates a 2-d double matrix initialized to zero
// a double** must be passed by reference from main to keep it
// from being allocated into the stack memory
void zeros(double*** m, int rows, int cols){
    // create double* array of double*
    (*m) = (double**)calloc(rows,sizeof(double));

    for (int i=0; i<rows; i++)
        (*m)[i] = (double*)calloc(cols,sizeof(double));
}

// this will create the determinate of the array recursively
double** determinate(double** m, int rows, int cols){
    printf("%dx%d:\n",rows,cols);
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            printf("%f ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return m;
}

// Opens the file passed in
FILE* openFile(char* f){
    // variable declarations and initializations
    FILE* in_f;

    // open image file
    // TODO: when using CMAKE change this to read from a relative path...
    in_f = fopen(f,"r");
    if (!in_f){
        printf("Error opening file...");
    }
    
    return in_f;
}

// prints the files data as Hex
void printFileDataHex(FILE* f){
    // variable declarations
    unsigned char buffer[BUFFER_SIZE];
    int bytes_read = 0;

    // read a buffer of binary data of max size BUFFER_SIZE
    while ((bytes_read = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, f)) > 0){
        // print buffer as hex
        for (int i = 0; i < bytes_read; i++){
            printf("%x ", buffer[i]);
        }
        printf("\b\n");
    }
}

int main()
{   
    int rows = 3;
    int cols = 2;
    
    double** m;
    zeros(&m,rows,cols);
    determinate(m,rows,cols);

    return 0;
}
