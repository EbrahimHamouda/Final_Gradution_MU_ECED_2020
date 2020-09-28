/*
 * CAN.h
 *
 * Created: 6/14/2020 8:28:20 AM
 *  Author: ebrah
 */

#ifndef CAN_H_
#define CAN_H_
#include "common.h"
#include "Com_DataTypes.h"
#include "I2C.h"

#define CAN_init(X) I2C_AssignCallBackRX(X)

inline void CAN_Write(uint8 Message_Id,uint8* Buff)
{
	uint8 counter;
    I2C_Start();
    I2C_Write(0x00);
    _delay_ms(1);
    I2C_Write(Message_Id);
    _delay_ms(1);
    for (counter = 0; counter < len; counter++)
    {
        I2C_Write(buff[counter]);
        _delay_ms(1);
    }
    I2C_Stop();
    I2C_WaitForRx();
}


#endif /* CAN_H_ */