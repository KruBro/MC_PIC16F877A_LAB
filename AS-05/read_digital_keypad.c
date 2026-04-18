#include "main.h"

unsigned char read_digital_keypad(unsigned char trigger_method)
{
    static unsigned int once = 1;
    static unsigned char delay = 0;
    if(trigger_method == LEVEL)
    {
        return PORTB & 0x3F;
    }
    else if(trigger_method == EDGE)
    {
        // Small delay to reduce the bouncing effect 
        if(delay++ == 200)
        {
            delay = 0;

            //Pressed
            if(((PORTB & 0x3F) != 0x3F) && once)
            {

                once = 0;
                return PORTB & 0x3F;
            }

            //Released
            else if((PORTB & 0x3F) == 0x3F)
            {
                once = 1;
            }
        }
    }
    return 0x3F;
}