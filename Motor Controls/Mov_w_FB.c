// Servo Test 2 w/ fb
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
unsigned short ADC_Rd(unsigned short address);
unsigned short Rd_Rev(unsigned short);
void Pan_Gusset(int Pan_Loc, int Lower_Bound, int Upper_Bound);
void Mov_Motor(int Motor_Num, int Motor_Loc);
void Tilt_Gusset(int Tilt_Loc, int Lower_Bound, int Upper_Bound);

const unsigned char butPin = 18; // Active something

unsigned short ADC_Rd(unsigned short address) //Read channel 0 adc, Pan Motor
    {
    unsigned short adc_hex = 0;
    int result;

    result=wiringPiI2CSetup(0x48);
    wiringPiI2CWriteReg16(result, 0x01, address); //Address for the register, and configuring the read channel 0

    adc_hex = wiringPiI2CReadReg16(result,0x00);
    adc_hex = Rd_Rev(adc_hex);
    printf("0x%04x\n %d\n",adc_hex,adc_hex);

    return adc_hex;
    }


unsigned short Rd_Rev(unsigned short a)
    {
     return ((a << 4) | (a >> 12)) & 0x0FFF;
    }

void Pan_Gusset(int Pan_Loc, int Lower_Bound, int Upper_Bound)
{
    printf("Pan Gusset....\n");
    static int i=0;
    Mov_Motor(0, Pan_Loc);
    sleep(1);
        if(Pan_Loc==150)
        {
            while (ADC_Rd(0x83C5)< Lower_Bound || ADC_Rd(0x83C5) > Upper_Bound)
            {
                Mov_Motor(0, Pan_Loc);
                i++;

                if(i>=5)
                {
                    printf("Issue with Pan Motor for location %d", Pan_Loc);
                    break;
                }
            }
        }
    }

void Mov_Motor(int Motor_Num, int Motor_Loc) //Motor number (0 or 1), and Motor Location (50-250)
{
    int n=35;
    int cx=0;
    char command[n];
    cx=snprintf(command, n, "echo %d=%d > /dev/servoblaster", Motor_Num, Motor_Loc); //assigns the echo call as the command, with the limit of n characters
    if(cx>n)
        printf("Command Length Too Long");
    else
        system(command);
}

void Tilt_Gusset(int Tilt_Loc, int Lower_Bound, int Upper_Bound)
    {
    printf("Tilt Gusset....\n");
    static int i=0;
    sleep(1); //Wait for 1 second
        if (Tilt_Loc==150)
        {
            while (ADC_Rd(0x83D5)< Lower_Bound || ADC_Rd(0x83D5) > Upper_Bound) //Upper and Lower Bounds for each Location
            {
                Mov_Motor(1, Tilt_Loc);
                i++;

                if(i>=5)
                {
                    printf("Issue with Tilt Motor for location %d", Tilt_Loc);
                    break;
                }
            }
        }

    }

int main()
{
system("echo ./servod --p1pins=7, 11, 0, 0, 0, 0, 0, 0");
wiringPiSetupGpio();
pinMode(butPin, INPUT);
pullUpDnControl(butPin, PUD_DOWN);

    while(1)
    {
        if (digitalRead(butPin)==1)
        {
         Pan_Gusset(150, 1660, 1675);  //actual value 1669 or 1.669V
         Tilt_Gusset(150, 1630, 1645); //actual value 1637 or 1.637V
//         Pan_Gusset(180, 1967, 1973); //actual value 1970 or 1.970V
//         Tilt_Gusset(180,1927,1933);  // actual value 1930, or 1.93V
//         Pan_Gusset(100,1139, 1145); //actual value 1142 or 1.142V
//         Tilt_Gusset(100, 1120, 1133); //actual value 1127 or 1.127V feedback
        }

    }

return 0;
}
