#ifndef _MOTOR_H
#define _MOTOR_H

#include "includes.h"

#define moton()			MOTOR_PORT |= _BV(MOT_ANODE_PIN)
#define motoff()		MOTOR_PORT &= ~_BV(MOT_ANODE_PIN)

void motorinit(void);

#endif
