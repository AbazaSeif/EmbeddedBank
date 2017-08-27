
/*======================================================================*/
/*																		*/
/*								HWTEST.H								*/
/*																		*/
/*======================================================================*/

extern const char DOWNLOAD_PORT_TBL[];
extern const char SERIAL2_PORT_TBL[];

extern int iModemTestOKCnt;
extern int iModemTestTotalCnt;
extern unsigned char ucModemTestFlag;


extern void MSRTest(void);
extern void ICCardTest(void);
extern void KeyTest_IC3100PE(void);
extern void KeyTest_IC5100P(void);
extern void LCDTest(void);
extern void LCDBacklightTest(void);
extern void LCDDotTest(void);
extern void LCDContrastTest(void);
extern void RS232Test(void);
extern void RTCTest(void);

/* */
