#include "main.h"

void __interrupt() isr()
{
    static unsigned count = 0;
    static unsigned count1 = 0;
    static unsigned count2 = 0;
    if(TMR0IF)
    {
        TMR0 = TMR0 + 8;        //Compensating for Drift
        if(count++ == 20000)
        {
            count = 0;
            RD0 = !RD0;
        }
        TMR0IF = 0;
    }

    if(TMR1IF)
    {
        TMR1 = TMR1 + 3038;     //Compensating for Drift
        if(count1++ == 80)
        {
            count1 = 0;
            RD1 = !RD1;
        }
        TMR1IF = 0;
    }

    if(TMR2IF)
    {
        if(count2++ == 20000)
        {
            count2 = 0;
            RD2 = !RD2;
        }
        TMR2IF = 0;
    }
}