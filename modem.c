
/*======================================================================*/
/*																		*/
/*								MODEM.C									*/
/*																		*/
/*======================================================================*/

#include "system.h"
#include "extern.h"


const char DISCONNECT_TBL[] ={
    '\r', '\n', 'N', 'O', ' ', 'C', 'A', 'R', 'R', 'I', 'E', 'R', '\r', '\n'
};


#ifdef AUTO_MODEM_TEST
unsigned short usModemAutoTest10MSTimer;
#endif

// Common Variables
int iRxCnt; // Rx counter
int iRxSize; // Rx data size
int iTxSize; // Tx data size
unsigned char ucReqDataReadyFlag; // Request data ready flag
unsigned char ucReqDataTxFlag; // Request data transmitted flag
unsigned char ucDisconnectCnt; // Check disconnection counter
unsigned char ucTrxnRxBuf[8192]; // Transaction Rx data buffer
unsigned char ucTrxnTxBuf[8192]; // Transaction Tx data buffer
unsigned char ucRxBuf[8192]; // Rx data buffer
unsigned char ucTxBuf[8192]; // Tx data buffer
unsigned char ucRxTempBuf[8192]; // Rx temporary data buffer
unsigned char ucTxTempBuf[8192]; // Tx temporary data buffer


void ModemTask(void);
int GetConnectionConditions(unsigned char com_device, int trxn_mode, int check_paper);
void DisplayConnectionErrorCondition(int err_condition);
void DisplayConnectionErrorConditionAndGotoInitialStatus(int err_condition);
BOOL GetTrxnMenuActiveStatus(void);
void ModemOpen(char pre_connect);
void ModemClose(void);
BOOL CheckDisconnect(int rxdata);
void AbnormalProcessingBeforeTx(void);
void AbnormalProcessingAfterTx(void);
void OnlineTrxnResultProcessing(void);

/* Modem task */
void ModemTask(void) {
    GprsTask();
    if (ucTMSDownloadFlag && iTMS_ProcessStep > 0) {
        TMSDownloadTask(st_POSSetupInfo.ucComDevice, GPRS_COM_PORT);
    }
}

/*
Get Connection Conditions
        Input
                com_device
                        0: dial-up Modem, 1: LAN, 2: GSM
                trxn_mode
                        0: transaction mode, 1: EOD, 2: Request Black List, 3: TMS mode, 4: Call Home
                check_paper (It is available when trxn_mode is 0)
                        0: Does not check paper, 1: Check paper
	
        return values
                -2: SIM Error
                -1: GSM module doesn't response
                 0: OK
                 1: No Terminal ID
                 2: No Merchant ID
                 3: No Transaction Telephone number
                 4: No EOD Telephone number
                 5: No Black List Telephone number
                 6: No TMS Telephone number
                 7: No Local IP address
                 8: No Subnet Mask
                 9: No Gateway
                10: No Local port number(0-65535)
                11: No Local Timeout(0-6000 sec)
                12: No Transaction Server IP address
                13: No Transaction Server port number(0-65535)
                14: No EOD Server IP address
                15: No EOD Server port number(0-65535)
                16: No Black List Server IP address
                17: No Black List Server port number(0-65535)
                18: No TMS Server IP address
                19: No TMS Server port number(0-65535)
                20: No Paper (except Reversal Transaction)
 */
