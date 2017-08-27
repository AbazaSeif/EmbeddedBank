
/*------------------------------------------------------------------------------
Author		: K.H LEE Bitel Co., Ltd.
File name	: BEEPLIB.H
Purpose		: Control of key beep sound and event beep sound

Revision history
Revision No.	Date				Contents
R1.00			21/May/2005 		First revison
R1.01			24/October/2008 	Change functions name, modify a function
									and add a function
------------------------------------------------------------------------------*/

#ifndef BEEPLIB_H
#define BEEPLIB_H

#ifdef __cplusplus
extern "C" {
#endif


/* define the tone of beep */
#define KEY_TONE				0
#define OK_TONE					1
#define COMPLETION_TONE			2
#define ERROR_TONE				3
#define WARNING_TONE			7



/* Enable key beep sound */
extern void Beep_KeySoundEnable(void);

/* Disable key beep sound */
extern void Beep_KeySoundDisable(void);

/* Enable event beep sound */
extern void Beep_EventSoundEnable(void);

/* Disable event beep sound */
extern void Beep_EventSoundDisable(void);

/*
Beep event sound
	Input
		tone
			0-7
*/
extern void Beep_EventSound(char tone);


#ifdef __cplusplus
}
#endif

#endif	/* BEEPLIB_H */

/* */
