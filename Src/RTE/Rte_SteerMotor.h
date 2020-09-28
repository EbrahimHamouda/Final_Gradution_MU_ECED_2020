/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_STEER_MOTOR_H
#define RTE_STEER_MOTOR_H

#include "Rte_VLS_Type.h"

/* RTE APIs Prototype Declaration */
Std_ReturnType Rte_Call_rpIoservoMotor_Opr_IoGetServoMotorPosition(ServoPosition_t*);
Std_ReturnType Rte_Call_rpIoservoMotor_Opr_ServoMotorSet(ServoPosition_t);

/* Runnables Prototype Declaration */
void RE_GetServoPosition (ServoPosition_t*);
Std_ReturnType RE_ServoPositionSet(ServoPosition_t ServoPosition);
#endif