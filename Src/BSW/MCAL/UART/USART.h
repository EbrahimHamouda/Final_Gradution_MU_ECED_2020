/*
* USART.h
*
*  Created on: Aug 1, 2018
*      Author: Ebrahim hamouda
*/

#ifndef HAL_UART_USART_H_
#define HAL_UART_USART_H_

#include "common.h"
#include "HW_UART.h"


void  Uart_init();  //BAUD RANGE 2400

uint8 Uart_ReadByte();

void  Uart_SendByte(uint8 Chr);

void Uart_SendFrame(uint8* str,uint8 dlc);

void  Uart_TxInterruptEnable(void (*ptr)());

void  Uart_RxInterruptEnable(void (*ptr)(uint8));

void Uart_TxinterruptDisable();

#endif /* HAL_UART_USART_H_ */
