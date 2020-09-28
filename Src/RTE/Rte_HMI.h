/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */
 
#ifndef RTE_HMI_H
#define RTE_HMI_H

#include "Rte_HMI_Type.h"

/* RTE APIs Prototype Declaration */
Std_ReturnType Rte_Call_rpIoChkControls_Opr_ChkControls(ControlSgnls_t*);
Std_ReturnType Rte_Write_ppDisplaySignals_DE_DisplayCtrls(DisplaySgnls_t*);
Std_ReturnType Rte_Write_ppVLS_SetSgnl_DE_VLS(DisplaySgnls_t*);
Std_ReturnType Rte_Write_ppPTS_SetSgnl_DE_PTS(PowerTrainSgnls_t*);

/* Runnables Prototype Declaration */
void RE_HMI_ChkCtrls_MainFunction(void);

#endif