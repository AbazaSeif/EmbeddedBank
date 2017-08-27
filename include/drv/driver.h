
/*======================================================================*/
/*																		*/
/*								DRIVER.H								*/
/*																		*/
/*======================================================================*/

/*-----------------------------------------------------------------------
	1. LCD display
-----------------------------------------------------------------------*/
extern char DSPBUF0[16];    // LCD 1'st Dispay buffer
extern char DSPBUF1[16];    // 2'nd
extern char DSPBUF2[16];    // 3rd
extern char DSPBUF3[16];    // 4th
extern char FONTBUF[32];	// for FONT_LOAD function

extern void LCD_ON(void);
//  0 <----------------------> 63
//    light                    dark level
extern void LCD_CONT(int value);
extern void BACK_ONOFF(int on_off);		// 1:on, 0:off
extern void LCD_DISPLAY(char cmd, char, char, char);
extern void GRA_LOAD(char *address, char start_line, char line_count);
extern void GRADATA_LOAD(char *address, char x_position, char y_position, char line_dot_count);
extern void LCD_BLINKING(char cmd, char, char, char);
extern void FONT_LOAD(char line_number, char position, char single_double, char front_back);

extern void ICON_DISPLAY(char icon_data);
extern void ICON_CLOCK_DISPLAY(char *clock_data);
extern void CLEAR_ICON_CLOCK(void);

extern void INITLCD(void);

extern void GRAMOVE_ON(void);
extern void GRAMOVE_OFF(void);
extern char GRA_MOVE;


/*-----------------------------------------------------------------------
	2. Free running TIMER and Time delay
-----------------------------------------------------------------------*/
extern unsigned int TIME_BASE0;		// 1ms based free running increment timer (lower 16 bits working)
extern unsigned int TIME_BASE1;		// 1ms based free running increment timer (lower 16 bits working)
extern unsigned int MODEMTINC;		// 1ms based free running increment timer (lower 16 bits working)
extern unsigned int LONGTIMER;		// 1ms based free running increment timer (32 bits working)
extern unsigned int MON_TIME;		// 1ms based free running decrement timer (lower 16 bits working)
extern unsigned int MODEMTDEC;		// 1ms based free running decrement timer (lower 16 bits working)
extern unsigned int TIME_BASE10;	// 10ms based free running increment timer (lower 16 bits working)

extern int GET_1M_TIMER(void);		// 0x00000000 to 0x7fffffff ms
extern void DELAY_US(int us);		// 1 to 0xffffff us


/*-----------------------------------------------------------------------
	3. Multi-application
-----------------------------------------------------------------------*/
extern char FIND_APPLICATION(char app_number);		// z=application doesn't exist, nz=application exists
extern int SELECT_APPLICATION(char app_number);		// z=application doesn't exist
extern int SAVE_BOOT_APPLICATION(char app_number);	// 0x00=application doesn't exist, 0xff=success

extern void ENTER_RESET(void);


/*-----------------------------------------------------------------------
	4. Multitasking
-----------------------------------------------------------------------*/
extern char TASK_SEQ[32];		// for SET_TASK_PRIORITY_MODE function

extern void SET_MULTITASKING_USAGE(char use_or_not);	// 0:not used, 1:used multitasking routine
// input
//   0:32kbytes(default), 1:64kbytes
// output
//   zero:OK, none zero:input error
extern char SET_TASK_STACK_SIZE(char stack_size);
// input
//   allowed 5 to 200 (default:10ms)
// output
//   zero:OK, none zero:input error
extern char SET_TASK_CHANGE_TIME(char  ms);
// input
//   task_number
//     accept 1 to 15 (0:main task, 1 to 15:multitask)
//   function_name
//     pointer of fuction
// output
//   zero:OK to start task, none zero:input error
extern char TASK_START(char task_number, char *function_name);
// input
//   task_number
//     accept 1 to 15 (0:main task, 1 to 15:multitask)
// output
//   zero:OK to stop task, none zero:input error
extern char TASK_STOP(char task_number);
// input
//   accept 0 to 2
//     0:each task has same priority and perform task (default)
//     1:give higher priority(50%) to main routine
//     2:Use task sequence assignment table
// output
//   zero:OK, none zero:input error
extern char SET_TASK_PRIORITY_MODE(char mode);


