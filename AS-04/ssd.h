#ifndef SSD_H
#define SSD_H

#include <xc.h>

#pragma config WDTE = OFF

#define LEVEL 0
#define EDGE 1

#define SW1 0x3E

#define ZERO  0X3f
#define ONE   0X06
#define TWO   0X5B
#define THREE 0X4F
#define FOUR  0X66
#define FIVE  0X6D
#define SIX   0X7D
#define SEVEN 0X07
#define EIGHT 0X7F
#define NINE  0X6F

void init_ssd();
void display(unsigned char *ssd);
unsigned char read_digital_keypad(unsigned char trigger_method);



#endif