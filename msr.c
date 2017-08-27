
#include "system.h"
#include "extern.h"


//#define MSR_DEBUG


unsigned char ucMSRTrack;
char sz77Track1Data[77];
char sz27CardholderName[27];
char sz38Track2Data[38];
char sz20PAN[20];
char sz5ExpiryDate[5];
char sz4CardServiceCode[4];
char sz105Track3Data[105];
int isDetectCard;

void MSRTask(void);
void ClearAllMSRDataBuf(void);
void MSREnable(void);
void MSRDisable(void);
int MSRRead(void);

extern char CardNo2[52];

void MSRTask(void) {
    int i, j, msr_track;
    int track1, track2, track3;

    msr_track = MSRRead();
    if (msr_track == 0) {
        return;
    }

    MSRDisable();
    track1 = -999;
    track2 = -999;
    track3 = -999;

#ifdef USER_DEBUG
#ifdef MSR_DEBUG
    Rprintf("\r\nMSR return value = %d\r\n", msr_track);
#endif
#endif

    switch (msr_track) {
        case 1: // Track 1(or 3) Only
        case 2: // Track 2 Only
        case 3: // Track 1(or 3) & 2
        case 8: // Track 3 Only
        case 9: // Track 1 & 3
        case 10: // Track 2 & 3
        case 11: // Track 1 & 2 & 3
            if (msr_track & 0x01) {
                // Track 1 Data Capture
                // track 1 data: max 76, cardholder name: max 26
                track1 = MSR_GetTrack1Data(sz77Track1Data, sz27CardholderName);
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
                Debug_Output("sz77Track1Data", sz77Track1Data, strlen(sz77Track1Data), 1);
                Debug_Output("sz27CardholderName", sz27CardholderName, strlen(sz27CardholderName), 1);
#endif
#endif
            }
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
            if (track1) {
                Rprintf("Track 1 Error = %d\r\n", track1);
            }
#endif
#endif

            if (msr_track & 0x02) {
                // Track 2 Data Capture
                // track 2 data: max 37
                track2 = MSR_GetTrack2Data(sz38Track2Data, sz20PAN, sz5ExpiryDate, sz4CardServiceCode);
                CardNo2[0] = strlen(sz38Track2Data);
                memcpy(&CardNo2[1], sz38Track2Data, sizeof (sz38Track2Data));
#ifdef TEST_CARD
                memset(sz38Track2Data, 0x00, sizeof (sz38Track2Data));
                memset(sz20PAN, 0x00, sizeof (sz20PAN));
                memset(sz5ExpiryDate, 0x00, sizeof (sz5ExpiryDate));
                memset(sz4CardServiceCode, 0x00, sizeof (sz4CardServiceCode));

                /*
                strcpy(sz38Track2Data, "6037991000000016=99121014295000000000");	// PIN: 1111
                strcpy(sz20PAN, "6037991000000016");
                strcpy(sz5ExpiryDate, "9912");
                strcpy(sz4CardServiceCode, "101");
                 */
                strcpy(sz38Track2Data, "6037991037177031=91041012731000000000"); // PIN: 1272
                strcpy(sz20PAN, "6037991037177031");
                strcpy(sz5ExpiryDate, "9104");
                strcpy(sz4CardServiceCode, "101");
#endif
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
                Debug_Output("sz38Track2Data", sz38Track2Data, strlen(sz38Track2Data), 1);
                Debug_Output("sz20PAN", sz20PAN, strlen(sz20PAN), 1);
                Debug_Output("sz5ExpiryDate", sz5ExpiryDate, strlen(sz5ExpiryDate), 1);
                Debug_Output("sz4CardServiceCode", sz4CardServiceCode, strlen(sz4CardServiceCode), 1);
#endif
#endif
            }
            if (!track2) {
                if (strlen(sz20PAN) && strlen(sz5ExpiryDate)) {
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
                    i = MSR_CheckLuhnCheckSum(sz20PAN, strlen(sz20PAN));
                    Rprintf("MSR_CheckLuhnCheckSum = %d\r\n", i);
#endif
#endif
                } else {
                    track2 = -99;
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
                    Rprintf("Track 2 Data Error = %d\r\n", track2);
#endif
#endif
                }
            }
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
            else {
                Rprintf("Track 2 Data Error = %d\r\n", track2);
            }
#endif
#endif

            if (ucMSRTrack == 2) {
                if (msr_track & 0x08) {
                    // Track 3 Data Capture
                    // track 3 data: max 104
                    track3 = MSR_GetTrack3Data(sz105Track3Data);
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
                    Debug_Output("Track 3 Data", sz105Track3Data, strlen(sz105Track3Data), 1);
#endif
#endif
                }
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
                if (track3) {
                    Rprintf("Track 3 Error = %d\r\n", track3);
                }
#endif
#endif
            }

            MSR_ClearAllCardDataBuffer();

            switch (*pusServiceAddr) {
                case 0x0000: // Initial status
                case 0x5000: // Customer Trans. - Retry to swipe card
                    // Card read OK
                    if (!track2) {
                        if (!st_POSSetupInfo.ucPOSActive) {
                            // "                ", "POS isn't active", "                ", "                "
                            ErrorDisplayAndGoInitialStatus(M4POSNotActive_00001, -1, ucLangFlag);
                            return;
                        }

                        i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 1);
                        if (i) {
                            DisplayConnectionErrorConditionAndGotoInitialStatus(i);
                            return;
                        }

                        i = GetTrxnMenuActiveStatus();
                        if (i == 0) {
                            return;
                        } else {
                            // for Pre-dialing
                            ModemOpen(PRE_CONNECTION);

                            Beep_EventSound(OK_TONE);
                            isDetectCard = 0x01;

                            if (InitTrxnReqData() < 0) {
                                ErrorDisplayAndGoErrorStatus(M4ErrNoBatchNo_00001, -1, ucLangFlag);
                                return;
                            }
                            //strcpy(st_POSSetupInfo.sz9TerminalID, "0987654");
                            //strcpy(st_POSSetupInfo.sz16MerchantID, "87654321");
                            //ucGprsModuleOkFlag = 1;
                            //ucGprsSIMStatus = SIM_READY;


                        }

                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                    } else {
                        Beep_EventSound(ERROR_TONE);
                        // "Swipe your card ", "                ", "                ", "Try again       "
                        MainStatusSetting(MSS_CUSTOMER_TRANS, MST_CUSTOMER_TRANS, M4SwipeAgain_0000001, -1, ucLangFlag);

                        ClearAllMSRDataBuf();
                        MSREnable();
                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                    }
                    break;
                case 0x5002:
                    if (!track2) {
                        Beep_EventSound(OK_TONE);
                        isDetectCard = 0x01;
                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                        sVirtualKey = BTKEY_ENTER;
                    } else {
                        Beep_EventSound(ERROR_TONE);
                        // "Swipe your card ", "                ", "                ", "Try again       "
                        LCDDisplay4Lines(M4SwipeAgain_0000001, -1, ucLangFlag);

                        ClearAllMSRDataBuf();
                        MSREnable();
                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                    }
                    break;
                case 0x1531: // Modem Test - Swipe card
                    // Card read OK
                    if (!track2) {
                        Beep_EventSound(OK_TONE);
                        pusServiceAddr++;
                        sVirtualKey = BTKEY_ENTER;
                    } else {
                        Beep_EventSound(ERROR_TONE);
                        // "Try again       ",
                        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1TryAgain_000000001], ucLangFlag);

                        ClearAllMSRDataBuf();
                        MSREnable();
                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                    }
                    break;
                default:
                    ClearAllMSRDataBuf();
                    break;
            }
            break;

        default: // Card Reading Error
