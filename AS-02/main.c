/**
 * @file main.c
 * @author krubro
 * @date 2026-03-24
 * @brief Main function
 */
#include "main.h"

int flag = 0;

int main(){
    initConfig();
    unsigned char key;
    unsigned char current_pattern = 0;
    unsigned int delay = 0;
    
    while(1)
    {
        key = read_digital_keypad(EDGE);
        
        // If a new valid key is pressed, change pattern immediately
        if(key != 0x3F) 
        {
            if(key == SW1)  current_pattern = 1;
            else if(key == SW2) current_pattern = 2;
            else if(key == SW3) current_pattern = 3;
            else if(key == SW4) current_pattern = 4;
            
            PORTD = 0x00; 
            delay = 0;    
        }

        if(delay++ == 50000)
        {
            delay = 0; 
            
            switch (current_pattern)
            {
                case 1:
                    pattern1();
                    break;
                case 2:
                    pattern2();
                    break;
                case 3:
                    pattern3();
                    break;
                case 4:
                    pattern4(); 
                    break;
                default:
                    PORTD = 0x00;
                    break;
            }
        }
    }
    return 0;
}