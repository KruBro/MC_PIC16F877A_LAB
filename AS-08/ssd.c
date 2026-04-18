#include "ssd.h"

void init_ssd()
{
    TRISD = 0x00; // PORTD as output port
    TRISA = TRISA & 0xC3;  // PORTA as output (RA2 to RA5)
    PORTA = PORTA & 0xC3;  // All SSD's off
    
    // ADDED: Configure Keypad pins as inputs (assuming RB0-RB5)
    TRISB = TRISB | 0x3F; 
}

void display(unsigned char *ssd)
{
    for(int i = 0; i < 4; i++)
    {
        PORTD = ssd[i]; // load data into PORTD
        PORTA =  (PORTA & 0xC3) | (0x04 << i); // Turn on required SSD
        for(unsigned int wait = 500; wait--; ); // Small Delay for persistence of vision
    }
}
