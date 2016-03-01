#ifndef XSERIAL_HPP
#define XSERIAL_HPP

#include "xSerial.hpp"
//#include <stdio.h>

int main(){

        char *device = (char *)"/dev/ttyUSB0";

        Serial xbee(device, 9600);
        xbee.Open();
	char temp;
for(;;)
{
    	while (xbee.DataAvail() > 0)
    	{
	  temp = xbee.GetChar();
	  std::cout << temp;
//	  putchar ( xbee.GetChar());
//    	  xbee.FlushData();
	  fflush(stdout);
    	}
}
xbee.Close();
return 0;
}

#endif
