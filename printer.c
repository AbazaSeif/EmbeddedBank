
#include "system.h"
#include "extern.h"

extern PARAMS *pstParams; // 2K


const _st_PrintErrorMsg_ PrintErrorMsg[52] = {
    { 1, P1ErrorCode02_000001, 0}, // 0x3032
    { 1, P1ErrorCode03_000001, 0}, // 0x3033
    { 1, P1ErrorCode06_000001, 0}, // 0x3036
    { 2, P1ErrorCode12_000001, P1ErrorCode12_000002}, // 0x3132
    { 1, P1ErrorCode13_000001, 0}, // 0x3133
    { 1, P1ErrorCode14_000001, 0}, // 0x3134
    { 1, P1ErrorCode15_000001, 0}, // 0x3135
    { 1, P1ErrorCode16_000001, 0}, // 0x3136
    { 1, P1ErrorCode19_000001, 0}, // 0x3139
    { 2, P1ErrorCode24_000001, P1ErrorCode24_000002}, // 0x3234
    { 1, P1ErrorCode25_000001, 0}, // 0x3235
    { 2, P1ErrorCode29_000001, P1ErrorCode29_000002}, // 0x3239
    { 1, P1ErrorCode30_000001, 0}, // 0x3330
    { 1, P1ErrorCode33_000001, 0}, // 0x3333
    { 2, P1ErrorCode34_000001, P1ErrorCode34_000002}, // 0x3334
    { 1, P1ErrorCode40_000001, 0}, // 0x3430
    { 2, P1ErrorCode41_000001, P1ErrorCode41_000002}, // 0x3431
    { 2, P1ErrorCode43_000001, P1ErrorCode43_000002}, // 0x3433
    { 2, P1ErrorCode44_000001, P1ErrorCode44_000002}, // 0x3434
    { 1, P1ErrorCode48_000001, 0}, // 0x3438
    { 1, P1ErrorCode51_000001, 0}, // 0x3531
    { 1, P1ErrorCode55_000001, 0}, // 0x3535
    { 1, P1ErrorCode56_000001, 0}, // 0x3536
    { 1, P1ErrorCode57_000001, 0}, // 0x3537
    { 1, P1ErrorCode60_000001, 0}, // 0x3630
    { 2, P1ErrorCode61_000001, P1ErrorCode61_000002}, // 0x3631
    { 2, P1ErrorCode62_000001, P1ErrorCode62_000002}, // 0x3632
    { 2, P1ErrorCode64_000001, P1ErrorCode64_000002}, // 0x3634
    { 2, P1ErrorCode65_000001, P1ErrorCode65_000002}, // 0x3635
    { 2, P1ErrorCode66_000001, P1ErrorCode66_000002}, // 0x3636
    { 1, P1ErrorCode68_000001, 0}, // 0x3638
    { 2, P1ErrorCode70_000001, P1ErrorCode70_000002}, // 0x3730
    { 2, P1ErrorCode71_000001, P1ErrorCode71_000002}, // 0x3731
    { 2, P1ErrorCode75_000001, P1ErrorCode75_000002}, // 0x3735
    { 1, P1ErrorCode77_000001, 0}, // 0x3737
    { 1, P1ErrorCode78_000001, 0}, // 0x3738
    { 1, P1ErrorCode79_000001, 0}, // 0x3739
    { 2, P1ErrorCode80_000001, P1ErrorCode80_000002}, // 0x3830
    { 1, P1ErrorCode81_000001, 0}, // 0x3831
    { 1, P1ErrorCode83_000001, 0}, // 0x3833
    { 1, P1ErrorCode84_000001, 0}, // 0x3834
    { 1, P1ErrorCode85_000001, 0}, // 0x3835
    { 2, P1ErrorCode86_000001, P1ErrorCode86_000002}, // 0x3836
    { 1, P1ErrorCode87_000001, 0}, // 0x3837
    { 1, P1ErrorCode88_000001, 0}, // 0x3838
    { 1, P1ErrorCode89_000001, 0}, // 0x3839
    { 2, P1ErrorCode90_000001, P1ErrorCode90_000002}, // 0x3930
    { 1, P1ErrorCode91_000001, 0}, // 0x3931
    { 1, P1ErrorCode92_000001, 0}, // 0x3932
    { 2, P1ErrorCode93_000001, P1ErrorCode93_000002}, // 0x3933
    { 1, P1ErrorCode94_000001, 0}, // 0x3934
    { 1, P1ErrorCode96_000001, 0} // 0x3936
};


unsigned short usPrintStep;
unsigned short usPrint10MSTimer;
unsigned short usPrintingFinish10MSTimer;
unsigned short usPrintAutoSecondReceipt10MSTimer;
unsigned char ucPrintReceiptNo;
unsigned char ucPRTDensity;
unsigned char ucPrintError;
unsigned char ucPrintPrePrintingAreaFlag; // Print Pre-printing Area Flag for printing of pre-printing area


void PrintTask(void);
BOOL DetectPaper(void);
void InitializePrinterParameter(void);
void PrintSetFF(int line, int form_feed_line);
void BuildPrintLine(int line, char *item, int item_len, char *msg, int msg_len, char attr, char justify_mode, char lang);

void BuildPrintPOSInfoReport(void);
void BuildPrintTrxnReceipt(_st_TrxnLog_ *trxn_log);
void BuildPrintReversalReceipt(void);
void BuildPrintUnsuccessfulReversalReceipt(void);
void BuildPrintTrxnsReport(void);
void BuildReprintBuyWithExternalPrinter(_st_TrxnLog_ *trxn_log);
void BuildReprintBillPaymentWithExternalPrinter(_st_TrxnLog_ *trxn_log);
void BuildPrintBalanceReceipt(void);
void BuildPrintEndOfDayReceipt(void);

int PrintCardSystem(int line);
int PrintPaymasterLogo(int line);
int PrintApplicationVersion(int line);
int PrintPoweredbyPayMaster(int line);
int PrintStoreName(int line);
int PrintMerchantName(int line);
int PrintMultiMerchantStoreName(int line, _st_TrxnLog_ *trxn_log);
int PrintDateAndTime(int line, unsigned char *date, unsigned char *time);
int PrintBuyTrxnName(int line, _st_TrxnLog_ *trxn_log);
int PrintMerchantID(int line, char *merchant_id);
int PrintTerminalID(int line, char *terminal_id);
int PrintPOSSerialNo(int line);
int PrintPAN(int line, char *track2data, unsigned short len);
int PrintApprovalNo(int line, _st_TrxnLog_ *trxn_log);
int PrintReferenceNo(int line, _st_TrxnLog_ *trxn_log);
int PrintCustomerID(int line, _st_TrxnLog_ *trxn_log);
int PrintTraceNo(int line, _st_TrxnLog_ *trxn_log);
int PrintAmount(int line, _st_TrxnLog_ *trxn_log);
int PrintBalance(int line, _st_TrxnLog_ *trxn_log);
int PrintBillPaymentContents(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log);
int PrintSIMChargeContents(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log);
int PrintStoreAdvertisement(int line);
int PrintTotal(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log);
int PrintAllStars(int line);
int PrintAllDashes(int line);
int PrintAllEquals(int line);

extern void time_to_tm(time_t totalsecs, int offset, _tDATE_TIME *result);
int PrintULDateAndTime(int line, unsigned long ulDateTime);
int PrintBatchNo(int line, _st_TrxnLog_ *trxn_log);
int PrintSeqNo(int line, _st_TrxnLog_ *trxn_log);

#ifdef USER_DEBUG
void OutputReceiptData(int line);
#endif

