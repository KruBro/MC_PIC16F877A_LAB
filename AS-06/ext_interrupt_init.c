#include "main.h"

void init_ext_interrtup()
{
    GIE = 1;        //Global Interrupt Enabled
    PEIE = 1;        //Peripheral Interrupt Enabled
    INTE = 1;       //External Interrupt Enabled

    INTF = 0;       //Interrupt Flag Disabled
    INTEDG = 0;     //Falling Interrupt Edge
    TRISB0 = 1;     //Make RB0 as INPUT
}