/*
* USART.c
*
*  Created on: Aug 5, 2018
*      Author: ebrahim
*/

#include "USART.h"
#include <avr/interrupt.h>

static void (*ptr_CallBackfnUartTx)();
static void (*ptr_CallBackfnUartRx)(uint8);



ISR(USART_UDRE_vect)
{
	ptr_CallBackfnUartTx();
}

ISR(USART_RXC_vect)
{
	ptr_CallBackfnUartRx(ACCESS_REG_8BIT((UARTDATAREG +UART_BASE)));
}

void Uart_init()  
{
	ACCESS_REG_8BIT((UARTBITREGLOW+UART_BASE)) = 25;								     // baud rate setting 
	ACCESS_REG_8BIT((UARTCONTROLB+UART_BASE)) |= (1 << RXEN) | (1 << TXEN);			 // wake up uart for recieve and transmit 
	ACCESS_REG_8BIT((UARTCONTROLC+UART_BASE)) |= (1<<URSEL) |  (3 << UCSZ0);		 //1stop , no parity , 8bit data  >> fram format 
}

void Uart_SendByte(uint8 Chr)
{
	while (!(ACCESS_REG_8BIT((UARTCONTROLA+UART_BASE)) & (1 << UDRE)));		// checking if there's still data in Buffer
	UDR = Chr;
}

static void Hex2Ascii(uint8 Hex,uint8* asiiOut)
{
	if (( (Hex>>4) & 0x0F) >= 10)
	{
		asiiOut[0] = (Hex >> 4)+55;
	}
	else
	{
		asiiOut[0] = (Hex >> 4) + 48;
	}

	if (( Hex & 0x0F) >= 10)
	{
		asiiOut[1] = ( Hex & 0x0F)+55;
	}
	else
	{
		asiiOut[1] = ( Hex & 0x0F) + 48;
	}
	asiiOut[2] = ' ';
}


void Uart_SendFrame(uint8* str,uint8 dlc)
{
	uint8 i=0,temp_buff[2];
	for (i=0;i<dlc;i++)
	{
		Hex2Ascii(str[i],temp_buff);
		Uart_SendByte(temp_buff[0]);
		Uart_SendByte(temp_buff[1]);
		Uart_SendByte(temp_buff[2]);
	}
	Uart_SendByte('\n');
	Uart_SendByte('\r');			
}
uint8 Uart_ReadByte()
{
	while (!(ACCESS_REG_8BIT((UARTCONTROLA+UART_BASE)) & (1 << RXC)));       // checking is that recieve completed
	return UDR;
}

void Uart_TxInterruptEnable(void (*ptr)())
{
	ptr_CallBackfnUartTx=ptr;           // assign ptr to call back fun
	ACCESS_REG_8BIT((UARTCONTROLB+UART_BASE)) |= 1<<UDRIE;                  // enable interrupt when buffer is empty
}

void  Uart_RxInterruptEnable(void (*ptr)(uint8))
{
	ptr_CallBackfnUartRx = ptr;         // assign ptr to call back fun
	ACCESS_REG_8BIT((UARTCONTROLB+UART_BASE)) |= 1<<RXCIE;                  // enable interrupt when data recieved 
}

void Uart_TxinterruptDisable()
{
	(ACCESS_REG_8BIT((UARTCONTROLB+UART_BASE))) &= ~(1<<UDRIE); 
}
