#ifndef ISR_H
#define	ISR_H

extern volatile unsigned int time;

void ISR_initialize(void);
void interrupt ISR(void);

#endif

