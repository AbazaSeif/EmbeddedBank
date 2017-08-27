
/*------------------------------------------------------------------------------
Author		: K.H LEE Bitel Co., Ltd.
File name	: SYSINFO.H
Purpose		: Library of system information

Revision history
Revision No.	Date				Contents
R1.00			21/May/2005 		First revison
R1.01			24/October/2008 	Change functions name
------------------------------------------------------------------------------*/

#ifndef SYSINFO_H
#define SYSINFO_H

#ifdef __cplusplus
extern "C" {
#endif


/*
Get BIOS Version
	Output
		bios_ver: pointer of a null-terminated string
			ex) "3.217"
*/
extern void SYSINFO_GetBiosVersion(char bios_ver[6]);

/*
Get Hardware Information
	Output
		hw_info: pointer of a null-terminated string
			hw_info[0] : CUP MODEL       (0x33:MIPS)
			hw_info[1] : SRAM SIZE       (0x30:NONE, 0x34:2MB(default), 0x35:4MB, 0x36/0x37:8MB, 0x38:16MB)
			hw_info[2] : SDRAM SIZE      (0x30:NONE(default), 0x34:2MB, 0x35:4MB, 0x36/0x37:8MB, 0x38:16MB)
			hw_info[3] : FLASH SIZE      (0x30:NONE(default), 0x34:2MB, 0x35:4MB, 0x36/0x37:8MB, 0x38:16MB)
			hw_info[4] : FLASH1 SIZE     (0x30:NONE(default), 0x34:2MB, 0x35:4MB, 0x36/0x37:8MB, 0x38:16MB)
			hw_info[5] : USB             (0x30:USB NONE(default), 0x31:USB Exist)
			hw_info[6] : SDRAM REQUIRED  (0x30:NOT REQUIRED(default), 0x31:REQUIRED)
			hw_info[7] : MODEM SPEED     (0x32:56Kbps(default))
			hw_info[8] : PRINTER TYPE    (0x31(default))
			hw_info[9] : MODEL NAME      (0x33:IC3x00 series, 0x35:IC5x00 series, 0x36:IC6x00 series)
			hw_info[10]: MODEL DETAIL    (0x31:ICx100 series, 0x33:ICx300 series)
			hw_info[11]: VERIFY REQUIRED (0x30:NOT REQUIRED(default), 0x31:REQUIRED)
			hw_info[12]: LCD TYPE        (0x31:IC3100, 0x32:IC5100/IC3300)
			hw_info[13]: KEY TYPE        (0x31:IC5100, 0x32:IC3100)
			hw_info[14]: PARTIAL ACCEPT  (0x30:NOT ACCEPTED, 0x31:ACCEPTED(default))
			hw_info[15]: PCI REQUIRED    (0x30:NOT REQUIRED(default), 0x31:REQUIRED)
*/
extern void SYSINFO_GetHWInformation(char hw_info[17]);


#ifdef __cplusplus
}
#endif

#endif	/* SYSINFO_H */

/* */
