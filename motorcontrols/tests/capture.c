// Servo Test 2 w/ fb
// Jacob Lambert
// /dev/servoblaster

#include "servo.h"

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
//         Pan_Gusset(150, 1600, 1700);  //actual value 1669 or 1.669V
//         sleep(4);
//         Tilt_Gusset(120, 1290, 1350); //actual value 1637 or 1.637V
//	 sleep(4);
//         Cap_Image();
//         Pan_Gusset(180, 1900, 2100); //actual value 1970 or 1.970V
 //        sleep(4);
   //      Tilt_Gusset(150,1600,1675);  // actual value 1930, or 1.93V
//	 sleep(4);
//         Cap_Image();
  //       Pan_Gusset(130,1400, 1500); //actual value 1142 or 1.142V
    //     sleep(4);
      //   Tilt_Gusset(120, 1290, 1375); //actual value 1127 or 1.127V feedback
	// sleep(4);
         Cap_Image();
        }
    }

return 0;
}
