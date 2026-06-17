#include "digital_keypad.h"
#include <xc.h>

void init_digital_keypad()
{
    TRISB2 = 1;
    RB2 = 1; 
}

unsigned char read_digital_keypad(unsigned char trigger_method)
{
    static unsigned char once = 1;
    if(trigger_method == LEVEL)
    {
        return KEYPAD_PORT & ALL_RELEASED;
    }
    else if(trigger_method == EDGE)
    {
        if((KEYPAD_PORT & ALL_RELEASED) != ALL_RELEASED && once)
        {
            for(unsigned int i = 0; i < 500; i++);     //Small Delay
            if((KEYPAD_PORT & ALL_RELEASED) != ALL_RELEASED)
            {
                once = 0; // Consume the edge flag
                return KEYPAD_PORT & ALL_RELEASED;
            }
        }
        else if((KEYPAD_PORT & ALL_RELEASED) == ALL_RELEASED)
        {
            once = 1; // Reset flag only when switch is fully released
        }
    }

    return ALL_RELEASED;
}