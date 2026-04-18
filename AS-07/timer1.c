#include "main.h"

void initTimer1()
{
    /*Set the prescaler 1 : 1*/
    T1CKPS1 = 0;
    T1CKPS0 = 0;

    /*Oscillator is shut-of*/ 
    T1OSCEN = 0;

    /* Internal clock (FOSC/4) */ 
    TMR1CS = 0;

    /*Timer 1 Interrupt Flag*/ 
    TMR1IF = 0;

    /*Timer 1 Interrupt Enabled*/ 
    TMR1IE = 1;

    /*Timer 1 On Bit*/ 
    TMR1ON = 1;

    /*Preload Timer 1*/
    TMR1 = 3036;
}