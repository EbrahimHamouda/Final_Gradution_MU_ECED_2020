/**
*
* \file SWC_Display_Template.c
* \brief Rte Component Template for AUTOSAR SWC: SWC_Display
*
* \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
* Generated on 8/26/2020 09:04 AM
*
* For any inquiries: hassan.m.farahat@gmail.com
*
*/

#include "Rte_Display.h"

/*****************************
*   INTERNAL CONSTANTS		 *
******************************/
#define MAX_RPM 4095
#define MIN_RPM 0

#define MAX_KMH 255
#define MIN_KMH 0

/*****************************
* INTERNAL STATIC VARIABLES *
******************************/
static uint32 rpm = MIN_RPM;
static uint32 KMH = MIN_RPM;

static BlinkingObject_t BlinkingObject;
static RpmState_t S_RpmState = GAS_BRAKE_OFF;
static boolean Zero_flag = 0;
static Right_UltraSonicBlinkingRate = 5;
static Left_UltraSonicBlinkingRate = 5;
uint32 hours, Mins, Secs;
static uint8 SCvtMoood;

/**
*
* Runnable RE_MainFunction_UpdateScreen
*
* Triggered By:
*  - TimingEventImpl.TE_RE_MainFunction_UpdateScreen_100ms
*
*/

void RE_MainFunction_UpdateScreen(void)
{
	Std_ReturnType status;
	boolean HazardState;
	boolean LeftState;
	boolean RightState;
	boolean RightUltraSonicState;
	boolean LeftUltraSonicState;

	if ((SCvtMoood == 0) || (SCvtMoood == 2))
	{
		/*Update RPM KM CvtMood */

		if (S_RpmState == GAS_IS_ON)
		{

			if (rpm < MAX_RPM)
			{
				rpm += 20;
			}
			else
			{
			}
		}
		else
		{
			if (rpm > MIN_RPM)
			{
				if (S_RpmState == BRAKE_ON)
				{
					if (rpm >= 40)
					{
						rpm -= 40;
					}
					else
					{
						rpm = 0;
					}
				}
				else
				{
					if (rpm >= 20)
					{
						rpm -= 20;
					}
					else
					{
						rpm = 0;
					}
				}
			}
			else
			{
			}
		}
		KMH = map(rpm, MIN_RPM, MAX_RPM, MIN_KMH, MAX_KMH);
		if (rpm == 0)
		{
			if (Zero_flag == 0)
			{
				Zero_flag = 1;
				status = Rte_Call_rpLcdSet_Opr_RpmUpdate(&rpm);
				status = Rte_Call_rpLcdSet_Opr_KMH_Update(&KMH);
			}
			else
			{
			}
		}
		else
		{
			Zero_flag = FALSE;
			status = Rte_Call_rpLcdSet_Opr_RpmUpdate(&rpm);
			status = Rte_Call_rpLcdSet_Opr_KMH_Update(&KMH);
		}
	}

	if (SCvtMoood == 2)
	{
		if ((BlinkingObject.Right_UltraSonic.Isworking == TRUE) &&
			(static_counter % Right_UltraSonicBlinkingRate == 0))
		{
			RightUltraSonicState = !(BlinkingObject.Right_UltraSonic.Current_status);
			status = Rte_Call_rpLcdSet_Opr_RightUltrasonicSet(RightUltraSonicState);
			BlinkingObject.Right_UltraSonic.Current_status = RightUltraSonicState;
		}
		else
		{
			status = Rte_Call_rpLcdSet_Opr_RightUltrasonicSet(FALSE);
		}

		if ((BlinkingObject.Left_UltraSonic.Isworking == TRUE) &&
			(static_counter % Left_UltraSonicBlinkingRate == 0))
		{
			LeftUltraSonicState = !(BlinkingObject.Left_UltraSonic.Current_status);
			status = Rte_Call_rpLcdSet_Opr_LeftUltrasonicSet(LeftUltraSonicState);
			BlinkingObject.Left_UltraSonic.Current_status = LeftUltraSonicState;
		}
		else
		{
			status = Rte_Call_rpLcdSet_Opr_LeftUltrasonicSet(FALSE);
		}
	}

	if ((static_counter % 10) == 0)
	{
		BlinkingObject.Clock_state.Current_status = !BlinkingObject.Clock_state.Current_status;
		if (BlinkingObject.Clock_state.Current_status == TRUE)
		{
			lcd_goto(&lcd1, 1, 17);
			lcd_chr(&lcd1, ':');
		}
		else
		{
			lcd_goto(&lcd1, 1, 17);
			lcd_chr(&lcd1, ' ');
		}

		Secs++;
		if (Secs == 60)
		{
			Secs = 0;
			Mins++;
			if (Mins < 10)
			{
				lcd_chr(&lcd1, '0');
				lcd_num(&lcd1, 1, 19, &Mins);
			}
			else
			{
				lcd_num(&lcd1, 1, 18, &Mins);
			}
		}
	}
	static_counter++;
}

/**
*
* Runnable RE_MainFunction_Lights
*
* Triggered By:
*  - TimingEventImpl.TE_RE_MainFunction_Lights_500ms
*
*/

