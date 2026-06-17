#ifndef SSD_H
#define SSD_H

#define DATA_PORT PORTD
#define DISPLAY_SELECT PORTA

#define SSD_ZERO  0x3f
#define SSD_ONE   0x06
#define SSD_TWO   0x5B
#define SSD_THREE 0x4F
#define SSD_FOUR  0x66
#define SSD_FIVE  0x6D
#define SSD_SIX   0x7D
#define SSD_SEVEN 0x07
#define SSD_EIGHT 0x7F
#define SSD_NINE  0x6F

void ssdInit();
void display(unsigned char *ssd);

#endif