int GetConnectionConditions(unsigned char com_device, int trxn_mode, int check_paper) {
    int i, max_line;
    long ltemp;

    // Check Terminal ID
    if (strlen(st_POSSetupInfo.sz9TerminalID) != 8) {
        return 1;
    }
    /*
            // Check Merchant ID
            if (strlen(st_POSSetupInfo.sz16MerchantID) == 0) {
                    return 2;
            }
     */
    max_line = 0;

    // Check GSM module status
    if (ucGprsModuleOkFlag == 0) {
        return -1;
    }

    // Check SIM status
    if (ucGprsSIMStatus != SIM_CHECK && ucGprsSIMStatus != SIM_READY) {
        return -2;
    }

    ucGprsMaxConnectCnt = 0;
    if (trxn_mode == 0 || trxn_mode == 4) {
        if (strlen(st_POSSetupInfo.sz16TrxnServerIP[0]) == 0 ||
                strlen(st_POSSetupInfo.sz6TrxnServerPortNo[0]) == 0) {
            return 3;
        }
    } else if (trxn_mode == 3) {
        if (strlen(st_POSSetupInfo.sz16TMSServerIP[0]) == 0 ||
                strlen(st_POSSetupInfo.sz6TMSServerPortNo[0]) == 0) {
            return 6;
        }
    }

    /*
            if (trxn_mode == 0) {
                    // Check Transaction Telephone number
                    for (i = 0; i < DIALUP_TRXN_MAX_LINE; i++) {
                            if (strlen(st_POSSetupInfo.sz17TrxnTelNo[i]) == 0) {
                                    break;
                            }
                            max_line++;
                    }
            }
            else if (trxn_mode == 1) {
                    // Check EOD Telephone number
                    for (i = 0; i < DIALUP_EOD_MAX_LINE; i++) {
                            if (strlen(st_POSSetupInfo.sz17EODTelNo[i]) == 0) {
                                    break;
                            }
                            max_line++;
                    }
            }
            else if (trxn_mode == 2) {
                    // Check Request Black List Telephone number
                    for (i = 0; i < DIALUP_BLIST_MAX_LINE; i++) {
                            if (strlen(st_POSSetupInfo.sz17BListTelNo[i]) == 0) {
                                    break;
                            }
                            max_line++;
                    }
            }
            else {
                    // Check TMS Telephone number
                    for (i = 0; i < DIALUP_TMS_MAX_LINE; i++) {
                            if (strlen(st_POSSetupInfo.sz17TMSTelNo[i]) == 0) {
                                    break;
                            }
                            max_line++;
                    }
            }
            if (max_line == 0) {
                    ucGprsMaxConnectCnt = 0;
                    if (trxn_mode == 0) {
                            return 3;
                    }
                    else if (trxn_mode == 1) {
                            return 4;
                    }
                    else if (trxn_mode == 2) {
                            return 5;
                    }
                    else {
                            return 6;
                    }
            }
            else {
                    ucGprsMaxConnectCnt = max_line * GPRS_MAX_CONNECT_COUNT;
            }
     */
    //ucGprsMaxConnectCnt = 2 * GPRS_MAX_CONNECT_COUNT;
    ucGprsMaxConnectCnt = 1 * GPRS_MAX_CONNECT_COUNT;

    if (!trxn_mode && check_paper) {
        // NO PAPER?
        if (!DetectPaper()) {
            return 20;
        }
    }

    return 0;
}

void DisplayConnectionErrorCondition(int err_condition) {
    if (err_condition == -1) {
        LCD_ClearScreen();
        // "????????????????", "   GSM module   ", "doesn't response", "                "
        LCDDisplay4Lines(M4GSMNoResponse_0001, -1, ucLangFlag);
    } else if (err_condition == -2) {
        LCD_ClearScreen();
        GprsDisplaySIMErrorMessage();
    } else {
        // "                ", "No Terminal ID  ", "                ", "                "
        LCDDisplay4Lines(M4NoTerminalID_00001 + err_condition - 1, -1, ucLangFlag);
    }
}

void DisplayConnectionErrorConditionAndGotoInitialStatus(int err_condition) {
    if (err_condition == -1) {
        LCD_ClearScreen();
        // "????????????????", "   GSM module   ", "doesn't response", "                "
        ErrorDisplayAndGoInitialStatus(M4GSMNoResponse_0001, -1, ucLangFlag);
    } else if (err_condition == -2) {
        LCD_ClearScreen();
        GprsDisplaySIMErrorMessage();
        // "????????????????", "????????????????", "????????????????", "????????????????"
        ErrorDisplayAndGoInitialStatus(M4_____________Dummy, -1, ucLangFlag);
    } else {
        // "                ", "No Terminal ID  ", "                ", "                "
        ErrorDisplayAndGoInitialStatus(M4NoTerminalID_00001 + err_condition - 1, -1, ucLangFlag);
    }
}

