
/*------------------------------------------------------------------------------
Author		: K.H LEE Bitel Co., Ltd.
File name	: TIMERLIB.H
Purpose		: Library of timer

Revision history
Revision No.	Date				Contents
R1.00			21/May/2005 		First revison
R1.01			24/October/2008 	Change functions name and add a function
------------------------------------------------------------------------------*/

#ifndef TIMERLIB_H
#define TIMERLIB_H

#ifdef __cplusplus
extern "C" {
#endif


/*
Get the value of 1 ms timer
	Return value
		the value of 1 ms timer (0-65535)
*/
extern unsigned short TIMER_Get1MSTimer(void);

/*
Get the elapsed time from ref1MS to current 1MS timer
	Input
		ref1MS: reference 1 ms timer (0-65535)
			maximum 65.535sec
	
	Return value
		maximum 65.535sec (0-65535)
*/
extern unsigned short TIMER_GetElapsed1MSTime(unsigned short ref1MS);

/*
Get the value of 10 ms timer
	Return value
		the value of 10 ms timer (0-65535)
*/
extern unsigned short TIMER_Get10MSTimer(void);

/*
Get the elapsed time from ref10MS to current 10MS timer
	Input
		ref10MS: reference 10 ms timer (0-65535)
			maximum 655.35sec
	
	Return value
		maximum 655.35sec (0-65535)
*/
extern unsigned short TIMER_GetElapsed10MSTime(unsigned short ref10MS);

/*
Get the value of 1 sec timer
	Return value
		the value of 1 sec timer (0-86399): 23Hoursx3600Seconds + 59Minutes*60Seconds + 59Seconds
*/
extern long TIMER_Get1SECTimer(void);

/*
Get the elapsed time from ref1SEC to current 1SEC timer
	Input
		ref1SEC: reference 1 sec timer (0-86399)
			maximum 86399sec
	
	Return value
		maximum 86399sec (0-86399)
*/
extern long TIMER_GetElapsed1SECTime(long ref1SEC);

/*
Wait until time_out_1ms is elpased
	Input
		time_out_1ms (0-65535)
			maximum 65.535sec
*/
extern void TIMER_Wait1MS(unsigned short time_out_1ms);

/*
Wait until any key is pressed or time_out_1ms is elapsed
	Input
		time_out_1ms (0-65535)
			maximum 65.535sec
	
	Return Value
		0xFF: No key is inputed until timeout, else: Inputed key value
*/
extern int TIMER_WaitKeyPress1MS(unsigned short time_out_1ms);


#ifdef __cplusplus
}
#endif

#endif	/* TIMERLIB_H */

/* */
