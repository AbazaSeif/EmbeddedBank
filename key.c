
/*======================================================================*/
/*																		*/
/*								KEY.C									*/
/*																		*/
/*======================================================================*/

#include "system.h"
#include "extern.h"

// begin sispp 20111010
extern char CardNo2[52];
extern U08 SelectedAID[17];
extern int GetEncryptedTrack2(char *pTrack2, char *pOutBuf);
// end sispp 20111010
char sz17TrxnTitle[17];
long lCallHome1SECTimer;
_st_EndOfDay_ st_EndOfDay;


const unsigned short tbl_MainService[][48] = {
    // Initial Status													- MSS_INITIAL
    {0x0000, 0x0001, 0x0002,},

    // Special Functions												- MSS_SPECIAL_FUNC
    { 0x0100, // Input Maintenance's Password
        0x0011, // Select Maintenance menu item
        0x0012, // Display LCD Message or Printer Message for debug mode
    },

    {0x1100,}, // Select Setup Terminal Menu

    {0x1160, // Select GSM/GPRS setup menu item
        0x1161, 0x1162, 0x1163, 0x1164, // Input GSM/GPRS Parameters
        0x1165, 0x1166, // Reserved for Future Use
        0x1167, 0x1168, 0x1169, 0x116A, // Input GSM/GPRS Server
        0x116B, 0x116C, 0x116D, 0x116E, // Input GSM/GPRS TMS Server
        0x116F, // Reserved for Future Use
    },

    {0x1180, // Select Set Parameters menu item
        0x1181, // Input Terminal ID
        0x1182, // Input Sequence No
        0x1183, // Input Store Name
    },

    {0x11B0,}, // Set Help Desk Telephone No

    {0x11D0, 0x11D1, 0x11D2, 0x11D3,}, // POS Serial Number

    {0x11E0, 0x11E1, 0x11E2, 0x11E3, 0x11E4, 0x11E5, // Download All Parameters
        0x11E6, 0x11E7, 0x11E8, 0x11E9,},

    {0x11F0, 0x11F1, 0x11F2, 0x11F3,}, // CallHome

    {0x1200, // Select POS Information menu item
        0x1201, 0x1202, 0x1203, 0x1204, 0x1205, 0x1206, 0x1207, // View Information
        0x1208, // Print Information
    },

    {0x1300, // Initialize - Select Initialize menu item
        0x1301, // Reset Parameters
        0x1302, // Reset Merchant
        0x1303, // Erase Transaction Logs
    },

    {0x1400, 0x1401,}, // Change Master's Password

    {0x1500,}, // Select Hardware Test menu item
    {0x1510,}, // Printer Test
    {0x1520,}, // MSR Test
    {0x1530, 0x1531, 0x1532, 0x1533, 0x1534, 0x1535,}, // Modem Test
    {0x1540,}, // IC Card Test
    {0x1550,}, // Key Test
    {0x1560,}, // LCD Test
    {0x1570,}, // RS232 Test
    {0x1580,}, // RTC Test

    // F1 Functions														- MSS_F1_FUNC
    {0x2000, // Input Supervisor Password
        0x2001, // Select Supervisor menu item
    },

    {0x2100, 0x2101, 0x2102, 0x2103, 0x2104, 0x2105, 0x2106,}, // MST_F1_REVERSAL_TRANS
    {0x2110, 0x2111, 0x2112, 0x2113, 0x2114, 0x2115,}, // MST_F1_ENDOFDAY
    {0x2120, 0x2121, 0x2122, 0x2123, 0x2124, 0x2125,}, // MST_F1_EOD_TODAY
    {0x2130, 0x2131, 0x2132, 0x2133, 0x2134, 0x2135,}, // MST_F1_EOD_REPRINT
    {0x2140, 0x2141, 0x2142, 0x2143, 0x2144, 0x2145,}, // MST_F1_EOD_PASTDAY

    {0x2600, 0x2601,}, // Change Merchant's Password

    {0x2900, // Display Select TMS menu
        0x290A, // Select TMS menu for Ethernet
        0x290B, 0x290C, 0x290D, 0x290E, // Setup TMS Server for Ethernet
        0x290F, 0x2910, // Select Remote Download for Ethernet
    },

    // F3 Functions														- MSS_F3_FUNC
    {0x4000,}, // Select Setup POS Status menu item
    {0x4100,}, // Set CallHome
    {0x4200,}, // Set Comm Timeout
    {0x4300,}, // Input Date
    {0x4400,}, // Input Time
    {0x4500,}, // Set LCD Contrast
    {0x4600,}, // Set Beep Sound

    // Customer Trans.													- MSS_CUSTOMER_TRANS
    {0x5000, // Retry to swipe magnetic striped card
        0x5001, // Swipe Card or Insert Smart Card - Select Customer trans.
        0x5002, // Swipe Card or Insert Smart Card - After Selecting Customer trans.
    },
    {0x5100, 0x5101, 0x5102, 0x5103, 0x5104, 0x5105, 0x5106, 0x5107, // Buy
        0x5108, 0x5109, 0x510A, 0x510B, 0x510C, 0x510D, 0x510E, 0x510F,
        0x5110, 0x5111, 0x5112, 0x5113, 0x5114, 0x5115, 0x5116, 0x5117,
        0x5118, 0x5119},
    {0x5100, 0x5101, 0x5102, 0x5103, 0x5106, 0x5200, 0x5201, 0x5202, // Balance
        0x5203, 0x5204, 0x5205, 0x5206, 0x5207, 0x5208, 0x5209, 0x520A,
        0x520B,},
    {0x0000,},
    {0x5100, 0x5101, 0x5A10, 0x5A11, 0x5A12, 0x5104, 0x5105, 0x5A00, // SIM Charge
        0x5A01, 0x5A02, 0x5102, 0x5103, 0x5106, 0x5400, 0x5108, 0x5109,
        0x5406, 0x5407, 0x5408, 0x5409, 0x540A, 0x540B,},

    // Reversal															- MSS_REVERSAL
    {0x9000, 0x9001,}, // Print Reversal Receipt
    {0x9100,}, // Reversal Mode
    {0x9200, 0x9201,}, // Reversal
    {0x9300, // Input Merchant's or Cashier's Password
        0x9301, // Set Telephone menu item
        0x9302, 0x9303, 0x9304, 0x9305, 0x9306, // Select PABX Access
        0x9307, // Input Telephone No
        0x9308, // Pulse Dial
        0x9309, // Input Server IP Address 1
        0x930A, // Input Server Port Number 1
        0x930B, // Input GSM City Access Code
        0x930C, // Input GSM Telephone No
    },
    {0x9400, 0x9401,}, // Print Unsuccessful Reversal Receipt
};


unsigned short usMainStatus;
unsigned short *pusServiceAddr;
unsigned short usAutoInitial10MSTimer;
unsigned short usAutoReversal10MSTimer;
unsigned short usReversalPrint10MSTimer;
short sVirtualKey;
short sTempKey;
char cXPos;
char cYPos;
char cMaxInputCnt;
char c65CommaAndDotString[65];
char c65TempKeyBuf[65];
char c65TempBuf[65];


void KeyTask(void);
void InputKeyService(int key);
void EnterKeyService(void);
void CancelKeyService(void);
void SetInitialStatus(void);
void InitializeGlobalVariables(void);
void ClearTempKeyBufAndStringCopy(char *str);
void MainStatusSetting(unsigned short Status, short ServiceTableNo, short DisplayMsgNo, char HighlightLine, char lang);
void ErrorDisplayAndGoInitialStatus(short DisplayMsgNo, char HighlightLine, char lang);
void ErrorDisplayAndGoErrorStatus(short DisplayMsgNo, char HighlightLine, char lang);
void DisplayTrxnTelNo(void);
void ResetTrxnTelNo(void);
void DisplayEODTelNo(void);
void ResetEODTelNo(void);
void DisplayBlackListTelNo(void);
void ResetBlackListTelNo(void);
void DisplayTMSTelNo(void);
void ResetTMSTelNo(void);
void DisplayHelpDeskTelNo(void);
void ResetHelpDeskTelNo(void);
#ifdef USER_DEBUG
void DisplayLCDMsgOrPrinterMsgInDebugMode(void);
#endif


extern char gbEmvScTaskStep;
extern int isDetectCard;




extern PARAMS *pstParams; // 2K



// Transaction ���Խ����� ȣ�� - �ʱ���¿��� EnterŰ�� �����ų� ī�带 ���� ���

int InitTrxnReqData() {
    st_TrxnReqData.usTrxnType = TRXN_NULL;
    LoadPOSUtilBuf();
    st_TrxnReqData.usBatchNo = tPOSUtilBuf.usBatchNo;
    st_TrxnReqData.usSeqNo = tPOSUtilBuf.usSeqNo + 1;
    if (st_TrxnReqData.usBatchNo <= 0) {
        return -1;
    }
    strcpy(st_TrxnReqData.sz16MerchantID, pstParams->szMerchantID);
    st_TrxnReqData.ulDateTime = GetULDateTime(); // Transaction ���� ����� ������ UPDATE
    memset(st_TrxnReqData.sz42Track2Data, 0x00, sizeof (st_TrxnReqData.sz42Track2Data)); // GetTrack2Data(st_TrxnReqData.sz42Track2Data);	// ī���а� UPDATE
    memset(st_TrxnReqData.sz4CVV, 0x00, sizeof (st_TrxnReqData.sz4CVV)); // GetCVV(st_TrxnReqData.sz4CVV);	// ī���а� UPDATE
    strcpy(st_TrxnReqData.sz7OperatorNo, "1"); // Operator �Է��� �޴´ٸ� UPDATE
    st_TrxnReqData.ucSupervisor = 'N';
    strcpy(st_TrxnReqData.sz13Amount, "0");
    strcpy(st_TrxnReqData.sz13Cashback, "0");
    strcpy(st_TrxnReqData.sz13Tip, "0");
    strcpy(st_TrxnReqData.sz5Budget, "0");

    //memset(st_TrxnReqData.sz13Amount, 0x00, sizeof(st_TrxnReqData.sz13Amount));	// Amount �Է��� �ް� UPDATE
    //memset(st_TrxnReqData.sz13Cashback, 0x00, sizeof(st_TrxnReqData.sz13Cashback));	// Cashback �Է��� �ް� UPDATE
    //memset(st_TrxnReqData.sz13Tip, 0x00, sizeof(st_TrxnReqData.sz13Tip));	// Tip �Է��� �ް� UPDATE
    //memset(st_TrxnReqData.sz5Budget, 0x00, sizeof(st_TrxnReqData.sz5Budget));	// Budget �Է��� �ް� UPDATE
    st_TrxnReqData.ucAccount = 0; // Account ���� �� UPDATE

    strcpy(st_TrxnReqData.sz17PinBlock, "OFFLINE"); // ���Է� �� UPDATE
    //	memset(st_TrxnReqData.sz17PinBlock, 0x00, sizeof(st_TrxnReqData.sz17PinBlock));	// ���Է� �� UPDATE
    memset(st_TrxnReqData.sz21KSN, 0x00, sizeof (st_TrxnReqData.sz21KSN)); // ���Է� �� DUKPT�� ��� UPDATE
    st_TrxnReqData.ucOffline = 'N';
    st_TrxnReqData.ucManual = 'N';

    memset(st_TrxnReqData.sz13ReferenceCode, 0x00, sizeof (st_TrxnReqData.sz13ReferenceCode));

    st_TrxnReqData.usOrigSeqNo = 0;
    memset(st_TrxnReqData.sz9OrigTerminalID, 0x00, sizeof (st_TrxnReqData.sz9OrigTerminalID));
    st_TrxnReqData.ulReversalDateTime = 0;
    st_TrxnReqData.usReversalTrxnType = 0;
    memset(st_TrxnReqData.sz13ReferenceNo, 0x00, sizeof (st_TrxnReqData.sz13ReferenceNo));

    bcd2asc(st_TrxnReqData.sz4CurrencyCode, pstParams->ucCurrCode, 4);
    memset(st_TrxnReqData.sz13ProcessorFee, 0x00, sizeof (st_TrxnReqData.sz13ProcessorFee));
    memset(st_TrxnReqData.sz13AcquiringFee, 0x00, sizeof (st_TrxnReqData.sz13AcquiringFee));
    memset(st_TrxnReqData.sz41AdditionalData, 0x00, sizeof (st_TrxnReqData.sz41AdditionalData));
    memset(st_TrxnReqData.sz512IccData, 0x00, sizeof (st_TrxnReqData.sz512IccData)); // GetTrxnIccData(st_TrxnReqData.sz512IccData);	// ICC Processing �� UPDATE
    memset(st_TrxnReqData.uc6AuthID, 0x00, sizeof (st_TrxnReqData.uc6AuthID));

    return 0;
}

extern int BuildIccData(char *pBuf);

int BuildTrxnQueryString(char *pBuf, int iMultiTrxnNo) {
    char temp[512];

    GetNextTrxnParameter(&RealTime, 0);

    if (iMultiTrxnNo == 0) {
        pBuf[0] = 0x00;
    } else {
        strcat(pBuf, "&");
    }
    sprintf(temp, "T[%d]=", iMultiTrxnNo);
    strcat(pBuf, temp);
    // 1.  Transaction Type
    sprintf(temp, "%d", st_TrxnReqData.usTrxnType);
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 2.  Batch Number - The batch number currently in use (see EFT Reconcile)
    sprintf(temp, "%d", st_TrxnReqData.usBatchNo);
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 3.  Sequence Number - The sequence number currently in use for the batch.
    sprintf(temp, "%d", st_TrxnReqData.usSeqNo);
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 4.  Merchant ID/IRN - The unique TAMS merchant ID number
    strcat(pBuf, st_TrxnReqData.sz16MerchantID);
    strcat(pBuf, ",");

    // 5.  Date and time - The transaction date and time (UNIX time stamp)
    st_TrxnReqData.ulDateTime = GetULDateTime();
    sprintf(temp, "%lu", st_TrxnReqData.ulDateTime);
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 6.  Track 2 - Track 2 data in plain-text (not-recommended) or encrypted with 3DES prefixed with an "E" (highly recommended)
    // sz42Track2Data ����Ÿ�� ī�带 ���� �� ��ȣȭ�Ǿ� ����Ǿ� �ִ� ��
    memcpy(&st_TrxnReqData.sz42Track2Data[0], &CardNo2[1], CardNo2[0]);
    st_TrxnReqData.sz42Track2Data[CardNo2[0]] = 0x00;
    // strcpy(st_TrxnReqData.sz42Track2Data, "4424349999968937=12102261338113800000");	// "5061200300103988118=1402601072131861");

    strcat(pBuf, "E");
    GetEncryptedTrack2(st_TrxnReqData.sz42Track2Data, temp);
    strcat(pBuf, temp);
    //	strcat(pBuf, st_TrxnReqData.sz42Track2Data);
    strcat(pBuf, ",");
    // 7.  CVV - CVV data (Optional)
    strcat(pBuf, st_TrxnReqData.sz4CVV);
    strcat(pBuf, ",");
    // 8.  Operator - Terminal operator number
    strcat(pBuf, st_TrxnReqData.sz7OperatorNo);
    strcat(pBuf, ",");
    // 9.  Supervisor - Indicates if a supervisor is processing the transaction
    temp[0] = st_TrxnReqData.ucSupervisor;
    temp[1] = 0x00;
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 10. Amount - The amount to process
    strcat(pBuf, st_TrxnReqData.sz13Amount);
    strcat(pBuf, ",");
    // 11. Cashback - The cashback amount (Optional)
    strcat(pBuf, st_TrxnReqData.sz13Cashback);
    strcat(pBuf, ",");
    // 12. Tip - The tip amount (Optional)
    strcat(pBuf, st_TrxnReqData.sz13Tip);
    strcat(pBuf, ",");
    // 13. Budget - The budget months (Optional)
    strcat(pBuf, st_TrxnReqData.sz5Budget);
    strcat(pBuf, ",");
    // 14. Account - The account type (0=Default, 1=Savings, 2=Cheque/Current, 3=CreditCard)
    sprintf(temp, "%d", st_TrxnReqData.ucAccount);
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 15. PIN Block - Encrypted card PIN number block (Hex).
    strcat(pBuf, st_TrxnReqData.sz17PinBlock);
    strcat(pBuf, ",");
    // 16. Key Serial Number - KSN used for DUKPT translation (leave empty for 3DES encrypted PINBlocks)
    strcat(pBuf, st_TrxnReqData.sz21KSN);
    strcat(pBuf, ",");
    // 17. Offline - Indicates if this transaction was done offline (Y/N)
    temp[0] = st_TrxnReqData.ucOffline;
    temp[1] = 0x00;
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 18. Manual - Indicates if this transaction is a manual transaction (Y/N)
    temp[0] = st_TrxnReqData.ucManual;
    temp[1] = 0x00;
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 19. Original Sequence Number - Original transaction sequence number to reverse
    if (st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
        sprintf(temp, "%u", st_TrxnReqData.usOrigSeqNo);
        strcat(pBuf, temp);
    }
    strcat(pBuf, ",");
    // 20. Reserved for future use.
    strcat(pBuf, ",");
    // 21. Reference code - The reference code, used for reporting purposes. For instance, this can be a
    //     customer name, smartcard number, invoice number, etc. (Optional)
    strcat(pBuf, st_TrxnReqData.sz13ReferenceCode);
    strcat(pBuf, ",");
    // 22. Original Terminal ID - The original terminal that processed the transaction (reversal only)
    if (st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
        strcat(pBuf, st_TrxnReqData.sz13ReferenceCode);
    }
    strcat(pBuf, ",");
    // 23. Reversal Date and time - The date and time of the original transaction (reversal only)
    if (st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
        sprintf(temp, "%lu", st_TrxnReqData.ulReversalDateTime);
        strcat(pBuf, temp);
    }
    strcat(pBuf, ",");
    // 24. Reversal Transaction Type - The transaction type to reverse (reversal only)
    if (st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
        sprintf(temp, "%d", st_TrxnReqData.usReversalTrxnType);
        strcat(pBuf, temp);
    }
    strcat(pBuf, ",");
    // 25. Reversal Reference Number - The RefNo (STAN) of the original transaction (reversal only)
    if (st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
        strcat(pBuf, st_TrxnReqData.sz13ReferenceNo);
    }
    strcat(pBuf, ",");
    // 26. Currency Code - The currency code of the transaction (e.g. 566)
    strcat(pBuf, st_TrxnReqData.sz4CurrencyCode);
    strcat(pBuf, ",");
    // 27. Processor Fee - The processor fee (Optional)
    strcat(pBuf, st_TrxnReqData.sz13ProcessorFee);
    strcat(pBuf, ",");
    // 28. Acquiring Fee - The acquiring fee (Optional)
    strcat(pBuf, st_TrxnReqData.sz13AcquiringFee);
    strcat(pBuf, ",");
    // 29. Additional Data
    strcat(pBuf, st_TrxnReqData.sz41AdditionalData);
    strcat(pBuf, ",");
    // 30. Reserved for future use.
    strcat(pBuf, ",");
    // 31. Reserved for future use.
    strcat(pBuf, ",");
    // 32. Reserved for future use.
    strcat(pBuf, ",");
    // 33. Reserved for future use.
    strcat(pBuf, ",");
    // 34. ICC Data (in HEX) delimited by pipe "|" characters
    strcat(pBuf, st_TrxnReqData.sz512IccData);
    strcat(pBuf, ",");
    // 35. Auth ID - The Pre-Auth ID for Adjustments and Completion
    strcat(pBuf, st_TrxnReqData.uc6AuthID);

    return strlen(pBuf);
}

int BuildEftTotalQueryString(char *pBuf) {
    int i;
    char temp[512];

    memset((char *) &st_EndOfDay, 0x00, sizeof (_st_EndOfDay_));

    //	T = PC = PRC = RC = RRC = 0;
    //	A = PV = PRV = RV = RRV = 0L;

    LoadPOSUtilBuf();
    st_EndOfDay.BATCHNO = tPOSUtilBuf.usBatchNo;
    if (st_EndOfDay.BATCHNO <= 0) {
        st_EndOfDay.BATCHNO = 0;
        usTrxnTotalCount = 0;
    }
    for (i = 0; i < usTrxnTotalCount; i++) {
        pstfTempTrxnLog = pstfFirstTrxnLog + i;
        if (pstfTempTrxnLog->usBatchNo != st_EndOfDay.BATCHNO || pstfTempTrxnLog->ucStatus.BIT.EODTxFlag == 0)
            continue;
        switch (pstfTempTrxnLog->usTrxnType) {
            case TRXN_PURCHASE_ONLY:
                st_EndOfDay.PC++;
                memset(temp, 0x00, sizeof (temp));
                bcd_to_str(temp, pstfTempTrxnLog->uc6Amount, 12);
                st_EndOfDay.PV += atol(temp);
                break;
            case TRXN_REVERSAL:
                st_EndOfDay.PRC++;
                memset(temp, 0x00, sizeof (temp));
                bcd_to_str(temp, pstfTempTrxnLog->uc6Amount, 12);
                st_EndOfDay.PRV += atol(temp);
                break;
        }
    }
    st_EndOfDay.T = st_EndOfDay.PC + st_EndOfDay.PRC + st_EndOfDay.RC + st_EndOfDay.RRC;
    st_EndOfDay.A = st_EndOfDay.PV + st_EndOfDay.PRV + st_EndOfDay.RV + st_EndOfDay.RRV;

    sprintf(pBuf, "BATCHNO=%d&T=%d&A=%ld&PC=%d&PV=%ld&PRC=%d&PRV=%ld&RC=%d&RV=%ld&RRC=%d&RRV=%ld",
            st_EndOfDay.BATCHNO, st_EndOfDay.T, st_EndOfDay.A, st_EndOfDay.PC, st_EndOfDay.PV,
            st_EndOfDay.PRC, st_EndOfDay.PRV, st_EndOfDay.RC, st_EndOfDay.RV, st_EndOfDay.RRC, st_EndOfDay.RRV);

    return strlen(pBuf);
}

extern unsigned char sz18GsmOperator[18]; // Operator Identifier/Name [0]:Format '0'=long alpha '1'=short alpha '2'=numeric

