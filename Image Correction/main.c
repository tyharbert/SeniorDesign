#include "Libraries/my_lib.h"

int main()
{   
    FILE* f = openFile("/Users/harbertt11/_The University of Akron/FALL 2015/Senior Design/Senior Design Trunk/Image Correction/images/1.bmp");
    processBMPHeader(f);
    printFileDataHex(f);

    return 0;
}

//int rows = 4;
//int cols = 4;
//
//double** m;
//zeros(&m,rows,cols);
//dalloc(&m,rows);
//
//if(m==NULL)
//    printf("dalloc success\n");