
/*======================================================================*/
/*																		*/
/*									UTILLIB.H							*/
/*																		*/
/*======================================================================*/

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "typedef.h"


// Convert Iranian Code to Bitel Farsi Code
extern void IranianCode2BitelFarsiCode(char *str, int size);

// Convert Bitel Farsi Code to Olivetti PR4 SL Code
extern void BitelFarsiCode2OlivettiPR4SLCode(char *str, int size);

// Convert Bitel Farsi Code to BP-3000 Code
extern void BitelFarsiCode2BP3000Code(char *str, int size);

// Convert Indian number to Farsi number
extern void IndianNo2FarsiNo(char *str, int size);

// Build bitmap
extern void BuildBitMap(unsigned char bitmap[2], char *src);

/*
Return the status of the bit in the bit map corresponding to the field number.
If field_no is illegal for the given map, 0 is returned.
	Input
		bitmap
			Pointer of bit map buffer
		field_no
			field number to be set (1 up to 16)
	
	Return value
		0: bit is reset, 1: bit is set
*/
extern BOOL BitMap_Test(unsigned char *bitmap, int field_no);

extern void UnsignedShort_to_HEX2(char *dst, unsigned short src);

extern unsigned short HEX2_to_UnsignedShort(char *src);

extern void Unsignedlong_to_HEX3(char *dst, unsigned long src);

extern unsigned long HEX3_to_Unsignedlong(char *src);

/*
Convert a hexadecimal ASCII character to a hexadecimal digit.
	Input
		ch
			a hexadecimal ASCII character
	
	Return value
		ch='0'-'9':0x00-0x09, ch='A'-'F' or 'a'-'f':0x0A-0x0F, else:0x00
*/
extern char hch2hex(char ch);

/*
Convert a hexadecimal digit to a hexadecimal ASCII character.
	Input
		ch
			a hexadecimal digit
	
	Return value
		ch=0x00-0x09:'0'-'9', ch=0x0A-0x0F:'A'-'F', else:'0'
*/
extern char hex2hch(char ch);

/*
Convert a ASCII character of Track 2 or 3 data to a hexadecimal digit.
	Input
		ch
			a ASCII character of Track 2 or 3 data
	
	Return value
		ch='0'-'?':0x00-0x0F, else:0x00
*/
extern char zch2hex(char ch);

/*
Convert a hexadecimal digit to a ASCII character of Track 2 or 3 data.
	Input
		ch
			a hexadecimal digit
	
	Return value
		ch=0x00-0x0F:'0'-'?', else:'0'
*/
extern char hex2zch(char ch);

/*
Convert a hexadecimal ASCII string to a hexadecimal digit string.
If n is an odd number, a leading zero is inserted in the destination.
	Input
		src
			pointer of a hexadecimal ASCII string
		len
			length of digits
	
	Output
		dst
			pointer of destination buffer (0x00-0x09, 0x0A-0x0F)
	
	ex) char dst[8], src[16];
		
		memcpy(src, "123", 3);
		asc2bcd(dst, src, 3);
		
		result
			dst = \x01\x23
		
		memcpy(src, "1234567890ABCDEF", 16);
		asc2bcd(dst, src, 16);
		
		result
			dst = \x12\x34\x56\x78\x90\xAB\xCD\xEF
*/
extern void asc2bcd(char *dst, char *src, int len);

/*
Convert a hexadecimal digit string to a hexadecimal ASCII ASCII string.
If n is an odd number, the most significant nibble is not inserted in the
destination.
	Input
		src
			pointer of hexadecimal digits
		len
			length of digits
	
	Output
		dst
			pointer of destination buffer ('0'-'9', 'A'-'F')
	
	ex) char dst[16], src[8];
		
		memcpy(src, "\x01\x23", 2);
		bcd2asc(dst, src, 3);
		
		result
			dst = 123
		
		memcpy(src, "\x12\x34\x56\x78\x90\xAB\xCD\xEF", 8);
		bcd2asc(dst, src, 16);
		
		result
			dst = 1234567890ABCDEF
*/
extern void bcd2asc(char *dst, char *src, int len);