/*-----------------------------------------------------------------------
	5. Keypad input
-----------------------------------------------------------------------*/
extern char KEYSCAN(void);			// 0xff:no new key input, 0x00-0x23:new key input
extern void SAVE_PRINT_KEY(char);	// 0x22(default), use value for paper forward key


/*-----------------------------------------------------------------------
	6. Printing service related function
-----------------------------------------------------------------------*/
extern char PRINTING_NEED;
extern char CHAR_FILL1[5];
extern char CHAR_BUFFER1[5][36][32];
// bit7:line space adjust required
// bit6:graphics printing required
// bit5:double width
// bit4:under line required
extern char ATTB_BUFFER1[5][36][32];

extern int PRINTER_WORKING(void);
extern void SET_FORMFEED(int);
extern void ASSIGN_GRAPHICS(char *, char);
extern void SET_PRINTING_PREFERENCE(char);
extern void SET_LINESPACE(int);
extern void SEEK_NO_PAPER(char);
extern int PAPER_READ(void);
extern int ONLINE_READ(void);
extern void MAKEONLINE(void);
extern void MAKEOFFLINE(void);
extern void PRINT_FROM_FIRST(void);
extern void DISABLE_PRINTER_PROTECTION(void);
extern void ENABLE_PRINTER_PROTECTION(void);


/*-----------------------------------------------------------------------
	7. Usage of font table for LCD display and printing
-----------------------------------------------------------------------*/
extern char LCDMODE;
extern char PRTMODE;

extern void USE_LCDFONT(char *font_addr, char mode);
extern void USE_LCDFONT_2B(char *font_addr, char mode);
extern void USE_PRTFONT(char *font_addr, char mode);
extern void USE_PRTFONT_2B(char *font_addr, char mode);
extern void SET_PRINTER_CURRENT_LIMIT(char mode);


/*-----------------------------------------------------------------------
	8. RS232 related driver function and PORT selection
-----------------------------------------------------------------------*/
//	bit0 - UNDER COM0 TRANSMIT  
//	bit1 - UNDER COM1 TRAMSMIT
//	bit2 - COM0 TRAMSMISSION FINISH 
//	bit3 - COM1 TRAMSMISSION FINISH
//	bit4 - UNDER COM2 TRANSMIT  
//	bit5 - UNDER COM3 TRAMSMIT
//	bit6 - COM2 TRAMSMISSION FINISH 
//	bit7 - COM3 TRAMSMISSION FINISH
//		EX: channel 0 transmittion
//			xxxxx0x1     	
//			channel 0 transmission finish
//			xxxxx1x0
//	You may check bit0 or 2 for TX action finished
extern char SCITX;
extern int COM0T_IPOINT, COM0T_MPOINT, COM0T_COUNT;
extern int COM0R_IPOINT, COM0R_MPOINT, COM0R_COUNT;
extern int COM1T_IPOINT, COM1T_MPOINT, COM1T_COUNT;
extern int COM1R_IPOINT, COM1R_MPOINT, COM1R_COUNT;
extern int COM2T_IPOINT, COM2T_MPOINT, COM2T_COUNT;
extern int COM2R_IPOINT, COM2R_MPOINT, COM2R_COUNT;
extern int COM3T_IPOINT, COM3T_MPOINT, COM3T_COUNT;
extern int COM3R_IPOINT, COM3R_MPOINT, COM3R_COUNT;
extern char COM0T_BUFFER[8192], COM0R_BUFFER[8192];
extern char COM1T_BUFFER[8192], COM1R_BUFFER[8192];
extern char COM2T_BUFFER[8192], COM2R_BUFFER[8192];
extern char COM3T_BUFFER[8192], COM3R_BUFFER[8192];

