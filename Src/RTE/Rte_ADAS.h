/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_PTS_H
#define RTE_PTS_H

#include "Rte_Type.h"

/* RTE APIs Prototype Declaration */
Std_ReturnType Rte_Write_ppSensorData_DE_SensorData(SensorData_t*);
Std_ReturnType Rte_Call_rpBatterlyLvl_Opr_GetBatteryVal(Batterylvl_t*);
Std_ReturnType Rte_Call_rpTempertureAndHumid_GetTempAndHum(Temperature_t*, Humditity_t*);
Std_ReturnType Rte_Call_rpUltraSonic_Opr_GetUltraSonic(UltraSonicDis_t*);

/* Runnables Prototype Declaration */
void RE_ADAS_MainFunction(void);


#endif