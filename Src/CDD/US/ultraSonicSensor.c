/*
* ultraSonicSensor.c
*
* Created: 4/27/2019 10:17:34 AM
*  Author: ebrah
*/

#include <avr/interrupt.h>
#include "ultraSonicSensor.h"
#include "common.h"
// use timer 1 to capture the duration .

static volatile uint16 pulse = 0;//interger  to access all though the program
static volatile uint8 i = 0;// integer  to access all though the program
static volatile uint8 flag=0;

UltraSonic_t ultrasnoic1={D4,D2};
UltraSonic_t ultrasnoic2={D5,D3};
	

static void Static_UltraSonic_Init(UltraSonic_t* ptr_USconfg)
{
	SetPinDirection((ptr_USconfg->Trigger),OUTPUT);
	SetPinDirection((ptr_USconfg->Echo),INPUT);
}

void UltraSonic_Init(void)
{
	Static_UltraSonic_Init(&ultrasnoic1);
	Static_UltraSonic_Init(&ultrasnoic2);
	
}

uint16 ultraSonic_Read(UltraSonic_t* ptr_USconfg)
{
	TCCR1B|=(1<<CS10);//enabling counter
	Dio_WriteChannel((ptr_USconfg->Trigger),SET_VALUE_LOW);
	_delay_us(2);///triggering the sensor for 15usec
	Dio_WriteChannel((ptr_USconfg->Trigger),SET_VALUE_HIGH);
	_delay_us(15);
	Dio_WriteChannel((ptr_USconfg->Trigger),SET_VALUE_LOW);
	_delay_us(310);
	TCNT1 = 0;
	while(Dio_ReadChannel(ptr_USconfg->Echo) == SET_VALUE_HIGH)
	pulse = TCNT1;
	TCCR1B=0;
	return (pulse/58);  //getting the distance based on formula on introduction
}