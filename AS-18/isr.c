#include "uart.h"
#include <xc.h>

void __interrupt() isr(void)
{
    if(RCIF == 1)
    {
        if(OERR == 1)
            CREN = 0;

        ch = RCREG;

        RCIF = 0;
    }
}