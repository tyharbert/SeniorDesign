#include <glib.h>
#include <glib/gprintf.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wiringPi.h>

const char addr = 0b10010000;        // The I2C address of the ADC
const gchar *buffer;
	
void I2C_init(int file) {
    char filename[40];

    sprintf(filename,"/dev/i2c-1");
    if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }

    if (ioctl(file,I2C_SLAVE,addr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }

	I2C_write(file, addr); //write address of ADC
	I2C_write(file, 0b00000001);  //point to ADC configuration register
	I2C_write(file, 0b11000101);  //set MSB of ADC configureation register
	I2C_write(file, 0b10000011);  //set LSB of ADC configureation register
	
	
	
    char buf[10] = {0};
    float data;
    char channel;

	
    for(int i = 0; i<4; i++) {
        // Using I2C Read
        if (read(file,buf,2) != 2) {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            buffer = g_strerror(errno);
            printf(buffer);
            printf("\n\n");
        } else {
            data = (float)((buf[0] & 0b00001111)<<8)+buf[1];
            data = data/4096*5;
            channel = ((buf[0] & 0b00110000)>>4);
            printf("Channel %02d Data:  %04f\n",channel,data);
        }
    }

    //unsigned char reg = 0x10; // Device register to access
    //buf[0] = reg;
    buf[0] = 0b11110000;

    if (write(file,buf,1) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
        buffer = g_strerror(errno);
        printf(buffer);
        printf("\n\n");
    }
}

void I2C_write(int file, unsigned char data)
{
	if (write(file,data,1) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
        buffer = g_strerror(errno);
        printf(buffer);
        printf("\n\n");
    }
}

void I2C_read(int file)
{
	char buf[10] = {0};
	
	I2C_write(file, addr); //write address of ADC
	
	if (read(file,buf,2) != 2) {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            buffer = g_strerror(errno);
            printf(buffer);
            printf("\n\n");
        } else {
            data = (float)((buf[0] & 0b00001111)<<8)+buf[1];
            data = data/4096*3.3;
            printf("Channel %02d Data:  %04f\n",channel,data);
        }
}

int main(void)
{
	int file;	//file for I2C bus buffer
	
	I2C_init(file);	//setup I2C bus
	
	for (unsigned char i = 0; i < 3; i++)
	{
		I2C_read(file); //read ADC
		
		delay(1); //delay 1 ms for ADC conversion
	}
	
	return 0;
}