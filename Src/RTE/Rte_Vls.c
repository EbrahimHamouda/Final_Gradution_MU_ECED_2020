/**
*
* \brief Sprints AUTOSAR Master Class - SeatCtrlApp
* \author Ebrahim Hamouda
*
* For any inquiries: ebrahim.hamouda25@gmail.com
*
*/

#include "Rte_Type.h"
#include "Rte_Main.h"
#include "Rte_VLS.h"
#include "Rte_Led.h"
#include "Rte_IoHwAbs.h"
#include "Com.h"
#include "Os.h"

/* ***************************************************** */
/* 														 */
/* Sender Receiver Variables 							 */
/* 														 */
/* ***************************************************** */

volatile static Rte_SenderReceiverBuffersType Rte_SenderReceiverBuffers;
volatile static Rte_SenderReceiverFlagsType Rte_SenderReceiverFlags;

/* ***************************************************** */
/* 														 */
/* Mode Switch Variables 								 */
/* 														 */
/* ***************************************************** */

/* ***************************************************** */
/* 														 */
/* Sender Receiver APIs - IntraECU 						 */
/* 														 */
/* ***************************************************** */


/* ***************************************************** */
/* 														 */
/* Sender Receiver APIs - InterECU 						 */
/* 														 */
/* ***************************************************** */
Std_ReturnType Rte_Read_rpVLS_SetSgnl_DE_VlsSignals(DisplaySgnls_t* DisplaySgnlPtr)
{
	/*Read needed Signals from Com module buffer*/
	Com_ReceiveGroupSignal(0,(uint8*)DisplaySgnlPtr);
	return E_OK;
}

/* ***************************************************** */
/* 														 */
/* Mode Switch APIs					 					 */
/* 														 */
/* ***************************************************** */

/* ***************************************************** */
/* 														 */
/* Client Server APIs					 				 */
/* 														 */
/* ***************************************************** */

Std_ReturnType Rte_Call_rpLedSet_HeadLed_Set(boolean HeadState)
{
	RE_HeadLightLed(HeadState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLedSet_BrakeLed_set(boolean BrakeState)
{
	RE_BrakeLightLed(BrakeState);
	return RTE_E_OK;
}
Std_ReturnType Rte_Call_rpLedSet_HazardLed_Set(boolean HazardState)
{
	RE_HazardLightLed(HazardState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLedSet_RightLed_Set(boolean RightState)
{
	RE_RightLightLed(RightState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLedSet_LeftLed_Set(boolean LeftState)
{
	RE_LeftLightLed(LeftState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpWiperSet_WiperSet(boolean Wiper_poistion)
{
	RE_WiperPosition(Wiper_poistion);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpSet_Led_Opr_SetHeadLed(boolean LedState)
{
	RE_HeadLed(LedState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpSet_Led_Opr_SetBrakeLed(boolean BrakeState)
{
	RE_BrakeLed(BrakeState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpSet_Led_Opr_SetHazardLed(boolean LedState)
{
	RE_HazardLed(LedState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpSet_Led_Opr_SetRightLed(boolean LedState)
{
	RE_RightLed(LedState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpSet_Led_Opr_SetLeftLed(boolean LedState)
{
	RE_LeftLed(LedState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpSet_Led_Opr_SetWiperPosition(uint8 Wiper_poistion)
{
	RE_WiperPoistion(Wiper_poistion);
	return RTE_E_OK;
}



/* ***************************************************** */
/* 														 */
/* Com Callbacks Impl - InterECU					 	 */
/* 														 */
/* ***************************************************** */

void Rte_ComCbk_LightStateGroup(void)
{
	Os_SetEvent(OsTaskId_AppTsk, OsConf_OsEvent_AppTsk_DRE_Visiabilty_DisplaySignals);
}

/* ***************************************************** */
/* 														 */
/* Tasks Impl					 						 */
/* 														 */
/* ***************************************************** */

void CyclicTask(void)
{
	RE_MainFunction_Update();
	Os_TerminateTask();
}

void AppTsk(void)
{
	EventMaskType CurrentEvents = 0;

	/* Wait for events */
	Os_WaitEvent(OsConf_OsEvent_AppTsk_DRE_Visiabilty_DisplaySignals);

	/* Get the set events */
	Os_GetEvent(OsTaskId_AppTsk, &CurrentEvents);

	/* Clear the events */
	Os_ClearEvent(CurrentEvents);

	if ((CurrentEvents & OsConf_OsEvent_AppTsk_DRE_Visiabilty_DisplaySignals) != 0)
	{
		RE_DataRevieve_VLS_Sgnl_Update();
	}
}

/* ***************************************************** */
/* 														 */
/* RTE State Machine APIs					 			 */
/* 														 */
/* ***************************************************** */

Std_ReturnType Rte_Start()
{
	
	Os_SetRelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_500ms, 0, 500);

	return RTE_E_OK;
}

Std_ReturnType Rte_Stop()
{
	Os_CancelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_500ms);

	return RTE_E_OK;
}
