/*
 * serial.c:
 *	Example program to read bytes from the Serial line
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */
#ifndef XBEE_H
#define XBEE_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "xSerial.hpp"
#include <wiringSerial.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main ()
{
  int fd ;
  if ((fd = serialOpen ("/dev/ttyUSB1", 9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

void* buf= NULL;
FILE* fp = NULL;
long len = 3397;

// Loop, getting and printing characters
char temp;
int count = 0;
bool readComplete = false;
int bytesRead = 0;

fp = fopen("copyImage11.jpeg", "rwb");

  for (;;)
  {
	if(xserialDataAvail(fd) > 0)
	{
	bytesRead =  xserialDataAvail(fd);
	bytesRead = serialRead(fd, buf, len);
	std::cout << count+1;
	readComplete = true;
	}

	if (readComplete)
	{
	 std::cout << bytesRead;
//	 fp = fopen("copyImage22.jpeg", "rwb");
	 if (!fwrite(buf, bytesRead, 1, fp))
	 {
	 free(buf);
	 fclose(fp);
	 return 0;
	 }

	 fclose(fp);
	 free(buf);
	 return 1;
	}


//	temp = serialGetchar(fd);

//	if (temp == '\r'){
//	 puts("new line");
//	}
//	else if (temp == '5'){
//	puts("Enter 5!");
//	}

//    	else {


//	putchar (temp) ;
//	fflush (stdout) ;


//	putchar ('\n');
//    	}

  }
}

#endif
