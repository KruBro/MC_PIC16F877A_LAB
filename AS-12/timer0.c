#include "timer0.h"
#include <xc.h>

void initTimer0()
{ 
    GIE = 1;        //Global Interrupt Enable Bit
    PEIE = 1;       //Peripheral Interrupt Enable Bit
    TMR0IE = 1;     //Timer 0 Interrupt Enable bit

    TMR0IF = 0;     //Timer0 interrupt flag enable
    T0CS = 0;       //Internal instruction cycle clock (CLKO)
    PSA = 1;        //Prescaler Assignment bit
    TMR0 = 6;       //Preload The Timer 0 with 6
}