// Servo Test 1
// Jacob Lambert
// /dev/servoblaster


/* Servo 0 is the Pan servo and can tilt from 0-180 degrees, or .5 ms to 2.5 ms
Servo 1 is the Tilt servo and can tilt from 0-150 degrees, or .5 ms to 2.08 ms
*/

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>

//./servod --min={50|Nus|2.5%} //2.5% as minimum PW
//./servod --max={200|Nus|75%} //75% to prevent servo1 (tilt) from hitting at max pulse
//./servod --step-size=10us //default step size
// echo 0=120 > /dev/servoblaster  //sends servo 0 a pulse of 1.2 ms (120 us)
// udelay(100) //delays 100 us, or .1 ms

const unsigned char butPin = 18; // Active something

int main()
{
system("echo ./servod --p1pins=7, 11, 0, 0, 0, 0, 0, 0");
wiringPiSetupGpio();
pinMode(butPin, INPUT);
pullUpDnControl(butPin, PUD_DOWN);

int i;

while(1)
{

	if (digitalRead(butPin)==1)
	{
		for(i=0; i<=5; i++)
           	{
		system("echo 0=150 > /dev/servoblaster"); //move servo 0 to center/middle position
		sleep(1);
		system("echo 1=150 > /dev/servoblaster"); //move servo 1 to center/middle position
		sleep(1); //Wait for 1 second
/*
GetADC(5)
int Servo1FB=GetADC(5);
        Rvolts=Servo1FB*3.3/1024;
        while (Rvolts<=1.6 && >= 1.7)
        {
            echo 0=150 > /dev/servoblaster //move servo to center/middle position
            sleep(1000)
        }
*/
		system("echo 0=180 > /dev/servoblaster");
		sleep(1);
		system("echo 1=180 > /dev/servoblaster");
		sleep(1);

		system("echo 0=100 > /dev/servoblaster");
		sleep(1);
		system("echo 1=100 > /dev/servoblaster");
		sleep(1);
		}
        }
}
return 0;
}