/*
BOOL GetTrxnMenuActiveStatus(void)
{
        int i, j, k, len;
        unsigned short trxn_menu;
	
        trxn_menu = 0;
        if (st_POSSetupInfo.ucBuyActiveFlag) {
                trxn_menu |= 0x01;
        }
        if (st_POSSetupInfo.ucBuyWithExtraActiveFlag) {
                trxn_menu |= 0x02;
        }
        if (st_POSSetupInfo.ucBuyExtPrnActiveFlag) {
                trxn_menu |= 0x04;
        }
        if (st_POSSetupInfo.ucBalanceActiveFlag) {
                trxn_menu |= 0x08;
        }
        if (st_POSSetupInfo.ucBillPaymentActiveFlag) {
                trxn_menu |= 0x10;
        }
        if (st_POSSetupInfo.ucCheckBillPaymentActiveFlag) {
                trxn_menu |= 0x20;
        }
        if (st_POSSetupInfo.ucSIMChargeActiveFlag) {
                trxn_menu |= 0x40;
        }
	
        if (trxn_menu == 0) {
                // "                ", "Transaction menu", "is not active   ", "                "
                ErrorDisplayAndGoInitialStatus(M4TrxnMenuNotActive1, -1, ucLangFlag);
                return FALSE;
        }
        else {
                memset(c9ActiveTrxnMenuType, 0x00, sizeof(c9ActiveTrxnMenuType));
                memset(sz17ActiveTrxnMenuMsg, 0x00, sizeof(sz17ActiveTrxnMenuMsg));
                for (i = 0, j = 0; i < 7; i++) {
                        if (trxn_menu & 0x01) {
                                c9ActiveTrxnMenuType[j] = i;
                                // " .Buy           ",
                                strcpy(sz17ActiveTrxnMenuMsg[j], (char *)LCD_MSG_TBL1[ucLangFlag][M1TrxnMenu_000000001+i]);
                                // Insert Item No.
                                if (ucLangFlag == 0) {
                                        sz17ActiveTrxnMenuMsg[j][0] = j + '1';
                                }
                                else {
                                        sz17ActiveTrxnMenuMsg[j][15] = j + '1';
                                        IndianNo2FarsiNo(&sz17ActiveTrxnMenuMsg[j][15], 1);
                                }
                                j++;
                        }
                        trxn_menu >>= 1;
                }
		
                if (j == 1) {
                        // "????????????????", "????????????????", "????????????????", "????????????????"
                        MainStatusSetting(MSS_CUSTOMER_TRANS, MST_CUSTOMER_TRANS, M4_____________Dummy, -1, ucLangFlag);
                        sSelectedMenuItemNo = 1;
                        pusServiceAddr++;
                        sVirtualKey = BTKEY_ENTER;
                }
                else {
                        // "Customer Trans. ", "                ", "                ", "                "
                        MainStatusSetting(MSS_CUSTOMER_TRANS, MST_CUSTOMER_TRANS, M4CustomerTrxnMenu_1, -1, ucLangFlag);
                        if (j < 4) {
                                k = j;
                        }
                        else {
                                k = 3;
                        }
                        for (i = 0; i < k; i++) {
                                LCD_DisplayLine(i+1, LEFT_JUSTIFIED, sz17ActiveTrxnMenuMsg[i], ucLangFlag);
                        }
                        LCD_HighlightLineOn(1);
                        SetMenuScrollUpDownInfo(1, 1, 1, j, sz17ActiveTrxnMenuMsg[0]);
                        pusServiceAddr++;
                }
		
                return TRUE;
        }
}
 */
