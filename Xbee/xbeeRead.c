#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
//#include <wiringPi.h>
#include <wiringSerial.h>
#include "xmodem.c"

using namespace std;

int main(){

        int fd;
        if ((fd = serialOpen ("/dev/ttyUSB0", 9600)) < 0)
          {
            fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
            return 1 ;
          }

/*      if (wiringPiSetup () == -1)
          {
            fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
            return 1 ;
          }
*/

        int result;
        result = XReceive(fd, "testImage.jpeg", 0777);

	std::cout << result << std::endl;
	return 0;
}