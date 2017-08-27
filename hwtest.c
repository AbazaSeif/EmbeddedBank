
#include "system.h"
#include "extern.h"
#include "./include/emv/emv_apdu.h"


//#define MSR_TEST_DEBUG


const char DOWNLOAD_PORT_TBL[] = {
    "Download Port(COM0)"
};

const char SERIAL2_PORT_TBL[] = {
    "Serial2 Port (COM1)"
};


int iModemTestOKCnt;
int iModemTestTotalCnt;
unsigned char ucModemTestFlag;


void MSRTest(void);
void ICCardTest(void);
void KeyTest_IC3100PE(void);
void KeyTest_IC5100P(void);
void RS232Test(void);
void LCDTest(void);
void LCDBacklightTest(void);
void LCDDotTest(void);
void LCDContrastTest(void);
void RTCTest(void);


//******************************************************************************
// MSR Test
//******************************************************************************

void MSRTest(void) {
    int i, msr_track, key, msr_disp_cnt;
    int track1, track2, track3;
    char track1_data[77], cardholder_name[27];
    char track2_data[38], pan[20], expiry_date[5], svc_code[4];
    char track3_data[105];

    memset(track1_data, 0x00, sizeof (track1_data));
    memset(cardholder_name, 0x00, sizeof (cardholder_name));
    memset(track2_data, 0x00, sizeof (track2_data));
    memset(pan, 0x00, sizeof (pan));
    memset(expiry_date, 0x00, sizeof (expiry_date));
    memset(svc_code, 0x00, sizeof (svc_code));
    memset(track3_data, 0x00, sizeof (track3_data));

    MSR_ClearAllCardDataBuffer();
    MSREnable();

    msr_disp_cnt = 0;
    while (1) {
        key = KEYSCAN() & 0xFF;
        if (key == BTKEY_CANCEL) {
            MSRDisable();
            MSR_ClearAllCardDataBuffer();
            return;
        }

        msr_track = MSRRead();
        if (msr_track == 0) {
            continue;
        }

        MSRDisable();
        if (ucLangFlag) {
            if (msr_disp_cnt) {
                LCD_DisplayChar(0, 2, '+', ucLangFlag);
            } else {
                LCD_DisplayChar(0, 2, '*', ucLangFlag);
            }
        } else {
            if (msr_disp_cnt) {
                LCD_DisplayChar(0, 13, '+', ucLangFlag);
            } else {
                LCD_DisplayChar(0, 13, '*', ucLangFlag);
            }
        }
        msr_disp_cnt ^= 0x01;
        LCD_ClearLine(1);
        LCD_ClearLine(2);
        LCD_ClearLine(3);

#ifdef USER_DEBUG
        Rprintf("\r\nMSR return value = %d\r\n", msr_track);
#endif

        track1 = -999;
        track2 = -999;
        track3 = -999;
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
                    track1 = MSR_GetTrack1Data(track1_data, cardholder_name);
#ifdef USER_DEBUG
                    Debug_Output("Track 1 Data    ", track1_data, strlen(track1_data), 1);
                    Debug_Output("Cardholder Name", cardholder_name, strlen(cardholder_name), 1);
#endif
                }
                if (!track1) {
                    // Display PAN of Track 1
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, track1_data, ucLangFlag);
                } else {
                    // "Track 1 Error!  "
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1Track1Error_000001], ucLangFlag);
#ifdef USER_DEBUG
                    Rprintf("Track 1 Error = %d\r\n", track1);
#endif
                }

                if (msr_track & 0x02) {
                    // Track 2 Data Capture
                    // track 2 data: max 37
                    track2 = MSR_GetTrack2Data(track2_data, pan, expiry_date, svc_code);
#ifdef USER_DEBUG
                    Debug_Output("Track 2 Data", track2_data, strlen(track2_data), 1);
                    Debug_Output("PAN         ", pan, strlen(pan), 1);
                    Debug_Output("Expiry Date", expiry_date, strlen(expiry_date), 1);
                    Debug_Output("Service Code", svc_code, strlen(svc_code), 1);
                    if (strlen(pan)) {
                        i = MSR_CheckLuhnCheckSum(pan, strlen(pan));
                        Rprintf("MSR_CheckLuhnCheckSum = %d\r\n", i);
                    }
#endif
                }
                if (!track2) {
                    // Display PAN
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, track2_data, ucLangFlag);
                } else {
                    // "Track 2 Error!  "
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1Track2Error_000001], ucLangFlag);
#ifdef USER_DEBUG
                    Rprintf("Track 2 Error = %d\r\n", track2);
