#include "main.h"

struct  {
	volatile int8u Meas:1;
	volatile int8u alcohol:1;
	volatile int8u sw:1;
	volatile int8u vibr:1;
}Flags;

extern int8u lcdptr;

int main(void)
{
	init();
	
	Flags.Meas = 0;
	Flags.sw = FALSE;
	Flags.alcohol = FALSE;
	Flags.vibr = FALSE;
	
	
	while (TRUE) {

		sleep();
		
		if (Flags.Meas == TRUE) {
			
			if (!(SENS_PPIN & _BV(ALCOHOL_PIN))) {
				if (Flags.alcohol == FALSE) {
					Flags.alcohol = TRUE;
					beep(1,150);
					sendRF(4);
					
				}
			} else 
				Flags.alcohol = FALSE;
			
			if (!(SENS_PPIN & _BV(SW_PIN))) {
				if (Flags.sw == TRUE) {
					Flags.sw = FALSE;
					beep(2,100);
					sendRF(1);
					
				}
			} else {
				if (Flags.sw == FALSE) {
					beep(3,75);
					sendRF(2);
					Flags.sw = TRUE;
				}
			}
			
			if (Flags.vibr == TRUE) {
					Flags.vibr = FALSE;
					beep(4,50);
					sendRF(3);
					
			}
							
			Flags.Meas = FALSE;
		}
	}
	return 0;
}


static void init(void)
{
	buzinit();
	ledinit();
	gpioinit();
	beep(2,100);
	tmr1init();
	EXTINTinit();
	sensinit();
	sei();
	StartTmr();
}
	
static void tmr1init(void)
{
	TCNT1H   = 0xD3;
	TCNT1L   = 0x00;
	TIMSK   |= _BV(TOIE1);			//ENABLE OVERFLOW INTERRUPT
	TCCR1A   = 0x00;					
	TCCR1B  |= _BV(CS10) | _BV(CS11); /* PRESCALAR BY 16 */
}

/* overflows at every 100msec */
ISR(TIMER1_OVF_vect) 
{ 
	static int8u i,j;

	TCNT1H = 0xD3;
	TCNT1L = 0x00;
	
	if (Flags.Meas == FALSE && ++j >= 10) {
		Flags.Meas = TRUE;
		j = 0;
	}
	
	if (++i >= 50) 
		 i = 0;
	
	switch(i) {
		case 0: case 2: ledon(); break;
		case 1: case 3: ledoff(); break;
	} 
}
static void EXTINTinit(void)
{
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);

	GICR |= _BV(INT0);			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01);		//FALLING EDGE INTERRUPT

}
ISR(INT0_vect)
{
	Flags.vibr = TRUE;
	GICR |= _BV(INT0);
}
static void gpioinit(void)
{
	SENS_DDR &= 0XF8;
	SENS_PORT |= 0x07;
	
	RF_DATA_DDR = 0XFF;
	RF_DATA_PORT = 0X10;		/* Enable HIGH */
}

static void sendRF(int8u x)
{
	RF_DATA_PORT = (RF_DATA_PORT & 0XF0) | x ;
	RF_DATA_PORT &= ~_BV(RF_EN_PIN);
	dlyms(1000);
	RF_DATA_PORT |= _BV(RF_EN_PIN);
}
static void sensinit(void)
{
	dlyms(5000);
	beep(1,100);
	while (!(SENS_PPIN & _BV(ALCOHOL_PIN))){
		beep(1,50);
		dlyms(500);
	}
	beep(1,500);
}