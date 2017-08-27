
/*======================================================================*/
/*																		*/
/*								RS232.H									*/
/*																		*/
/*======================================================================*/

extern int iRS232RxCnt;						// RS232 Rx counter
extern int iRS232RxSize;						// RS232 Rx data size
extern unsigned short usRS232TaskStep;			// RS232 task step
extern unsigned short usRS23210MSMaxTimeout;	// RS232 10ms maximum timeout
extern unsigned short usRS23210MSTimer;		// RS232 10ms timer
extern unsigned char ucRS232RxBuf[8192];		// RS232 Rx data buffer


extern void RS232Task(void);
extern void RS232Open(void);
extern void RS232Close(void);

/* */
