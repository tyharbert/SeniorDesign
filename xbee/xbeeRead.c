#ifndef XMESSAGE_HPP
#define XMESSAGE_HPP
#include "xMessage.hpp"

int main(){

        char *device = (char *)"/dev/ttyUSB0";
        Serial xbee(device, 57600);
        int fd = xbee.Open();
	static int imageCounter = 1;
	const char* fileName;
	std::string tempFileName;
        std::ostringstream oss;
for(;;)
{
    	while (xbee.DataAvail() > 0)
    	{
	  char temp = xbee.GetChar();
	  if(temp == '1')
	  {
	    std::cout << "Attempting to receive\n";
	    oss.str(std::string());
	    oss << "Image" << imageCounter;
	    tempFileName = oss.str();
	    fileName = tempFileName.c_str();
//	    snprintf(fileName, "Image%03d.jpeg", imageCounter);

//	    fileName = ("image%d.jpeg", imageCounter);
	    int result = XReceive(fd, fileName, 0777);
	    if(result == 0)
		std::cout << "Image receive success!\n";
	    else
		std::cout << "error during image receive\n";
	    imageCounter++;
	  }

//	  fflush(stdout);
    	}
}

xbee.Close();
return 0;
}

#endif
