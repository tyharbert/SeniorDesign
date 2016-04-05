/*
 * File:   powerSystem.c
 * Author: Joshua R. Reiderman
 *
 * Analog to digital conversion functions
 * 
 *
 */

#include <xc.h>
#include "ADC.h"
#include "power_system.h"

// function to set up the ADC
void ADC_initialize(void)
{
    // setup ADC control register (ADCON1)
    
    // bit 7: right justified ADC result (1)
    // bits 6-4: conversion clock = Fosc/2 (000)
    // bit 3: unimplemented; read as 0
    // bit 2: Vref- is connected to Vss (0)
    // bits 1-0: Vref+ is connected to Vdd (00)
    ADCON1 = 0x80;   
}

// reads an analog input
unsigned int ADC_read(unsigned char channel)
{
    ADCON0 = channel;
    __delay_us(5);  
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO);
    ADCON0bits.ADON = 0;
    
    return ((ADRESH << 8) | ADRESL);
}