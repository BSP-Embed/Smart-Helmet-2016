#ifndef _APP_H
#define _APP_H

/* Main settings */

/********** GPS & GSM MUX CONFIGURATION ***********/
#define GSM_GPS_DDR				DDRC
#define GSM_GPS_PORT			PORTC
#define GSM_GPS_PIN				PC3

/******** MAIN CONFIGURATION ENDS ****************/

/* LCD CONFIGURATION */
#define LCD_DDR           	   		DDRB 
#define LCD_DATA_PORT          		PORTB
#define LCD_ENABLE_PIN        		PB3 
#define LCD_REGISTER_SELECT_PIN     PB2
#define DISPLAY_INIT				1
#define LCD_NSCRL					1
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			10

/******** LCD CONFIGURATION ENDS ****************/

/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/

/* LED: CONFIGURATION */

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/

/* GSM: CONFIGURATION */

#define MSG_START					""
#define MSG_END						". Automated SMS By: Smart Helmet."

/******** ADC CONFIGURATION ENDS ****************/
#define REF_VOL_256


/******** EEPROM CONFIGURATION ****************/
#define EEPROM_DISPLAY		0

/******** MOTOR CONFIGURATION *****************/
#define MOTOR_DDR				DDRC
#define MOTOR_PORT				PORTC
#define MOT_ANODE_PIN			PC5
#define MOT_CATHODE_PIN			PC4

#endif
