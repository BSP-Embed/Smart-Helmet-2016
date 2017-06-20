
#include "motor.h"

void motorinit(void)
{
	MOTOR_DDR	|= _BV(MOT_ANODE_PIN) | _BV(MOT_CATHODE_PIN);
	MOTOR_PORT	&= ~(_BV(MOT_ANODE_PIN) | _BV(MOT_CATHODE_PIN));
}

