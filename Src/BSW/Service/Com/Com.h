/*
 * Com.h
 *
 * Created: 6/22/2020 1:28:22 AM
 *  Author: ebrah
 */

#include "common.h"
#include "Com_DataTypes.h"
#include "Com_Pcfg.h"

void Com_SendSignal(uint8 SignalId,uint8* Data);

void Com_RxIndication(uint8 PduId,uint8* Dataptr);

void Com_ReceiveSignal(uint8 Signa_Id, void* _buffer);

void Com_SendGroupSignal(uint8 GroupSignalId, uint8 *Data);

void Com_ReceiveGroupSignal(uint8 GroupSignalId, uint8 *Data);