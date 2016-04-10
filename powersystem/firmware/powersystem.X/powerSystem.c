/*
 * File:   powerSystem.c
 * Author: Joshua R. Reiderman
 *
 * This is the main c file for the power system firmware.
 * 
 * Created on March 13, 2016, 5:21 PM
 */

#include <xc.h>
#include "powerSystem.h"
#include "ADC.h"
#include "SPI.h"
#include "memory.h"

#define SLEEP_FLAG_ADDR 0x7000

// main function; program starts here
void main(void) 
{
    unsigned int time = 0;  // number of times WDT is cleared
                            // 21600 == 24 hours
    unsigned char data =0;
    unsigned char sleep_flag = 1;
    unsigned int battery_voltage = 0; // ADC reading of battery voltage
    
    ports_initialize(); //set up ports 
    ADC_initialize();    //configure ADC
    SPI_initialize(); // set up SPI module
    
    sleep_flag = DATAEE_ReadByte(SLEEP_FLAG_ADDR);
    
    WDTCON = 0b00011100;
    
    while (sleep_flag)
    {
        WDTCONbits.SWDTEN = 1;
        SLEEP();
        time++;
        if(time == 1)
        {
            DATAEE_WriteByte(SLEEP_FLAG_ADDR, 0);
            RESET();
        }
    }

    DATAEE_WriteByte(SLEEP_FLAG_ADDR, 255);
    
    //battery_voltage = ADC_read(0x09); // read battery voltage
    battery_voltage = 700;
    if( battery_voltage >= 690 ) // 3*4s = 12 s 
    {                                          // 690 -> 11 V
        LATCbits.LATC4 = 1;  //turn relay on

        while(data != 0xDA)      
        {
           while(!SSP1STATbits.BF); 
           data = SSP1BUF;
        }
        
        __delay_ms(4000);
        
        RESET();
    }     
}


// function to setup the microcontroller ports at boot
void ports_initialize(void)
{
    // clear all ports
    PORTA = 0x00;
    PORTC = 0x00;

    TRISA = 0x2C;   // bits 5: temperature (RA5); set as input (1)
                    // bit 3: unimplemented; read as 1
                    // bit 2: battery voltage (RA2); set as input (1) 
    
    TRISC = 0x0B;   // bit 4: power relay (RC4); set as output (0)
                    // bit 3: SPI SS (RC3); set as input (1)
                    // bit 2: SPI SDO (RC2); set as output (0)
                    // bit 1: SPI SDI (RC1); set as input (1)
                    // bit 0: SPI SCK (RC0); set as input (1)
    
    ANSELA = 0x24;  // bit 5: temperature (RA5); set as analog (1)
                    // bit 2: battery voltage (RA2); set as analog (1)
    
    ANSELC = 0x00;  // all digital
}