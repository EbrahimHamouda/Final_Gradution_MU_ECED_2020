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
#include "Rte_HMI.h"
#include "Rte_LCD_CDD.h"
#include "Rte_Display.h"
#include "Rte_IoHwAbs.h"
#include "Com.h"
#include "Os.h"
#include "lcd.h"
/* ***************************************************** */
/* 														 */
/* Sender Receiver Variables 							 */
/* 														 */
/* ***************************************************** */

volatile static Rte_SenderReceiverBuffersType Rte_SenderReceiverBuffers;
volatile static Rte_SenderReceiverFlagsType Rte_SenderReceiverFlags;
static uint8 static_counter = 0;

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

Std_ReturnType Rte_Write_ppDisplaySignals_DE_DisplayCtrls(DisplaySgnls_t *DisplaySgnlPtr)
{
	// check data if changed or not
	if (memcmp(&(Rte_SenderReceiverBuffers.Display_Sgnls), DisplaySgnlPtr, sizeof(DisplaySgnls_t)) != 0)
	{
		Rte_SenderReceiverBuffers.Display_Sgnls = *DisplaySgnlPtr;
		Os_SetEvent(OsTaskId_AppTsk, OsConf_OsEvent_AppTsk_DRE_Display_DisplaySignals);
	}

	return RTE_E_OK;
}

Std_ReturnType Rte_Read_rpDiplaySet_DE_DisplayCtrls(DisplaySgnls_t *DisplaySgnlPtr)
{
	*DisplaySgnlPtr = Rte_SenderReceiverBuffers.Display_Sgnls;
	return RTE_E_OK;
}



/* ***************************************************** */
/* 														 */
/* Sender Receiver APIs - InterECU 						 */
/* 														 */
/* ***************************************************** */
Std_ReturnType Rte_Write_ppVLS_SetSgnl_DE_VLS(DisplaySgnls_t* DisplaySgnlPtr)
{
	Com_SendGroupSignal(0,(uint8*)DisplaySgnlPtr);
	return RTE_E_OK;
}

Std_ReturnType Rte_Write_ppPTS_SetSgnl_DE_PTS(PowerTrainSgnls_t* PowerTrainSgnlsRef)
{
	Com_SendGroupSignal(1,(uint8*)PowerTrainSgnlsRef);
	return RTE_E_OK;	
}

Std_ReturnType Rte_Read_rpDiplaySet_DE_SensorsData(DisplaySgnls_t *SensorSgnlPtr)
{
	Com_ReceiveGroupSignal(2,(uint8*)SensorSgnlPtr);
	return RTE_E_OK;
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

Std_ReturnType Rte_Call_rpIoChkControls_Opr_ChkControls(ControlSgnls_t *ControlSgnlsPtr)
{
	RE_IoChkUserControls(ControlSgnlsPtr);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLcdSet_Opr_HeadSet(boolean HeadState)
{
	RE_HeadLightDisplay(HeadState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLcdSet_Opr_WiperSet(boolean WiperState)
{
	RE_WiperDisplay(WiperState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLcdSet_Opr_CVtSet(uint8 Cvt_val)
{
	RE_CvtDisplay(Cvt_val);
	return RTE_E_OK;
}
Std_ReturnType Rte_Call_rpLcdSet_Opr_HazardSet(boolean HazardState)
{
	RE_HazardLightDisplay(HazardState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLcdSet_Opr_RightUltrasonicSet(boolean RightUltraSonicState)
{
	RE_RightUltraSonic(RightUltraSonicState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLcdSet_Opr_LeftUltrasonicSet(boolean LeftUltraSonicState)
{
	RE_LeftUltraSonic(LeftUltraSonicState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLcdSet_Opr_LeftSet(boolean LeftState)
{
	RE_LeftLightDisplay(LeftState);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpLcdSet_Opr_RightSet(boolean RightState)
{
	RE_RightLightDisplay(RightState);
	return RTE_E_OK;
}

Std_ReturnType  Rte_Call_rpLcdSet_Opr_RpmUpdate(uint32* Rpm)
{
	RE_RpmUpdate(Rpm);
	return RTE_E_OK;
}
Std_ReturnType  Rte_Call_rpLcdSet_Opr_KMH_Update(uint32* KMH_Ref)
{
	RE_KMH_Update(KMH_Ref);
	return RTE_E_OK;
}
Std_ReturnType  Rte_Call_rpLcdSet_Opr_Screen_init()
{
	RE_Screen_init();
	return RTE_E_OK;
}

Std_ReturnType  Rte_Call_rpLcdSet_Opr_BattLvlSet(Batterylvl_t* Batterylvl)
{
	RE_BatteryLvlUpdate(Batterylvl);
	return RTE_E_OK;
}


Std_ReturnType  Rte_Call_rpLcdSet_Opr_TempertureSet(Temperature_t* Temperature)
{
	RE_TemperatureUpdate(Temperature);
	return RTE_E_OK;
}


/* ***************************************************** */
/* 														 */
/* Com Callbacks Impl - InterECU					 	 */
/* 														 */
/* ***************************************************** */

void Rte_ComCbk_Sensor_StateGroup()
{
	Os_SetEvent(OsTaskId_AppTsk,
	OsConf_OsEvent_AppTsk_DRE_Sensor_Data_Signals);
	
}
/* ***************************************************** */
/* 														 */
/* Tasks Impl					 						 */
/* 														 */
/* ***************************************************** */

void CyclicTask(void)
{
	RE_HMI_ChkCtrls_MainFunction();
	RE_MainFunction_UpdateScreen();
	if(static_counter%5 == 0)
	{
		RE_MainFunction_Lights();
	}
	Os_TerminateTask();
}

void AppTsk(void)
{
	EventMaskType CurrentEvents = 0;

	/* Wait for events */
	Os_WaitEvent(OsConf_OsEvent_AppTsk_DRE_Display_DisplaySignals);

	/* Get the set events */
	Os_GetEvent(OsTaskId_AppTsk, &CurrentEvents);

	/* Clear the events */
	Os_ClearEvent(CurrentEvents);

	if ((CurrentEvents & OsConf_OsEvent_AppTsk_DRE_Display_DisplaySignals) != 0)
	{
		RE_DataRecieve_ControlsUpdate();
	}
	
	if ((CurrentEvents & OsConf_OsEvent_AppTsk_DRE_Sensor_Data_Signals) != 0)
	{
		RE_DataRecieve_SensorsUpdate();
	}
}

/* ***************************************************** */
/* 														 */
/* RTE State Machine APIs					 			 */
/* 														 */
/* ***************************************************** */
volatile uint8 Num_buffer[9];
Std_ReturnType Rte_Start()
{
	// Initialization of Display LCD software commpoent
	RE_Display_init();
	Os_SetRelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_100ms, 0, 100);
	
	return RTE_E_OK;
}

Std_ReturnType Rte_Stop()
{
	Os_CancelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_100ms);

	return RTE_E_OK;
}
