#ifndef XMESSAGE_HPP
#define XMESSAGE_HPP
//#include <wiringSerial.h>
//#include "xSerial.hpp"
#include "xMessage.hpp"
//#include "xmodem.c"
int main(){

	char *device = (char *)"/dev/ttyUSB1";

  int fd;
/*
  if ((fd = serialOpen ("/dev/ttyUSB1", 57600)) < 0)
  {
    printf ("Unable to open serial device:\n");
    return 1 ;
  }
*/
	Serial xbee(device, 57600);
	Message msg;

//	int fd = serialOpen ("/dev/ttyUSB1", 115200);

//	Serial xbee(device, 115200);
//	xbee.Open();
//	xbee.PutMsg("This is a test");
//	xbee.Close();

//	serialPuts (fd, "this is a test");
//	printf("this is a test\n");

//	Message msg;
	int result;
	msg.sendingImage();
	fd = xbee.Open();
	std::cout << "Send Image signal\n";
	sleep(2);
	std::cout << "Transmitting image\n";
		result = XSend(fd, "testImage.jpeg");
		if(result == 0){
			std::cout << "Image transmitted successfully\n";
		}
		else{
			std::cout << "Error during image transmission\n";
		}
//		}

//		else
//			std::cout << "timed out\n";
//	}
//}
xbee.Close();
	//}




//	serialPuts (fd, "1");

//	printf("output 1\n");

//	serialClose(fd);
	return 0;



}

#endif
