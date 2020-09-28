/**
*
* \file UltraSonic_Template.c
* \brief Rte Component Template for AUTOSAR SWC: UltraSonic
*
* \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
* Generated on 9/16/2020 05:53 PM
*
* For any inquiries: hassan.m.farahat@gmail.com
*
*/

#include "Rte_UltraSonic.h"


/**
*
* Runnable RE_UltraSonicGetVal
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppUltraSonicGet_Opr_GetUltraSonic
*
*/

static uint8 internal_coun =0;

void RE_UltraSonicGetVal (UltraSonicDis_t* UltaSonic_MinDistance)
{
	Std_ReturnType status;

	status = Rte_Call_rpIoUltraSonicGet_Opr_Us1(&(UltaSonic_MinDistance->Right_UltraSonic));
	
	status = Rte_Call_rpIoUltraSonicGet_Opr_Us2(&(UltaSonic_MinDistance->Left_UltraSonic));
}

