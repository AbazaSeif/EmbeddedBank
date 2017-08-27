
/*======================================================================*/
/*																		*/
/*								MEMLIB.H								*/
/*																		*/
/*======================================================================*/

#ifndef MEMLIB_H
#define MEMLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "typedef.h"


/*
Set Flash 1 Sector Size
	Input
		sector_size
			sector size of flash memory
	
	Return value
		none
*/
extern void MEMLIB_SetFlashSectorSize(long sector_size);

/*
Get Flash 1 Sector Blank Status
	Input
		top_addr
			top address of flash 1 Sector
	
	Return value
		0: Not blank, 1: Blank
*/
extern BOOL MEMLIB_GetFlash1SectorBlankStatus(char *top_addr);

/*
Get Flash n Bytes Blank Status
	Input
		start_addr
			start address of flash for checking blank status
		size
			length of bytes
	
	Return value
		0: Not blank, 1: Blank
*/
extern BOOL MEMLIB_GetFlashBytesBlankStatus(char *start_addr, long size);

/*
Get Flash 1 Sector Erasing Condition
	Input
		dst_top_addr
			pointer of destination sector top address
		src_top_addr
			pointer of source sector top address
	
	Return value
		0: Not need to earse 1 Sector of Flash, 1: Need to earse 1 Sector of Flash
*/
extern BOOL MEMLIB_GetFlash1SectorErasingCondition(char *dst_top_addr, char *src_top_addr);

/*
Get Flash 1 Sector Erasing Condition With n Bytes in 1 Sector
	Input
		dst
			pointer of destination
		src
			pointer of source
		size
			length of string
	
	Return value
		0: Not need to earse 1 Sector of Flash, 1: Need to earse 1 Sector of Flash
*/
extern BOOL MEMLIB_GetFlash1SectorErasingConditionWithBytes(char *dst, char *src, long size);


#ifdef __cplusplus
}
#endif

#endif	/* MEMLIB_H */

/* */
