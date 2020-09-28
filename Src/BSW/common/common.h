/*
* hw_types.h
*
*  Created on: 7/30/2018
*      Author: EbrahimHamouda
*/

#ifndef HW_TYPES_H_
#define HW_TYPES_H_

#define F_CPU 1000000UL
#define NULL ((void *)0)


#define INPUT  0
#define OUTPUT 1
#define HIGH   1
#define LOW    0

#define FALSE 0
#define TRUE  1
 
typedef unsigned char uint8;
typedef unsigned char boolean;
typedef unsigned int  uint16;
typedef unsigned long  uint32;
typedef char int8;
typedef char* String;

typedef enum
{
	E_NOT_OK,
	E_OK
} Std_ReturnType;

#define ACCESS_REG_8BIT(REG)         (*(volatile uint8*)REG)

#define ACCESS_REG_16BIT(REG)         (*(volatile uint16*)REG)

#define READ_REG_8BIT(REG)           (*(volatile uint8*)(REG))

#define WRITE_REG_8BIT(REG,Val)      (ACCESS_REG_8BIT(REG))=(Val);

#define SET_BIT(REG,BIT_NUM)		 (ACCESS_REG_8BIT(REG)|=1<<(BIT_NUM))

#define CLEAR_BIT(REG,BIT_NUM)       (ACCESS_REG_8BIT(REG) &=(~(1<<(BIT_NUM))))

#define BIT_IS_SET(REG,BIT_NUM)      ((ACCESS_REG_8BIT(REG) & (1 << BIT_NUM)))

#define BIT_IS_CLEAR(REG,BIT_NUM)    (!(BIT_IS_SET(REG,BIT_NUM)))

#define TOGGLE_BIT(REG,BIT_NUM)  	 (ACCESS_REG_8BIT(REG) = ACCESS_REG_8BIT(REG) ^ (1<<BIT_NUM) )

#define Min(x,y) ((x) < (y) ? (x) : (y))

#define Max(x,y) ((x) > (y) ? (x) : (y))

inline long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return  (((x - in_min) * (out_max - out_min + 1)) / ((in_max - in_min + 1) + out_min));
}

inline int bcd_decimal(uint8 hex)
{
	int dec = ((hex & 0xF0) >> 4) * 10 + (hex & 0x0F);
	return dec;
}

/*********************************************
*******************************************/
#endif /* HW_TYPES_H_ */
