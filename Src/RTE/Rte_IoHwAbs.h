/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_IOHWABS_H
#define RTE_IOHWABS_H

#include "Rte_IoHwAbs_Type.h"

/* RTE APIs Prototype Declaration */

/* Runnables Prototype Declaration */
void RE_IoChkUserControls(ControlSgnls_t *Control_Signals);
void RE_HeadLed(boolean HeadState);
void RE_HazardLed(boolean HazardState);
void RE_RightLed(boolean RightState);
void RE_LeftLed(boolean LeftState);
void RE_WiperPoistion(uint8);
void RE_IoMainMotor_Plus(void);
void RE_IoMainMotor_Minus(void);
void RE_IoGetMainMotor_Speed(MotorSpeed_t *MotorSpeed);
Std_ReturnType RE_IoServoMotor_Set(ServoPosition_t );
void RE_IoGetServoMotor_Position(ServoPosition_t *ServoPosition);
#endif