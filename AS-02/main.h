#ifndef MAIN_H
#define MAIN_H

#include <xc.h>

#pragma config WDTE = OFF
#define _XTAL_FREQ 20000000 

#define KEYPAD_PORT PORTB   
#define EDGE 1
#define LEVEL 0

#define SW1 0x3E
#define SW2 0x3D
#define SW3 0x3B
#define SW4 0x37

void initConfig();
unsigned char read_digital_keypad(unsigned char trigger_method);

void pattern1();
void pattern2();
void pattern3();
void pattern4();

#endif