extern int SC_POINT;
extern unsigned char SC_INPUT[512], SC_OUTPUT[512];

//	Assign 8KBytes for communication TX & RX buffer size
//	- default: 2kbytes
//	- SET_BUFFER_SIZE_8K: 8kbytes
extern void SET_BUFFER_SIZE_8K(void);

// (for flex5000 series only)
extern void UART23_POWERON(void);
extern void UART2_RESETOUT(void);
extern void UART3_RESETOUT(void);

extern void SERIAL2_SEL(void);
extern void PINPAD_SEL(void);
extern void SCARD_SEL(void);
extern void AUX_SEL(void);

extern void RS232_SEL(void);
extern void HI_SEL(void);
extern void MODEM_SEL(void);
extern void SET_SERIAL_OUTPUT(int);
extern void SET_SERIAL_COMBO(int);

extern void RS232_SETUP(char channel, char baud, char parity, char stopbit);
extern void RS232_ENABLE(char channel, char enable_disable, char rx_tx);
extern void RS232_RX_COUNT_DEC(int channel);
extern int RS232_TX_STATUS(int channel);
extern char WRCOM0(char *str, int size);
extern char WRCOM1(char *str, int size);
extern char WRCOM2(char *str, int size);
extern char WRCOM3(char *str, int size);
extern char WRITE_COM0(char *str, int size);
extern char WRITE_COM1(char *str, int size);
extern char WRITE_COM2(char *str, int size);
extern char WRITE_COM3(char *str, int size);
extern char RDCOM0(void);
extern char RDCOM1(void);
extern char RDCOM2(void);
extern char RDCOM3(void);
extern char READ_COM0(void);
extern char READ_COM1(void);
extern char READ_COM2(void);
extern char READ_COM3(void);
extern void SET_TX_TIME_INTERVAL(int channel, int us, int, int);	// us:100 to 10000

extern void COM0_POINT_INIT(void);
extern void COM1_POINT_INIT(void);
extern void COM2_POINT_INIT(void);
extern void COM3_POINT_INIT(void);
extern void GEMRXCOUNT(void);
extern void COM1RXCOUNT(void);
extern void COM2RXCOUNT(void);
extern void COM3RXCOUNT(void);


/*-----------------------------------------------------------------------
	9. MS card reading(MSR)
-----------------------------------------------------------------------*/
extern char CARDRDB[112];	// TRACK_SETUP(0/2/3): Track 1 data, TRACK_SETUP(1): Track 3 data
extern char CARDRDB2[52];	// TRACK_SETUP(0/1/2/3): Track 2 data
extern char CARDRDB3[112];	// TRACK_SETUP(2/3): Track 3 data
extern int CARDNCOUNT;		// TRACK_SETUP(0/2/3): Track 1 count, TRACK_SETUP(1): Track 3 count
extern int CARDNCOUNT2;		// TRACK_SETUP(0/1/2/3): Track 2 count
extern int CARDNCOUNT3;		// TRACK_SETUP(2/3): Track 3 count

// 0 : Track 1 & 2 used (H/W - DEFAULT) 
// 1 : Track 2 & 3 H/W installed (option)
// 2 : Track 1&2&3 H/W installed (option)
// 3 : Track 1&2&3 H/W installed (option for JIS-II)
extern void TRACK_SETUP(int);
extern void CARD_ENABLE(void);
extern void CARD_DISABLE(void);
extern int CARD_READ(void);


/*-----------------------------------------------------------------------
	10. Real time clock(RTC)
-----------------------------------------------------------------------*/
extern int RTC_CLK_READ(void *clk_data);
extern void RTC_CLK_WRITE(void *clk_data);
extern void RTC_RAM_WRITE(void);
extern void RTC_RAM_READ(void);


