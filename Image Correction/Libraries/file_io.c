#include "file_io.h"

struct tagBMP_Header{
    int temp;
};

// Opens the file passed in
FILE* openFile(char* f){
    // variable declarations and initializations
    FILE* in_f;
    
    BMP_Header b;

    // open image file
    in_f = fopen(f,"r");
    if (!in_f){
        printf("Error opening file...");
    }
    
    return in_f;
}

// prints the files data as Hex
void printFileDataHex(FILE* f){
    // variable declarations
    const int BUFFER_SIZE = 256;
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