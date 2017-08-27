
/*======================================================================*/
/*																		*/
/*									MAIN.H								*/
/*																		*/
/*======================================================================*/

extern int iModelName;
extern unsigned char ucLangFlag;
extern unsigned char ucCurrencyExp;
extern char sz6BIOSVersion[6];
extern char sz17HWInfo[17];
extern char sz17ProgramVersion[17];
extern char sz17ProgramDate[17];
extern char sz17TMSSWVersion[17];
extern char sz17TRMModelName[17];
extern char sz9POSSetupInfoDate[9];
extern char sz5LCDDisplayProgramVersion[5];

extern int main(void);
#ifdef USER_DEBUG
	extern void Output_SystemInfomation(void);
#endif
#ifdef ERASE_DATA_ROM_OPTION
	extern void EraseDataROM(void);
#endif

/* */
