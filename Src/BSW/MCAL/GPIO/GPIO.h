/*
 * GPIO.h
 *
 *  Created on: 7/30/2018
 *      Author: Ebrahim hamouda
 */

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include "common.h"
#include "GPIO_Pcfg.h"


typedef enum
{
	INT_LOW_LEVEL,
	INT_ANY_LOGIC_CHANGE,
	INT_FALLING_EDGE,
	INT_RISING_EDGE
} ExtInterrupt_type;

typedef enum
{
	EXT_INT0=6,
	EXT_INT1=7,
	EXT_INT2=5,
} ExtInterruptID_type;

typedef enum
{			// to set values of logic level
	SET_VALUE_LOW,
	SET_VALUE_HIGH,
} enum_PinValue_t;

typedef enum{      // to set dirication 
	SET_PIN_IN,
	SET_PIN_OUT,
}  enum_PinDirection_t;

typedef enum{   // to set the base address it confg from hw-gpio
	//can be added more if there's
	A = BASE_A,
	B = BASE_B,
	C = BASE_C,
	D = BASE_D,
} enum_PortName_t;

void gpio_uart_cng();

// to set single pin dirction
void SetPinDirection(enum_PinsNum_t Pin,enum_PinDirection_t Direction);

//to set whole port dirction 
void SetPortDirection(enum_PortName_t port,uint8 Val);

//to write to single pin value
void Dio_WriteChannel(enum_PinsNum_t Pin,enum_PinValue_t Val);

//to read from single pin value
enum_PinValue_t  Dio_ReadChannel(enum_PinsNum_t Pin);

//to write to whole port values
void Dio_WritePort(uint8 port,enum_PinValue_t Val);

//to read the whole port values
uint8 Dio_ReadPort(uint8 port);

//to write to multi-different pin in different ports
void Dio_WriteChannelGroup(uint8* arr,uint8 N,enum_PinValue_t type);

//to read to multi-different pin in different ports
void Dio_ReadChannelGroup(uint8* arr_Input,uint8 arr_Output,uint8 Num);

//confg spi to be master
void gpio_spi_cng_master();

//confg spi to be slave 
void gpio_spi_cng_slave();

void DioExtInterrupt_init(ExtInterruptID_type X,ExtInterrupt_type int_type,void (*NotifyWhenISR)());

void DioExtInterrupt_Enable(uint8 X);

void DioExtInterrupt_Disable(uint8 X);

#endif /* HAL_GPIO_H_ */