
/*------------------------------------------------------------------------------
Author	: K.H LEE Bitel Co., Ltd.
File	: TMSLIB.H
Purpose	: Terminal Management System (TMS) Library

Revision history
Rev. No.	Date			Contents
R1.00		21-May-2005 	First revison.
------------------------------------------------------------------------------*/

#ifndef TMSLIB_H
#define TMSLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "typedef.h"


extern long lTMS_PGMPARAMPgmUpgradeStartAddr;			// upgrading start address of program
extern long lTMS_PGMPARAMPgmTotalDataSize;				// total data size of program
extern long lTMS_PGMPARAMParamTotalDataSize;			// total data size of parameters
extern long lTMS_PGMPARAMReferenceNo;					// reference number of downloading program and parameters
extern int iTMS_ProcessStep;							// step of TMS processing
extern short sTMS_SectorDownloadDataSize;				// downloading data size of sector
extern short sTMS_PGMPARAMTotalSectorNo;				// total sector number of downloading program and parameters
extern short sTMS_PGMPARAMCurrentSectorNo;				// current sector number of downloading program and parameters
extern unsigned short usTMS_PGMPARAMTotalLRCData;		// total LRC of downloading program and parameters
extern short sTMS_PARAMTotalSectorNo;					// total sector number of downloading parameters
extern short sTMS_PARAMCurrentSectorNo;				// current sector number of downloading parameters
extern unsigned short usTMS_PARAMTotalLRCData;			// total LRC of downloading parameters
extern char sz65TMS_ErrorMsg[65];						// TMS error message



/*
TMS processing
	Input
		com_device
			0: Dial-up modem
			1: Ethernet
		com_port
			serial communication port for TMS
	
	Output
		*rx_buf
			received data from TMS server
	
	Return Codes
	   0: Polling
	   1: Received ENQ
	   2: Received first character
	   3: Received program (and parameter) downloading information
	   4: Received parameter downloading information
	   5: Received data packet
	   6: Received End of communication command
	  -1: Rx data LRC error
	  -2: Rx data packet LRC error
	  -3: Received Tx data LRC error code
	  -4: Received Command error code
	 -99: Received error message
	-999: "NO CARRIER"
*/
extern short TMS_Process(char com_device, char com_port, char *rx_buf);

/* Clear TMS variables */
extern void TMS_ClearBuf(void);

/*
Send resume program and/or parameter downloading command
	Input
		pgm_no
			program number (0 up to 99)
		country_code
			pointer of country code
		svc_company_code
			pointer of service company code
		terminal_maker_code
			pointer of terminal maker code
		model_name
			pointer of terminal model name
		serial_no
			pointer of terminal serial number
		merchant_id
			pointer of merchant identification
		sw_version
			pointer of terminal application version
		bios_version
			pointer of terminal BIOS version
		hw_info
			pointer of terminal hardware information
		download_addr
			pointer of downloading start address for application
		param_version
			pointer of terminal parameter version
		param_date
			pointer of terminal parameter version date
		reference_no
			reference number of application without parameters or application with parameters
		download_sector_no
			current downloading sector number of resume downloading for application
*/
extern void TMS_SendResumePgmParamDownload(char pgm_no,
											char *country_code,
											char *svc_company_code,
											char *terminal_maker_code,
											char *model_name,
											char *serial_no,
											char *merchant_id,
											char *sw_version,
											char *bios_version,
											char *hw_info,
											char *download_addr,
											char *param_version,
											char *param_date,
											long reference_no,
											short download_sector_no);

/* Send downloading start command */
extern void TMS_SendDownloadStart(void);

/*
Send ACK or NAK for downloading data
	Input
		sector_no
			current downloading sector number
		ack_nak
			ACK or NAK
*/
extern void TMS_SendDownloadDataAckNak(short sector_no, unsigned char ack_nak);

/*
Send ACK or NAK for end of downloading
	Input
		ack_nak
			ACK or NAK
*/
extern void TMS_SendDownloadEndAckNak(unsigned char ack_nak);

/*
Calculate downloaded ROM file LRC
	Input
		str
			pointer of string
		size
			the length of string
	
	Return Value
		value of calculated ROM file LRC
*/
extern unsigned short TMS_CalDownloadROMFileLRC(unsigned char *str, long size);

extern void SetTMSGprsModel(unsigned char model);

#ifdef __cplusplus
}
#endif

#endif	/* TMSLIB_H */

/* */
