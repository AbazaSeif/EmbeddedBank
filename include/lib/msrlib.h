
/*------------------------------------------------------------------------------
Author		: K.H LEE Bitel Co., Ltd.
File name	: MSRLIB.H
Purpose		: Get Track 1, 2 or 3 Data of Magnetic Stripe Card

Revision history

Revision No.	Date				Contents
R1.00			21/May/2005 		First revison

R1.01			24/October/2008 	Change functions name, modify functions and
									add functions

R1.02			04/May/2011			Fixed bug  of MSR_GetTrack3Data function
------------------------------------------------------------------------------*/

#ifndef MSRLIB_H
#define MSRLIB_H

#ifdef __cplusplus
extern "C" {
#endif


/*
Get Track 1 Data of Magnetic Stripe Card
	Output
		track1_data: pointer of a null-terminated string
			maximum 76 characters
		cardholder_name: pointer of a null-terminated string
			maximum 26 characters
	
	Return Value
		 0: OK
		-1: Start Sentinel Error
		-2: The length of track 1 data is zero
		-3: End Sentinel Error
*/
extern int MSR_GetTrack1Data(char track1_data[77], char cardholder_name[27]);

/*
Get Track 2 Data of Magnetic Stripe Card
	Output
		track2_data: pointer of a null-terminated string
			maximum 37 characters
		pan (Primary Account Number): pointer of a null-terminated string
			maximum 19 characters
		expiry_date: pointer of a null-terminated string
			4 characters (YYMM)
		svc_code: pointer of a null-terminated string
			maximum 3 characters (first digit = '2' or '6': IC card)
	
	Return Value
		 0: OK
		-1: Start Sentinel Error
		-2: The length of track 2 data is zero
		-3: End Sentinel Error
*/
extern int MSR_GetTrack2Data(char track2_data[38], char pan[20], char expiry_date[5], char svc_code[4]);

/*
Get Track 3 Data of Magnetic Stripe Card
	Output
		track3_data: pointer of a null-terminated string
			maximum 104 characters
	
	Return Value
		 0: OK
		-1: Start Sentinel Error
		-2: The length of track 3 data is zero
		-3: End Sentinel Error
*/
extern int MSR_GetTrack3Data(char track_data3[105]);

/*
Get Cardholder Name in Track 1 Data of Magnetic Stripe Card
	Input
		track1_data: pointer of a null-terminated string
			maximum 76 characters
	
	Output
		cardholder_name: pointer of a null-terminated string
			maximum 26 characters
	
	Return Value
		 0: OK
		-1: The length of track 1 data is zero
		-2: The length of track 1 data is over 76 characters
		-3: There is no cardholder name
*/
extern int MSR_GetCardholderName(char track1_data[77], char cardholder_name[27]);

/*
Get Card PAN in Track 2 Data of Magnetic Stripe Card
	Input
		track2_data: pointer of a null-terminated string
			maximum 37 characters
	
	Output
		pan (Primary Account Number): pointer of a null-terminated string
			maximum 19 characters
	
	Return Value
		 0: OK
		-1: The length of track 2 data is zero
		-2: The length of track 2 data is over 37 characters
		-3: There is no PAN
*/
extern int MSR_GetCardPAN(char track2_data[38], char pan[20]);

/*
Get Card Expirey Date in Track 2 Data of Magnetic Stripe Card
	Input
		track2_data: pointer of a null-terminated string
			maximum 37 characters
	
	Output
		expiry_date: pointer of a null-terminated string
			4 characters (YYMM)
	
	Return Value
		 0: OK
		-1: The length of track 2 data is zero
		-2: The length of track 2 data is over 37 characters
		-3: There is no expirey date
*/
extern int MSR_GetCardExpiryDate(char track2_data[38], char expiry_date[5]);

/*
Get Card Service Code in Track 2 Data of Magnetic Stripe Card
	Input
		track2_data: pointer of a null-terminated string
			maximum 37 characters
	
	Output
		svc_code: pointer of a null-terminated string
			maximum 3 characters (first digit = '2' or '6': IC card)
	
	Return Value
		 0: OK
		-1: The length of track 2 data is zero
		-2: The length of track 2 data is over 37 characters
		-3: There is no service code
*/
extern int MSR_GetCardServiceCode(char track2_data[38], char svc_code[4]);

/*
Check checksum of PAN with Luhn algorithm
	Input
		pan (Primary Account Number)
			pointer of string
		len
			length of pan (13 to 19)
	
	Return Value
		 0: OK
		-1: The length of PAN is less than 13 or greater than 19
		-2: The format of PAN data is incorrect
		-3: Checksum is incorrect
*/
extern int MSR_CheckLuhnCheckSum(char *pan, int len);

/* Clear All MSR Card Data Buffers */
extern void MSR_ClearAllCardDataBuffer(void);


#ifdef __cplusplus
}
#endif

#endif	/* MSRLIB_H */

/* */
