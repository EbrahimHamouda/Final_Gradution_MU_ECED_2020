/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_Display_H
#define RTE_Display_H

#include "Rte_Display_Type.h"

/* RTE APIs Prototype Declaration */
Std_ReturnType Rte_Read_rpDiplaySet_DE_DisplayCtrls(DisplaySgnls_t *);
Std_ReturnType Rte_Call_rpLcdSet_Opr_HeadSet(boolean HeadState);
Std_ReturnType Rte_Call_rpLcdSet_Opr_WiperSet(boolean WiperState);
Std_ReturnType Rte_Call_rpLcdSet_Opr_HazardSet(boolean HazardState);
Std_ReturnType Rte_Call_rpLcdSet_Opr_LeftSet(boolean LeftState);
Std_ReturnType Rte_Call_rpLcdSet_Opr_RightSet(boolean RightState);

/* Runnables Prototype Declaration */
void RE_MainFunction_UpdateScreen(void);
void RE_DataRecieve_ControlsUpdate(void);

#endif