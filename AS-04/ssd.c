#include "ssd.h"

void init_ssd()
{
    TRISD = 0x00; // PORTD as OUTPUT PORT
    PORTD = 0x00; // All Leds OFF

    TRISA = TRISA & 0xC3; //PORTA as OUTPUT PORT
     PORTA = PORTA & 0xC3; //All SSDs OFF
}

void display(unsigned char *ssd)
{
    for(unsigned int i = 0; i < 4; i++)
    {
        PORTD = ssd[i];       // Loading the data
        PORTA = (PORTA & 0xC3) | (0x04 << i); // TURN On Required SSDs
        for(unsigned int j = 0; j < 500; j++); //Delay
    }
}