/*
Convert a ASCII string of Track 2 or 3 data to a hexadecimal digit string.
If n is an odd number, a trailing F is inserted in the destination.
	Input
		src
			pointer of a ASCII string of Track 2 or 3 data
		len
			length of digits
	
	Output
		dst
			pointer of destination buffer (0x00-0x09, 0x0A-0x0F)
	
	ex) char dst[19], src[37];
		
		memcpy(src, "1234567890123456=1009:;<=>?012345678", 36);
		zasc2bcd(dst, src, 36);
		
		result
			dst = \x12\x34\x56\x78\x90\x12\x34\x56\xD1\x00\x9A\xBC\xDE\xF0\x12\x34\x56\x78
		
		memcpy(src, "1234567890123456=1009:;<=>?0123456789", 37);
		zasc2bcd(dst, src, 37);
		
		result
			dst = \x12\x34\x56\x78\x90\x12\x34\x56\xD1\x00\x9A\xBC\xDE\xF0\x12\x34\x56\x78\x9F
*/
extern void zasc2bcd(char *dst, char *src, int len);

/*
Convert a hexadecimal digit string to a ASCII string of Track 2 or 3 data.
If n is an odd number, the least significant nibble is not inserted in the
destination.
	Input
		src
			pointer of hexadecimal digit string
		len
			length of digits
	
	Output
		dst
			pointer of destination buffer ('0'-'?')
	
	ex) char dst[38], src[19];
		
		memcpy(src, "\x12\x34\x56\x78\x90\x12\x34\x56\xD1\x12\x01\x00\x00\x00\x00\x00\x00\x00", 18);
		bcd2zasc(dst, src, 36);
		
		result
			dst = 1234567890123456=1201000000000000000
		
		memcpy(src, "\x12\x34\x56\x78\x90\x12\x34\x56\xD1\x12\x01\x00\x00\x00\x00\x00\x00\x00\0x0F", 19);
		bcd2zasc(dst, src, 37);
		
		result
			dst = 1234567890123456=12010000000000000000
*/
extern void bcd2zasc(char *dst, char *src, int len);

/*
Convert a null-terminated ASCII string to packed BCD.
If n is greater than the length of a null-terminated ASCII string, leading zeroes
are inserted in the destination.
If the length of the string is greater than the count specified, the characters
beyond the count in the string will not be converted.
	Input
		src
			pointer of a null-terminated numeric ASCII string
		len
			fixed length of digits
	
	Output
		dst
			pointer of destination buffer
	
	ex) char dst[6], src[13];
		
		strcpy(src, "123");
		str_to_bcd(dst, src, 3);
		
		result
			dst = \x01\x23
		
		strcpy(src, "123456789012");
		str_to_bcd(dst, src, 12);
		
		result
			dst = \x12\x34\x56\x78\x90\x12
*/
extern void str_to_bcd(char *dst, char *src, int len);

/*
Convert n BCD nibbles to a null-terminated numeric ASCII string
	Input
		src
			pointer of a numeric digit string
		len
			fixed length of digits
	
	Output
		dst
			pointer of destination buffer
	
	ex) char dst[12], src[6];
		
		memcpy(src, "\x01\x23", 2);
		bcd_to_str(dst, src, 3);
		
		result
			dst = "123"
		
		memcpy(src, "\x12\x34\x56\x78\x90\x12", 6);
		bcd_to_str(dst, src, 12);
		
		result
			dst = "123456789012"
*/
extern void bcd_to_str(char *dst, char *src, int len);

