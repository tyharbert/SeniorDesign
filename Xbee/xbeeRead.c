#ifndef XSERIAL_HPP
#define XSERIAL_HPP

#include "xSerial.hpp"
#include <wiringSerial.h>
#include <errno.h>
//#include <stdio.h>

int main(){
/*
        char *device = (char *)"/dev/ttyUSB0";

        Serial xbee(device, 115200);
        xbee.Open();
*/
	char temp;
	int fd;
  if ((fd = serialOpen ("/dev/ttyUSB0", 57600)) < 0)
  {
    printf ("Unable to open serial device:\n");
    return 1 ;
  }


//        int fd = serialOpen ("/dev/ttyUSB0", 115200);


for(;;)
{
//    	while (xbee.DataAvail() > 0)
	while (serialDataAvail(fd) > 0)
    	{
	  temp = serialGetchar(fd);
//	  temp = xbee.GetChar();
	  std::cout << temp;
//	  putchar ( xbee.GetChar());
//    	  xbee.FlushData();
	  fflush(stdout);
    	}
}

serialClose(fd);

//xbee.Close();
return 0;
}

#endif
