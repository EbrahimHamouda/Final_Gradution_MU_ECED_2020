/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */
 
#ifndef RTE_MAIN_H
#define RTE_MAIN_H

#include "Rte_Type.h"


typedef struct
{
	boolean IsUpdated;
	Std_ReturnType Status;
} Rte_DataFlagsType;

typedef struct
{
	Rte_DataFlagsType Display_Sgnls;
} Rte_SenderReceiverFlagsType;

typedef struct
{
	DisplaySgnls_t Display_Sgnls;
} Rte_SenderReceiverBuffersType;

Std_ReturnType Rte_Start(void);
Std_ReturnType Rte_Stop(void);

#endif