/*
* Rte_UltraSonic.h
*
* Created: 9/17/2020 12:35:10 PM
*  Author: ebrah
*/


#ifndef RTE_ULTRASONIC_H_
#define RTE_ULTRASONIC_H_
#include "Rte_Type.h"


Std_ReturnType Rte_Call_rpIoUltraSonicGet_Opr_Echo(uint8);
Std_ReturnType Rte_Call_rpIoUltraSonicGet_Opr_Trigger(uint8);


void RE_UltraSonicGetVal (UltraSonicDis_t* );
#endif /* RTE_ULTRASONIC_H_ */