BOOL GetTrxnMenuActiveStatus(void) {
    int i, j, k, len;
    unsigned short trxn_menu;

    trxn_menu = 0;
    if (st_POSSetupInfo.ucBuyActiveFlag) {
        trxn_menu |= 0x01;
    }
    if (st_POSSetupInfo.ucBalanceActiveFlag) {
        trxn_menu |= 0x04;
    }

    trxn_menu |= 0x01; // Purchase
    //trxn_menu |= 0x02;	// Recharge
    trxn_menu |= 0x04; // Balance

    if (trxn_menu == 0) {
        // "                ", "Transaction menu", "is not active   ", "                "
        ErrorDisplayAndGoInitialStatus(M4TrxnMenuNotActive1, -1, ucLangFlag);
        return FALSE;
    } else {
        memset(c9ActiveTrxnMenuType, 0x00, sizeof (c9ActiveTrxnMenuType));
        memset(sz17ActiveTrxnMenuMsg, 0x00, sizeof (sz17ActiveTrxnMenuMsg));
        for (i = 0, j = 0; i < 7; i++) {
            if (trxn_menu & 0x01) {
                c9ActiveTrxnMenuType[j] = i;

                // " .Purchase      ",
                strcpy(sz17ActiveTrxnMenuMsg[j], (char *) LCD_MSG_TBL1[ucLangFlag][M1TrxnMenu_000000001 + i]);

                // Insert Item No.
                sz17ActiveTrxnMenuMsg[j][0] = j + '1';

                j++;
            }
            trxn_menu >>= 1;
        }

        if (j == 1) {
            // "????????????????", "????????????????", "????????????????", "????????????????"
            MainStatusSetting(MSS_CUSTOMER_TRANS, MST_CUSTOMER_TRANS, M4_____________Dummy, -1, ucLangFlag);
            sSelectedMenuItemNo = 1;
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
        } else {
            // "Customer Trans. ", "                ", "                ", "                "
            MainStatusSetting(MSS_CUSTOMER_TRANS, MST_CUSTOMER_TRANS, M4CustomerTrxnMenu_1, -1, ucLangFlag);
            if (j < 4) {
                k = j;
            } else {
                k = 3;
            }
            for (i = 0; i < k; i++) {
                LCD_DisplayLine(i + 1, LEFT_JUSTIFIED, sz17ActiveTrxnMenuMsg[i], ucLangFlag);
            }
            LCD_HighlightLineOn(1);
            SetMenuScrollUpDownInfo(1, 1, 1, j, sz17ActiveTrxnMenuMsg[0]);
            pusServiceAddr++;
        }

        return TRUE;
    }
}

/*
Open modem
        Input
                pre_connect
                        0: Normal connection, 1: Pre-connection
 */
void ModemOpen(char pre_connect) {
#ifdef USER_DEBUG
    Rprintf("ModemOpen\r\n");
#endif
    if (pre_connect) {
        if (st_POSSetupInfo.ucPreDialingFlag) {
            GprsOpen();
        }
    } else {
        GprsOpen();
    }
}

/* Close modem */
void ModemClose(void) {
#ifdef USER_DEBUG
    Rprintf("ModemClose\r\n");
#endif
    if (usGprsTaskStep == 81 || usGprsTaskStep >= 200) {
        GprsDisconnect(0);
    } else if (usGprsTaskStep > 72) {
        GprsDisconnect(1);
    } else {
        usGprsTaskStep = 0;
    }

    if (ucGprsPowerOffFlag) {
        GprsPowerOff();
    }
}

/*
Check disconnection
        Input
                rxdata
                        received data
	
        Return Value
                0: Not disconnected, 1: Disconnected
 */
BOOL CheckDisconnect(int rxdata) {
    if (rxdata == DISCONNECT_TBL[ucDisconnectCnt]) {
        ucDisconnectCnt++;
        if (ucDisconnectCnt >= 14) {
            ucDisconnectCnt = 0;
            return TRUE;
        }
    } else if (rxdata == DISCONNECT_TBL[0]) {
        ucDisconnectCnt = 1;
    } else {
        ucDisconnectCnt = 0;
    }

    return FALSE;
}

