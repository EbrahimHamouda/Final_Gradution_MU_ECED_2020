/*
* File:   lcd.c
* Author: ebrahim hamouda
*
* Created on March 15, 2018, 11:23 PM
*/

#include "lcd.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>


#define EN        ptr->Enable_pin
#define RS        ptr->Reg_Select

static void kick(const struct_PinsCnfg_t* ptr)
{
	/*
	* assign data in the pins of the confg
	* make pulse to make lcd work
	*/
	
	Dio_WriteChannel(EN,SET_VALUE_LOW);
	Dio_WriteChannel(EN,SET_VALUE_HIGH);
}

void lcd_init(const struct_PinsCnfg_t* ptr)
{
	/*
	* set direction output for data and control pins
	* config the lcd to start working
	*/
	uint8 i;
	for(i=0;i<DATA_PINS;i++)
	{
		SetPinDirection(ptr->arr_DataPins[i],SET_PIN_OUT);
	}
	SetPinDirection(RS,SET_PIN_OUT);
	SetPinDirection(EN,SET_PIN_OUT);
	
	#ifdef _4BIT_MODE
	lcd_cmd(ptr,0x02);						//config lcd mode send commands to
	lcd_cmd(ptr,BIT_4);
	#endif
	
	#ifdef _8BIT_MODE
	lcd_cmd(ptr,BIT_8);
	#endif
	
	lcd_cmd(ptr,ENTRY_MODE);                          // init lcd to use
	lcd_goto(ptr,0, 0);
	lcd_cmd(ptr,CURSOR_OFF);
	lcd_clear(ptr);
	/*initialize Custom Symbols*/
	Lcd_initCustomSymol_Callout();
}
volatile uint8 var ;
static void Send__Data(const struct_PinsCnfg_t* ptr,uint8 cmd,uint8 temp)
{
	#ifdef _8BIT_MODE
	Dio_WriteChannelGroup(ptr->arr_DataPins,DATA_PINS,cmd);
	kick(ptr);
	#endif

	#ifdef _4BIT_MODE
	Dio_WriteChannelGroup(ptr->arr_DataPins,DATA_PINS,cmd>>4);
	kick(ptr);
	Dio_WriteChannelGroup(ptr->arr_DataPins,DATA_PINS,cmd);
	kick(ptr);
	#endif
	_delay_ms(2);
}

void lcd_cmd(const struct_PinsCnfg_t* ptr,uint8 cmd)
{
	/*
	* select the register "command || data " in this case command
	* sent the command
	*/
	Dio_WriteChannel(RS,SET_VALUE_LOW);    // register select command
	Send__Data(ptr,cmd,0);
}

void lcd_chr(const struct_PinsCnfg_t* ptr,uint8 chr)
{
	/*
	* select the register "command || data " in this case data
	* sent the data
	*/
	Dio_WriteChannel(RS,SET_VALUE_HIGH);              // register select data
	Send__Data(ptr,chr,1);
}

void lcd_clear(const struct_PinsCnfg_t* ptr)
{
	lcd_cmd(ptr,CLEAR_SCREEN); // do the same as a command
}

void lcd_goto(const struct_PinsCnfg_t* ptr,uint8 row, uint8 col)
{
	if (row == 0)
	{
		lcd_cmd(ptr,(unsigned) 0x80 | col);
	}
	else if (row == 1)
	{
		lcd_cmd(ptr,(unsigned) 0xc0 | col);
	}
	#ifdef _LCD_16_4_
	else if (row==2)
	{
		lcd_cmd(ptr,(unsigned) 0x94  + col);
	}
	else if (row==3)
	{
		lcd_cmd(ptr,(unsigned) 0xD4 + col);
	}
	#endif // _LCD_16_4_
	else
	{
		// should never be here
	}
}

void lcd_str(const struct_PinsCnfg_t* ptr_lcd,uint8 row, uint8 col,uint8* ptr_chr)
{
	lcd_goto(ptr_lcd,row,col);
	while (*ptr_chr != '\0')
	{
		if (*ptr_chr == '*') // so i can't put * inside string to be shown in lcd
		{
			lcd_goto(ptr_lcd,++row,0);
			ptr_chr++;
			continue; // SKIP printing '*'
		}
		lcd_chr(ptr_lcd,*ptr_chr);
		ptr_chr++;
	}
}

volatile uint8 Num_buffer[9];
void lcd_num(const struct_PinsCnfg_t* ptr_lcd,uint8 row, uint8 col,uint32* num)
{	
	itoa((*num),Num_buffer,10);
	lcd_str(ptr_lcd,row,col,Num_buffer);
}

void LCD_Custom_Char (const struct_PinsCnfg_t* ptr_lcd,unsigned char loc, unsigned char *msg)
{
	
	unsigned char j;
	if(loc<8)
	{
		lcd_cmd(ptr_lcd,(0x40 + (loc*8)));  /* Command 0x40 and onwards forces the device to point CGRAM address */
		for(j=0;j<8;j++)	/* Write 8 byte for generation of 1 character */
		lcd_chr(ptr_lcd,msg[j]);
	}
}

