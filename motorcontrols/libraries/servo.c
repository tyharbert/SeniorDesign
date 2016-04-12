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
    adc_hex= wiringPiI2CReadReg16(result,0x00);

    wiringPiI2CWriteReg16(result, 0x01, address);
    adc_hex = wiringPiI2CReadReg16(result,0x00); //device address, assigning device to read only

    adc_hex = Rd_Rev(adc_hex); //Reverses the order of the hex value taken in
    // printf("%d \n",adc_hex);
    return adc_hex;
    }

void CaptureSavedLocations(const char* location_file_path) {
    system("echo ./servod --p1pins=7, 11, 0, 0, 0, 0, 0, 0");
    system("echo ./servod --step-size=1us");
    system("sudo echo 0=150 > /dev/servoblaster");
    system("sudo echo 1=135 > /dev/servoblaster");
    wiringPiSetupGpio();
    pinMode(butPin, INPUT);
    pullUpDnControl(butPin, PUD_DOWN);

    while(1)
    {
	if(1)
        //if (digitalRead(butPin)==1)
        {
            int i = 0;
            int length;
            int* positions;
            positions = getPositions(&length, location_file_path);

           if (positions == NULL)
	   {
		printf("Null locations returning");
                return;
	   }
           while (i < length) {
                move_and_check_Position(positions[i], 0); //Pan Motor
                i++;
                move_and_check_Position(positions[i], 1); //Tilt Motor
                i++;
		move_and_check_Position(positions[i-2], 0);//Double check Pan Motor
		move_and_check_Position(positions[i-1], 1);//Double check Tilt Motor
                Cap_Image();
            }
            break;
        }
    }
}

unsigned short Rd_Rev(unsigned short a)
    {
     return ((a << 4) | (a >> 12)) & 0x0FFF;
    }

int FB_to_PW_Conv(int Servo)
{
  if (Servo==0)
    {

        int Read=ADC_Rd(0x83C5); //read from servo 0
        int current_echo_value = FB_to_PW(Read, 0); //Multiplies the Percent by Range of Echo PW, and adds 50 to obtain accurate echo value
        printf("%d --current pan servo position echo value\n", current_echo_value);

        return current_echo_value;
    }
    else if(Servo==1)
    {
        int Read=ADC_Rd(0x83D5); //read from servo 0
        int current_echo_value = FB_to_PW(Read, 1); //Multiplies the Percent by Range of Echo PW, and adds 50 to obtain accurate echo value
        printf("%d  --current tilt servo position echo value\n", current_echo_value);

        return current_echo_value;
    }
}
int FB_to_PW(int feedback, int motor){
	float fb= (float)feedback;
	float new_echo;
	if (motor==0){
		new_echo=4.3529*.000001*fb*fb+.0835*fb-1.5046;
	}
	if (motor==1){
		new_echo=-.00000018924*fb*fb*fb+.00084797*fb*fb-1.1654*fb+615.19;
	}

	return roundf(new_echo);
}

void Pan_Gusset(int feedbackTarget)
{
    printf("Pan Gusset....\n");
    int current_echo_value=FB_to_PW_Conv(0);
    int change_in_echo= FB_to_PW(feedbackTarget, 0) - current_echo_value; //gives the difference between desired echo and current echo value
    printf("%d --feedback target echo value \n", FB_to_PW(feedbackTarget, 0));
    printf("%d --change in echo necessary \n", change_in_echo);

    if (change_in_echo<0)
        {
        change_in_echo = -change_in_echo;
        int i;
	for (i=0; i<change_in_echo; i++)
            {
            system("sudo echo 0=-1 > /dev/servoblaster");
	    delayMicroseconds(30000);
            }
        }
    else
        {
        int i;
	for (i=0; i<change_in_echo; i++)
            {
            system("sudo echo 0=+1 > /dev/servoblaster");
	    delayMicroseconds(30000);
            }
        }
    sleep(3);

    }

void move_and_check_Position(int feedbackTarget, int motor)
{
    int i=0;
    int Read=-1;
    if (motor==0)
    {
        while (Read < (feedbackTarget - 10) || Read > (feedbackTarget + 10))
        {
	Pan_Gusset(feedbackTarget);
        Read=ADC_Rd(0x83C5);
        i++;

            if(i>=5)
            {
            printf("Issue with Pan Motor for location %d \n", feedbackTarget);
            break;
            }
        }
	i=0;
    }
    else
    {

    while (Read < (feedbackTarget - 10) || Read > (feedbackTarget + 10))
        {
	Tilt_Gusset(feedbackTarget);
        Read=ADC_Rd(0x83D5);
        i++;
            if(i>=5)
            {
            printf("Issue with Tilt Motor for location %d \n", feedbackTarget);
            break;
            }
        }
	i=0;
    }
	sleep(1);
	printf("Exiting move and pan/tilt\n");
}

void Tilt_Gusset(int feedbackTarget)
{
    printf("Tilt Gusset....\n");
    int current_echo_value = FB_to_PW_Conv(1);
    int change_in_echo = FB_to_PW(feedbackTarget, 1) - current_echo_value; //gives the difference between desired echo and current echo value
    printf("%d --feedback target echo value \n", FB_to_PW(feedbackTarget, 1));
    printf("%d --change in echo necessary \n", change_in_echo);
    if (change_in_echo<0)
        {
        change_in_echo=-change_in_echo;
        int i;
	for (i=0; i < change_in_echo; i++)
            {
            system("sudo echo 1=-1 > /dev/servoblaster");
            delayMicroseconds(30000);
		if(i>=30)
		sleep(3);
            }
        }
    else
        {
        int i;
	for (i=0; i < change_in_echo; i++)
            {
            system("sudo echo 1=+1 > /dev/servoblaster");
            delayMicroseconds(30000);
		if(i==30)
		sleep(3);
            }
        }
        sleep(3);
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

void Cap_Image()
{
    int n=75;
    int cx=0;
    static int i=0;
    char command[n];
    cx=snprintf(command, n, "fswebcam -r 2592x1944 --jpeg 100 -D 17 -S 13 1 ../images/testing%d.jpeg", i); //assigns the echo call as the command, with the limit of n characters
    if(cx>n)
        printf("Command Length Too Long");
    else
        system(command);
        i++;
}

// gets the locations from the save file
int* getPositions(int* length, const char* location_file_path) {
    FILE* f;
    char buffer[1024];

    f = fopen(location_file_path, "r");

    if (!f)
        return NULL;

    if (fgets(buffer, sizeof(buffer), f) == NULL) {
        printf("problem with reading the locations file.\n");
        return NULL;
    }

    *length = numPositions(buffer);

    // this is twice the size because it includes both servo positions
    // this is hard coded into captureLocation() of calibration.cpp
    static int positions[8];

    for (int i=0; i < *length; i++) {
        positions[i] = nextPosition(buffer);
    }

    return positions;
}

// determine number of positions
int numPositions(char buffer[buffSize]) {
    int i = 0, commas = 0;

    while (buffer[i] != '\0') {
        if (buffer[i] == ',')
            commas++;

        i++;
    }

    return ++commas;
}

// get next position number
int nextPosition(char buffer[buffSize]) {
    static int end = 0, begin = 0;
    char tempBuff[10];

    // make sure tempBuff has nothing in it
    for (int i = 0; i < 10; i++)
        tempBuff[i] = 0;

    while (buffer[end] != '\0') {
        if (buffer[end] == ',') {
            begin = ++end;
            break;
        }

        tempBuff[end-begin] = buffer[end];
        end++;
    }

    return atoi(tempBuff);
}
