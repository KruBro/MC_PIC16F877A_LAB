#include "ssd.h"

//
unsigned char read_digital_keypad(unsigned char trigger_method)
{
    static unsigned char once = 1;
    static unsigned int delay = 0;

    //If Method is Level
    if(trigger_method == LEVEL)
        return PORTB & 0x3F;
    //If method is edge
    if(trigger_method == EDGE)
    {
        //Small Delay to reduce eliminate bouncing effect
        if(delay++ == 200)
        {
            delay = 0;    //Reset delay
            //If Key is Pressed
            if((PORTB & 0x3F) != 0x3F && once)
            {
                once = 0;
                return PORTB & 0x3F;
            }
            //If Key is Released
            else if((PORTB & 0x3F) == 0x3F)
            {
                once = 1;
            }
        }
    }

    return 0x3F;
}