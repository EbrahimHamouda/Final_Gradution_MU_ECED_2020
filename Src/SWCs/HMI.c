/**
*
* \file SWC_HMI_Template.c
* \brief Rte Component Template for AUTOSAR SWC: SWC_HMI
*
* \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
* Generated on 8/25/2020 09:27 AM
*
* For any inquiries: hassan.m.farahat@gmail.com
*
*/

#include "Rte_HMI.h"

static boolean ignition_State = FALSE ;

/*
* STATIC FUNCATIONS
*/
static void Map_ControlSgnls_2_DisplaySgnls(ControlSgnls_t *ControlSgnlsPtr, DisplaySgnls_t *DisplaySgnlPtr)
{
	DisplaySgnlPtr->Hazard_State = ControlSgnlsPtr->HazardCtrl;
	DisplaySgnlPtr->Head_State   = ControlSgnlsPtr->HeadCtrl;
	DisplaySgnlPtr->Brake_State  = ControlSgnlsPtr->BrakeCtrl;
	DisplaySgnlPtr->Left_State   = ControlSgnlsPtr->LeftCtrl;
	DisplaySgnlPtr->Right_State  = ControlSgnlsPtr->RightCtrl;
	DisplaySgnlPtr->Wiper_State  = ControlSgnlsPtr->WiperCtrl;
	if (ControlSgnlsPtr->GasCtrl == TRUE)
	{
		DisplaySgnlPtr->Rpm_State    = GAS_IS_ON;
	}
	else if (ControlSgnlsPtr->BrakeCtrl == TRUE)
	{
		DisplaySgnlPtr->Rpm_State    = BRAKE_ON;
	}
	else
	{
		DisplaySgnlPtr->Rpm_State    = GAS_BRAKE_OFF;
	}
	DisplaySgnlPtr->CvtMood = map((ControlSgnlsPtr->CVTCtrl),0,1024,0,3);
}

static void Map_ControlSgnls_2_ptsSgnls(ControlSgnls_t *ControlSgnlsPtr, PowerTrainSgnls_t *PowerTrainSgnlsRef)
{
	PowerTrainSgnlsRef->Brake_State = ControlSgnlsPtr->BrakeCtrl;
	PowerTrainSgnlsRef->Streeing_Angle = map((ControlSgnlsPtr->StreeingCtrl), 0, 1023, 0, 255);
	PowerTrainSgnlsRef->Gas_State = ControlSgnlsPtr->GasCtrl;
}

/**
*
* Runnable RE_HMI_ChkCtrls_MainFunction
*
* Triggered By:
*  - TimingEventImpl.TE_RE_HMI_ChkCtrls_MainFunction_100ms
*
*/

volatile ControlSgnls_t Control_Signals;
DisplaySgnls_t DE_DisplayCtrls;
PowerTrainSgnls_t DE_PTS;

void RE_HMI_ChkCtrls_MainFunction(void)
{
	Std_ReturnType status;

	/* Server Call Points */
	status = Rte_Call_rpIoChkControls_Opr_ChkControls(&Control_Signals);
	
	ignition_State = Control_Signals.IgntionCtrl;
	
	if (ignition_State)
	{
		/* Mapping Controls To other components*/
		Map_ControlSgnls_2_DisplaySgnls(&Control_Signals, &DE_DisplayCtrls);
		Map_ControlSgnls_2_ptsSgnls(&Control_Signals, &DE_PTS);

		/* Data Send Points */
		status = Rte_Write_ppDisplaySignals_DE_DisplayCtrls(&DE_DisplayCtrls);
		status = Rte_Write_ppVLS_SetSgnl_DE_VLS(&DE_DisplayCtrls);
		if (DE_PTS.Gas_State == 1)
		{
			if (DE_DisplayCtrls.CvtMood == 0)
			{
				DE_PTS.Gas_State = 1;
			}
			else if (DE_DisplayCtrls.CvtMood == 2)
			{
				DE_PTS.Gas_State = 255;
			}
			else
			{
				DE_PTS.Gas_State = 0;
			}
		}
		status = Rte_Write_ppPTS_SetSgnl_DE_PTS(&DE_PTS);
	}
}
