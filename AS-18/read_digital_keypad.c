#include "digital_keypad.h"
#include <xc.h>

void initDigitalkeypad(void)
{
    TRISB |= 0x3F;
    PORTB &= 0x3F;
}

unsigned char read_digital_keypad(unsigned char trigger_method)
{
    static unsigned char once = 1;
    if(trigger_method == LEVEL)
        return (PORTB & 0x3F);
    else if(trigger_method == EDGE)
    {
        if(((PORTB & 0x3F) != 0x3F) && once)
        {
            for(int i = 0; i < 500; i++);       //Small Delay
            
            if((PORTB & 0x3F) != 0x3F)
            {
                once = 0;
                return (PORTB & 0x3F);
            }
        }
        else if((PORTB & 0x3F) == 0x3F)
        {
            once = 1;
        }
    }

    return (0x3F);
}