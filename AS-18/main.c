/**
 * @file main.c
 * @author krubro
 * @date 2026-04-26
 * @brief Main function
 */

#include <xc.h>
#include "uart.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF

unsigned char ch;

void initConfig(void)
{
    /*Global Interrupt Enable Bit*/ 
    GIE = 1;

    /*Peripheral Interrupt Enable bit*/ 
    PEIE = 1;

    initDigitalkeypad();
    initUart(9600);
}

int main(){

    initConfig();
    unsigned char key;
    puts("UART TEST RUN\r\n");
    while(1)
    {
        key = read_digital_keypad(EDGE);
        if(key == SW1)
            puts("SWITCH 1 Pressed!\n\r");
        else if(key == SW2)
            puts("SWITCH 2 Preessed!\n\r");
        else if(key == SW3)
            puts("SWITCH 3 Pressed!\n\r");
        else if(key == SW4)
            puts("SWTICH 4 Pressed!\n\r");
    }
    return 0;
}