/* Abnormal processing before transmission */
void AbnormalProcessingBeforeTx(void) {
    ModemClose();

#ifdef USER_DEBUG
    Rprintf("AbnormalProcessingBeforeTx: RF=%d, RRC=%d, RRTPC=%d\r\n", ucReversalFlag, ucReversalRetryCnt, ucReversalRetryTimePerCnt);
#endif
    if (ucReversalFlag == 1) {
        TIMER_WaitKeyPress1MS(5000);
        ucReversalRetryTimePerCnt++;
        if (ucReversalRetryTimePerCnt < 3) {
            PerformReversalTransaction();
        } else {
            ucReversalRetryCnt++;
            ucReversalRetryTimePerCnt = 0;
            if (ucReversalRetryCnt < 3) {
                // Go to Reversal Mode
                GotoReversalMode();
            } else {
                ucReversalRetryCnt = 0;
                PrintUnsuccessfulReversalReceipt();
            }
        }
        return;
    }

    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
        TIMER_WaitKeyPress1MS(5000);
        ucReqDataReadyFlag = 0;
        sVirtualKey = BTKEY_CANCEL;
    }
}

/* Abnormal processing after transmission */
void AbnormalProcessingAfterTx(void) {
    ModemClose();

    // Purchase transaction�� ������ reversal�� �ؾ��ϴ��� �Ǵ� --> Purchase�� ���� ucReversalFlag=1
    // else ucReversalFlag=0 && �Ϲ�Ʈ�����
#ifdef USER_DEBUG
    Rprintf("AbnormalProcessingAfterTx: pstfLastTrxnLog=%p, pstfSavingTrxnLog=%p\r\n", pstfLastTrxnLog, pstfSavingTrxnLog);
#endif
    if (pstfSavingTrxnLog->usTrxnType == TRXN_PURCHASE_ONLY &&
            pstfSavingTrxnLog->ucStatus.BIT.ReversalFlag == 1 &&
            pstfSavingTrxnLog->ucStatus.BIT.EODTxFlag == 1) {
        ucReversalFlag = 1;
        //pstfSavingTrxnLog = pstfLastTrxnLog;
    }

#ifdef USER_DEBUG
    Rprintf("AbnormalProcessingAfterTx: RF=%d, RRC=%d, RRTPC=%d\r\n", ucReversalFlag, ucReversalRetryCnt, ucReversalRetryTimePerCnt);
#endif
    if (ucReversalFlag == 1) {
        TIMER_WaitKeyPress1MS(5000);
        ucReversalRetryTimePerCnt++;
        if (ucReversalRetryTimePerCnt < 3) {
            PerformReversalTransaction();
        } else {
            ucReversalRetryCnt++;
            ucReversalRetryTimePerCnt = 0;
            if (ucReversalRetryCnt < 3) {
                // Go to Reversal Mode
                GotoReversalMode();
            } else {
                ucReversalRetryCnt = 0;
                PrintUnsuccessfulReversalReceipt();
            }
        }
    } else {
        TIMER_WaitKeyPress1MS(5000);
        sVirtualKey = BTKEY_CANCEL;
    }
}

extern char sz17TrxnTitle[17];
extern int isDetectCard;
extern char gbEmvScTaskStep;
#define Tvb_TrmScript (int)0x17
extern int pgbAppBufUpdate(int uTag, int uLen, U08 *uDat);

