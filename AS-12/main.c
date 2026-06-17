#include <xc.h>
#include "timer0.h"
#include "adc.h"
#include "pwm.h"

#pragma config WDTE = OFF       // Watch Dog Timer OFF

void initConfig()
{
    initTimer0();
    initADC();
    initPWM();
}

int main() {
    initConfig();
    
    unsigned short curr_val = 0;
    unsigned short prev_val = 0xFFFF; // Initialized to an impossible ADC value to force the first update
    
    while(1)
    {
        // 1. Read the value of pot
        curr_val = read_adc_channel(0x00);
        
        // 2. If it is different from previous value, update duty cycle
        if(curr_val != prev_val)
        {
            prev_val = curr_val;
            pwm_control(curr_val);
        }
        // 3. If it is the same, do nothing (implicitly handled by skipping the if-block)
    }

    return 0;
}