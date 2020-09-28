/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_LED_H
#define RTE_LED_H

#include "Rte_Type.h"

/* RTE APIs Prototype Declaration */
Std_ReturnType Rte_Call_rpSet_Led_Opr_SetHeadLed(boolean);
Std_ReturnType Rte_Call_rpSet_Led_Opr_SetHazardLed(boolean);
Std_ReturnType Rte_Call_rpSet_Led_Opr_SetRightLed(boolean);
Std_ReturnType Rte_Call_rpSet_Led_Opr_SetLeftLed(boolean);
Std_ReturnType Rte_Call_rpSet_Led_Opr_SetWiperPosition(uint8);
/* Runnable Prototype Declaration */

void RE_HeadLightLed (boolean HeadState);
void RE_HazardLightLed (boolean HazardState);
void RE_RightLightLed (boolean RightState);
void RE_LeftLightLed (boolean LeftState);
void RE_WiperPosition (uint8 WiperPosition);

#endif