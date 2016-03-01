#ifndef XBEE_H
#define XBEE_H

#include "xSerial.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

int copy_file( const char* srcfilename, const char* dstfilename );


int main(){

//copy_file("tylerUseThisImage.jpeg", "copyImage.jpeg");

copy_file("test.txt", "copyTxt.txt");

return 0;
}

int copy_file( const char* srcfilename, const char* dstfilename )
  {
  long  len;
  char* buf = NULL;
  FILE* fp  = NULL;

  // Open the source file
  fp = fopen( srcfilename, "rb" );
  if (!fp) return 0;

  // Get its length (in bytes)
  if (fseek( fp, 0, SEEK_END ) != 0)  // This should typically succeed
    {
    fclose( fp );
    return 0;
    }

  len = ftell( fp );
  std::cout << len;
  rewind( fp );

  // Get a buffer big enough to hold it entirely
  buf = (char*)malloc( len );
  if (!buf)
    {
    fclose( fp );
    return 0;
    }

  // Read the entire file into the buffer
  if (!fread( buf, len, 1, fp ))
    {
    std::cout << "read file buffer cout";
    free( buf );
    fclose( fp );
    return 0;
    }

  fclose( fp );

  // Open the destination file
  fp = fopen( dstfilename, "wb" );
  if (!fp)
    {
    std::cout << "open file buffer cout";
    free( buf );
    return 0;
    }

  // Writes buffer over serial port
  int fd;
  fd = xserialOpen("/dev/ttyUSB0", 9600);
  serialWrite(fd, buf, len);


  // Write the entire buffer to file
  if (!fwrite( buf, len, 1, fp ))
    {
    free( buf );
    fclose( fp );
    return 0;
    }

  // All done -- return success
  fclose( fp );
  free( buf );
  return 1;
  }




#endif
