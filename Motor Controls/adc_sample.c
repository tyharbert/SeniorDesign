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

void ADC_write ()
    if (write(file,buf,1) != 1)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
        buffer = g_strerror(errno);
        printf(buffer);
        printf("\n\n");
    }

void
sensors_ADC_init(void) {
    int file;
    char filename[40];
    const gchar *buffer;
    int addr = 0b00101001;        // The I2C address of the ADC

    sprintf(filename,"/dev/i2c-2");
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
    //ads1015 datasheet settings pg 16
    buf[0] = 0b10010000; //Writing to Config Register: Address
    ADC_write ();
    buf[0] = 0b00000001; //Points to the config register
    ADC_write ();
    buf[0] = 0b10000101; //Bits 15-8, Single Conversion, dafult multiplexer config, default voltage range (+-2.048)
    ADC_write ();
    buf[0] = 0b10000011; //bits 7-0, Comparator settings, comparator disabled
    ADC_write ();

}

int adc_read()
{
    char buf[10] = {0};
    float data;
    char channel;

    for(int i = 0; i<4; i++)
        {
        // Using I2C Read
            if (read(file,buf,2) != 2)
            {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            buffer = g_strerror(errno);
            printf(buffer);
            printf("\n\n");
            }
            else
            {
            data = (float)((buf[0] & 0b00001111)<<8)+buf[1];
            data = data/4096*3.3;
            channel = ((buf[0] & 0b00110000)>>4);
            printf("Channel %02d Data:  %04f\n",channel,data);
            }
}

int main()
{
sensors_ADC_init();
adc_read();

}
