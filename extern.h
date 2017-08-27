
/*======================================================================*/
/*																		*/
/*								EXTERN.H								*/
/*																		*/
/*======================================================================*/

#ifndef EXTERN_H
#define EXTERN_H

#ifdef __cplusplus
extern "C" {
#endif


//#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "include/drv/driver.h"

#include "include/lib/typedef.h"
#include "include/lib/keydef.h"

#include "include/lib/prtpmlogo.h"
#include "include/lib/prtbitellogo.h"

#include "include/lib/btsclib.h"

#include "include/lib/sysinfo.h"
#include "include/lib/memlib.h"
#include "include/lib/beeplib.h"
#include "include/lib/rtclib.h"
#include "include/lib/timerlib.h"
#include "include/lib/msrlib.h"
#include "include/lib/commlib.h"
#include "include/lib/lcdlib.h"
#include "include/lib/keylib.h"
#include "include/lib/country.h"
#include "include/lib/unzip.h"
#include "include/lib/tmslib.h"

#include "include/lib/iconlib.h"
#include "include/lib/gsmlib.h"
#include "include/lib/utillib.h"

#include "include/lib/magtek_msr.h"

#include "include/lib/frmwri.h"
#include "include/lib/printf.h"

#include "stsdef.h"
#include "main.h"
#include "flash.h"
#include "apppos.h"
#include "rtc.h"
#include "key.h"
#include "msr.h"
#include "modem.h"
#include "gsm.h"
#include "rs232.h"
#include "lcdmsg1.h"
#include "lcdmsg4.h"
#include "lcdmsg.h"
#include "prtmsg1.h"
#include "prtmsg.h"
#include "printer.h"
#include "hwtest.h"
#include "tmsdown.h"
#include "utils.h"

extern int _etext;
extern int __usr_rom_start;
extern int __usr_ram_start;
extern int __usr_ram_end;

extern int __ram_heap_start;
extern int __ram_heap_end;


extern const long REFTABLE[];


// usblib.a
// 0: Not connected, 1: Connected
extern int UsbStartFlg;

// Return Value
// 0: OK, else: Open Error
extern int USB_Open(void);

// Return Value
// 0: OK, else: Close Error
extern int USB_Close(void);

// Output
//		stream
//			point of received data string (maximum 64 bytes)
// Return Value
//		length of received data
extern int USB_Read(unsigned char *stream);

// Output
//		stream
//			point of sending data string
//		length
//			length of sending data
// Return Value
//		0: OK, else: Error
extern int USB_Write(unsigned char *stream, int length);


#ifdef __cplusplus
}
#endif

#endif	/* EXTERN_H */

/* */
