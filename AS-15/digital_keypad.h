#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H


#define SW2 0x3B

#define LEVEL 1
#define EDGE 0

#define KEYPAD_PORT PORTB
#define ALL_RELEASED 0x3F

void init_digital_keypad();
unsigned char read_digital_keypad(unsigned char trigger_method);

#endif