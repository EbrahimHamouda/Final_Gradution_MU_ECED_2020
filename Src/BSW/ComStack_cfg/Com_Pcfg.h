/*
 * Com_Pcfg.h
 *
 * Created: 6/22/2020 6:35:43 AM
 *  Author: ebrah
 */ 


#ifndef COM_PCFG_H_
#define COM_PCFG_H_

#define  NUM_COM_IPDUs				3
#define  COM_PDU_MAX_BUFFER_SIZE	8

#define  Num_GROUP_SIGNAL			3

#define  Num_SIGNAL_GROUP_PDU0		6
#define  Num_SIGNAL_GROUP_PDU1		3
#define  Num_SIGNAL_GROUP_PDU2		4



typedef enum
{
	ComConf_ComSignal_HEAD_LIGHT,
	COMCONF_COMSIGNAL_BRAKE_LIGHT,
	ComConf_ComSignal_HAZARD_LIGHT,
	ComConf_ComSignal_RIGHT_LIGHT,
	ComConf_ComSignal_LEFT_LIGHT,
	ComConf_ComSignal_WIPER,
	ComConf_ComSignal_ENGINE_BRAKE,
	ComConf_ComSignal_STEERING_ANGLE,
	ComConf_ComSignal_ENGINE_GAS,
	ComConf_ComSignal_BATTERT_LVL,
	ComConf_ComSignal_ULTRA_SONIC,
	ComConf_ComSignal_TEMPERTURE,
	ComConf_ComSignal_HUMIDITIY
} ComSignals_e;

#endif /* COM_PCFG_H_ */