#include "main.h"

int8u phnum[15];
int8u sbuf[100];

struct  {
	volatile int8u sw:1;
	volatile int8u Meas:1;
	volatile int8u HelmetOn:1;
	volatile int8u state:1
}Flags;

extern int8u lcdptr;

int main(void)
{
	init();
	
	Flags.sw = 0;
	Flags.Meas = 0;
	Flags.state = TRUE;

	while (TRUE) {

		sleep();
		 
		if (Flags.Meas == TRUE) {
			if (RF_DATA_PIN & _BV(RF_VD_PIN)) {
				beep(1,150);
				lcdclrr(1);
				switch ((RF_DATA_PIN & 0Xf0) >> 4) {
					case 1: lcdws(" Helmet Weared");
							GICR |= _BV(INT0);			//ENABLE EXTERNAL INTERRUPT
							MCUCR |= _BV(ISC01);		//FALLING EDGE INTERRUPT
							Flags.HelmetOn = TRUE;
							break;
					case 2: lcdws(" Helmet Removed");
							Flags.HelmetOn = FALSE;
							Flags.state = TRUE;
							GICR &=  ~_BV(INT0);		/* Disable Switch */
							MCUCR &= ~_BV(ISC01);
							motoff();
							beep(1,150);
							lcdclrr(1);
							lcdws(" Vehicle Stopped");
							break;
					case 3: lcdws("Vibration Occu'd");
							sendloc(0);
							break;
					case 4: lcdws("Alcohol Consumed");
							motoff();
							GICR &=  ~_BV(INT0);		/* Disable Switch */
							MCUCR &= ~_BV(ISC01);
							beep(1,500);
							lcdclr();
							lcdws("Vehicle Stopped");
							lcdr2();
							lcdws(" Reset to START");
							for(;;) {
								beep(1,50);
								dlyms(3000);
							}
							break;
				}
			}	
			Flags.Meas = FALSE;
		}
				
		if (Flags.sw && Flags.HelmetOn) {
			beep(1,100);
			if (Flags.state == TRUE) {
				Flags.state = FALSE;
				moton();
				lcdclrr(1);
				lcdws(" Vehicle Moving");
			} else {
				Flags.state = TRUE;
				motoff();
				lcdclrr(1);
				lcdws(" Vehicle Stopped");
			}
			Flags.sw = 0;
		}
			
	}
	return 0;
}


static void init(void)
{
	buzinit();
	ledinit();

	beep(2,100);
	lcdinit();
	motorinit();
	
	uartinit();
	EXTINTinit();
	GPSinit();
	GSMEn();
	GSMinit();
	tmr1init();
	disptitl();
	sei();
	StartTmr();
	beep(1,100);
	
}
static void EXTINTinit(void)
{
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);

	GICR |= _BV(INT0);			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01);		//FALLING EDGE INTERRUPT

}

static void disptitl(void)
{
	lcdclr();
	lcdws("  SMART HELMET");
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
ISR(INT0_vect) 
{ 
	Flags.sw = 1;
	GICR |= _BV(INT0);
}

static void gpioinit(void)
{
	RF_DATA_DDR &= 0X03;
	RF_DATA_PORT |= 0xFC;

}