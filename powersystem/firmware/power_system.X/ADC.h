/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once. 
#ifndef ADC_H
#define	ADC_H

// function to set up the ADC
void ADC_initialize(void);

// reads an analog input
unsigned int ADC_read(unsigned char channel);

#endif
