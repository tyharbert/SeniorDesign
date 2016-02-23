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
void ADC_Rd_0();
void ADC_Rd_1();
unsigned short Rd_Rev(unsigned short);
void Pan_Gusset(int Pan_Loc);
void Mov_Motor(int Motor_Num, int Motor_Loc);
void Tilt_Gusset(int Tilt_Loc);

const unsigned char butPin = 18; // Active something

void ADC_Rd_0() //Read channel 0 adc, Pan Motor
    {
    unsigned short adc_hex = 0;
    int result;
    printf("%08x\n", adc_hex);

    result=wiringPiI2CSetup(0x48);
    printf("%d \n", wiringPiI2CWriteReg16(result, 0x01, 0x83C5)); //Address for the register, and configuring the read channel 0

    adc_hex = wiringPiI2CReadReg16(result,0x00);
    printf("0x%04x \n", adc_hex);
    adc_hex = Rd_Rev(adc_hex);
    printf("0x%04x\n %d\n",adc_hex,adc_hex);
    }

void ADC_Rd_1() //Read channel 1 adc, Tilt Motor
    {
    unsigned short adc_hex = 0;
    int result;
    printf("%08x\n", adc_hex);

    result=wiringPiI2CSetup(0x48);
    printf("%d \n", wiringPiI2CWriteReg16(result, 0x01, 0xA3C5)); //Address for the register, and configuring the read channel 1

    adc_hex = wiringPiI2CReadReg16(result,0x00);
    printf("0x%04x \n", adc_hex);
    adc_hex = Rd_Rev(adc_hex);
    printf("0x%04x\n %d\n",adc_hex,adc_hex);
    }


unsigned short Rd_Rev(unsigned short a)
    {
     return ((a << 4) | (a >> 12)) & 0x0FFF;
    }

void Pan_Gusset(int Pan_Loc)
{
    Motor_Loc=Pan_Loc;
    static int i=0;
    Mov_Motor(0, Motor_Loc);
    sleep(1);
        if(Pan_Loc==150)
        {
            if(ADC_Rd_0()< 1665 | ADC_Rd_0() > 1670 ) //actual value of 1668, or 1.668V
            {
            i=i++;   //incrementing i to prevent from continuous failing
            Pan_Gusset(150);
            }
            if(i>=5)
            {
            printf("Issue with Pan Motor For Location %d", Pan_Loc);
            i=0;   //reset i
            }
        }
        else if(Pan_Loc==180)
        {
            if(ADC_Rd_0()< 1967 | ADC_Rd_0() > 1973 ) //actual value of 1970, or 1.970V
            {
            i=i++;   //incrementing i to prevent from continuous failing
            Pan_Gusset(180);
            }
            if(i>=5)
            {
            printf("Issue with Pan Motor For Location %d", Pan_Loc);
            i=0;   //reset i
            }
        }
        else if(Pan_Loc==100)
        {
            if(ADC_Rd_0()< 1139 | ADC_Rd_0() > 1145 ) //actual value of 1142, or 1.142V
            {
            i=i++;   //incrementing i to prevent from continuous failing
            Pan_Gusset(100);
            }
            if(i>=5)
            {
            printf("Issue with Pan Motor For Location %d", Pan_Loc);
            i=0;   //reset i
            }
        }
    }

void Mov_Motor(int Motor_Num, int Motor_Loc) //Motor number (0 or 1), and Motor Location (50-250)
{
    if(Motor_Num>1)
        printf("Incorrect Servo Motor Address");
    int n=30;
    int cx=0;
    char*command[n];
    cx=snprintf(command, n, "echo %d=%d > /dev/servoblaster", Motor_Num, Motor_Loc); //assigns the echo call as the command, with the limit of n characters
    if(cx>n)
        printf("Command Length Too Long");
    else
        system(command);
}

void Tilt_Gusset(int Tilt_Loc)
    {
    Motor_Loc=Tilt_Loc;
    static int i=0;
    Mov_Motor(1, Motor_Loc);
    sleep(1); //Wait for 1 second
        if (Tilt_Loc==150)
        {
            if(ADC_Rd_1()< 1634 | ADC_Rd_1() > 1640) //1637 or 1.637V feedback
            {
            i=i++;
            Tilt_Gusset(150);
            }
            if(i>=5)
            {
            printf("Issue with Tilt Motor for location %d", Tilt_Loc);
            i=0;
            }
        }
        else if (Tilt_Loc==180)
        {
            if(ADC_Rd_1()< 1927 | ADC_Rd_1() > 1933) //1930 or 1.93V feedback
            {
            i=i++;
            Tilt_Gusset(180);
            }
            if(i>=5)
            {
            printf("Issue with Tilt Motor for location %d", Tilt_Loc);
            i=0;
            }
        }
        else if (Tilt_Loc==100)
        {
            if(ADC_Rd_1()< 1124 | ADC_Rd_1() > 1130) //1127 or 1.127V feedback
            {
            i=i++;
            Tilt_Gusset(100);
            }
            if(i>=5)
            {
            printf("Issue with Tilt Motor for location %d", Tilt_Loc);
            i=0;
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
         Pan_Gusset(150);
         Tilt_Gusset(150);
         Pan_Gusset(180);
         Tilt_Gusset(180);
         Pan_Gusset(100);
         Tilt_Gusset(100);
        }

    }

return 0;
}
