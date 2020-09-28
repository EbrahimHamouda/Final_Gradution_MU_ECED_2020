/**
 *
 * \file SteerMotor_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: SteerMotor
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/13/2020 12:31 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_SteerMotor.h"






/**
 *
 * Runnable RE_GetServoPosition
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppSetSteerAngle_Opr_GetServoMotorPos
 *
 */

void RE_GetServoPosition (ServoPosition_t* ServoPosition)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpIoservoMotor_Opr_IoGetServoMotorPosition(&ServoPosition);
	
}


/**
 *
 * Runnable RE_ServoPositionMinus
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppSetSteerAngle_Opr_ServoMotorMinus
 *
 */

Std_ReturnType RE_ServoPositionSet(ServoPosition_t ServoPosition)
{
	ServoPosition = (ServoPosition / 17) + 15;
	Rte_Call_rpIoservoMotor_Opr_ServoMotorSet(ServoPosition);
	
}



