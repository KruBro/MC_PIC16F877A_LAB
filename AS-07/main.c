/**
 * @file main.c
 * @author krubro
 * @date 2026-04-14
 * @brief Main function
 */

#pragma config WDTE = OFF

#include "main.h"

void initConfig()
{
    /*RD0 RD1 and RD2 as Output*/ 
    TRISD &= 0xF8;
    PORTD |= 0xF8;

    /*Global Interrupt Enabled*/ 
    GIE = 1;

    /*Peripheral Interrupt Enabled*/
    PEIE = 1;
    initTimer0();
    initTimer1();
    initTimer2();
}

int main(){

    initConfig();

    while(1)
    {
        ;
    }

    return 0;
}
