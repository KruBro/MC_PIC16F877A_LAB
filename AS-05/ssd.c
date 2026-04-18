#include "main.h"

void ssdInit()
{
    TRISD = 0x00;       //Configure PORTD as OUTPUT
    PORTD = 0x00;       //All Leds OFF
    
    TRISA &= 0xC3;      //PORTA as OUTPUT
    PORTA &= 0xC3;      //All SSDs OFF
}

void display(unsigned char *ssd)
{
    for(unsigned int i = 0; i < 4; i++)
    {
        PORTD = ssd[i];                         //Loading the DATA
        PORTA = (PORTA & 0xC3) | (0x04 << i);   // TURN ON REQUIRED SSDs
        for(unsigned int j = 0; j < 500; j++);  //Small Delay
    }
}