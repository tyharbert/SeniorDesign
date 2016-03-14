/*
 * File:   powerSystem.c
 * Author: Joshua R. Reiderman
 *
 * This is the main c file for the power system firmware.
 * 
 * Created on March 13, 2016, 5:21 PM
 */

// PIC16F18324 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include "powerSystem.h"


//main function; program starts here
void main(void) {
    
    ports_initialize(); //set up ports 
    ADC_initialize();    //configure ADC
    
    while(1)
    {        
        unsigned int batt = ADC_read(0b00001001); //read batt voltage
        
        if (batt >= 690) //checks if battery voltage is at or above 11V
        {
            PORTCbits.RC4 = 1;  //turn LED on
        }
        else //battery voltage below 11V
        {
            PORTCbits.RC4 = 0; //turn led off
        }
        
        __delay_ms(500); //wait 0.5 seconds between ADC readings
    }
    
    return;
}

//function to setup the microcontroller ports at boot
void ports_initialize(void)
{
    //clear all ports
    PORTA = 0x00;
    PORTC = 0x00;
    
    //set tri-state registers to implement
    //pins as inputs or outputs
    
    //tri-state A
    //bits 7-6: unimplemented; read as 0
    //bits 5-4: unused; set as outputs (0)
    //bit 3: unimplemented; read as 1
    //bit 2: battery voltage (RA2); set as input (1)
    //bits 1-0: unused; set as output(0)
    TRISA = 0x0C;   
    
    //tri-state C
    //bits 7-5: unused; set as outputs (0)
    //bit 4: power relay (RC4); set as output (0)
    //bit 3: unused; set as output (0)
    //bit 2 : thermistor (RC2); set as input (1)
    //bit 1-0: unused; set as output (0)
    TRISC = 0x04;
    
    //set analog inputs
    
    //port A analog inputs
    //bits 7-6: unimplemented; read as 0
    //bits 5-4: not used; set as digital (0)
    //bit 3: unimplemented; read as 0
    //bit 2: battery voltage (RA2); set as analog (1)
    //bits 1-0: not used; set as digital (0)
    ANSELA = 0x04;
    
    //port C analog inputs
    //bits 7-3: not used; set as digital (0)
    //bit 2: temperature (RC2); set as analog (1)
    //bits 1-0: not used; set as digital (0)
    ANSELC = 0x04;
    
    return;
}

//function to set up the ADC
void ADC_initialize(void)
{
    //setup ADC control register (ADCON1)
    
    //bit 7: right justified ADC result (1)
    //bits 6-4: conversion clock = Fosc/2 (000)
    //bit 3: unimplemented; read as 0
    //bit 2: Vref- is connected to Vss (0)
    //bits 1-0: Vref+ is connected to Vdd (00)
    ADCON1 = 0x80;
    
    
}

//reads an analog input
unsigned int ADC_read(unsigned char channel)
{
    ADCON0 = channel;
    __delay_us(5);
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO);
    ADCON0bits.ADON = 0;
    
    return ((ADRESH << 8) | ADRESL);
}