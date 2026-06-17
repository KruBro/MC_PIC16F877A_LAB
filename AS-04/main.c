/**
 * @file main.c
 * @author krubro
 * @date 2026-03-27
 * @brief Main function
 */

#include "ssd.h"

void initConfig()
{
    TRISB |= 0x3F; //Configure PORTB as input
    init_ssd();
}
int main(){

    initConfig();

    unsigned char ssd[4];       //Data Control lines 
    unsigned char key;
    unsigned int wait = 0;
    unsigned int count = 0;
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

    while(1)
    {
        //Store Output of read_digital_keypad
        key = read_digital_keypad(LEVEL);
        
        //If key is pressed
        if(key == SW1)
        {
            //Start the timer
            wait++;
        }
        //If Key is released
        else
        {
            //Check the timer value
            //If it stays under 2 sec
            if(wait > 0 && wait < 50)
            {
                //increment the counter
                count++;

                //If counter value exceeds the value 9
                if(count > 9)
                    count = 0;      //reset the counter
            }
            //If it exceeds two seconds
            else if(wait > 100)
            {
                count = 0;   //reset the counter
            }

            wait = 0;       //reset the timer
        }

        ssd[0] = digits[0];
        ssd[1] = digits[0];
        ssd[2] = digits[0];
        ssd[3] = digits[count];

        //display the counter value;
        display(ssd);
    }
    return 0;
}
