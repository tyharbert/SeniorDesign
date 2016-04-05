#ifndef CALIBRATION_HPP
#define CALIBRATION_HPP

extern "C" {
#include "servo.h"
}

#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

// This will be used to capture the feedback positions of the servos
// and save them to a file so they can be read back when needed
void calibrateLocations(const char*);
void printMenu();
short processInput(char, const char*);
void loadLocations(const char*);
void saveLocations(const char*);
void removeLocation();
void printLocations();
void captureLocation();

static std::vector<std::vector<int> > locations;

#endif