int BuildCallHomeQueryString(char *pBuf) {
    int i;
    char temp[512], cPwrStatus[16];

    memset(cPwrStatus, 0x00, sizeof (cPwrStatus));
    READ_POWER_SAVING_STATUS(15, cPwrStatus);

    // T=8400NG43AF02008801428551,20110001,EX_POWER_OPERATING,,,,,Radio OK,0,0,no RSSI,SIM OK,,No Location info,,No Operator info,,0,0,0,0,0,,Tech_Jumper_Off,No Phone Line,PRINTER IDLE,1326978170,INACTIVE

    // T - List of device information in CSV
    strcpy(pBuf, "T=");
    // 1. Device Serial Number
    memset(temp, 0x00, sizeof (temp));
    i = GET_PROD_ID(temp); // BNI51111200001
    if (i == 0) {
        strcat(pBuf, temp);
    }
    strcat(pBuf, ",");
    // 2. Terminal ID
    strcat(pBuf, st_POSSetupInfo.sz9TerminalID);
    strcat(pBuf, ",");
    // 3. Battery Status (string):
    //   1. "INT_BAT_OPERATING"
    //   2. "EX_POWER_OPERATING"
    strcat(pBuf, ((cPwrStatus[5] & 0xFF) ? "EX_POWER_OPERATING" : "INT_BAT_OPERATING"));
    strcat(pBuf, ",");
    // 4. Battery Version (int): Battery version number
    strcat(pBuf, ",");
    // 5. Battery Energy (int): Current battery level (0 - 100)
    sprintf(temp, "%d", ((cPwrStatus[8] & 0xFF) - 60) * 4);
    strcat(pBuf, temp);
    strcat(pBuf, ",");

    strcat(pBuf, ","); // ?????
    strcat(pBuf, ","); // ?????

    // 6. Radio Supported (string):
    //   1. "No Radio"
    //   2. "Radio Installed"
    if (sz17HWInfo[7] == 0x33 || sz17HWInfo[7] == 0x34 || sz17HWInfo[7] == 0x35) {
        strcat(pBuf, "Radio_Installed");
    } else {
        strcat(pBuf, "No_Radio");
    }
    strcat(pBuf, ",");
    // 7. Radio Level (int) - Radio signal strength (0 - 100)
    if (ucGprsRssiValue < 31) {
        i = ucGprsRssiValue * 3.3;
    } else if (ucGprsRssiValue == 31) {
        i = 100;
    } else { // include 99
        i = 0;
    }
    sprintf(temp, "%d", i);
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 8. Radio Base ID (int) - Radio signal base station ID
    strcat(pBuf, ",");
    // 9. Radio Status Info (string) - Free text information on the radio status (20)
    strcat(pBuf, ",");
    // 10. SIM Status
    // SIM OK
    strcat(pBuf, ",");
    // 11. SIM ID
    strcat(pBuf, ",");
    // 12. SIM Area Code
    // No Location info
    strcat(pBuf, ",");
    // 13. SIM Cell ID
    strcat(pBuf, ",");

    for (i = 0; i < strlen(sz18GsmOperator); i++) {
        if (sz18GsmOperator[i] == ' ') {
            sz18GsmOperator[i] = '_';
        }
    }
    // 14. SIM Operator ID
    if (sz18GsmOperator[0] == '2') {
        strcat(pBuf, &sz18GsmOperator[1]);
    }
    strcat(pBuf, ",");
    // 15. SIM Operator Name
    if (sz18GsmOperator[0] == '0' || sz18GsmOperator[0] == '1') {
        strcat(pBuf, &sz18GsmOperator[1]);
    }
    strcat(pBuf, ",");
    // 16. SIM Last Connect DateTime
    strcat(pBuf, ",");
    // 17. SIM Last Connect OK
    strcat(pBuf, ",");
    // 18. SIM No Network
    strcat(pBuf, ",");
    // 19. Modem Fatal Error
    strcat(pBuf, ",");
    // 20. Modem Error Message
    strcat(pBuf, ",");

    strcat(pBuf, ","); // ?????

    // 21. Tech Jumper
    strcat(pBuf, ",");
    // 22. Phone Line
    strcat(pBuf, "No_Phone_Line");
    strcat(pBuf, ",");
    // 23. Printer Status
    strcat(pBuf, "PRINTER_IDLE");
    strcat(pBuf, ",");
    // 24. Local Time Stamp
    sprintf(temp, "%ld", GetULDateTime());
    strcat(pBuf, temp);
    strcat(pBuf, ",");
    // 25. Idle Mode
    strcat(pBuf, "INACTIVE");

    return strlen(pBuf);
}

int SetReversalReqData(char *pSTAN) {
    int i, len;
    char bBinStanBuf[32];

    // �Ϸ�� Transaction�� �������� Reversal - STAN���� Transaction Log���� �ش� Transaction�� ã�Ƽ� ���õ� ���� ����
    // PRINTING�� FAIL - STAN�� NULL�̸� ������ Ʈ������� üũ�ؼ� Reversal��Ʈ�� Set�Ǿ� ������ �� Ʈ������� ������ ����
    if (pSTAN == NULL) {
        pstfTempTrxnLog = pstfSavingTrxnLog; //pstfLastTrxnLog
    } else {
        // Find TrxnLog using STAN
        U32 ulSTAN, ulLogRefNo;
        char temp[13];
        //len = strlen(pSTAN);
        //str_to_bcd(bBinStanBuf, pSTAN, len);
        ulSTAN = atol(pSTAN);
        //len = (len + 1) / 2;
        for (i = 0; i < usTrxnTotalCount; i++) {
            pstfTempTrxnLog = pstfFirstTrxnLog + i;
            memset(temp, 0x00, sizeof (temp));
            bcd_to_str(temp, pstfTempTrxnLog->uc6ReferenceNo, 12);
            ulLogRefNo = atol(temp);
            if (ulSTAN == ulLogRefNo) {
                break;
            }
        }
        if (i == usTrxnTotalCount) {
            // STAN is not found
            pstfTempTrxnLog = NULL;
            return -1;
        }
    }

    st_TrxnReqData.usTrxnType = TRXN_REVERSAL;

    memset(CardNo2, 0x00, sizeof (CardNo2));
    CardNo2[0] = pstfTempTrxnLog->uc20Track2Data[0];
    zbcd_to_str(&CardNo2[1], &pstfTempTrxnLog->uc20Track2Data[1], pstfTempTrxnLog->uc20Track2Data[0]);

    // 10. Amount - The amount to process
    {
        char temp[20];
        memset(temp, 0x00, sizeof (temp));
        bcd_to_str(temp, pstfTempTrxnLog->uc6Amount, 12);
        sprintf(st_TrxnReqData.sz13Amount, "%ld", atol(temp));
    }

    // 19. Original Sequence Number ? Original transaction sequence number to reverse
    st_TrxnReqData.usOrigSeqNo = pstfTempTrxnLog->usSeqNo; // reversal �ؾ��� Ʈ������� sequence number
    // 22. Original Terminal ID ? The original terminal that processed the transaction (reversal only)
    strcpy(st_TrxnReqData.sz9OrigTerminalID, st_POSSetupInfo.sz9TerminalID);
    //bcd_to_str(st_TrxnReqData.sz9OrigTerminalID, pstfTempTrxnLog->uc4OrigTerminalID, 8);

    // 23. Reversal Date and Time ? The date and time of the original transaction (reversal only)
    st_TrxnReqData.ulReversalDateTime = pstfTempTrxnLog->ulDateTime; // reversal �ؾ��� Ʈ������� datetime
    // 24. Reversal Transaction Type ? The transaction type to reverse (reversal only)
    st_TrxnReqData.usReversalTrxnType = pstfTempTrxnLog->usTrxnType; // reversal �ؾ��� Ʈ������� type
    // 25. Reversal Reference Number ? The RefNo (STAN) of the original transaction (reversal only)
    // ���� reversal�� STAN�� �Է¹޾� original transaction�� ã�Ƽ� reversal����
    // �ڵ� reversal��? TX�� RX����Ÿ�� ���޾��� ��� NULL???
    if (pSTAN == NULL) {
        memset(st_TrxnReqData.sz13ReferenceNo, 0x00, sizeof (st_TrxnReqData.sz13ReferenceNo));
    } else {
        bcd_to_str(st_TrxnReqData.sz13ReferenceNo, pstfTempTrxnLog->uc6ReferenceNo, 12);
    }

    return 0;
}

extern U16 giApplIdx;
extern int giRequestType;

int BuildQueryString() {
    memset(ucTrxnTxBuf, 0x00, sizeof (ucTrxnTxBuf));

    if (giRequestType == API_GET_FUNCLIST) {
        sprintf(ucTrxnTxBuf, "ApplId=%d&ApiVersion=%s", pstAppList[giApplIdx].usApplId, "1");
    } else if (giRequestType == API_TAMS_PARAM) {
        sprintf(ucTrxnTxBuf, "ver=%s&serial=%s", "3.8.21", "8400NG43AF02008801428551");
    } else if (giRequestType == API_BANK_EFTTRAN) {
        if (isDetectCard == 2 && gbEmvScTaskStep == 99) {
            BuildIccData(st_TrxnReqData.sz512IccData);
        }
        BuildTrxnQueryString(ucTrxnTxBuf, 0);
        // Save Tx Log if it is purchase OK 
    } else if (giRequestType == API_BANK_EFTTOTALS) {
        BuildEftTotalQueryString(ucTrxnTxBuf);
        // strcpy(ucTrxnTxBuf, "BATCHNO=0&T=0&A=0&PC=0&PV=0&PRC=0&PRV=0&RC=0&RV=0&RRC=0&RRV=0");
    } else if (giRequestType == API_TAMS_CALLHOME) {
        BuildCallHomeQueryString(ucTrxnTxBuf);
    }

    return strlen(ucTrxnTxBuf);
}

int dequeue_key() {
    int key;

    if (sVirtualKey != BTKEY_NULL) {
        key = sVirtualKey;
        sVirtualKey = BTKEY_NULL;
    } else {
        key = KEYSCAN() & 0xFF;
    }

    return key;
}

extern int TestParsing();
extern void SaveTxTransactionLog(void);
extern void EraseAllTransactionLog(void);
extern void time_to_tm(long totalsecs, int offset, _tDATE_TIME *result);

void KeyTask(void) {
    int i, key;

    key = KEYSCAN() & 0xFF;

    if (sVirtualKey != BTKEY_NULL) {
        key = sVirtualKey;
        sVirtualKey = BTKEY_NULL;
    }

    if (key == BTKEY_NULL) {
        return;
    }

    usAutoInitial10MSTimer = TIMER_Get10MSTimer();

    ucLCDBacklightOnFlag = 1;
    BACK_ONOFF(ON);
    usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();

    if (ucReversalFlag) {
        usAutoReversal10MSTimer = TIMER_Get10MSTimer();
    }

    if (usPrintStep) {
        return;
    }

    // IC5100
    if (iModelName == IC5100P) {
        switch (key) {
            case BTKEY_FCN_IC5100P:
                if (*pusServiceAddr == 0x0000) {
                    MSRDisable();

                    //              "Enter Password  ", "                ", "                ", "                "
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_FUNC, M4EnterPassword_0001, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 2;
                    cMaxInputCnt = 12;
                    LCD_CursorOn(cYPos, cXPos);
                } else {
                    InputKeyService(key);
                }
                break;

            case BTKEY_SFUNC_IC5100P:
                if (*pusServiceAddr == 0x0000) {
                    MSRDisable();

                    // "Enter Password  ", "                ", "                ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SPECIAL, M4EnterPassword_0001, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 2;
                    cMaxInputCnt = 12;
                    LCD_CursorOn(cYPos, cXPos);
                }
#ifdef USER_DEBUG
                    // Maintenance Menu - Select Maintenance menu item
                else if (*pusServiceAddr == 0x0011) {
                    pusServiceAddr++;
                    DisplayLCDMsgOrPrinterMsgInDebugMode();
                    sVirtualKey = BTKEY_CANCEL;
                }
#endif
                else {
                    InputKeyService(key);
                }
                break;

            case BTKEY_CANCEL:
                CancelKeyService();
                break;

            case BTKEY_ENTER:
                /*
                                                if (*pusServiceAddr == 0x0000) {
                                                        i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 1);
                                                        if (i) {
                                                                DisplayConnectionErrorConditionAndGotoInitialStatus(i);
                                                                return;
                                                        }
                                                        if(InitTrxnReqData() < 0) {
                                                                ErrorDisplayAndGoErrorStatus(M4ErrNoBatchNo_00001, -1, ucLangFlag);
                                                                return;
                                                        }
                                                        giTransactionType = TRXN_BANK_EFTTRAN;

                                                        i = GetTrxnMenuActiveStatus();
                                                        if (i == 0) {
                                                                return;
                                                        }
                                                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                                                }
                                                else {
                                                        EnterKeyService();
                                                }
                 */
                EnterKeyService();
                break;

#if 0
            case BTKEY_ASTERISK:
                /*				tPOSUtilBuf.usSeqNo = tPOSUtilBuf.usSeqNo + 10;
                                                SavePOSUtilBuf();
                                                Rprintf("tPOSUtilBuf.usBatchNo = %d, tPOSUtilBuf.usSeqNo = %d\r\n", tPOSUtilBuf.usBatchNo, tPOSUtilBuf.usSeqNo);
                 */
                //				GotoReversalMode();
                //TestParsing();

                strncpy(stMasterKey.ucMasterKey, "d944f8a45468da2f0f77a41ac04aea36", 32);
                stMasterKey.ucMKFlag = 0x5A;
                stMasterKey.usMagicNo = MAGICNO_MASTERKEY;
                FLASH_WRITE((char *) FLASH8MB_NIBSS_MASTERKEY, sizeof (MASTERKEY), (char *) &stMasterKey);

                /*
				
                MainStatusSetting(MSS_CALLHOME, MST_TAMS_CALLHOME, M4StartCallHome_0001, -1, ucLangFlag);
                sVirtualKey = BTKEY_ENTER;
                 */

                break;

#endif
            default:
                InputKeyService(key);
                break;
        }
    }
}

void InputKeyService(int key) {
    int i, x, y;
    char temp[17];

    switch (*pusServiceAddr) {
        case 0x0100: // Special Functions - Input Maintenance's Password
        case 0x1400: // Change Maintenance's Password - Input New Maintenance's Password
        case 0x1401: // Change Maintenance's Password - Retype New Maintenance's Password
        case 0x1533: // Modem Test - Enter your PIN
        case 0x5107: // Buy - Enter your PIN (Multi-Merchant)
        case 0x2000: // F1 Functions - Select Main menu item
        case 0x2600: // Change Merchant's Password - Input New Merchant's Password
        case 0x2601: // Change Merchant's Password - Retype New Merchant's Password
        case 0x5109: // Buy - Enter your PIN
        case 0x5201: // Balance Inquiry - Enter your PIN
        case 0x5401: // SIM Charge(Preliminary Transaction) - Enter your PIN
        case 0x9300: // Change parameters of telephone in Reversal Mode - Input Merchant's or Cashier's Password
            KEY_InputPassWord(cYPos, cXPos, cMaxInputCnt, key, c65TempKeyBuf);
            break;

        case 0x0011: // Maintenance Menu - Select Maintenance menu item
        case 0x1100: // Select Setup Terminal Menu - Select Setup Terminal menu item
        case 0x1160: // Select GSM Setup Menu - Select GSM setup menu item
        case 0x1161: // GSM Set Parameters - Select SIM
        case 0x1180: // Set Parameters Menu - Select Set Parameters menu item
        case 0x1186: // Set Parameters - Select Setup External Printer menu item
        case 0x1187: // Set Parameters - Select External Printer Model menu item
        case 0x118A: // Set Parameters - Select Setup External Printer Paper menu item
        case 0x1192: // Set Parameters - Select Set Offline menu item
        case 0x1195: // Set Parameters - Select Multi-Merchant menu item
        case 0x1197: // Set Parameters - Select Set Amounts n menu item
        case 0x1198: // Set Parameters - Select Set Amounts menu item
        case 0x11D3: // POS Serial Number - Confirm POS Serial Number
        case 0x11E0: // Download Parameters - Select Parameters to download
        case 0x11E6: // Download Parameters - Select Function List to download
        case 0x11E7: // Download Parameters - Select Key Download to download
        case 0x11E8: // Download Parameters - Select EFT Parameters to download
        case 0x11E9: // Download Parameters - Select EMV Parameters to download
        case 0x1200: // POS Information menu - Select POS Information menu item
        case 0x1300: // Initialize - Select Initialize menu item
        case 0x1301: // Reset Param. - Reset Parameters
        case 0x1302: // Reset Merchant's Password - Reset Merchant
        case 0x1303: // Erase Transaction Logs
        case 0x1500: // Hardware Test - Select Hardware Test menu item
        case 0x2001: // Select Merchant Item in Main Menu - Input Merchant's Password
        case 0x2002: // Merchant Menu - Select Merchant menu item
        case 0x2110: // Supervisor Menu - Select End-of-Day menu item
        case 0x2115: // Current Merchant Total - Select Reprint or Exit
        case 0x2125: // Previous Merchant Total - Select Reprint or Exit
        case 0x2135: // Clear Merchant Total - Select Reprint or Exit
        case 0x290A: // Remote Download - Select TMS menu for Ethernet
        case 0x290F: // Remote Download - Select Remote Download for Ethernet
        case 0x4000: // Setup POS Status Menu - Select Setup POS Status menu item
        case 0x4600: // Set Beep Sound - Select Beep Sound ON/OFF
        case 0x5001: // Swipe Card or Insert Smart Card - Select Customer Trans. menu item
        case 0x5101: // Buy - Select Account (Multi-Merchant)
            //		case 0x5103:	// Buy - Select Amount (Multi-Merchant)
        case 0x5119: // Not Approved Buy - Select Reprint or Exit
        case 0x5207: // Balance Inquiry - Select Print or Exit
        case 0x520B: // Balance Inquiry - Select Reprint or Exit
        case 0x5A11: // SIM Charge(Preliminary Transaction) - Select Company
        case 0x5A12: // SIM Charge(Preliminary Transaction) - Select SIM Charge Amount
        case 0x540B: // SIM Charge(Preliminary Transaction) - Select Reprint or Exit
        case 0x9100: // Reversal Mode - Select Reversal Mode menu item
        case 0x9301: // Set Telephone Menu - Select Set Telephone menu item
        case 0x9302: // Dial-up Modem PABX Access Code - Select PABX Access
        case 0x9305: // Dial-up Modem City Access Code - Select City Access
        case 0x9308: // Dial-up Modem Set Parameters - Select Pulse Dial
            MenuScrollUpDown(sStartDisplayMenuLine, &sSelectedMenuItemNo, &sSelectedMenuItemLine, sTotalMenuItemNo, psz17FirstMenuItemMsgAddr, key, ucLangFlag);
            if (key >= BTKEY_1 && key <= sTotalMenuItemNo) {
                sVirtualKey = BTKEY_ENTER;
            }
            break;

        case 0x1168: // Setup GSM/GPRS Server - Input Server Port Number 1
        case 0x116A: // Setup GSM/GPRS Server - Input Server Port Number 2
        case 0x116C: // Setup GSM/GPRS TMS Server - Input TMS Server Port Number 1
        case 0x116E: // Setup GSM/GPRS TMS Server - Input TMS Server Port Number 2
        case 0x1165: // GSM City Access Code - Input GSM City Access Code
            //		case 0x1181:	// Set Parameters - Input Terminal ID
        case 0x1182: // Set Parameters - Input Merchant ID
        case 0x1188: // Set Parameters - Input Maximum External Printer Copy Count
        case 0x118B: // Set Parameters - Input Left Number of Paper
        case 0x118C: // Set Parameters - Input Right Number of Paper
        case 0x118D: // Set Parameters - Input Line Number of Paper
        case 0x1191: // Set Parameters - Input NII
        case 0x2100: // Supervisor Menu - Select Reversal menu item
        case 0x2140: // Supervisor Menu - EOD - Past Day
        case 0x290C: // Remote Download - Input TMS Server Port Number 1 for Ethernet
        case 0x290E: // Remote Download - Input TMS Server Port Number 2 for Ethernet
        case 0x4100: // Set CallHome Interval
        case 0x4200: // Set Comm Timeout
        case 0x5103: // Enter last 4 Digits of Card No.
        case 0x5112: // Buy - Input customer ID
        case 0x5A01:
        case 0x5A02:
        case 0x9303: // Dial-up Modem PABX Access Code - Input PABX Access Code
        case 0x9306: // Dial-up Modem City Access Code - Input City Access Code
        case 0x930A: // Setup Ethernet Server - Input Server Port Number 1
        case 0x930B: // Setup GSM Server - Input GSM City Access Code
            KEY_InputNoString(cYPos, cXPos, cMaxInputCnt, key, c65TempKeyBuf, ucLangFlag);
            break;

        case 0x1166: // GSM Telephone No - Input GSM Telephone No
        case 0x116F: // GSM TMS phone No - Input GSM TMS phone No
        case 0x11B0: // Setup Help Desk Telephone No - Input Help Desk Telephone No
        case 0x9307: // Set Telephone No - Input Telephone No
        case 0x930C: // Setup GSM Server - Input GSM Telephone No
            if (sTempKey < 3) {
                i = sTempKey;
            } else {
                i = 3;
            }
            KEY_InputNoString(i, cXPos, cMaxInputCnt, key, c65TempKeyBuf, ucLangFlag);
            break;

        case 0x1193: // Set Parameters - Input Maximum offline transaction number
        case 0x1194: // Set Parameters - Input Maximum offline transaction amount
        case 0x1199: // Set Parameters - Input Amount 1
        case 0x119A: // Set Parameters - Input Amount 2
        case 0x119B: // Set Parameters - Input Amount 3
        case 0x119C: // Set Parameters - Input Maximum Amount
        case 0x5105: // Buy - Input Amount (Multi-Merchant)
        case 0x510C: // Buy - Input amount
            KEY_InputAmount(cYPos, cXPos, cMaxInputCnt, key, c65TempKeyBuf, c65CommaAndDotString, ucCurrencyExp, ucLangFlag);
            break;

        case 0x1167: // Setup GSM/GPRS Server - Input Server IP Address 1
        case 0x1169: // Setup GSM/GPRS Server - Input Server IP Address 2
        case 0x116B: // Setup GSM/GPRS TMS Server - Input TMS Server IP Address 1
        case 0x116D: // Setup GSM/GPRS TMS Server - Input TMS Server IP Address 2
        case 0x290B: // Remote Download - Input TMS Server IP Address 1 for Ethernet
        case 0x290D: // Remote Download - Input TMS Server IP Address 2 for Ethernet
        case 0x9309: // Setup Ethernet Server - Input Server IP Address 1
            KEY_InputIPAddress(cYPos, key, c65TempKeyBuf, ucLangFlag);
            break;

        case 0x4300: // Set Date - Input Date
            KEY_InputChristianDate(cYPos, cXPos, key, c65TempKeyBuf, ucLangFlag);
            break;

        case 0x4400: // Set Time - Input Time
            KEY_InputTime(cYPos, cXPos, key, c65TempKeyBuf, ucLangFlag);
            break;

        case 0x1162: // GSM Set Parameters - Input APN
        case 0x1163: // GSM Set Parameters - Input Username
        case 0x1164: // GSM Set Parameters - Input Password
        case 0x1181: // Set Parameters - Input Terminal ID
        case 0x1183: // Set Parameters - Input Store Name
        case 0x11D1: // POS Serial Number - Input POS Serial Number
            InputAlpNoString(cYPos, cXPos, cMaxInputCnt, key, c65TempKeyBuf);
            break;

        case 0x4500: // Set Contrast - Set LCD Contrast
            if (key >= BTKEY_1 && key <= BTKEY_2) {
                if (key == BTKEY_1) { // light
                    if (sTempKey > MIN_LCD_CONTRAST) {
                        sTempKey--;
                        sprintf(temp, "[%2d]", sTempKey);
                        LCD_DisplayLine(2, CENTER_JUSTIFIED, temp, ucLangFlag);
                        LCD_CONT(sTempKey);
                    }
                } else {
                    if (sTempKey < MAX_LCD_CONTRAST) {
                        sTempKey++;
                        sprintf(temp, "[%2d]", sTempKey);
                        LCD_DisplayLine(2, CENTER_JUSTIFIED, temp, ucLangFlag);
                        LCD_CONT(sTempKey);
                    }
                }
            }
            break;
    }
}

