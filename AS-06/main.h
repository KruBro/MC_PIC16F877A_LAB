#ifndef MAIN_H
#define MAIN_H

#include <xc.h>

#pragma config WDTE = OFF
#define _XTAL_FREQ 200000

#define ZERO  0X3f      //0
#define ONE   0X06      //1
#define TWO   0X5B      //2
#define THREE 0X4F      //3
#define FOUR  0X66      //4
#define FIVE  0X6D      //5
#define SIX   0X7D      //6
#define SEVEN 0X07      //7
#define EIGHT 0X7F      //8
#define NINE  0X6F      //9

void ssdInit();
void display(unsigned char *ssd);

void init_ext_interrtup();
void __interrupt() isr();


#endif