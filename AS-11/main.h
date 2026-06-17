#ifndef MAIN_H
#define MAIN_H

#include <xc.h>

#define _XTAL_FREQ 20000000
#define KEYPAD_PORT PORTB

#define EDGE 0
#define LEVEL 1

#define SW1 0x3E

extern volatile unsigned char second;
extern volatile unsigned int count; 

void initTimer0();
void init_keypad();
void __interrupt() isr();
unsigned char read_digital_keypad(unsigned char trigger_method);

#endif