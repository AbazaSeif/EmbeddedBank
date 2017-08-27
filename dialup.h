
/*======================================================================*/
/*																		*/
/*								DIALUP.H								*/
/*																		*/
/*======================================================================*/

// Dial-up modem
#define DIALUP_MODEM_COM_PORT						COM2	// Internal Serial Port

#define DIALUP_MAX_CMD_RETRY						3
#define DIALUP_MAX_CONNECT_RETRY					2
#define DIALUP_TRXN_MAX_LINE						8
#define DIALUP_NAK_MAX_RETRY						3
#define DIALUP_EOD_MAX_LINE							3
#define DIALUP_BLIST_MAX_LINE						3
#define DIALUP_TNMS_MAX_LINE						8
#define DIALUP_REDIALING_PAUSE_TIME					200		// 2 sec


// High Speed Modem
extern unsigned short usHiSpeedModemTaskStep;			// High speed modem task step
extern unsigned short usHiSpeedModem10MSMaxTimeout;		// High speed modem 10ms maximum timeout
extern unsigned short usHiSpeedModem10MSTimer;			// High speed modem 10ms timer
extern unsigned char ucHiSpeedModemCmdRetryCnt;			// High speed modem command retry counter
extern unsigned char ucHiSpeedModemDataSendFlag;		// High speed modem data sending flag
extern unsigned char ucHiSpeedModemTNMSDialTimeout;		// High speed modem TNMS dialing timeout
extern unsigned char ucHiSpeedModemMaxConnectCnt;		// High speed modem maximum connection counter
extern unsigned char ucHiSpeedModemConnectCnt;			// High speed modem connection counter
extern unsigned char ucHiSpeedModemConnectLine;			// High speed modem connection line
extern unsigned char ucRxNAKCnt;						// High speed modem Rx NAK counter
extern unsigned char ucTxNAKCnt;						// High speed modem Tx NAK counter


/* Open high speed modem */
extern void HiSpeedModemOpen(void);

/* Reset high speed modem */
extern void HiSpeedModemReset(void);

/*
Transmit data to RS232 port for high speed modem
	Input
		stream
			pointer of stream
		size
			the length of stream
*/
extern void HiSpeedModemWrite(char *stream, int size);

/* High speed modem task */
extern void HiSpeedModemTask(void);

/* BMI asynchronous protocol */
extern void HiSpeedAsync_Bank_Melli_Iran(void);

/* */
