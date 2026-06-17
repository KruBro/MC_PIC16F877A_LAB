#ifndef UART_H
#define UART_H

#define FOSC 20000000

extern unsigned char ch;

void initUart(unsigned long baud_rate);
void putchar(unsigned char ch);
void puts(const char *str);
void __interrupt() isr(void);

#endif