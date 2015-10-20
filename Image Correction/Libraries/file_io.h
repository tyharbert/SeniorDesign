#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

// Opens the file passed in
FILE* openFile(char*);

// prints the files data as Hex
void printFileDataHex(FILE*);

#endif