#include "SPI_shutdown.h"

void SPI_shutdown(void)
{
	unsigned char buffer[10] = {0};
	buffer[0] = 218;

	//wiringPiSetup();
	pinMode(SPI_CS, OUTPUT); // SPI CS0 is output
	digitalWrite(SPI_CS, HIGH);

	wiringPiSPISetup(SPI_channel, SPI_speed); // setup SPI

	digitalWrite(SPI_CS, LOW); // set CS low
	delay(1); // 1 ms
	wiringPiSPIDataRW(SPI_channel, buffer, 1); // SPI data exchange
	delay(1); // 1 ms
	digitalWrite(SPI_CS, HIGH); // set CS high

	system("sudo poweroff");

	return;
}
