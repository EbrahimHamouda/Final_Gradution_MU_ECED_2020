/**
 *
 * \file SWC_Led_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: SWC_Led
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/7/2020 10:04 AM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_Led.h"


/**
 *
 * Runnable RE_HeadLightLed
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppLed_set_HeadLed_Set
 *
 */

void RE_HeadLightLed (boolean HeadState)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSet_Led_Opr_SetHeadLed(HeadState);
	
}


/**
 *
 * Runnable RE_HeadLightLed
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppLed_set_BrakeLed_Set
 *
 */

void RE_BrakeLightLed (boolean BrakeState)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSet_Led_Opr_SetBrakeLed(BrakeState);
	
}
/**
 *
 * Runnable RE_HazardLightLed
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppLed_set_HazardLed_Set
 *
 */

void RE_HazardLightLed (boolean HazardState)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSet_Led_Opr_SetHazardLed(HazardState);
	
}


/**
 *
 * Runnable RE_RightLightLed
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppLed_set_RightLed_Set
 *
 */

void RE_RightLightLed (boolean RightState)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSet_Led_Opr_SetRightLed(RightState);
	
}


/**
 *
 * Runnable RE_LeftLightLed
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppLed_set_LeftLed_Set
 *
 */

void RE_LeftLightLed (boolean LeftState)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSet_Led_Opr_SetLeftLed(LeftState);
	
}


/**
 *
 * Runnable RE_WiperPosition
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppLed_set_Wiper_PositionSet
 *
 */

void RE_WiperPosition (uint8 WiperPosition)
{
	Std_ReturnType status;
	
	/* Server Call Points */
	status = Rte_Call_rpSet_Led_Opr_SetWiperPosition(WiperPosition);
}

