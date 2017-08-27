
/*------------------------------------------------------------------------------
Author		: K.H LEE Bitel Co., Ltd.
File name	: RTCLIB.H
Purpose		: Library of RTC

Revision history

Revision No.	Date				Contents
R1.00			21/May/2005 		First revison

R1.01			24/October/2008 	Change functions name and add a function

R1.02			23/March/2011 		Add RTC_GetTime function

R1.03			27/June/2011 		Fixed bug of RTC_CheckGregorianInputDateTime
									function
------------------------------------------------------------------------------*/

#ifndef RTCLIB_H
#define RTCLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "typedef.h"


#define GREGORIAN_CALENDAR		0
#define JALALI_CALENDAR			1


typedef struct {
	unsigned char CLKSEC;		/* second(00-59) */
	unsigned char CLKMIN;		/* minute(00-59) */
	unsigned char CLKHOUR;		/* hour(00-23) */
	unsigned char CLKDATE;		/* date(01-31) */
	unsigned char CLKMONTH;		/* month(01-12) */
	/* 1:Monday, 2:Tuesday, 3: Wednesday, 4: Thursday, 5: Friday, 6:Saturday, 7:Sunday */
	unsigned char CLKDAY;		/* day(01-07) */
	unsigned char CLKYEARL;		/* year: 00xx */
	unsigned char CLKYEARH;		/* year: xx00 */
} _tDATE_TIME;



/*
Get date and time from RTC
	Input
		dt
			pointer of a _tDATE_TIME structure
		mode
			0: the Gregorian calendar, else the Jalali(Moslem) calendar
	
	Return value
		1: RTC data is ok, 0: RTC data is abnormal
*/
extern BOOL RTC_GetDateTime(_tDATE_TIME *dt, char mode);

/*
Set date and time to RTC
	Input
		YYYYMMDDhhmmss
			pointer of a string
		mode
			0: the Gregorian calendar, else the Jalali(Moslem) calendar
	
	Return value
		1: OK, 0: Error
*/
extern BOOL RTC_SetDateTime(char *YYYYMMDDhhmmss, char mode);

/*
Check input date and time of the Gregorian calender
	Input
		YYYYMMDDhhmmss
			pointer of a string
	
	Return value
		1: OK, 0: Error
*/
extern BOOL RTC_CheckGregorianInputDateTime(char *YYYYMMDDhhmmss);

/*
Get a day of the week in the Gregorian calendar mode
	Input
		year
			year of the Gregorian calendar
		month
			month of the Gregorian calendar
		date
			date of the Gregorian calendar
	
	Return value
		1:Monday, 2:Tuesday, 3: Wednesday, 4: Thursday, 5: Friday, 6:Saturday, 7:Sunday
*/
extern int RTC_GetGregorianDay(unsigned short year, unsigned short month, unsigned short date);

/*
Get leap month of the Gregorian calendar
	Input
		year
			year of the Gregorian calendar
	
	Return value
		1: leap month, 0: not leap month
*/
extern BOOL RTC_GetGregorianLeapMonth(unsigned short year);

/*
Get big month of the Gregorian calendar
	Input
		month
			month of the Gregorian calendar
	
	Return value
		1: big month, 0: not big month
*/
extern BOOL RTC_GetGregorianBigMonth(unsigned short month);

/*
Get the Gregorian days from the first date of specific year
	Input
		dt
			pointer of a _tDATE_TIME structure
	
	Return value
		the Gregorian days from the first date of specific year
*/
extern unsigned short RTC_GetGregorianDays(_tDATE_TIME *dt);

/*
Get the system time
	Input
		dt
			pointer of a _tDATE_TIME structure
	
	Return Value
		Return the time in elapsed seconds. There is no error return. 
		A call to RTC_GetTime can fail, however, if the date passed to the function is: 
		- Before midnight, January 1, 1970. 
		- After 19:14:07, January 18, 2038, LTC. 
	
	Remarks
		The RTC_GetTime function returns the number of seconds elapsed since midnight
		(00:00:00), January 1, 1970, coordinated local time (LTC), according
		to the system clock.
*/
extern long RTC_GetTime(_tDATE_TIME *dt);

/*
Convert the Gregorian calendar to the Jalali(Moslem) calendar
	Input
		dt
			pointer of a _tDATE_TIME structure of the Gregorian calendar
	
	Output
		dt
			pointer of a _tDATE_TIME structure of the Jalali(Moslem) calendar
*/
extern void RTC_Gregorian2Jalali(_tDATE_TIME *dt);

/*
Convert the Jalali(Moslem) calendar to the Gregorian calendar
	Input
		dt
			pointer of a _tDATE_TIME structure of the Jalali(Moslem) calendar
	
	Output
		dt
			pointer of a _tDATE_TIME structure of the Gregorian calendar
*/
extern void RTC_Jalali2Gregorian(_tDATE_TIME *dt);


#ifdef __cplusplus
}
#endif

#endif	/* RTCLIB_H */

/* */
