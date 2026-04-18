#include "main.h"

void initConfig()
{
    TRISD = 0x00;
    PORTD = 0x00;

    TRISB = TRISB | 0x3F;
}