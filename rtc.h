
/*======================================================================*/
/*																		*/
/*								RTC.H									*/
/*																		*/
/*======================================================================*/

//#include "extern.h"

#define DATETIME_DISPLAY_LINE			2


extern const char DAY_STR_TBL[7][10];


extern _tDATE_TIME RealTime;
extern unsigned short usLCDBackLightOn10MSTimer;
extern unsigned short usColonOn1MSTimer;
extern unsigned char ucTempMin;
extern unsigned char ucTempSec;
extern unsigned char ucDateTimeRefreshFlag;
extern unsigned char ucLCDBacklightOnFlag;
extern unsigned char ucCheckColonTimerFlag;


// RTC Task
extern void RTCTask(void);

// LCD Backlight On/Off Control
extern void LCDBacklightOnOffControl(unsigned short on_time);	// sec

// Display Date and Time at Initial Status
extern void DisplayDateTime(_tDATE_TIME *dt);

// Display YYYYMMDD at Set Date
extern void DisplayYYYYMMDD(_tDATE_TIME *dt, char mode);

// Display hhmmss at Set Time
extern void Displayhhmmss(_tDATE_TIME *dt);

// Initialize RTC date and time
extern void InitializeRTCDateTime(void);

// Set RTC date and time when power is turned on
extern void SetRTCDateTimeWhenPowerIsTurnedOn(void);

// Get seconds since 1970-01-01 00:00:00.
extern U32 GetULDateTime();

/* */
