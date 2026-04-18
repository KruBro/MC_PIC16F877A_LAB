#ifndef CONFIG_H
#define	CONFIG_H

// PIC16F877A Configuration Bits
#pragma config FOSC = HS        // High-Speed Oscillator
#pragma config WDTE = OFF       // Watchdog Timer Disabled
#pragma config PWRTE = ON       // Power-up Timer Enabled
#pragma config BOREN = ON       // Brown-out Reset Enabled
#pragma config LVP = OFF        // Low-Voltage Programming Disabled
#pragma config CPD = OFF        // Data EEPROM Code Protection Off
#pragma config WRT = OFF        // Flash Program Memory Write Enable Off
#pragma config CP = OFF         // Code Protection Off

#define _XTAL_FREQ 20000000     // 20 MHz clock frequency for __delay_ms()

#include <xc.h>

#endif	/* CONFIG_H */