#include "imglib.hpp"

// Opens the file passed in
FILE* openFile(char* f){
    // variable declarations and initializations
    FILE* in_f;

    // open image file
    in_f = fopen(f,"r");
    if (!in_f){
        printf("Error opening file...");
    }
    
    return in_f;
}

// prints the files data as Hex
void readBMP(FILE* f){
    // variable declarations
    const int BUFFER_SIZE = 256;
    unsigned char buffer[BUFFER_SIZE];
    int bytes_read = 0;
    
    BMPHead bmpHead;
    DIBHead dibHead;
    
    bytes_read = fread(&bmpHead, sizeof(BMPHead), 1, f);
    
    bytes_read = fread(&dibHead, sizeof(DIBHead), 1, f);
    
    printf("0x%04x, %u\n", bmpHead.type(), bmpHead.type());
    printf("0x%08x, %u\n", bmpHead.size(), bmpHead.size());
    printf("0x%04x, %u\n", bmpHead.unused1(), bmpHead.unused1());
    printf("0x%04x, %u\n", bmpHead.unused2(), bmpHead.unused2());
    printf("0x%08x, %u\n\n", bmpHead.offset(), bmpHead.offset());
    
    printf("0x%08x, %u\n", dibHead.size(), dibHead.size());
    printf("0x%08x, %u\n", dibHead.width(), dibHead.width());
    printf("0x%08x, %u\n", dibHead.height(), dibHead.height());
    printf("0x%04x, %u\n", dibHead.colorPlanes(), dibHead.colorPlanes());
    printf("0x%04x, %u\n", dibHead.bitsPerPixel(), dibHead.bitsPerPixel());
    printf("0x%08x, %u\n", dibHead.compression(), dibHead.compression());
    printf("0x%08x, %u\n\n", dibHead.sizeOfBMP(), dibHead.sizeOfBMP());
    
//    // read a buffer of binary data of max size BUFFER_SIZE
//    while ((bytes_read = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, f)) > 0){
//        // print buffer as hex
//        for (int i = 0; i < bytes_read; i++){
//            printf("0x%02x ", buffer[i]);
//        }
//        
//        printf("\b\n");
//    }
}