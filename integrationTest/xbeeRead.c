#ifndef XSERIAL_HPP
#define XSERIAL_HPP
#include "xMessage.hpp"
//#include "xSerial.hpp"
//#include <wiringSerial.h>
#include <errno.h>
//#include "xmodem.c"
//#include <stdio.h>

int main(){

        char *device = (char *)"/dev/ttyUSB0";

        Serial xbee(device, 57600);
//        xbee.Open();
//	Message msg(device);
	char temp;
//	int fd;
	int result;
/*  if ((fd = serialOpen (device, 57600)) < 0)
  {
    printf ("Unable to open serial device:\n");
    return 1 ;
  }
*/

        int fd = xbee.Open();


for(;;)
{
    	while (xbee.DataAvail() > 0)
//	while (serialDataAvail(fd) > 0)
    	{
	  // temp = serialGetchar(fd);
	  temp = xbee.GetChar();
//	  std::cout << "Recedfdfd333ive Ready\n";
	  if(temp == '1')
	  {
//	    sleep(5);
//	    xbee.Open();
//	    msg.receiveReady();
	    std::cout << "Receive Ready\n";
//	    sleep(5);
//	    xbee.Open();
	    std::cout << "Receiving Image\n";
//	    xbee.Open();
	    result = XReceive(fd, "testReceive.jpeg", 0777);
	    if(result == 0)
		std::cout << "Image receive success!\n";
	    else
		std::cout << "error during image receive\n";
//     	    std::cout << temp;

	  }

	  fflush(stdout);
    	}
}

//serialClose(fd);

xbee.Close();
return 0;
}

#endif