/*----------------------------------------------------------------------------
        char PRINTER_WORKING(void);
        Output	: return = 0xFF ( No ACTION )
                        : return = 0x35 - NO PAPER
                        : return = 0x60 - ALL PAGE PRINTING FINISH
                        : return = 0x61 - ONE PAGE PRINTING FINISH
----------------------------------------------------------------------------*/
void PrintTask(void) {
    int i, key;

    i = PRINTER_WORKING() & 0xFF;

    if (usPrintStep == 0) {
        return;
    }

    switch (i) {
        case 0x60: // ALL PAGE PRINTING FINISH
#ifdef USER_DEBUG
            Rprintf("All page printing is finished = %d\r\n", usPrintStep);
#endif
            if (usPrintStep == 4) {
                usPrintStep = 5;
            }
            break;
        case 0x61: // ONE PAGE PRINTING FINISH
#ifdef USER_DEBUG
            Rprintf("One page printing is finished = %d\r\n", usPrintStep);
#endif
            if (usPrintStep == 2) {
                usPrintStep = 3;
            }
            break;
    }

    switch (usPrintStep) {
        case 1: // Print Initial Status
#ifdef USER_DEBUG
            Rprintf("Print Initial Status = %d\r\n", usPrintStep);
#endif
            // NO PAPER?
            if (!DetectPaper()) {
#ifdef USER_DEBUG
                Rprintf("No Paper at Print Initial Status = %d\r\n", usPrintStep);
#endif
                usPrintStep = 6;
                break;
            }

            // Printer Off-Line?
            if ((ONLINE_READ() & 0xFF) != 0xFF) {
                MAKEONLINE();
            }

            switch (*pusServiceAddr) {
                case 0x1208: // Print Information - Build Print Data for POS Information Reports
                case 0x1510: // Printer Test - Build Print Data for POS Information Reports
                    BuildPrintPOSInfoReport();
                    break;

                case 0x5114: // Buy - Build Print Data for Transaction Receipt of pre-printing
                case 0x5407: // SIM Charge(Preliminary Transaction) of pre-printing
                    BuildPrintTrxnReceipt(pstfTempTrxnLog);
                    break;

                case 0x2113: // Current Merchant Total - Build Print Data for Transaction Receipt
                    //case 0x2123:	// Previous Merchant Total - Build Print Data for Transaction Receipt
                case 0x2133: // Clear Merchant Total - Build Print Data for Transaction Receipt
                case 0x2213: // Current POS Total - Build Print Data for Transaction Receipt
                case 0x2223: // Previous POS Total - Build Print Data for Transaction Receipt
                case 0x2233: // Clear POS Total - Build Print Data for Transaction Receipt
                case 0x2243: // POS Balance - Build Print Data for Transaction Receipt
                case 0x2313: // Current Store Total - Build Print Data for Transaction Receipt
                case 0x2323: // Previous Store Total - Build Print Data for Transaction Receipt
                case 0x2333: // Clear Store Total - Build Print Data for Transaction Receipt
                case 0x2343: // Open Store - Build Print Data for Transaction Receipt
                case 0x2353: // Close Store - Build Print Data for Transaction Receipt
                case 0x5117: // Buy - Build Print Data for Transaction Receipt
                case 0x5409: // SIM Charge(Preliminary Transaction) - Build Print Data for Transaction Receipt
                    BuildPrintTrxnReceipt(pstfTempTrxnLog);
                    break;

                case 0x3102: // Print POS Last Trans. - Build Print Data for Transaction Reports
                case 0x3202: // Print Required Trans. - Build Print Data for Transaction Reports
                case 0x3302: // Print POS Last 20 Trans. - Build Print Data for Transaction Reports
                    BuildPrintTrxnsReport();
                    break;

                case 0x3402: // Reprint Buy with external printer - Build Print Data for Transaction Reports
                    BuildReprintBuyWithExternalPrinter(pstfTempTrxnLog);
                    break;

                case 0x3404: // Reprint Bill Payment with external printer - Build Print Data for Transaction Reports
                    BuildReprintBillPaymentWithExternalPrinter(pstfTempTrxnLog);
                    break;

                case 0x9001: // Print Reversal Receipt
                    BuildPrintReversalReceipt();
                    break;

                case 0x2104: // Print Reversal Receipt
                    BuildPrintReversalReceipt();
                    break;

                case 0x2123: // Print EndOfDay Receipt
                    BuildPrintEndOfDayReceipt();
                    break;

                case 0x5209: // Balance Inquiry - Build Print Data for Transaction Receipt
                    BuildPrintBalanceReceipt();
                    break;

                case 0x9401: // Print Unsuccessful Reversal Receipt
                    BuildPrintUnsuccessfulReversalReceipt();
                    break;
            }

            CHAR_FILL1[0] = 0xFF;
            PRINTING_NEED = 0xFF;
            usPrintStep = 2;
#ifdef USER_DEBUG
            Rprintf("Printing Status = %d\r\n", usPrintStep);
#endif
            break;
        case 2: // Printing Status
            // NO PAPER?
            if (!DetectPaper()) {
#ifdef USER_DEBUG
                Rprintf("No Paper at Printing Status = %d\r\n", usPrintStep);
#endif
                usPrintStep = 6;
            }
            break;
        case 3: // ONE PAGE PRINTING FINISH
            switch (*pusServiceAddr) {
                case 0x3302: // Print POS Last 20 Trans. - Build Print Data for Transaction Reports
                    if (iStartDBCtrlIndex >= iMaxDBCtrlIndex) {
                        Beep_EventSound(OK_TONE);
                    }
                    break;

                case 0x5114: // Buy - Build Print Data for Transaction Receipt of pre-printing
                case 0x5407: // SIM Charge(Preliminary Transaction) of pre-printing
                    break;

                case 0x5117: // Buy - Build Print Data for Transaction Receipt
                    if (usResponseCode == 0x3030) {
                        if (ucPrintReceiptNo == 3 || ucPrintReceiptNo == 1) {
                            Beep_EventSound(OK_TONE);
                        }
                    } else {
                        Beep_EventSound(OK_TONE);
                    }
                    break;

                default:
                    Beep_EventSound(OK_TONE);
                    break;
            }
            usPrint10MSTimer = TIMER_Get10MSTimer();
            usPrintStep = 4;
#ifdef USER_DEBUG
            Rprintf("Check PRINTING FINISH = %d\r\n", usPrintStep);
#endif
            break;
        case 4: // Check PRINTING FINISH
            if (TIMER_GetElapsed10MSTime(usPrint10MSTimer) >= PRT_FINISH_TIMEOUT) {
#ifdef USER_DEBUG
                Rprintf("Check PRINTING FINISH time-out = %d\r\n", usPrintStep);
#endif
                usPrintStep = 5;
            }
            break;
        case 5: // PRINTING FINISH
#ifdef USER_DEBUG
            Rprintf("PRINTING FINISH = %d\r\n", usPrintStep);
            Rprintf("pusServiceAddr = 0x%04X\r\n", *pusServiceAddr);
#endif
            // Clear Print Pre-printing Area Flag for printing of pre-printing area
            ucPrintPrePrintingAreaFlag = 0;

            switch (*pusServiceAddr) {
                case 0x5114: // Buy - Build Print Data for Transaction Receipt of pre-printing
                case 0x5407: // SIM Charge(Preliminary Transaction) of pre-printing
                    usPrintStep = 0;
                    ucPrintReceiptNo = 0;
#ifdef USER_DEBUG
                    Rprintf("Clear Print Step = %d\r\n", usPrintStep);
#endif
                    return;

                case 0x2113: // Current Merchant Total - Build Print Data for Transaction Receipt
                    //case 0x2123:	// Previous Merchant Total - Build Print Data for Transaction Receipt
                case 0x2133: // Clear Merchant Total - Build Print Data for Transaction Receipt
                case 0x2213: // Current POS Total - Build Print Data for Transaction Receipt
                case 0x2223: // Previous POS Total - Build Print Data for Transaction Receipt
                case 0x2233: // Clear POS Total - Build Print Data for Transaction Receipt
                case 0x2243: // POS Balance - Build Print Data for Transaction Receipt
                case 0x2313: // Current Store Total - Build Print Data for Transaction Receipt
                case 0x2323: // Previous Store Total - Build Print Data for Transaction Receipt
                case 0x2333: // Clear Store Total - Build Print Data for Transaction Receipt
                case 0x2343: // Open Store - Build Print Data for Transaction Receipt
                case 0x2353: // Close Store - Build Print Data for Transaction Receipt
                case 0x5117: // Buy - Build Print Data for Transaction Receipt
                case 0x5409: // SIM Charge(Preliminary Transaction) - Build Print Data for Transaction Receipt
                    if (st_TrxnRespData.ucResult == '1' && (*pusServiceAddr == 0x5117)) {
                        ucPrintReceiptNo--;
                        if (*pusServiceAddr == 0x5117) {
                            /*							if (ucPrintReceiptNo == 3) {
                                                                                            // Save Print Transaction Log
                                                                                            SavePrintTransactionLog(pstfTempTrxnLog, 0);
                                                                                            usPrintStep = 1;
                                                                                            return;
                                                                                    }
                                                                                    else if (ucPrintReceiptNo == 2) {
                             */
                            if (ucPrintReceiptNo == 1) {
                                SavePrintTransactionLog(pstfTempTrxnLog, 0);
                                // "Please cut a    ", "receipt         ", "                ", "Press ENTER Key "
                                LCDDisplay4Lines(M4CutReceiptMsg_0001, -1, ucLangFlag);
                                usPrintAutoSecondReceipt10MSTimer = TIMER_Get10MSTimer();
                                while (1) {
                                    if (TIMER_GetElapsed10MSTime(usPrintAutoSecondReceipt10MSTimer) >= PRT_AUTO_SECOND_RECEIPT_TIMEOUT) {
                                        usPrintStep = 1;
                                        return;
                                    }

                                    key = KEYSCAN() & 0xFF;
                                    if (key == BTKEY_ENTER) {
                                        usPrintStep = 1;
                                        return;
                                    }
                                }
                            } else if (ucPrintReceiptNo == 1) {
                                usPrintStep = 1;
                                return;
                            }
                        } else {
                            // Save Print Transaction Log
                            SavePrintTransactionLog(pstfTempTrxnLog, 0);

                            if (ucPrintReceiptNo) {
                                // "Second Receipt  ", "                ", "1.Print         ", "2.Exit          "
                                LCDDisplay4Lines(M4Bill2ndReceipt_001, LCD_LINE2, ucLangFlag);
                                SetMenuScrollUpDownInfo(2, 1, 2, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelectPrintExit_01]);

                                usPrintAutoSecondReceipt10MSTimer = TIMER_Get10MSTimer();
                                while (1) {
                                    if (TIMER_GetElapsed10MSTime(usPrintAutoSecondReceipt10MSTimer) >= AUTO_INITIAL_TIMEOUT) {
                                        break;
                                    }

                                    key = KEYSCAN() & 0xFF;
                                    if (sVirtualKey != BTKEY_NULL) {
                                        key = sVirtualKey;
                                        sVirtualKey = BTKEY_NULL;
                                    }
                                    if (key != BTKEY_NULL) {
                                        if (key == BTKEY_ENTER) {
                                            if (sSelectedMenuItemNo == BTKEY_1) {
                                                usPrintStep = 1;
                                                return;
                                            } else {
                                                break;
                                            }
                                        } else if (key == BTKEY_CANCEL) {
                                            break;
                                        } else {
                                            MenuScrollUpDown(sStartDisplayMenuLine, &sSelectedMenuItemNo, &sSelectedMenuItemLine, sTotalMenuItemNo, psz17FirstMenuItemMsgAddr, key, ucLangFlag);
                                            if (key >= BTKEY_1 && key <= sTotalMenuItemNo) {
                                                sVirtualKey = BTKEY_ENTER;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Save Print Transaction Log
                    if (pstfTempTrxnLog->ucStatus.BIT.NotPrint1Flag == 1) {
                        SavePrintTransactionLog(pstfTempTrxnLog, 0);
                    } else {
                        SavePrintTransactionLog(pstfTempTrxnLog, 1);
                    }
                    break;

                case 0x3302: // Print POS Last 20 Trans. - Build Print Data for Transaction Reports
                    if (iStartDBCtrlIndex < iMaxDBCtrlIndex) {
                        usPrintStep = 1;
                        return;
                    }
                    break;

                case 0x3402: // Reprint Buy with external printer - Build Print Data for Transaction Reports
                case 0x3404: // Reprint Bill Payment with external printer - Build Print Data for Transaction Reports
                    // Save Reprinting Count
                    SaveReprintingCount(pstfTempTrxnLog);
                    break;

                case 0x9001: // Print Reversal Receipt
                    usPrintStep = 0;
                    ucPrintReceiptNo = 0;

                    pstfTempTrxnLog = pstfSavingTrxnLog;
                    // Save Reversal TransactionLog
                    SaveReversalTransactionLog(pstfTempTrxnLog);
                    // Perform Reversal Transaction
                    PerformReversalTransaction();

                    ucReversalRetryCnt = 0;
                    ucReversalRetryTimePerCnt = 0;
                    return;

                case 0x2104: // Print Reversal Receipt
                case 0x2123: // Print EndOfDay Receipt
                    usPrintStep = 0;
                    ucPrintReceiptNo = 0;
                    break;

                case 0x9401: // Print Unsuccessful Reversal Receipt
                    ucReversalFlag = 0;
                    ucReversalRetryCnt = 0;
                    ucReversalRetryTimePerCnt = 0;
                    pstfTempTrxnLog = pstfSavingTrxnLog;
                    SavePrintTransactionLog(pstfTempTrxnLog, 0);
                    break;

                case 0x5209: // Balance Inquiry - Build Print Data for Transaction Receipt
                    break;
            }

            usPrintStep = 0;
            ucPrintReceiptNo = 0;
            sVirtualKey = BTKEY_CANCEL;
#ifdef USER_DEBUG
            Rprintf("Clear Print Step = %d\r\n", usPrintStep);
#endif
            break;
        case 6: // Printing Error
#ifdef USER_DEBUG
            Rprintf("Printing Error = %d\r\n", usPrintStep);
#endif
            usPrintStep = 0;
            ucPrintReceiptNo = 0;
            // Clear Print Pre-printing Area Flag for printing of pre-printing area
            ucPrintPrePrintingAreaFlag = 0;

            PRINTING_NEED = 0;
            for (i = 0; i < 5; i++) {
                CHAR_FILL1[i] = 0;
            }
            PRINT_FROM_FIRST();
#ifdef USER_DEBUG
            Rprintf("Clear Print Step = %d\r\n", usPrintStep);
#endif

            switch (*pusServiceAddr) {
                case 0x5114: // Buy - Build Print Data for Transaction Receipt of pre-printing
                case 0x5407: // SIM Charge(Preliminary Transaction) of pre-printing
                    return;

                case 0x2113: // Current Merchant Total - Build Print Data for Transaction Receipt
                case 0x2123: // Previous Merchant Total - Build Print Data for Transaction Receipt
                case 0x2133: // Clear Merchant Total - Build Print Data for Transaction Receipt
                case 0x2213: // Current POS Total - Build Print Data for Transaction Receipt
                case 0x2223: // Previous POS Total - Build Print Data for Transaction Receipt
                case 0x2233: // Clear POS Total - Build Print Data for Transaction Receipt
                case 0x2243: // POS Balance - Build Print Data for Transaction Receipt
                case 0x2313: // Current Store Total - Build Print Data for Transaction Receipt
                case 0x2323: // Previous Store Total - Build Print Data for Transaction Receipt
                case 0x2333: // Clear Store Total - Build Print Data for Transaction Receipt
                case 0x2343: // Open Store - Build Print Data for Transaction Receipt
                case 0x2353: // Close Store - Build Print Data for Transaction Receipt
                case 0x5117: // Buy - Build Print Data for Transaction Receipt
                case 0x5209: // Balance Inquiry - Build Print Data for Transaction Receipt
                case 0x5409: // SIM Charge(Preliminary Transaction) - Build Print Data for Transaction Receipt
                case 0x2104: // Print Reversal Receipt
                    TIMER_Wait1MS(2000);
                    pusServiceAddr++;
                    sVirtualKey = BTKEY_ENTER;
                    break;

                case 0x9001: // Print Reversal Receipt
                    pstfTempTrxnLog = pstfSavingTrxnLog;
                    // Save Reversal TransactionLog
                    SaveReversalTransactionLog(pstfTempTrxnLog);
                    // Display "Insert paper" or print a reversal receipt
                    PrintReversalReceipt(0);
                    return;

                case 0x9401: // Print Unsuccessful Reversal Receipt
                    PrintUnsuccessfulReversalReceipt();
                    break;

                default:
                    sVirtualKey = BTKEY_CANCEL;
                    break;
            }
            break;
    }
}

/*
Detect Paper
        Output
                0: Detect no paper
                1: Detect paper
 */
BOOL DetectPaper(void) {
    // NO PAPER?
    if ((PAPER_READ() & 0xFF) != 0xFF) {
        return FALSE;
    } else {
        return TRUE;
    }
}

// Initialize Printer Parameter

void InitializePrinterParameter(void) {
    int i;

    /*
            : Set printing preference for control density or contrast level   
            : accept 0 t0 29 value for control ( default : 15 )
            : 0 1 2 3 -- 8 -- -- -- 15 -- -- -- -- -- 26 27 28 29
            :            <- Used current standard printer ->                       
            : <- special high speed printer in here ->
            : 
            : high speed    < ---------------------- >  slow speed 
            : light quality < ---------------------- >  dark level
     */
    SET_PRINTING_PREFERENCE(ucPRTDensity);
    /*
            : accept 0 to 15 data for line space gap 
            : (default : 4 )
     */
    SET_LINESPACE(PRT_LINE_SPACE);

    for (i = 0; i < 5; i++) {
        CHAR_FILL1[i] = 0x00;
    }
    memset((char *) &CHAR_BUFFER1[0], 0x00, 5 * PRT_LINES_PER_PAGE * PRT_CHARACTERS_PER_LINE);
    memset((char *) &ATTB_BUFFER1[0], 0x00, 5 * PRT_LINES_PER_PAGE * PRT_CHARACTERS_PER_LINE);

    PRINT_FROM_FIRST();
}

// Set Paper Form Feed

void PrintSetFF(int line, int form_feed_line) {
    line += form_feed_line;
    SET_FORMFEED(line);

#ifdef USER_DEBUG
    Rprintf("line = %d\r\n", line);
    Rprintf("End\r\n");
    OutputReceiptData(line);
#endif
}

// Build Print One Line Data

void BuildPrintLine(int line, char *item, int item_len, char *msg, int msg_len, char attr, char justify_mode, char lang) {
    int i, j;
    char *p, *q;
    char temp[33];
    unsigned char ch;

    if (item_len <= 0 && msg_len <= 0) {
        return;
    }

    p = (char *) &CHAR_BUFFER1[0];
    p += line * PRT_CHARACTERS_PER_LINE;
    q = (char *) &ATTB_BUFFER1[0];
    q += line * PRT_CHARACTERS_PER_LINE;

    if (item_len < 0) {
        item_len = 0;
    } else {
        if (attr != PRT_DOUBLE_WIDTH_MODE) {
            if (item_len > PRT_CHARACTERS_PER_LINE) {
                item_len = PRT_CHARACTERS_PER_LINE;
            }
        } else {
            if ((item_len * 2) > PRT_CHARACTERS_PER_LINE) {
                item_len = PRT_CHARACTERS_PER_LINE / 2;
            }
        }

        memset(temp, 0x00, sizeof (temp));
        memcpy(temp, item, item_len);
        if (lang) {
            IndianNo2FarsiNo(temp, strlen(temp));
        }

        if (ucLangFlag) {
            // right justified
            if (attr != PRT_DOUBLE_WIDTH_MODE) {
                j = PRT_CHARACTERS_PER_LINE - item_len;
            } else {
                j = PRT_CHARACTERS_PER_LINE - (item_len * 2);
            }
        } else {
            // left justified
            j = 0;
        }

        i = 0;
        while (i < item_len) {
            p[j] = temp[i++];
            q[j] = attr;
            // Double width
            if (attr == PRT_DOUBLE_WIDTH_MODE) {
                j += 2;
            } else {
                j++;
            }
        }
    }

    if (msg_len <= 0) {
        return;
    } else {
        if (attr != PRT_DOUBLE_WIDTH_MODE) {
            if (msg_len > PRT_CHARACTERS_PER_LINE) {
                msg_len = PRT_CHARACTERS_PER_LINE;
            }
        } else {
            if ((msg_len * 2) > PRT_CHARACTERS_PER_LINE) {
                msg_len = PRT_CHARACTERS_PER_LINE / 2;
            }
        }

        if (item_len) {
            if (attr != PRT_DOUBLE_WIDTH_MODE) {
                if ((item_len + msg_len) > PRT_CHARACTERS_PER_LINE) {
                    msg_len = PRT_CHARACTERS_PER_LINE - item_len;
                }
            } else {
                if ((item_len + msg_len) > (PRT_CHARACTERS_PER_LINE / 2)) {
                    msg_len = (PRT_CHARACTERS_PER_LINE / 2) - item_len;
                }
            }
        }

        if (msg_len <= 0) {
            return;
        } else {
            memset(temp, 0x00, sizeof (temp));
            memcpy(temp, msg, msg_len);
            if (lang) {
                IndianNo2FarsiNo(temp, strlen(temp));
            }

            if (item_len) {
                if (ucLangFlag) {
                    // left justified
                    j = 0;
                } else {
                    // right justified
                    if (attr != PRT_DOUBLE_WIDTH_MODE) {
                        j = PRT_CHARACTERS_PER_LINE - msg_len;
                    } else {
                        j = PRT_CHARACTERS_PER_LINE - (msg_len * 2);
                    }
                }
            } else {
                if (justify_mode == LEFT_JUSTIFIED) {
                    // left justified
                    j = 0;
                } else if (justify_mode == CENTER_JUSTIFIED) {
                    // center justified
                    if (attr != PRT_DOUBLE_WIDTH_MODE) {
                        j = (PRT_CHARACTERS_PER_LINE - msg_len) / 2;
                    } else {
                        j = (PRT_CHARACTERS_PER_LINE - (msg_len * 2)) / 2;
                    }
                } else {
                    // right justified
                    if (attr != PRT_DOUBLE_WIDTH_MODE) {
                        j = PRT_CHARACTERS_PER_LINE - msg_len;
                    } else {
                        j = PRT_CHARACTERS_PER_LINE - (msg_len * 2);
                    }
                }
            }

            i = 0;
            while (i < msg_len) {
                p[j] = temp[i++];
                q[j] = attr;
                // Double width
                if (attr == PRT_DOUBLE_WIDTH_MODE) {
                    j += 2;
                } else {
                    j++;
                }
            }
        }
    }
}

// Build Print POS Information Report

void BuildPrintPOSInfoReport(void) {
    int i, j, k, line;
    char justify_mode;
    char item[33], msg[33], temp[33];
    _tDATE_TIME dt;

#ifdef USER_DEBUG
    Rprintf("\r\nBuildPrintPOSInfoReport()\r\n");
#endif
    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    line = 0;


    // Merchant Name
    line = PrintMerchantName(line);
    line++;

    // "********************************"
    line = PrintAllStars(line);

    BuildPrintLine(line++, "", 0, "POS Information", 15, PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);

    // "********************************"
    line = PrintAllStars(line);

    // "Terminal ID:",
    line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);

    // "Merchant ID:",
    //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
    line = PrintMerchantID(line, pstParams->szMerchantID);

    // "Store Name :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1StoreName_00000001]);
    BuildPrintLine(line++, item, strlen(item), NULL, 0, PRT_NORMAL_MODE, LEFT_JUSTIFIED, 0);
    strcpy(msg, st_POSSetupInfo.sz33StoreName);
    BuildPrintLine(line++, NULL, 0, msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, 0);

    temp[0] = sz17HWInfo[9];
    temp[1] = sz17HWInfo[10];
    temp[2] = 0x00;
#ifndef SDRAM_VERSION
    switch (atoi(temp)) {
        case 31: strcpy(msg, "IC3100PE");
            break;
            //case 33:	strcpy(msg, "IC3300P"); break;
        case 51: strcpy(msg, "IC5100P");
            break;
            //case 60:	strcpy(msg, "IC6000"); break;
        default: strcpy(msg, "Unknown Code");
            break;
    }
#else
    switch (atoi(temp)) {
        case 31: strcpy(msg, "IC3100SD");
            break;
            //case 33:	strcpy(msg, "IC3300SD"); break;
        case 51: strcpy(msg, "IC5100SD");
            break;
            //case 60:	strcpy(msg, "IC6000"); break;
        default: strcpy(msg, "Unknown Code");
            break;
    }
#endif
    // "Model Name :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1ModelName_00000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "POS S/N    :",
    line = PrintPOSSerialNo(line);

    switch (sz17HWInfo[1]) {
        case 0x30: strcpy(msg, "NONE");
            break;
        case 0x34: strcpy(msg, "2 MB");
            break;
        case 0x35: strcpy(msg, "4 MB");
            break;
        case 0x36:
        case 0x37: strcpy(msg, "8 MB");
            break;
        case 0x38: strcpy(msg, "16 MB");
            break;
        default: strcpy(msg, "Unknown Code");
            break;
    }
    // "SRAM       :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SRAM_0000000000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    switch (sz17HWInfo[2]) {
        case 0x30: strcpy(msg, "NONE");
            break;
        case 0x34: strcpy(msg, "2 MB");
            break;
        case 0x35: strcpy(msg, "4 MB");
            break;
        case 0x36:
        case 0x37: strcpy(msg, "8 MB");
            break;
        case 0x38: strcpy(msg, "16 MB");
            break;
        default: strcpy(msg, "Unknown Code");
            break;
    }
    // "SDRAM      :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SDRAM_000000000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    switch (sz17HWInfo[3]) {
        case 0x30: strcpy(msg, "NONE");
            break;
        case 0x34: strcpy(msg, "2 MB");
            break;
        case 0x35: strcpy(msg, "4 MB");
            break;
        case 0x36:
        case 0x37: strcpy(msg, "8 MB");
            break;
        case 0x38: strcpy(msg, "16 MB");
            break;
        default: strcpy(msg, "Unknown Code");
            break;
    }
    // "Flash ROM  :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1FlashROM_000000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    switch (sz17HWInfo[5]) {
        case 0x30: strcpy(msg, "NONE");
            break;
        case 0x31: strcpy(msg, "EXISTED");
            break;
        default: strcpy(msg, "Unknown Code");
            break;
    }
    // "USB        :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1USB_00000000000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    switch (sz17HWInfo[7]) {
        case 0x30: strcpy(msg, "NONE");
            break;
        case 0x31: strcpy(msg, "Dial-up 2400bps");
            break;
        case 0x32: strcpy(msg, "Dial-up 56Kbps");
            break;
        case 0x33: strcpy(msg, "GSM/GPRS");
            break;
        case 0x34: strcpy(msg, "CDMA");
            break;
        case 0x35: strcpy(msg, "56Kbps, GSM/GPRS");
            break;
        default: strcpy(msg, "Unknown Code");
            break;
    }
    // "MODEM      :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Modem_000000000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "BIOS Ver   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1BIOSVersion_000001]);
    BuildPrintLine(line++, item, strlen(item), sz6BIOSVersion, strlen(sz6BIOSVersion), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "S/W Version:",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SWVersion_00000001]);
    BuildPrintLine(line++, item, strlen(item), sz17ProgramVersion, strlen(sz17ProgramVersion), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "S/W Date   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SWDate_00000000001]);
    if (ucLangFlag) {
        dt.CLKYEARH = (sz17ProgramDate[0] << 4) + (sz17ProgramDate[1] & 0x0F);
        dt.CLKYEARL = (sz17ProgramDate[2] << 4) + (sz17ProgramDate[3] & 0x0F);
        dt.CLKMONTH = (sz17ProgramDate[5] << 4) + (sz17ProgramDate[6] & 0x0F);
        dt.CLKDATE = (sz17ProgramDate[8] << 4) + (sz17ProgramDate[9] & 0x0F);
        dt.CLKHOUR = 0x12;
        dt.CLKMIN = 0x00;
        dt.CLKSEC = 0x00;
        // Convert the Gregorian calendar to the Jalali(Moslem) calendar
        RTC_Gregorian2Jalali(&dt);

        sprintf(temp, "%02X%02X/%02X/%02X      ", dt.CLKYEARH, dt.CLKYEARL, dt.CLKMONTH, dt.CLKDATE);
    } else {
        strcpy(temp, sz17ProgramDate);
    }
    RemoveLeadingAndTrailingSpaces(msg, temp, strlen(temp));
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Param Ver  :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1POSSetupVersion_01]);
    sprintf(msg, "%04X", st_POSSetupInfo.usVersionNo);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Param Date :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1POSSetupDate_00001]);
    if (ucLangFlag) {
        dt.CLKYEARH = ((st_POSSetupInfo.sz9InfoDate[0] - '0') << 4) + ((st_POSSetupInfo.sz9InfoDate[1] - '0') & 0x0F);
        dt.CLKYEARL = ((st_POSSetupInfo.sz9InfoDate[2] - '0') << 4) + ((st_POSSetupInfo.sz9InfoDate[3] - '0') & 0x0F);
        dt.CLKMONTH = ((st_POSSetupInfo.sz9InfoDate[4] - '0') << 4) + ((st_POSSetupInfo.sz9InfoDate[5] - '0') & 0x0F);
        dt.CLKDATE = ((st_POSSetupInfo.sz9InfoDate[6] - '0') << 4) + ((st_POSSetupInfo.sz9InfoDate[7] - '0') & 0x0F);
        dt.CLKHOUR = 0x12;
        dt.CLKMIN = 0x00;
        dt.CLKSEC = 0x00;
        // Convert the Gregorian calendar to the Jalali(Moslem) calendar
        RTC_Gregorian2Jalali(&dt);

        sprintf(msg, "%02X%02X/%02X/%02X", dt.CLKYEARH, dt.CLKYEARL, dt.CLKMONTH, dt.CLKDATE);
    } else {
        sprintf(msg, "%c%c%c%c/%c%c/%c%c",
                st_POSSetupInfo.sz9InfoDate[0],
                st_POSSetupInfo.sz9InfoDate[1],
                st_POSSetupInfo.sz9InfoDate[2],
                st_POSSetupInfo.sz9InfoDate[3],
                st_POSSetupInfo.sz9InfoDate[4],
                st_POSSetupInfo.sz9InfoDate[5],
                st_POSSetupInfo.sz9InfoDate[6],
                st_POSSetupInfo.sz9InfoDate[7]);
    }
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Dial Signal:",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1DialSignal_0000001]);
    if (!st_POSSetupInfo.ucPulseDial) {
        strcpy(msg, "DTMF");
    } else {
        strcpy(msg, "PULSE");
    }
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Trans. Tel :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1TrxnTel_0000000001]);
    BuildPrintLine(line++, item, strlen(item), st_POSSetupInfo.sz17TrxnTelNo[0], strlen(st_POSSetupInfo.sz17TrxnTelNo[0]), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "TMS Tel    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1TMSTel_00000000001]);
    BuildPrintLine(line++, item, strlen(item), st_POSSetupInfo.sz17TMSTelNo[0], strlen(st_POSSetupInfo.sz17TMSTelNo[0]), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Help Desk  :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1HelpDeskTel_000001]);
    BuildPrintLine(line++, item, strlen(item), st_POSSetupInfo.sz17HelpDeskTelNo[0], strlen(st_POSSetupInfo.sz17HelpDeskTelNo[0]), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    line++;

    // "System Font",
    BuildPrintLine(line++, "", 0, "System Font", 11, PRT_UNDER_LINE_MODE, LEFT_JUSTIFIED, ucLangFlag);
    i = 0;
    while (i < 256) {
        for (j = 0; j < PRT_CHARACTERS_PER_LINE; j++) {
            msg[j] = i++;
        }
        BuildPrintLine(line++, "", 0, msg, PRT_CHARACTERS_PER_LINE, PRT_NORMAL_MODE, LEFT_JUSTIFIED, 0);
    }

    // "--------------------------------"
    line = PrintAllDashes(line);

    // LOGO Image
    k = ((unsigned short) BitelPrinterLogo[2] << 8) | (unsigned short) BitelPrinterLogo[3]; // Image Height
    /*
            void ASSIGN_GRAPHICS(char* , char or int);
            : Address point input for graphics data  
            : assign graphics data to 0 to 4 number to handle for printing
     */
    ASSIGN_GRAPHICS((char *) &BitelPrinterLogo[0], 1);
    ATTB_BUFFER1[0][line][0] = PRT_GRAPHICS_MODE + 1;
    line += (k + 23) / 24;

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

// Build Print Transaction Receipt

void BuildPrintTrxnReceipt(_st_TrxnLog_ *trxn_log) {
    int i, j, line;
    int pre_printed_flag;
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    char justify_mode;
    char item[33], msg[33];
    unsigned char date[4], time[3];

#ifdef USER_DEBUG
    Rprintf("\r\nBuildPrintTrxnReceipt(), 0x%04X, %d\r\n", *pusServiceAddr, ucPrintReceiptNo);
#endif
    InitializePrinterParameter();

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    line = 0;

    switch (*pusServiceAddr) {
        case 0x5114: // Buy - Build Print Data for Transaction Receipt of pre-printing
        case 0x5407: // SIM Charge(Preliminary Transaction) of pre-printing
            if (*pusServiceAddr == 0x5114) {
                msg_type = MTYPE_FINANCIAL_TRXN_REQUEST;
            } else {
                msg_type = MTYPE_AUTHORIZATION_REQUEST;
            }
            proc_code = HEX3_to_Unsignedlong((char *) trxn_log->uc3ProcCode);
            GetTransactionType(&trxn_type, msg_type, proc_code);
#ifdef USER_DEBUG
            Rprintf("msg_type       = %04X\r\n", msg_type);
            Rprintf("proc_code      = %06lX\r\n", proc_code);
            Rprintf("trxn_type      = %d\r\n", trxn_type);
            Rprintf("usResponseCode = %04X\r\n", usResponseCode);
#endif

            ucPrintReceiptNo = 1;

            // Merchant Name
            line = PrintMerchantName(line);
            line++;

            // "--------------------------------"
            line = PrintAllDashes(line);

            // "Terminal ID:",
            if (strlen(trxn_log->sz9TerminalID)) {
                line = PrintTerminalID(line, trxn_log->sz9TerminalID);
            } else {
                line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
            }

            // "Merchant ID:",
            if (strlen(trxn_log->sz16MerchantID)) {
                line = PrintMerchantID(line, trxn_log->sz16MerchantID);
            } else {
                line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
            }

            PrintSetFF(line, 0);
            return;

        default:
            msg_type = HEX2_to_UnsignedShort((char *) trxn_log->uc2MsgType);
            proc_code = HEX3_to_Unsignedlong((char *) trxn_log->uc3ProcCode);
            GetTransactionType(&trxn_type, msg_type, proc_code);
#ifdef USER_DEBUG
            Rprintf("msg_type       = %04X\r\n", msg_type);
            Rprintf("proc_code      = %06lX\r\n", proc_code);
            Rprintf("trxn_type      = %d\r\n", trxn_type);
            Rprintf("usResponseCode = %04X\r\n", usResponseCode);
#endif
            trxn_type = trxn_log->usTrxnType;

            switch (trxn_type) {
                    // Buy
                case TRXN_PURCHASE_ONLY:
                    // Bill Payment
                    // SIM Charge
                case TRXN_BILL_PAYMENT:
                    if (ucPrintReceiptNo == 0) {
                        //if (usResponseCode == 0x3030) {
                        if (st_TrxnRespData.ucResult == '1') {
                            if (trxn_type == TRXN_PURCHASE_ONLY) {
                                ucPrintReceiptNo = 2;
                            } else {
                                ucPrintReceiptNo = 1;
                            }
                        } else {
                            ucPrintReceiptNo = 1;
                        }
                        //pre_printed_flag = 1;
                        pre_printed_flag = 0;
                    } else {
                        pre_printed_flag = 0;
                    }
                    break;

                default:
                    ucPrintReceiptNo = 1;
                    pre_printed_flag = 0;
                    break;
            }
            break;
    }

    Rprintf("ucPrintReceiptNo = %d\r\n", ucPrintReceiptNo);
#if 0
    if (/*usResponseCode == 0x3030*/ st_TrxnRespData.ucResult == '1' &&
            (trxn_type == TRXN_PURCHASE_ONLY) &&
            (ucPrintReceiptNo == 3 || ucPrintReceiptNo == 1)) {
        // "================================"
        line = PrintAllEquals(line);

        if (ucPrintReceiptNo == 3) {
            // "        (Store Receipt)         ",
            strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1StoreReceipt_00001]);
        } else {
            // "       (Customer Receipt)       ",
            strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1CustomerReceipt_01]);
        }
        BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);

        // "Signature  :",
        strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Signature_00000001]);
        BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, LEFT_JUSTIFIED, ucLangFlag);
        line += 2;

        line = PrintStoreAdvertisement(line);

        line++;
        // Application version for receipt
        line = PrintApplicationVersion(line);
        // Powered by PayMaster
        line = PrintPoweredbyPayMaster(line);

        PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
        return;
    }
