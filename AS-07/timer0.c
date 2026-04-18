#include "main.h"

void initTimer0()
{
    /*Timer 1 Interrupt Enabled*/ 
    TMR0IE = 1;

    /*Internal instruction cycle clock (CLKO)*/ 
    T0CS = 0;

    /*Preload with 6*/ 
    TMR0 = 6;

    /*Timer 0 interrupt Flag*/ 
    TMR0IF = 0;

    /*Prescaler is assigned to the WDT*/ 
    PSA = 1;    
}
