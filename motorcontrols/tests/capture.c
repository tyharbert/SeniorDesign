// Servo Test 2 w/ fb
// Jacob Lambert
// /dev/servoblaster

#include "servo.h"

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
         Tilt_Gusset(120, 1317, 1340); //actual value 1637 or 1.637V
         Cap_Image();
         Pan_Gusset(180, 1960, 1980); //actual value 1970 or 1.970V
         Tilt_Gusset(150,1627,1648);  // actual value 1930, or 1.93V
         Cap_Image();
         Pan_Gusset(130,1453, 1475); //actual value 1142 or 1.142V
         Tilt_Gusset(120, 1317, 1340); //actual value 1127 or 1.127V feedback
         Cap_Image();
        }
    }

return 0;
}