void EnterKeyService(void) {
    int i, j, k, m, n;
    long ltemp;
    double dtemp, dtemp1;
    unsigned short stemp;
    char temp[256];
    _tDATE_TIME dt;

    switch (*pusServiceAddr) {
        case 0x0100: // Special Functions - Input Maintenance's Password
            if (strlen(c65TempKeyBuf) < 4) {
                Beep_EventSound(ERROR_TONE);
                return;
            }

            if (!strcmp(c65TempKeyBuf, st_POSSetupInfo.sz13MasterPIN)) {
                // "  Maintenance   ", "1.Setup Terminal", "2.POS Info.     ", "3.Initialize    "
                MainStatusSetting(MSS_SPECIAL_FUNC, MST_SPECIAL, M4MaintenanceMenu_01, LCD_LINE1, ucLangFlag);
                SetMenuScrollUpDownInfo(1, 1, 1, 5, (char *) LCD_MSG_TBL1[ucLangFlag][M1MaintenanceMenu_02]);
                pusServiceAddr++;
            } else {
                Beep_EventSound(ERROR_TONE);
                // "????????????????", "????????????????", "????????????????", "Wrong Password  "
                LCDDisplay4Lines(M4WrongPassword_0001, -1, ucLangFlag);
                TIMER_Wait1MS(2000);

                LCD_ClearLine(2);
                LCD_ClearLine(3);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                ucKeyCnt = 0;
                cYPos = 2;
                cXPos = 2;
                cMaxInputCnt = 12;
                LCD_CursorOn(cYPos, cXPos);
            }
            break;

        case 0x0011: // Maintenance Menu - Select Maintenance menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Select Setup Terminal Menu
                    // " Setup Terminal ", "1.Setup Modem   ", "2.Set Parameters", "3.Download Param"
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_TERMINAL, M4SetupTrmMenu_00001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 5, (char *) LCD_MSG_TBL1[ucLangFlag][M1SetupTrmMenu_00002]);
                    break;
                case BTKEY_2: // Select POS Information menu item
                    // "POS Information ", "1.View Info.    ", "2.Print Info.   ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_POS_INFO, M4POSInfoMenu_000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1POSInfoMenu_000002]);
                    break;
                case BTKEY_3: // Initialize
                    // "Initialize      ", "1.Reset Param.  ", "2.Reset Merchant", "3.Erase POS Logs"
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_INITIALIZE, M4InitializeMenu_001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1InitializeMenu_002]);
                    break;
                case BTKEY_4: // Change Master's Password
                    // "New Password    ", "                ", "                ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_CHANGE_MASTER_PIN, M4NewPassword_000001, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 2;
                    cMaxInputCnt = 12;
                    LCD_CursorOn(cYPos, cXPos);
                    break;
                case BTKEY_5: // Hardware Test
                    // "Hardware Test   ", "1.Printer Test  ", "2.MSR Test      ", "3.Modem Test    "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_HW_TEST, M4HWTestMenu_0000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 8, (char *) LCD_MSG_TBL1[ucLangFlag][M1HWTestMenu_0000002]);
                    break;
            }
            break;

        case 0x1100: // Select Setup Terminal Menu - Select Setup Terminal menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Select Modem Menu
                    // "    GSM/GPRS    ", "1.Set Parameters", "2.Set Server    ", "3.Set TMS Server"
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_GSM, M4GSMMenu_0000000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1GSMMenu_0000000002]);
                    break;
                case BTKEY_2: // Set Parameters
                    // "Set Parameters  ", "1.Terminal ID   ", "2.Store Name    ", "3.Sequence No   "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_SET_PARAM, M4SetParameterMenu_1, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1SetParamMenu_00002]);
                    break;
                case BTKEY_3: // Download Parameters
                    i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 0);
                    if (i) {
                        DisplayConnectionErrorConditionAndGotoInitialStatus(i);
                        return;
                    }
                    // "Download Params ", "1.App Lists     ", "2.Function Lists", "3.Key Download  "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_DOWNLOAD_PARAMETERS, M4DownloadParam_0001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 6, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadParam_0002]);
                    break;
                case BTKEY_4: // POS Serial Number
                    memset(temp, 0x00, sizeof (temp));
                    i = GET_PROD_ID(temp);
                    if (i == 0) {
                        // "Serial Number   ", "                ", "                ", "                "
                        MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_POS_SERIAL_NO, M4SerialNumber_00001, -1, ucLangFlag);
                        LCD_DisplayLine(1, CENTER_JUSTIFIED, temp, ucLangFlag);
                        TIMER_WaitKeyPress1MS(5000);
                        sVirtualKey = BTKEY_CANCEL;
                    } else {
                        // "Input S/N       ", "                ", "                ", "                "
                        MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_POS_SERIAL_NO, M4InputSN_0000000001, -1, ucLangFlag);
                        memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                        InitializeAlpNoInputParameter(1);
                        // "           [ALP]",
                        LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1AlphabetMode_00001], ucLangFlag);
                        ucKeyCnt = 0;
                        cYPos = 1;
                        cXPos = 0;
                        cMaxInputCnt = 16;
                        LCD_CursorOn(cYPos, cXPos);

                        RS232Open();
                        pusServiceAddr++;
                    }
                    break;
                case BTKEY_5: // POS Serial Number
                    LCDDisplay4Lines(M4PinpadKeyLoad_0001, -1, ucLangFlag);
                    if (CryptoKeyLoad() == 0)
                        ENTER_AFTER_KEYLOAD();
                    sVirtualKey = BTKEY_CANCEL;
                    break;

            }
            break;

        case 0x1160: // Select GSM Setup Menu - Select GSM setup menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Set Parameters
                    // "Select SIM      ", "1.SIM1          ", "2.SIM2          ", "                "
                    LCDDisplay4Lines(M4GSMSelSIM_00000001, 1 + st_POSSetupInfo.ucGprsSIMNo, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1 + st_POSSetupInfo.ucGprsSIMNo, 1 + st_POSSetupInfo.ucGprsSIMNo, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1GSMSelSIM_00000002]);
                    pusServiceAddr++;
                    break;
                case BTKEY_2: // Set GSM/GPRS Server
                    // "SERVER IP 1     ", "                ", "                ", "*='.'           "
                    LCDDisplay4Lines(M4ServerIPAddress_01, -1, ucLangFlag);
                    ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz16TrxnServerIP[0]);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                    ucKeyCnt = 0;
                    cYPos = 1;
                    cXPos = 0;
                    if (strlen(c65TempKeyBuf) == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    pusServiceAddr += 7;
                    break;
                case BTKEY_3: // Setup GSM/GPRS TMS Server
                    // "TMS IP 1        ", "                ", "                ", "*='.'           "
                    LCDDisplay4Lines(M4TMSServerIP_000001, -1, ucLangFlag);
                    ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz16TMSServerIP[0]);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                    ucKeyCnt = 0;
                    cYPos = 1;
                    cXPos = 0;
                    if (strlen(c65TempKeyBuf) == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    pusServiceAddr += 11;
                    break;
            }
            break;

        case 0x1161: // GSM Set Parameters - Input APN
            st_POSSetupInfo.ucGprsSIMNo = sSelectedMenuItemNo - 1;

            LCDDisplay4Lines(M4GSMInputAPN_000001, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz33GprsAPN[st_POSSetupInfo.ucGprsSIMNo]);
            i = strlen(c65TempKeyBuf);
            if (i) {
                if (i <= 16) {
                    LCD_DisplayString(1, 0, i, c65TempKeyBuf, 0);
                } else {
                    LCD_DisplayString(1, 0, 16, &c65TempKeyBuf[0], 0);
                    i = i - 16;
                    LCD_DisplayString(2, 0, i, &c65TempKeyBuf[16], 0);
                }
            }
            // "           [ALP]",
            LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1AlphabetMode_00001], ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 32;
            if (i == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            InitializeAlpNoInputParameter(1);
            sTempKey = 0;
            pusServiceAddr++;
            break;

        case 0x1162: // GSM Set Parameters - Input Username
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }
            strcpy(st_POSSetupInfo.sz33GprsAPN[st_POSSetupInfo.ucGprsSIMNo], c65TempKeyBuf);

            LCDDisplay4Lines(M4GSMInputID_0000001, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz33GprsUserName[st_POSSetupInfo.ucGprsSIMNo]);
            i = strlen(c65TempKeyBuf);
            if (i) {
                if (i <= 16) {
                    LCD_DisplayString(1, 0, i, c65TempKeyBuf, 0);
                } else {
                    LCD_DisplayString(1, 0, 16, &c65TempKeyBuf[0], 0);
                    i = i - 16;
                    LCD_DisplayString(2, 0, i, &c65TempKeyBuf[16], 0);
                }
            }
            // "           [ALP]",
            LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1AlphabetMode_00001], ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 32;
            if (i == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            InitializeAlpNoInputParameter(1);
            sTempKey = 0;
            pusServiceAddr++;
            break;

        case 0x1163: // GSM Set Parameters - Input Password
            strcpy(st_POSSetupInfo.sz33GprsUserName[st_POSSetupInfo.ucGprsSIMNo], c65TempKeyBuf);

            LCDDisplay4Lines(M4GSMInputPWD_000001, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz33GprsPassword[st_POSSetupInfo.ucGprsSIMNo]);
            i = strlen(c65TempKeyBuf);
            if (i) {
                if (i <= 16) {
                    LCD_DisplayString(1, 0, i, c65TempKeyBuf, 0);
                } else {
                    LCD_DisplayString(1, 0, 16, &c65TempKeyBuf[0], 0);
                    i = i - 16;
                    LCD_DisplayString(2, 0, i, &c65TempKeyBuf[16], 0);
                }
            }
            // "           [ALP]",
            LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1AlphabetMode_00001], ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 32;
            if (i == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            InitializeAlpNoInputParameter(1);
            sTempKey = 0;
            pusServiceAddr++;
            break;

        case 0x1164: // GSM Set Parameters - Save Password
            strcpy(st_POSSetupInfo.sz33GprsPassword[st_POSSetupInfo.ucGprsSIMNo], c65TempKeyBuf);
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x1167: // Setup GSM/GPRS Server - Input Server IP Address 1
            if (KEY_CheckIPAddress(c65TempKeyBuf)) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memcpy(st_POSSetupInfo.sz16TrxnServerIP[0], c65TempKeyBuf, sizeof (st_POSSetupInfo.sz16TrxnServerIP[0]));

            // "SERVER PORT NO 1", "                ", "                ", "                "
            LCDDisplay4Lines(M4ServerPortNo_00001, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz6TrxnServerPortNo[0]);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 5;
            if (strlen(c65TempKeyBuf) == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            pusServiceAddr++;
            break;

        case 0x1168: // Setup GSM/GPRS Server - Input Server Port Number 1
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            ltemp = atol(c65TempKeyBuf);
            if (ltemp > 65535L) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            sprintf(st_POSSetupInfo.sz6TrxnServerPortNo[0], "%ld", ltemp);

            // "SERVER IP 2     ", "                ", "                ", "*='.'           "
            LCDDisplay4Lines(M4ServerIPAddress_02, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz16TrxnServerIP[1]);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            if (strlen(c65TempKeyBuf) == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            pusServiceAddr++;
            break;

        case 0x1169: // Setup GSM/GPRS Server - Input Server IP Address 2
            if (KEY_CheckIPAddress(c65TempKeyBuf)) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memcpy(st_POSSetupInfo.sz16TrxnServerIP[1], c65TempKeyBuf, sizeof (st_POSSetupInfo.sz16TrxnServerIP[1]));

            // "SERVER PORT NO 2", "                ", "                ", "                "
            LCDDisplay4Lines(M4ServerPortNo_00002, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz6TrxnServerPortNo[1]);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 5;
            if (strlen(c65TempKeyBuf) == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            pusServiceAddr++;
            break;

        case 0x116A: // Setup GSM/GPRS Server - Input Server Port Number 2
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            ltemp = atol(c65TempKeyBuf);
            if (ltemp > 65535L) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            sprintf(st_POSSetupInfo.sz6TrxnServerPortNo[1], "%ld", ltemp);
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x116B: // Setup GSM/GPRS TMS Server - Input TMS Server IP Address 1
        case 0x290B: // Remote Download - Input TMS Server IP Address 1 for Ethernet
            if (KEY_CheckIPAddress(c65TempKeyBuf)) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memcpy(st_POSSetupInfo.sz16TMSServerIP[0], c65TempKeyBuf, sizeof (st_POSSetupInfo.sz16TMSServerIP[0]));

            // "TMS PORT NO 1  ", "                ", "                ", "                "
            LCDDisplay4Lines(M4TMSServerPortNo_01, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz6TMSServerPortNo[0]);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 5;
            if (strlen(c65TempKeyBuf) == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            pusServiceAddr++;
            break;

        case 0x116C: // Setup GSM/GPRS TMS Server - Input TMS Server Port Number 1
        case 0x290C: // Remote Download - Input TMS Server Port Number 1 for Ethernet
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            ltemp = atol(c65TempKeyBuf);
            if (ltemp > 65535L) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            sprintf(st_POSSetupInfo.sz6TMSServerPortNo[0], "%ld", ltemp);

            // "TMS IP 2       ", "                ", "                ", "*='.'           "
            LCDDisplay4Lines(M4TMSServerIP_000002, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz16TMSServerIP[1]);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            if (strlen(c65TempKeyBuf) == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            pusServiceAddr++;
            break;

        case 0x116D: // Setup GSM/GPRS TMS Server - Input TMS Server IP Address 2
        case 0x290D: // Remote Download - Input TMS Server IP Address 2 for Ethernet
            if (KEY_CheckIPAddress(c65TempKeyBuf)) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memcpy(st_POSSetupInfo.sz16TMSServerIP[1], c65TempKeyBuf, sizeof (st_POSSetupInfo.sz16TMSServerIP[1]));

            // "TMS PORT NO 2   ", "                ", "                ", "                "
            LCDDisplay4Lines(M4TMSServerPortNo_02, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz6TMSServerPortNo[1]);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 5;
            if (strlen(c65TempKeyBuf) == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            pusServiceAddr++;
            break;

        case 0x116E: // Setup GSM/GPRS TMS Server - Input TMS Server Port Number 2
        case 0x290E: // Remote Download - Input TMS Server Port Number 2 for Ethernet
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            ltemp = atol(c65TempKeyBuf);
            if (ltemp > 65535L) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            sprintf(st_POSSetupInfo.sz6TMSServerPortNo[1], "%ld", ltemp);
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x9308: // Set Telephone Pulse Dial - Select Pulse Dial
            st_POSSetupInfo.ucPulseDial = sSelectedMenuItemNo - 1;
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x9302: // Dial-up Modem PABX Access Code - Select PABX Access
            switch (*pusServiceAddr) {
                case 0x9302: // Dial-up Modem PABX Access Code - Select PABX Access
                    st_POSSetupInfo.ucPABXUse = sSelectedMenuItemNo - 1;
                    break;
            }

            if (sSelectedMenuItemNo == 2) {
                // "PABX ACCESS CODE", "                ", "                ", "                "
                LCDDisplay4Lines(M4PABXAccessCode_001, -1, ucLangFlag);
                switch (*pusServiceAddr) {
                    case 0x9302: // Dial-up Modem PABX Access Code - Select PABX Access
                        ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz6PABXCode);
                        break;
                }
                LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                ucKeyCnt = 0;
                cYPos = 1;
                cXPos = 0;
                cMaxInputCnt = 5;
                if (strlen(c65TempKeyBuf) == 0) {
                    LCD_CursorOn(cYPos, cXPos);
                }
                pusServiceAddr++;
            } else {
                pusServiceAddr += 2;
                sVirtualKey = BTKEY_ENTER;
            }
            break;

        case 0x9303: // Dial-up Modem PABX Access Code - Input PABX Access Code
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            LCD_CursorOff();
            switch (*pusServiceAddr) {
                case 0x9303: // Dial-up Modem PABX Access Code - Input PABX Access Code
                    memcpy(st_POSSetupInfo.sz6PABXCode, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz6PABXCode));
                    break;
            }
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x9304: // Dial-up Modem City Access Code - Display Select City Access
            switch (*pusServiceAddr) {
                case 0x9304: // Dial-up Modem City Access Code - Display Select City Access
                    sSelectedMenuItemNo = st_POSSetupInfo.ucCityUse + 1;
                    break;
            }
            // "CITY ACCESS     ", "1.NO            ", "2.YES           ", "                "
            LCDDisplay4Lines(M4CityAccess_0000001, sSelectedMenuItemNo, ucLangFlag);
            SetMenuScrollUpDownInfo(1, sSelectedMenuItemNo, sSelectedMenuItemNo, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
            pusServiceAddr++;
            break;

        case 0x9305: // Dial-up Modem City Access Code - Select City Access
            switch (*pusServiceAddr) {
                case 0x9305: // Dial-up Modem City Access Code - Select City Access
                    st_POSSetupInfo.ucCityUse = sSelectedMenuItemNo - 1;
                    break;
            }

            if (sSelectedMenuItemNo == 2) {
                // "CITY ACCESS CODE", "                ", "                ", "                "
                LCDDisplay4Lines(M4CityAccessCode_001, -1, ucLangFlag);
                switch (*pusServiceAddr) {
                    case 0x9305: // Dial-up Modem City Access Code - Select City Access
                        if (*pusServiceAddr == 0x9305) {
                            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz10CityCode);
                        } else {
                            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz10GsmCityCode);
                        }
                        break;
                }
                LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                ucKeyCnt = 0;
                cYPos = 1;
                cXPos = 0;
                cMaxInputCnt = 9;
                if (strlen(c65TempKeyBuf) == 0) {
                    LCD_CursorOn(cYPos, cXPos);
                }
                pusServiceAddr++;
            } else {
                sVirtualKey = BTKEY_CANCEL;
            }
            break;

        case 0x9306: // Dial-up Modem City Access Code - Input City Access Code
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            switch (*pusServiceAddr) {
                case 0x9306: // Dial-up Modem City Access Code - Input City Access Code
                    if (*pusServiceAddr == 0x9306) {
                        memcpy(st_POSSetupInfo.sz10CityCode, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz10CityCode));
                    } else {
                        memcpy(st_POSSetupInfo.sz10GsmCityCode, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz10GsmCityCode));
                    }
                    break;
            }
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x9307: // Set Telephone No - Input Telephone No
        case 0x930C: // Setup GSM Server - Input GSM Telephone No
            //if (strlen(c65TempKeyBuf) == 0 && sTempKey == 1) {
            //	Beep_EventSound(ERROR_TONE);
            //	break;
            //}

            LCD_CursorOff();
            memcpy(st_POSSetupInfo.sz17TrxnTelNo[sTempKey - 1], c65TempKeyBuf, sizeof (st_POSSetupInfo.sz17TrxnTelNo[sTempKey - 1]));
            sTempKey++;
            if (strlen(c65TempKeyBuf) == 0 || sTempKey > 8) {
                sVirtualKey = BTKEY_CANCEL;
            } else {
                DisplayTrxnTelNo();
            }
            break;




        case 0x1180: // Set Parameters Menu - Select Set Parameters menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Set Terminal ID
                    // "Terminal ID     ", "                ", "                ", "                "
                    LCDDisplay4Lines(M4TerminalID_0000001, -1, ucLangFlag);
                    ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz9TerminalID);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1NumberMode_0000001], ucLangFlag);
                    ucKeyCnt = 0;
                    cYPos = 1;
                    cXPos = 0;
                    cMaxInputCnt = 8;
                    if (strlen(c65TempKeyBuf) == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    sTempKey = 0;
                    pusServiceAddr++;
                    break;

                case BTKEY_2: // Set Store Name
                    // "Store Name      ", "                ", "                ", "                "
                    LCDDisplay4Lines(M4StoreName_00000001, -1, ucLangFlag);
                    ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz33StoreName);
                    i = strlen(c65TempKeyBuf);
                    if (i) {
                        if (i <= 16) {
                            LCD_DisplayString(1, 0, i, c65TempKeyBuf, 0);
                        } else {
                            LCD_DisplayString(1, 0, 16, &c65TempKeyBuf[0], 0);
                            i = i - 16;
                            LCD_DisplayString(2, 0, i, &c65TempKeyBuf[16], 0);
                        }
                    }
                    // "           [ALP]",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1AlphabetMode_00001], ucLangFlag);

                    ucKeyCnt = 0;
                    cYPos = 1;
                    cXPos = 0;
                    cMaxInputCnt = 32;
                    if (i == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    InitializeAlpNoInputParameter(1);
                    sTempKey = 0;
                    pusServiceAddr += 3;
                    break;

                case BTKEY_3: // Set Sequence No
                    // "                ", "                ", "                ", "                "
                    LCDDisplay4Lines(M4_____________Space, -1, ucLangFlag);
                    LCD_DisplayLine(0, LEFT_JUSTIFIED, "New Sequence No?", ucLangFlag);
                    sprintf(temp, "%d", tPOSUtilBuf.usSeqNo);
                    ClearTempKeyBufAndStringCopy(temp);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                    ucKeyCnt = 0;
                    cYPos = 1;
                    cXPos = 0;
                    cMaxInputCnt = 4;
                    if (strlen(c65TempKeyBuf) == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    sTempKey = 0;
                    pusServiceAddr += 2;
                    break;

            }
            break;

        case 0x11E0:
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // 1. APPLIST
                    // "    App List    ", "                ", "Press ENTER Key ", "to download!    "
                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1AppLists_000000001]);
                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                    giTransactionType = TRXN_DOWNLOAD_APPLIST;
                    pusServiceAddr++;
                    break;
                case BTKEY_2: // 2. FUNCLIST - SUBMENU: Tams, VoucherVault, Banking - ���߿� APPLIST���� FUNCLIST�̸��� �����ͼ� �����ϵ��� ����
                    // " Function List  ", "1.Tams          ", "2.VoucherVault  ", "3.Banking       "
                    LCDDisplay4Lines(M4DownFuncList_00001, LCD_LINE1, ucLangFlag);
                    pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][6];
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownFuncList_00002]);
                    break;
                case BTKEY_3: // 3. KEY - SUBMENU: NEWKEY, GETKEY
                    // "  Key Download  ", "1.Master Key    ", "2.Session Key   ", "                "
                    LCDDisplay4Lines(M4DownTrxnKeys_00001, LCD_LINE1, ucLangFlag);
                    pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][7];
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownTrxnKeys_00002]);
                    break;
                case BTKEY_4: // 4. PARAMS - SUBMENU: PARAM, EFTPARAMS, BINTABLE
                    // " EFT Parameters ", "1.Params        ", "2.EFT Params    ", "3.BIN Tables    "
                    LCDDisplay4Lines(M4DownEftParams_0001, LCD_LINE1, ucLangFlag);
                    pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][8];
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownEftParams_0002]);
                    break;
                case BTKEY_5: // 5. EMV - SUBMENU: EMVAPP, EMVCAPK, EMVREVOKECAPK
                    // " EMV Parameters ", "1.EMV APPs      ", "2.EMV CAPKs     ", "3.Revoke CAPKs  "
                    LCDDisplay4Lines(M4DownEmvParams_0001, LCD_LINE1, ucLangFlag);
                    pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][9];
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownEmvParams_0002]);
                    break;
                case BTKEY_6: // 6. HOTCARDS
                    // ���� ���� ������ ����ؼ� start
                    // "   Hot Cards    ", "                ", "Press ENTER Key ", "to download!    "
                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1HotCards_000000001]);
                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                    giTransactionType = TRXN_DOWNLOAD_HOTCARDS;
                    pusServiceAddr++;
                    break;

            }

            /*
                                    switch (sSelectedMenuItemNo) {
                                            case BTKEY_1:	// All Parameters
                                                    // " All Parameters ", "                ", "Press ENTER Key ", "to download!    "
                                                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                                                    strcpy(sz17TrxnTitle, (char *)LCD_MSG_TBL1[ucLangFlag][M1AllParameters_0001]);
                                                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                                                    giTransactionType = TRXN_DOWNLOAD_ALL_PARAMETER;
                                                    pusServiceAddr++;
                                                    break;
                                            case BTKEY_2:	// App/Func Lists
                                                    // " App/Func Lists ", "                ", "Press ENTER Key ", "to download!    "
                                                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                                                    strcpy(sz17TrxnTitle, (char *)LCD_MSG_TBL1[ucLangFlag][M1AppFuncLists_00001]);
                                                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                                                    giTransactionType = TRXN_DOWNLOAD_APPFUNCLIST;
                                                    pusServiceAddr++;
                                                    break;
                                            case BTKEY_3:	// New Keys
                                                    // "    New Keys    ", "                ", "Press ENTER Key ", "to download!    "
                                                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                                                    strcpy(sz17TrxnTitle, (char *)LCD_MSG_TBL1[ucLangFlag][M1NewKeys_0000000001]);
                                                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                                                    giTransactionType = TRXN_DOWNLOAD_KEY;
                                                    pusServiceAddr++;
                                                    break;
                                            case BTKEY_4:	// Param/BinTable
                                                    // " Param/BinTable ", "                ", "Press ENTER Key ", "to download!    "
                                                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                                                    strcpy(sz17TrxnTitle, (char *)LCD_MSG_TBL1[ucLangFlag][M1ParamBinTable_0001]);
                                                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                                                    giTransactionType = TRXN_DOWNLOAD_PARAMETER;
                                                    pusServiceAddr++;
                                                    break;
                                            case BTKEY_5:	// EMV Parameters
                                                    // " EMV Parameters ", "                ", "Press ENTER Key ", "to download!    "
                                                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                                                    strcpy(sz17TrxnTitle, (char *)LCD_MSG_TBL1[ucLangFlag][M1EMVParameters_0001]);
                                                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                                                    giTransactionType = TRXN_DOWNLOAD_EMV_PARAMETER;
                                                    pusServiceAddr++;
                                                    break;
                                            case BTKEY_6:	// Hot Cards
                                                    // ���� ���� ������ ����ؼ� start
                                                    // "   Hot Cards    ", "                ", "Press ENTER Key ", "to download!    "
                                                    LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
                                                    strcpy(sz17TrxnTitle, (char *)LCD_MSG_TBL1[ucLangFlag][M1HotCards_000000001]);
                                                    LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
                                                    giTransactionType = TRXN_DOWNLOAD_HOTCARD;
                                                    pusServiceAddr++;
                                                    break;
                                    }
             */
            break;
        case 0x11E1:
            usTransType = TRXN_LOAD_PARAMETERS;
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;
        case 0x11E4:
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x11E6: // Download Parameters - Select Function List to download
            // "                ", "                ", "Press ENTER Key ", "to download!    "
            LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // "1.Tams          "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1FuncLists_00000001]);
                    giApplIdx = 0;
                    break;
                case BTKEY_2: // "2.VoucherVault  "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1FuncLists_00000001]);
                    giApplIdx = 1;
                    break;
                case BTKEY_3: // "3.Banking       "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1FuncLists_00000001]);
                    giApplIdx = 2;
                    break;
            }
            giTransactionType = TRXN_DOWNLOAD_FUNCLIST;
            LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
            pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][1];
            break;
        case 0x11E7: // Download Parameters - Select Key Download to download
            // "                ", "                ", "Press ENTER Key ", "to download!    "
            LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // "1.Master Key    "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1MasterKey_00000001]);
                    giTransactionType = TRXN_DOWNLOAD_MASTERKEY;
                    break;
                case BTKEY_2: // "2.Session Key   "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1SessionKey_0000001]);
                    giTransactionType = TRXN_DOWNLOAD_SESSIONKEY;
                    break;
            }
            LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
            pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][1];
            break;
        case 0x11E8: // Download Parameters - Select EFT Parameters to download
            // "                ", "                ", "Press ENTER Key ", "to download!    "
            LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // "1.Params        "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1Params_00000000001]);
                    giTransactionType = TRXN_DOWNLOAD_PARAM;
                    break;
                case BTKEY_2: // "2.EFT Params    "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1EftParams_00000001]);
                    giTransactionType = TRXN_DOWNLOAD_EFTPARAMS;
                    break;
                case BTKEY_3: // "3.BIN Tables    "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1BinTables_00000001]);
                    giTransactionType = TRXN_DOWNLOAD_BINTABLE;
                    break;
            }
            LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
            pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][1];
            break;
        case 0x11E9: // Download Parameters - Select EMV Parameters to download
            // "                ", "                ", "Press ENTER Key ", "to download!    "
            LCDDisplay4Lines(M4ConfirmDownload_01, -1, ucLangFlag);
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // "1.EMV APPs      "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1EmvApps_0000000001]);
                    giTransactionType = TRXN_DOWNLOAD_EMVAPP;
                    break;
                case BTKEY_2: // "2.EMV CAPKs     "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1EmvCapks_000000001]);
                    giTransactionType = TRXN_DOWNLOAD_EMVCAPK;
                    break;
                case BTKEY_3: // "3.Revoke CAPKs  "
                    strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1RevokeCapks_000001]);
                    giTransactionType = TRXN_DOWNLOAD_EMVREVOKECAPK;
                    break;
            }
            LCD_DisplayLine(0, LEFT_JUSTIFIED, sz17TrxnTitle, ucLangFlag);
            pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][1];
            break;

        case 0x11F0:
            strcpy(sz17TrxnTitle, (char *) LCD_MSG_TBL1[ucLangFlag][M1CallHome_000000001]);
            giTransactionType = TRXN_TAMS_CALLHOME;
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x1181: // Set Parameters - Input Terminal ID
            if (strlen(c65TempKeyBuf) != 8) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memcpy(st_POSSetupInfo.sz9TerminalID, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz9TerminalID));
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x1182: // Set Sequence No
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }
            tPOSUtilBuf.usSeqNo = atoi(c65TempKeyBuf);
            SavePOSUtilBuf();
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x1183: // Set Parameters - Input Store Name
            memset(temp, 0x00, sizeof (temp));
            RemoveLeadingAndTrailingSpaces(temp, c65TempKeyBuf, strlen(c65TempKeyBuf));

            memset(st_POSSetupInfo.sz33StoreName, 0x00, sizeof (st_POSSetupInfo.sz33StoreName));
            strcpy(st_POSSetupInfo.sz33StoreName, temp);
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x11B0: // Setup Help Desk Telephone No - Input Help Desk Telephone No
            LCD_CursorOff();
            memcpy(st_POSSetupInfo.sz17HelpDeskTelNo[sTempKey - 1], c65TempKeyBuf, sizeof (st_POSSetupInfo.sz17HelpDeskTelNo[sTempKey - 1]));
            sTempKey++;
            if (strlen(c65TempKeyBuf) == 0 || sTempKey > 4) {
                sVirtualKey = BTKEY_CANCEL;
            } else {
                DisplayHelpDeskTelNo();
            }
            break;

        case 0x11D1: // POS Serial Number - Input POS Serial Number by Key-in
            i = strlen(c65TempKeyBuf);
            if (i < 8) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memset(temp, 0x00, sizeof (temp));
            RemoveLeadingAndTrailingSpaces(temp, c65TempKeyBuf, i);

            i = strlen(temp);
            if (i < 8) {
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
                break;
            }

            RS232Close();
            ClearTempKeyBufAndStringCopy(temp);
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x11D2: // POS Serial Number - Input POS Serial Number by Key-in or Barcode Reader
            // "Confirm S/N     ", "                ", "1.NO            ", "2.YES           "
            LCDDisplay4Lines(M4ConfirmSN_00000001, LCD_LINE2, ucLangFlag);
            LCD_DisplayLine(1, CENTER_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            SetMenuScrollUpDownInfo(2, 1, 2, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
            pusServiceAddr++;
            break;

        case 0x11D3: // POS Serial Number - Confirm POS Serial Number
            if (sSelectedMenuItemNo == BTKEY_2) {
                TIMER_Wait1MS(500);
                memset(temp, 0x00, sizeof (temp));
                strcpy(temp, c65TempKeyBuf);
                j = 0;
                i = SAVE_PROD_ID(temp);
                if (i == 0) {
                    memset(temp, 0x00, sizeof (temp));
                    i = GET_PROD_ID(temp);
                    if (i == 0) {
                        if (!strcmp(temp, c65TempKeyBuf)) {
                            j = 1;
                        }
                    }
                }

                LCD_ClearLine(2);
                if (j) {
                    // "   Saving OK    ",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SavingOK_000000001], ucLangFlag);
                    Beep_EventSound(OK_TONE);
                } else {
                    // "  Saving Error  ",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SavingError_000001], ucLangFlag);
                    Beep_EventSound(ERROR_TONE);
                }
                TIMER_Wait1MS(5000);
            }
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x1200: // POS Information menu - Select POS Information menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // View Information
                    // "Terminal ID     ", "                ", "Merchant ID     ", "                "
                    LCDDisplay4Lines(M4ViewPOSInfo_000001, -1, ucLangFlag);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, st_POSSetupInfo.sz9TerminalID, ucLangFlag);
                    //LCD_DisplayLine(3, LEFT_JUSTIFIED, st_POSSetupInfo.sz16MerchantID, ucLangFlag);
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, pstParams->szMerchantID, ucLangFlag);
                    pusServiceAddr++;
                    break;
                case BTKEY_2: // Print Information
                    // NO PAPER?
                    if (!DetectPaper()) {
                        // "                ", "No Printer Paper", "                ", "                "
                        ErrorDisplayAndGoInitialStatus(M4NoPrinterPaper_001, -1, ucLangFlag);
                        return;
                    }

                    // "Print Info.     ", "                ", "Printing Now... ", "                "
                    LCDDisplay4Lines(M4PrintPOSInfo_00001, -1, ucLangFlag);
                    usPrintStep = 1;
                    pusServiceAddr += 8;
                    break;
            }
            break;

        case 0x1201: // View Information
            // "Store Name      ", "                ", "                ", "                "
            LCDDisplay4Lines(M4StoreName_00000001, -1, ucLangFlag);
            i = strlen(st_POSSetupInfo.sz33StoreName);
            if (i) {
                if (i <= 16) {
                    LCD_DisplayString(1, 0, i, st_POSSetupInfo.sz33StoreName, 0);
                } else {
                    LCD_DisplayString(1, 0, 16, &st_POSSetupInfo.sz33StoreName[0], 0);
                    i = i - 16;
                    LCD_DisplayString(2, 0, i, &st_POSSetupInfo.sz33StoreName[16], 0);
                }
            }
            pusServiceAddr++;
            break;

        case 0x1202: // View Information
            // "Model Name      ", "                ", "                ", "                "
            LCDDisplay4Lines(M4ViewPOSInfo_000002, -1, ucLangFlag);
            temp[0] = sz17HWInfo[9];
            temp[1] = sz17HWInfo[10];
            temp[2] = 0x00;
            switch (atoi(temp)) {
                case 31: strcpy(c65TempKeyBuf, "IC3100PE");
                    break;
                case 51: strcpy(c65TempKeyBuf, "IC5100P");
                    break;
                default: strcpy(c65TempKeyBuf, "Unknown Code");
                    break;
            }
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            pusServiceAddr++;
            break;

        case 0x1203: // View Information
            // "S/W Version     ", "                ", "S/W Date        ", "                "
            LCDDisplay4Lines(M4ViewPOSInfo_000003, -1, ucLangFlag);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, sz17ProgramVersion, ucLangFlag);
            strcpy(c65TempKeyBuf, sz17ProgramDate);
            LCD_DisplayLine(3, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            sTempKey = 0;
            pusServiceAddr++;
            break;
        case 0x1204: // View Information
            if (sTempKey == 0) {
                // "SERVER IP 1     ", "                ", "SERVER PORT NO 1", "                "
                LCDDisplay4Lines(M4ViewInfoServer_001, -1, ucLangFlag);
                LCD_DisplayLine(1, LEFT_JUSTIFIED, st_POSSetupInfo.sz16TrxnServerIP[0], ucLangFlag);
                LCD_DisplayLine(3, LEFT_JUSTIFIED, st_POSSetupInfo.sz6TrxnServerPortNo[0], ucLangFlag);
            } else if (sTempKey == 1) {
                // "SERVER IP 2     ", "                ", "SERVER PORT NO 2", "                "
                LCDDisplay4Lines(M4ViewInfoServer_002, -1, ucLangFlag);
                LCD_DisplayLine(1, LEFT_JUSTIFIED, st_POSSetupInfo.sz16TrxnServerIP[1], ucLangFlag);
                LCD_DisplayLine(3, LEFT_JUSTIFIED, st_POSSetupInfo.sz6TrxnServerPortNo[1], ucLangFlag);
            } else if (sTempKey == 2) {
                // "TMS IP 1        ", "                ", "TMS PORT NO 1   ", "                "
                LCDDisplay4Lines(M4ViewInfoTMS_000001, -1, ucLangFlag);
                LCD_DisplayLine(1, LEFT_JUSTIFIED, st_POSSetupInfo.sz16TMSServerIP[0], ucLangFlag);
                LCD_DisplayLine(3, LEFT_JUSTIFIED, st_POSSetupInfo.sz6TMSServerPortNo[0], ucLangFlag);
            } else if (sTempKey == 3) {
                // "TMS IP 2        ", "                ", "TMS PORT NO 2   ", "                "
                LCDDisplay4Lines(M4ViewInfoTMS_000002, -1, ucLangFlag);
                LCD_DisplayLine(1, LEFT_JUSTIFIED, st_POSSetupInfo.sz16TMSServerIP[1], ucLangFlag);
                LCD_DisplayLine(3, LEFT_JUSTIFIED, st_POSSetupInfo.sz6TMSServerPortNo[1], ucLangFlag);
            } else if (sTempKey == 4) {
                sTempKey = 0;
                pusServiceAddr++;
                sVirtualKey = BTKEY_ENTER;
                break;
            }
            sTempKey++;
            break;
        case 0x1205: // View Information
            // "Help Desk Tel No", "                ", "                ", "                "
            LCDDisplay4Lines(M4HelpDeskPhoneNo_01, -1, ucLangFlag);
            if (sTempKey == 2) {
                sVirtualKey = BTKEY_CANCEL;
                break;
            }

            if (sTempKey < 1) {
                j = 3;
            } else {
                j = 1;
            }
            for (i = 0; i < j; i++) {
                k = (sTempKey * 3) + i;
                sprintf(c65TempKeyBuf, "%d)%s", k + 1, st_POSSetupInfo.sz17HelpDeskTelNo[k]);
                LCD_DisplayLine(i + 1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            }
            sTempKey++;
            break;

        case 0x1300: // Initialize - Select Initialize menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1:
                    // "Reset Parameters", "1.NO            ", "2.YES           ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_INITIALIZE, M4ResetParameter_001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
                    pusServiceAddr++;
                    break;
                case BTKEY_2:
                    // "Reset Merchant  ", "1.NO            ", "2.YES           ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_INITIALIZE, M4ResetMerchant_0001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
                    pusServiceAddr += 2;
                    break;
                case BTKEY_3:
                    // "Erase POS Logs  ", "1.NO            ", "2.YES           ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_INITIALIZE, M4ErasePOSLogs_00001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
                    pusServiceAddr += 3;
                    break;
            }
            break;

        case 0x1301: // Reset Param. - Reset Parameters
            if (sSelectedMenuItemNo == BTKEY_2) {
                ResetPOSSetupInfo();
                InitializeTMSDownloadInfo();
            }
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x1302: // Reset Merchant's Password - Reset Merchant
            if (sSelectedMenuItemNo == BTKEY_2) {
                ResetMerchantPassword();
            }
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x1303: // Erase Transaction Logs
            if (sSelectedMenuItemNo == BTKEY_2) {
                // "Erase POS Logs  ", "                ", " Please Wait... ", "                "
                LCDDisplay4Lines(M4ErasePOSLogs_00002, -1, ucLangFlag);
                EraseAllTransactionLog();
            }
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x1400: // Change Maintenance's Password - Input New Maintenance's Password
        case 0x2600: // Change Merchant's Password - Input New Merchant's Password
            if (strlen(c65TempKeyBuf) < 4) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memset(c65TempBuf, 0x00, sizeof (c65TempBuf));
            strcpy(c65TempBuf, c65TempKeyBuf);

            // "Confirm Password", "                ", "                ", "                "
            LCDDisplay4Lines(M4ConfirmPassword_01, -1, ucLangFlag);
            memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
            ucKeyCnt = 0;
            cYPos = 2;
            cXPos = 2;
            cMaxInputCnt = 12;
            LCD_CursorOn(cYPos, cXPos);
            pusServiceAddr++;
            break;

        case 0x1401: // Change Maintenance's Password - Retype New Maintenance's Password
        case 0x2601: // Change Merchant's Password - Retype New Merchant's Password
            if (strlen(c65TempKeyBuf) < 4) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            if (strcmp(c65TempKeyBuf, c65TempBuf) == 0) {
                if (*pusServiceAddr == 0x1401) {
                    memcpy(st_POSSetupInfo.sz13MasterPIN, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz13MasterPIN));
                } else if (*pusServiceAddr == 0x2601) {
                    memcpy(st_POSSetupInfo.sz13MerchantPIN, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz13MerchantPIN));
                } else {
                    memcpy(st_POSSetupInfo.sz13CashierPIN, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz13CashierPIN));
                }

                WritePOSSetupInfo();

                // "Password Changed",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PasswordChanged_01], ucLangFlag);
                TIMER_Wait1MS(2000);
                sVirtualKey = BTKEY_CANCEL;
            } else {
                Beep_EventSound(ERROR_TONE);
                // "Mismatch Error  ",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1MismatchError_0001], ucLangFlag);
                TIMER_Wait1MS(2000);

                LCD_ClearLine(2);
                LCD_ClearLine(3);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                ucKeyCnt = 0;
                cYPos = 2;
                cXPos = 2;
                cMaxInputCnt = 12;
                LCD_CursorOn(cYPos, cXPos);
            }
            break;

        case 0x1500: // Hardware Test - Select Hardware Test menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Printer Test
                    // " <Printer Test> ", "                ", "Printing Now... ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_PRINTER_TEST, M4PrinterTest_000001, -1, ucLangFlag);
                    // NO PAPER?
                    if (!DetectPaper()) {
                        // "                ", "No Printer Paper", "                ", "                "
                        LCDDisplay4Lines(M4NoPrinterPaper_001, -1, ucLangFlag);
                        Beep_EventSound(ERROR_TONE);
                        TIMER_WaitKeyPress1MS(5000);
                        sVirtualKey = BTKEY_CANCEL;
                        return;
                    }
                    usPrintStep = 1;
                    break;
                case BTKEY_2: // MSR Test
                    // " <MSR Test> [ ] ", "                ", "                ", "Swipe your card "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_MSR_TEST, M4MSRTest_0000000001, -1, ucLangFlag);
                    MSRTest();
                    sVirtualKey = BTKEY_CANCEL;
                    break;
                case BTKEY_3: // Modem Test
                    // "  <Modem Test>  ", "                ", "                ", "Press ENTER Key "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_MODEM_TEST, M4ModemTest_00000001, -1, ucLangFlag);

                    i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 0);
                    if (i) {
                        Beep_EventSound(ERROR_TONE);
                        DisplayConnectionErrorCondition(i);
                        TIMER_WaitKeyPress1MS(5000);
                        usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                        sVirtualKey = BTKEY_CANCEL;
                        return;
                    }

                    iModemTestOKCnt = 0;
                    iModemTestTotalCnt = -1;
                    sVirtualKey = BTKEY_ENTER;
                    break;
                case BTKEY_4: // IC Card Test
                    // " <IC Card Test> ", "                ", "Read F/W Version", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_ICCARD_TEST, M4ICCardTest_0000001, -1, ucLangFlag);
                    ICCardTest();
                    sVirtualKey = BTKEY_CANCEL;
                    break;
                case BTKEY_5: // Key Test
                    // "                ", "                ", "                ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_KEY_TEST, M4_____________Space, -1, ucLangFlag);
                    if (iModelName == IC3100PE) {
                        KeyTest_IC3100PE();
                    } else {
                        KeyTest_IC5100P();
                    }
                    sVirtualKey = BTKEY_CANCEL;
                    break;
                case BTKEY_6: // LCD Test
                    // "   <LCD Test>   ", "1.Backlight Test", "2.Dot Test      ", "3.Contrast Test "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_LCD_TEST, M4LCDTestMenu_000001, -1, ucLangFlag);
                    LCDTest();
                    sVirtualKey = BTKEY_CANCEL;
                    break;
                case BTKEY_7: // RS232 Test
                    // "  <RS232 Test>  ", "                ", "                ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_RS232_TEST, M4RS232Test_00000001, -1, ucLangFlag);
                    RS232Test();
                    sVirtualKey = BTKEY_CANCEL;
                    break;
                case BTKEY_8: // RTC Test
                    // "   <RTC Test>   ", "                ", " Please Wait... ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_RTC_TEST, M4RTCTest_0000000001, -1, ucLangFlag);
                    RTCTest();
                    sVirtualKey = BTKEY_CANCEL;
                    break;
            }
            usAutoInitial10MSTimer = TIMER_Get10MSTimer();
            break;

        case 0x1530: // Modem Test - Display Swipe your card
            SetInitialStatus();

            // "  <Modem Test>  ", "                ", "                ", "Press ENTER Key "
            MainStatusSetting(MSS_SPECIAL_FUNC, MST_MODEM_TEST, M4ModemTest_00000001, -1, ucLangFlag);
            ucModemTestFlag = 1;
            iModemTestTotalCnt++;
            sprintf(temp, "[%d/%d]", iModemTestOKCnt, iModemTestTotalCnt);
            LCD_DisplayLine(1, CENTER_JUSTIFIED, temp, ucLangFlag);
            giTransactionType = TRXN_TAMS_CALLHOME;
            pusServiceAddr += 4;
            //			sVirtualKey = BTKEY_ENTER;
            break;

        case 0x1532: // Modem Test - Display Enter your PIN
            // "Enter your PIN  ", "                ", "                ", "                "
            LCDDisplay4Lines(M4EnterYourPIN_00001, -1, ucLangFlag);
            memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
            ucKeyCnt = 0;
            cYPos = 2;
            cXPos = 2;
            cMaxInputCnt = 4;
            LCD_CursorOn(cYPos, cXPos);

            usMsgType = MTYPE_FINANCIAL_TRXN_REQUEST;
            ulPCode = PCODE_DEBIT_BALANCE_INQUIRY;
            GetTransactionType(&usTransType, usMsgType, ulPCode);

            pusServiceAddr++;
            break;

        case 0x1533: // Modem Test - Enter your PIN
        case 0x5109: // Buy - Enter your PIN
        case 0x5201: // Balance Inquiry - Enter your PIN
        case 0x5401: // SIM Charge(Preliminary Transaction) - Enter your PIN
            if (strlen(c65TempKeyBuf) < 4) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            LCD_CursorOff();
            strcpy(sz13CardPIN, c65TempKeyBuf);
            if (*pusServiceAddr == 0x1533) {
                pusServiceAddr++;
                sVirtualKey = BTKEY_ENTER;
            } else if (*pusServiceAddr == 0x5107) {
                pusServiceAddr += 12;
                sVirtualKey = BTKEY_ENTER;
            } else {
                if (*pusServiceAddr == 0x5109 && ucPINInputAndReconnectFlag == 1) {
                    pusServiceAddr += 10;
                } else {
                    pusServiceAddr += 2;
                }
                sVirtualKey = BTKEY_ENTER;
            }
            break;

        case 0x11E2:
        case 0x11F1:
        case 0x1534: // Modem Test - Dialing
        case 0x2120: // Previous Merchant Total - Dialing
        case 0x2130: // Clear Merchant Total - Dialing
        case 0x5113: // Buy - Dialing
        case 0x5203: // Balance Inquiry - Dialing
        case 0x5406: // SIM Charge(Preliminary Transaction) - Dialing
        case 0x9200: // Reversal - Dialing
        case 0x2101: // Reversal - Dialing (sispp)
