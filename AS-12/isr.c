#include "timer0.h"
#include "pwm.h"
#include <xc.h>

unsigned char timer_cycle = 0;

void __interrupt() isr()
{
    if(TMR0IF)
    {
        TMR0 = TMR0 + 8; // Preload timer
        TMR0IF = 0;      // CLEAR the interrupt flag (Crucial step!)
        
        timer_cycle++;
        
        if(timer_cycle >= 100)
        {
            timer_cycle = 0; // Reset cycle at 100%
        }
        
        // Software PWM Logic: Toggle pin based on current cycle vs target duty
        if(timer_cycle < duty_cycle)
        {
            RD0 = 1; // Output HIGH
        }
        else
        {
            RD0 = 0; // Output LOW
        }
    }
}