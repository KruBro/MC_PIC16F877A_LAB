/**
 * @file main.c
 * @author krubro
 * @date 2026-03-25
 * @brief Main function
 */

#include "ssd.h"

void initConfig()
{
    init_ssd();
}

int main(){

    initConfig();
    unsigned char ssd[4];
    unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, 0x08, 0x08};

    unsigned char count = 0;
    unsigned int delay = 0;
    while(1)
    {
        ssd[0] = digit[(count) % 12];
        ssd[1] = digit[(count + 1) % 12];
        ssd[2] = digit[(count + 2) % 12];
        ssd[3] = digit[(count + 3) % 12];

        display(ssd);

        if(delay++ == 50)
        {
            delay = 0;
            count++;
            if(count == 12)
                count = 0;
        }
    }
    return 0;
}