#if 0 // sispp 20111228
            if (*pusServiceAddr != 0x9200) {
                strcpy(st_TrxnReqData.sz9TerminalID, st_POSSetupInfo.sz9TerminalID);
                strcpy(st_TrxnReqData.sz16MerchantID, st_POSSetupInfo.sz16MerchantID);
            }
#endif

            memset(ucTrxnTxBuf, 0x00, sizeof (ucTrxnTxBuf));
            ucGprsConnectCnt = 0;
            ucReqDataReadyFlag = 1;
#ifdef TEST_OFFLINE
            usGprs10MSMaxTimeout = (unsigned short) (st_POSSetupInfo.ucCommTimeout) * 100;
            usGprsTaskStep = 201; // Wait for data setup & Sending Data
#else
            ModemOpen(NORMAL_CONNECTION);
#endif
            pusServiceAddr++;
            break;

        case 0x2000: // Select Merchant Item in Main Menu - Input Merchant's Password
            if (strlen(c65TempKeyBuf) < 4) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            if (!strcmp(c65TempKeyBuf, st_POSSetupInfo.sz13MerchantPIN)) {
                // "   Supervisor   ", "1.Reversal      ", "2.Balance       ", "3.End-of-Day    "
                LCDDisplay4Lines(M4Supervisor_0000001, LCD_LINE1, ucLangFlag);
                SetMenuScrollUpDownInfo(1, 1, 1, 6, (char *) LCD_MSG_TBL1[ucLangFlag][M1Supervisor_0000002]);
                pusServiceAddr++;
            } else {
                Beep_EventSound(ERROR_TONE);
                // "????????????????", "????????????????", "????????????????", "Wrong Password  "
                LCDDisplay4Lines(M4WrongPassword_0001, -1, ucLangFlag);
                TIMER_Wait1MS(2000);

                LCD_ClearLine(2);
                LCD_ClearLine(3);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                ucKeyCnt = 0;
                cYPos = 2;
                cXPos = 2;
                cMaxInputCnt = 12;
                LCD_CursorOn(cYPos, cXPos);
            }
            break;

        case 0x2001: // Supervisor Menu - Select Supervisor menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Reversal
                    i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 1);
                    if (i) {
                        DisplayConnectionErrorConditionAndGotoInitialStatus(i);
                        return;
                    }
                    // "    Reversal    ", "Enter Stan:     ", "                ", "[              ]"
                    MainStatusSetting(MSS_F1_REVERSAL_TRANS, MST_F1_REVERSAL_TRANS, M4Reversal_000000001, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 2;
                    cMaxInputCnt = 12;
                    LCD_CursorOn(cYPos, cXPos);
                    break;
                case BTKEY_2:
                    i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 1);
                    if (i) {
                        DisplayConnectionErrorConditionAndGotoInitialStatus(i);
                        return;
                    }
                    if (InitTrxnReqData() < 0) {
                        ErrorDisplayAndGoErrorStatus(M4ErrNoBatchNo_00001, -1, ucLangFlag);
                        return;
                    }
                    usAutoInitial10MSTimer = TIMER_Get10MSTimer();
                    MainStatusSetting(MSS_CUSTOMER_TRANS, MST_CUSTOMER_TRANS, M4InsertSwipeCard_01, -1, ucLangFlag);
                    pusServiceAddr += 2;
                    giTransactionType = TRXN_BANK_EFTTRAN;
                    st_TrxnReqData.usTrxnType = TRXN_BALANCE_INQUIRY;
                    isDetectCard = 0;
                    gbEmvScTaskStep = 2;
                    break;
                case BTKEY_3: // End-of-Day
                    // "   End of Day   ", "1.Today         ", "2.Print Last Txn", "                "
                    /*					MainStatusSetting(MSS_F1_FUNC, MST_F1_ENDOFDAY, M4EndOfDay_000000001, LCD_LINE1, ucLangFlag);
                                                            SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *)LCD_MSG_TBL1[ucLangFlag][M1EndOfDay_000000002]);
                     */
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_EOD_TODAY, M4_____________Dummy, -1, ucLangFlag);
                    sprintf(temp, "BatchNo : %6d", tPOSUtilBuf.usBatchNo);
                    LCD_DisplayLine(0, LEFT_JUSTIFIED, temp, ucLangFlag);
                    sprintf(temp, "TrxnCnt : %6d", usEodTrxnCount);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, temp, ucLangFlag);
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PressEnterKey_0001], ucLangFlag);
                    //if(tPOSUtilBuf.usBatchNo <= 0 || (tPOSUtilBuf.usBatchNo > 0 && usEodTrxnCount <= 0)) {
                    if (tPOSUtilBuf.usBatchNo <= 0) {
                        LCD_DisplayLine(3, LEFT_JUSTIFIED, "to get new Batch", ucLangFlag);
                    } else {
                        LCD_DisplayLine(3, LEFT_JUSTIFIED, "to start EOD    ", ucLangFlag);
                    }
                    giTransactionType = TRXN_BANK_EFTTOTAL;
                    break;
                case BTKEY_4: // Setup POS
                    // "Setup POS Status", "1.Set CallHome  ", "2.Set Timeout   ", "3.Set Date      "
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_FUNC, M4SVSetupPOS_0000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 6, (char *) LCD_MSG_TBL1[ucLangFlag][M1SVSetupPOS_0000002]);
                    break;
                case BTKEY_5: // Remote Download
                    // "????????????????", "????????????????", "????????????????", "????????????????"
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_REMOTEDOWNLOAD, M4_____________Dummy, -1, ucLangFlag);
                    sVirtualKey = BTKEY_ENTER;
                    break;
                case BTKEY_6: // Change Merchant's Passord
                    // "New Password    ", "                ", "                ", "                "
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_CHANGE_MERCHANT_PIN, M4NewPassword_000001, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 2;
                    cMaxInputCnt = 12;
                    LCD_CursorOn(cYPos, cXPos);
                    break;
            }
            break;

        case 0x2100: // Merchant Operations Menu - Select Merchant Operations menu item
            // Find STAN in the log
