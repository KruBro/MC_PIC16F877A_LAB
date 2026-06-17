#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#define LEVEL 1
#define EDGE 0

#define SW1 0x3E
#define SW2 0x3D
#define SW3 0x3B
#define SW4 0x37

void initDigitalkeypad(void);
unsigned char read_digital_keypad(unsigned char trigger_method);

#endif