#ifndef SERVO_HPP
#define SERVO_HPP

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>

static const int buffSize = 1024;
// this is twice the size because it includes both servo positions
// this is hard coded into captureLocation() of calibration.cpp
static const int maxPositions = 8;

static const unsigned char butPin = 18; // Active something

unsigned short ADC_Rd(unsigned short address);
unsigned short Rd_Rev(unsigned short);
void Pan_Gusset(int feedbackTarget);
void Mov_Motor(int Motor_Num, int Motor_Loc);
void Tilt_Gusset(int feedbackTarget);
void CaptureSavedLocations();
int FB_to_PW_Conv(int Servo);
float FB_to_PW(int feedback, float min_fb, float max_fb);
int* getPositions(int* length);
int numPositions(char buffer[buffSize]);
int nextPosition(char buffer[buffSize]);

// Write up an equation to convert a feedback value to a corresponding pulse width. We will be taking in a feedback
// value when setting up the gusset plate locations.

#endif
