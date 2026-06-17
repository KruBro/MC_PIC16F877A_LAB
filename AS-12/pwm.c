#include <xc.h>
#include "pwm.h"

unsigned char duty_cycle = 0; // Global variable used by ISR

void initPWM()
{
    /* Configure RC2 as a standard digital output for our Software PWM */
    TRISD0 = 0; 
    RD0 = 0;    
}

void set_pwm_duty(unsigned char duty)
{
    // Update the global duty cycle (0-100)
    duty_cycle = duty;
}

void pwm_control(unsigned short adc_val)
{
    // Convert 10-bit ADC value (0-1023) to a 0-100 percentage
    unsigned char calculated_duty = (unsigned char)(adc_val / 10.23);
    set_pwm_duty(calculated_duty);
}