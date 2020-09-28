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
#include "CanIf_Pcfg.h"
#include "Can_Wrapper.h"


extern HOH_CfgType HOHs_2_PDUs_Arr[NUM_PDU] ;

void CanIf_Write(uint8 Pdu_Id,uint8* buff);

void CanIf_WriteByte(uint8 Pdu_Id,uint8 byte);

void CanIf_init();


#endif /* CAN_H_ */