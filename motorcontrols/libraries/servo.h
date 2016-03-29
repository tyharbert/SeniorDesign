#ifndef SERVO_HPP
#define SERVO_HPP

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>

unsigned short ADC_Rd(unsigned short address);
unsigned short Rd_Rev(unsigned short);
void Pan_Gusset(int Pan_Loc, int Lower_Bound, int Upper_Bound);
void Mov_Motor(int Motor_Num, int Motor_Loc);
void Tilt_Gusset(int Tilt_Loc, int Lower_Bound, int Upper_Bound);
int FB_to_PW_Conv(int Servo);

static const unsigned char butPin = 18; // Active something

// Write up an equation to convert a feedback value to a corresponding pulse width. We will be taking in a feedback
// value when setting up the gusset plate locations.

#endif
