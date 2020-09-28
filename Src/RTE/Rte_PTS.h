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
Std_ReturnType Rte_Call_rpMotorSet_Opr_GetMainMotorSpeed(MotorSpeed_t *);
Std_ReturnType Rte_Call_rpMotorSet_Opr_MainMotorMinus();
Std_ReturnType Rte_Call_rpMotorSet_Opr_MainMotorPlus();
Std_ReturnType Rte_Read_rpPTs_SetSignals_DE_PTS(PowerTrainSgnls_t *);
Std_ReturnType Rte_Call_rpServoSet_Opr_GetServoMotorPos(ServoPosition_t *);
Std_ReturnType Rte_Call_rpServoSet_Opr_ServoMotorSet(ServoPosition_t);

/* Runnables Prototype Declaration */
void RE_DataRevieve_PTS_SgnlNormal_Update(void);
void RE_MainFunction_Update(void);
void RE_DataRevieve_PTS_SgnlParking_Update(void);

#endif