#endif

    if (pre_printed_flag == 0 || ucPrintPrePrintingAreaFlag || st_POSSetupInfo.ucComDevice == ETHERNET_MODEM) {
        // Merchant Name
        line = PrintMerchantName(line);
        line++;

        // "--------------------------------"
        line = PrintAllDashes(line);

        // "Terminal ID:",
        if (strlen(trxn_log->sz9TerminalID)) {
            line = PrintTerminalID(line, trxn_log->sz9TerminalID);
        } else {
            line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
        }

        // "Merchant ID:",
        if (strlen(trxn_log->sz16MerchantID)) {
            line = PrintMerchantID(line, trxn_log->sz16MerchantID);
        } else {
            //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
            line = PrintMerchantID(line, pstParams->szMerchantID);

        }
    }

    switch (trxn_type) {
        case TRXN_PURCHASE_ONLY:
            // "************* BUY **************", or // "************* PAY **************", Buy transaction name
            line = PrintBuyTrxnName(line, trxn_log);
            break;
        case TRXN_BALANCE_INQUIRY:
            // "*********** BALANCE ************",
            strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1BalanceInquiry_001]);
            BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
            break;
    }

    // Authorization Request
    // Financial Transaction
    //	if (msg_type == MTYPE_AUTHORIZATION_REQUEST || msg_type == MTYPE_FINANCIAL_TRXN_REQUEST) {
    if (trxn_type == TRXN_PURCHASE_ONLY) {
        i = 20;
    }        // Supervisory Transaction
    else {
        i = 26;
    }
    /*
            str_to_bcd((char *)date, (char *)&trxn_log->uc64AdditionalData[i], 8);
            str_to_bcd((char *)time, (char *)&trxn_log->uc64AdditionalData[i+8], 6);
            // "Date       :",
            // "Time       :",
            line = PrintDateAndTime(line, date, time);
     */
    // "Date       :",
    // "Time       :",
    line = PrintULDateAndTime(line, trxn_log->ulDateTime);

    // Authorization Request
    // Financial Transaction
    //	if (msg_type == MTYPE_AUTHORIZATION_REQUEST || msg_type == MTYPE_FINANCIAL_TRXN_REQUEST) {
    if (trxn_type == TRXN_PURCHASE_ONLY) {
        if (trxn_log->uc20Track2Data[0]) {
            // "PAN        : ",
            line = PrintPAN(line, (char *) &trxn_log->uc20Track2Data[1], (unsigned short) trxn_log->uc20Track2Data[0]);
        }
    }

    // "Approval No:",
    // line = PrintApprovalNo(line, trxn_log);

    // "Ref. No    :",
    line = PrintReferenceNo(line, trxn_log);

    // "Batch No   :",
    line = PrintBatchNo(line, trxn_log);
    // "Seq. No    :",
    line = PrintSeqNo(line, trxn_log);
    /*
            if (((trxn_type == TRXN_PURCHASE_ONLY) && trxn_log->ucBuyTrxnType)) {
                    // "Customer ID:",
                    line = PrintCustomerID(line, trxn_log);
            }
	
            if (trxn_type == TRXN_PURCHASE_ONLY || trxn_type == TRXN_BALANCE_INQUIRY) {
                    // "Trace No   :",
                    line = PrintTraceNo(line, trxn_log);
            }
     */
    //	if (usResponseCode == 0x3030) {
    if (st_TrxnRespData.ucResult == '1') {
        switch (trxn_type) {
            case TRXN_PURCHASE_ONLY:
            case TRXN_BILL_PAYMENT:
                // "--------------------------------"
                line = PrintAllDashes(line);

                // "Amount(Rials)  :",
                line = PrintAmount(line, trxn_log);
                break;
            case TRXN_BALANCE_INQUIRY:
                // "--------------------------------"
                line = PrintAllDashes(line);

                // "Balance(Rials) :",
                line = PrintBalance(line, trxn_log);
                break;
            default:
                // "--------------------------------"
                line = PrintAllDashes(line);

                switch (trxn_type) {
                    default:
                        line = PrintTotal(line, trxn_type, trxn_log);
                        break;
                }
                break;
        }
    }

    if (st_TrxnRespData.ucResult == '1' &&
            (trxn_type == TRXN_PURCHASE_ONLY)) {
        // "================================"
        line = PrintAllEquals(line);

        if (ucPrintReceiptNo == 2) {
            // "        (Store Receipt)         ",
            strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1StoreReceipt_00001]);
        } else {
            // "       (Customer Receipt)       ",
            strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1CustomerReceipt_01]);
        }
        BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);

        // "Signature  :",
        //		strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Signature_00000001]);
        //		BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, LEFT_JUSTIFIED, ucLangFlag);
        //		line += 2;
    }

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);

