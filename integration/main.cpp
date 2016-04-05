#include "imglib.hpp"
#include "xMessage.hpp"
extern "C"
{
#include "servo.h"
}

void transmitImageToBase();

int main()
{
	//Captures all the images from the locations in locations.txt
	//saves images in image folder called testing0.jpeg, testing1.jpeg, etc.
	CaptureSavedLocations("../motorcontrols/locations/locations.txt");

	//fucntions to convert .jpeg to .bmp

	//transforms gussets
	transformGusset("../images/test_in.bmp", "../images/test_out0.bmp");
	transformGusset("../images/test_in.bmp", "../images/test_out1.bmp");

	//function to convert .bmp to .jpeg

	//transmits all images to base station
	transmitImageToBase();
	return 0;
}


void transmitImageToBase()
{
        char *device = (char *)"/dev/ttyUSB1";
	int result;
        Serial xbee(device, 57600);
        Message msg(device);

        int fd = xbee.Open();
//TRANSMIT IMAGE 1
        std::cout << "Send Image signal\n";
        msg.sendingImage();

        std::cout << "Transmitting Image\n";
        result = XSend(fd, "../images/test_out0.jpeg");

        if(result == 0){
                std::cout << "Image transmitted successfully\n";
        }
        else{
                std::cout << "Error during image transmission\n";
        }
//TRANSMIT IMAGE 2
        std::cout << "Send Image signal\n";
        msg.sendingImage();

        std::cout << "Transmitting Image\n";
        result = XSend(fd, "../images/test_out1.jpeg");

        if(result == 0){
                std::cout << "Image transmitted successfully\n";
        }
        else{
                std::cout << "Error during image transmission\n";
        }

        xbee.Close();
}
