
#include "system.h"
#include "extern.h"


const char DAY_STR_TBL[7][10] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturaday"
};

const char Month12[12][4] = {
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

_tDATE_TIME RealTime;
unsigned short usLCDBackLightOn10MSTimer;
unsigned short usColonOn1MSTimer;
unsigned char ucTempMin;
unsigned char ucTempSec;
unsigned char ucDateTimeRefreshFlag;
unsigned char ucLCDBacklightOnFlag;
unsigned char ucCheckColonTimerFlag;

void RTCTask(void);
void LCDBacklightOnOffControl(unsigned short on_time);
void DisplayDateTime(_tDATE_TIME *dt);
void DisplayYYYYMMDD(_tDATE_TIME *dt, char mode);
void Displayhhmmss(_tDATE_TIME *dt);
void InitializeRTCDateTime(void);
void SetRTCDateTimeWhenPowerIsTurnedOn(void);

void RTCTask(void) {
    LCDBacklightOnOffControl(60);

    if (*pusServiceAddr != 0x0000) {
        // Set Date - Input Iranian Year
        // Set Date - Input Christian Year
        // Set Time - Input Time
        if (*pusServiceAddr == 0x4301 || *pusServiceAddr == 0x4302 || *pusServiceAddr == 0x4400) {
            RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);

            if ((RealTime.CLKSEC & 0xFF) != ucTempSec || ucDateTimeRefreshFlag) {
                if (*pusServiceAddr == 0x4301) {
                    DisplayYYYYMMDD(&RealTime, JALALI_CALENDAR);
                } else if (*pusServiceAddr == 0x4302) {
                    DisplayYYYYMMDD(&RealTime, GREGORIAN_CALENDAR);
                } else {
                    Displayhhmmss(&RealTime);
                }
            }

            if (ucDateTimeRefreshFlag) {
                ucDateTimeRefreshFlag = 0;
            }
        }

        if (ucReversalFlag == 0) {
            // Printing now
            if (usPrintStep) {
                usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                return;
            }

            // Communicating now
#if 0 // sispp 20111008
            if (usHiSpeedModemTaskStep > 0 || usEthernetTaskStep > 0 || usGprsTaskStep > 0) {
#endif
                if (usGprsTaskStep > 0) {
                    if (!ucTMSDownloadFlag) {
                        if (ucReqDataReadyFlag || ucReqDataTxFlag) {
                            usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                            return;
                        }
                    } else {
                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                        return;
                    }
                }

                // Hardware Testing now
                if (*pusServiceAddr >= 0x1500 && *pusServiceAddr <= 0x1580) {
                    usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                    return;
                }

                switch (*pusServiceAddr) {
                    case 0x2115: // Current Merchant Total - Select Reprint or Exit
                    case 0x2125: // Previous Merchant Total - Select Reprint or Exit
                    case 0x2135: // Clear Merchant Total - Select Reprint or Exit
                    case 0x2215: // Current POS Total - Select Reprint or Exit
                    case 0x2225: // Previous POS Total - Select Reprint or Exit
                    case 0x2235: // Clear POS Total - Select Reprint or Exit
                    case 0x2245: // POS Balance - Select Reprint or Exit
                    case 0x2315: // Current Store Total - Select Reprint or Exit
                    case 0x2325: // Previous Store Total - Select Reprint or Exit
                    case 0x2335: // Clear Store Total - Select Reprint or Exit
                    case 0x2345: // Open Store - Select Reprint or Exit
                    case 0x2355: // Close Store - Select Reprint or Exit
                    case 0x5119: // Not Approved Buy - Select Reprint or Exit
                    case 0x520B: // Balance Inquiry - Select Reprint or Exit
                    case 0x540B: // SIM Charge(Preliminary Transaction) - Select Reprint or Exit
                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                        return;
                }

                if (TIMER_GetElapsed10MSTime(usAutoInitial10MSTimer) >= AUTO_INITIAL_TIMEOUT) {
                    RS232Close();

                    WritePOSSetupInfo();
                    Beep_EventSound(OK_TONE);
                    SetInitialStatus();
                }
            } else {
                usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                switch (*pusServiceAddr) {
                    case 0x9000: // Print Reversal Receipt - "Insert paper and Press ENTER key"
                        if (TIMER_GetElapsed10MSTime(usReversalPrint10MSTimer) >= REVERSAL_PRINT_TIMEOUT) {
                            pstfTempTrxnLog = pstfSavingTrxnLog;
                            // Save Reversal TransactionLog
                            SaveReversalTransactionLog(pstfTempTrxnLog);
                            // Perform Reversal Transaction
                            PerformReversalTransaction();

                            ucReversalRetryCnt = 0;
                            ucReversalRetryTimePerCnt = 0;
                        }
                        break;
                        /*
                                                        case 0x9100:	// Reversal Mode - Select Reversal Mode menu item
                                                                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                                                                if (RealTime.CLKYEARH != pstfLastTrxnLog->uc4LocalDate[0] ||
                                                                        RealTime.CLKYEARL != pstfLastTrxnLog->uc4LocalDate[1] ||
                                                                        RealTime.CLKMONTH != pstfLastTrxnLog->uc4LocalDate[2] ||
                                                                        RealTime.CLKDATE  != pstfLastTrxnLog->uc4LocalDate[3]) {
                                                                        PrintUnsuccessfulReversalReceipt();
                                                                }
                                                                break;
                         */
                }
            }

            return;
        }

        usAutoInitial10MSTimer = TIMER_Get10MSTimer();

        RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);

        if ((RealTime.CLKSEC & 0xFF) != ucTempSec || ucDateTimeRefreshFlag) {
            LCD_DisplayChar(DATETIME_DISPLAY_LINE, 13, ':', ucLangFlag);
            ucTempSec = RealTime.CLKSEC;
            usColonOn1MSTimer = TIMER_Get1MSTimer();
            ucCheckColonTimerFlag = 1;

            if (st_POSSetupInfo.ucComDevice == GSM_MODEM) {
                if (ucGprsModuleOkFlag) {
                    switch (ucGprsSIMStatus) {
                        case SIM_CHECK: // ME is checking the SIM
                        case SIM_FAILURE: // SIM not inserted or failure
                            GprsDisplayAntennaLevelBar(GPRS_ANTENNA_LEVEL_1_LIMIT);
                            //LCD_DisplayString(0, 8, 8, " SIM    ", ucLangFlag);
                            DisplaySimGprsIcon(1, 0);
                            break;
                        case SIM_READY: // ME is not pending for any password (SIM is ready)
                            //LCD_DisplayString(0, 8, 4, " SIM", ucLangFlag);
                            DisplaySimGprsIcon(1, -1);
                            break;
                        case SIM_BLOCK: // SIM is blocked
                            GprsDisplayAntennaLevelBar(GPRS_ANTENNA_LEVEL_1_LIMIT);
                            //LCD_DisplayString(0, 8, 8, "SIM LOCK", ucLangFlag);
                            LCD_DisplayString(3, 2, 4, "[SL]", ucLangFlag); // "SIM LOCK"
                            break;
                        case SIM_PIN: // CHV1 is required
                        case SIM_PUK: // PUK1 is required
                        case SIM_PIN2: // CHV2 is required
                        case SIM_PUK2: // PUK2 is required
                        case PH_SIM_PIN: // SIM lock (phone-to-SIM) is required
                        case PH_NET_PIN: // Network personalization PIN required
                        case PH_NET_PUK: // Network personalization PUK required
                        case PH_NET_SUB_PIN: // Network subset personalization PIN required
                        case PH_NET_SUB_PUK: // Network subset personalization PUK required
                        case PH_SVC_PROVIDER_PIN: // Service provider personalization PIN required
                        case PH_SVC_PROVIDER_PUK: // Service provider personalization PUK required
                        case PH_CORPORATE_PIN: // Corporate personalization PIN required
                        case PH_CORPORATE_PUK: // Corporate personalization PUK required
                        case PH_SIM_PUK: // PH-SIM PUK (master phone code) required
                            GprsDisplayAntennaLevelBar(GPRS_ANTENNA_LEVEL_1_LIMIT);
                            //LCD_DisplayString(0, 8, 8, " SIM PIN", ucLangFlag);
                            LCD_DisplayString(3, 2, 4, "[SP]", ucLangFlag);
                            break;
                    }
                } else {
                    GprsDisplayAntennaLevelBar(GPRS_ANTENNA_LEVEL_4_LIMIT + 1);
                    //LCD_DisplayString(0, 8, 8, " SIM GSM", ucLangFlag);
                    DisplaySimGprsIcon(1, 1);
                }
            }
        }

        if (ucCheckColonTimerFlag && TIMER_GetElapsed1MSTime(usColonOn1MSTimer) >= 500) {
            LCD_DisplayChar(DATETIME_DISPLAY_LINE, 13, ' ', ucLangFlag);
            ucCheckColonTimerFlag = 0;

            if (st_POSSetupInfo.ucComDevice == GSM_MODEM) {
                if (ucGprsModuleOkFlag) {
                    switch (ucGprsSIMStatus) {
                        case SIM_CHECK: // ME is checking the SIM
                        case SIM_FAILURE: // SIM not inserted or failure
                        case SIM_BLOCK: // SIM is blocked
                        case SIM_PIN: // CHV1 is required
                        case SIM_PUK: // PUK1 is required
                        case SIM_PIN2: // CHV2 is required
                        case SIM_PUK2: // PUK2 is required
                        case PH_SIM_PIN: // SIM lock (phone-to-SIM) is required
                        case PH_NET_PIN: // Network personalization PIN required
                        case PH_NET_PUK: // Network personalization PUK required
                        case PH_NET_SUB_PIN: // Network subset personalization PIN required
                        case PH_NET_SUB_PUK: // Network subset personalization PUK required
                        case PH_SVC_PROVIDER_PIN: // Service provider personalization PIN required
                        case PH_SVC_PROVIDER_PUK: // Service provider personalization PUK required
                        case PH_CORPORATE_PIN: // Corporate personalization PIN required
                        case PH_CORPORATE_PUK: // Corporate personalization PUK required
                        case PH_SIM_PUK: // PH-SIM PUK (master phone code) required
                            GprsDisplayAntennaLevelBar(99);
                            //LCD_DisplayString(0, 8, 8, "        ", ucLangFlag);
                            DisplaySimGprsIcon(0, 0);
                            break;
                        case SIM_READY: // ME is not pending for any password (SIM is ready)
                            //LCD_DisplayString(0, 8, 4, " SIM", ucLangFlag);
                            DisplaySimGprsIcon(1, -1);
                            break;
                    }
                } else {
                    GprsDisplayAntennaLevelBar(99);
                    //LCD_DisplayString(0, 8, 8, "        ", ucLangFlag);
                    DisplaySimGprsIcon(0, 0);
                }
            }
        }

        if ((RealTime.CLKMIN & 0xFF) != ucTempMin || ucDateTimeRefreshFlag) {
            DisplayDateTime(&RealTime);
            ucTempMin = RealTime.CLKMIN;
#if 1
            if ((GetULDateTime() - tPOSUtilBuf.ulLastCallHomeTime) > atol(st_POSSetupInfo.sz5CallHomeInterval) * 60) {
                if (TIMER_GetElapsed1SECTime(lCallHome1SECTimer) >= 120) {
#ifdef USER_DEBUG
                    Rprintf("Start CallHome!\r\n");
#endif
                    if (GetConnectionConditions(st_POSSetupInfo.ucComDevice, 4, 0) == 0) {
                        MainStatusSetting(MSS_CALLHOME, MST_TAMS_CALLHOME, M4StartCallHome_0001, -1, ucLangFlag);
                        sVirtualKey = BTKEY_ENTER;
                        return;
                    }
                }
            }
#endif
        }

        if (ucDateTimeRefreshFlag) {
            ucDateTimeRefreshFlag = 0;
        }

        if (st_POSSetupInfo.ucAutoTMSActiveFlag) {
            CheckAutoTMSDownloadStart();
        }


#ifdef AUTO_MODEM_TEST
        if (TIMER_GetElapsed10MSTime(usModemAutoTest10MSTimer) >= 300) {
            MSRDisable();

            // "Enter your PIN  ", "                ", "                ", "                "
            MainStatusSetting(MSS_BALANCE, MST_BALANCE_INQUIRY, M4EnterYourPIN_00001, -1, ucLangFlag);

            usMsgType = MTYPE_FINANCIAL_TRXN_REQUEST;
            ulPCode = PCODE_DEBIT_BALANCE_INQUIRY;
            GetTransactionType(&usTransType, usMsgType, ulPCode);

            // Get PAN
            memset(sz20PAN, 0x00, sizeof (sz20PAN));
            strcpy(sz20PAN, "1700191111300032");

            // Display PAN
            LCD_DisplayLine(2, LEFT_JUSTIFIED, sz20PAN, ucLangFlag);

            // Get expired date
            memset(sz5ExpiryDate, 0x00, sizeof (sz5ExpiryDate));
            strcpy(sz5ExpiryDate, "8604");

            strcpy(sz13CardPIN, "3333");

            strcpy(st_TrxnReqData.sz9TerminalID, st_POSSetupInfo.sz9TerminalID);
            strcpy(st_TrxnReqData.sz16MerchantID, st_POSSetupInfo.sz16MerchantID);
            strcpy(st_TrxnReqData.sz16MerchantID, pstParams->szMerchantID);

            memset(ucTrxnTxBuf, 0x00, sizeof (ucTrxnTxBuf));
            iTxSize = BuildRequestMessage(&ucTrxnTxBuf[0]);
            ucReqDataReadyFlag = 1;

            pusServiceAddr += 3;
        }
#endif
    }

    // LCD Backlight On/Off Control

    void LCDBacklightOnOffControl(unsigned short on_time) {
        unsigned short max_on_time;

        if (*pusServiceAddr == 0x0000) {
            if (ucLCDBacklightOnFlag) {
                max_on_time = on_time * 100;
                if (TIMER_GetElapsed10MSTime(usLCDBackLightOn10MSTimer) >= max_on_time) {
                    ucLCDBacklightOnFlag = 0;
                    BACK_ONOFF(OFF);
                }
            }
        } else {
            if (ucLCDBacklightOnFlag == 0) {
                ucLCDBacklightOnFlag = 1;
                BACK_ONOFF(ON);
            }
            usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();
        }
    }

    // Display Date and Time at Initial Status

    void DisplayDateTime(_tDATE_TIME * dt) {
        int i;
        char temp[17];
        _tDATE_TIME dt1;

        dt1 = *dt;
        if (ucLangFlag) {
            // Convert the Gregorian calendar to the Jalali(Moslem) calendar
            RTC_Gregorian2Jalali(&dt1);
        }

        i = ((dt1.CLKMONTH >> 4) & 0x0F) * 10;
        i += dt1.CLKMONTH & 0x0F;
        sprintf(temp, "%02X%s,%02X%02X %02X:%02X",
                dt1.CLKDATE,
                Month12[i - 1],
                dt1.CLKYEARH,
                dt1.CLKYEARL,
                dt1.CLKHOUR,
                dt1.CLKMIN);
        LCD_DisplayString(DATETIME_DISPLAY_LINE, 0, strlen(temp), temp, ucLangFlag);
    }

    // Display YYYYMMDD at Set Date

    void DisplayYYYYMMDD(_tDATE_TIME *dt, char mode) {
        char temp[17];
        _tDATE_TIME dt1;

        dt1 = *dt;
        if (mode == JALALI_CALENDAR) {
            // Convert the Gregorian calendar to the Jalali(Moslem) calendar
            RTC_Gregorian2Jalali(&dt1);
        }

        sprintf(temp, "%02X%02X%02X%02X", dt1.CLKYEARH, dt1.CLKYEARL, dt1.CLKMONTH, dt1.CLKDATE);
        LCD_DisplayString(2, 4, strlen(temp), temp, ucLangFlag);

        ucTempMin = dt->CLKMIN;
        ucTempSec = dt->CLKSEC;
    }

    // Display hhmmss at Set Time

    void Displayhhmmss(_tDATE_TIME * dt) {
        char temp[17];

        sprintf(temp, "%02X%02X%02X", dt->CLKHOUR, dt->CLKMIN, dt->CLKSEC);
        LCD_DisplayString(2, 4, strlen(temp), temp, ucLangFlag);

        ucTempMin = dt->CLKMIN;
        ucTempSec = dt->CLKSEC;
    }

    // Initialize RTC date and time

    void InitializeRTCDateTime(void) {
        char temp[17];

        strcpy(temp, "20000101000000"); // January 1, 2000 00:00:00
        RTC_SetDateTime(temp, GREGORIAN_CALENDAR);
        RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
    }

    // Set RTC date and time when power is turned on

    void SetRTCDateTimeWhenPowerIsTurnedOn(void) {
        int i, j, key, ret;
        char temp[17];

        // "Please replace a", "RTC backup      ", "battery with a  ", "new one         "
        LCDDisplay4Lines(M4BackupBatErrMsg_01, -1, ucLangFlag);
        for (i = 0; i < 3; i++) {
            Beep_EventSound(ERROR_TONE);
            TIMER_Wait1MS(1500);
        }

        while (1) {
#if 0 // sispp 20111013
            // "Set Date        ", "1.Iranian Year  ", "2.Christian Year", "                "
            LCDDisplay4Lines(M4SelectCalendar_001, LCD_LINE1, ucLangFlag);
            SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelectCalendar_002]);
            while (1) {
                key = KEYSCAN() & 0xFF;
                if (key != BTKEY_NULL) {
                    if (key != BTKEY_ENTER && key != BTKEY_CANCEL) {
                        MenuScrollUpDown(sStartDisplayMenuLine, &sSelectedMenuItemNo, &sSelectedMenuItemLine, sTotalMenuItemNo, psz17FirstMenuItemMsgAddr, key, ucLangFlag);
                        if (key >= BTKEY_1 && key <= sTotalMenuItemNo) {
                            key = BTKEY_ENTER;
                        }
                    }
                    if (key == BTKEY_ENTER) {
                        if (sSelectedMenuItemNo == BTKEY_1) {
                            // "Iranian Year    ", "    YYYYMMDD    ", "                ", "=>              "
                            LCDDisplay4Lines(M4IranianYear_000001, -1, ucLangFlag);
                            j = 1;
                        } else {
                            // "Christian Year  ", "    YYYYMMDD    ", "                ", "=>              "
                            LCDDisplay4Lines(M4ChristianYear_0001, -1, ucLangFlag);
                            j = 0;
                        }
                        memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                        ucKeyCnt = 0;
                        cYPos = 3;
                        cXPos = 4;
                        LCD_CursorOn(cYPos, cXPos);
                        break;
                    }
                }
            }
