/**
 *
 * \file SWC_ADAS_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: SWC_ADAS
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/16/2020 05:01 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_ADAS.h"
#include "DHT11.h"

/**
 *
 * Runnable RE_ADAS_MainFunction
 *
 * Triggered By:
 *  - TimingEventImpl.TE_RE_ADAS_MainFunction_100ms
 *
 */

SensorData_t DE_SensorData;


void RE_ADAS_MainFunction(void)
{
	Std_ReturnType status;
	UltraSonicDis_t UltraSonicDis;
	/* Server Call Points */
	status = Rte_Call_rpBatterlyLvl_Opr_GetBatteryVal(&(DE_SensorData.Batterylvl));
	status = Rte_Call_rpTempertureAndHumid_GetTempAndHum(&(DE_SensorData.Temperature), &(DE_SensorData.Humditity));
	status = Rte_Call_rpUltraSonic_Opr_GetUltraSonic(&UltraSonicDis);
	DE_SensorData.UltraSonicDisLeft = UltraSonicDis.Left_UltraSonic;
	DE_SensorData.UltraSonicDisRight = UltraSonicDis.Right_UltraSonic;
	status = Rte_Write_ppSensorData_DE_SensorData(&DE_SensorData);
}

#if 0
/**
 * here is the parking algo used to determine the angel this function should work if parking mode activated 
 *
 * Runnable RE_ADAS_ParkingSys
 *
 * Triggered By:
 *  - SwcModeSwitchEventImpl.MSE_rpCVT_Mode_Park_ON_ENTRY
 *
 */

void RE_ADAS_ParkingSys (void)
{
	Std_ReturnType status;
	PowerTrainSgnls_t DE_PTS;

	/* Data Send Points */
	status = Rte_Write_ppPts_SetSignls_DE_PTS(DE_PTS);
	
}
#endif
