#include "file_io.h"

#define BUFFER_SIZE 256

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