#if 0
    if (/*usResponseCode == 0x3030*/ (st_TrxnRespData.ucResult == '1') &&
            (trxn_type == TRXN_PURCHASE_ONLY)) {
        PrintSetFF(line, 0);
    } else {
        line = PrintStoreAdvertisement(line);

        PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
    }
#endif
}

void BuildPrintEndOfDayReceipt(void) {
    int i, line;
    char justify_mode;
    char item[33], msg[33];
    U08 uc20Track2Data[20];
    _st_TrxnLog_ *trxn_log;
    U32 ulDateTime;

    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    line = 0;

    // Merchant Name
    line = PrintMerchantName(line);
    line++;

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Terminal ID:",
    line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);

    // "Merchant ID:",
    line = PrintMerchantID(line, pstParams->szMerchantID);

    line++;
    // "********** END OF DAY **********",
    strcpy(msg, "********** END OF DAY **********");
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);

    line++;

    // "Date       :",
    // "Time       :",
    ulDateTime = GetULDateTime();
    line = PrintULDateAndTime(line, ulDateTime);

    line++;

    strcpy(item, "BATCHNO    :");
    sprintf(msg, "%d", st_EndOfDay.BATCHNO);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "T          :");
    sprintf(msg, "%d", st_EndOfDay.T);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "A          :");
    sprintf(msg, "%ld", st_EndOfDay.A);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "PC         :");
    sprintf(msg, "%d", st_EndOfDay.PC);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "PV         :");
    sprintf(msg, "%ld", st_EndOfDay.PV);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "PRC        :");
    sprintf(msg, "%d", st_EndOfDay.PRC);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "PRV        :");
    sprintf(msg, "%ld", st_EndOfDay.PRV);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "RC         :");
    sprintf(msg, "%d", st_EndOfDay.RC);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "RV         :");
    sprintf(msg, "%ld", st_EndOfDay.RV);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "RRC        :");
    sprintf(msg, "%d", st_EndOfDay.RRC);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    strcpy(item, "RRV        :");
    sprintf(msg, "%ld", st_EndOfDay.RRV);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "================================"
    line = PrintAllEquals(line);

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

