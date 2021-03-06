/*
 * pwm.h
 *
 * Created: 3/8/2019 8:48:43 PM
 *  Author: ebrah
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "GPIO.h"


void pwm_init();

void pwm_generate(uint8 pin, int val);

void pwm_stop(uint8 pin);

uint8 PWM_Read(uint8 channel);

#endif /* PWM_H_ */