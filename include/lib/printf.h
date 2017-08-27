
/*======================================================================*/
/*																		*/
/*								PRINTF.H								*/
/*																		*/
/*======================================================================*/

#ifndef PRINTF_H
#define PRINTF_H

#ifdef __cplusplus
extern "C" {
#endif


/* Output data to RS232 Port */
extern int Rprintf(const char *format, ...);

/* Open debug RS232 port */
extern void OpenDebugPort(char comport, char baudrate, char parity_data_bit, char stop_bit, unsigned char delay_bits);

/* Disable Debug Output to RS232 Port */
extern void DisableDebugOutput(void);

/*
Output debug data to RS232 Port
	Input
		name
			pointer of debug data name
		data
			pointer of debug data
		len
			the length of data
		mode
			0: hexadecimal, 1: hexadecimal and character
*/
extern void Debug_Output(char *name, char *data, int len, char mode);


#ifdef __cplusplus
}
#endif

#endif	/* PRINTF_H */

/* */
