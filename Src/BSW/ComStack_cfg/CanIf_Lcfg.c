/*
 * CAN_Lcfg.c
 *
 * Created: 6/15/2020 12:01:23 PM
 *  Author: ebrah
 */ 
#include "CanIf_Pcfg.h"
#include "Com_DataTypes.h"
#include "Com.h"

HOH_CfgType HOHs_2_PDUs_Arr[NUM_PDU] =
{
		{
			LIGHT_STATE_IPDU_ID,
			6,
			TX,
			0xF0,
			0xFF,
			NULL
		},
		{
			POWER_TRAIN_STATE_IPDU_ID,
			3,
			TX,
			0xA0,
			0xFF,
			NULL
		},
		{
			SENSOR_DATA_STATE_IPDU_ID,
			5,
			RX,
			0xE0,
			0xFF,
			Com_RxIndication
		}
};