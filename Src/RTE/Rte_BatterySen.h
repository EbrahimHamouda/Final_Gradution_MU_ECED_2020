/*
 * Rte_BatterySen.h
 *
 * Created: 9/17/2020 12:32:49 PM
 *  Author: ebrah
 */ 


#ifndef RTE_BATTERYSEN_H_
#define RTE_BATTERYSEN_H_
#include "Rte_Type.h"


Std_ReturnType Rte_Call_rpIoBattGet_Opr_GetVal(Batterylvl_t);


void RE_BatteryGetVal(Batterylvl_t*);
#endif /* RTE_BATTERYSEN_H_ */