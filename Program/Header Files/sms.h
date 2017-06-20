#ifndef SMS_H
#define SMS_H

//INCLUDE HEADER FILES
#include "includes.h"



#define GSMEn()				do {									\
								GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN); 	\
								dlyms(500);							\
							} while(0)

#define GPSEn()				do {									\
								GSM_GPS_PORT |= _BV(GSM_GPS_PIN);	\
								dlyms(500);							\
							} while(0)

//FUNCTION PROTOTYPE
void GPSinit	(void);
void sendloc	(int8u state);

#endif