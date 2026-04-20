#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#include <xc.h>

#define _XTAL_FREQ 20000000

#define SW1             0x3E            
#define SW2             0x3D
#define ALL_RELEASED    0x3F

#define KEYPAD_PORT     PORTB

#define LEVEL           0
#define EDGE            1

void initKeypad(void);
unsigned char read_digital_keypad(unsigned char trigger_method);

#endif /* DIGITAL_KEYPAD_H */