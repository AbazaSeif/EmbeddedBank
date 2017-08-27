
/*======================================================================*/
/*																		*/
/*								KEY.H									*/
/*																		*/
/*======================================================================*/

#define MIN_LCD_CONTRAST				15
#define MAX_LCD_CONTRAST				45

#define AUTO_INITIAL_TIMEOUT			2000	// 20 sec
#define AUTO_REVERSAL_TIMEOUT			2000	// 20 sec
#define REVERSAL_PRINT_TIMEOUT			30000	// 5 min


extern const unsigned short tbl_MainService[][48];

extern unsigned short usMainStatus;
extern unsigned short *pusServiceAddr;
extern unsigned short usAutoInitial10MSTimer;
extern unsigned short usAutoReversal10MSTimer;
extern unsigned short usReversalPrint10MSTimer;
extern short sVirtualKey;
extern short sTempKey;
extern char cXPos;
extern char cYPos;
extern char cMaxInputCnt;
extern char c65CommaAndDotString[65];
extern char c65TempKeyBuf[65];
extern char c65TempBuf[65];


extern void KeyTask(void);
extern void InputKeyService(int key);
extern void EnterKeyService(void);
extern void CancelKeyService(void);
extern void SetInitialStatus(void);
extern void InitializeGlobalVariables(void);
extern void ClearTempKeyBufAndStringCopy(char *str);
extern void MainStatusSetting(unsigned short Status, short ServiceTableNo, short DisplayMsgNo, char HighlightLine, char lang);
extern void ErrorDisplayAndGoInitialStatus(short DisplayMsgNo, char HighlightLine, char lang);
extern void ErrorDisplayAndGoErrorStatus(short DisplayMsgNo, char HighlightLine, char lang);
extern void DisplayTrxnTelNo(void);
extern void ResetTrxnTelNo(void);
extern void DisplayEODTelNo(void);
extern void ResetEODTelNo(void);
extern void DisplayBlackListTelNo(void);
extern void ResetBlackListTelNo(void);
extern void DisplayTMSTelNo(void);
extern void ResetTMSTelNo(void);
extern void DisplayHelpDeskTelNo(void);
extern void ResetHelpDeskTelNo(void);
extern int InitTrxnReqData();
extern int SetReversalReqData(char *pSTAN);

#ifdef USER_DEBUG
extern void DisplayLCDMsgOrPrinterMsgInDebugMode(void);
#endif

/* */
