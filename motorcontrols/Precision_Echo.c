// Servo Test 2 w/ fb
// Jacob Lambert
// /dev/servoblaster


/* Servo 0 is the Pan servo and can tilt from 0-180 degrees, or .5 ms to 2.5 ms
Servo 1 is the Tilt servo and can tilt from 0-150 degrees, or .5 ms to 2.08 ms
*/

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>


unsigned short ADC_Rd(unsigned short address);
unsigned short Rd_Rev(unsigned short);
void Pan_Gusset(int Pan_Loc, int Lower_Bound, int Upper_Bound);
void Mov_Motor(int Motor_Num, int Motor_Loc);
void Tilt_Gusset(int Tilt_Loc, int Lower_Bound, int Upper_Bound);
void FB_to_PW_Conv(int Servo);

const unsigned char butPin = 18; // Active something

unsigned short ADC_Rd(unsigned short address) //Read channel 0 or 1 adc, Pan Motor
    {
    unsigned short adc_hex = 0;
    int result;

    result=wiringPiI2CSetup(0x48); //device address

    wiringPiI2CWriteReg16(result, 0x01, address); //Address for the register, and configuring the read channel 0
    adc_hex= wiringPiI2CReadReg16(result, 0x00);

    wiringPiI2CWriteReg16(result, 0x01, address);
    adc_hex = wiringPiI2CReadReg16(result,0x00); //device address, assigning device to read only

    adc_hex = Rd_Rev(adc_hex); //Reverses the order of the hex value taken in
    printf("%d\n",adc_hex);
    sleep(5);
    return adc_hex;
    }


unsigned short Rd_Rev(unsigned short a)
    {
     return ((a << 4) | (a >> 12)) & 0x0FFF;
    }

void FB_to_PW_Conv(int Servo)
{
  if (Servo==0)
    {
  Read=ADC_Rd(0x83C5); //read from servo 0
  float min_fb=584 //echo 0=50
  float max_fb=2170; //echo 0=200
  float fb_range=max_fb-min_fb;
  int echo_range=150;
  float Perc_PW= (Read-min_fb)/fb_range; //subtracts mininum voltage read value, divides by total range of voltages
  float current_echo_value = (Perc_Pw*echo_range)+47; //Multiplies the Percent by Range of Echo PW, and adds 50 to obtain accurate echo value
  printf("%f \n", current_echo_value);

  return current_echo_value;
    }
  else if(Servo==1)
    {
  Read=ADC_Rd(0x83D5); //read from servo 0
  float min_fb=584 //echo 0=50
  float max_fb=2170; //echo 0=200
  float fb_range=max_fb-min_fb;
  int echo_range=150;
  float Perc_PW= (Read-min_fb)/fb_range; //subtracts mininum voltage read value, divides by total range of voltages
  float current_echo_value = (Perc_Pw*echo_range)+47; //Multiplies the Percent by Range of Echo PW, and adds 50 to obtain accurate echo value
  printf("%f \n", current_echo_value);

  return current_echo_value;
    }

}
void Pan_Gusset(int desired_Pan_Loc, int Lower_Bound, int Upper_Bound)
{
    printf("Pan Gusset....\n");
    int current_echo_value=FB_to_PW_Conv(0);
    int change_in_echo=desired_Pan_Loc-current_echo_value; //gives the difference between desired echo and current echo value
    if (change_in_echo<0)
        {
        change_in_echo=-change_in_echo;
        int change= change_in_echo/10; //gives number of +/- 10 echo steps
        int change_remainder=change_in_echo%10; //gives the size of the +/- remainder
        for (i=0; i<change-1; i++)
            {
            system("echo 0=-10 /dev/servoblaster");
            }
        system("echo 0=-%d", change_remainder);
        }
    else
        {
        int change = change_in_echo/10; //gives number of +/- 10 echo steps
        int change_remainder=change_in_echo%10; //gives the size of the +/- remainder
        for (i=0; i<change-1; i++)
            {
            system("echo 0=+10 /dev/servoblaster");
            }
        system("echo 0=+%d", change_remainder);
        }


    static int i=0;
    int Read=-1;

    while (Read < Lower_Bound || Read > Upper_Bound)
    {
        Mov_Motor(0, desired_Pan_Loc);
        Read=ADC_Rd(0x83C5);
        i++;

        if(i>=5)
        {
            printf("Issue with Pan Motor for location %d", Pan_Loc);
            break;
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
    sleep(1);
}





int main()
{
system("echo ./servod --p1pins=7, 11, 0, 0, 0, 0, 0, 0");
system("echo ./servod --step-size=1us");
wiringPiSetupGpio();
pinMode(butPin, INPUT);
pullUpDnControl(butPin, PUD_DOWN);

    while(1)
    {
        if (digitalRead(butPin)==1)
        {
         Pan_Gusset(150, 1660, 1675);  //actual value 1669 or 1.669V
//         Tilt_Gusset(150, 1630, 1645); //actual value 1637 or 1.637V
//         Cap_Image();
         Pan_Gusset(180, 1960, 1973); //actual value 1970 or 1.970V
//         Tilt_Gusset(180,1920,1937);  // actual value 1930, or 1.93V
//         Cap_Image();
         Pan_Gusset(100,1130, 1150); //actual value 1142 or 1.142V
//         Tilt_Gusset(100, 1120, 1140); //actual value 1127 or 1.127V feedback
//        Cap_Image();
        }
    }

return 0;
}

//Write up an equation to convert a feedback value to a corresponding pulse width. We will be taking in a feedback
//value when setting up the gusset plate locations.

