
/*------------------------------------------------------------------------------
Author		: K.H LEE Bitel Co., Ltd.
File name	: COMMLIB.H
Purpose		: RS232 communication library

Revision history
Revision No.	Date				Contents
R1.00			21/May/2005 		First revison
R1.01			24/October/2008 	Change functions name
------------------------------------------------------------------------------*/

#ifndef COMMLIB_H
#define COMMLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "typedef.h"


/* define RS232 port number */
#define COM0				0
#define COM1				1
#define COM2				2
#define COM3				3

/* define RS232 enable or disable */
#define DISABLE				0
#define ENABLE				1

/* define RX and TX enable or disable */
#define RX_ENABLE			0
#define TX_ENABLE			1
#define TX_DISABLE			2

/* define Baud rate */
#define BPS1200				0
#define BPS2400				1
#define BPS4800				2
#define BPS9600				3
#define BPS19200			4
#define BPS38400			5
#define BPS57600			6
#define BPS115200			7

/* define Parity and Data bits */
#define NONE8BIT			0
#define EVEN7BIT			1
#define ODD7BIT				2
#define NONE7BIT			3

/* define Stop bits */
#define STOP1BIT			1
#define STOP2BIT			2

/* define control characters */
#define NUL					0x00	// null
#define SOH					0x01	// start of header
#define STX					0x02	// start of text
#define ETX					0x03	// end of text
#define EOT					0x04	// end of transmission
#define ENQ					0x05	// enquiry
#define ACK					0x06	// acknowledgement
#define BEL					0x07	// bell
#define BS					0x08	// backspace
#define HT					0x09	// horizontal tab
#define LF					0x0A	// line feed
#define VT					0x0B	// vertical tab
#define FF					0x0C	// form feed
#define CR					0x0D	// carriage return
#define SO					0x0E	// shift out
#define SI					0x0F	// shift in
#define DLE					0x10	// data link escape
#define XON					0x11	// transmit on  / device control 1 (DC1)
#define DC2					0x12	// device control 2
#define XOFF				0x13	// transmit off / device control 3 (DC3)
#define DC4					0x14	// device control 4
#define NAK					0x15	// negative acknowledgement
#define SYN					0x16	// synchronous idle
#define ETB					0x17	// end of transmission block
#define CAN					0x18	// cancel
#define EM					0x19	// end of medium
#define SUB					0x1A	// substitute
#define ESC					0x1B	// escape
#define FS					0x1C	// file separator (field separator)
#define GS					0x1D	// group separator
#define RS					0x1E	// record separator
#define US					0x1F	// unit separator


/*
Table of the baud rate
	0: 1200
	1: 2400
	2: 4800
	3: 9600
	4: 19200
	5: 38400
	6: 57600
	7: 115200
*/
extern const unsigned int BAUD_RATE_TABLE[8];



/*
Open RS232 port
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
		baudrate
			0: 1200, 1: 2400, 2: 4800, 3: 9600, 4: 19200, 5: 38400, 6: 57600, 7: 115200, else: 1200
		parity_data_bit
			0: 8 bits none parity, 1: 7 bits even parity, 2: 7 bits odd parity, 3: 7 bits none parity
		stop_bit
			1: 1 stop bit, 2: 2 stop bits
		delay_bits
			0 up to 100 bits
			if delay_bits is less than 1, don't delay after transmitting 1 byte.
			if delay_bits is greater than 100, delay_bit will be 100.
*/
extern void RS232_OpenPort(char port_no, char baudrate, char parity_data_bit, char stop_bit, unsigned char delay_bits);

/*
Clear RS232 pointer
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
*/
extern void RS232_ClearPointer(char port_no);

/*
Clear RS232 buffer
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
*/
extern void RS232_ClearBuffer(char port_no);

/*
Read 1 byte data from RS232 port
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
		
	Return Value
		received 1 byte data
*/
extern int RS232_Read(char port_no);

/*
Transmit data to RS232 port
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
		stream
			pointer of a string
		size
			length of a string (maximum 8192)
*/
extern void RS232_Write(char port_no, char *stream, int size);

/*
Check that data transmission is completed to RS232 port
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
		
	Return Value
		1: completed, 0: not completed
*/
extern BOOL RS232_CheckTxDone(char port_no);

/*
Wait until data transmission is completed to RS232 port
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
*/
extern void RS232_WaitTxDone(char port_no);

/*
Check that a data is received form RS232 port
	Input
		port_no
			0: COM0, 1: COM1, 2: COM2, 3: COM3
			
	Return Value
		1: received, 0: not received
*/
extern BOOL RS232_CheckRxInput(char port_no);


#ifdef __cplusplus
}
#endif

#endif	/* COMMLIB_H */

/* */
