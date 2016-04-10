#ifndef SPI_SHUTDOWN_H
#define SPI_SHUTDOWN_H

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>

#define SPI_speed 500000 // 0.5 MHz
#define SPI_channel 0 // channel 0
#define SPI_CS 15 // chip select is pin 15

void SPI_shutdown();

#endif
