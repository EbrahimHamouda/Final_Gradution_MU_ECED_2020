/**
 *
 * \file SWC_PTS_Template.c
 * \brief Rte Component Template for AUTOSAR SWC: SWC_PTS
 *
 * \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
 * Generated on 9/13/2020 12:45 PM
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#include "Rte_PTS.h"
#include "pwm.h"
/*****************************
 * INTERNAL STATIC VARIABLES *
******************************/
static volatile PowerTrainSgnls_t SPowerTrainSgnls;

/**
 *
 * Runnable RE_DataRevieve_PTS_SgnlNormal_Update
 *
 * Triggered By:
 *  - DataReceivedEventImpl.DRE_rpPTs_SetSignals_DE_PTS
 *
 */
void RE_DataRevieve_PTS_SgnlNormal_Update(void)
{
	Std_ReturnType status;
	PowerTrainSgnls_t DE_PTS;
	ServoPosition_t current_ServoPosition;

	/* Data Receive Points */
	status = Rte_Read_rpPTs_SetSignals_DE_PTS(&DE_PTS);
	/* Save in internal buffer */
	SPowerTrainSgnls = DE_PTS;
	/* adjust Steering Motor */
	status = Rte_Call_rpServoSet_Opr_GetServoMotorPos(&current_ServoPosition);
	if (current_ServoPosition != DE_PTS.Streeing_Angle)
	{
		Rte_Call_rpServoSet_Opr_ServoMotorSet(DE_PTS.Streeing_Angle);
	}
}

/**
 *
 * Runnable RE_MainFunction_Update
 *
 * Triggered By:
 *  - TimingEventImpl.TE_RE_MainFunction_Update_100ms
 *
 */

void RE_MainFunction_Update(void)
{
	Std_ReturnType status;
	MotorSpeed_t MotorSpeed;

	/* adjust Main motor*/
	if (SPowerTrainSgnls.Gas_State == 1)
	{
		Rte_Call_rpMotorSet_Opr_DirctionChange(FORWARD_DIRCTION);
		status = Rte_Call_rpMotorSet_Opr_MainMotorPlus();
	}
	else if (SPowerTrainSgnls.Gas_State == 0xff)
	{
		Rte_Call_rpMotorSet_Opr_DirctionChange(BACKWARD_DIRCTION);
		status = Rte_Call_rpMotorSet_Opr_MainMotorPlus();
	}
	else if (SPowerTrainSgnls.Brake_State == TRUE)
	{
		status = Rte_Call_rpMotorSet_Opr_MainMotorMinus();
		status = Rte_Call_rpMotorSet_Opr_MainMotorMinus();
	}
	else
	{
		//TODO: Minus here is different 
		status = Rte_Call_rpMotorSet_Opr_MainMotorMinus();
	}
}

/**
 *
 * Runnable RE_DataRevieve_PTS_SgnlParking_Update
 *
 * Triggered By:
 *  - DataReceivedEventImpl.DRE_rpADAS_ParkingSgnls_DE_PTS
 *
void RE_DataRevieve_PTS_SgnlParking_Update (void)
{
	Std_ReturnType status;
	PowerTrainSgnls_t DE_PTS;

	status = Rte_Read_rpADAS_ParkingSgnls_DE_PTS(&DE_PTS);
	
	status = Rte_Call_rpServoSet_Opr_GetServoMotorPos();
	status = Rte_Call_rpServoSet_Opr_ServoMotorMinus();
	status = Rte_Call_rpServoSet_Opr_ServoMotorPlus();
	
}
 */
