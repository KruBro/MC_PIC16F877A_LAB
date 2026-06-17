#include "main.h"

void pattern1()
{
    static unsigned char phase = 0;
    static unsigned char step = 0;

    switch(phase) {
        case 0: // Glow Left to Right
            PORTD = (PORTD << 1) | 0x01;
            if (++step >= 8) { step = 0; phase = 1; }
            break;
        case 1: // Turn off Left to Right
            PORTD = PORTD << 1;
            if (++step >= 8) { step = 0; phase = 2; }
            break;
        case 2: // Glow Right to Left
            PORTD = (PORTD >> 1) | 0x80;
            if (++step >= 8) { step = 0; phase = 3; }
            break;
        case 3: // Turn off Right to Left
            PORTD = PORTD >> 1;
            if (++step >= 8) { step = 0; phase = 0; }
            break;
    }
}