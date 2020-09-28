/*
 * ultraSonicSensor.h
 *
 * Created: 4/27/2019 10:18:09 AM
 *  Author: ebrah
 */ 


#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_
#include <util\delay.h>
#include "GPIO.h"
#include "common.h"


typedef struct
{
	enum_PinsNum_t Trigger;
	enum_PinsNum_t Echo;
} UltraSonic_t;


extern UltraSonic_t ultrasnoic1;
extern UltraSonic_t ultrasnoic2;

void UltraSonic_Init(void);
uint16 ultraSonic_Read(UltraSonic_t* ptr_USconfg);

#endif /* ULTRASONICSENSOR_H_ */