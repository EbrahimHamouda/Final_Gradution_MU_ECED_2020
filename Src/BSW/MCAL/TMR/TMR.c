/*
 * timer.c
 *
 * Created: 3/13/2020 10:54:58 AM
 *  Author: ebrah
 */ 
#include "TMR.h"
#include <avr//io.h>
#include <avr/interrupt.h>
// #include "TMU.h"
ISR(TIMER0_OVF_vect)
{
	TCNT0=131;
}
void Timer0_init(void)
{
	
	TIMSK |= 1<<0;	//enable interrupt for timer
	TCCR0 |= 1<<1;	// TCCR0 for edjust the resolution
	TCNT0 =131;
}

void Timer0_Start(void)
{
	TIMSK |= (1<<0);	//Enable interrupt for timer
}

void Timer0_Stop(void)
{
	TIMSK &= ~(1<<0);	//disable interrupt for timer
}

void Timer2_init(void)
{
	
}

uint8 Timer2_getVal()
{
	
}
