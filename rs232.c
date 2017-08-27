
/*======================================================================*/
/*																		*/
/*								RS232.C									*/
/*																		*/
/*======================================================================*/

#include "system.h"
#include "extern.h"


int iRS232RxCnt; // RS232 Rx counter
int iRS232RxSize; // RS232 Rx data size
unsigned short usRS232TaskStep; // RS232 task step
unsigned short usRS23210MSMaxTimeout; // RS232 10ms maximum timeout
unsigned short usRS23210MSTimer; // RS232 10ms timer
unsigned char ucRS232RxBuf[8192]; // RS232 Rx data buffer


void RS232Task(void);
void RS232Open(void);
void RS232Close(void);

/* RS232 task */
void RS232Task(void) {
    int i, j, k, len, rxdata;
    char bill_id[14], payment_id[14];
    char str[17], temp[17];
    char ch;

    if (usRS232TaskStep == 0) {
        return;
    }

    if (iRS232RxCnt) {
        if (TIMER_GetElapsed10MSTime(usRS23210MSTimer) >= usRS23210MSMaxTimeout) {
            memset((char *) &ucRS232RxBuf, 0x00, sizeof (ucRS232RxBuf));
            iRS232RxCnt = 0;
            return;
        }
    }

    if (RS232_CheckRxInput(COM0) == 0) {
        return;
    }

    rxdata = RS232_Read(COM0) & 0xFF;
    ucRS232RxBuf[iRS232RxCnt] = rxdata;
    iRS232RxCnt++;
    iRS232RxCnt &= 0x1FFF;

    if (iRS232RxCnt == 1) {
        usRS23210MSTimer = TIMER_Get10MSTimer();
        usRS23210MSMaxTimeout = 100;
        return;
    }

    if (iRS232RxCnt >= 2 && ucRS232RxBuf[iRS232RxCnt - 2] == '\r' && ucRS232RxBuf[iRS232RxCnt - 1] == '\n') {
        //LCD_DisplayLine(2, LEFT_JUSTIFIED, ucRS232RxBuf, ucLangFlag);
        //if (iRS232RxCnt > 16) {
        //	LCD_DisplayLine(3, LEFT_JUSTIFIED, &ucRS232RxBuf[16], ucLangFlag);
        //}

        switch (*pusServiceAddr) {
            case 0x11D1: // POS Serial Number - Input POS Serial Number
                i = iRS232RxCnt - 2;
                if (i < 8 || i > 16) {
                    Beep_EventSound(ERROR_TONE);
                    break;
                }

                memset(temp, 0x00, sizeof (temp));
                RemoveLeadingAndTrailingSpaces(temp, ucRS232RxBuf, i);
                if (!memcmp(temp, "S/N", 3)) {
                    memset(str, 0x00, sizeof (str));
                    strcpy(str, &temp[3]);
                    i = strlen(str);
                    RemoveLeadingAndTrailingSpaces(temp, str, i);
                }

                i = strlen(temp);
                if (i < 8 || i > 16) {
                    Beep_EventSound(ERROR_TONE);
                    break;
                }

                for (j = 0; j < i; j++) {
                    if ((temp[j] < '0' || temp[j] > '9') && (temp[j] < 'A' || temp[j] > 'Z') && temp[j] != ' ') {
                        break;
                    }
                }
                if (j != i) {
                    Beep_EventSound(ERROR_TONE);
                } else {
                    RS232Close();
                    ClearTempKeyBufAndStringCopy(temp);

                    pusServiceAddr++;
                    sVirtualKey = BTKEY_ENTER;
                }
                break;
        }

        memset((char *) &ucRS232RxBuf, 0x00, sizeof (ucRS232RxBuf));
        iRS232RxCnt = 0;
    }
}

/* Open RS232 */
void RS232Open(void) {
#ifdef USER_DEBUG
    DisableDebugOutput();
#endif
    RS232_OpenPort(COM0, BPS9600, NONE8BIT, STOP1BIT, 0);

    memset((char *) &ucRS232RxBuf, 0x00, sizeof (ucRS232RxBuf));
    iRS232RxCnt = 0;
    iRS232RxSize = 0;

    usRS232TaskStep = 1;
}

void RS232Close(void) {
    if (usRS232TaskStep > 0) {
        usRS232TaskStep = 0;
#ifdef USER_DEBUG
        OpenDebugPort(COM0, BPS115200, NONE8BIT, STOP1BIT, 0);
#else
        DisableDebugOutput();
#endif
    }
}

/* */
