/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */
 
#ifndef RTE_DISPLAY_TYPE_H
#define RTE_DISPLAY_TYPE_H

#include "Rte_Type.h"

typedef struct 
{
    boolean Isworking;
    boolean Current_status;
} ObejctPortfile_t;


typedef struct 
{
    ObejctPortfile_t Hazard_State;
    ObejctPortfile_t Left_State;
    ObejctPortfile_t Right_State;
	ObejctPortfile_t Clock_state;
	ObejctPortfile_t Right_UltraSonic;
	ObejctPortfile_t Left_UltraSonic;
} BlinkingObject_t;


#define RTE_
#endif