/* Online transaction result processing */
void OnlineTrxnResultProcessing(void) {
    int i, len;
    int iStopProcFlag;
    char temp[256];

#ifdef USER_DEBUG
    Rprintf("OnlineTrxnResultProcessing\r\n");
#endif
    if (st_ErrRespData.iErrFlag == 1) {
        LCD_ClearScreen();
        LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
        memset(temp, 0x00, sizeof (temp));
        sprintf(temp, "%s: %s", st_ErrRespData.sz4ErrCode, st_ErrRespData.sz49ErrMsg);
        len = strlen(temp);
        LCD_DisplayLine(1, LEFT_JUSTIFIED, temp, 0);
        if (len > 16) {
            LCD_DisplayLine(2, LEFT_JUSTIFIED, &temp[16], 0);
        }
        if (len > 32) {
            LCD_DisplayLine(3, LEFT_JUSTIFIED, &temp[32], 0);
        }

        if (giTransactionType != TRXN_TAMS_CALLHOME) {
            sVirtualKey = BTKEY_CANCEL;
        } else {
            Beep_EventSound(OK_TONE);
            ucLCDBacklightOnFlag = 1;
            BACK_ONOFF(ON);
            usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();
            pusServiceAddr = (unsigned short *) &tbl_MainService[MST_INITIAL][1];
        }
    } else if (giTransactionType == TRXN_BANK_EFTTRAN) {
        // �����̸� �����޼��� ���÷����ϰ� ��?
        LCD_ClearScreen();
        LCD_DisplayLine(0, LEFT_JUSTIFIED, st_TrxnRespData.sz4StatusCode, 0);
        LCD_DisplayLine(1, LEFT_JUSTIFIED, st_TrxnRespData.sz33Message, 0);
        if (strlen(st_TrxnRespData.sz33Message) > 16) {
            LCD_DisplayLine(2, LEFT_JUSTIFIED, &st_TrxnRespData.sz33Message[16], 0);
        }
        if (st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY && !strcmp(st_TrxnRespData.sz33Message, "No response from Acquirer")) {
            AbnormalProcessingAfterTx();
            ucReqDataTxFlag = 0;
            return;
        }

        if (isDetectCard == 2 && gbEmvScTaskStep == 99) {
            len = strlen(st_TrxnRespData.sz512IccResponse);
            if (len) {
                str_to_bcd(temp, st_TrxnRespData.sz512IccResponse, len);
                len = (len + 1) / 2;
                pgbAppBufUpdate(Tvb_TrmScript, len, temp);
            }
            gbEmvScTaskStep = 100;
        }

        iStopProcFlag = 1;
        switch (st_TrxnReqData.usTrxnType) {
            case TRXN_PURCHASE_ONLY:
            case TRXN_REVERSAL:
                if (ucReversalFlag == 1) {
                    // if Approved or Transaction not found
                    i = atoi(st_TrxnRespData.sz4StatusCode);
                    //   0 - OK
                    // 302 - Transaction Not Found
                    // 322 - Reversal transaction not allowed
                    // 328 - Transaction already reversed
                    if (i == 0 || i == 302 || i == 322 || i == 328) {
                        SaveReversalTransactionLog(pstfSavingTrxnLog);
                        ucReversalFlag = 0;
                    } else {
                        // ????? reversal ����
                        break;
                    }
                } else {
                    SaveRxTransactionLog();
                }
                //if(st_TrxnReqData.usTrxnType == TRXN_REVERSAL)
                //	break;
            case TRXN_BALANCE_INQUIRY:
                if (st_TrxnRespData.ucResult == '1') {
                    iStopProcFlag = 0;
                    pusServiceAddr++;
                    if (gbEmvScTaskStep <= 0) {
                        sVirtualKey = BTKEY_ENTER;
                    }
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ProcessingMsg_0001], 0);
                }
                break;
        }
#ifdef USER_DEBUG
        Rprintf("iStopProcFlag=%d, sVirtualKey=%d\r\n", iStopProcFlag, sVirtualKey);
