#include "clcd.h"

void LCD_Pulse(void) {
    LCD_EN = 1;
    __delay_us(20);
    LCD_EN = 0;
    __delay_us(200);
}

void LCD_Command(unsigned char cmd) {
    LCD_RS = 0;
    LCD_RW = 0;

    // Send the entire 8-bit command at once
    LCD_DATA_PORT = cmd; 
    LCD_Pulse();

    __delay_ms(2);
}

void LCD_Char(unsigned char data) {
    LCD_RS = 1;
    LCD_RW = 0;

    // Send the entire 8-bit data at once
    LCD_DATA_PORT = data;
    LCD_Pulse();

    __delay_ms(2);
}

void LCD_Init(void) {
    // All 8 pins set to output for 8-bit mode
    LCD_DATA_TRIS = 0x00; 

    LCD_RS_TRIS = 0;
    LCD_RW_TRIS = 0;
    LCD_EN_TRIS = 0;

    LCD_EN = 0;

    __delay_ms(20);

    LCD_RS = 0;
    LCD_RW = 0;

    // Initialization sequence (critical)
    LCD_DATA_PORT = 0x30;
    LCD_Pulse();
    __delay_ms(5);

    LCD_DATA_PORT = 0x30;
    LCD_Pulse();
    __delay_us(200);

    LCD_DATA_PORT = 0x30;
    LCD_Pulse();

    // 8-bit initialization commands
    LCD_Command(0x38); // 8-bit, 2 line, 5x8 dots (Changed from 0x28)
    LCD_Command(0x0C); // display ON
    LCD_Command(0x06); // entry mode
    LCD_Command(0x01); // clear

    __delay_ms(2);
}

void LCD_Clear(void) {
    LCD_Command(0x01);
    __delay_ms(2);
}

void LCD_SetCursor(unsigned char row, unsigned char col) {
    unsigned char address;

    if (row == 0)
        address = 0x80 + col;
    else
        address = 0xC0 + col;

    LCD_Command(address);
}

void LCD_String(const char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}