void RE_MainFunction_Lights(void)
{
	Std_ReturnType status;
	boolean HazardState;
	boolean LeftState;
	boolean RightState;
	boolean RightUltraSonicState;
	boolean LeftUltraSonicState;

	if (BlinkingObject.Hazard_State.Isworking == 1)
	{
		HazardState = !(BlinkingObject.Hazard_State.Current_status);
		status = Rte_Call_rpLcdSet_Opr_HazardSet(HazardState);
		BlinkingObject.Hazard_State.Current_status = HazardState;
	}
	else
	{
		// Default State when off
		BlinkingObject.Hazard_State.Current_status = 0;

		if (BlinkingObject.Right_State.Isworking == 1)
		{
			RightState = !(BlinkingObject.Right_State.Current_status);
			status = Rte_Call_rpLcdSet_Opr_RightSet(RightState);
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
			status = Rte_Call_rpLcdSet_Opr_LeftSet(LeftState);
			BlinkingObject.Left_State.Current_status = LeftState;
		}
		else
		{
			// Default State when off
			BlinkingObject.Left_State.Current_status = 0;
		}
	}
}

/**
*
* Runnable RE_DataRecieve_ControlsUpdate
*
* Triggered By:
*  - DataReceivedEventImpl.DRE_rpDiplaySet_DE_DisplayCtrls
*
*/

void RE_DataRecieve_ControlsUpdate(void)
{
	Std_ReturnType status;
	DisplaySgnls_t DE_DisplayCtrls;
	boolean HeadState;
	boolean WiperState;
	boolean HazardState;
	boolean LeftState;
	boolean RightState;

	/* Data Receive Points */
	status = Rte_Read_rpDiplaySet_DE_DisplayCtrls(&DE_DisplayCtrls);

	HazardState = DE_DisplayCtrls.Hazard_State;
	BlinkingObject.Hazard_State.Isworking = HazardState;

	LeftState = DE_DisplayCtrls.Left_State;
	BlinkingObject.Left_State.Isworking = LeftState;

	RightState = DE_DisplayCtrls.Right_State;
	BlinkingObject.Right_State.Isworking = RightState;

	S_RpmState = DE_DisplayCtrls.Rpm_State;

	/*Static Display objects*/
	status = Rte_Call_rpLcdSet_Opr_HeadSet(DE_DisplayCtrls.Head_State);
	status = Rte_Call_rpLcdSet_Opr_WiperSet(DE_DisplayCtrls.Wiper_State);
	status = Rte_Call_rpLcdSet_Opr_CVtSet((DE_DisplayCtrls.CvtMood));

	if (HazardState == 1)
	{
		status = Rte_Call_rpLcdSet_Opr_HazardSet(HazardState);
	}
	else
	{
		status = Rte_Call_rpLcdSet_Opr_LeftSet(LeftState);
		status = Rte_Call_rpLcdSet_Opr_RightSet(RightState);
	}

	SCvtMoood = DE_DisplayCtrls.CvtMood;
}

/**
*
* Runnable RE_DataRecieve_ControlsUpdate
*
* Triggered By:
*  - DataReceivedEventImpl.DRE_rpDiplaySet_DE_SensorData
*
*/

SensorData_t SensorData;
void RE_DataRecieve_SensorsUpdate(void)
{
	Std_ReturnType status;

	status = Rte_Read_rpDiplaySet_DE_SensorsData(&SensorData);

	if (SensorData.UltraSonicDisRight < 50)
	{
		BlinkingObject.Right_UltraSonic.Isworking = TRUE;
		BlinkingObject.Right_UltraSonic.Current_status = FALSE;
		Right_UltraSonicBlinkingRate = (SensorData.UltraSonicDisRight / 10) + 1;
	}
	else
	{
		BlinkingObject.Right_UltraSonic.Isworking = FALSE;
	}

	if (SensorData.UltraSonicDisLeft < 50)
	{
		BlinkingObject.Left_UltraSonic.Isworking = TRUE;
		BlinkingObject.Left_UltraSonic.Current_status = FALSE;
		Left_UltraSonicBlinkingRate = (SensorData.UltraSonicDisLeft / 10) + 1;
	}
	else
	{
		BlinkingObject.Left_UltraSonic.Isworking = FALSE;
	}

	Rte_Call_rpLcdSet_Opr_BattLvlSet(&(SensorData.Batterylvl));
	Rte_Call_rpLcdSet_Opr_TempertureSet(&(SensorData.Temperature));
}

void RE_Display_init()
{
	Rte_Call_rpLcdSet_Opr_Screen_init();
	RTC_GetDateTime(&myRtc);
	hours = bcd_decimal(myRtc.hour);
	Mins = bcd_decimal(myRtc.min);
	Secs = bcd_decimal(myRtc.sec);

	if (hours < 10)
	{
		lcd_goto(&lcd1, 1, 15);
		lcd_chr(&lcd1, '0');
		lcd_num(&lcd1, 1, 16, &hours);
	}
	else
	{
		lcd_num(&lcd1, 1, 15, &hours);
	}
	lcd_goto(&lcd1, 1, 17);
	lcd_chr(&lcd1, ':');

	if (Mins < 10)
	{
		lcd_chr(&lcd1, '0');
		lcd_num(&lcd1, 1, 19, &Mins);
	}
	else
	{
		lcd_num(&lcd1, 1, 18, &Mins);
	}
}