#endif
        if (iStopProcFlag == 1) {
            Beep_EventSound(OK_TONE);
            ucLCDBacklightOnFlag = 1;
            BACK_ONOFF(ON);
            usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();
            pusServiceAddr = (unsigned short *) &tbl_MainService[MST_INITIAL][1];
        }
    } else if (giTransactionType == TRXN_DOWNLOAD_ALL_PARAMETER || giTransactionType == TRXN_DOWNLOAD_APPLIST ||
            giTransactionType == TRXN_DOWNLOAD_FUNCLIST || giTransactionType == TRXN_DOWNLOAD_MASTERKEY ||
            giTransactionType == TRXN_DOWNLOAD_SESSIONKEY || giTransactionType == TRXN_DOWNLOAD_PARAM ||
            giTransactionType == TRXN_DOWNLOAD_EFTPARAMS || giTransactionType == TRXN_DOWNLOAD_BINTABLE ||
            giTransactionType == TRXN_DOWNLOAD_EMVAPP || giTransactionType == TRXN_DOWNLOAD_EMVCAPK ||
            giTransactionType == TRXN_DOWNLOAD_EMVREVOKECAPK || giTransactionType == TRXN_DOWNLOAD_HOTCARDS) {
        LCD_ClearScreen();
        LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadSuccess_01], 0);

        Beep_EventSound(OK_TONE);
        ucLCDBacklightOnFlag = 1;
        BACK_ONOFF(ON);
        usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();
        pusServiceAddr++;
    } else if (giTransactionType == TRXN_TAMS_CALLHOME) {
        LCD_ClearScreen();
        if (usMainStatus == MSS_SPECIAL_FUNC) {
            LCD_DisplayLine(2, LEFT_JUSTIFIED, "   Modem OK!    ", ucLangFlag);
        } else {
            LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
            LCD_DisplayLine(2, LEFT_JUSTIFIED, "CallHome Success", ucLangFlag);
            // Save Last Call Home Time
            tPOSUtilBuf.ulLastCallHomeTime = GetULDateTime();
#ifdef USER_DEBUG
            Rprintf("TRXN_TAMS_CALLHOME: ulLastCallHomeTime = %ld\r\n", tPOSUtilBuf.ulLastCallHomeTime);
#endif
            SavePOSUtilBuf();
        }
        sVirtualKey = BTKEY_CANCEL;
    } else if (giTransactionType == TRXN_BANK_EFTTOTAL) {
        LCD_ClearScreen();
        LCD_DisplayLine(0, LEFT_JUSTIFIED, st_TrxnRespData.sz4StatusCode, 0);
        LCD_DisplayLine(1, LEFT_JUSTIFIED, st_TrxnRespData.sz33Message, 0);
        if (strlen(st_TrxnRespData.sz33Message) > 16) {
            LCD_DisplayLine(2, LEFT_JUSTIFIED, &st_TrxnRespData.sz33Message[16], 0);
        }

        iStopProcFlag = 1;
        if (st_TrxnRespData.ucResult == '0' || !strcmp(st_TrxnRespData.sz4StatusCode, "100")) {
            LCD_DisplayLine(1, LEFT_JUSTIFIED, "OK", 0);
            if (st_TrxnRespData.usTrxnBatchNo != tPOSUtilBuf.usBatchNo) {
                // �ܸ����� Batch Number�� ���� Batch Number�� Ʋ���� ���� ������ ����, Sequence Number�� �ʱ�ȭ
                sprintf(temp, "New BatchNo:%4d", st_TrxnRespData.usTrxnBatchNo);
                LCD_DisplayLine(2, LEFT_JUSTIFIED, temp, 0);

                tPOSUtilBuf.usBatchNo = st_TrxnRespData.usTrxnBatchNo;
                tPOSUtilBuf.usSeqNo = 0;
                SavePOSUtilBuf();
                // Batch Printing��? - Request/Response Data�� �̿��ؼ� Printing
                EraseAllTransactionLog();

                iStopProcFlag = 0;
                pusServiceAddr++;
                sVirtualKey = BTKEY_ENTER;
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ProcessingMsg_0001], 0);
            } else {
                LCD_DisplayLine(2, LEFT_JUSTIFIED, "Batch Number is ", 0);
                LCD_DisplayLine(3, LEFT_JUSTIFIED, "Not Changed!    ", 0);
            }
        } else {
            LCD_DisplayLine(1, LEFT_JUSTIFIED, "Exception", 0);
        }

        if (iStopProcFlag == 1) {
            Beep_EventSound(OK_TONE);
            ucLCDBacklightOnFlag = 1;
            BACK_ONOFF(ON);
            usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();
            pusServiceAddr = (unsigned short *) &tbl_MainService[MST_INITIAL][1];
        }
    }

    ModemClose();
    ucGprsConnectCnt = 0;
    ucReqDataTxFlag = 0;
    ucReqDataReadyFlag = 0;

}

/* */
