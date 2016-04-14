#include "imglib.hpp"
#include "xMessage.hpp"
#include "calibration.cpp"
extern "C"
{
#include "SPI_shutdown.h"
}

#include <iostream>
#include <string>

#define JUMPER 18

void transmitImageToBase(const char*);
void calibrationNeeded();
const char* imgPath(std::string, int, std::string);

int main()
{
	int locations = 4; // max locations 4

	// remove amx of 4 existing images
	//for (int i=0; i < locations; i++)
//	  remove("../images/testing0.jpeg");
//	  remove("../images/testing1.jpeg");
//	  remove("../images/testing2.jpeg");
//	  remove("../images/testing3.jpeg");

	calibrationNeeded(); // checks if jumper is set to calibrate system

	//Captures all the images from the locations in locations.txt
	//saves images in image folder called testing0.jpeg, testing1.jpeg, etc.
	locations = CaptureSavedLocations("../motorcontrols/locations/locations.txt");

	//for (int i=0; i < locations; i++ ) {
	    //fucntions to convert .jpeg to .bmp
//	    JPEG_to_BMP("../images/testing0.jpeg", "../images/test_in0.bmp");
//	    JPEG_to_BMP("../images/testing1.jpeg", "../images/test_in1.bmp");
//	    JPEG_to_BMP("../images/testing2.jpeg", "../images/test_in2.bmp");

	    //transforms gussets
//	    transformGusset("../images/test_in0.bmp", "../images/test_out0.bmp");

	    //function to convert .bmp to .jpeg
//	    BMP_to_JPEG("../images/test_out0.bmp", "../images/test_out0.jpeg");

	    //transmits all images to base station
//	    transmitImageToBase("../images/test_out0.jpeg");
//	    transmitImageToBase("../images/testing1.jpeg");
//	    transmitImageToBase("../images/testing2.jpeg");
	//}

        //send PIC micro command to cut power after R Pi shutdown
	SPI_shutdown();

	return 0;
}


void transmitImageToBase(const char* file_path)
{
        char *device = (char *)"/dev/ttyUSB0";
	int result;
        Serial xbee(device, 57600);
        Message msg(device);

        int fd = xbee.Open();
//TRANSMIT IMAGE 1
        std::cout << "Send Image signal\n";
        msg.sendingImage();

        std::cout << "Attempting to Transmit Image\n";
        result = XSend(fd, file_path);

        if(result == 0){
                std::cout << "Image transmitted successfully\n";
        }
        else{
                std::cout << "Error during image transmission\nError code: " << result << "\n";
        }

        xbee.Close();
}

void calibrationNeeded()
{
	wiringPiSetupGpio(); // run wiringPi initalizations
	pinMode (JUMPER, INPUT); // set jumper pin as input
	pullUpDnControl(JUMPER, PUD_UP); // set jumper pin to use interal pull up (~50K) to 3.3V

	if( !digitalRead(JUMPER) ) // jumper pulling pin low?
	{
		calibrateLocations("../motorcontrols/locations/locations.txt"); // run calibration program
	}
}

const char* imgPath(std::string name, int index, std::string extension) {
	std::string path = "../images/";

	return (path + name + std::to_string(index) + extension).c_str();
}
