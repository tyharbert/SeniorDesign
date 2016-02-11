

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>


//Import the ADS1x15 module.
import Adafruit_ADS1x15
const unsigned char butPin = 18; // Active something

//create an ADS1015 ADC (12-bit) instance.
int main()
{

//wiringPiSetupGpio();
//pinMode(butPin, INPUT);
//pullUpDnControl(butPin, PUD_DOWN);

adc = Adafruit_ADS1x15.ADS1015();

GAIN=1; //1 reads +/- 4.096V
        //2 reads +/- 2.048V
        //Can set gain to a floating point number
        //Servo puts out .1V to 2.2V feeback

printf("Reading ADS1x15 values, press Ctrl-C to quit...");

printf("| {0:>6} | {1:>6} | {2:>6} | {3:>6} |".format(*range(4)));
printf("-" * 37);

while(1)
{
values =[0]*3 //an array of one row and 4 columns

    //if (digitalRead(butPin)==1)
    //{
        for (int i=0; i<=3; i++) //runs until the all 4 digits are collected
        {
        values=[i]=adc.read_adc(i, gain=GAIN);
        }

    //Display the ADC values from 0-4095
    printf("| {0:>6} | {1:>6} | {2:>6} | {3:>6} |".format(*values)) ;
    sleep(5);
    //}

 return 0
}
