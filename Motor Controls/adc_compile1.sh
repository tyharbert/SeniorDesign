#! /bin/bash

gcc ADC.c -lwiringPi -lpthread -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -lglib-2.0 -std=c99 -o ADC.o
