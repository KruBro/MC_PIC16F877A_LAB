/**
 * @author Shahad K
 * @date    09-04-2026
 * @brief   Implement system sleep and wake up while Interrupt on change (Shown in the video).
 * **/ 

#include "main.h"

volatile unsigned int count = 0;

void initConfig()
{
    TRISB = 0x00;
    PORTB = 0x00;
    ssdInit();
    init_ext_interrtup();   
}

int main(){

    initConfig();

    unsigned char ssd[4];
    unsigned long delay = 0; 
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
    
    ssd[0] = digits[1];
    ssd[1] = digits[2];
    ssd[2] = digits[3];
    ssd[3] = digits[4];

    while(1)
    {
        display(ssd); // Keep SSD turned ON

        // You will need to tune this number (e.g., to 500 or 1000) 
        // because display() now adds a huge delay to the loop.
        if(delay++ == 255) 
        {
            delay = 0;
            RB7 = ~RB7;
            count++;
        }

        if(count == 5)
        {
            // Optional: turn off SSD before sleeping to save power
            PORTA = 0x00; 
            PORTD = 0x00;
            SLEEP();
        }
    }
    return 0;
}