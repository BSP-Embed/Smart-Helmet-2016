#include "sms.h"

/*********** TESTING or RELEASE SETTINGS ***********/
/*comment below line for release*/

//#define TESTING

#ifdef TESTING
	#define PhNum	 "9980237552"
#else
	#define PhNum	 "9535500896"
#endif

const char *MSG[] = { "Your vehicle got accident"};

void GPSinit(void)
{ 
	GSM_GPS_DDR  |= _BV(GSM_GPS_PIN);
	GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN);
}

void sendloc(int8u state)
{
	int8u i;
	int8u lat[11];
	int8u lon[11];
	int8u gsmmsg[150];

	gsmmsg[0] = '\0';

	for (i = 0; i < 10; i++)
	lat[i] = lon[i] = '0';

	lat[10] = lon[10] = '\0';

	GPSEn();
	GPSgetloc(lat,lon);

	strcat(gsmmsg,MSG[state]);
	strcat(gsmmsg," at LAT:");
	strcat(gsmmsg,lat);
	strcat(gsmmsg," & LON: ");
	strcat(gsmmsg,lon);

	GSMEn();
	GSMsndmsg(PhNum, gsmmsg);
}