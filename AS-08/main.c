/**
 * @file main.c
 * @author krubro
 * @date 2026-04-15
 * @brief Main function
 */
#include "config.h"
#include "ssd.h"

#pragma config WDTE = OFF

unsigned char minute = 0;
extern unsigned char second;
extern unsigned char blink_dot;


void initConfig()
{
    init_ssd();
    initTimer0();    
}

int main(){
    initConfig();

    // Start clock at 12:00
    static unsigned char hour = 12;

    unsigned char ssd[4];
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

    while(1)
    {
        // 1. Fetch proper 7-segment patterns for the current time
        ssd[0] = digits[(hour / 10)];
        ssd[1] = digits[(hour % 10)];
        ssd[2] = digits[(minute / 10)];
        ssd[3] = digits[(minute % 10)];

        // 2. Add the blinking decimal point to the one's place of the hour
        if (blink_dot) 
        {
            ssd[1] = ssd[1] | 0x80; // Turn on DP segment
        }

        // 3. Output the patterns to the hardware
        display(ssd);

        // 4. Time keeping logic
        if(second > 59)
        {
            second = 0;
            minute++;
        }

        // Reset the minute if it exceeds 59 and increment hour
        if(minute > 59)
        {
            minute = 0;
            hour++;
        }

        // Reset the hour if it exceeds 23 (24-hour format)
        if(hour > 23)
        {
            hour = 0;
        }
    }
    return 0;
}