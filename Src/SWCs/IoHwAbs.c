/**
*
* \file SWC_IoHwAbs_Template.c
* \brief Rte Component Template for AUTOSAR SWC: SWC_IoHwAbs
*
* \author Sprints AUTOSAR Authoring Tool (SAAT) v1.0.2
* Generated on 8/25/2020 11:23 AM
*
* For any inquiries: hassan.m.farahat@gmail.com
*
*/

#include "Rte_IoHwAbs.h"
#include "GPIO.h"
#include "ADC.h"
#include "pwm.h"
#include "ultraSonicSensor.h"
#include "DHT11.h"


/*****************************
*   INTERNAL CONSTANTS		 *
******************************/
#define MAX_STEERING_ANGLE 30
#define MIN_STEERING_ANGLE 15

#define MAX_MOTOR_POWER    255
#define MIN_MOTOR_POWER	   0

/*****************************
* INTERNAL STATIC VARIABLES *
******************************/
ServoPosition_t Steering_MotorPos = (MIN_STEERING_ANGLE+7);
MotorSpeed_t	Motor_Speed        =   MIN_MOTOR_POWER;
/**
*
* Runnable RE_IoChkUserControls
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoChkControls_Opr_ChkControls
*
*/

void RE_IoChkUserControls(ControlSgnls_t *Control_Signals)
{
	Control_Signals->HeadCtrl = Dio_ReadChannel(B7);
	Control_Signals->HazardCtrl = Dio_ReadChannel(B6);
	Control_Signals->RightCtrl = Dio_ReadChannel(B5);
	Control_Signals->LeftCtrl = Dio_ReadChannel(B4);
	Control_Signals->WiperCtrl = Dio_ReadChannel(B3);
	Control_Signals->IgntionCtrl = Dio_ReadChannel(B2);
	Control_Signals->GasCtrl = Dio_ReadChannel(B1);
	Control_Signals->BrakeCtrl = Dio_ReadChannel(B0);
	Control_Signals->StreeingCtrl = adc_read(CHANNEL0);
	Control_Signals->CVTCtrl = adc_read(CHANNEL1);
}

/**
*
* Runnable RE_HeadLed
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoSetLedsWiper_HeadLed_Set
*
*/

void RE_HeadLed(boolean HeadState)
{
	Dio_WriteChannel(B7, HeadState);
}


/**
*
* Runnable RE_HeadLed
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoSetLedsWiper_HeadLed_Set
*
*/

void RE_BrakeLed(boolean BrakeState)
{
	Dio_WriteChannel(B4, BrakeState);
}

/**
*
* Runnable RE_HazardLed
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoSetLedsWiper_HazardLed_Set
*
*/
void RE_HazardLed(boolean HazardState)
{
	RE_RightLed(HazardState);
	RE_LeftLed(HazardState);
}

/**
*
* Runnable RE_RightLed
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoSetLedsWiper_RightLed_Set
*
*/

void RE_RightLed(boolean RightState)
{
	Dio_WriteChannel(B6, RightState);
}

/**
*
* Runnable RE_LeftLed
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoSetLedsWiper_LeftLed_Set
*
*/

void RE_LeftLed(boolean LeftState)
{
	Dio_WriteChannel(B5, LeftState);
}

/**
*
* Runnable RE_WiperPoistion
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoSetLedsWiper_Wiper_PositionSet
*
*/
void RE_WiperPoistion(uint8 WiperPoistion)
{
	pwm_generate(B3, WiperPoistion); // init pos
}

/**
*
* Runnable RE_IoMainMotor_DirctionChange
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppMainMotorFun_Opr_IoMainMotor_plus
*
*/

void RE_IoMainMotor_DirctionChange(MotorDirction_t MotorDirction)
{
	if (MotorDirction == FORWARD_DIRCTION)
	{
		Dio_WriteChannel(C2,SET_VALUE_HIGH);
		Dio_WriteChannel(C3,SET_VALUE_LOW);
	}
	else
	{
		Dio_WriteChannel(C2,SET_VALUE_LOW);
		Dio_WriteChannel(C3,SET_VALUE_HIGH);
	}
}


/**
*
* Runnable RE_IoMainMotor_Plus
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppMainMotorFun_Opr_IoMainMotor_plus
*
*/

void RE_IoMainMotor_Plus(void)
{
	if (Motor_Speed < MAX_MOTOR_POWER )
	{
		if (Motor_Speed == 0)
		{
			pwm_init();
		}
		Motor_Speed++;
		pwm_generate(D4,Motor_Speed);
	}
	else
	{
		
	}
}

/**
*
* Runnable RE_IoMainMotor_Minus
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppMainMotorFun_Opr_IoMainMotor_Minus
*
*/

void RE_IoMainMotor_Minus(void)
{
	if (Motor_Speed > MIN_MOTOR_POWER )
	{
		Motor_Speed--;
		pwm_generate(D4,Motor_Speed);
	}
	else
	{
		pwm_stop(D4);
	}
}

/**
*
* Runnable RE_IoGetMainMotor_Speed
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppMainMotorFun_Opr_IoGetMainMotor_Speed
*
*/

void RE_IoGetMainMotor_Speed(MotorSpeed_t *MotorSpeed)
{
	Std_ReturnType status;
	*MotorSpeed =Motor_Speed;
}

/**
*
* Runnable RE_IoServoMotor_plus
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppServoMotorFun_Opr_IoServoMotorPlus
*
*/

Std_ReturnType RE_IoServoMotor_Set(ServoPosition_t Steering_MotorPos)
{
	pwm_generate(B3,Steering_MotorPos);
}


/**
*
* Runnable RE_IoGetServoMotor_Position
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppServoMotorFun_Opr_IoGetServoMotorPosition
*
*/

void RE_IoGetServoMotor_Position(ServoPosition_t *ServoPosition)
{
	*ServoPosition = Steering_MotorPos;
}


/**
*
* Runnable RE_BatteryGetVal
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoBattGet_Opr_GetVal
*
*/

void RE_IoBatteryGetVal (Batterylvl_t* IO_Batterylvl)
{
	Std_ReturnType status;
	uint16 Adc_val = adc_read(A0);
	*IO_Batterylvl = map(Adc_val,0,1024,0,100);

}

/**
*
* Runnable RE_IoTempHumGetVal
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_rpIoTempHumGet_Opr_GetVal
*
*/

void RE_IoTempHumGetVal (Temperature_t* IO_Temperature, Humditity_t* IO_Humidity)
{
	DHT11_RequestData();
	DHT11_GetResponse();
	DHT11_ReceiveData(&DHT11_1);
	*IO_Temperature = DHT11_1.I_Temp;
	*IO_Humidity = DHT11_1.I_RH;
}


/**
*
* Runnable RE_UltraSonic1
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoUltraSonic_Opr_Echo
*
*/

void RE_UltraSonic1 (uint8* UltraSonicRef)
{
	uint16 US_val= ultraSonic_Read(&ultrasnoic1);
	
	if (US_val > 255 )
	{
		*UltraSonicRef =255;
	}
	else
	{
		*UltraSonicRef = US_val;
	}
}


/**
*
* Runnable RE_UltraSonic2
*
* Triggered By:
*  - OperationInvokedEventImpl.OIE_ppIoUltraSonic_Opr_Trigger
*
*/

void RE_UltraSonic2 (uint8* UltraSonicRef)
{
	uint16 US_val= ultraSonic_Read(&ultrasnoic2);
	
	if (US_val > 255 )
	{
		*UltraSonicRef =255;
	}
	else
	{
		*UltraSonicRef = US_val;
	}
}

