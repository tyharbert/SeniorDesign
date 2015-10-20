#include "imglib.h"


// this will create the determinate of the array recursively
void determinate(double** m, int rows, int cols){
    printf("%dx%d:\n",rows,cols);
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            printf("%f ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}