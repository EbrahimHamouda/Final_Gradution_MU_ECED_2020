/**
 *
 * \file SWC_BatterySen_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: SWC_BatterySen
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/16/2020 05:27 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_BatterySen.h"


/**
 *
 * Runnable RE_BatteryGetVal
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppBattsenGet_Opr_GetBatteryVal
 *
 */

void RE_BatteryGetVal (Batterylvl_t* BatteryLvl)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpIoBattGet_Opr_GetVal(BatteryLvl);
	
}

