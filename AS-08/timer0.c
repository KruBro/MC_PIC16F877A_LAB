#include "config.h" 

void initTimer0()
{
    /*Global Interrupt Enable Bit*/ 
    GIE = 1;

    /*Peripheral Interrupt Enable Bit*/ 
    PEIE = 1;

    /*Timer 0 Interrupt Enable Bit*/ 
    TMR0IE = 1;

    /*TMR0 Clock Source Select bit*/ 
    T0CS = 0;

    /*Prescaler Assignment bit */ 
    PSA  = 1;


    TMR0 = 6;
}