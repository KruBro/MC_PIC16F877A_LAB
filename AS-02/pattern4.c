#include "main.h"

void pattern4()
{
    // Toggle between first 4 LEDs ON / next 4 OFF, and vice versa
    PORTD = (PORTD == 0xF0) ? 0x0F : 0xF0;
}