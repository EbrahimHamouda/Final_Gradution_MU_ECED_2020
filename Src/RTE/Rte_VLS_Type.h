/**
 *
 * \brief Sprints AUTOSAR Master Class - SeatCtrlApp
 * \author Hassan Farahat
 *
 * For any inquiries: hassan.m.farahat@gmail.com
 *
 */

#ifndef RTE_VLS_TYPE_H
#define RTE_VLS_TYPE_H

#include "Rte_Type.h"

#define WIPER_MAX_UP_WORD     30
#define WIPER_MIN_DOWN_WORD   14 


typedef struct 
{
    boolean Isworking;
    uint8  Current_status;
} ObejctPortfile_t;


typedef struct 
{
    ObejctPortfile_t Hazard_State;
    ObejctPortfile_t Right_State;
    ObejctPortfile_t Left_State;
    ObejctPortfile_t Wiper_State;
} BlinkingObject_t;

typedef enum
{
    UP_WORD,
    DOWN_WORD
} WiperDirction_t;


#define RTE_
#endif