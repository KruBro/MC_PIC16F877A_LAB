#include "main.h"

unsigned char read_digital_keypad(unsigned char trigger_method)
{
    static unsigned char isOn = 1;
    if(trigger_method == LEVEL)
    {
        return KEYPAD_PORT & 0x3F;
    }
    else if(trigger_method == EDGE)
    {
        if(((KEYPAD_PORT & 0x3F) != 0x3F) && isOn)
        {
            __delay_ms(20);
            if((KEYPAD_PORT & 0x3F) != 0x3F) 
            {
                isOn = 0;
                return (KEYPAD_PORT & 0x3F);
            }
        }
        else if((KEYPAD_PORT & 0x3F) == 0x3F) 
        {
            isOn = 1;
        }
    }

    return 0x3F;
}