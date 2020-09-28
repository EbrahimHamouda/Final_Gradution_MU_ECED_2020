/**
*
* \file SWC_VLS_Template.c
* \brief Rte Component Template for AUTOSAR SWC: SWC_VLS
*
* \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
* Generated on 8/28/2020 08:09 AM
*
* For any inquiries: hassan.m.farahat@gmail.com
*
*/

#include "Rte_VLS.h"

static BlinkingObject_t BlinkingObject;
static WiperDirction_t Wiper_Dirction = UP_WORD;
static uint8 sCounter = 0;

/**
*
* Runnable RE_DataRevieve_VLS_Sgnl_Update
* Triggered By:
*  - DataReceivedEventImpl.DRE_rpVLS_SetSgnl_DE_VlsSignals
*
*/

DisplaySgnls_t DE_VlsSignals;
boolean RightState;
void RE_DataRevieve_VLS_Sgnl_Update(void)
{
	Std_ReturnType status;
	boolean HazardState;
	boolean HeadState;
	boolean LeftState;
	boolean WiperState;
	boolean BrakeState;
	

	/*
	*Data Receive Points
	* Signals needed to be update
	* at every new Data recieve Event
	*/
	status = Rte_Read_rpVLS_SetSgnl_DE_VlsSignals(&DE_VlsSignals);
	/* Change the Head State Light*/
	HeadState = DE_VlsSignals.Head_State;
	/**/
	BrakeState = DE_VlsSignals.Brake_State;
	/* Change the Hazard State Light*/
	HazardState = DE_VlsSignals.Hazard_State;
	/* Change the Hazard State Blinking Status*/
	BlinkingObject.Hazard_State.Isworking = HazardState;
	/* Change the Hazard State Light*/
	LeftState = DE_VlsSignals.Left_State;
	/* Change the Hazard State Blinking Status*/
	BlinkingObject.Left_State.Isworking = LeftState;
	/* Change the Hazard State Light*/
	RightState = DE_VlsSignals.Right_State;
	/* Change the Hazard State Blinking Status*/
	BlinkingObject.Right_State.Isworking = RightState;
	/* Change the Hazard State Blinking Status*/
	WiperState = DE_VlsSignals.Wiper_State;
	/* Change the Hazard State Blinking Status*/
	BlinkingObject.Wiper_State.Isworking = WiperState;
	

	status = Rte_Call_rpLedSet_HeadLed_Set(HeadState);
	status = Rte_Call_rpLedSet_BrakeLed_set(BrakeState);
	status = Rte_Call_rpWiperSet_WiperSet(WiperState);

	if (HazardState == 1)
	{
		status = Rte_Call_rpLedSet_HazardLed_Set(HazardState);
	}
	else
	{
		status = Rte_Call_rpLedSet_LeftLed_Set(LeftState);
		status = Rte_Call_rpLedSet_RightLed_Set(RightState);
	}
}

/**
*
* Runnable RE_MainFunction_Update
*
* Triggered By:
*  - TimingEventImpl.TE_RE_MainFunction_Update_500ms
*
*/

void RE_MainFunction_Update(void)
{
	Std_ReturnType status;
	boolean HeadState;
	boolean HazardState;
	boolean RightState;
	boolean LeftState;
	uint8 Wiper_poistion;

	if (sCounter % 5 == 0)
	{
		if (BlinkingObject.Hazard_State.Isworking == 1)
		{
			HazardState = !(BlinkingObject.Hazard_State.Current_status);
			status = Rte_Call_rpLedSet_HazardLed_Set(HazardState);
			BlinkingObject.Hazard_State.Current_status = HazardState;
		}
		else
		{
			// Default State when off
			BlinkingObject.Hazard_State.Current_status = 0;
			
			if (BlinkingObject.Right_State.Isworking == 1)
			{
				RightState = !(BlinkingObject.Right_State.Current_status);
				status = Rte_Call_rpLedSet_RightLed_Set(RightState);
				BlinkingObject.Right_State.Current_status = RightState;
			}
			else
			{
				// Default State when off
				BlinkingObject.Right_State.Current_status = 0;
			}
			
			if (BlinkingObject.Left_State.Isworking == 1)
			{
				LeftState = !(BlinkingObject.Left_State.Current_status);
				status = Rte_Call_rpLedSet_LeftLed_Set(LeftState);
				BlinkingObject.Left_State.Current_status = LeftState;
			}
			else
			{
				// Default State when off
				BlinkingObject.Left_State.Current_status = 0;
			}
		}
	}

	if (BlinkingObject.Wiper_State.Isworking == 1)
	{
		if (Wiper_Dirction == UP_WORD)
		{
			(BlinkingObject.Wiper_State.Current_status)++;
		}
		else if (Wiper_Dirction == DOWN_WORD)
		{
			(BlinkingObject.Wiper_State.Current_status)--;
		}
		else
		{
			/* code */
		}

		Wiper_poistion = BlinkingObject.Wiper_State.Current_status;
		status = Rte_Call_rpWiperSet_WiperSet(Wiper_poistion);

		if (BlinkingObject.Wiper_State.Current_status == WIPER_MAX_UP_WORD)
		{
			Wiper_Dirction = DOWN_WORD;
		}
		else if (BlinkingObject.Wiper_State.Current_status == WIPER_MIN_DOWN_WORD)
		{
			Wiper_Dirction = UP_WORD;
		}
		else
		{
			/* code */
		}
	}
	else
	{
		// Default State when off
		BlinkingObject.Wiper_State.Current_status = WIPER_MIN_DOWN_WORD;
	}
	
	sCounter++;
}
