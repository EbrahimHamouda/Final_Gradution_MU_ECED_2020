/*
 * EcuM.c
 *
 * Created: 8/28/2020 6:42:43 AM
 *  Author: ebrah
 */ 


#include "ADC.h"
#include "GPIO.h"
#include "I2C.h"
#include "CanIf.h"
#include "EcuM_Pcfg.h"
#include "pwm.h"

#ifdef DASHBOARD
#include "LCD.h"
#include "RTCDS1307.h"
#endif // _DASHBOARD

#ifdef ADAS_ECU
#include "ultraSonicSensor.h"
#endif

void EcuM_init()
{
	I2C_Init();
	CanIf_init();
#ifdef DASHBOARD
	SetPortDirection(B, 0x00);
	adc_init(AREF, FREE_RUNNING_MODE, CLK_ADC_DIV_128);
	lcd_init(&lcd1);	
	RTC_Init();
#endif // _DASHBOARD

#ifdef VLS_ECU
	SetPortDirection(B, 0xFF);
	pwm_init();
#endif // VLS_ECU

#ifdef PTS_ECU
	pwm_init();
	SetPinDirection(C2,OUTPUT);
	SetPinDirection(C3,OUTPUT);
#endif // PTS_ECU

#ifdef ADAS_ECU
	adc_init(AREF, FREE_RUNNING_MODE, CLK_ADC_DIV_128);
	UltraSonic_Init();
#endif // ADAS_ECU
}
