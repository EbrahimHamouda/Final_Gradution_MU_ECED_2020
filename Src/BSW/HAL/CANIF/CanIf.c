/*
 * CAN.c
 *
 * Created: 6/14/2020 8:28:32 AM
 *  Author: ebrah
 */ 

#include "CanIf.h"
#include <util/delay.h>


static Std_ReturnType Software_filter(uint8 message_Id,uint8* Pdu_Id)
{
	uint8 i;
	Std_ReturnType ret_val = E_NOT_OK;
	for (i=0;i<NUM_PDU;i++)
	{
		if (HOHs_2_PDUs_Arr[i].PduType == RX)
		{
			if ((message_Id & HOHs_2_PDUs_Arr[i].Mask) ==
				(HOHs_2_PDUs_Arr[i].Message_ID & HOHs_2_PDUs_Arr[i].Mask))
			{
				*Pdu_Id = i;
				ret_val = E_OK ;
			}
		}
	}
	return ret_val;
}

static void CanIf_RxIndication(uint8* data)
{
	uint8 local_messageId = ((CanMailBox_t*)data)->Message_Id;
	uint8* local_data = ((CanMailBox_t*)data)->Data;
	uint8 local_PduId;

	if (Software_filter(local_messageId,&local_PduId) == E_OK)
	{
		if(HOHs_2_PDUs_Arr[local_PduId].Mask ==0 )
		{
			HOHs_2_PDUs_Arr[local_PduId].User_CanRxIndiction(local_PduId,data);
		}
		else
		{
			HOHs_2_PDUs_Arr[local_PduId].User_CanRxIndiction(local_PduId,local_data);
		}
	}
}

void CanIf_init()
{
	CAN_init(CanIf_RxIndication);	
}

void CanIf_Write(uint8 Pdu_Id,uint8* buff)
{
	uint8 len = HOHs_2_PDUs_Arr[Pdu_Id].len;
	CAN_Write(HOHs_2_PDUs_Arr[Pdu_Id].Message_ID, Buff)
}

