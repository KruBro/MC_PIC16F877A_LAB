/**
 * @file main.c
 * @brief Main function
 */
#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF

void init_Config()
{
    init_digital_keypad();
    ssdInit();    
}

int main()
{
    init_Config();

    unsigned char ssd[4];
    // SSD_ZERO added to align indices (digits[0] now correctly points to SSD_ZERO)
    unsigned char digits[10] = {SSD_ZERO, SSD_ONE, SSD_TWO, SSD_THREE, SSD_FOUR, SSD_FIVE, SSD_SIX, SSD_SEVEN, SSD_EIGHT, SSD_NINE};
    unsigned char key;
    unsigned int count = 0;
    unsigned char program_cycle = 0;

    // Read 16-bit count from EEPROM once during boot
    unsigned char high_byte = eeprom_read(0x00);
    unsigned char low_byte = eeprom_read(0x01);
    count = ((unsigned int)high_byte << 8) | low_byte;

    // Handle uninitialized EEPROM or out-of-bounds count
    if(count == 0xFFFF || count > 9999)
    {
        count = 0;
    }

    while(1)
    {
        if(program_cycle++ == 25)
        {
            program_cycle = 0;
            count++;
            
            // Prevent counter from exceeding 4 digits
            if (count > 9999) 
            {
                count = 0; 
            }
        }
        
        ssd[0] = digits[count / 1000];
        ssd[1] = digits[(count / 100) % 10];
        ssd[2] = digits[(count / 10) % 10];
        ssd[3] = digits[count % 10];

        display(ssd);

        key = read_digital_keypad(EDGE);

        if(key == SW2)
        {
            // Split the 16-bit count into two 8-bit bytes to store in EEPROM
            eeprom_write(0x00, (unsigned char)(count >> 8)); // High Byte
            eeprom_write(0x01, (unsigned char)(count & 0xFF)); // Low Byte
        }
    }
    return 0;
}