#ifdef USER_DEBUG
            Rprintf("STAN = %s\r\n", c65TempKeyBuf);
#endif   
            if (InitTrxnReqData() < 0) {
                ErrorDisplayAndGoErrorStatus(M4ErrNoBatchNo_00001, -1, ucLangFlag);
                return;
            }
            st_TrxnReqData.usTrxnType = TRXN_REVERSAL;
            if (SetReversalReqData(c65TempKeyBuf) == -1) {
                // STAN is not found
                LCD_DisplayLine(3, LEFT_JUSTIFIED, "STAN Not Found! ", ucLangFlag);
                Beep_EventSound(ERROR_TONE);
#ifdef USER_DEBUG
                Rprintf("STAN %s is not found in the transaction log.\r\n", c65TempKeyBuf);
#endif
                return;
            }
#ifdef USER_DEBUG
            Rprintf("st_TrxnReqData.usTrxnType     = %d\r\n", st_TrxnReqData.usTrxnType);
            Rprintf("st_TrxnReqData.usOrigSeqNo     = %d\r\n", st_TrxnReqData.usOrigSeqNo);
            Rprintf("st_TrxnReqData.sz9OrigTerminalID     = %s\r\n", st_TrxnReqData.sz9OrigTerminalID);
            Rprintf("st_TrxnReqData.ulReversalDateTime     = %d\r\n", st_TrxnReqData.ulReversalDateTime);
            Rprintf("st_TrxnReqData.usReversalTrxnType     = %d\r\n", st_TrxnReqData.usReversalTrxnType);
            Rprintf("st_TrxnReqData.sz13ReferenceNo     = %s\r\n", st_TrxnReqData.sz13ReferenceNo);
#endif
            giTransactionType = TRXN_BANK_EFTTRAN;

            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            return;

            i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 1);
            if (i) {
                DisplayConnectionErrorConditionAndGotoInitialStatus(i);
                return;
            }

            usMsgType = MTYPE_SUPERVISORY_TRXN_REQUEST;
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Current Merchant Total
                    //					ulPCode = PCODE_CURRENT_MERCHANT_TOTAL;
                    //					pusServiceAddr = (unsigned short *)&tbl_MainService[MST_F1_CUR_MERCHANT_TOTAL][0];
                    break;
                case BTKEY_2: // Previous Merchant Total
                    //					ulPCode = PCODE_PREVIOUS_MERCHANT_TOTAL;
                    //					pusServiceAddr = (unsigned short *)&tbl_MainService[MST_F1_PRE_MERCHANT_TOTAL][0];
                    break;
                case BTKEY_3: // Clear Merchant Total
                    //					ulPCode = PCODE_CLEAR_MERCHANT_TOTAL;
                    //					pusServiceAddr = (unsigned short *)&tbl_MainService[MST_F1_CLR_MERCHANT_TOTAL][0];
                    break;
            }
            GetTransactionType(&usTransType, usMsgType, ulPCode);
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x2110:
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Today
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_EOD_TODAY, M4_____________Dummy, -1, ucLangFlag);
                    sprintf(temp, "BatchNo : %6d", tPOSUtilBuf.usBatchNo);
                    LCD_DisplayLine(0, LEFT_JUSTIFIED, temp, ucLangFlag);
                    sprintf(temp, "TrxnCnt : %6d", usEodTrxnCount);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, temp, ucLangFlag);
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PressEnterKey_0001], ucLangFlag);
                    //if(tPOSUtilBuf.usBatchNo <= 0 || (tPOSUtilBuf.usBatchNo > 0 && usEodTrxnCount <= 0)) {
                    if (tPOSUtilBuf.usBatchNo <= 0) {
                        LCD_DisplayLine(3, LEFT_JUSTIFIED, "to get new Batch", ucLangFlag);
                    } else {
                        LCD_DisplayLine(3, LEFT_JUSTIFIED, "to start EOD    ", ucLangFlag);
                    }
                    giTransactionType = TRXN_BANK_EFTTOTAL;
                    break;
                case BTKEY_2: // Print Last Txn
                    // Last Transaction�� ����Ÿ�� �غ�
                    break;
                case BTKEY_3: // Past Day
                    // "    Past Day    ", "Enter Date in   ", "   DDMMYY format", " [        ]     "
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_EOD_PASTDAY, M4PastDay_0000000001, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 3;
                    cXPos = 3;
                    cMaxInputCnt = 6;
                    LCD_CursorOn(cYPos, cXPos);
                    break;
            }
            break;

        case 0x2112: // Current Merchant Total - Go to Print Initial Status
        case 0x2122: // Previous Merchant Total - Go to Print Initial Status
        case 0x2132: // Clear Merchant Total - Go to Print Initial Status
        case 0x5116: // Buy - Go to Print Initial Status
        case 0x5208: // Balance Inquiry - Go to Print Initial Status
        case 0x5408: // SIM Charge(Preliminary Transaction) - Go to Print Initial Status
        case 0x2103: // Reversal - Printing (sispp)
            switch (*pusServiceAddr) {
                default:
                    pstfTempTrxnLog = pstfSavingTrxnLog;
                    break;
            }
            usPrintStep = 1;
            pusServiceAddr++;
            break;

        case 0x2114: // Current Merchant Total - Display Printing Error
        case 0x2124: // Previous Merchant Total - Display Printing Error
        case 0x2134: // Clear Merchant Total - Display Printing Error
        case 0x5118: // Buy - Display Printing Error
        case 0x520A: // Balance Inquiry - Display Printing Error
        case 0x540A: // SIM Charge(Preliminary Transaction) - Display Printing Error
        case 0x2105: // Reversal - Display Printing Error (sispp)
            if (*pusServiceAddr == 0x5118 && usResponseCode == 0x3030 &&
                    pstfTempTrxnLog->ucStatus.BIT.NotPrint1Flag == 1) {
                pstfTempTrxnLog = pstfSavingTrxnLog;
                // Save Reversal TransactionLog
                SaveReversalTransactionLog(pstfTempTrxnLog);
                // Display "Insert paper" or print a reversal receipt
                PrintReversalReceipt(0);
            } else {
                // "Can not Print!  ", "1.Reprint       ", "2.Exit          ", "                "
                LCDDisplay4Lines(M4CanNotPrintMenu_01, LCD_LINE1, ucLangFlag);
                SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1CanNotPrintMenu_02]);
                pusServiceAddr++;
            }
            break;

        case 0x2115: // Current Merchant Total - Select Reprint or Exit
        case 0x2125: // Previous Merchant Total - Select Reprint or Exit
        case 0x2135: // Clear Merchant Total - Select Reprint or Exit
        case 0x5119: // Not Approved Buy - Select Reprint or Exit
        case 0x520B: // Balance Inquiry - Select Reprint or Exit
        case 0x540B: // SIM Charge(Preliminary Transaction) - Select Reprint or Exit
        case 0x2106: // Reversal - Display Printing Error (sispp)
            if (sSelectedMenuItemNo == BTKEY_1) {
                // Set Print Pre-printing Area Flag for printing of pre-printing area
                ucPrintPrePrintingAreaFlag = 1;
                // "Reprint         ", "                ", "Printing Now... ", "                "
                LCDDisplay4Lines(M4ReprintMsg_0000001, -1, ucLangFlag);
                pusServiceAddr -= 3;
                sVirtualKey = BTKEY_ENTER;
            } else {
                switch (*pusServiceAddr) {
                    case 0x5119: // Not Approved Buy - Select Reprint or Exit
                        // Save Print Transaction Log
                        if (pstfTempTrxnLog->ucStatus.BIT.NotPrint1Flag == 1) {
                            SavePrintTransactionLog(pstfTempTrxnLog, 0);
                        } else {
                            SavePrintTransactionLog(pstfTempTrxnLog, 1);
                        }
                        SetInitialStatus();
                        break;
                    default:
                        // Save Print Transaction Log
                        SavePrintTransactionLog(pstfTempTrxnLog, 0);
                        SetInitialStatus();
                        break;
                }
            }
            break;

        case 0x9301: // Set Telephone Menu - Select Set Telephone menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Access Code
                    sSelectedMenuItemNo = st_POSSetupInfo.ucPABXUse + 1;
                    // "PABX ACCESS     ", "1.NO            ", "2.YES           ", "                "
                    LCDDisplay4Lines(M4PABXAccess_0000001, sSelectedMenuItemNo, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, sSelectedMenuItemNo, sSelectedMenuItemNo, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
                    pusServiceAddr++;
                    break;
                case BTKEY_2: // Telephone No
                    // "TELEPHONE NO    ", "                ", "                ", "                "
                    LCDDisplay4Lines(M4TrxnTelephoneNo_01, -1, ucLangFlag);
                    sTempKey = 1;
                    DisplayTrxnTelNo();
                    pusServiceAddr += 6;
                    break;
                case BTKEY_3: // Pulse Dial
                    sSelectedMenuItemNo = st_POSSetupInfo.ucPulseDial + 1;
                    // "PULSE DIAL      ", "1.NO            ", "2.YES           ", "                "
                    LCDDisplay4Lines(M4PulseDial_00000001, sSelectedMenuItemNo, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, sSelectedMenuItemNo, sSelectedMenuItemNo, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
                    pusServiceAddr += 7;
                    break;
            }
            break;

        case 0x9309: // Setup Ethernet Server - Input Server IP Address 1
            if (KEY_CheckIPAddress(c65TempKeyBuf)) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memcpy(st_POSSetupInfo.sz16TrxnServerIP[0], c65TempKeyBuf, sizeof (st_POSSetupInfo.sz16TrxnServerIP[0]));

            // "SERVER PORT NO 1", "                ", "                ", "                "
            LCDDisplay4Lines(M4ServerPortNo_00001, -1, ucLangFlag);
            ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz6TrxnServerPortNo[0]);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 5;
            if (strlen(c65TempKeyBuf) == 0) {
                LCD_CursorOn(cYPos, cXPos);
            }
            pusServiceAddr++;
            break;

        case 0x930A: // Setup Ethernet Server - Input Server Port Number 1
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            ltemp = atol(c65TempKeyBuf);
            if (ltemp > 65535L) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            sprintf(st_POSSetupInfo.sz6TrxnServerPortNo[0], "%ld", ltemp);
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x930B: // Setup GSM Server - Input GSM City Access Code
            if (strlen(c65TempKeyBuf) == 0) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            memcpy(st_POSSetupInfo.sz10GsmCityCode, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz10GsmCityCode));

            // "TELEPHONE NO    ", "                ", "                ", "                "
            LCDDisplay4Lines(M4TrxnTelephoneNo_01, -1, ucLangFlag);
            sTempKey = 1;
            DisplayTrxnTelNo();
            pusServiceAddr++;
            break;

        case 0x2900: // Display Select TMS menu
            // "Remote Download ", "1.TMS Server    ", "2.TMS Download  ", "                "
            MainStatusSetting(MSS_F1_FUNC, MST_F1_REMOTEDOWNLOAD, M4TMSMenu_0000000001, LCD_LINE1, ucLangFlag);
            SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1TMSMenu_0000000011]);
            pusServiceAddr++;
            break;

        case 0x290F: // Remote Download - Select Remote Download for Ethernet
            if (sSelectedMenuItemNo == BTKEY_1) {
                sVirtualKey = BTKEY_CANCEL;
            } else {
                ResetTrxnTelNo();
                ResetTMSTelNo();

                WritePOSSetupInfo();
                TIMER_Wait1MS(1000);

                i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 3, 0);
                if (i) {
                    DisplayConnectionErrorConditionAndGotoInitialStatus(i);
                    return;
                }

