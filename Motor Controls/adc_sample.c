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

void ADC_write (char * buf,int file)
    {
    const gchar *buffer;
    int addr = 0b01001000; // I2C address of the ADC
	if (write(file,buf,1) != 1)
    	{
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
        buffer = g_strerror(errno);
        printf(buffer);
        printf("\n\n");
    	}
    }

int sensors_ADC_init(void) 
{
    int file;
    char filename[40];
    const gchar *buffer;
    int addr = 0b01001000;        // The I2C address of the ADC

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

    char buf[10] = {0};

    //unsigned char reg = 0x10; // Device register to access
    //buf[0] = reg;
    //ads1015 datasheet settings pg 16
    buf[0] = 0b10010000; //Writing to Config Register: Address
    ADC_write (buf,file);
    buf[0] = 0b00000001; //Points to the config register
    ADC_write (buf,file);
    buf[0] = 0b11000101; //Bits 15-8, Single Conversion, CH0 multiplexer config, default voltage range (+-2.048)
    ADC_write (buf,file);
    buf[0] = 0b10000011; //bits 7-0, Comparator settings, comparator disabled
    ADC_write (buf,file);

return file;
}

void adc_read(char * buf,int  file)
{
  //  char buf[10] = {0}; //defaults buf to zero
    float data;
    char channel;
    buf[0]=0b10010000; //pointer register
    ADC_write(buf, file);
    buf[0]=0b00000000;//conversion reister
    ADC_write(buf, file);
    buf[0]=0b10010001; //
    ADC_write(buf, file);

    for(int i = 0; i<4; i++)
    {
        // Using I2C Read
            if (read(file,buf,2) != 2)
            {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            const gchar * buffer = g_strerror(errno);
            printf(buffer);
            printf("\n\n");
            }
            else
            {
            data = (float)((buf[0] & 0b00001111)<<8)+buf[1];
            data = data/4096*3.3;
            channel = ((buf[0] & 0b00110000)>>4);
            printf("Channel %02d Data:  %04f\n",channel,data);
	    delay(10);
	    }
    }
}

int main()
{
char buf[10]={0};
int file = sensors_ADC_init();
delay(1); //1ms delay
adc_read(buf, file);

return 0;
}
