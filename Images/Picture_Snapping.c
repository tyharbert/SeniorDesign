/*Jacob Lambert
    Repeated Image Taking to find a pattern and test
*/

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>

void Cap_Image()
{
    int n=65;
    int cx=0;
    static int i=0;
    char command[n];
    cx=snprintf(command, n, "fswebcam -r 1280x720 --jpeg 100 -D 30 -S 13 1 test%d.jpeg", i);
    if(cx>n)
        printf("Command Length Too Long");
    else
        system(command);
        i++;

}

int main()
{
    while(1)
    {
     Cap_Image();
     sleep(1); //sleep for 1 second to allow the camera to fail if necessary and reboot
    }

    return 0;
}
