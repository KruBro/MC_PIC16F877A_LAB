#include "digital_keypad.h"

void initKeypad(void)
{
    TRISB = TRISB | 0x3F;
    KEYPAD_PORT = KEYPAD_PORT & 0x3F;
}

unsigned char read_digital_keypad(unsigned char trigger_method)
{
    static unsigned char isOn = 1;
    
    if (trigger_method == LEVEL)
    {
        return KEYPAD_PORT & ALL_RELEASED;
    }
    else if (trigger_method == EDGE)
    {
        // 1. Detect the Press
        if (((KEYPAD_PORT & ALL_RELEASED) != ALL_RELEASED) && isOn)
        {
            __delay_ms(50); // Increased debounce time to 50ms for stubborn switches
            
            if ((KEYPAD_PORT & ALL_RELEASED) != ALL_RELEASED) 
            {
                isOn = 0; // Lock the switch out from triggering again
                return (KEYPAD_PORT & ALL_RELEASED);
            }
        }
        // 2. Detect the Release (THIS IS THE FIX)
        else if (((KEYPAD_PORT & ALL_RELEASED) == ALL_RELEASED) && !isOn) 
        {
            __delay_ms(50); // Wait for the mechanical release bounce to settle
            
            if ((KEYPAD_PORT & ALL_RELEASED) == ALL_RELEASED) 
            {
                isOn = 1; // Only unlock after we are 100% sure it's released
            }
        }
    }

    return ALL_RELEASED;
}