/*-----------------------------------------------------------------------
	11. Flash ROM control function
-----------------------------------------------------------------------*/
extern int FLASH_SECTOR_ERASE(char *flash_ROM_physical_address);
extern char FLASH_WRITE(char *Flash_address, long Count, char * source_address);
extern int WRITE_APP_PROGRAM(long count, char *src_addr, char *des_addr, char code);


/*-----------------------------------------------------------------------
	12. Beep tone
-----------------------------------------------------------------------*/
extern void BEEP_TONE(char cmd, char);


/*-----------------------------------------------------------------------
	13. Modem control routine
-----------------------------------------------------------------------*/
extern char TELNUMBER[64];

extern void MODEM_RESET(void);


/*-----------------------------------------------------------------------
	14. Smart card driver
-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------
	15. Dual SIM selection
-----------------------------------------------------------------------*/
extern void SIM_SELECT(char sim_slot_no);	// 0 or 1


/*-----------------------------------------------------------------------
	16. Application software upgrade function
-----------------------------------------------------------------------*/
extern void SYSTEM_DOWNLOAD(void);


/*-----------------------------------------------------------------------
	17. Contactless card working related function(optional hardware)
-----------------------------------------------------------------------*/
extern void SET_CONTACTLESS_INTERFACE(char serial_parallel);
extern void CL_CARD_ENABLE(void);
extern void CL_CARD_DISABLE(void);
extern void WriteRawRC(unsigned char addr, unsigned char value);
extern unsigned char ReadRawRC(unsigned char addr);
extern void CONTACTLESS_CARD_ENABLE(void);
extern void CONTACTLESS_CARD_DISABLE(void);


/*-----------------------------------------------------------------------
	18. Power management driver function(for flex5000 series only)
-----------------------------------------------------------------------*/
extern char PWR_SAV_STS[16];

extern void READ_POWER_SAVING_STATUS(char cmd, char *outputbuf);
extern void CONTROL_POWER_SAVING_STATUS(char cmd, char data);
extern void ENTER_STANDBY(void);
extern void POWER_OFF(void);


/*-----------------------------------------------------------------------
	19. Miscellaneous function
-----------------------------------------------------------------------*/
extern int RANDOM_NUMBER[4];

extern void GET_TRUE_RANDOM_NUMBER(void);

// Get Production ID (serial number)
// 	Output
//	- meminput: pointer of production ID (16 bytes)
//	Return value
//	- 0: OK, -1: Error (Production ID is not found)
extern int GET_PROD_ID(char *meminput);

// Save Production ID (serial number)
// 	Input
//	- meminput: pointer of production ID (16 bytes)
//	Return value
//	- 0: OK, -1: Error (Production ID is already saved)
extern int SAVE_PROD_ID(char *meminput);

// Power on/off of FOMA module
//	Input
//	- power_on (0: power off, 1: power on)
//	Return value
//	- power on
//		0 to 3 (step on Foma data sheet)
//		0xff (finished)
//	- power off
//		0xfe to 0xfc (step on Foma data sheet)
//		0x00 (finished)
extern unsigned char FOMA_ONOFF(unsigned char power_on);

extern void GRAPOSITION240(unsigned char x_start, unsigned char y_start, unsigned char x_end, unsigned char y_end);

// *address -> font address
// mode -> 0 ( library에서 dot별로 grayscale value 0x3f( max.)를 write
// mode -> 1 ( memory 1byte가 32 grayscale 1 dot data ) 
// Grayscale ( 0 to 0x3f data )
// display dot count -> Number of dots to be display
extern void GRADATALOAD240(char *address, unsigned char mode, int display_dot_count);

// offset -> font data start offset
extern void GRADATALOAD240OFFSET(char *address, int offset, unsigned char mode, int display_dot_count);

extern int CryptoKeyLoad();

extern void ENTER_AFTER_KEYLOAD();

/* */
