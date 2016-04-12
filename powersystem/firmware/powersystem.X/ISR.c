#include <xc.h>
#include "ISR.h"

void ISR_initialize(void)
{ 
    IOCAP = 0x00; // no ioc PORTA positive edge
    IOCAN = 0x10; // RA4 ioc negative edge
    IOCCP = 0x00; // no ioc PORTC positive edge
    IOCCN = 0x00; // no ioc PORTC negative edge
    
    IOCAFbits.IOCAF4 = 0; // clear IOC on RA4 flag
    
    PIE0bits.IOCIE = 1; // interrupt on change for push button interrupt enabled
    INTCONbits.PEIE = 1; // enable peripheral interrupt
    INTCONbits.GIE = 1; // enable global interrupt
}

void interrupt ISR(void)
{
    if ( IOCAFbits.IOCAF4 ) // push button pressed 
    {
        time = 250; //set time above needed to exit sleep
        IOCAFbits.IOCAF4 = 0; //clear interrupt flag
    }
}
