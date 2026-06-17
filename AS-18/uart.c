#include "uart.h"
#include <xc.h>

void initUart(unsigned long baud_rate)
{
    /*High Baud Rate Select bit*/ 
    BRGH = 1;

    /*Serial Port Enable bit*/ 
    SPEN = 1;

    /*Continuous Receive Enable bit*/ 
    CREN = 1;

    /* Baud Rate Generator Register*/
    SPBRG = (FOSC / (16 * baud_rate)) - 1;

    /*Transmit Enable bit*/ 
    TXEN = 1;

    /*Interrupt Enable Bit*/ 
    RCIE = 1;

    /*Interrupt Flag Enable Bit*/ 
    RCIF = 0;
}

void putchar(unsigned char ch)
{
    while(TXIF != 1);       //Wait Until Ready

    TXREG = ch;
}

void puts(const char *str)
{
    while(*str)
    {
        putchar(*str);
        str++;
    }
}