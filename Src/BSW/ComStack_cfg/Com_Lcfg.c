/*
 * Com_Lcfg.c
 *
 * Created: 6/22/2020 6:35:24 AM
 *  Author: ebrah
 */
#include "Com_DataTypes.h"
#include "Com_Pcfg.h"
#include "CanIf_Pcfg.h"
#include "Rte_Cbk.h"

// internal shadow buffer 
static uint8 IpdusShadowBuffer[NUM_COM_IPDUs][COM_PDU_MAX_BUFFER_SIZE];

ComSignalGroup_t ComSignalGroup0[Num_SIGNAL_GROUP_PDU0] =
{
	{
		ComConf_ComSignal_HEAD_LIGHT,
		0,
		1
	},
	{
		ComConf_ComSignal_HAZARD_LIGHT,
		1,
		1,
	},
	{
		ComConf_ComSignal_RIGHT_LIGHT,
		2,
		1,
	},
	{
		ComConf_ComSignal_LEFT_LIGHT,
		3,
		1,
	},
	{
		ComConf_ComSignal_WIPER,
		4,
		1,
	},
	{
		COMCONF_COMSIGNAL_BRAKE_LIGHT,
		5,
		1,
	}
};

ComSignalGroup_t ComSignalGroup1[Num_SIGNAL_GROUP_PDU1] =
{
	{
		ComConf_ComSignal_ENGINE_BRAKE,
		0,
		1
	},
	{
		ComConf_ComSignal_STEERING_ANGLE,
		1,
		1,
	},
	{
		ComConf_ComSignal_ENGINE_GAS,
		2,
		1,
	}
};

ComSignalGroup_t ComSignalGroup2[Num_SIGNAL_GROUP_PDU2] =
{
	{
		ComConf_ComSignal_BATTERT_LVL,
		0,
		1
	},
	{
		ComConf_ComSignal_ULTRA_SONIC,
		1,
		2,
	},
	{
		ComConf_ComSignal_TEMPERTURE,
		3,
		1,
	},
	{
		ComConf_ComSignal_HUMIDITIY,
		4,
		1,
	},
};

ComGroupSignal_t ComGroupSignals[Num_GROUP_SIGNAL] =
{
	{
		0,
		LIGHT_STATE_IPDU_ID,
		ComSignalGroup0,
		Num_SIGNAL_GROUP_PDU0,
		NULL
	},
	{
		1,
		POWER_TRAIN_STATE_IPDU_ID,
		ComSignalGroup1,
		Num_SIGNAL_GROUP_PDU1,
		NULL
	},
	{
		2,
		SENSOR_DATA_STATE_IPDU_ID,
		ComSignalGroup2,
		Num_SIGNAL_GROUP_PDU2,
		Rte_ComCbk_Sensor_StateGroup
	}
};

ComIPdu_t ComIPdus[NUM_COM_IPDUs] =
{
	{	
		LIGHT_STATE_IPDU_ID,
		ComGroupSignals,
		&IpdusShadowBuffer[LIGHT_STATE_IPDU_ID]
	},
	{
		POWER_TRAIN_STATE_IPDU_ID,
		&ComGroupSignals[1],
		&IpdusShadowBuffer[POWER_TRAIN_STATE_IPDU_ID]
	},
	{
		SENSOR_DATA_STATE_IPDU_ID,
		&ComGroupSignals[2],
		&IpdusShadowBuffer[SENSOR_DATA_STATE_IPDU_ID]
	}
};