#ifdef USER_DEBUG
                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                sprintf(temp, "%02X%02X%02X%02X%02X%02X%02X",
                        RealTime.CLKYEARH, RealTime.CLKYEARL, RealTime.CLKMONTH, RealTime.CLKDATE,
                        RealTime.CLKHOUR, RealTime.CLKMIN, RealTime.CLKSEC);
                Rprintf("\r\n");
                Rprintf("tTMSDownloadInfo.sz9UpgradedDate = %s\r\n", tTMSDownloadInfo.sz9UpgradedDate);
                Rprintf("Date & Time          : %02X%02X/%02X/%02X %02X:%02X:%02X - %d[%s]\r\n",
                        RealTime.CLKYEARH, RealTime.CLKYEARL, RealTime.CLKMONTH, RealTime.CLKDATE,
                        RealTime.CLKHOUR, RealTime.CLKMIN, RealTime.CLKSEC,
                        RealTime.CLKDAY, DAY_STR_TBL[RealTime.CLKDAY % 7]);
                Rprintf("\r\n");
#endif

                ucTMSDownloadFlag = 1; // Set TMS download mode
                iTMS_ProcessStep = 1; // Go to dialing
                pusServiceAddr++;
            }
            break;

        case 0x290A: // Remote Download - Select TMS menu for Ethernet
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Setup TMS Server for Ethernet
                    // "TMS IP 1       ", "                ", "                ", "*='.'           "
                    LCDDisplay4Lines(M4TMSServerIP_000001, -1, ucLangFlag);
                    ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz16TMSServerIP[0]);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                    ucKeyCnt = 0;
                    cYPos = 1;
                    cXPos = 0;
                    if (strlen(c65TempKeyBuf) == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    pusServiceAddr++;
                    break;
                default: // TMS Download for Ethernet
                    // "Remote Download ", "1.NO            ", "2.YES           ", "                "
                    LCDDisplay4Lines(M4RemoteDownload_001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1NO_000000000000001]);
                    pusServiceAddr += 5;
                    break;
            }
            break;


        case 0x4000: // Setup POS Status Menu - Select Setup POS Status menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Enter CallHome
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_CALLHOME, M4EnterCallHome_0001, -1, ucLangFlag);
                    ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz5CallHomeInterval);
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 6;
                    cMaxInputCnt = 4;
                    LCD_DisplayString(cYPos, cXPos, strlen(c65TempKeyBuf), c65TempKeyBuf, ucLangFlag);
                    if (strlen(c65TempKeyBuf) == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    sTempKey = 0;
                    break;
                case BTKEY_2: // Set Comm Timeout
                    // " Comm. Timeout  ", "Enter Timeout   ", "     [    ]     ", "                "
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_COMM_TIMEOUT, M4EnterCommTimeout_1, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    sprintf(c65TempKeyBuf, "%d", st_POSSetupInfo.ucCommTimeout);
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 7;
                    cMaxInputCnt = 2;
                    LCD_DisplayString(cYPos, cXPos, strlen(c65TempKeyBuf), c65TempKeyBuf, ucLangFlag);
                    if (strlen(c65TempKeyBuf) == 0) {
                        LCD_CursorOn(cYPos, cXPos);
                    }
                    sTempKey = 0;
                    break;
                case BTKEY_3: // Set Date
                    // "Set Date        ", "    YYYYMMDD    ", "                ", "=>              "
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_DATE, M4SetDate_0000000001, -1, ucLangFlag);
                    RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                    DisplayYYYYMMDD(&RealTime, GREGORIAN_CALENDAR);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 3;
                    cXPos = 4;
                    LCD_CursorOn(cYPos, cXPos);
                    break;
                case BTKEY_4: // Set Time
                    // "Set Time        ", "    hhmmss      ", "                ", "=>              "
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_TIME, M4SetTime_0000000001, -1, ucLangFlag);
                    RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                    Displayhhmmss(&RealTime);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 3;
                    cXPos = 4;
                    LCD_CursorOn(cYPos, cXPos);
                    break;
                case BTKEY_5: // Set LCD Contrast
                    // "LCD Contrast    ", "1:Light 2:Dark  ", "                ", "                "
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_CONTRAST, M4LCDContrast_000001, -1, ucLangFlag);
                    sTempKey = st_POSSetupInfo.ucLCDContrast;
                    sprintf(temp, "[%2d]", sTempKey);
                    LCD_DisplayLine(2, CENTER_JUSTIFIED, temp, ucLangFlag);
                    break;
                case BTKEY_6: // Set Beep Sound
                    sSelectedMenuItemNo = st_POSSetupInfo.ucBeep + 1;
                    // "Beep Sound      ", "1.OFF           ", "2.ON            ", "                "
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_BEEP_SOUND, M4BeepSound_00000001, sSelectedMenuItemNo, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, sSelectedMenuItemNo, sSelectedMenuItemNo, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1OFF_00000000000001]);
                    break;
            }
            break;

        case 0x4100: // Set Call Home Interval
            memcpy(st_POSSetupInfo.sz5CallHomeInterval, c65TempKeyBuf, sizeof (st_POSSetupInfo.sz5CallHomeInterval));
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x4200: // Set Comm Timeout
            if (atoi(c65TempKeyBuf) < 20 || atoi(c65TempKeyBuf) > 70) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            st_POSSetupInfo.ucCommTimeout = atoi(c65TempKeyBuf);
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x4300: // Set Date - Input Date
            if (strlen(c65TempKeyBuf) != 0 && strlen(c65TempKeyBuf) != 8) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            if (strlen(c65TempKeyBuf) == 8) {
                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                c65TempKeyBuf[ 8] = (RealTime.CLKHOUR >> 4) + '0';
                c65TempKeyBuf[ 9] = (RealTime.CLKHOUR & 0x0F) + '0';
                c65TempKeyBuf[10] = (RealTime.CLKMIN >> 4) + '0';
                c65TempKeyBuf[11] = (RealTime.CLKMIN & 0x0F) + '0';
                c65TempKeyBuf[12] = (RealTime.CLKSEC >> 4) + '0';
                c65TempKeyBuf[13] = (RealTime.CLKSEC & 0x0F) + '0';
                c65TempKeyBuf[14] = 0x00;

                RTC_SetDateTime(c65TempKeyBuf, GREGORIAN_CALENDAR);

                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                DisplayYYYYMMDD(&RealTime, GREGORIAN_CALENDAR);

                pusServiceAddr -= 2;

                // "Date is changed ",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DateIsChanged_0001], ucLangFlag);
                TIMER_Wait1MS(2000);

                // "Set Date        ", "    YYYYMMDD    ", "                ", "=>              "
                MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_DATE, M4SetDate_0000000001, -1, ucLangFlag);
                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                DisplayYYYYMMDD(&RealTime, GREGORIAN_CALENDAR);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                ucKeyCnt = 0;
                cYPos = 3;
                cXPos = 4;
                LCD_CursorOn(cYPos, cXPos);
            } else {
                sVirtualKey = BTKEY_CANCEL;
            }
            break;

        case 0x4400: // Set Time - Input Time
            if (strlen(c65TempKeyBuf) != 0 && strlen(c65TempKeyBuf) != 6) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            if (strlen(c65TempKeyBuf) == 6) {
                c65TempKeyBuf[ 8] = c65TempKeyBuf[0];
                c65TempKeyBuf[ 9] = c65TempKeyBuf[1];
                c65TempKeyBuf[10] = c65TempKeyBuf[2];
                c65TempKeyBuf[11] = c65TempKeyBuf[3];
                c65TempKeyBuf[12] = c65TempKeyBuf[4];
                c65TempKeyBuf[13] = c65TempKeyBuf[5];

                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                c65TempKeyBuf[0] = (RealTime.CLKYEARH >> 4) + '0';
                c65TempKeyBuf[1] = (RealTime.CLKYEARH & 0x0F) + '0';
                c65TempKeyBuf[2] = (RealTime.CLKYEARL >> 4) + '0';
                c65TempKeyBuf[3] = (RealTime.CLKYEARL & 0x0F) + '0';
                c65TempKeyBuf[4] = (RealTime.CLKMONTH >> 4) + '0';
                c65TempKeyBuf[5] = (RealTime.CLKMONTH & 0x0F) + '0';
                c65TempKeyBuf[6] = (RealTime.CLKDATE >> 4) + '0';
                c65TempKeyBuf[7] = (RealTime.CLKDATE & 0x0F) + '0';
                c65TempKeyBuf[14] = 0x00;

                RTC_SetDateTime(c65TempKeyBuf, GREGORIAN_CALENDAR);

                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                Displayhhmmss(&RealTime);

                // "Time is changed ",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1TimeIsChanged_0001], ucLangFlag);
                TIMER_Wait1MS(2000);

                // "Set Time        ", "    hhmmss      ", "                ", "=>              "
                MainStatusSetting(MSS_F3_FUNC, MST_F3_SET_TIME, M4SetTime_0000000001, -1, ucLangFlag);
                RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
                Displayhhmmss(&RealTime);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                ucKeyCnt = 0;
                cYPos = 3;
                cXPos = 4;
                LCD_CursorOn(cYPos, cXPos);
            } else {
                sVirtualKey = BTKEY_CANCEL;
            }
            break;

        case 0x4500: // Set Contrast - Set LCD Contrast
            st_POSSetupInfo.ucLCDContrast = sTempKey;
            LCD_CONT(st_POSSetupInfo.ucLCDContrast);
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x4600: // Set Beep Sound - Select Beep Sound ON/OFF
            st_POSSetupInfo.ucBeep = sSelectedMenuItemNo - 1;
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 0x5001: // Swipe Card or Insert Smart Card - Select Customer Trans. menu item
            switch (c9ActiveTrxnMenuType[sSelectedMenuItemNo - 1]) {
                case TRXN_MENU_PURCHASE:
                    usMsgType = MTYPE_FINANCIAL_TRXN_REQUEST;
                    ulPCode = PCODE_CREDIT_BUY;
                    ucBuyTrxnType = BUY_TYPE_NORMAL_BUY;
                    break;
                case TRXN_MENU_RECHARGE:
                    usMsgType = MTYPE_AUTHORIZATION_REQUEST;
                    ulPCode = PCODE_BILL_PAYMENT_PRELIMINARY;
                    st_TrxnReqData.ucBillPaymentType = PAYMENT_TYPE_SIM_CHARGE;
                    break;
                case TRXN_MENU_BALANCE:
                    usMsgType = MTYPE_FINANCIAL_TRXN_REQUEST;
                    ulPCode = PCODE_CREDIT_BALANCE_INQUIRY;
                    break;
            }
            GetTransactionType(&usTransType, usMsgType, ulPCode);
            st_TrxnReqData.usTrxnType = usTransType;

            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x5002:
            // check swipe or insert
            // ok? -> processing transaction
            if (isDetectCard == 0) {
                LCDDisplay4Lines(M4InsertSwipeCard_01, -1, ucLangFlag);
                if (gbEmvScTaskStep <= 0) {
                    gbEmvScTaskStep = 2;
                }
                break;
            } else if (isDetectCard == 1) { // MSR swipe
                if (sz4CardServiceCode[0] == '2' || sz4CardServiceCode[0] == '6') {
                    // This is a IC card
                    // Please Insert
                    // a IC Card!

                    LCD_DisplayString(1, 0, 16, "This is IC Card!", ucLangFlag);
                    LCD_DisplayString(2, 0, 16, " Insert IC Card ", ucLangFlag);
                    if (gbEmvScTaskStep <= 0) {
                        gbEmvScTaskStep = 2;
                    }
                    break;
                }
            }
            /*
                                    switch (c9ActiveTrxnMenuType[sSelectedMenuItemNo-1]) {
                                            case TRXN_MENU_PURCHASE:
                                                    // "????????????????", "????????????????", "????????????????", "????????????????"
                                                    MainStatusSetting(MSS_PURCHASE, MST_BUY, M4_____________Dummy, -1, ucLangFlag);
                                                    //pusServiceAddr += 8;
                                                    break;
                                            case TRXN_MENU_RECHARGE:
                                                    // "????????????????", "????????????????", "????????????????", "????????????????"
                                                    MainStatusSetting(MSS_RECHARGE, MST_SIM_CHARGE, M4_____________Dummy, -1, ucLangFlag);
                                                    break;
                                            case TRXN_MENU_BALANCE:
                                                    // "????????????????", "????????????????", "????????????????", "????????????????"
                                                    MainStatusSetting(MSS_BALANCE, MST_BALANCE_INQUIRY, M4_____________Dummy, -1, ucLangFlag);
                                                    break;
                                    }
             */
            switch (st_TrxnReqData.usTrxnType) {
                case TRXN_PURCHASE_ONLY:
                    // "????????????????", "????????????????", "????????????????", "????????????????"
                    MainStatusSetting(MSS_PURCHASE, MST_BUY, M4_____________Dummy, -1, ucLangFlag);
                    break;
                case TRXN_BALANCE_INQUIRY:
                    // "????????????????", "????????????????", "????????????????", "????????????????"
                    MainStatusSetting(MSS_BALANCE, MST_BALANCE_INQUIRY, M4_____________Dummy, -1, ucLangFlag);
                    break;
            }

            sVirtualKey = BTKEY_ENTER;
            break;
            // Waiting 'Select account, last 4 digits of card no., enter amount'
        case 0x5100: // Select account
            LCDDisplay4Lines(M4SelAccount_0000001, LCD_LINE0, ucLangFlag);
            SetMenuScrollUpDownInfo(0, 1, 0, 4, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelAccount_0000001]);
            pusServiceAddr++;
            break;
        case 0x5101:
            st_TrxnReqData.ucAccount = sSelectedMenuItemNo - 1;
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;
        case 0x5102:
            pusServiceAddr += 2;
            sVirtualKey = BTKEY_ENTER;
            // "Enter last 4    ", "Digits of CardNo", "    [      ]    ", "                "
            /*			LCDDisplay4Lines(M4EnterLast4_0000001, -1, ucLangFlag);
                                    memset(c65TempKeyBuf, 0x00, sizeof(c65TempKeyBuf));
                                    ucKeyCnt = 0;
                                    cYPos = 2;
                                    cXPos = 6;
                                    cMaxInputCnt = 4;
                                    LCD_CursorOn(cYPos, cXPos);
                                    pusServiceAddr++;
             */ break;
        case 0x5103:
            // check last 4 digits
            for (i = 1; i < CardNo2[0] + 1; i++) {
                if (CardNo2[i] == '=' || CardNo2[i] == 0x00)
                    break;
            }
            if (i < 4 || memcmp(c65TempKeyBuf, &CardNo2[i - 4], 4) != 0) {
                // Error
                LCD_DisplayString(1, 0, 16, "  Invalid Card  ", ucLangFlag);
                LCD_DisplayString(2, 0, 16, "   (Mismatch)   ", ucLangFlag);
                Beep_EventSound(ERROR_TONE);
                TIMER_WaitKeyPress1MS(2000);
                //				sVirtualKey = BTKEY_CANCEL;
                pusServiceAddr--;
                sVirtualKey = BTKEY_ENTER;
                break;
            }
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;
        case 0x5104:
            // "INPUT AMOUNT    ", "                ", "                ", "                "
            LCDDisplay4Lines(M4InputAmount_000001, -1, ucLangFlag);
            memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
            c65TempKeyBuf[0] = '0';
            LCD_DisplayString(2, 12, 4, "0.00", ucLangFlag);
            ucKeyCnt = 0;
            cYPos = 2;
            cXPos = 15;
            cMaxInputCnt = 12;
            LCD_CursorOn(cYPos, cXPos);
            pusServiceAddr++;
            break;

        case 0x5105:
            if (c65TempKeyBuf[0] == '0') {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            LCD_CursorOff();
            strcpy(sz13Amount, c65TempKeyBuf);
            strcpy(st_TrxnReqData.sz13Amount, sz13Amount);
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x5106:
            if (isDetectCard == 2 && gbEmvScTaskStep == 17) {
                gbEmvScTaskStep++;
                pusServiceAddr++;
            } else {
                pusServiceAddr += 2;
                sVirtualKey = BTKEY_ENTER;
            }
            break;
        case 0x5107: // Waiting IC card processing
            if (isDetectCard == 2 && gbEmvScTaskStep == 99) {
                pusServiceAddr += 12; // 0x5113
                sVirtualKey = BTKEY_ENTER;
            }
            break;
        case 0x5200: // Waiting IC card processing
            if (isDetectCard == 2 && gbEmvScTaskStep == 99) {
                pusServiceAddr += 3;
                sVirtualKey = BTKEY_ENTER;
            }
            break;
        case 0x5400: // Waiting IC card processing
            if (isDetectCard == 2 && gbEmvScTaskStep == 99) {
                pusServiceAddr += 3;
                sVirtualKey = BTKEY_ENTER;
            }
            break;
            /*
                            case 0x5108:	// Enter Online PIN
                            case 0x5201:	// Enter Online PIN
                            case 0x5401:	// Enter Online PIN
                                    break;
                            case 0x5109:
                            case 0x5202:
                            case 0x5402:
                                    break;
             */

        case 0x5111: // Buy - Display customer ID
            if (ucBuyTrxnType == BUY_TYPE_BUY_WITH_EXTRA ||
                    ucBuyTrxnType == BUY_TYPE_BUY_WITH_EXTERNAL_PRINTER) {
                // "Customer ID     ", "                ", "                ", "                "
                LCDDisplay4Lines(M4InputCustomerID_01, -1, ucLangFlag);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                ucKeyCnt = 0;
                cYPos = 1;
                cXPos = 0;
                cMaxInputCnt = 18;
                LCD_CursorOn(cYPos, cXPos);
                pusServiceAddr++;

                // for Pre-dialing
                //ModemOpen(PRE_CONNECTION);
            } else {
                pusServiceAddr += 2;
                sVirtualKey = BTKEY_ENTER;
            }
            break;

        case 0x5112: // Buy - Input customer ID
            if (strlen(c65TempKeyBuf) == 0) {
                break;
            }

            memset(sz19BillID, 0x00, sizeof (sz19BillID));
            strcpy(sz19BillID, c65TempKeyBuf);
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x5115: // Wait completion if it is EMV transaction
        case 0x5205: // Wait completion if it is EMV transaction
            if (isDetectCard == 2 && gbEmvScTaskStep > 0)
                break;
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x5206: // Balance Inquiry - Display Balance and Print or Exit
            if (st_TrxnRespData.ucResult == '1') {
                // "                ", "                ", "1.Print         ", "2.Exit          "
                LCDDisplay4Lines(M4SelectPrintExit_01, LCD_LINE2, ucLangFlag);
                LCD_DisplayLine(0, LEFT_JUSTIFIED, st_TrxnRespData.sz13Balance, 0);
                LCD_DisplayLine(1, LEFT_JUSTIFIED, st_TrxnRespData.sz13Available, 0);
                SetMenuScrollUpDownInfo(2, 1, 2, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelectPrintExit_01]);
                pusServiceAddr++;
            }
            /*			if (usResponseCode == 0x3030) {
                                            // "                ", "                ", "1.Print         ", "2.Exit          "
                                            LCDDisplay4Lines(M4SelectPrintExit_01, LCD_LINE2, ucLangFlag);
				
                                            memcpy_null(temp, pstfSavingTrxnLog->uc25AdditionalResponseData, 12);
                                            sprintf(temp, "%.0lf", atof(temp));
                                            KEY_InsertCommaAndDot(c65CommaAndDotString, temp, ucCurrencyExp);
                                            strcpy(temp, c65CommaAndDotString);
                                            LCD_DisplayLine(1, RIGHT_JUSTIFIED, temp, ucLangFlag);
				
                                            SetMenuScrollUpDownInfo(2, 1, 2, 2, (char *)LCD_MSG_TBL1[ucLangFlag][M1SelectPrintExit_01]);
                                            pusServiceAddr++;
                                    }
                                    else {
                                            pusServiceAddr += 2;
                                            sVirtualKey = BTKEY_ENTER;
                                    }
             */ break;

        case 0x5207: // Balance Inquiry - Select Print or Exit
            if (sSelectedMenuItemNo == BTKEY_1) {
                pusServiceAddr++;
                sVirtualKey = BTKEY_ENTER;
            } else {
                sVirtualKey = BTKEY_CANCEL;
            }
            break;

        case 0x5A00:
            // "Enter Phone No  ", "                ", "[              ]", "                "
            LCDDisplay4Lines(M4EnterPhoneNo_00001, -1, ucLangFlag);
            memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
            ucKeyCnt = 0;
            cYPos = 2;
            cXPos = 2;
            cMaxInputCnt = 11;
            LCD_CursorOn(cYPos, cXPos);
            pusServiceAddr++;
            break;
        case 0x5A01:
            if (strlen(c65TempKeyBuf) < 11) {
                Beep_EventSound(ERROR_TONE);
                break;
            }
            LCD_CursorOff();
            strcpy(sz12PhoneNo, c65TempKeyBuf);
            // "Confirm Phone No", "                ", "[              ]", "                "
            LCDDisplay4Lines(M4ConfirmPhoneNo_001, -1, ucLangFlag);
            memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
            ucKeyCnt = 0;
            cYPos = 2;
            cXPos = 2;
            cMaxInputCnt = 11;
            LCD_CursorOn(cYPos, cXPos);
            pusServiceAddr++;
            break;
        case 0x5A02:
            if (strlen(c65TempKeyBuf) < 11) {
                Beep_EventSound(ERROR_TONE);
                break;
            }
            if (memcmp(sz12PhoneNo, c65TempKeyBuf, 11)) {
                // Error
                LCD_DisplayString(1, 0, 16, "  Phone Number  ", ucLangFlag);
                LCD_DisplayString(2, 0, 16, "   Mismatch!!   ", ucLangFlag);
                Beep_EventSound(ERROR_TONE);
                TIMER_WaitKeyPress1MS(2000);
                // "Confirm Phone No", "                ", "[              ]", "                "
                LCDDisplay4Lines(M4ConfirmPhoneNo_001, -1, ucLangFlag);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                ucKeyCnt = 0;
                cYPos = 2;
                cXPos = 2;
                cMaxInputCnt = 11;
                LCD_CursorOn(cYPos, cXPos);
                break;
            }
            LCD_CursorOff();
            //			strcpy(sz13Amount, c65TempKeyBuf);

            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x5A10: // SIM Charge(Preliminary Transaction) - Display Select Company
            // "GLO             ", "MTN Prepaid     ", "STARCOMMS       ", "ZAIN            "
            LCDDisplay4Lines(M4SelCompanyMenu_001, LCD_LINE0, ucLangFlag);
            SetMenuScrollUpDownInfo(0, 1, 0, 4, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelCompanyMenu_001]);
            pusServiceAddr++;
            break;
        case 0x5A11: // SIM Charge(Preliminary Transaction) - Select Company
            ucSIMChargeOperatorCode = sSelectedMenuItemNo - 1;

            switch (ucSIMChargeOperatorCode) {
                case OPERATOR_CODE_GLO:
                    // "GLO 500         ", "GLO 1000        ", "GLO 3000        ", "GLO OTHER       "
                    LCDDisplay4Lines(M4SelSIMAmount_00001, LCD_LINE0, ucLangFlag);
                    SetMenuScrollUpDownInfo(0, 1, 0, 4, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelSIMAmount_00001]);
                    break;
                case OPERATOR_CODE_MTN:
                    // "MTN 400         ", "MTN 750         ", "MTN 1500        ", "MTN OTHER       "
                    LCDDisplay4Lines(M4SelSIMAmount_00011, LCD_LINE0, ucLangFlag);
                    SetMenuScrollUpDownInfo(0, 1, 0, 4, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelSIMAmount_00011]);
                    break;
                case OPERATOR_CODE_STARCOMMS:
                    // "STARCOMMS 500   ", "STARCOMMS OTHER ", "                ", "                "
                    LCDDisplay4Lines(M4SelSIMAmount_00021, LCD_LINE0, ucLangFlag);
                    SetMenuScrollUpDownInfo(0, 1, 0, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelSIMAmount_00021]);
                    break;
                case OPERATOR_CODE_ZAIN:
                    // "ZAIN 500        ", "ZAIN 1000       ", "ZAIN OTHER      ", "                "
                    LCDDisplay4Lines(M4SelSIMAmount_00031, LCD_LINE0, ucLangFlag);
                    SetMenuScrollUpDownInfo(0, 1, 0, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1SelSIMAmount_00031]);
                    break;
            }
            pusServiceAddr++;
            break;
        case 0x5A12: // SIM Charge(Preliminary Transaction) - Select SIM Charge Amount
            i = 0;
            switch (ucSIMChargeOperatorCode) {
                case OPERATOR_CODE_GLO:
                    switch (sSelectedMenuItemNo) {
                        case 1: strcpy(sz13Amount, "50000");
                            break;
                        case 2: strcpy(sz13Amount, "100000");
                            break;
                        case 3: strcpy(sz13Amount, "300000");
                            break;
                        case 4: i = 1;
                            break;
                    }
                    break;
                case OPERATOR_CODE_MTN:
                    switch (sSelectedMenuItemNo) {
                        case 1: strcpy(sz13Amount, "40000");
                            break;
                        case 2: strcpy(sz13Amount, "75000");
                            break;
                        case 3: strcpy(sz13Amount, "150000");
                            break;
                        case 4: i = 1;
                            break;
                    }
                    break;
                case OPERATOR_CODE_STARCOMMS:
                    switch (sSelectedMenuItemNo) {
                        case 1: strcpy(sz13Amount, "50000");
                            break;
                        case 2: i = 1;
                            break;
                    }
                    break;
                case OPERATOR_CODE_ZAIN:
                    switch (sSelectedMenuItemNo) {
                        case 1: strcpy(sz13Amount, "50000");
                            break;
                        case 2: strcpy(sz13Amount, "100000");
                            break;
                        case 3: i = 1;
                            break;
                    }
                    break;
            }
            if (i == 1) {
                pusServiceAddr++;
            } else {
                pusServiceAddr += 3;
            }
            sVirtualKey = BTKEY_ENTER;
            break;

        case 0x9000: // Print Reversal Receipt - "Insert paper and Press ENTER key"
            // Display "Insert paper" or print a reversal receipt
            PrintReversalReceipt(0);
            break;

        case 0x9100: // Reversal Mode - Select Reversal Mode menu item
            switch (sSelectedMenuItemNo) {
                case BTKEY_1: // Reversal
                    // Perform Reversal Transaction
                    PerformReversalTransaction();
                    break;
                case BTKEY_2: // Set Telephone
                    // "Enter Password  ", "                ", "                ", "                "
                    MainStatusSetting(MSS_REVERSAL, MST_REVERSAL_SETTELEPHONE, M4EnterPassword_0001, -1, ucLangFlag);
                    memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                    ucKeyCnt = 0;
                    cYPos = 2;
                    cXPos = 2;
                    cMaxInputCnt = 12;
                    LCD_CursorOn(cYPos, cXPos);
                    break;
                case BTKEY_3: // 3.Print & Clear
                    PrintUnsuccessfulReversalReceipt();
                    break;
            }
            break;

        case 0x9300: // Change parameters of telephone in Reversal Mode - Input Merchant's or Cashier's Password
            if (strlen(c65TempKeyBuf) < 4) {
                Beep_EventSound(ERROR_TONE);
                break;
            }

            if (!strcmp(c65TempKeyBuf, st_POSSetupInfo.sz13MerchantPIN) ||
                    !strcmp(c65TempKeyBuf, st_POSSetupInfo.sz13CashierPIN)) {
                // "SERVER IP 1     ", "                ", "                ", "*='.'           "
                MainStatusSetting(MSS_REVERSAL, MST_REVERSAL_SETTELEPHONE, M4ServerIPAddress_01, -1, ucLangFlag);
                ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz16TrxnServerIP[0]);
                LCD_DisplayLine(1, LEFT_JUSTIFIED, c65TempKeyBuf, ucLangFlag);
                ucKeyCnt = 0;
                cYPos = 1;
                cXPos = 0;
                if (strlen(c65TempKeyBuf) == 0) {
                    LCD_CursorOn(cYPos, cXPos);
                }
                pusServiceAddr += 9;
            } else {
                Beep_EventSound(ERROR_TONE);
                // "????????????????", "????????????????", "????????????????", "Wrong Password  "
                LCDDisplay4Lines(M4WrongPassword_0001, -1, ucLangFlag);
                TIMER_Wait1MS(2000);

                LCD_ClearLine(2);
                LCD_ClearLine(3);
                memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
                cYPos = 2;
                cXPos = 2;
                cMaxInputCnt = 12;
                LCD_CursorOn(cYPos, cXPos);
                ucKeyCnt = 0;
            }
            break;

            // Print Unsuccessful Reversal Receipt - "Insert paper and Press ENTER key"
        case 0x9400:
            PrintUnsuccessfulReversalReceipt();
            break;
    }
}

