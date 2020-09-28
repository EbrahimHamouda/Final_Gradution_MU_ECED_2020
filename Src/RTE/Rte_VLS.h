/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_VLS_H
#define RTE_VLS_H

#include "Rte_VLS_Type.h"

/* RTE APIs Prototype Declaration */
Std_ReturnType Rte_Call_rpLedSet_HeadLed_Set(boolean);
Std_ReturnType Rte_Call_rpLedSet_HazardLed_Set(boolean);
Std_ReturnType Rte_Call_rpLedSet_RightLed_Set(boolean);
Std_ReturnType Rte_Call_rpLedSet_LeftLed_Set(boolean);
Std_ReturnType Rte_Call_rpWiperSet_WiperSet(boolean);
Std_ReturnType Rte_Read_rpVLS_SetSgnl_DE_VlsSignals(DisplaySgnls_t*);
/* Runnables Prototype Declaration */
void RE_DataRevieve_VLS_Sgnl_Update(void);
void RE_MainFunction_Update(void);
#endif