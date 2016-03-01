#ifndef XBEE_H
#define XBEE_H

#include "xSerial.hpp"
//#include <iostream>
//#include <cstdlib>
//#include <wiringSerial.h>
using namespace std;


int main(){
	int fd;
	char *device = (char *)"/dev/ttyUSB0";

	fd = xserialOpen(device, 9600);
//	serialWrite(fd, "adc", 3);

	xserialClose(fd);


return 0;
}


#endif
