/**
 *
 * \file MainMotor_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: MainMotor
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/13/2020 12:31 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_MainMotor.h"


/**
 *
 * Runnable RE_GetMainMotor_Speed
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppMotorSetPwr_Opr_GetMainMotorSpeed
 *
 */

void RE_GetMainMotor_Speed (MotorSpeed_t* MotorSpeed)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSetMotorIoPwr_Opr_IoGetMainMotor_Speed(&MotorSpeed);
	
}


/**
 *
 * Runnable RE_MainMotorPwr_Minus
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppMotorSetPwr_Opr_MainMotorMinus
 *
 */

void RE_MainMotorPwr_Minus (void)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_Minus();
}


/**
 *
 * Runnable RE_MainMotorPwr_plus
 *
 * Triggered By:
 *  - OperationInvokedEventImpl.OIE_ppMotorSetPwr_Opr_MainMotorPlus
 *
 */

void RE_MainMotorPwr_plus (void)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_plus();
	
}
void RE_MainMotor_DirctionChange(MotorDirction_t MotorDirction)
{
	Rte_Call_rpSetMotorIoPwr_Opr_IoMainMotor_DirctionChange(MotorDirction);
}