#include "servo.h"

/* Servo 0 is the Pan servo and can tilt from 0-180 degrees, or .5 ms to 2.5 ms
Servo 1 is the Tilt servo and can tilt from 0-150 degrees, or .5 ms to 2.08 ms
*/

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
    sleep(3);
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
    if(Motor_Num==1)
	system("echo ./servod min={100}");
    char command[n];
    cx=snprintf(command, n, "echo %d=%d > /dev/servoblaster", Motor_Num, Motor_Loc); //assigns the echo call as the command, with the limit of n characters
    if(cx>n)
        printf("Command Length Too Long");
    else
        system(command);
    sleep(2);
}

void Tilt_Gusset(int Tilt_Loc, int Lower_Bound, int Upper_Bound)
{
    printf("Tilt Gusset....\n");
    static int i=0;
    int Read=-1;

    while (Read < Lower_Bound || Read > Upper_Bound) //Upper and Lower Bounds for each Location
    {
        Mov_Motor(1, Tilt_Loc);
        Read=ADC_Rd(0x83D5);
        i++;

        if(i>=5)
        {
            printf("Issue with Tilt Motor for location %d", Tilt_Loc);
            break;
        }
    }
}
void Cap_Image() //Motor number (0 or 1), and Motor Location (50-250)
{
    int n=65;
    int cx=0;
    static int i=0;
    char command[n];
    cx=snprintf(command, n, "fswebcam -r 1280x720 --jpeg 100 -D 30 -S 13 1 testing%d.jpeg", i); //assigns the echo call as the command, with the limit of n characters
    if(cx>n)
        printf("Command Length Too Long");
    else
        system(command);
        i++;

}
