#include "main.h"
#include <pic16f877a.h>

volatile unsigned char second = 0;
volatile unsigned int count = 0;

void __interrupt() isr()
{
    if(TMR0IF)
    {
        TMR0 = TMR0 + 8;
        if(count++ == 20000)
        {
            count = 0;
            second++;
        }
        TMR0IF = 0;
    }
}