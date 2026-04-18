/**
 * @file main.c
 * @author Shahad K
 * @date 2026-04-09
 * @brief Assignment 05
 * @aim Implement a 4 digit key press counter with persistence using Internal EEPROM.
 **/

#include "main.h" 

void initConfig()
{
    TRISB |= 0x3F;      //Configure PORTB as INPUT
    ssdInit();      
}

int main(){

    initConfig();

    unsigned char ssd[4];
    unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

    unsigned char key;
    unsigned int wait = 0;
    static unsigned char count = 0;
    unsigned char isSW2Pressed = 0;

    count = eeprom_read(0x00);
    if(count == 0xFF) { 
        count = 0; // Default to 0 on a brand new microcontroller
    }

    while(1)
    {
        ssd[0] = digits[count / 1000];          // Thousands: 1234 / 1000 = 1
        ssd[1] = digits[(count / 100) % 10];    // Hundreds: (1234 / 100) = 12, 12 % 10 = 2
        ssd[2] = digits[(count / 10) % 10];     // Tens: (1234 / 10) = 123, 123 % 10 = 3
        ssd[3] = digits[count % 10];            // Units: 1234 % 10 = 4

        display(ssd);

        key = read_digital_keypad(LEVEL);

        //If Swich1 is pressed increment the wait
        if(key == SW1)
        {
            wait++;
        }
        //if switch 2 is pressed, store the count in eeprom
        else if(key == SW2)
        {
            if(isSW2Pressed == 0)
            { 
               eeprom_write(0x00, count);
               isSW2Pressed = 1;
            }
        }
        //If All keys are Released
        else if(key == 0x3F)
        {
            isSW2Pressed = 0;
            //Watch the Wait
            //If it is under 2sec
            //Increment the counter
            if(wait > 0 && wait < 50)
            {
                count++;
            }
            //if it exceeds 2 sec
            //Reset the counter
            else if(wait > 100)
            {
                count = 0;
            }
            wait = 0;
        }
    }

    return 0;
}
