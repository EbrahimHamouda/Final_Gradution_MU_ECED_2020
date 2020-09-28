/*
* I2C.h
*
* Created: 3/12/2014 12:05:49 PM
*  Author: Ebrahin hamouda
*/


#ifndef I2C_H_
#define I2C_H_

#include "common.h"
#include<avr/io.h>

typedef void(*Call_backTX_t)(void);
typedef	void(*Call_backRecive_t)(unsigned char*);


/* STATUS VALUES */
typedef enum
{
	SALVE_RX_ADD_ACK  = 0x70,
	SALVE_RX_DATA_ACK = 0x90,
	STOP_RX =0xA0
} I2c_DisplayStatus_t;

void I2C_Init();
void I2C_setOwnSlaveAddress(unsigned char add);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char data);
void I2C_TxWithInterrupt(unsigned char data);
unsigned char I2C_ReadWithACK(void); //read with send Ack
unsigned char I2C_ReadWithACKAndInterrupt(void);//read with send Ack && interrupt enable
void I2C_AssignCallBackRX(Call_backRecive_t pass_callBack);
unsigned char I2C_ReadWithNACK(void); //read without send Ack
unsigned char I2C_GetStatus(void);
void I2C_AssignCallBackTx(Call_backTX_t pass_callBackFuncation);
void i2c_disable_interrupt();
void I2C_WaitForRx();
#endif /* I2C_H_ */