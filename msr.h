
/*======================================================================*/
/*																		*/
/*									MSR.H								*/
/*																		*/
/*======================================================================*/

extern unsigned char ucMSRTrack;
extern char sz77Track1Data[77];
extern char sz27CardholderName[27];
extern char sz38Track2Data[38];
extern char sz20PAN[20];
extern char sz5ExpiryDate[5];
extern char sz4CardServiceCode[4];


extern void MSRTask(void);
extern void ClearAllMSRDataBuf(void);
extern void MSREnable(void);
extern void MSRDisable(void);
extern int MSRRead(void);

/* */