void BuildPrintBalanceReceipt(void) {
    int i, line;
    char justify_mode;
    char item[33], msg[33];
    U08 uc20Track2Data[20];
    _st_TrxnLog_ *trxn_log;

    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    line = 0;

    // Merchant Name
    line = PrintMerchantName(line);
    line++;

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Terminal ID:",
    line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);

    // "Merchant ID:",
    line = PrintMerchantID(line, pstParams->szMerchantID);

    line++;
    // "*********** BALANCE ************",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1BalanceInquiry_001]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);

    line++;

    // "Date       :",
    // "Time       :",
    line = PrintULDateAndTime(line, st_TrxnReqData.ulDateTime);

    // "PAN        : ",
    uc20Track2Data[0] = strlen(st_TrxnReqData.sz42Track2Data);
    str_to_zbcd((char *) &uc20Track2Data[1], &st_TrxnReqData.sz42Track2Data[0], uc20Track2Data[0]);
    line = PrintPAN(line, (char *) &uc20Track2Data[1], (unsigned short) uc20Track2Data[0]);

    // "Ref. No    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1ReferenceNo_000001]);
    BuildPrintLine(line++, item, strlen(item), st_TrxnRespData.sz13ReferenceNo, strlen(st_TrxnRespData.sz13ReferenceNo), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Batch No   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1BatchNo_0000000001]);
    sprintf(msg, "%d", st_TrxnReqData.usBatchNo);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Seq. No    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SeqNo_000000000001]);
    sprintf(msg, "%d", st_TrxnReqData.usSeqNo);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Balance    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Balance_0000000001]);
    BuildPrintLine(line++, item, strlen(item), st_TrxnRespData.sz13Balance, strlen(st_TrxnRespData.sz13Balance), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Available  :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Available_00000001]);
    BuildPrintLine(line++, item, strlen(item), st_TrxnRespData.sz13Available, strlen(st_TrxnRespData.sz13Available), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "================================"
    line = PrintAllEquals(line);

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

// Build Print Reversal Receipt

void BuildPrintReversalReceipt(void) {
    int i, j, line;
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    char justify_mode;
    char item[33], msg[33];
    _st_TrxnLog_ *trxn_log;

#ifdef USER_DEBUG
    Rprintf("\r\nBuildPrintReversalReceipt()\r\n");
#endif
    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    trxn_log = pstfSavingTrxnLog;

    msg_type = HEX2_to_UnsignedShort((char *) trxn_log->uc2MsgType);
    proc_code = HEX3_to_Unsignedlong((char *) trxn_log->uc3ProcCode);
    GetTransactionType(&trxn_type, msg_type, proc_code);
#ifdef USER_DEBUG
    Rprintf("msg_type  = %04X\r\n", msg_type);
    Rprintf("proc_code = %06lX\r\n", proc_code);
    Rprintf("trxn_type = %d\r\n", trxn_type);
#endif

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    line = 0;

    // Merchant Name
    line = PrintMerchantName(line);
    line++;

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Terminal ID:",
    if (strlen(trxn_log->sz9TerminalID)) {
        line = PrintTerminalID(line, trxn_log->sz9TerminalID);
    } else {
        line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
    }

    // "Merchant ID:",
    if (strlen(trxn_log->sz16MerchantID)) {
        line = PrintMerchantID(line, trxn_log->sz16MerchantID);
    } else {
        //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
        line = PrintMerchantID(line, pstParams->szMerchantID);
    }

    line++;

    // "*** Reversal ***",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1Reversal_000000001]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);

    line++;

    // "Date       :",
    // "Time       :",
    line = PrintULDateAndTime(line, trxn_log->ulDateTime);

    // "PAN        : ",
    line = PrintPAN(line, (char *) &trxn_log->uc20Track2Data[1], (unsigned short) trxn_log->uc20Track2Data[0]);

    // "Ref. No    :",
    line = PrintReferenceNo(line, trxn_log);

    // "Batch No   :",
    line = PrintBatchNo(line, trxn_log);
    // "Seq. No    :",
    line = PrintSeqNo(line, trxn_log);

    // "Amount(Rials)  :",
    line = PrintAmount(line, trxn_log);

    // "================================"
    line = PrintAllEquals(line);

    strcpy(msg, "Original Transaction Information");
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
    // "Seq. No    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SeqNo_000000000001]);
    sprintf(msg, "%d", trxn_log->usOrigSeqNo);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    // "Date       :",
    // "Time       :",
    line = PrintULDateAndTime(line, trxn_log->ulReversalDateTime);
    // "Ref. No    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1ReferenceNo_000001]);
    bcd_to_str(msg, trxn_log->uc6OrigRefNo, 12);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    // "================================"
    line = PrintAllEquals(line);

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

// Build Print Unsuccessful Reversal Receipt

void BuildPrintUnsuccessfulReversalReceipt(void) {
    int i, line;
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    char justify_mode;
    char item[33], msg[33];
    _st_TrxnLog_ *trxn_log;

#ifdef USER_DEBUG
    Rprintf("\r\nBuildPrintUnsuccessfulReversalReceipt()\r\n");
#endif
    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    trxn_log = pstfSavingTrxnLog;

    msg_type = HEX2_to_UnsignedShort((char *) trxn_log->uc2MsgType);
    proc_code = HEX3_to_Unsignedlong((char *) trxn_log->uc3ProcCode);
    GetTransactionType(&trxn_type, msg_type, proc_code);
#ifdef USER_DEBUG
    Rprintf("msg_type  = %04X\r\n", msg_type);
    Rprintf("proc_code = %06lX\r\n", proc_code);
    Rprintf("trxn_type = %d\r\n", trxn_type);
#endif

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    line = 0;

    // Merchant Name
    line = PrintMerchantName(line);
    line++;

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Terminal ID:",
    if (strlen(trxn_log->sz9TerminalID)) {
        line = PrintTerminalID(line, trxn_log->sz9TerminalID);
    } else {
        line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
    }

    // "Merchant ID:",
    if (strlen(trxn_log->sz16MerchantID)) {
        line = PrintMerchantID(line, trxn_log->sz16MerchantID);
    } else {
        //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
        line = PrintMerchantID(line, pstParams->szMerchantID);
    }

    line++;

    // "  Reversal for  ",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1ReversalFail_00001]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);
    // "  unsuccessful  ",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1ReversalFail_00002]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);
    // " transaction is ",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1ReversalFail_00003]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);
    // "   impossible   ",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1ReversalFail_00004]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);

    line++;

    // "Date       :",
    // "Time       :",
    line = PrintULDateAndTime(line, trxn_log->ulDateTime);

    // "PAN        : ",
    line = PrintPAN(line, (char *) &trxn_log->uc20Track2Data[1], (unsigned short) trxn_log->uc20Track2Data[0]);

    // "Ref. No    :",
    line = PrintReferenceNo(line, trxn_log);

    // "Batch No   :",
    line = PrintBatchNo(line, trxn_log);
    // "Seq. No    :",
    line = PrintSeqNo(line, trxn_log);

    // "Amount(Rials)  :",
    line = PrintAmount(line, trxn_log);

    // "================================"
    line = PrintAllEquals(line);

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

// Build Print Transactions Report

void BuildPrintTrxnsReport(void) {
    int i, line;
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    unsigned char first_flag;
    unsigned char date[4], time[3];
    char item[33], msg[33];
    _st_TrxnLog_ *trxn_log;

#ifdef USER_DEBUG
    Rprintf("\r\nBuildPrintTrxnsReport()\r\n");
#endif
    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    line = 0;

    if (iStartDBCtrlIndex == 0) {
        first_flag = 1;
    } else {
        first_flag = 0;
    }

    switch (*pusServiceAddr) {
        case 0x3102: // Print POS Last Trans.
        case 0x3202: // Print Required Trans.
            if (*pusServiceAddr == 0x3102) {
                // Get the Last Transaction DB Index
                i = iMaxDBCtrlIndex - 1;
            } else {
                i = 0;
            }
            trxn_log = st_TrxnLogDB[i].pstTrxnLogAddr;

            msg_type = HEX2_to_UnsignedShort((char *) trxn_log->uc2MsgType);
            proc_code = HEX3_to_Unsignedlong((char *) trxn_log->uc3ProcCode);
            GetTransactionType(&trxn_type, msg_type, proc_code);

            // Merchant Name
            line = PrintMerchantName(line);
            line++;

            // "--------------------------------"
            line = PrintAllDashes(line);

            if (*pusServiceAddr == 0x3102) {
                // "   Print POS Last Transaction   ",
                strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1PrtLastTrxn_000001]);
                BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
            } else {
                // "   Print Required Transaction   ",
                strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1PrtRequiredTrxn_01]);
                BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
            }

            // "--------------------------------"
            line = PrintAllDashes(line);

            // "Terminal ID:",
            if (strlen(trxn_log->sz9TerminalID)) {
                line = PrintTerminalID(line, trxn_log->sz9TerminalID);
            } else {
                line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
            }

            // "Merchant ID:",
            if (strlen(trxn_log->sz16MerchantID)) {
                line = PrintMerchantID(line, trxn_log->sz16MerchantID);
            } else {
                //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
                line = PrintMerchantID(line, pstParams->szMerchantID);
            }

            // "************* BUY **************", or // "************* PAY **************", Buy transaction name
            line = PrintBuyTrxnName(line, trxn_log);

            str_to_bcd((char *) date, (char *) &trxn_log->uc64AdditionalData[20], 8);
            str_to_bcd((char *) time, (char *) &trxn_log->uc64AdditionalData[28], 6);
            // "Date       :",
            // "Time       :",
            line = PrintDateAndTime(line, date, time);

            // "PAN        : ",
            line = PrintPAN(line, (char *) &trxn_log->uc20Track2Data[1], (unsigned short) trxn_log->uc20Track2Data[0]);

            // "Approval No:",
            line = PrintApprovalNo(line, trxn_log);

            // "Ref. No    :",
            line = PrintReferenceNo(line, trxn_log);

            if (((trxn_type == TRXN_PURCHASE_ONLY) && trxn_log->ucBuyTrxnType)) {
                // "Customer ID:",
                line = PrintCustomerID(line, trxn_log);
            }

            if (trxn_type == TRXN_PURCHASE_ONLY) {
                // "Trace No   :",
                line = PrintTraceNo(line, trxn_log);
            }

            // "--------------------------------"
            line = PrintAllDashes(line);

            // "Amount(Rials)  :",
            line = PrintAmount(line, trxn_log);

            // "================================"
            line = PrintAllEquals(line);
            break;

        case 0x3302: // Print POS Last 20 Trans.
            if (first_flag) {
                // Merchant Name
                line = PrintMerchantName(line);
                line++;

                // "--------------------------------"
                line = PrintAllDashes(line);

                // " Print POS Last 20 Transactions ",
                strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1PrtLast20Trxn_0001]);
                BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);

                // "--------------------------------"
                line = PrintAllDashes(line);

                // Get the first transaction DB index of Last 20 Transactions
                if (iMaxDBCtrlIndex > 20) {
                    iStartDBCtrlIndex = iMaxDBCtrlIndex - 20;
                }
            }

            i = 0;
            while (1) {
                trxn_log = st_TrxnLogDB[iStartDBCtrlIndex].pstTrxnLogAddr;

                msg_type = HEX2_to_UnsignedShort((char *) trxn_log->uc2MsgType);
                proc_code = HEX3_to_Unsignedlong((char *) trxn_log->uc3ProcCode);
                GetTransactionType(&trxn_type, msg_type, proc_code);

                // "Terminal ID:",
                if (strlen(trxn_log->sz9TerminalID)) {
                    line = PrintTerminalID(line, trxn_log->sz9TerminalID);
                } else {
                    line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
                }

                // "Merchant ID:",
                if (strlen(trxn_log->sz16MerchantID)) {
                    line = PrintMerchantID(line, trxn_log->sz16MerchantID);
                } else {
                    //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
                    line = PrintMerchantID(line, pstParams->szMerchantID);
                }

                // Buy
                if (trxn_type == TRXN_PURCHASE_ONLY) {
                    // "************* BUY **************", // "************* PAY **************", or Buy transaction name
                    line = PrintBuyTrxnName(line, trxn_log);
                }

                str_to_bcd((char *) date, (char *) &trxn_log->uc64AdditionalData[20], 8);
                str_to_bcd((char *) time, (char *) &trxn_log->uc64AdditionalData[28], 6);
                // "Date       :",
                // "Time       :",
                line = PrintDateAndTime(line, date, time);

                // "PAN        : ",
                line = PrintPAN(line, (char *) &trxn_log->uc20Track2Data[1], (unsigned short) trxn_log->uc20Track2Data[0]);

                // "Approval No:",
                line = PrintApprovalNo(line, trxn_log);

                // "Ref. No    :",
                line = PrintReferenceNo(line, trxn_log);

                if (((trxn_type == TRXN_PURCHASE_ONLY) && trxn_log->ucBuyTrxnType)) {
                    // "Customer ID:",
                    line = PrintCustomerID(line, trxn_log);
                }

                if (trxn_type == TRXN_PURCHASE_ONLY) {
                    // "Trace No   :",
                    line = PrintTraceNo(line, trxn_log);
                }

                // "--------------------------------"
                line = PrintAllDashes(line);

                // "Amount(Rials)  :",
                line = PrintAmount(line, trxn_log);

                // "================================"
                line = PrintAllEquals(line);

                iStartDBCtrlIndex++;
                if (iStartDBCtrlIndex >= iMaxDBCtrlIndex) {
                    break;
                }
                i++;
                if (i >= 5) {
                    break;
                }
            }

            if (iStartDBCtrlIndex < iMaxDBCtrlIndex) {
                PrintSetFF(line, 0);
                return;
            }
            break;
    }

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

