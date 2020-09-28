/**
*
* \file SWC_LCD_CDD_Template.c
* \brief Rte Component Template for AUTOSAR SWC: SWC_LCD_CDD
*
* \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
* Generated on 8/26/2020 09:43 AM
*
* For any inquiries: hassan.m.farahat@gmail.com
*
*/

#include "Rte_LCD_CDD.h"
#include "LCD.h"



static boolean Flag_RpmSymbol= 0;
/**
*
* Runnable RE_HazardLightDisplay
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppLcd_set_Opr_HazardSet
*
*/

void RE_HazardLightDisplay(boolean HazardState)
{
	RE_LeftLightDisplay(HazardState);
	RE_RightLightDisplay(HazardState);
}

/**
*
* Runnable RE_HazardLightDisplay
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppLcd_set_Opr_HazardSet
*
*/

void RE_RightUltraSonic(boolean RightUltraSonicState)
{
	lcd_goto(&lcd1, 0, 12);
	if (RightUltraSonicState == TRUE)
	{
		lcd_chr(&lcd1, '!');
	}
	else
	{
		lcd_chr(&lcd1,' ');
	}
}


/**
*
* Runnable RE_HazardLightDisplay
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppLcd_set_Opr_HazardSet
*
*/

void RE_LeftUltraSonic(boolean LeftUltraSonicState)
{
	lcd_goto(&lcd1, 0, 8);
	if (LeftUltraSonicState == TRUE)
	{
		lcd_chr(&lcd1, '!');
	}
	else
	{
		lcd_chr(&lcd1, ' ');
	}
}

/**
*
* Runnable RE_HeadLightDisplay
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppLcd_set_Opr_HeadSet
*
*/

void RE_HeadLightDisplay(boolean HeadState)
{
	lcd_goto(&lcd1, 0, 2);
	if (HeadState == 1)
	{
		lcd_chr(&lcd1, HEAD_SYMBPL);
	}
	else
	{
		lcd_chr(&lcd1, ' ');
	}
}

/**
*
* Runnable RE_LeftLightDisplay
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppLcd_set_Opr_LeftSet
*
*/

void RE_LeftLightDisplay(boolean LeftState)
{
	lcd_goto(&lcd1, 0, 0);
	if (LeftState == 1)
	{
		lcd_chr(&lcd1, '<');
	}
	else
	{
		lcd_chr(&lcd1, ' ');
	}
}

/**
*
* Runnable RE_RightLightDisplay
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppLcd_set_Opr_RightSet
*
*/

void RE_RightLightDisplay(boolean RightState)
{
	lcd_goto(&lcd1, 0, 19);
	if (RightState == 1)
	{
		lcd_chr(&lcd1, '>');
	}
	else
	{
		lcd_chr(&lcd1, ' ');
	}
}

/**
*
* Runnable RE_WiperDisplay
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppLcd_set_Opr_WiperSet
*
*/

void RE_WiperDisplay(boolean WiperState)
{
	lcd_goto(&lcd1, 0, 17);
	if (WiperState == 1)
	{
		lcd_chr(&lcd1, 0x02);
	}
	else
	{
		lcd_chr(&lcd1, ' ');
	}
}

void RE_BatteryLvlUpdate(Batterylvl_t* Batterylvl)
{
	static uint32 Battval_St;
	Battval_St = *Batterylvl;
	
	if (Battval_St < 10)
	{
		lcd_str(&lcd1, 3, 1,"  ");
	}
	else if (Battval_St < 100)
	{
		lcd_str(&lcd1, 3, 2," ");
	}
	else
	{
		
	}
	lcd_num(&lcd1, 3, 0,&Battval_St);
}


void RE_TemperatureUpdate(Temperature_t* Temperture)
{
	static uint32 Temperture_St;
	Temperture_St = *Temperture;
	
	
	lcd_str(&lcd1, 3, 16,"  ");
	
	lcd_num(&lcd1, 3, 16,&Temperture_St);
}



void RE_CvtDisplay(uint8 Cvt_val)
{
	lcd_goto(&lcd1, 3, 10);
	
	switch(Cvt_val)
	{
		case 0:
		{
			lcd_chr(&lcd1, 'D');
			break;
		}
		case 1:
		{
			lcd_chr(&lcd1, 'N');
			break;
		}
		case 2:
		{
			lcd_chr(&lcd1, 'R');
			break;
		}
		case 3:
		{
			lcd_chr(&lcd1, 'P');
			break;
		}
	}
	
	
}


void RE_RpmUpdate(uint32* N_rpm)
{
	uint8 col;
	if (*N_rpm < 100)
	{
		lcd_str(&lcd1, 1, 0,"  ");
		col = 2;
	}
	else if (*N_rpm < 1000)
	{
		lcd_str(&lcd1, 1, 0," ");
		col = 1;
	}
	else
	{
		col = 0;
	}
	
	lcd_num(&lcd1, 1, col, N_rpm);
	lcd_goto(&lcd1, 1, 4);
	if (*N_rpm > 0)
	{
		if (Flag_RpmSymbol == 0)
		{
			Flag_RpmSymbol = 1;
			lcd_chr(&lcd1, RPM_SYMBPL);
		}
		else
		{
			Flag_RpmSymbol = 0;
			lcd_chr(&lcd1, RPM2_SYMBPL);
		}
	}
	else
	{
		lcd_chr(&lcd1, RPM_SYMBPL);
	}
}


void RE_KMH_Update(uint32* KMH_Ref)
{
	uint8 col;
	if (*KMH_Ref < 10)
	{
		lcd_str(&lcd1, 2, 5,"  ");
		col = 7;
	}
	else if (*KMH_Ref < 100)
	{
		lcd_str(&lcd1, 2, 5," ");
		col = 6;
	}
	else
	{
		col = 5;
	}
	
	lcd_num(&lcd1, 2, col, KMH_Ref);
}

void RE_Screen_init()
{
	lcd_goto(&lcd1, 3, 3);
	lcd_chr(&lcd1, 0x00);
	
	//Celsius
	lcd_goto(&lcd1, 3, 18);
	lcd_chr(&lcd1, 0x03);
	lcd_chr(&lcd1, 'C');

	//Clock
	lcd_goto(&lcd1, 1, 14);
	lcd_chr(&lcd1, 0x04);

/*	// Ultra Sonic Wanning
	lcd_goto(&lcd1, 0, 8);
	lcd_chr(&lcd1, '!');
	lcd_goto(&lcd1, 0, 12);
	lcd_chr(&lcd1, '!');
*/
	// Km
	lcd_str(&lcd1, 2, 9, "KM/Hr");

	//Gear
	lcd_str(&lcd1, 3, 10, "N");
	
	lcd_goto(&lcd1, 1, 4);
	lcd_chr(&lcd1, 0x05);
	/*
	//Rpm
	lcd_goto(&lcd1, 1, 4);
	lcd_chr(&lcd1, 0x05);
	lcd_str(&lcd1, 1, 0, "3200");
	*/
}