void CancelKeyService(void) {
#ifdef USER_DEBUG
    Rprintf("CancelKeyService: usPrintStep=%d, ucReversalFlag=%d\r\n", usPrintStep, ucReversalFlag);
    Rprintf("ucReqDataTxFlag=%d, usGprsTaskStep=%d, *pusServiceAddr=%04X\r\n", ucReqDataTxFlag, usGprsTaskStep, *pusServiceAddr);
#endif

    // Printing
    if (usPrintStep) {
        return;
    }

    // Communicating
#if 0 // sispp 20111008
    if ((ucReversalFlag || ucReqDataTxFlag) &&
            (usHiSpeedModemTaskStep > 0 || usEthernetTaskStep > 0 || usGprsTaskStep > 0)) {
#endif
        /*	if ((ucReversalFlag || ucReqDataTxFlag) && (usGprsTaskStep > 0)) {
                        return;
                }
         */
        if (ucReversalFlag && (usGprsTaskStep >= 70)) {
            return;
        }
        // ucReqDataReadyFlag ???
        if (ucReqDataTxFlag && (giTransactionType == TRXN_BANK_EFTTRAN) && (usGprsTaskStep >= 200)) {
            // SaveTxLog���� transaction type�� ������ ���ϴ°� ???
            if (st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY) {
                return;
            }
            ModemClose();
        }

        switch (*pusServiceAddr) {
            case 0x2115: // Current Merchant Total - Select Reprint or Exit
            case 0x2125: // Previous Merchant Total - Select Reprint or Exit
            case 0x2135: // Clear Merchant Total - Select Reprint or Exit
            case 0x5119: // Not Approved Buy - Select Reprint or Exit
            case 0x520B: // Balance Inquiry - Select Reprint or Exit
            case 0x540B: // SIM Charge(Preliminary Transaction) - Select Reprint or Exit
                sSelectedMenuItemNo = BTKEY_2;
                sVirtualKey = BTKEY_ENTER;
                return;
        }

        LCD_CursorOff();
        RS232Close();

        switch (usMainStatus) {
            case MSS_INITIAL: // Initial Status
                if (*pusServiceAddr != 0x0000) {
                    SetInitialStatus();
                }
                break;

            case MSS_SPECIAL_FUNC: // Special Functions
                // Select Setup Terminal Menu - Select Setup Terminal menu item
                // POS Information menu - Select POS Information menu item
                // Initialize - Select Initialize menu item
                // Change Maintenance's Password - Input New Maintenance's Password
                // Change Maintenance's Password - Retype New Maintenance's Password
                // Special Functions - Select Hardware Test menu item
                if (*pusServiceAddr == 0x1100 || *pusServiceAddr == 0x1200 ||
                        *pusServiceAddr == 0x1300 ||
                        *pusServiceAddr == 0x1400 || *pusServiceAddr == 0x1401 ||
                        *pusServiceAddr == 0x1500) {
                    ResetTrxnTelNo();
                    ResetEODTelNo();
                    ResetBlackListTelNo();
                    ResetTMSTelNo();
                    ResetHelpDeskTelNo();

                    WritePOSSetupInfo();

                    // "  Maintenance   ", "1.Setup Terminal", "2.POS Info.     ", "3.Initialize    "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SPECIAL, M4MaintenanceMenu_01, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 5, (char *) LCD_MSG_TBL1[ucLangFlag][M1MaintenanceMenu_02]);
                    pusServiceAddr++;
                }// Setup Modem Memu - Setup Modem
                    // Set Parameters Menu - Select Set Parameters menu item
                    // Setup Help Desk Telephone No - Input Help Desk Telephone No
                    // POS Serial Number - Display POS Serial Number
                    // POS Serial Number - Input POS Serial Number by Key-in
                    // POS Serial Number - Input POS Serial Number by Key-in or Barcode Reader
                    // POS Serial Number - Confirm POS Serial Number
                else if (*pusServiceAddr == 0x1160 || *pusServiceAddr == 0x1180 || *pusServiceAddr == 0x11E0 ||
                        (*pusServiceAddr >= 0x11D0 && *pusServiceAddr <= 0x11D3)) {
                    // " Setup Terminal ", "1.Setup Modem   ", "2.Set Parameters", "3.Download Param"
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_TERMINAL, M4SetupTrmMenu_00001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 5, (char *) LCD_MSG_TBL1[ucLangFlag][M1SetupTrmMenu_00002]);
                }// Setup GSM/GPRS Parameters
                else if (*pusServiceAddr >= 0x1161 && *pusServiceAddr <= 0x116F) {
                    // "      GSM       ", "1.Set Parameters", "2.Set Server    ", "3.Set TMS Server"
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_GSM, M4GSMMenu_0000000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1GSMMenu_0000000002]);
                }// Set Parameters - Input Terminal ID
                    // Set Parameters - Input Merchant ID
                    // Set Parameters - Input Store Name
                else if ((*pusServiceAddr >= 0x1181 && *pusServiceAddr <= 0x1183)) {
                    // "Set Parameters  ", "1.Terminal ID   ", "2.Store Name    ", "3.Sequence No   "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_SET_PARAM, M4SetParameterMenu_1, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1SetParamMenu_00002]);
                }// Download Parameters
                else if ((*pusServiceAddr > 0x11E0 && *pusServiceAddr <= 0x11E9)) {
                    if (giTransactionType == TRXN_DOWNLOAD_FUNCLIST) {
                        // " Function List  ", "1.Tams          ", "2.VoucherVault  ", "3.Banking       "
                        LCDDisplay4Lines(M4DownFuncList_00001, LCD_LINE1, ucLangFlag);
                        pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][6];
                        SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownFuncList_00002]);
                    } else if (giTransactionType == TRXN_DOWNLOAD_MASTERKEY || giTransactionType == TRXN_DOWNLOAD_SESSIONKEY) {
                        // "  Key Download  ", "1.Master Key    ", "2.Session Key   ", "                "
                        LCDDisplay4Lines(M4DownTrxnKeys_00001, LCD_LINE1, ucLangFlag);
                        pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][7];
                        SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownTrxnKeys_00002]);
                    } else if (giTransactionType == TRXN_DOWNLOAD_PARAM || giTransactionType == TRXN_DOWNLOAD_EFTPARAMS || giTransactionType == TRXN_DOWNLOAD_BINTABLE) {
                        // " EFT Parameters ", "1.Params        ", "2.EFT Params    ", "3.BIN Tables    "
                        LCDDisplay4Lines(M4DownEftParams_0001, LCD_LINE1, ucLangFlag);
                        pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][8];
                        SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownEftParams_0002]);
                    } else if (giTransactionType == TRXN_DOWNLOAD_EMVAPP || giTransactionType == TRXN_DOWNLOAD_EMVCAPK || giTransactionType == TRXN_DOWNLOAD_EMVREVOKECAPK) {
                        // " EMV Parameters ", "1.EMV APPs      ", "2.EMV CAPKs     ", "3.Revoke CAPKs  "
                        LCDDisplay4Lines(M4DownEmvParams_0001, LCD_LINE1, ucLangFlag);
                        pusServiceAddr = (unsigned short *) &tbl_MainService[MST_SETUP_DOWNLOAD_PARAMETERS][9];
                        SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownEmvParams_0002]);
                    } else {
                        // "Download Params ", "1.App Lists     ", "2.Function Lists", "3.Key Download  "
                        MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_DOWNLOAD_PARAMETERS, M4DownloadParam_0001, LCD_LINE1, ucLangFlag);
                        SetMenuScrollUpDownInfo(1, 1, 1, 6, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadParam_0002]);
                    }
                    giTransactionType = TRXN_NULL;
                }// View Information
                    // Print Information
                else if (*pusServiceAddr >= 0x1201 && *pusServiceAddr <= 0x1208) {
                    // "POS Information ", "1.View Info.    ", "2.Print Info.   ", "                "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_POS_INFO, M4POSInfoMenu_000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1POSInfoMenu_000002]);
                }// Reset Parameters
                    // Reset Merchant
                    // Erase Transaction Logs
                else if (*pusServiceAddr >= 0x1301 && *pusServiceAddr <= 0x1303) {
                    LCD_CONT(st_POSSetupInfo.ucLCDContrast);
                    if (st_POSSetupInfo.ucBeep) {
                        Beep_KeySoundEnable();
                    } else {
                        Beep_KeySoundDisable();
                    }

                    // "Initialize      ", "1.Reset Param.  ", "2.Reset Merchant", "3.Erase POS Logs"
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_INITIALIZE, M4InitializeMenu_001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1InitializeMenu_002]);
                }// Printer Test - Build Print Data for POS Information Reports
                    // MSR Test
                    // Modem Test
                    // IC Card Test
                    // Key Test
                    // LCD Test
                    // RS232 Test
                    // RTC Test
                else if (*pusServiceAddr >= 0x1510 && *pusServiceAddr <= 0x1580) {
                    SetInitialStatus();
                    MSRDisable();

                    // "Hardware Test   ", "1.Printer Test  ", "2.MSR Test      ", "3.Modem Test    "
                    MainStatusSetting(MSS_SPECIAL_FUNC, MST_SETUP_HW_TEST, M4HWTestMenu_0000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 8, (char *) LCD_MSG_TBL1[ucLangFlag][M1HWTestMenu_0000002]);
                } else {
                    ResetTrxnTelNo();
                    ResetEODTelNo();
                    ResetBlackListTelNo();
                    ResetTMSTelNo();
                    ResetHelpDeskTelNo();

                    WritePOSSetupInfo();

                    SetInitialStatus();
                }
                break;

            case MSS_F1_FUNC: // F1 Functions
            case MSS_F1_REVERSAL_TRANS:
                // Merchant Operations Menu - Select Merchant Operations menu item
                // POS Operations Menu - Select POS Operations menu item
                // Store Operations Menu - Select Store Operations menu item
                // EOD Operations Menu - Select EOD Operations menu item
                // Change Merchant's Password - Input New Merchant's Password
                // Change Merchant's Password - Retype New Merchant's Password
                // Transfer Log for Merchant
                // Set Telephone Menu - Select Set Telephone menu item
                // Setup Ethernet Server - Input Server IP Address 1
                // Setup Ethernet Server - Input Server Port Number 1
                // Setup GSM Server - Input GSM City Access Code
                // Setup GSM Server - Input GSM Telephone No
                // Remote Download - Select TMS menu for GSM
                if (*pusServiceAddr == 0x2100 || *pusServiceAddr == 0x2110 || *pusServiceAddr == 0x2120 ||
                        *pusServiceAddr == 0x2600 || *pusServiceAddr == 0x2601 ||
                        *pusServiceAddr == 0x290A) {
                    // "   Supervisor   ", "1.Reversal      ", "2.Balance       ", "3.End-of-Day    "
                    LCDDisplay4Lines(M4Supervisor_0000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 5, (char *) LCD_MSG_TBL1[ucLangFlag][M1Supervisor_0000002]);
                    pusServiceAddr = (unsigned short *) &tbl_MainService[MST_F1_FUNC][1];
                }// Input TMS Server
                    // Remote Download - Select Remote Download for Dial-up
                else if (*pusServiceAddr >= 0x290B && *pusServiceAddr <= 0x290F) {
                    // "Remote Download ", "1.TMS Server    ", "2.TMS Download  ", "                "
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_REMOTEDOWNLOAD, M4TMSMenu_0000000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 2, (char *) LCD_MSG_TBL1[ucLangFlag][M1TMSMenu_0000000011]);
                    pusServiceAddr++;
                }// End Of Day - Today
                    // End Of Day - Reprint
                    // End Of Day - Past Day
                else if (*pusServiceAddr >= 0x2140 && *pusServiceAddr <= 0x2145) {
                    // "   End of Day   ", "1.Today         ", "2.Print Last Txn", "                "
                    MainStatusSetting(MSS_F1_FUNC, MST_F1_ENDOFDAY, M4EndOfDay_000000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1EndOfDay_000000002]);
                } else {
                    ResetTrxnTelNo();
                    ResetTMSTelNo();

                    WritePOSSetupInfo();

                    SetInitialStatus();
                }
                break;

            case MSS_F3_FUNC: // F3 Functions
                // Set CallHome
                // Set Comm Timeout
                // Set Date - Input Date
                // Set Time - Input Time
                // Set Contrast - Set LCD Contrast
                // Set Beep Sound - Select Beep Sound ON/OFF
                if (*pusServiceAddr == 0x4100 ||
                        *pusServiceAddr == 0x4200 || *pusServiceAddr == 0x4300 ||
                        *pusServiceAddr == 0x4400 || *pusServiceAddr == 0x4500 ||
                        *pusServiceAddr == 0x4600) {
                    LCD_CONT(st_POSSetupInfo.ucLCDContrast);
                    if (st_POSSetupInfo.ucBeep) {
                        Beep_KeySoundEnable();
                    } else {
                        Beep_KeySoundDisable();
                    }

                    // "Setup POS Status", "1.Set CallHome  ", "2.Set Timeout   ", "3.Set Date      "
                    MainStatusSetting(MSS_F3_FUNC, MST_F3_FUNC, M4SVSetupPOS_0000001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 6, (char *) LCD_MSG_TBL1[ucLangFlag][M1SVSetupPOS_0000002]);
                } else {
                    WritePOSSetupInfo();

                    SetInitialStatus();
                }
                break;

            case MSS_REVERSAL: // Reversal
                // Print Reversal Receipt - "Insert paper and Press ENTER key"
                if (*pusServiceAddr == 0x9000) {
                    pstfTempTrxnLog = pstfSavingTrxnLog;
                    // Save Reversal TransactionLog
                    SaveReversalTransactionLog(pstfTempTrxnLog);
                    // Perform Reversal Transaction
                    PerformReversalTransaction();

                    ucReversalRetryCnt = 0;
                    ucReversalRetryTimePerCnt = 0;
                    break;
                }// Reversal Mode - Select Reversal Mode menu item
                else if (*pusServiceAddr == 0x9100) {
                    break;
                }// Set Telephone Menu - Select Set Telephone menu item
                    // Setup Ethernet Server - Input Server IP Address 1
                    // Setup Ethernet Server - Input Server Port Number 1
                    // Setup GSM Server - Input GSM City Access Code
                    // Setup GSM Server - Input GSM Telephone No
                else if (*pusServiceAddr == 0x9301 ||
                        *pusServiceAddr == 0x9309 || *pusServiceAddr == 0x930A ||
                        *pusServiceAddr == 0x930B || *pusServiceAddr == 0x930C) {
                    ResetTrxnTelNo();

                    WritePOSSetupInfo();

                    // Go to Reversal Mode
                    GotoReversalMode();
                }// Set Telephone
                else if (*pusServiceAddr >= 0x9302 && *pusServiceAddr <= 0x9308) {
                    // "Set Telephone   ", "1.Access Code   ", "2.Telephone No  ", "3.Pulse Dial    "
                    MainStatusSetting(MSS_REVERSAL, MST_REVERSAL_SETTELEPHONE, M4SetTelephone_00001, LCD_LINE1, ucLangFlag);
                    SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1SetTelephone_00002]);
                    pusServiceAddr++;
                }// Print Unsuccessful Reversal Receipt - "Insert paper and Press ENTER key"
                else if (*pusServiceAddr == 0x9400) {
                    break;
                }// Print Unsuccessful Reversal Receipt
                else if (*pusServiceAddr == 0x9401) {
                    SetInitialStatus();
                } else {
                    // Reversal
                    if (ucReversalFlag) {
                        ModemClose();

                        // Go to Reversal Mode
                        GotoReversalMode();
                    } else {
                        SetInitialStatus();
                    }
                }
                break;

            default:
                SetInitialStatus();
                break;
        }
    }

    extern int CheckSmartCardSlot();

    void SetInitialStatus(void) {
        int i;

#ifdef USER_DEBUG
        Rprintf("\r\nSetInitialStatus\r\n");
#endif
        LCD_CursorOff();
        RS232Close();
        ModemClose();

        memset(CardNo2, 0x00, sizeof (CardNo2));

        if (CheckSmartCardSlot() == 1) {
            // "                ", "Eject your card ", "                ", "                "
            LCDDisplay4Lines(M4EjectYourCard_0001, -1, ucLangFlag);
            while (1) {
                i = CheckSmartCardSlot();
                if (i == 0) {
                    break;
                } else if (i == -1) {
                    Beep_EventSound(ERROR_TONE);
                    TIMER_WaitKeyPress1MS(1000);
                }
            }
        }


#if 0 // sispp 20111008
        ucSmartCardTrxnFlag = 0;
        ucSmartCardOnlineTrxnFlag = 1;
#ifdef USER_DEBUG
        Rprintf("sSmartCardTaskStep = %d\r\n", sSmartCardTaskStep);
#endif
        if (ucSmartCardIFMErrorFlag == 0) {
            if (sSmartCardTaskStep < 0 || sSmartCardTaskStep > 2) {
                gsc_Power(0);
                // "Eject your card ", "                ", "                ", "                "
                LCDDisplay4Lines(M4EjectYourCard_0001, -1, ucLangFlag);
                SCARD_EjectSmartCard(10);
                TL_Close();
                usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();
            }
            sSmartCardTaskStep = 1;
        } else {
            sSmartCardTaskStep = -1;
        }
#endif // sispp 20111008

        LoadFlashPOSUtilInfo();
        GetNextTrxnParameter(&RealTime, 0);

        // Program (and parameter) downloading is completed
        if (LoadTMSDownloadSectorNo()) {
            UpgradeApplication();
        }

        // Parameter downloading is completed
        if (tTMSDownloadInfo.sParamWrittenSectorNo >= (tTMSDownloadInfo.sParamTotalSectorNo - 1) && tTMSDownloadInfo.lParamTotalDataSize != 0L) {
            UpgradePOSParameter(0);
        }

        InitializeGlobalVariables();

        ucPINInputAndReconnectFlag = 0;

        giTransactionType = TRXN_NULL;
        memset(sz13Amount, 0x00, sizeof (sz13Amount));
        sz13Amount[0] = '0';

        memset(sz19BillID, 0x00, sizeof (sz19BillID));
        memset(sz19PaymentID, 0x00, sizeof (sz19PaymentID));
        memset(sz12PhoneNo, 0x00, sizeof (sz12PhoneNo));

        usPrintStep = 0;
        ucPrintReceiptNo = 0;
        InitializePrinterParameter();

        if (ucAutoTMSDownloadDateFlag) {
            if (ucAutoTMSDownloadFirstFlag) {
                ucAutoTMSDownloadFirstFlag = 0;
            }
            lTMSAutoDownloadTried1SECTimer = TIMER_Get1SECTimer();
        }

        ucTMSDownloadFlag = 0;
        iTMS_ProcessStep = 0;

        lCallHome1SECTimer = TIMER_Get1SECTimer();

        MSR_ClearAllCardDataBuffer();
        ClearAllMSRDataBuf();

        if (ucGprsModuleOkFlag == 0 && ucGprsPowerOffFlag == 1) {
            GprsModuleInitialize();
        }
        // "                ", "                ", "                ", "                "
        MainStatusSetting(MSS_INITIAL, MST_INITIAL, M4_____________Space, -1, ucLangFlag);

        // Display Initial Image
        DisplayInitialImage();

        if (st_POSSetupInfo.ucComDevice != GSM_MODEM) {
            // "Card Sys. ",
            LCD_DisplayString(0, 6, 10, (char *) LCD_INITIAL_MSG_TBL[ucLangFlag], ucLangFlag);
            ICON_DISPLAY(0); // Antena all off
        }

        RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
        ucDateTimeRefreshFlag = 1;
        DisplayDateTime(&RealTime); // Display date and time on LCD

        // Display Program Version
        LCD_DisplayString(3, 11, 1, "V", ucLangFlag);
        LCD_DisplayString(3, 12, strlen(sz5LCDDisplayProgramVersion), sz5LCDDisplayProgramVersion, ucLangFlag);

        MSREnable();

        isDetectCard = 0x00;
        if (gbEmvScTaskStep > 0) {
            gbEmvScTaskStep = 127; //call appEmvTaskEnd
        } else {
            gbEmvScTaskStep = 0;
        }
        //     if(!gbReversalFlag)
        memset(SelectedAID, 0x00, sizeof (SelectedAID));

        usAutoInitial10MSTimer = TIMER_Get10MSTimer();

#ifdef AUTO_MODEM_TEST
        usModemAutoTest10MSTimer = TIMER_Get10MSTimer();
#endif

#ifdef USER_DEBUG
        OpenDebugPort(COM0, BPS115200, NONE8BIT, STOP1BIT, 0);
#else
        DisableDebugOutput();
#endif

    }

    void InitializeGlobalVariables(void) {
        sVirtualKey = BTKEY_NULL;
        sTempKey = BTKEY_NULL;
        ucKeyCnt = 0;

        memset((char *) &st_TrxnReqData, 0x00, sizeof (st_TrxnReqData));
        memset((char *) &st_TrxnRespData, 0x00, sizeof (st_TrxnRespData));
        memset((char *) &ucTrxnTxBuf, 0x00, sizeof (ucTrxnTxBuf));
        memset((char *) &ucTrxnRxBuf, 0x00, sizeof (ucTrxnRxBuf));
        memset((char *) &ucTxBuf, 0x00, sizeof (ucTxBuf));
        memset((char *) &ucRxBuf, 0x00, sizeof (ucRxBuf));
        memset((char *) &st_ErrRespData, 0x00, sizeof (_st_ErrRespData_));

        ucModemTestFlag = 0;

        usTransType = TRXN_NULL;
        usMsgType = 0x0000;
        ulPCode = 0x000000L;
        usResponseCode = 0x0000;
        dBuyAmount = 0.0;
        dRefundAmout = 0.0;
        dDebitBuyAmount = 0.0;
        dCreditBuyAmout = 0.0;

#if 0 // sispp 20111008
        ucHiSpeedModemConnectCnt = 0;
        ucEthernetConnectCnt = 0;
#endif
        ucGprsConnectCnt = 0;

        ucReqDataTxFlag = 0;
        ucReqDataReadyFlag = 0;
#if 0 // sispp 20111008
        ucHiSpeedModemDataSendFlag = 0;
#endif
        iTxSize = 0;
        iRxSize = 0;
        iRxCnt = 0;

        memset(c65CommaAndDotString, 0x00, sizeof (c65CommaAndDotString));
        memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
        memset(c65TempBuf, 0x00, sizeof (c65TempBuf));

        memset(sz13CardPIN, 0x00, sizeof (sz13CardPIN));
        memset(sz17EncypritedCardPIN, 0x00, sizeof (sz17EncypritedCardPIN));

        memset(F048aL3_sz1003BillPaymentData1, 0x00, sizeof (F048aL3_sz1003BillPaymentData1));
        memset(F121aL3_sz1003BillPaymentData2, 0x00, sizeof (F121aL3_sz1003BillPaymentData2));
        memset(sz29OrganizationAccount, 0x00, sizeof (sz29OrganizationAccount));

        memset(st_TrxnLogDB, 0x00, sizeof (st_TrxnLogDB));

        // Clear Print Pre-printing Area Flag for printing of pre-printing area
        ucPrintPrePrintingAreaFlag = 0;
    }

    void ClearTempKeyBufAndStringCopy(char *str) {
        memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
        strcpy(c65TempKeyBuf, str);
    }

    void MainStatusSetting(unsigned short Status, short ServiceTableNo, short DisplayMsgNo, char HighlightLine, char lang) {
        usMainStatus = Status;
        LCDDisplay4Lines(DisplayMsgNo, HighlightLine, lang);
        pusServiceAddr = (unsigned short *) &tbl_MainService[ServiceTableNo][0];
#ifdef USER_DEBUG
        Rprintf("MainStatusSetting = 0x%04X\r\n", *pusServiceAddr);
#endif
    }

    void ErrorDisplayAndGoInitialStatus(short DisplayMsgNo, char HighlightLine, char lang) {
        ucLCDBacklightOnFlag = 1;
        BACK_ONOFF(ON);
        usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();

        LCDDisplay4Lines(DisplayMsgNo, HighlightLine, lang);
        Beep_EventSound(ERROR_TONE);
        pusServiceAddr = (unsigned short *) &tbl_MainService[MST_INITIAL][1];
        TIMER_WaitKeyPress1MS(5000);
        SetInitialStatus();
    }

    void ErrorDisplayAndGoErrorStatus(short DisplayMsgNo, char HighlightLine, char lang) {
        ucLCDBacklightOnFlag = 1;
        BACK_ONOFF(ON);
        usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();

        LCDDisplay4Lines(DisplayMsgNo, HighlightLine, lang);
        Beep_EventSound(ERROR_TONE);
        pusServiceAddr = (unsigned short *) &tbl_MainService[MST_INITIAL][1];
    }

    void DisplayTrxnTelNo(void) {
        short i, j, start;
        char temp[17];

        ResetTrxnTelNo();

        if (sTempKey < 3) {
            j = sTempKey;
            start = 1;
        } else {
            j = 3;
            start = sTempKey - 2;
        }

        for (i = 0; i < j; i++) {
            LCD_ClearLine(i + 1);
            memset(temp, 0x00, sizeof (temp));
            if (strlen(st_POSSetupInfo.sz17TrxnTelNo[start + i - 1]) != 0) {
                sprintf(temp, "%d)%s", start + i, st_POSSetupInfo.sz17TrxnTelNo[start + i - 1]);
            } else {
                sprintf(temp, "%d)              ", start + i);
            }
            LCD_DisplayString(i + 1, 0, strlen(temp), temp, ucLangFlag);
        }

        ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz17TrxnTelNo[sTempKey - 1]);
        ucKeyCnt = 0;
        cYPos = j;
        cXPos = 2;
        cMaxInputCnt = 14;
        if (strlen(c65TempKeyBuf) == 0) {
            LCD_CursorOn(j, cXPos);
        }
    }

    void ResetTrxnTelNo(void) {
        short i;

        for (i = 0; i < 8; i++) {
            if (strlen(st_POSSetupInfo.sz17TrxnTelNo[i]) == 0) {
                break;
            }
        }
        for (; i < 8; i++) {
            memset(st_POSSetupInfo.sz17TrxnTelNo[i], 0x00, sizeof (st_POSSetupInfo.sz17TrxnTelNo[i]));
        }
    }

    void DisplayEODTelNo(void) {
        short i, j, start;
        char temp[17];

        ResetEODTelNo();

        j = sTempKey;
        start = 1;
        for (i = 0; i < j; i++) {
            LCD_ClearLine(i + 1);
            memset(temp, 0x00, sizeof (temp));
            if (strlen(st_POSSetupInfo.sz17EODTelNo[start + i - 1]) != 0) {
                sprintf(temp, "%d)%s", start + i, st_POSSetupInfo.sz17EODTelNo[start + i - 1]);
            } else {
                sprintf(temp, "%d)              ", start + i);
            }
            LCD_DisplayString(i + 1, 0, strlen(temp), temp, ucLangFlag);
        }

        ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz17EODTelNo[sTempKey - 1]);
        ucKeyCnt = 0;
        cYPos = j;
        cXPos = 2;
        cMaxInputCnt = 14;
        if (strlen(c65TempKeyBuf) == 0) {
            LCD_CursorOn(j, cXPos);
        }
    }

    void ResetEODTelNo(void) {
        short i;

        for (i = 0; i < 3; i++) {
            if (strlen(st_POSSetupInfo.sz17EODTelNo[i]) == 0) {
                break;
            }
        }
        for (; i < 3; i++) {
            memset(st_POSSetupInfo.sz17EODTelNo[i], 0x00, sizeof (st_POSSetupInfo.sz17EODTelNo[i]));
        }
    }

    void DisplayBlackListTelNo(void) {
        short i, j, start;
        char temp[17];

        ResetBlackListTelNo();

        j = sTempKey;
        start = 1;
        for (i = 0; i < j; i++) {
            LCD_ClearLine(i + 1);
            memset(temp, 0x00, sizeof (temp));
            if (strlen(st_POSSetupInfo.sz17BListTelNo[start + i - 1]) != 0) {
                sprintf(temp, "%d)%s", start + i, st_POSSetupInfo.sz17BListTelNo[start + i - 1]);
            } else {
                sprintf(temp, "%d)              ", start + i);
            }
            LCD_DisplayString(i + 1, 0, strlen(temp), temp, ucLangFlag);
        }

        ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz17BListTelNo[sTempKey - 1]);
        ucKeyCnt = 0;
        cYPos = j;
        cXPos = 2;
        cMaxInputCnt = 14;
        if (strlen(c65TempKeyBuf) == 0) {
            LCD_CursorOn(j, cXPos);
        }
    }

    void ResetBlackListTelNo(void) {
        short i;

        for (i = 0; i < 3; i++) {
            if (strlen(st_POSSetupInfo.sz17BListTelNo[i]) == 0) {
                break;
            }
        }
        for (; i < 3; i++) {
            memset(st_POSSetupInfo.sz17BListTelNo[i], 0x00, sizeof (st_POSSetupInfo.sz17BListTelNo[i]));
        }
    }

    void DisplayTMSTelNo(void) {
        short i, j, start;
        char temp[17];

        ResetTMSTelNo();

        if (sTempKey < 3) {
            j = sTempKey;
            start = 1;
        } else {
            j = 3;
            start = sTempKey - 2;
        }

        for (i = 0; i < j; i++) {
            LCD_ClearLine(i + 1);
            memset(temp, 0x00, sizeof (temp));
            if (strlen(st_POSSetupInfo.sz17TMSTelNo[start + i - 1]) != 0) {
                sprintf(temp, "%d)%s", start + i, st_POSSetupInfo.sz17TMSTelNo[start + i - 1]);
            } else {
                sprintf(temp, "%d)              ", start + i);
            }
            LCD_DisplayString(i + 1, 0, strlen(temp), temp, ucLangFlag);
        }

        ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz17TMSTelNo[sTempKey - 1]);
        ucKeyCnt = 0;
        cYPos = j;
        cXPos = 2;
        cMaxInputCnt = 14;
        if (strlen(c65TempKeyBuf) == 0) {
            LCD_CursorOn(j, cXPos);
        }
    }

    void ResetTMSTelNo(void) {
        short i;

        for (i = 0; i < 8; i++) {
            if (strlen(st_POSSetupInfo.sz17TMSTelNo[i]) == 0) {
                break;
            }
        }
        for (; i < 8; i++) {
            memset(st_POSSetupInfo.sz17TMSTelNo[i], 0x00, sizeof (st_POSSetupInfo.sz17TMSTelNo[i]));
        }
    }

    void DisplayHelpDeskTelNo(void) {
        short i, j, start;
        char temp[17];

        ResetHelpDeskTelNo();

        if (sTempKey < 3) {
            j = sTempKey;
            start = 1;
        } else {
            j = 3;
            start = sTempKey - 2;
        }

        for (i = 0; i < j; i++) {
            LCD_ClearLine(i + 1);
            memset(temp, 0x00, sizeof (temp));
            if (strlen(st_POSSetupInfo.sz17HelpDeskTelNo[start + i - 1]) != 0) {
                sprintf(temp, "%d)%s", start + i, st_POSSetupInfo.sz17HelpDeskTelNo[start + i - 1]);
            } else {
                sprintf(temp, "%d)              ", start + i);
            }
            LCD_DisplayString(i + 1, 0, strlen(temp), temp, ucLangFlag);
        }

        ClearTempKeyBufAndStringCopy(st_POSSetupInfo.sz17HelpDeskTelNo[sTempKey - 1]);
        ucKeyCnt = 0;
        cYPos = j;
        cXPos = 2;
        cMaxInputCnt = 14;
        if (strlen(c65TempKeyBuf) == 0) {
            LCD_CursorOn(j, cXPos);
        }
    }

    void ResetHelpDeskTelNo(void) {
        short i;

        for (i = 0; i < 4; i++) {
            if (strlen(st_POSSetupInfo.sz17HelpDeskTelNo[i]) == 0) {
                break;
            }
        }
        for (; i < 4; i++) {
            memset(st_POSSetupInfo.sz17HelpDeskTelNo[i], 0x00, sizeof (st_POSSetupInfo.sz17HelpDeskTelNo[i]));
        }
    }

