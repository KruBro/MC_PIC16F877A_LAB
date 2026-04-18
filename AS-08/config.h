#ifndef CONFIG_H
#define CONFIG_H

#include <xc.h>
#define _XTAL_FREQ 20000000


void initTimer0();
void __interrupt() isr();

#endif