/***************************************************************************
                       gem_TL.h  -  description
                          -------------------
 begin                : Wed May 30 2001
 copyright            : (C) 2001 by Gemplus
 email                :
***************************************************************************/

#ifndef _gem_TL_H_
#define _gem_TL_H_

#include "../../system.h"
#include "../../extern.h"

/* ---- From gem_ERR.h ----*/
#define ERR_BASE 0x1000

#define NO_ERR  0   /*Everything is OK*/
#define ERR_COMNUM            ERR_BASE      /*Wrong Com number or Serial Port is Absent*/
#define ERR_INITPORT          ERR_BASE+1    /*One of the argument (BaudRate,start bit,...) is wrong*/
#define ERR_LRC               ERR_BASE+2    /*Wrong LRC*/
#define ERR_READER_MUTE       ERR_BASE+3    /*Reader is mute*/
#define ERR_SEQUENCE_NUMBER   ERR_BASE+4    /*The Sequence Number received is incorrect*/
#define ERR_RESYNCH           ERR_BASE+5    /*The API had to send Resynch Command to the Reader.*/
#define ERR_WRITEPORT         ERR_BASE+6    /*An error occured during Send operation*/
#define ERR_READPORT          ERR_BASE+7    /*An error occured during Write operation*/
#define ERR_SERIOUS_ERROR     ERR_BASE+8    /*A serious error occured. Resynch was unsucessfull */
#define ERR_NACK              ERR_BASE+9    /*The Reader has sent NACK Value. Only in TLP Protocol.*/
#define ERR_NO_EOT            ERR_BASE+10   /*No EOT received*/
#define ERR_PARITY            ERR_BASE+10   /*Parity Error found.*/

/* ---- From gem_TL.h ----*/
#define TLP_PROTOCOL    0
#define GBP_PROTOCOL    1

#define GBP_SIZE 262    /*GBP MAX -> 255 Data + NAD + PCB +LEN +LRC = 259*/
//#define GBP_SIZE 32    /*GBP MAX -> 255 Data + NAD + PCB +LEN +LRC = 259*/
#define MAXTRY   3      /*Number of retry in GBP Protocol if some errors occur*/
#define EOT_GEM  0x03   /*The end of a transmission in TLP 224 Protocol*/
#define DEFAULT_PCB_VALUE 0x00  /*Default PCB Value in GBP Protocol*/
#define DEFAULT_NAD_VALUE 0x42  /*Default Host to Reader NAD Value in GBP Protocol*/
#define RESYNCH  0xC0   /*Resynch Value*/
#define TL_VERSION "TL_VERSION-V1.0" /*Library Version*/
#define DEFAULT_TIMEOUT   2000  /*Default Communication Timeout Value between Library and GBP device*/

#ifdef __cplusplus
extern "C" {
#endif

short TL_SendReceive(U32 ucLnCmd, U08 *pszCmd, U32 *pucLnResp, U08 *pszResp );

short TL_Open( U08 ucNCom, S32 uliVCom );
short TL_Close(void);

void TL_SetSlotNo(U08 slot_no);
U08 TL_GetSlotNo();

#ifdef __cplusplus
}
#endif

#endif
