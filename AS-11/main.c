/*@author   : Shahad K*/
/*@aim      : Implement a point brightness control*/  
/*@date     : 20-04-2026*/ 

#include "main.h"

#pragma config WDTE = OFF


/*Startup Configuration*/ 
void initConfig()
{
    TRISD0 = 0;
    RD0 = 0;
    initTimer0();
    init_keypad();
}

int main(){
    initConfig();
    //Setting PWM Dutry Cycle, Period
    unsigned char period = 100, program_cycle = 0, delay = 0;
    unsigned char duty_cycle = 10;
    unsigned char key;
    while(1)
    {
        key = read_digital_keypad(EDGE);
        if(key == SW1)
        {
            duty_cycle = 100;
            second = 0;
            count = 0;
        }

        if(second == 5)
        {
            second = 0;
            duty_cycle = 10;
        }
        if(delay++ == 50) 
        {
            delay = 0;
            
            // 1. Evaluate the PWM state FIRST
            if(program_cycle < duty_cycle)
            {
                RD0 = 1;
            }
            else
            {
                RD0 = 0;
            }

            // 2. Increment the cycle AFTER evaluating
            program_cycle++;

            // 3. Reset when the period completes
            if(program_cycle >= period)
            {
                program_cycle = 0;
            }
        }
    }
    return 0;
}