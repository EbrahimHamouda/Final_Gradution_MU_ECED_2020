/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_MAIN_MOTOR_H
#define RTE_MAIN_MOTOR_H

#include "Rte_Type.h"

/* RTE APIs Prototype Declaration */
Std_ReturnType Rte_Call_rpSetMotorIoPwr_Opr_IoGetMainMotor_Speed(MotorSpeed_t *);
Std_ReturnType Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_Minus();
Std_ReturnType Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_plus();

/* Runnables Prototype Declaration */
void RE_GetMainMotor_Speed(MotorSpeed_t *);
void RE_MainMotorPwr_Minus(void);
void RE_MainMotorPwr_plus(void);
#endif