
/*======================================================================*/
/*																		*/
/*								PRINT.H									*/
/*																		*/
/*======================================================================*/

#define PRT_BYTES_PER_LINE					48		// Bytes per line: PRT_BYTES_PER_LINE*8=384 pixels per line
#define PRT_CHARACTERS_PER_LINE				32		// Charaters per line
#define PRT_LINES_PER_PAGE					36		// Lines per page
#define PRT_MAX_LINES_PER_PAGE				150		// Maximum lines per page[up to 150]: depends on Application

#define PRT_LINE_SPACE						0		// Line space gap[up to 15]: depends on Application
#define PRT_PAPER_FORM_FEED_LINE			6   	// 6 lines


/*
Bit information for Printing attribute buffer data  

bit 7 6 5 4 3 2 1 0 
    | | | |
    | | | +-------------- under line required
    | |	+---------------- double width
    | +------------------ graphics prinitng required
    +-------------------- line space adjust required 

0x00=normal, 0x10=under line, 0x20=double width
*/
#define PRT_NORMAL_MODE						0x00	// normal
#define PRT_UNDER_LINE_MODE					0x10	// under line required
#define PRT_DOUBLE_WIDTH_MODE				0x20	// double width
#define PRT_GRAPHICS_MODE					0x40	// graphics prinitng required

#define PRT_SIGN_MINUS_MODE					-1		// minus sign
#define PRT_SIGN_NO_MODE					0		// no sign
#define PRT_SIGN_PLUS_MODE					1		// plus sign

#define PRT_FINISH_TIMEOUT					100		// 1 sec
#define PRT_TIMEOUT							1000	// 10 sec
#define PRT_AUTO_SECOND_RECEIPT_TIMEOUT		500		// 5 sec


typedef struct {
	U08 uErrorMsgNo;				// Number of Error Message
	U16 usErrorMsgIndex[2];			// Index of Error Message
} _st_PrintErrorMsg_;


const _st_PrintErrorMsg_ PrintErrorMsg[52];

extern unsigned short usPrintStep;
extern unsigned short usPrint10MSTimer;
extern unsigned short usPrintingFinish10MSTimer;
extern unsigned short usPrintAutoSecondReceipt10MSTimer;
extern unsigned char ucPrintReceiptNo;
extern unsigned char ucPRTDensity;
extern unsigned char ucPrintError;
extern unsigned char ucPrintPrePrintingAreaFlag;			// Print Pre-printing Area Flag for printing of pre-printing area


// Print Task
extern void PrintTask(void);

/*
Detect Paper
 	Output
		0: Detect no paper
		1: Detect paper
*/
extern BOOL DetectPaper(void);

// Initialize Printer Parameter
extern void InitializePrinterParameter(void);

// Set Paper Form Feed
extern void PrintSetFF(int line, int form_feed_line);

// Build Print One Line Data
extern void BuildPrintLine(int line, char *item, int item_len, char *msg, int msg_len, char attr, char justify_mode, char lang);

// Build Print POS Information Report
extern void BuildPrintPOSInfoReport(void);

// Build Print Transaction Receipt
extern void BuildPrintTrxnReceipt(_st_TrxnLog_ *trxn_log);

// Build Print Reversal Receipt
extern void BuildPrintReversalReceipt(void);

// Build Print Unsuccessful Reversal Receipt
extern void BuildPrintUnsuccessfulReversalReceipt(void);

// Build Print Transactions Report
extern void BuildPrintTrxnsReport(void);

// Build Reprint Buy with external printer
extern void BuildReprintBuyWithExternalPrinter(_st_TrxnLog_ *trxn_log);

// Build Reprint Bill Payment with external printer
extern void BuildReprintBillPaymentWithExternalPrinter(_st_TrxnLog_ *trxn_log);

extern int PrintCardSystem(int line);
extern int PrintPaymasterLogo(int line);
extern int PrintApplicationVersion(int line);
extern int PrintStoreName(int line);
extern int PrintMultiMerchantStoreName(int line, _st_TrxnLog_ *trxn_log);
extern int PrintDateAndTime(int line, unsigned char *date, unsigned char *time);
extern int PrintBuyTrxnName(int line, _st_TrxnLog_ *trxn_log);
extern int PrintMerchantID(int line, char *merchant_id);
extern int PrintTerminalID(int line, char *terminal_id);
extern int PrintPOSSerialNo(int line);
extern int PrintPAN(int line, char *track2data, unsigned short len);
extern int PrintApprovalNo(int line, _st_TrxnLog_ *trxn_log);
extern int PrintReferenceNo(int line, _st_TrxnLog_ *trxn_log);
extern int PrintCustomerID(int line, _st_TrxnLog_ *trxn_log);
extern int PrintTraceNo(int line, _st_TrxnLog_ *trxn_log);
extern int PrintAmount(int line, _st_TrxnLog_ *trxn_log);
extern int PrintBalance(int line, _st_TrxnLog_ *trxn_log);
extern int PrintBillPaymentContents(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log);
extern int PrintSIMChargeContents(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log);
extern int PrintStoreAdvertisement(int line);
extern int PrintTotal(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log);
extern int PrintAllStars(int line);
extern int PrintAllDashes(int line);
extern int PrintAllEquals(int line);

#ifdef USER_DEBUG
	extern void OutputReceiptData(int line);
#endif

/* */