#ifdef USER_DEBUG
#ifdef MSR_DEBUG
            Rprintf("Card Reading Error!\r\n");
#endif
#endif
            MSR_ClearAllCardDataBuffer();
            ClearAllMSRDataBuf();
            switch (*pusServiceAddr) {
                case 0x0000: // Initial status
                case 0x1531: // Modem Test - Swipe card
                case 0x5000: // Customer Trans. - Retry to swipe card
                    MSREnable();
                    break;
            }
            break;
    }
}

void ClearAllMSRDataBuf(void) {
    memset(sz77Track1Data, 0x00, sizeof (sz77Track1Data));
    memset(sz27CardholderName, 0x00, sizeof (sz27CardholderName));
    memset(sz38Track2Data, 0x00, sizeof (sz38Track2Data));
    memset(sz20PAN, 0x00, sizeof (sz20PAN));
    memset(sz5ExpiryDate, 0x00, sizeof (sz5ExpiryDate));
    memset(sz4CardServiceCode, 0x00, sizeof (sz4CardServiceCode));
    memset(sz105Track3Data, 0x00, sizeof (sz105Track3Data));
}

void MSREnable(void) {
    // MSR TYPE
    // 0x33:Uniform Triple, 0x34:MagTek Triple
    if (sz17HWInfo[6] != 0x34) {
        CARD_ENABLE();
    } else {
        MAGTEK_MSR_NewMode_Card_Enable();
    }
}

void MSRDisable(void) {
    // MSR TYPE
    // 0x33:Uniform Triple, 0x34:MagTek Triple
    if (sz17HWInfo[6] != 0x34) {
        CARD_DISABLE();
    } else {
        MAGTEK_MSR_NewMode_Card_Disable();
    }
}

int MSRRead(void) {
    int ret;

    // MSR TYPE
    // 0x33:Uniform Triple, 0x34:MagTek Triple
    if (sz17HWInfo[6] != 0x34) {
        ret = CARD_READ() & 0xFF;
    } else {
        ret = MAGTEK_MSR_NewMode_Card_Read();
    }
}

/* */