#ifdef USER_DEBUG

    void DisplayLCDMsgOrPrinterMsgInDebugMode(void) {
        int i, view_lcd_mode, total_msg_cnt, view_msg_no, key, len;
        char justify_mode;
        char temp[65];
        char disp_msg[2][17];
        char menu_msg[9][17];

        while (1) {
            memset(menu_msg, 0x00, sizeof (menu_msg));
            strcpy(menu_msg[0], "1.LCD Message   ");
            strcpy(menu_msg[1], "2.Print Message ");

            LCD_ClearScreen();
            LCD_DisplayLine(0, LEFT_JUSTIFIED, "Select View Msg ", ucLangFlag);
            LCD_DisplayLine(1, LEFT_JUSTIFIED, menu_msg[0], ucLangFlag);
            LCD_DisplayLine(2, LEFT_JUSTIFIED, menu_msg[1], ucLangFlag);
            LCD_HighlightLineOn(1);
            SetMenuScrollUpDownInfo(1, 1, 1, 2, menu_msg[0]);

            // Select LCD Message or Printer Message
            while (1) {
                key = KEYSCAN() & 0xFF;

                if (sVirtualKey != BTKEY_NULL) {
                    key = sVirtualKey;
                    sVirtualKey = BTKEY_NULL;
                }

                if (key == BTKEY_NULL) {
                    continue;
                }

                if (key == BTKEY_CANCEL) {
                    return; // Escape
                } else if (key == BTKEY_ENTER) {
                    break;
                } else {
                    MenuScrollUpDown(sStartDisplayMenuLine, &sSelectedMenuItemNo, &sSelectedMenuItemLine, sTotalMenuItemNo, psz17FirstMenuItemMsgAddr, key, ucLangFlag);
                    if (key >= BTKEY_1 && key <= sTotalMenuItemNo) {
                        sVirtualKey = BTKEY_ENTER;
                    }
                }
            }

            LCD_ClearScreen();
            if (sSelectedMenuItemNo == BTKEY_1) {
                view_lcd_mode = 1;
                total_msg_cnt = M1_____________Space + 1;
                LCD_DisplayLine(0, LEFT_JUSTIFIED, "Start No for LCD", ucLangFlag);
            } else {
                view_lcd_mode = 0;
                total_msg_cnt = P1SoftwareVersion_01 + 1;
                LCD_DisplayLine(0, LEFT_JUSTIFIED, "Start No for PRN", ucLangFlag);
            }
            sprintf(temp, "Max = %d", total_msg_cnt);
            LCD_DisplayLine(3, LEFT_JUSTIFIED, temp, ucLangFlag);
            LCD_HighlightLineOn(0);

            memset(c65TempKeyBuf, 0x00, sizeof (c65TempKeyBuf));
            ucKeyCnt = 0;
            cYPos = 1;
            cXPos = 0;
            cMaxInputCnt = 4;
            LCD_CursorOn(cYPos, cXPos);

            // Input View Start Number of Message
            while (1) {
                key = KEYSCAN() & 0xFF;

                if (sVirtualKey != BTKEY_NULL) {
                    key = sVirtualKey;
                    sVirtualKey = BTKEY_NULL;
                }

                if (key == BTKEY_NULL) {
                    continue;
                }

                if (key == BTKEY_CANCEL) {
                    break;
                } else if (key == BTKEY_ENTER) {
                    if (strlen(c65TempKeyBuf) == 0) {
                        Beep_EventSound(ERROR_TONE);
                        continue;
                    }

                    view_msg_no = atoi(c65TempKeyBuf);
                    if (view_msg_no <= 0 || view_msg_no > total_msg_cnt) {
                        Beep_EventSound(ERROR_TONE);
                        continue;
                    }
                    break;
                } else {
                    KEY_InputNoString(cYPos, cXPos, cMaxInputCnt, key, c65TempKeyBuf, ucLangFlag);
                }
            }
            LCD_CursorOff();

            if (key == BTKEY_ENTER) {
                LCD_ClearScreen();
                if (view_lcd_mode) {
                    LCD_DisplayLine(0, LEFT_JUSTIFIED, "View LCD Message", ucLangFlag);
                } else {
                    LCD_DisplayLine(0, LEFT_JUSTIFIED, "View PRN Message", ucLangFlag);
                }
                LCD_HighlightLineOn(0);

                // View LCD or Printer Message
                while (1) {
                    sprintf(temp, "[ %d / %d ]", view_msg_no, total_msg_cnt);
                    LCD_DisplayLine(1, CENTER_JUSTIFIED, temp, ucLangFlag);

                    LCD_ClearLine(2);
                    LCD_ClearLine(3);

                    if (view_lcd_mode) {
                        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][view_msg_no - 1], ucLangFlag);
                    } else {
                        if (ucLangFlag) {
                            justify_mode = RIGHT_JUSTIFIED;
                        } else {
                            justify_mode = LEFT_JUSTIFIED;
                        }

                        memset(temp, 0x00, sizeof (temp));
                        strcpy(temp, PRT_MSG_TBL1[ucLangFlag][view_msg_no - 1]);
                        len = strlen(temp);
                        if (len <= 16) {
                            LCD_DisplayLine(2, justify_mode, temp, ucLangFlag);
                        } else {
                            memset(disp_msg, 0x00, sizeof (disp_msg));
                            if (ucLangFlag == 0) {
                                memcpy(disp_msg[0], temp, 16);
                                strcpy(disp_msg[1], &temp[16]);
                            } else {
                                strcpy(disp_msg[0], &temp[len - 16]);
                                memcpy(disp_msg[1], temp, len - 16);
                            }
                            LCD_DisplayLine(2, justify_mode, disp_msg[0], ucLangFlag);
                            LCD_DisplayLine(3, justify_mode, disp_msg[1], ucLangFlag);
                        }
                    }

                    while (1) {
                        key = KEYSCAN() & 0xFF;

                        if (sVirtualKey != BTKEY_NULL) {
                            key = sVirtualKey;
                            sVirtualKey = BTKEY_NULL;
                        }

                        if (key == BTKEY_NULL) {
                            continue;
                        }

                        if (key == BTKEY_CANCEL) {
                            break;
                        } else if (key == BTKEY_ENTER || key == BTKEY_SHARP) { // Increase View Number of Message
                            view_msg_no += 1;
                            if (view_msg_no > total_msg_cnt) {
                                view_msg_no = 1;
                            }
                            break;
                        } else if (key == BTKEY_CLEAR || key == BTKEY_ASTERISK) { // Decrease View Number of Message
                            view_msg_no -= 1;
                            if (view_msg_no < 1) {
                                view_msg_no = total_msg_cnt;
                            }
                            break;
                        }
                    }

                    if (key == BTKEY_CANCEL) {
                        break;
                    }
                }
            }
        }
    }
#endif

    /* */