// Build Reprint Buy with external printer

void BuildReprintBuyWithExternalPrinter(_st_TrxnLog_ *trxn_log) {
    int i, j, line;
    char justify_mode;
    char item[33], msg[33];
    unsigned char date[4], time[3];

#ifdef USER_DEBUG
    Rprintf("\r\nBuildReprintBuyWithExternalPrinter()\r\n");
#endif
    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    line = 0;

    // Merchant Name
    line = PrintMerchantName(line);
    line++;

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Terminal ID:",
    if (strlen(trxn_log->sz9TerminalID)) {
        line = PrintTerminalID(line, trxn_log->sz9TerminalID);
    } else {
        line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
    }

    // "Merchant ID:",
    if (strlen(trxn_log->sz16MerchantID)) {
        line = PrintMerchantID(line, trxn_log->sz16MerchantID);
    } else {
        //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
        line = PrintMerchantID(line, pstParams->szMerchantID);
    }

    // "(Reprint)",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1ExtPrnReprint_0001]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);

    // "************* BUY **************", // "************* PAY **************", or Buy transaction name
    line = PrintBuyTrxnName(line, trxn_log);

    str_to_bcd((char *) date, (char *) &trxn_log->uc64AdditionalData[20], 8);
    str_to_bcd((char *) time, (char *) &trxn_log->uc64AdditionalData[28], 6);
    // "Date       :",
    // "Time       :",
    line = PrintDateAndTime(line, date, time);

    if (trxn_log->uc20Track2Data[0]) {
        // "PAN        : ",
        line = PrintPAN(line, (char *) &trxn_log->uc20Track2Data[1], (unsigned short) trxn_log->uc20Track2Data[0]);
    }

    // "Approval No:",
    line = PrintApprovalNo(line, trxn_log);

    // "Ref. No    :",
    line = PrintReferenceNo(line, trxn_log);

    // "Customer ID:",
    line = PrintCustomerID(line, trxn_log);

    // "Trace No   :",
    line = PrintTraceNo(line, trxn_log);

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Amount(Rials)  :",
    line = PrintAmount(line, trxn_log);

    // "================================"
    line = PrintAllEquals(line);

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

// Build Reprint Bill Payment with external printer

void BuildReprintBillPaymentWithExternalPrinter(_st_TrxnLog_ *trxn_log) {
    int i, j, line;
    char justify_mode;
    char item[33], msg[33];
    unsigned char date[4], time[3];

#ifdef USER_DEBUG
    Rprintf("\r\nBuildReprintBillPaymentWithExternalPrinter()\r\n");
#endif
    InitializePrinterParameter();
    ucPrintReceiptNo = 1;

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    line = 0;

    // Merchant Name
    line = PrintMerchantName(line);
    line++;

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Terminal ID:",
    if (strlen(trxn_log->sz9TerminalID)) {
        line = PrintTerminalID(line, trxn_log->sz9TerminalID);
    } else {
        line = PrintTerminalID(line, st_POSSetupInfo.sz9TerminalID);
    }

    // "Merchant ID:",
    if (strlen(trxn_log->sz16MerchantID)) {
        line = PrintMerchantID(line, trxn_log->sz16MerchantID);
    } else {
        //line = PrintMerchantID(line, st_POSSetupInfo.sz16MerchantID);
        line = PrintMerchantID(line, pstParams->szMerchantID);
    }

    // "(Reprint)",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1ExtPrnReprint_0001]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);

    // "********* BILL PAYMENT *********",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1BillPayment_000001]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);

    str_to_bcd((char *) date, (char *) &trxn_log->uc64AdditionalData[20], 8);
    str_to_bcd((char *) time, (char *) &trxn_log->uc64AdditionalData[28], 6);
    // "Date       :",
    // "Time       :",
    line = PrintDateAndTime(line, date, time);

    if (trxn_log->uc20Track2Data[0]) {
        // "PAN        : ",
        line = PrintPAN(line, (char *) &trxn_log->uc20Track2Data[1], (unsigned short) trxn_log->uc20Track2Data[0]);
    }

    // "Approval No:",
    line = PrintApprovalNo(line, trxn_log);

    // "Ref. No    :",
    line = PrintReferenceNo(line, trxn_log);

    // "Organization Name :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1OrganizationName_1]);
    BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, LEFT_JUSTIFIED, ucLangFlag);

    i = strlen(trxn_log->sz34F11FarsiOrganizationName);
    if (i) {
        if (i <= 32) {
            j = i;
        } else {
            j = 32;
        }
        memset(msg, 0x00, sizeof (msg));
        memcpy(msg, &trxn_log->sz34F11FarsiOrganizationName[0], j);
        // Convert Iranian Farsi Code to Bitel Farsi Code
        IranianCode2BitelFarsiCode(msg, strlen(msg));
        BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
        if ((i - j) > 0) {
            memset(msg, 0x00, sizeof (msg));
            memcpy(msg, &trxn_log->sz34F11FarsiOrganizationName[32], 1);
            // Convert Iranian Farsi Code to Bitel Farsi Code
            IranianCode2BitelFarsiCode(msg, strlen(msg));
            BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
        }
    } else {
        line++;
    }

    // "Trace No   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1TraceNo_0000000001]);
    memcpy_null(msg, trxn_log->uc6AIDRefence, 6);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Bill ID    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1BillID_00000000001]);
    memset(msg, 0x00, sizeof (msg));
    bcd_to_str(msg, (char *) &trxn_log->uc10BillID[1], trxn_log->uc10BillID[0]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Payment ID :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1PaymentID_00000001]);
    memset(msg, 0x00, sizeof (msg));
    bcd_to_str(msg, (char *) &trxn_log->uc10PaymentID[1], trxn_log->uc10PaymentID[0]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "--------------------------------"
    line = PrintAllDashes(line);

    // "Amount(Rials)  :",
    line = PrintAmount(line, trxn_log);

    // "================================"
    line = PrintAllEquals(line);

    line = PrintStoreAdvertisement(line);

    line++;
    // Application version for receipt
    line = PrintApplicationVersion(line);
    // Powered by PayMaster
    line = PrintPoweredbyPayMaster(line);

    PrintSetFF(line, PRT_PAPER_FORM_FEED_LINE);
}

