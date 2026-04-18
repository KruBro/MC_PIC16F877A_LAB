#include "config.h"

unsigned char second = 0; 
unsigned char blink_dot = 0;

void __interrupt() isr()
{
    static unsigned int count = 0;  // FIX: Must be unsigned int to hold 20000
    
    if(TMR0IF)
    {
        TMR0 = TMR0 + 8;            // Reduce Drift
        count++;

        if(count == 20000)     // One full second passed (1000ms)
        {
            blink_dot = !(blink_dot);          // Turn dot OFF
            count = 0;              // Reset count
            second++;               // Increment second
        }
        
        TMR0IF = 0;                 // Clear the interrupt flag
    }
}