#endif
                }

                if (ucMSRTrack == 2) {
                    if (msr_track & 0x08) {
                        // Track 3 Data Capture
                        // track 3 data: max 104
                        track3 = MSR_GetTrack3Data(track3_data);
#ifdef USER_DEBUG
                        Debug_Output("Track 3 Data", track3_data, strlen(track3_data), 1);
#endif
                    }
                    if (!track3) {
                        // Display PAN of Track 3
                        LCD_DisplayLine(3, LEFT_JUSTIFIED, track3_data, ucLangFlag);
                    } else {
                        // "Track 3 Error!  "
                        LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1Track3Error_000001], ucLangFlag);
#ifdef USER_DEBUG
                        Rprintf("Track 3 Error = %d\r\n", track3);
#endif
                    }
                }

                if (ucMSRTrack == 0) {
                    // Card read OK
                    if (!track1 && !track2) {
                        Beep_EventSound(OK_TONE);
                    }// Card read NG
                    else {
                        Beep_EventSound(ERROR_TONE);
                    }
                } else {
                    // Card read OK
                    if (!track1 && !track2 && !track3) {
                        Beep_EventSound(OK_TONE);
                    }// Card read NG
                    else {
                        Beep_EventSound(ERROR_TONE);
                    }
                }
                break;
            default: // MS Read Error
                // "   MSR Error!   "
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1MSRError_000000001], ucLangFlag);
#ifdef USER_DEBUG
                Rprintf("MS Read Error!\r\n");
#endif
                Beep_EventSound(ERROR_TONE);
                break;
        }

        memset(track1_data, 0x00, sizeof (track1_data));
        memset(cardholder_name, 0x00, sizeof (cardholder_name));
        memset(track2_data, 0x00, sizeof (track2_data));
        memset(pan, 0x00, sizeof (pan));
        memset(expiry_date, 0x00, sizeof (expiry_date));
        memset(svc_code, 0x00, sizeof (svc_code));
        memset(track3_data, 0x00, sizeof (track3_data));

        MSR_ClearAllCardDataBuffer();
        MSREnable();
    }
}

//******************************************************************************
// IC Card Test
//******************************************************************************

