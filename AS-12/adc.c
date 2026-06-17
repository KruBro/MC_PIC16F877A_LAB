#include "adc.h"
#include <xc.h>

void initADC()
{
    /*A/D Conversion Clock Select bits*/ 
    ADCS2 = 0;
    ADCS1 = 1;
    ADCS0 = 0;

    /*A/D On bit*/ 
    ADON = 1;

    /* A/D Configuration: Left justified, all pins Analog */ 
    ADCON1 = 0x00; 
}

unsigned short read_adc_channel(unsigned char channel)
{
    unsigned short adc_reg_val;

    // Clear bits 5,4,3 and load the new channel 
    ADCON0 = (ADCON0 & 0xC7) | (channel << 3); 

    // Start the conversion 
    GO_nDONE = 1;

    // Wait Until Completion
    while(GO_nDONE);

    // ADRESH contains the 8 MSBs, ADRESL contains the 2 LSBs
    adc_reg_val = (ADRESH << 2) | (ADRESL >> 6);

    return adc_reg_val;
}