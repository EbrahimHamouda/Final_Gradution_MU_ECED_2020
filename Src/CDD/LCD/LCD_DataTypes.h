/*
 * Lcd_DataTypes.h
 *
 * Created: 6/12/2020 10:02:42 AM
 *  Author: ebrah
 */ 


#ifndef LCD_DATATYPES_H_
#define LCD_DATATYPES_H_

#include "common.h"
#include "LCD_Pcfg.h"

typedef struct
{
	uint8 arr_DataPins[DATA_PINS]; // put the num of the pin for data
	uint8 Enable_pin;			   // put the num of the enable bit
	uint8 Reg_Select;			   // put the num of the RS bit
	uint8 RW_Select;			   // put the num of the RS bit
} struct_PinsCnfg_t;



#endif /* LCD_DATATYPES_H_ */