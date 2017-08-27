
/*======================================================================*/
/*																		*/
/*								KEYLIB.H								*/
/*																		*/
/*======================================================================*/

#ifndef KEYLIB_H
#define KEYLIB_H

#ifdef __cplusplus
extern "C" {
#endif


extern unsigned char ucKeyCnt;


/*
Get a null-terminated number string by keypad
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		MaxInputCnt
			maximum input count (1 up to 64)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				CLEAR: clear the last character
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated number string
*/
extern void KEY_InputNoString(char YPos, char XPos, char MaxInputCnt, char InputKey, char *str, char num_lang);

/*
Get a number by keypad
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		InputKey
			inputted key value
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a number character
*/
extern void KEY_InputOneNo(char YPos, char XPos, char InputKey, char *str, char num_lang);

/*
Get a null-terminated amount string with comma and dot by keypad
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		MaxInputCnt
			maximum input count (1 up to 12)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				*    : add double zeroes in str and display it on LCD
				#    : add triple zeroes in str and display it on LCD
				CLEAR: clear the last character
		currency_exp
			currency expoenet (0 up to 2)
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated amount string
		comma_dot_str
			pointer of a null-terminated amount string with comma and dot
*/
extern void KEY_InputAmount(char YPos, char XPos, char MaxInputCnt, char InputKey, char *str, char *comma_dot_str, unsigned char currency_exp, char num_lang);

/*
Convert a null-terminated number string to a null-terminated number string with comma and dot
	Input
		src
			pointer of a null-terminated number string
		currency_exp
			currency expoenet (0 up to 2)
	
	Output
		dst
			a null-terminated number string with comma and dot
	
	Return value
		the length of a null-terminated number string with comma and dot
*/
extern int KEY_InsertCommaAndDot(char *dst, char *src, unsigned char currency_exp);

/*
Get a null-terminated password string by keypad
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		MaxInputCnt
			maximum input count (1 up to 16)
		InputKey
			inputted key value
				0-9  : add that number in str and display '*' on LCD
				CLEAR: clear the last character
	
	Output
		str
			pointer of a null-terminated number string
*/
extern void KEY_InputPassWord(char YPos, char XPos, char MaxInputCnt, char InputKey, char *str);

/*
Get a null-terminated Christian YYYYMMDDhhmmss string by keypad
If you input year less than 1900, this function does not accept it
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				CLEAR: clear the last character
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated Christian YYYYMMDDhhmmss string
*/
extern void KEY_InputChristianDateTime(char YPos, char XPos, char InputKey, char *str, char num_lang);

/*
Get a null-terminated Christian YYYYMMDD string by keypad
If you input year less than 1900, this function does not accept it
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				CLEAR: clear the last character
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated Christian YYYYMMDD string
*/
extern void KEY_InputChristianDate(char YPos, char XPos, char InputKey, char *str, char num_lang);

/*
Get a null-terminated Iranian YYYYMMDDhhmmss string by keypad
If you input year less than 1300, this function does not accept it
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				CLEAR: clear the last character
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated Iranian YYYYMMDDhhmmss string
*/
extern void KEY_InputIranianDateTime(char YPos, char XPos, char InputKey, char *str, char num_lang);

/*
Get a null-terminated Iranian YYYYMMDD string by keypad
If you input year less than 1300, this function does not accept it
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				CLEAR: clear the last character
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated Iranian YYYYMMDD string
*/
extern void KEY_InputIranianDate(char YPos, char XPos, char InputKey, char *str, char num_lang);

/*
Get a null-terminated hhmmss string by keypad
	Input
		YPos
			display line number (0 up to 3)
		XPos
			start position (0 up to 15)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				CLEAR: clear the last character
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated hhmmss string
*/
extern void KEY_InputTime(char YPos, char XPos, char InputKey, char *str, char num_lang);

/*
Get a null-terminated IP address string
	Input
		YPos
			display line number (0 up to 3)
		InputKey
			inputted key value
				0-9  : add that number in str and display it on LCD
				*    : add a dot in str and display it on LCD
				CLEAR: clear the last character
		num_lang
			display language number
				0: English
				1: Farsi
	
	Output
		str
			pointer of a null-terminated IP address string
*/
extern void KEY_InputIPAddress(char YPos, char InputKey, char *str, char num_lang);

/*
Check the inputted a null-terminated IP address string is correct or not
	Input
		str
			pointer of a null-terminated IP address string
	
	Return
		 0: No error
		-1: Length of a null terminated IP address string error
		-2: Dot size error
		-3: Digit size error
		-4: Address of digit error
*/
extern int KEY_CheckIPAddress(char *str);


#ifdef __cplusplus
}
#endif

#endif	/* KEYLIB_H */

/* */