int PrintCardSystem(int line) {
    char msg[33];

    // "  Card System  ",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1CardSystem_0000001]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, ucLangFlag);
    return line;
}

int PrintPaymasterLogo(int line) {
    int i;

    // Paymaster Logo Image
    i = ((unsigned short) PMPrinterLogo[2] << 8) | (unsigned short) PMPrinterLogo[3]; // Image Height
    /*
            void ASSIGN_GRAPHICS(char* , char or int);
            : Address point input for graphics data  
            : assign graphics data to 0 to 4 number to handle for printing
     */
    ASSIGN_GRAPHICS((char *) &PMPrinterLogo[0], 0);
    ATTB_BUFFER1[0][line][0] = PRT_GRAPHICS_MODE + 0;
    line += (i + 23) / 24;
    return line;
}

int PrintApplicationVersion(int line) {
    char msg[33];

    // Application version for receipt
    // "         <Version x.xx>         "
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1SoftwareVersion_01]);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
    return line;
}

int PrintPoweredbyPayMaster(int line) {
    char msg[33];

    strcpy(msg, "Powered by PayMaster");
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
    return line;
}

int PrintStoreName(int line) {
    char msg[33];

    if (strlen(st_POSSetupInfo.sz33StoreName)) {
        // Store Name
        strcpy(msg, st_POSSetupInfo.sz33StoreName);
        BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, 0);
    }
    return line;
}

int PrintMerchantName(int line) {
    char msg[33];

    if (strlen(st_POSSetupInfo.sz33StoreName)) {
        // Store Name
        strcpy(msg, st_POSSetupInfo.sz33StoreName);
        BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, CENTER_JUSTIFIED, 0);
    }
    return line;
}

int PrintMerchantAddress(int line) {
    char msg[33];

    if (strlen(st_POSSetupInfo.sz33StoreName)) {
        // Store Name
        strcpy(msg, st_POSSetupInfo.sz33StoreName);
        BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, 0);
    }
    return line;
}

int PrintMultiMerchantStoreName(int line, _st_TrxnLog_ *trxn_log) {
    int i, j;
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    char msg[33];

    if (strlen(st_POSSetupInfo.sz33StoreName)) {
        // Store Name
        strcpy(msg, st_POSSetupInfo.sz33StoreName);
        BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, 0);
    }
    return line;
}

int PrintULDateAndTime(int line, unsigned long ulDateTime) {
    _tDATE_TIME dt;
    U08 uc4Date[4], uc3Time[3];

    time_to_tm(ulDateTime, 0, &dt);
    uc4Date[0] = dt.CLKYEARH;
    uc4Date[1] = dt.CLKYEARL;
    uc4Date[2] = dt.CLKMONTH;
    uc4Date[3] = dt.CLKDATE;
    uc3Time[0] = dt.CLKHOUR;
    uc3Time[1] = dt.CLKMIN;
    uc3Time[2] = dt.CLKSEC;

    return PrintDateAndTime(line, uc4Date, uc3Time);
}

int PrintDateAndTime(int line, unsigned char *date, unsigned char *time) {
    char justify_mode;
    char item[33], msg[33];
    _tDATE_TIME dt;

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    dt.CLKYEARH = date[0];
    dt.CLKYEARL = date[1];
    dt.CLKMONTH = date[2];
    dt.CLKDATE = date[3];
    dt.CLKHOUR = time[0];
    dt.CLKMIN = time[1];
    dt.CLKSEC = time[2];

    if (ucLangFlag) {
        // Convert the Gregorian calendar to the Jalali(Moslem) calendar
        RTC_Gregorian2Jalali(&dt);
    }

    // "Date       :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Date_0000000000001]);
    sprintf(msg, "%02X%02X/%02X/%02X", dt.CLKYEARH, dt.CLKYEARL, dt.CLKMONTH, dt.CLKDATE);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Time       :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Time_0000000000001]);
    sprintf(msg, "%02X:%02X:%02X", dt.CLKHOUR, dt.CLKMIN, dt.CLKSEC);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    return line;
}

int PrintBuyTrxnName(int line, _st_TrxnLog_ *trxn_log) {
    int len, position;
    char msg[33];

    // "************* BUY **************",
    strcpy(msg, PRT_MSG_TBL1[ucLangFlag][P1BuyTrxn_0000000001]);

    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
    return line;
}

