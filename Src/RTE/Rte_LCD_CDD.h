/*
 * Rte_LCD_CDD.h
 *
 * Created: 8/26/2020 9:46:21 AM
 *  Author: ebrah
 */ 


#ifndef RTE_LCD_CDD_H_
#define RTE_LCD_CDD_H_
#include "Rte_Type.h"


/* Runnables Prototype Declaration */
void RE_HazardLightDisplay (boolean HazardState);
void RE_HeadLightDisplay (boolean HeadState);
void RE_LeftLightDisplay (boolean LeftState);
void RE_RightLightDisplay (boolean RightLightState);
void RE_WiperDisplay(boolean WiperState);

#endif /* RTE_LCD_CDD_H_ */