/*
Convert a null-terminated ASCII string of track 2 data to a hexadecimal
digit string
If n is an odd number, a trailing 'F' is inserted in the destination.
	Input
		src
			pointer of a null-terminated ASCII string of Track 2 data
		len
			maximum length of digits (maximum 37)
	
	Output
		dst
			pointer of a hexadecimal digit string
	
	ex) char dst[20], src[38];
		
		strcpy(src, "4579059185314019=0701101185079217650");
		str_to_zbcd(dst, src, 37);
		
		result
			dst = "\x45\x79\x05\x91\x85\x31\x40\x19\xD0\x70\x11\x01\x18\x50\x79\x21\x76\x50"
		
		strcpy(src, "4579059185314019=07011011850792176500");
		str_to_zbcd(dst, src, 37);
		
		result
			dst = "\x45\x79\x05\x91\x85\x31\x40\x19\xD0\x70\x11\x01\x18\x50\x79\x21\x76\x50\x0F"
*/
extern void str_to_zbcd(char *dst, char *src, int len);

/*
Convert a hexadecimal digit string to a null-terminated ASCII string of track 2
data
If n is an odd number, the least significant nibble is not inserted in the
destination.
	Input
		src
			pointer of a hexadecimal digit string
		len
			length of digits (maximum 37)
	
	Output
		dst
			pointer of a null-terminated ASCII string of Track 2 data
	
	ex) char dst[38], src[20];
		
		memcpy(src, "\x45\x79\x05\x91\x85\x31\x40\x19\xD0\x70\x11\x01\x18\x50\x79\x21\x76\x50", 18);
		zbcd_to_str(dst, src, 37);
		
		result
			dst = "4579059185314019=0701101185079217650\x00"
		
		memcpy(src, "\x45\x79\x05\x91\x85\x31\x40\x19\xD0\x70\x11\x01\x18\x50\x79\x21\x76\x50\x0F", 19);
		zbcd_to_str(dst, src, 37);
		
		result
			dst = "4579059185314019=07011011850792176500\x00"
*/
extern void zbcd_to_str(char *dst, char *src, int len);

/*
Copy n bytes from source to destination.
	Input
		src
			pointer of source buffer
		len
			fixed length of charcters
	
	Output
		dst
			pointer of destination buffer
	
	ex) char dst[8], src[8];
		
		memcpy(src, "abcdefgh", 8);
		asc_to_asc(dst, src, 8);
		
		result
			dst = "abcdefgh"
*/
extern void asc_to_asc(char *dst, char *src, int len);

/*
Convert a null-terminated ASCII string to a ASCII string
If n is greater than the length of a null-terminated ASCII string, trailing spaces
are inserted in the destination.
If the length of the string is greater than the count specified, the characters
beyond the count in the string will not be converted.
	Input
		src
			pointer of a null-terminated numeric ASCII string
		len
			fixed length of digits
	
	Output
		dst
			pointer of destination buffer
	
	ex) char dst[8], src[9];
		
		strcpy(src, "abcdef");
		str_to_asc(dst, src, 8);
		
		result
			dst = "abcdef  "
		
		strcpy(src, "abcdefgh");
		str_to_asc(dst, src, 8);
		
		result
			dst = "abcdefgh"
*/
extern void str_to_asc(char *dst, char *src, int len);

/*
Convert a ASCII string to a null-terminated ASCII string
If there are more characters in the source than n bytes, the characters
beyond the count in the string will not be converted.
	Input
		src
			pointer of a null-terminated numeric ASCII string
		len
			fixed length of digits
	
	Output
		dst
			pointer of destination buffer
	
	ex) char dst[9], src[8];
		
		memcpy(src, "abcdefgh", 8);
		asc_to_str(dst, src, 8);
		
		result
			dst = "abcdefgh\x00"
*/
extern void asc_to_str(char *dst, char *src, int len);

// memcpy and add null character
extern void memcpy_null(char *dst, char *src, int size);

// Remove leading Spaces
extern void RemoveLeadingSpaces(char *dst, char *src, int len);

// Remove trailing spaces
extern void RemoveTrailingSpaces(char *dst, char *src, int len);

// Remove leading and trailing spaces
extern void RemoveLeadingAndTrailingSpaces(char *dst, char *src, int len);


#ifdef __cplusplus
}
#endif

#endif	/* UTILS_H */

/* */
