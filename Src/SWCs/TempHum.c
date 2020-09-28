/**
 *
 * \file SWC_TempHum_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: SWC_TempHum
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/16/2020 05:37 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_TempHum.h"


/**
 *
 * Runnable RE_TempHumGetVal
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppTempHumGet_GetTempAndHum
 *
 */

void RE_TempHumGetVal (Temperature_t* Temperature, Humditity_t* Humedity)
{
	Std_ReturnType status;
	

	/* Server Call Points */
	status = Rte_Call_rpIoTempHumGet_Opr_GetVal(Temperature, Humedity);
	
}

