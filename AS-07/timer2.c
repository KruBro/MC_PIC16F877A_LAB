#include "main.h"

void initTimer2()
{
    /*Timer 2 Interrupt Enabled*/ 
    TMR2IE = 1;

    /*Timer 2 Interrupt Flag*/ 
    TMR2IF = 0;

    /*PR2 Register*/ 
    PR2 = 249;

    /*Timer 2 is On*/ 
    TMR2ON = 1;

    /*Timer 2 Prescale is set 1:1*/ 
    T2CKPS1 = 0;
    T2CKPS0 =  0;
}