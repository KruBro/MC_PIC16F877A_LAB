#include <xc.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#define _XTAL_FREQ 20000000

void initConfig() {
    // ADCON1 = 0x06; // Set all pins to Digital
    TRISD = 0x00;  // PORTD as Output
    PORTD = 0x00;  // Start with empty tunnel
}

int main() {
    initConfig();

    int i = 0;

    unsigned long int delay = 0;
    while (1) {
        if(delay++ == 50000)
        {
            delay = 0;
            if(i < 8)
            {
                PORTD = PORTD << 1 | 0x01;
                i++;
            }
            else if(i < 16)
            {
                PORTD = PORTD << 1;
                i++;
            }
            else if(i < 24)
            {
                PORTD = PORTD >> 1 | 0x80;
                i++;
            }
            else if(i < 32)
            {
                PORTD = PORTD >> 1;
                i++;
            }
            else
            {
                i = 0;
                PORTD = 0x00;
            }
        }
    }
    return 0;
}