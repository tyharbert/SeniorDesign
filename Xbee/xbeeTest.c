#ifndef XSERIAL_HPP
#define XSERIAL_HPP
#include <wiringSerial.h>
#include "xSerial.hpp"


int main(){

	char *device = (char *)"/dev/ttyUSB1";

  int fd;
  if ((fd = serialOpen ("/dev/ttyUSB1", 57600)) < 0)
  {
    printf ("Unable to open serial device:\n");
    return 1 ;
  }


//	int fd = serialOpen ("/dev/ttyUSB1", 115200);

//	Serial xbee(device, 115200);
//	xbee.Open();
//	xbee.PutMsg("This is a test");
//	xbee.Close();
	serialPuts (fd, "this is a test");
	printf("this is a test\n");
	serialClose(fd);
	return 0;



}

#endif
