//#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
//#include <wiringPi.h>
#include <wiringSerial.h>
#include "xmodem.c"

//#include "xSerial.hpp"

//using namespace std;

int main(){

	int fd;
/*
	if ((fd = serialOpen ("/dev/ttyUSB1", 115200)) < 0)
	  {
	    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
	    return 1 ;
  	  }
*/
	fd = serialOpen ("/dev/ttyUSB1", 57600);

	int result;
	result = XSend(fd, "testImage.jpeg");
	printf("%d", result);
//	std::cout << result << std::endl;

	return 0;



}
