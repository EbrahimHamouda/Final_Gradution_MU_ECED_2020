
#ifndef RTE_TYPE_H
#define RTE_TYPE_H

#include "common.h"

typedef enum
{
	FORWARD_DIRCTION,
	BACKWARD_DIRCTION	
} MotorDirction_t;

typedef enum 
{
	GAS_BRAKE_OFF,
	GAS_IS_ON,
	BRAKE_ON
} RpmState_t;


typedef uint8 Batterylvl_t;
typedef uint8 Temperature_t;
typedef uint8 Humditity_t;
typedef uint8 MotorSpeed_t;
typedef uint8 ServoPosition_t;

typedef struct 
{
	uint16 Right_UltraSonic;
	uint16 Left_UltraSonic;
}UltraSonicDis_t;

typedef struct
{
	boolean HeadCtrl : 1;
	boolean HazardCtrl : 1;
	boolean LeftCtrl : 1;
	boolean RightCtrl : 1;
	boolean WiperCtrl : 1;
	boolean IgntionCtrl : 1;
	boolean GasCtrl : 1;
	boolean BrakeCtrl : 1;
	uint16 StreeingCtrl;
	uint16 CVTCtrl;
} ControlSgnls_t;

typedef struct
{
    boolean		Head_State;
    boolean		Hazard_State;
    boolean		Left_State;
    boolean		Right_State;
    boolean		Wiper_State;
    boolean		Brake_State;
	uint8	    CvtMood;
	uint8		Speed;
	uint8		BatteyVal;
	uint8		Temperature;
	boolean		RightUltraSonic_State;
	boolean		LeftUltraSonic_State;
	RpmState_t	Rpm_State;
} DisplaySgnls_t;

typedef struct 
{
	Batterylvl_t	Batterylvl;
	uint8 UltraSonicDisRight;
	uint8 UltraSonicDisLeft;
	Temperature_t 	Temperature;
	Humditity_t		Humditity;
} SensorData_t;


typedef struct
{
    boolean Brake_State;
    boolean Gas_State;
    uint8   Streeing_Angle;
} PowerTrainSgnls_t;


#define RTE_E_OK 0U
#define RTE_E_NOK 1U

#endif