/*
 * Rte_TempHum.h
 *
 * Created: 9/17/2020 12:31:12 PM
 *  Author: ebrah
 */ 


#ifndef RTE_TEMPHUM_H_
#define RTE_TEMPHUM_H_

#include "Rte_Type.h"

Std_ReturnType Rte_Call_rpIoTempHumGet_Opr_GetVal(Temperature_t, Humditity_t);

void RE_TempHumGetVal();


#endif /* RTE_TEMPHUM_H_ */