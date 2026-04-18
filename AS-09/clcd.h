#ifndef CLCD_H
#define CLCD_H

#include "config.h"

// Use only upper 4 bits of PORTD
#define LCD_DATA_PORT PORTD
#define LCD_DATA_TRIS TRISD

// Control pins (keep your mapping)
#define LCD_RS RE2
#define LCD_RW RE0
#define LCD_EN RE1

#define LCD_RS_TRIS TRISE2
#define LCD_RW_TRIS TRISE0
#define LCD_EN_TRIS TRISE1

void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_String(const char *str);
void LCD_Clear(void);
void LCD_SetCursor(unsigned char row, unsigned char col);

#endif