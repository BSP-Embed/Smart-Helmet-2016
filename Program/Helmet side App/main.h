#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define INTDDR					DDRD
#define INTPORT					PORTD
#define INT0_PIN				PD2
#define INT1_PIN				PD3


#define SENS_DDR				DDRB
#define SENS_PORT				PORTB
#define SENS_PPIN				PINB
#define ALCOHOL_PIN				PB0
#define VIBR_PIN				PB2
#define SW_PIN					PB1


#define RF_DATA_DDR				DDRA
#define RF_DATA_PORT			PORTA
#define RF_DATA_PIN				PINA
#define RF_EN_PIN				PA4


//DEFINE CONSTANT


//DEFINE MACROS
#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)
							
#define sleep()				do {								\
							 set_sleep_mode(SLEEP_MODE_IDLE);	\
							 sleep_mode();						\
							} while (0);						\
							
							
//FUNCTION PROTOTYPES
static void		 init		(void);
static void 	tmr1init	(void);
static void		gpioinit	(void);
static void		sendRF		(int8u x);
static void		sensinit	(void);
static void		EXTINTinit	(void);
#endif