void ICCardTest(void) {
#if 1 // sispp 20111008
    int i, key, result, iccard_slot[5], iccard_ok[5];
    unsigned char ch;
    char tl_ver[33], temp[40];

    for (i = 0; i < 5; i++) {
        iccard_slot[i] = 0;
        iccard_ok[i] = 0;
    }

    if (gsc_IFMinit() != NO_ERR) {
        // "H/W No Response!",
        LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1IFMErrorMessage_01], ucLangFlag);
        TL_Close();
        TIMER_Wait1MS(5000);
        return;
    }

    if (gsc_FWversion() != NO_ERR) {
        // "H/W No Response!",
        LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1IFMErrorMessage_01], ucLangFlag);
        TL_Close();
        TIMER_Wait1MS(5000);
        return;
    } else {
        memset(tl_ver, 0x00, sizeof (tl_ver));
        i = giScLen - 1;
        if (i > 16) {
            i = 16;
        }
        strncpy(tl_ver, (char *) &gbScBuf[1], i);
        LCD_DisplayLine(3, LEFT_JUSTIFIED, tl_ver, ucLangFlag);
        TIMER_Wait1MS(1000);
    }

    // " Select SLOT[ ] ",
    LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelectSlotNo_00001], ucLangFlag);
    // "     0 - 4      ",
    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SlotNoRange_000001], ucLangFlag);
    while (1) {
        while (1) {
            key = KEYSCAN() & 0xFF;
            if (key == BTKEY_CANCEL) {
                gsc_Power(0);
                TL_Close();
                return;
            } else if (key <= BTKEY_4) {
                break;
            }
        }

        sprintf(temp, "%d", key);
        LCD_DisplayChar(1, 13, temp[0], ucLangFlag);
        LCD_ClearLine(3);

        iccard_slot[key] = 1;

        TL_SetSlotNo(key);
        if (key == 0) {
            gem_AUXcmmd = 0x00; // Main Card
        } else {
            gem_AUXcmmd = 0x08; // AUX Card
        }

        pgsSC_STAT = (GSC_STAT *) & gsSC_STAT;
        memset(pgsSC_STAT, 0, sizeof (GSC_STAT));
        if (gsc_SetCardTYPEandSLOT(0x02, key) != NO_ERR) {
#ifdef USER_DEBUG
            Rprintf(" Not Inserted or Card error!\r\n");
#endif
            // " IC Card Error! ",
            LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ICCardNGMessage_01], ucLangFlag);
        } else {
            if (key == 0) {
                if (pgsSC_STAT->pwON) {
                    gsc_Power(0);
                }
                gsc_Power(1);
            }

            if (gbATRdata[1] == 0x3B || gbATRdata[1] == 0x3F) {
                // "   IC Card OK   ",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ICCardOKMessage_01], ucLangFlag);
                iccard_ok[key] = 1;
            } else { // PSAM Card Error
                // " IC Card Error! ",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ICCardNGMessage_01], ucLangFlag);
            }
        }
        gsc_Power(0);
        TL_Close();

        for (i = 0; i < 5; i++) {
            if (iccard_slot[i] != 1) {
                break;
            }
        }

        if (i == 5) {
            for (i = 0; i < 5; i++) {
                if (iccard_ok[i] != 1) {
                    break;
                }
            }

            TIMER_Wait1MS(3000);
            if (i == 5) {
                // " <IC Card Test> ", "                ", "IC Card Test OK!", "                "
                LCDDisplay4Lines(M4ICCardTestOKMsg_01, -1, ucLangFlag);
            } else {
                // " <IC Card Test> ", "                ", "IC Card Test NG!", "                "
                LCDDisplay4Lines(M4ICCardTestNGMsg_01, -1, ucLangFlag);
            }
            TIMER_Wait1MS(5000);
            return;
        }
    }
#endif // sispp 20111008
}

//******************************************************************************
// Key Test
//******************************************************************************

