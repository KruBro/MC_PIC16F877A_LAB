/*
@author : Shahad K
@aim    : Implement a right scrolling message marquee on CLCD.
@date   : 18-04-2026
*/ 
#include "config.h"
#include "clcd.h"

void main(void) {
    // Ensure multiplexed analog pins on PORTE act as digital I/O
    ADCON1 = 0x06;  

    LCD_Init();
    
    // Draw the static UI
    char str[19] = "___Good Morning___";
    LCD_SetCursor(0, 0);
    LCD_String("Right Scrolling");

    char temp;
    static unsigned char delay = 0;
    while(1) {
        LCD_SetCursor(1, 0);
        LCD_String(str);
        if(delay++ == 25)
        {
            delay = 0;
            temp = str[17];
            for(int i = 17; i >= 0; i--)
            {
                str[i] = str[i - 1];
            }
            str[0] = temp;
            str[18] = '\0';
        }
    }
}