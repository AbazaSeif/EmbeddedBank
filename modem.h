
/*======================================================================*/
/*																		*/
/*								MODEM.H									*/
/*																		*/
/*======================================================================*/

// define connection mode
#define NORMAL_CONNECTION					0
#define PRE_CONNECTION						1

// define modem type
#define DIAL_UP_MODEM						0
#define ETHERNET_MODEM						1
#define GSM_MODEM							2


extern const char DISCONNECT_TBL[];

#ifdef AUTO_MODEM_TEST
extern unsigned short usModemAutoTest10MSTimer;
#endif

// Common Variables
extern int iRxCnt;							// Rx counter
extern int iRxSize;							// Rx data size
extern int iTxSize;							// Tx data size
extern unsigned char ucReqDataReadyFlag;	// Request data ready flag
extern unsigned char ucReqDataTxFlag;		// Request data transmitted flag
extern unsigned char ucDisconnectCnt;		// Check disconnection counter
extern unsigned char ucTrxnRxBuf[8192];		// Transaction Rx data buffer
extern unsigned char ucTrxnTxBuf[8192];		// Transaction Tx data buffer
extern unsigned char ucRxBuf[8192];			// Rx data buffer
extern unsigned char ucTxBuf[8192];			// Tx data buffer
extern unsigned char ucRxTempBuf[8192];		// Rx temporary data buffer
extern unsigned char ucTxTempBuf[8192];		// Tx temporary data buffer


/* Modem task */
extern void ModemTask(void);

/*
Get Connection Conditions
	Input
 		com_device
 			0: dial-up Modem, 1: LAN, 2: GSM
 		trxn_mode
 			0: transaction mode, 1: EOD, 2: Request Black List, 3: TMS mode
 		check_paper (It is available when trxn_mode is 0)
 			0: Does not check paper, 1: Check paper
	
	return values
		-2: SIM Error
		-1: GSM module doesn't response
		 0: OK
		 1: No Terminal ID
		 2: No Merchant ID
		 3: No Transaction Telephone number
		 4: No EOD Telephone number
		 5: No Black List Telephone number
		 6: No TMS Telephone number
		 7: No Local IP address
		 8: No Subnet Mask
		 9: No Gateway
		10: No Local port number(0-65535)
		11: No Local Timeout(0-6000 sec)
		12: No Transaction Server IP address
		13: No Transaction Server port number(0-65535)
		14: No EOD Server IP address
		15: No EOD Server port number(0-65535)
		16: No Black List Server IP address
		17: No Black List Server port number(0-65535)
		18: No TMS Server IP address
		19: No TMS Server port number(0-65535)
		20: No Paper (except Reversal Transaction)
*/
extern int GetConnectionConditions(unsigned char com_device, int trxn_mode, int check_paper);

extern void DisplayConnectionErrorCondition(int err_condition);

extern void DisplayConnectionErrorConditionAndGotoInitialStatus(int err_condition);

extern BOOL GetTrxnMenuActiveStatus(void);

/*
Open modem
	Input
		pre_connect
			0: Normal connection, 1: Pre-connection
*/
extern void ModemOpen(char pre_connect);

/* Close modem */
extern void ModemClose(void);

/*
Check disconnection
	Input
		rxdata
			received data
	
	Return Value
		0: Not disconnected, 1: Disconnected
*/
extern BOOL CheckDisconnect(int rxdata);

/* Abnormal processing before transmission */
extern void AbnormalProcessingBeforeTx(void);

/* Abnormal processing after transmission */
extern void AbnormalProcessingAfterTx(void);

/* Online transaction result processing */
extern void OnlineTrxnResultProcessing(void);


/* */