void KeyTest_IC3100PE(void) {
    int step, key;

    SAVE_PRINT_KEY(BTKEY_NULL);

    LCD_ClearScreen();
    LCD_DisplayLine(0, LEFT_JUSTIFIED, "1 2 3 4 5 6 7 8 ", ucLangFlag);
    LCD_DisplayLine(1, LEFT_JUSTIFIED, "9 * 0 #         ", ucLangFlag);
    LCD_DisplayLine(2, LEFT_JUSTIFIED, "Up Re SF CL EN  ", ucLangFlag);
    LCD_DisplayLine(3, LEFT_JUSTIFIED, "F1F2F3          ", ucLangFlag);

    step = 1;
    while (1) {
        key = KEYSCAN() & 0xFF;
        switch (key) {
            case BTKEY_1:
                if (step == 1) {
                    LCD_HighlightOn(0, 0, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_2:
                if (step == 2) {
                    LCD_HighlightOn(0, 2, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_3:
                if (step == 3) {
                    LCD_HighlightOn(0, 4, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_4:
                if (step == 4) {
                    LCD_HighlightOn(0, 6, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_5:
                if (step == 5) {
                    LCD_HighlightOn(0, 8, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_6:
                if (step == 6) {
                    LCD_HighlightOn(0, 10, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_7:
                if (step == 7) {
                    LCD_HighlightOn(0, 12, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_8:
                if (step == 8) {
                    LCD_HighlightOn(0, 14, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_9:
                if (step == 9) {
                    LCD_HighlightOn(1, 0, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_ASTERISK:
                if (step == 10) {
                    LCD_HighlightOn(1, 2, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_0:
                if (step == 11) {
                    LCD_HighlightOn(1, 4, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_SHARP:
                if (step == 12) {
                    LCD_HighlightOn(1, 6, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_UPARROW_IC3100PE:
                if (step == 13) {
                    LCD_HighlightOn(2, 0, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_REPRINT_IC3100PE:
                if (step == 14) {
                    LCD_HighlightOn(2, 3, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_SFUNC_IC3100PE:
                if (step == 15) {
                    LCD_HighlightOn(2, 6, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_CLEAR:
                if (step == 16) {
                    LCD_HighlightOn(2, 9, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_ENTER:
                if (step == 17) {
                    LCD_HighlightOn(2, 12, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_F1_IC3100PE:
                if (step == 18) {
                    LCD_HighlightOn(3, 0, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_F2_IC3100PE:
                if (step == 19) {
                    LCD_HighlightOn(3, 2, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_F3_IC3100PE:
                if (step == 20) {
                    LCD_HighlightOn(3, 4, 2);
                    TIMER_Wait1MS(1000);

                    Beep_EventSound(OK_TONE);
                    // "   <KEY Test>   ", "                ", "  Key Test OK!  ", "                "
                    LCDDisplay4Lines(M4KeyTestOKMsg_00001, -1, ucLangFlag);
                    TIMER_Wait1MS(5000);
                    SAVE_PRINT_KEY(BTKEY_UPARROW_IC3100PE);
                    return;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_CANCEL:
                Beep_EventSound(ERROR_TONE);
                // "   <KEY Test>   ", "                ", "  Key Test NG!  ", "                "
                LCDDisplay4Lines(M4KeyTestNGMsg_00001, -1, ucLangFlag);
                TIMER_Wait1MS(5000);
                SAVE_PRINT_KEY(BTKEY_UPARROW_IC3100PE);
                return;
        }
    }
}

void KeyTest_IC5100P(void) {
    int step, key;

    SAVE_PRINT_KEY(BTKEY_NULL);

    LCD_ClearScreen();
    LCD_DisplayLine(0, LEFT_JUSTIFIED, "1 2 3 4 5 6 7 8 ", ucLangFlag);
    LCD_DisplayLine(1, LEFT_JUSTIFIED, "9 * 0 #         ", ucLangFlag);
    LCD_DisplayLine(2, LEFT_JUSTIFIED, "CL EN SF FC Up  ", ucLangFlag);

    step = 1;
    while (1) {
        key = KEYSCAN() & 0xFF;
        switch (key) {
            case BTKEY_1:
                if (step == 1) {
                    LCD_HighlightOn(0, 0, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_2:
                if (step == 2) {
                    LCD_HighlightOn(0, 2, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_3:
                if (step == 3) {
                    LCD_HighlightOn(0, 4, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_4:
                if (step == 4) {
                    LCD_HighlightOn(0, 6, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_5:
                if (step == 5) {
                    LCD_HighlightOn(0, 8, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_6:
                if (step == 6) {
                    LCD_HighlightOn(0, 10, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_7:
                if (step == 7) {
                    LCD_HighlightOn(0, 12, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_8:
                if (step == 8) {
                    LCD_HighlightOn(0, 14, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_9:
                if (step == 9) {
                    LCD_HighlightOn(1, 0, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_ASTERISK:
                if (step == 10) {
                    LCD_HighlightOn(1, 2, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_0:
                if (step == 11) {
                    LCD_HighlightOn(1, 4, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_SHARP:
                if (step == 12) {
                    LCD_HighlightOn(1, 6, 2);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_CLEAR:
                if (step == 13) {
                    LCD_HighlightOn(2, 0, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_ENTER:
                if (step == 14) {
                    LCD_HighlightOn(2, 3, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_SFUNC_IC5100P:
                if (step == 15) {
                    LCD_HighlightOn(2, 6, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_FCN_IC5100P:
                if (step == 16) {
                    LCD_HighlightOn(2, 9, 3);
                    step++;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_UPARROW_IC5100P:
                if (step == 17) {
                    LCD_HighlightOn(2, 12, 3);
                    TIMER_Wait1MS(1000);

                    Beep_EventSound(OK_TONE);
                    // "   <KEY Test>   ", "                ", "  Key Test OK!  ", "                "
                    LCDDisplay4Lines(M4KeyTestOKMsg_00001, -1, ucLangFlag);
                    TIMER_Wait1MS(5000);
                    SAVE_PRINT_KEY(BTKEY_UPARROW_IC5100P);
                    return;
                } else {
                    Beep_EventSound(ERROR_TONE);
                }
                break;
            case BTKEY_CANCEL:
                Beep_EventSound(ERROR_TONE);
                // "   <KEY Test>   ", "                ", "  Key Test NG!  ", "                "
                LCDDisplay4Lines(M4KeyTestNGMsg_00001, -1, ucLangFlag);
                TIMER_Wait1MS(5000);
                SAVE_PRINT_KEY(BTKEY_UPARROW_IC5100P);
                return;
        }
    }
}

//******************************************************************************
// LCD Test
//******************************************************************************

void LCDTest(void) {
    int key;

    // "   <LCD Test>   ", "1.Backlight Test", "2.Dot Test      ", "3.Contrast Test "
    LCDDisplay4Lines(M4LCDTestMenu_000001, LCD_LINE1, ucLangFlag);
    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1LCDTestMenu_000002]);
    while (1) {
        key = KEYSCAN() & 0xFF;
        if (sVirtualKey != BTKEY_NULL) {
            key = sVirtualKey;
            sVirtualKey = BTKEY_NULL;
        }
        if (key == BTKEY_NULL) {
            continue;
        }

        switch (key) {
            case BTKEY_ENTER:
                switch (sSelectedMenuItemNo) {
                    case 1: // Backlight Test
                        LCDBacklightTest();
                        break;
                    case 2: // Dot Test
                        LCDDotTest();
                        break;
                    case 3: // Contrast Test
                        LCDContrastTest();
                        break;
                }
                // "   <LCD Test>   ", "1.Backlight Test", "2.Dot Test      ", "3.Contrast Test "
                LCDDisplay4Lines(M4LCDTestMenu_000001, sSelectedMenuItemNo, ucLangFlag);
                SetMenuScrollUpDownInfo(1, sSelectedMenuItemNo, sSelectedMenuItemNo, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1LCDTestMenu_000002]);
                break;
            case BTKEY_CANCEL:
                return;
            default:
                MenuScrollUpDown(sStartDisplayMenuLine, &sSelectedMenuItemNo, &sSelectedMenuItemLine, sTotalMenuItemNo, psz17FirstMenuItemMsgAddr, key, ucLangFlag);
                if (key >= 1 && key <= sTotalMenuItemNo) {
                    sVirtualKey = BTKEY_ENTER;
                }
                break;
        }
    }
}

void LCDBacklightTest(void) {
    // "<Backlight Test>", "                ", " Backlight OFF  ", "                "
    LCDDisplay4Lines(M4LCDBacklightOff_01, -1, ucLangFlag);
    BACK_ONOFF(OFF);
    TIMER_Wait1MS(3000);

    // " Back Lingt ON  "
    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1LCDBacklightOn_001], ucLangFlag);
    BACK_ONOFF(ON);
    TIMER_Wait1MS(3000);
}

void LCDDotTest(void) {
    int key;

    LCD_ClearScreen();
    LCD_HighlightAllOn();
    while (1) {
        key = KEYSCAN() & 0xFF;
        if (key == BTKEY_ENTER) {
            break;
        }
    }

    LCD_HighlightAllOff();
    while (1) {
        key = KEYSCAN() & 0xFF;
        if (key == BTKEY_ENTER) {
            break;
        }
    }
}

void LCDContrastTest(void) {
    int i;
    char temp[17];

    // "<Contrast  Test>", "                ", "                ", "                "
    LCDDisplay4Lines(M4LCDContrastTest_01, -1, ucLangFlag);
    for (i = 0; i < 64; i++) {
        sprintf(temp, "[%2d]", i);
        LCD_DisplayLine(2, CENTER_JUSTIFIED, temp, ucLangFlag);
        LCD_CONT(i);
        TIMER_Wait1MS(150);
    }
    TIMER_Wait1MS(1000);

    LCD_CONT(st_POSSetupInfo.ucLCDContrast);
}

//******************************************************************************
// RS232 Test
//******************************************************************************

void RS232Test(void) {
    int i, download_port, serial2_port;
    unsigned short waittime;
    unsigned char ch;
    char tx_buf[20], rx_buf[20];

    // "1.Download -    ",
    LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadPort_00001], ucLangFlag);

    // Download Port Test
    RS232_OpenPort(COM0, BPS19200, NONE8BIT, STOP1BIT, 0);

    memcpy(tx_buf, (char *) &DOWNLOAD_PORT_TBL[0], 19);
    RS232_Write(COM0, (char *) &tx_buf[0], 19);

    memset((char *) &rx_buf[0], 0x00, sizeof (rx_buf));

    waittime = TIMER_Get1MSTimer();
    download_port = 1;
    i = 0;
    while (1) {
        if (TIMER_GetElapsed1MSTime(waittime) >= 500) {
            break;
        }

        if (RS232_CheckRxInput(COM0)) {
            ch = RS232_Read(COM0) & 0xFF;
            rx_buf[i & 0x1FFF] = ch;
            i++;
            if (i == 19) {
                if (!memcmp(rx_buf, (char *) &DOWNLOAD_PORT_TBL[0], 19)) {
                    download_port = 0;
                }
                break;
            }
        }
    }
    if (!download_port) {
        // "1.Download - OK ",
        LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadPortOK_001], ucLangFlag);
    } else {
        // "1.Download - NG ",
        LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadPortNG_001], ucLangFlag);
    }

    // "2.Serial 2 -    ",
    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1Serial2Port_000001], ucLangFlag);

    // Serial2 Port Test
    RS232_OpenPort(COM1, BPS19200, NONE8BIT, STOP1BIT, 0);

    memcpy(tx_buf, (char *) &SERIAL2_PORT_TBL[0], 19);
    RS232_Write(COM1, (char *) &tx_buf[0], 19);

    memset((char *) &rx_buf[0], 0x00, sizeof (rx_buf));

    waittime = TIMER_Get1MSTimer();
    serial2_port = 1;
    i = 0;
    while (1) {
        if (TIMER_GetElapsed1MSTime(waittime) >= 500) {
            break;
        }

        if (RS232_CheckRxInput(COM1)) {
            ch = RS232_Read(COM1) & 0xFF;
            rx_buf[i & 0x1FFF] = ch;
            i++;
            if (i == 19) {
                if (!memcmp(rx_buf, (char *) &SERIAL2_PORT_TBL[0], 19)) {
                    serial2_port = 0;
                }
                break;
            }
        }
    }
    if (!serial2_port) {
        // "2.Serial 2 - OK ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1Serial2PortOK_0001], ucLangFlag);
    } else {
        // "2.Serial 2 - NG ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1Serial2PortNG_0001], ucLangFlag);
    }
    TIMER_Wait1MS(5000);
}

//******************************************************************************
// RTC Test
//******************************************************************************

void RTCTest(void) {
    int i;
    long stime, etime;
    _tDATE_TIME dt;

    i = RTC_GetDateTime(&dt, GREGORIAN_CALENDAR);
    if (i == 0) {
        Beep_EventSound(ERROR_TONE);
        // "   RTC Error!   ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1RTCTestNG_00000001], ucLangFlag);
        TIMER_Wait1MS(5000);
    }

    stime = (long) (((dt.CLKHOUR & 0xF0) >> 4) * 10 + (dt.CLKHOUR & 0x0F)) * 3600;
    stime += (long) (((dt.CLKMIN & 0xF0) >> 4) * 10 + (dt.CLKMIN & 0x0F)) * 60;
    stime += (long) (((dt.CLKSEC & 0xF0) >> 4) * 10 + (dt.CLKSEC & 0x0F));

    TIMER_Wait1MS(1500);

    memset(&dt, 0x00, sizeof (dt));
    RTC_GetDateTime(&dt, GREGORIAN_CALENDAR);

    etime = (long) (((dt.CLKHOUR & 0xF0) >> 4) * 10 + (dt.CLKHOUR & 0x0F)) * 3600;
    etime += (long) (((dt.CLKMIN & 0xF0) >> 4) * 10 + (dt.CLKMIN & 0x0F)) * 60;
    etime += (long) (((dt.CLKSEC & 0xF0) >> 4) * 10 + (dt.CLKSEC & 0x0F));

    if ((etime - stime) < 0L) {
        etime += (24 * 3600);
    }
    if ((etime - stime) == 1L || (etime - stime) == 2L) {
        Beep_EventSound(OK_TONE);
        // "     RTC OK     ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1RTCTestOK_00000001], ucLangFlag);
    } else {
        Beep_EventSound(ERROR_TONE);
        // "   RTC Error!   ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1RTCTestNG_00000001], ucLangFlag);
    }
    TIMER_Wait1MS(5000);
}


/* */
