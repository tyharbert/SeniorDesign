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
std::string imgPath(std::string, int, std::string);

int main()
{
	int locations = 4; // max locations 4

	// remove amx of 4 existing images
	for (int i=0; i < locations; i++)
	  remove(imgPath("temp", i, ".jpeg").c_str());

	calibrationNeeded(); // checks if jumper is set to calibrate system

	//Captures all the images from the locations in locations.txt
	//saves images in image folder called testing0.jpeg, testing1.jpeg, etc.
	locations = CaptureSavedLocations("../motorcontrols/locations/locations.txt");

	std::cout << "locations " << locations << std::endl;
	if (locations == 0) {
		std::cout << "No locations saved. Add calibration jumper and reboot." << std::endl;
		return 1;
	}

	for (int i=0; i < locations; i++ ) {
	    //fucntions to convert .jpeg to .bmp
	    JPEG_to_BMP(imgPath("temp", i, ".jpeg").c_str(), imgPath("temp_in", i, ".bmp").c_str());

	    //transforms gussets
	    transformGusset(imgPath("temp_in", i, ".bmp").c_str(), imgPath("temp_out", i, ".bmp").c_str());

	    //function to convert .bmp to .jpeg
	    BMP_to_JPEG(imgPath("temp_out", i, ".bmp").c_str(), imgPath("temp_out", i, ".jpeg").c_str());

	    //transmits all images to base station
	    transmitImageToBase(imgPath("temp_out", i, ".jpeg").c_str());

	}

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

std::string imgPath(std::string name, int index, std::string extension) {
	const static std::string path = "../images/";

	return path + name + std::to_string(index) + extension;
}
