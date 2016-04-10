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

// main function; program starts here
void main(void) 
{
    unsigned int time = 0;  // number of times WDT is cleared
                            // 21600 == 24 hours
    unsigned char data =0;
    unsigned int battery_voltage = 0; // ADC reading of battery voltage
    
    ports_initialize(); //set up ports 
    ADC_initialize();    //configure ADC
    SPI_initialize(); // set up SPI module
    
    WDTCON = 0b00011101; // 16 sec period
    CLRWDT(); // clear WDT
    
    while(1)
    {
        SLEEP(); // sleep PIC until WDT expires
        
        time++; // increment time (+16s)
        
        battery_voltage = ADC_read(0x09); // read battery voltage
        
        if ( time >= 1 ) // 1*16s=16s
        {        
            time = 0; // reset time
            if(battery_voltage >= 690) //690 = 11v
            {
                LATCbits.LATC4 = 1; // turn relay on
            
                while( data != 0xDA ) // wait for shutdown command to be received
                {
                    while(!SSP1STATbits.BF) // wait till data is in the buffer
                    {
                        CLRWDT();
                    }
                    data = SSP1BUF; // read data outside
                }
            
                data = 0x00;
            
                __delay_ms(10000); // wait for R Pi to shutdown
            
                LATCbits.LATC4 = 0; // turn relay off
            }  
        }
    }    
}

// function to setup the microcontroller ports at boot
void ports_initialize(void)
{
    // clear all ports
    PORTA = 0x00;
    PORTC = 0x00;

    TRISA = 0x3C;   // bits 5: temperature (RA5); set as input (1)
                    // bit 4: button (RA4); set as input (1)
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