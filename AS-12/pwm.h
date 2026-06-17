#ifndef PWM_H
#define PWM_H

extern unsigned char duty_cycle;

void initPWM();
void set_pwm_duty(unsigned char duty);
void pwm_control(unsigned short adc_val);

#endif