#include "main.h"

void pattern3()
{
    // Toggle between 10101010 and 01010101
    PORTD = (PORTD == 0xAA) ? 0x55 : 0xAA;
}