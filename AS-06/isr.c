#include "main.h"

extern volatile unsigned int count;

void __interrupt() isr()
{
    //If flag is set
    //Reset Count and Flag
    if(INTF)
    {
        count = 0;
        INTF = 0;
    }
}