
/*======================================================================*/
/*																		*/
/*								LCDLIB.H								*/
/*																		*/
/*======================================================================*/

#ifndef LCDLIB_H
#define LCDLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#define ON						1	// LCD on
#define OFF						0	// LCD off

#define CURSOR_OFF				0	// cursor off
#define CURSOR_ON				1	// cursor on
#define CURBOX_ON				2	// highlight on
#define CURBOX_OFF				3	// highlight off

#define CURSOR_BOX				0	// box cursor
#define CURSOR_UNDERBAR			1	// under bar cursor
#define CURSOR_IBEAM			2	// I beam cursor

#define LEFT_JUSTIFIED			0
#define CENTER_JUSTIFIED		1
#define RIGHT_JUSTIFIED			2

#define LCD_LINE0				0
#define LCD_LINE1				1
#define LCD_LINE2				2
#define LCD_LINE3				3




/*
Blink cursor on LCD
	Input
		YPos
			line number (0 up to 3)
		XPos
			position (0 up to 15)
*/
extern void LCD_CursorOn(char YPos, char XPos);

/* Erase cursor on LCD */
extern void LCD_CursorOff(void);

/*
Highlight on n characters on LCD
	Input
		YPos
			line number (0 up to 3)
		XPos
			position (0 up to 15)
		count
			count of characters (1 up to 16)
*/
extern void LCD_HighlightOn(char YPos, char XPos, char count);

/*
Highlight off n characters on LCD
	Input
		YPos
			line number (0 up to 3)
		XPos
			position (0 up to 15)
		count
			count of characters (1 up to 16)
*/
extern void LCD_HighlightOff(char YPos, char XPos, char count);

/*
Highlight on one LCD line
	Input
		YPos
			line number (0 up to 3)
*/
extern void LCD_HighlightLineOn(char YPos);

/*
Highlight off one LCD line
	Input
		YPos
			line number (0 up to 3)
*/
extern void LCD_HighlightLineOff(char YPos);

/* Highlight on all characters on LCD */
extern void LCD_HighlightAllOn(void);

/* Highlight off all characters on LCD */
extern void LCD_HighlightAllOff(void);

/* Clear LCD Screen */
extern void LCD_ClearScreen(void);

/*
Clear one LCD Line
	Input
		YPos
			line number (0 up to 3)
*/
extern void LCD_ClearLine(char YPos);

/*
Display a character on LCD
	Input
		YPos
			line number (0 up to 3)
		XPos
			position (0 up to 15)
		ch
			character for display on LCD
		num_lang
			display language number
				0: English
				1: Farsi
*/
extern void LCD_DisplayChar(char YPos, char XPos, char ch, char num_lang);

/*
Display n characters on one LCD line
	Input
		YPos
			line number (0 up to 3)
		XPos
			position (0 up to 15)
		count
			count of characters (1 up to 16)
		str
			pointer of string for display on LCD
		num_lang
			display language number
				0: English
				1: Farsi
*/
extern void LCD_DisplayString(char YPos, char XPos, char count, char *str, char num_lang);

/*
Clear one LCD Line and display a null-terminated string on one LCD line
	Input
		YPos
			line number (0 up to 3)
		justify_mode
			0: LEFT_JUSTIFIED
			1: CENTER_JUSTIFIED
			2: RIGHT_JUSTIFIED
		str
			pointer of a null-terminated string for display on LCD
		num_lang
			display language number
				0: English
				1: Farsi
*/
extern void LCD_DisplayLine(char YPos, char justify_mode, char *str, char num_lang);


#ifdef __cplusplus
}
#endif

#endif	/* LCDLIB_H */

/* */
