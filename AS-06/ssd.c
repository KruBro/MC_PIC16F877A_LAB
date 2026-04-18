#include "main.h"

void ssdInit()
{
    TRISD = 0x00;       //Configure PORTD as Outputs
    PORTD = 0x00;

    TRISA &= 0xC3;
    PORTA &= 0xC3;
}

void display(unsigned char *ssd)
{
    for(unsigned int i = 0; i < 4; i++)
    {
        PORTD = ssd[i]; // Load the data
        PORTA = (PORTA & 0xC3) | (0x04 << i);   //Turn on required SSDs
        for(unsigned int j = 0; j < 500; j++);  //small Delay
    }
}