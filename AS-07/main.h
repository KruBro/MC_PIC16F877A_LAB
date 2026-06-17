#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#define _XTAL_FREQ 20000000

void initTimer0();
void initTimer1();
void initTimer2();
void __interrupt() isr();

#endif