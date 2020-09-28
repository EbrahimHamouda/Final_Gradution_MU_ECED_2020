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
volatile uint8 estCallBack =0 ;
void Rte_Cbk_Test()
{
	estCallBack++;
}
/* ***************************************************** */
/* 														 */
/* Client Server APIs					 				 */
/* 														 */
/* ***************************************************** */

Std_ReturnType Rte_Write_ppSensorData_DE_SensorData(SensorData_t* SensorData)
{
	Com_SendGroupSignal(0,(uint8*)SensorData);
}
Std_ReturnType Rte_Call_rpBatterlyLvl_Opr_GetBatteryVal(Batterylvl_t* BatterylvlRef)
{
	RE_BatteryGetVal(BatterylvlRef);
}

Std_ReturnType Rte_Call_rpIoBattGet_Opr_GetVal(Batterylvl_t* BatterylvlRef)
{
	RE_IoBatteryGetVal(BatterylvlRef);
}

Std_ReturnType Rte_Call_rpTempertureAndHumid_GetTempAndHum(Temperature_t* TemperatureRef, Humditity_t* HumditityRef)
{
	RE_TempHumGetVal(TemperatureRef, HumditityRef);
}

Std_ReturnType Rte_Call_rpIoTempHumGet_Opr_GetVal(Temperature_t* TemperatureRef, Humditity_t* HumditityRef)
{
	RE_IoTempHumGetVal(TemperatureRef, HumditityRef);
}
Std_ReturnType Rte_Call_rpUltraSonic_Opr_GetUltraSonic(UltraSonicDis_t* UltraSonicDisRef)
{
	RE_UltraSonicGetVal(UltraSonicDisRef);
}

Std_ReturnType Rte_Call_rpIoUltraSonicGet_Opr_Us1(uint8* UltraSonicRef)
{
	RE_UltraSonic1(UltraSonicRef);
}
Std_ReturnType Rte_Call_rpIoUltraSonicGet_Opr_Us2(uint8* UltraSonicRef)
{
	RE_UltraSonic2(UltraSonicRef); 
}
/* ***************************************************** */
/* 														 */
/* Tasks Impl					 						 */
/* 														 */
/* ***************************************************** */

void CyclicTask(void)
{
	RE_ADAS_MainFunction();
	Os_TerminateTask();
}


void AppTsk(void)
{

}

/* ***************************************************** */
/* 														 */
/* RTE State Machine APIs					 			 */
/* 														 */
/* ***************************************************** */

Std_ReturnType Rte_Start()
{
	_delay_ms(500);
	Os_SetRelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_100ms, 0, 100);

	return RTE_E_OK;
}

Std_ReturnType Rte_Stop()
{
	Os_CancelAlarm(OsConf_OsAlarm_Rte_Alarm_CyclicTask_100ms);

	return RTE_E_OK;
}
