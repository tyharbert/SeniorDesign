#include <xc.h>
#include "SPI.h"

void SPI_initialize(void)
{
    PPSLOCK = 0x55; // three write sequences to unlock PPS
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    SSP1CLKPPSbits.SSP1CLKPPS = 0x0010; // RC0->MSSP1:SCK1;
    SSP1DATPPSbits.SSP1DATPPS = 0x0011; // RC1->MSSP1:SDI1;
    RC2PPSbits.RC2PPS = 0x0019;         // RC2->MSSP1:SDO1;
    SSP1SSPPSbits.SSP1SSPPS = 0x0013;   // RC3->MSSP1:SS1;

    PPSLOCK = 0x55; // three write sequences to lock PPS
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    SSP1STAT = 0x40; // SMP cleared for slave mode
                     // CKE Active to Idle
                     // SSPBUF empty

    SSP1CON1 = 0x24; // WCOL: no collision
                     // SSPOV: no overflow
                     // SSPEN: serial port enabled 
                     // CKP: Idle:Low, Active:High
                     // SSPM: SPI slave mode with slave select enabled

    SSP1CON3 = 0x00;  // BOEN: buffer overflow disabled
}

unsigned char SPI_transfer(unsigned char data)
{
    SSP1BUF = data; // load SPI data into buffer to transfer
    while(!SSP1STATbits.BF); // wait till buffer is filled with received data
    return SSP1BUF; // return received data
}