#ifndef TIMER0_H
#define TIMER0_H

extern unsigned char timer_cycle;
void initTimer0();
void __interrupt() isr();

#endif