#endif
            // "Christian Year  ", "    YYYYMMDD    ", "                ", "=>              "
            LCDDisplay4Lines(M4ChristianYear_0001, -1, ucLangFlag);
            LCD_DisplayString(0, 0, 16, "Set Date        ", ucLangFlag);
            j = 0;
            memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
            ucKeyCnt = 0;
            cYPos = 3;
            cXPos = 4;
            LCD_CursorOn(cYPos, cXPos);

            while (1) {
                key = KEYSCAN() & 0xFF;
                if (key != BTKEY_NULL) {
                    if (key != BTKEY_ENTER && key != BTKEY_CANCEL) {
                        if (j) {
                            KEY_InputIranianDate(cYPos, cXPos, key, c65TempKeyBuf, ucLangFlag);
                        } else {
                            KEY_InputChristianDate(cYPos, cXPos, key, c65TempKeyBuf, ucLangFlag);
                        }
                    } else if (key == BTKEY_ENTER) {
                        if (strlen(c65TempKeyBuf) == 8) {
                            strcpy(temp, c65TempKeyBuf);
                            ret = 0;
                            break;
                        }
                    } else if (key == BTKEY_CANCEL) {
                        ret = 1;
                        break;
                    }
                }
            }

            if (ret) {
                continue;
            } else {
                break;
            }
        }

        // "Set Time        ", "    hhmmss      ", "                ", "=>              "
        LCDDisplay4Lines(M4SetTime_0000000001, -1, ucLangFlag);
        memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
        ucKeyCnt = 0;
        cYPos = 3;
        cXPos = 4;
        LCD_CursorOn(cYPos, cXPos);
        while (1) {
            key = KEYSCAN() & 0xFF;
            if (key != BTKEY_NULL) {
                if (key != BTKEY_ENTER && key != BTKEY_CANCEL) {
                    KEY_InputTime(cYPos, cXPos, key, c65TempKeyBuf, ucLangFlag);
                } else if (key == BTKEY_ENTER) {
                    if (strlen(c65TempKeyBuf) == 6) {
                        break;
                    }
                }
            }
        }

        strcat(temp, c65TempKeyBuf);
        RTC_SetDateTime(temp, j);
        RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
    }

    /* Converts Gregorian date to seconds since 1970-01-01 00:00:00.
     * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
     * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
     *
     * [For the Julian calendar (which was used in Russia before 1917,
     * Britain & colonies before 1752, anywhere else before 1582,
     * and is still in use by some communities) leave out the
     * -year/100+year/400 terms, and add 10.]
     *
     * This algorithm was first published by Gauss (I think).
     *
     * WARNING: this function will overflow on 2106-02-07 06:28:16 on
     * machines where long is 32-bit! (However, as time_t is signed, we
     * will already get problems at other places on 2038-01-19 03:14:08)
     */
    unsigned long
    mktime(const unsigned int year0, const unsigned int mon0,
            const unsigned int day, const unsigned int hour,
            const unsigned int min, const unsigned int sec) {
        unsigned int mon = mon0, year = year0;

        /* 1..12 -> 11,12,1..10 */
        if (0 >= (int) (mon -= 2)) {
            mon += 12; /* Puts Feb last since it has leap day */
            year -= 1;
        }

        return ((((unsigned long)
                (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + day) +
                year * 365 - 719499
                )*24 + hour /* now have hours */
                )*60 + min /* now have minutes */
                )*60 + sec; /* finally seconds */
    }

    U32 GetULDateTime() {
        _tDATE_TIME dt;
        int year, month, date, hour, min, sec;

        RTC_GetDateTime(&dt, GREGORIAN_CALENDAR);

        year = ((dt.CLKYEARH >> 4) & 0x0F)*1000 + (dt.CLKYEARH & 0x0F)*100 + ((dt.CLKYEARL >> 4) & 0x0F)*10 + (dt.CLKYEARL & 0x0F);
        month = ((dt.CLKMONTH >> 4) & 0x01)*10 + (dt.CLKMONTH & 0x0F);
        date = ((dt.CLKDATE >> 4) & 0x03)*10 + (dt.CLKDATE & 0x0F);
        hour = ((dt.CLKHOUR >> 4) & 0x0F)*10 + (dt.CLKHOUR & 0x0F);
        min = ((dt.CLKMIN >> 4) & 0x0F)*10 + (dt.CLKMIN & 0x0F);
        sec = ((dt.CLKSEC >> 4) & 0x0F)*10 + (dt.CLKSEC & 0x0F);

        return mktime(year, month, date, hour, min, sec);
    }

    /* */
