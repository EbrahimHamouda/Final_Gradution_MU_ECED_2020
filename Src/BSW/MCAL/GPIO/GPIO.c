/*
* GPIO.c
*
* Created:
*   Author: EbrahimHamouda
*/

#include <avr/interrupt.h>
#include "GPIO.h"


static void (*Call_backFromExtISR[3]) (void); // arry of pointers to funcation

void Dio_WriteChannelGroup(uint8* arr,uint8 N,uint8 val)
{
	uint8 i;
	for (i=0;i<N;i++)
	{
		if (val & (1<<i))
		{
			Dio_WriteChannel(arr[i],SET_VALUE_HIGH);
		}
		else
		{
			Dio_WriteChannel(arr[i],SET_VALUE_LOW);
		}
	}
}

void gpio_spi_cng_master()
{
	SetPinDirection(B4,SET_PIN_OUT);     //SS
	SetPinDirection(B5,SET_PIN_OUT);     //MOSi
	SetPinDirection(B6,SET_PIN_IN);		 //MISO
	SetPinDirection(B7,SET_PIN_OUT);	 //SCK
}

void SetPinDirection(enum_PinsNum_t Pin,enum_PinDirection_t Direction)
{
	//TODO change to modules & divide
	if(Pin<8)                  //PORTA
	{
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_A+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_A+GPIODIR),(Pin));
		}
	}
	else if((Pin<16)&&(Pin>=8)) //PORTB
	{
		Pin-=8;
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_B+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_B+GPIODIR),(Pin));
		}
	}
	else if ((Pin<24)&&(Pin>=16)) //PORTC
	{
		Pin-=16;
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_C+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_C+GPIODIR),(Pin));
		}
	}
	else if ((Pin<32)&&(Pin>=24)) //PORTD
	{
		Pin-=24;
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_D+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_D+GPIODIR),(Pin));
		}
	}
	else
	{
		//error
	}
}

void SetPortDirection(uint8 port,enum_PinValue_t Val)
{
	WRITE_REG_8BIT((port+GPIODIR),Val);
}

void Dio_WriteChannel(enum_PinsNum_t Pin,enum_PinValue_t Val)
{
	if(Pin<8)                  //PORTA
	{
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_A+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_A+GPIOOUTDATA),(Pin));
		}
	}
	else if((Pin<16)&&(Pin>=8)) //PORTB
	{
		Pin-=8;
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_B+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_B+GPIOOUTDATA),(Pin));
		}
	}
	else if ((Pin<24)&&(Pin>=16)) //PORTC
	{
		Pin-=16;
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_C+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_C+GPIOOUTDATA),(Pin));
		}
	}
	else if ((Pin<32)&&(Pin>=24)) //PORTD
	{
		Pin-=24;
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_D+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_D+GPIOOUTDATA),(Pin));
		}
	}
	else
	{
		//error
	}
}

enum_PinValue_t  Dio_ReadChannel(enum_PinsNum_t Pin)
{
	enum_PinValue_t ret_val=SET_VALUE_LOW;
	if(Pin<8)                     //PORTA
	{
		if (BIT_IS_SET(BASE_A+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else if((Pin<16)&&(Pin>=8)) //PORTB
	{
		Pin-=8;
		if (BIT_IS_SET(BASE_B+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else if ((Pin<24)&&(Pin>=16)) //PORTC
	{
		Pin-=16;
		if (BIT_IS_SET(BASE_C+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else if ((Pin<32)&&(Pin>=24)) //PORTD
	{
		Pin-=24;
		if (BIT_IS_SET(BASE_D+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else
	{
		//error
	}
	return ret_val;
}

void Dio_WritePort(uint8 port,enum_PinValue_t Val)
{
	WRITE_REG_8BIT((port+GPIOOUTDATA),Val);
}

enum_PinValue_t Dio_ReadPort(uint8 port)
{
	return READ_REG_8BIT((port+GPIOINDATA));
}

void gpio_spi_cng_slave()
{
	SetPinDirection(B4,SET_PIN_IN);	 //SS
	SetPinDirection(B5,SET_PIN_IN);	 //MOSI
	SetPinDirection(B6,SET_PIN_OUT);    //MISO
	SetPinDirection(B7,SET_PIN_IN);     //SCK
}

void gpio_uart_cng()
{
	SetPinDirection(D0,SET_PIN_IN); // uart RX
	SetPinDirection(D1,SET_PIN_OUT); // uart TX
}

volatile uint8 Flag_ExtInt= 0;
ISR(INT0_vect)//interrupt service routine when there is a change in logic level
{
	if (Call_backFromExtISR[0] != NULL)
	{
		Call_backFromExtISR[0]();
	}
	Flag_ExtInt = !Flag_ExtInt ;
}

ISR(INT1_vect)//interrupt service routine when there is a change in logic level
{
	Call_backFromExtISR[1]();
}

ISR(INT2_vect)//interrupt service routine when there is a change in logic level
{
	Call_backFromExtISR[2]();
}

void DioExtInterrupt_init(ExtInterruptID_type X,ExtInterrupt_type int_type,void (*NotifyWhenISR)())
{
	switch (X)
	{
		case EXT_INT0 :
		{
			DDRD  &= ~(1<<2);
			MCUCR &= 0b11111100 ;
			MCUCR |= int_type << 0;
			Call_backFromExtISR[0]=NotifyWhenISR;
			GICR |=(1 << 6);
			break;
		}
		case EXT_INT1 :
		{
			DDRD  &= ~(1<<3);
			MCUCR &= 0b11110011;
			MCUCR |= int_type<<2;
			Call_backFromExtISR[1]=NotifyWhenISR;
			break;
		}
		case EXT_INT2 :
		{
			DDRB &= ~(1<<2);
			if(int_type==INT_FALLING_EDGE)
			{
				MCUCSR &= ~(1<<6);
			}
			else if(int_type==INT_RISING_EDGE)
			{
				MCUCSR |= (1<<6);
			}
			else
			{
				//error
			}
			Call_backFromExtISR[2]=NotifyWhenISR;
			break;
		}
	}
}

void DioExtInterrupt_Enable(uint8 X)
{
	GICR |=(1 << X);
}

void DioExtInterrupt_Disable(uint8 X)
{
	GICR &=(~(1 << X));
}