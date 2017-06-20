#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define INTDDR					DDRD
#define INTPORT					PORTD
#define INT0_PIN				PD2
#define INT1_PIN				PD3

#define RF_DATA_DDR				DDRD
#define RF_DATA_PORT			PORTD
#define RF_DATA_PIN				PIND
#define RF_VD_PIN				PD3

//DEFINE CONSTANT

#define LINE_FEED				0x0A


//DEFINE MACROS
#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)
							
#define sleep()				do {								\
							 set_sleep_mode(SLEEP_MODE_IDLE);	\
							 sleep_mode();						\
							} while (0);						\
							
							
//FUNCTION PROTOTYPES
static void		 init		(void);
static void 	 disptitl 	(void);
static void 	tmr1init	(void);
static void 	EXTINTinit	(void);
static int8u	checkmsg	(void);
static void		VehicLock	(void);
static void		VehicUnlock	(void);

#endif

