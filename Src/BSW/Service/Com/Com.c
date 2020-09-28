/*
* Com.c
*
* Created: 6/22/2020 1:28:09 AM
*  Author: ebrah
*/

#include "Com.h"
#include "Com_Pcfg.h"
#include <math.h>
#include "CANIF.h"

extern ComGroupSignal_t ComGroupSignals[1];
extern ComIPdu_t ComIPdus[NUM_COM_IPDUs];

#ifdef SIGNAL_STAND_ALONE_SUPPORT
void Com_SendSignal(uint8 SignalId, uint8 *Data)
{
	/**/
	uint8 Pdu_Id = temp_SignalCfg[SignalId].ComIPduHandleId;
	uint8 *Pdu_buffer = temp_SignalCfg[SignalId].ComPduBuffer;
	uint8 temp_ComBytePoistion = temp_SignalCfg[SignalId].ComBytePoistion;

	/*TODO Loop to cpy the whole size*/
	Pdu_buffer[temp_ComBytePoistion] = *Data;

	CanIf_Write(Pdu_Id, Pdu_buffer);
}
#endif // SIGNAL_STAND_ALONE_SUPPORT

void Com_SendGroupSignal(uint8 GroupSignalId, uint8 *Data)
{
	uint8 temp_ComBytePoistion;
	uint8 temp_ComByteSize;

	uint8 PduId = ComGroupSignals[GroupSignalId].ComIpduHandleId;
	ComSignalGroup_t *temp_ComSignalGroup = ComGroupSignals[GroupSignalId].ComSignalGroupRef;
	uint8 Temp_ComSignalGroupNum = ComGroupSignals[GroupSignalId].ComSignalGroupNum;
	uint8 *temp_ComPduBuffer = ComIPdus[PduId].Shadaw_Buff;
	uint8 i, j;
	boolean Signal_IsUpdate = FALSE;
	for (i = 0; i < Temp_ComSignalGroupNum; i++)
	{
		temp_ComBytePoistion = temp_ComSignalGroup[i].ComBytePoistion;
		temp_ComByteSize = temp_ComSignalGroup[i].ComByteSize;
		for (j = 0; j < temp_ComByteSize; j++)
		{
			if (temp_ComPduBuffer[temp_ComBytePoistion+j] != Data[temp_ComBytePoistion+j])
			{
				temp_ComPduBuffer[temp_ComBytePoistion+j] = Data[temp_ComBytePoistion+j];
				Signal_IsUpdate = TRUE ;
			}
		}
	}
	// Transmit on change
	if (Signal_IsUpdate == TRUE )
	{
		CanIf_Write(PduId, temp_ComPduBuffer);
	}
}

void Com_RxIndication(uint8 PduId, uint8 *Dataptr)
{
	uint8 temp_ComBytePoistion;
	uint8 temp_ComByteSize;

	ComGroupSignal_t *temp_ComGroupSignal = ComIPdus[PduId].Ref_GroupSignals;
	ComSignalGroup_t *temp_ComSignalGroup = temp_ComGroupSignal->ComSignalGroupRef;
	Com_UserComRxIndiction_t Rte_user = temp_ComGroupSignal->Com_UserRxIndiction;

	uint8 Temp_ComSignalGroupNum = temp_ComGroupSignal->ComSignalGroupNum;
	uint8 *temp_ComPduBuffer = ComIPdus[PduId].Shadaw_Buff;
	uint8 i, j;
	for (i = 0; i < Temp_ComSignalGroupNum; i++)
	{
		temp_ComBytePoistion = temp_ComSignalGroup[i].ComBytePoistion;
		temp_ComByteSize = temp_ComSignalGroup[i].ComByteSize;
		for (j = 0; j < temp_ComByteSize; j++)
		{
			temp_ComPduBuffer[temp_ComBytePoistion+j] = Dataptr[temp_ComBytePoistion+j];
		}
	}
	// Call Signal Rte_User
	Rte_user();
}

#ifdef SIGNAL_STAND_ALONE_SUPPORT
void Com_ReceiveSignal(uint8 Signa_Id, void *_buffer)
{
	uint8 *Pdu_buffer = temp_SignalCfg[Signa_Id].ComPduBuffer;
	uint8 temp_ComBytePoistion = temp_SignalCfg[Signa_Id].ComBytePoistion;

	/*TODO Loop to cpy the whole size*/
	*((uint8 *)_buffer) = Pdu_buffer[temp_ComBytePoistion];
}
#endif // SIGNAL_STAND_ALONE_SUPPORT

void Com_ReceiveGroupSignal(uint8 GroupSignalId, uint8 *Data)
{
	uint8 temp_ComBytePoistion;
	uint8 temp_ComByteSize;
	
	uint8 PduId = ComGroupSignals[GroupSignalId].ComIpduHandleId;
	ComSignalGroup_t *temp_ComSignalGroup = ComGroupSignals[GroupSignalId].ComSignalGroupRef;
	uint8 Temp_ComSignalGroupNum = ComGroupSignals[GroupSignalId].ComSignalGroupNum;
	uint8 *temp_ComPduBuffer = ComIPdus[PduId].Shadaw_Buff;
	uint8 i, j;

	for (i = 0; i < Temp_ComSignalGroupNum; i++)
	{
		temp_ComBytePoistion = temp_ComSignalGroup[i].ComBytePoistion;
		temp_ComByteSize = temp_ComSignalGroup[i].ComByteSize;
		for (j = 0; j < temp_ComByteSize; j++)
		{
			Data[temp_ComBytePoistion+j] = temp_ComPduBuffer[temp_ComBytePoistion+j];
		}
	}
}