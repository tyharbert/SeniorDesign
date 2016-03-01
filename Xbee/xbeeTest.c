#ifndef XSERIAL_HPP
#define XSERIAL_HPP

#include "xSerial.hpp"


int main(){

	char *device = (char *)"/dev/ttyUSB1";

	Serial xbee(device, 9600);
//	xbee.Open();
	xbee.PutMsg("This is a test");
//	xbee.Close();
	return 0;



}

#endif