int PrintMerchantID(int line, char *merchant_id) {
    char justify_mode;
    char item[33], msg[33], temp[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Merchant ID:",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1MerchantID00000001]);
    memcpy_null(temp, merchant_id, 15);
    memset(msg, 0x00, sizeof (msg));
    RemoveLeadingAndTrailingSpaces(msg, temp, strlen(temp));
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintTerminalID(int line, char *terminal_id) {
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Terminal ID:",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1TerminalID_0000001]);
    memcpy_null(msg, terminal_id, 8);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintPOSSerialNo(int line) {
    int i;
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "POS S/N    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1POSSerialNo_000001]);
    memset(msg, 0x00, sizeof (msg));
    i = GET_PROD_ID(msg);
    if (i == 0) {
        BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    } else {
        BuildPrintLine(line++, item, strlen(item), NULL, 0, PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    }
    return line;
}

int PrintPAN(int line, char *track2data, unsigned short len) {
    char justify_mode;
    char item[33], msg[33];
    char track2_data[38];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // Recover Track 2 Data
    memset(track2_data, 0x00, sizeof (track2_data));
    zbcd_to_str(track2_data, track2data, len);

    // Recover PAN
    memset(msg, 0x00, sizeof (msg));
    MSR_GetCardPAN(track2_data, msg);
    if (strlen(msg) > 10) {
        memset(&msg[6], '*', strlen(msg) - 10);
    }

    // "PAN        : ",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1PAN_00000000000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintApprovalNo(int line, _st_TrxnLog_ *trxn_log) {
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    char justify_mode;
    char item[33], msg[33];

    msg_type = HEX2_to_UnsignedShort((char *) trxn_log->uc2MsgType);
    proc_code = HEX3_to_Unsignedlong((char *) trxn_log->uc3ProcCode);
    GetTransactionType(&trxn_type, msg_type, proc_code);

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Approval No:",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1ApprovalNo_0000001]);
    // Buy (Offline)
    if (trxn_type == TRXN_PURCHASE_ONLY && trxn_log->ucStatus.BIT.OnlineFlag == 0) {
        strcpy(msg, "Offline");
    } else {
        memcpy_null(msg, trxn_log->uc6ApprovalCode, 6);
    }
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintReferenceNo(int line, _st_TrxnLog_ *trxn_log) {
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Ref. No    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1ReferenceNo_000001]);
    bcd_to_str(msg, trxn_log->uc6ReferenceNo, 12);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintCustomerID(int line, _st_TrxnLog_ *trxn_log) {
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Customer ID:",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1CustomerID_0000001]);
    bcd_to_str(msg, &trxn_log->uc10BillID[1], trxn_log->uc10BillID[0]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintBatchNo(int line, _st_TrxnLog_ *trxn_log) {
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Batch No   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1BatchNo_0000000001]);
    sprintf(msg, "%d", trxn_log->usBatchNo);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintSeqNo(int line, _st_TrxnLog_ *trxn_log) {
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Seq. No    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SeqNo_000000000001]);
    sprintf(msg, "%d", trxn_log->usSeqNo);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintTraceNo(int line, _st_TrxnLog_ *trxn_log) {
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Trace No   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1TraceNo_0000000001]);
    memcpy_null(msg, trxn_log->uc6AIDRefence, 6);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintAmount(int line, _st_TrxnLog_ *trxn_log) {
    double amount;
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Amount(Rials)  :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Amount_00000000001]);
    BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    bcd_to_str(msg, trxn_log->uc6Amount, 12);
    amount = atof(msg);
    sprintf(msg, "%.0lf", amount);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintBalance(int line, _st_TrxnLog_ *trxn_log) {
    double amount;
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Balance(Rials) :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Balance_0000000001]);
    BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    memcpy_null(msg, trxn_log->uc25AdditionalResponseData, 12);
    amount = atof(msg);
    sprintf(msg, "%.0lf", amount);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, justify_mode, ucLangFlag);
    return line;
}

#if 0 // sispp 20111008

int PrintBillPaymentContents(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log) {
    int i, j;
    char justify_mode;
    char item[33], msg[33];
    char temp[1003], bill_payment_data[1003];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    // "Organization Name :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1OrganizationName_1]);
    BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, LEFT_JUSTIFIED, ucLangFlag);

    memset(bill_payment_data, 0x00, sizeof (bill_payment_data));
    if (trxn_type == TRXN_BILL_PAYMENT) {
        strcpy(bill_payment_data, st_TrxnRespData.F121aL3_sz1003BillPaymentData2);
    } else {
        strcpy(bill_payment_data, st_TrxnReqData.F121aL3_sz1003BillPaymentData2);
    }
    ParseField121BillPaymentData((unsigned char *) bill_payment_data);

    // "Trace No   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1TraceNo_0000000001]);
    memcpy_null(msg, trxn_log->uc6AIDRefence, 6);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Bill ID    :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1BillID_00000000001]);
    strcpy(msg, st_TrxnReqData.sz19BillID);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Payment ID :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1PaymentID_00000001]);
    strcpy(msg, st_TrxnReqData.sz19PaymentID);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    return line;
}

int PrintSIMChargeContents(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log) {
    int i, j;
    char justify_mode;
    char item[33], msg[33];
    char temp[1003], bill_payment_data[1003];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    memset(bill_payment_data, 0x00, sizeof (bill_payment_data));
    strcpy(bill_payment_data, st_TrxnRespData.F121aL3_sz1003BillPaymentData2);
    ParseField121BillPaymentData((unsigned char *) bill_payment_data);

    // "Serial No  :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1SerialNo_000000001]);
    memset(bill_payment_data, 0x00, sizeof (bill_payment_data));
    if (trxn_type == TRXN_BILL_PAYMENT) {
        strcpy(bill_payment_data, st_TrxnRespData.F048aL3_sz1003BillPaymentData1);
    } else {
        strcpy(bill_payment_data, st_TrxnReqData.F048aL3_sz1003BillPaymentData1);
    }
    memset(msg, 0x00, sizeof (msg));
    memset(temp, 0x00, sizeof (temp));
    memcpy(temp, bill_payment_data, 3);
    i = atoi(temp);
    if (i == 108) {
        //memcpy(msg, &bill_payment_data[51], 16);
        RemoveTrailingSpaces(msg, &bill_payment_data[51], 16);
    }
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Voucher No",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1VoucherNo_00000001]);
    BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, justify_mode, ucLangFlag);
    i = strlen(uc21F06BoughtChargePassword);
    memset(msg, 0x00, sizeof (msg));
    if (i && (trxn_type == TRXN_BILL_PAYMENT) && usResponseCode == 0x3030) {
        strcpy(msg, uc21F06BoughtChargePassword);
    }
    // "Farsi No   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1FarsiNo_0000000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, 1);
    // "English No :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1EnglishNo_00000001]);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, 0);

    // "Trace No   :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1TraceNo_0000000001]);
    memcpy_null(msg, trxn_log->uc6AIDRefence, 6);
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    // "Help Desk  :",
    strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1BillPayHelpDesk_01]);
    memset(msg, 0x00, sizeof (msg));
    i = strlen(uc17F09HelpDesk);
    if (i) {
        strcpy(msg, uc17F09HelpDesk);
    }
    BuildPrintLine(line++, item, strlen(item), msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    return line;
}
#endif // sispp 20111008

int PrintStoreAdvertisement(int line) {
    int i;
    char justify_mode;
    char msg[33];

    if (ucLangFlag) {
        justify_mode = RIGHT_JUSTIFIED;
    } else {
        justify_mode = LEFT_JUSTIFIED;
    }
    /*
            for (i = 0; i < 3; i++) {
                    if (strlen(st_POSSetupInfo.sz33StoreAdvertisement[i])) {
                            strcpy(msg, st_POSSetupInfo.sz33StoreAdvertisement[i]);
                            BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_NORMAL_MODE, justify_mode, ucLangFlag);
                    }
            }
     */
    return line;
}

int PrintTotal(int line, unsigned short trxn_type, _st_TrxnLog_ *trxn_log) {
    double amount;
    char justify_mode;
    char item[33], msg[33];

    if (ucLangFlag) {
        justify_mode = LEFT_JUSTIFIED;
    } else {
        justify_mode = RIGHT_JUSTIFIED;
    }

    switch (trxn_type) {
        default:
            // "Total(Rials)   :",
            strcpy(item, PRT_MSG_TBL1[ucLangFlag][P1Total_000000000001]);
            break;
    }
    BuildPrintLine(line++, item, strlen(item), "", 0, PRT_NORMAL_MODE, justify_mode, ucLangFlag);

    memcpy_null(msg, &trxn_log->uc64AdditionalData[14], 12);
    amount = atof(msg);
    sprintf(msg, "%.0lf", amount);
    KEY_InsertCommaAndDot(c65CommaAndDotString, msg, ucCurrencyExp);
    strcpy(msg, c65CommaAndDotString);
    BuildPrintLine(line++, "", 0, msg, strlen(msg), PRT_DOUBLE_WIDTH_MODE, justify_mode, ucLangFlag);
    return line;
}

int PrintAllStars(int line) {
    // "********************************",
    BuildPrintLine(line++, "", 0, (char *) PRT_MSG_TBL1[ucLangFlag][P1AllStars_000000001], PRT_CHARACTERS_PER_LINE, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
    return line;
}

int PrintAllDashes(int line) {
    // "--------------------------------",
    BuildPrintLine(line++, "", 0, (char *) PRT_MSG_TBL1[ucLangFlag][P1AllDashes_00000001], PRT_CHARACTERS_PER_LINE, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
    return line;
}

int PrintAllEquals(int line) {
    // "================================",
    BuildPrintLine(line++, "", 0, (char *) PRT_MSG_TBL1[ucLangFlag][P1AllEquals_00000001], PRT_CHARACTERS_PER_LINE, PRT_NORMAL_MODE, CENTER_JUSTIFIED, ucLangFlag);
    return line;
}

#ifdef USER_DEBUG

void OutputReceiptData(int line) {
    int i, j;
    unsigned char *ptr, ch, str[33];

    //	Rprintf("\r\nOutputReceiptData()\r\n");
    //	Rprintf("line = %d\r\n", line);
    //	Rprintf("================================\r\n");

    ptr = (unsigned char *) CHAR_BUFFER1[0];
    for (i = 0; i < line; i++) {
        memset(str, 0x00, sizeof (str));
        memcpy(str, ptr, 32);
        for (j = 0; j < 32; j++) {
            ch = str[j];
            if (ch == 0x00) {
                ch = ' ';
            } else if ((ch >= 0xA0 && ch <= 0xA9)) {
                ch = (ch - 0xA0) + '0';
            } else if (ch >= 0x80) {
                ch = '.';
            }
            Rprintf("%c", ch);
        }
        ptr += 32;
        Rprintf("\r\n");
    }

    //	Rprintf("================================\r\n");
}
#endif


/* */
