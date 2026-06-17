#include "main.h"

void initTimer0()
{
    GIE = 1;        //Global Interrupt Enable Bit

    PEIE = 1;       //Peripheral Interrupt Enable Bit

    TMR0 = 6;       //Preload Timer with 6

    TMR0IF = 0;     //Timer 0 Interrupt Flag Enable Bit

    TMR0IE = 1;     //Timer 0 Interrupt Enable Bit

    PSA = 1;        //Prescaler Assignment bit

    T0CS = 0;       //TMR0 Clock Source Select bit
}