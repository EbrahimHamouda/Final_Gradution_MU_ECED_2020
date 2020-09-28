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
#include "Rte_PTS.h"
#include "Rte_SteerMotor.h"
#include "Rte_MainMotor.h"
#include "Rte_IoHwAbs.h"
#include "Com.h"
#include "Os.h"

/* ***************************************************** */
/* 														 */
/* Sender Receiver Variables 							 */
/* 														 */
/* ***************************************************** */

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
Std_ReturnType Rte_Read_rpPTs_SetSignals_DE_PTS(PowerTrainSgnls_t *PowerTrainSgnls)
{
	/*Read needed Signals from Com module buffer*/
	Com_ReceiveGroupSignal(0, (uint8 *)PowerTrainSgnls);
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

Std_ReturnType Rte_Call_rpServoSet_Opr_GetServoMotorPos(ServoPosition_t *ServoPositionRef)
{
	RE_GetServoPosition(ServoPositionRef);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpServoSet_Opr_ServoMotorSet(ServoPosition_t ServoPosition)
{
	return RE_ServoPositionSet(ServoPosition);
}

Std_ReturnType Rte_Call_rpIoservoMotor_Opr_IoGetServoMotorPosition(ServoPosition_t* ServoPositionRef)
{
	RE_IoGetServoMotor_Position(ServoPositionRef);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpIoservoMotor_Opr_ServoMotorSet(ServoPosition_t ServoPosition)
{
	RE_IoServoMotor_Set(ServoPosition);
	return RTE_E_OK;
	
}



Std_ReturnType Rte_Call_rpMotorSet_Opr_GetMainMotorSpeed(MotorSpeed_t *MotorSpeedRef)
{
	RE_GetMainMotor_Speed(MotorSpeedRef);
	return RTE_E_OK;
}
Std_ReturnType Rte_Call_rpMotorSet_Opr_MainMotorMinus()
{
	RE_MainMotorPwr_Minus();
	return RTE_E_OK;
}
Std_ReturnType Rte_Call_rpMotorSet_Opr_MainMotorPlus()
{
	RE_MainMotorPwr_plus();	
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpMotorSet_Opr_DirctionChange(MotorDirction_t MotorDirction)
{
	RE_MainMotor_DirctionChange(MotorDirction);
	return RTE_E_OK;
}

Std_ReturnType Rte_Call_rpSetMotorIoPwr_Opr_IoGetMainMotor_Speed(MotorSpeed_t *MotorSpeedRef)
{
	RE_IoGetMainMotor_Speed(MotorSpeedRef);
	return RTE_E_OK;
}
Std_ReturnType Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_Minus()
{
	RE_IoMainMotor_Minus();
	return RTE_E_OK;
}
Std_ReturnType Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_plus()
{
	RE_IoMainMotor_Plus();
	return RTE_E_OK;
}

Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_DirctionChange(MotorDirction_t MotorDirction)
{
	RE_IoMainMotor_DirctionChange(MotorDirction);
	return RTE_E_OK;
}
/* ***************************************************** */
/* 														 */
/* Com Callbacks Impl - InterECU					 	 */
/* 														 */
/* ***************************************************** */

void Rte_ComCbk_PTS_StateGroup(void)
{
	Os_SetEvent(OsTaskId_AppTsk,
				OsConf_OsEvent_AppTsk_DRE_POWER_TRIAN_Signals);
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
	Os_WaitEvent(OsConf_OsEvent_AppTsk_DRE_POWER_TRIAN_Signals);

	/* Get the set events */
	Os_GetEvent(OsTaskId_AppTsk, &CurrentEvents);

	/* Clear the events */
	Os_ClearEvent(CurrentEvents);

	if ((CurrentEvents & OsConf_OsEvent_AppTsk_DRE_POWER_TRIAN_Signals) != 0)
	{
		RE_DataRevieve_PTS_SgnlNormal_Update();
	}
}

/* ***************************************************** */
/* 														 */
/* RTE State Machine APIs					 			 */
/* 														 */
/* ***************************************************** */

Std_ReturnType Rte_Start()
{

	Os_SetRelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_100ms, 0, 100);

	return RTE_E_OK;
}

Std_ReturnType Rte_Stop()
{
	Os_CancelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_100ms);

	return RTE_E_OK;
}
