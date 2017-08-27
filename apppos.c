
#include "system.h"
#include "extern.h"


#ifdef USER_DEBUG
const char TrxnName_tbl[][64] = {
    "Preliminary of Bill Payment",

    "Purchase(buy) - Debit",
    "Purchase(buy) - Credit",
    "Purchase(buy) Cancel - Debit",
    "Balance - Debit",
    "Balance - Credit",
    "Bill Payment - Debit",
    "Bill Payment - Credit",

    "Reversal of Purchase(buy) - Debit",
    "Reversal of Purchase(buy) - Credit",

    "Open store",
    "Close store",
    "Load blacklist",
    "EOD process",
    "Current POS total",
    "Previous POS total",
    "Clear POS total",
    "POS balance",
    "Current store total",
    "Previous store total",
    "Clear store total",
    "Current Merchant total",
    "Previous Merchant total",
    "Clear Merchant total",
    "Print duplicate",
};
#endif

const unsigned short ResponseCode_tbl[] = {
    0x3030,
    0x3032,
    0x3033,
    0x3036,
    0x3132,
    0x3133,
    0x3134,
    0x3135,
    0x3136,
    0x3139,
    0x3234,
    0x3235,
    0x3239,
    0x3330,
    0x3333,
    0x3334,
    0x3430,
    0x3431,
    0x3433,
    0x3434,
    0x3438,
    0x3531,
    0x3535,
    0x3536,
    0x3537,
    0x3630,
    0x3631,
    0x3632,
    0x3634,
    0x3635,
    0x3636,
    0x3638,
    0x3730,
    0x3731,
    0x3735,
    0x3737,
    0x3738,
    0x3739,
    0x3830,
    0x3831,
    0x3833,
    0x3834,
    0x3835,
    0x3836,
    0x3837,
    0x3838,
    0x3839,
    0x3930,
    0x3931,
    0x3932,
    0x3933,
    0x3934,
    0x3936,
    0xFFFF
};

const unsigned char REPRINTER_COUNT_TO_LOG_COUNT_TBL[] = {
    0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF
};


_st_TrxnLog_ st_TrxnLog; // Transaction log buffer
_st_TrxnLog_ *pstfFirstTrxnLog; // Pointer to first transaction log address of flash ROM
_st_TrxnLog_ *pstfLastTrxnLog; // Pointer to last transaction log address of flash ROM
_st_TrxnLog_ *pstfSavingTrxnLog; // Pointer to saving transaction log address of flash ROM
_st_TrxnLog_ *pstfTempTrxnLog; // Pointer to temporary transaction log address of flash ROM
_st_TrxnReqData_ st_TrxnReqData; // Transaction request buffer
_st_TrxnReqData_ st_ReversalTrxnReqData; // Reversal transaction request buffer
_st_TrxnRespData_ st_TrxnRespData; // Transaction response buffer
_st_TrxnLogDB_ st_TrxnLogDB[MAX_TRANSACTION_LOG]; // Transaction log DB buffer
_st_ErrRespData_ st_ErrRespData; // Transaction(Parameter download) error response buffer

double dBuyAmount; // Buy amount
double dRefundAmout; // Refund amount
double dDebitBuyAmount; // Debit buy amount
double dCreditBuyAmout; // Credit buy amount
int iStartDBCtrlIndex; // Start DB control index
int iMaxDBCtrlIndex; // Maximum DB control index
unsigned long ulPCode; // Processing Code
unsigned long ulBackupPCode; // Back-up Processing Code
long lMinLogAddr; // Minimum transaction log address of flash ROM
long lMaxLogAddr; // Maximum transaction log address of flash ROM
unsigned short usMsgType; // Message type
unsigned short usBackupMsgType; // Back-up Message type
unsigned short usTransType; // Transaction type
unsigned short usBackupTransType; // Back-up Transaction type
unsigned short usTrxnLogIndex; // Transaction log index
unsigned short usTrxnTotalCount; // Total transaction log count
unsigned short usEodTrxnCount; // Eod Transaction log count
unsigned short usResponseCode; // Response code
unsigned char ucReversalFlag; // Reversal flag
unsigned char ucReversalRetryCnt; // Reversal retry count
unsigned char ucReversalRetryTimePerCnt; // Reversal retry time per a count
unsigned char ucBuyTrxnType; // Buy transaction type
unsigned char ucBlackListExistFlag; // Black list exist flag
unsigned char ucSIMChargeOperatorCode; // SIM charge operator code
unsigned char ucPINInputAndReconnectFlag; // PIN Input and Reconnect Flag
unsigned char ucMultiMerchantSelectedNo; // Multi-Merchant Selected Number
char sz9BackupTerminalID[9]; // Back-up Terminal ID
char sz9BackupMerchantID[16]; // Back-up Merchant ID
char sz13Amount[13]; // Transaction amount buffer
char sz13CardPIN[13]; // Transaction card PIN buffer
char sz17EncypritedCardPIN[17]; // Transaction encyprited card PIN buffer
char sz19BillID[19]; // Bill ID buffer
char sz19PaymentID[19]; // Payment ID buffer
char F048aL3_sz1003BillPaymentData1[1003]; // Bill Payment Data 1 (Bit 48) buffer
char F121aL3_sz1003BillPaymentData2[1003]; // Bill Payment Data 2 (Bit 121) buffer
char sz29OrganizationAccount[29]; // Organization account buffer
char c9ActiveTrxnMenuType[9]; // Active transaction menu type
char sz17ActiveTrxnMenuMsg[9][17]; // Active transaction menu message buffer
char sz12PhoneNo[12]; // Phone Number buffer


void GetNextTrxnParameter(_tDATE_TIME *dt, int mode);
void SaveTxTransactionLog(void);
void SaveRxTransactionLog(void);
void SavePrintTransactionLog(_st_TrxnLog_ *trxn_log, int second_prt);
void SaveReprintingCount(_st_TrxnLog_ *trxn_log);
void SaveReversalTransactionLog(_st_TrxnLog_ *trxn_log);
void GotoReversalMode(void);
void PrintReversalReceipt(unsigned short delay_time);
void PrintUnsuccessfulReversalReceipt(void);
void PerformReversalTransaction(void);
void RecoverReversalData(_st_TrxnLog_ *trxn_log);
void GetPOSBalanceData(void);
#ifdef USER_DEBUG
void DebugOutputTrxnLogData(_st_TrxnLog_ *trxn_log, int mode);
void DebugOutputTrxnLog(void);
void DebugOutputTrxnReqData(void);
void DebugOutputTrxnRespData(void);
#endif
#ifdef SAVE_TEST_TRXN_LOG
void SaveTestTrxnLogs(int log_cnt);
#endif


// Output Transaction Log data for debugging

void DebugOutputTrxnLogData(_st_TrxnLog_ *trxn_log, int mode) {
    if (mode & 0x01) {
        Rprintf("Address  Index Date     St MType PrCode Amount       Ref_No       Track2Data                               RCode\r\n");
    }

    if (mode & 0x02) {
        Rprintf("%08lX %04d %ld %02X %d %d %d %02X%02X%02X%02X%02X%02X %02X%02X%02X%02X%02X%02X %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X %d %02X%02X %s\r\n",
                (long) trxn_log,
                trxn_log->usIndex,
                trxn_log->ulDateTime,
                trxn_log->ucStatus.uBYTE,
                trxn_log->usTrxnType,
                trxn_log->usBatchNo,
                trxn_log->usSeqNo,
                trxn_log->uc6Amount[0], trxn_log->uc6Amount[1], trxn_log->uc6Amount[2], trxn_log->uc6Amount[3], trxn_log->uc6Amount[4], trxn_log->uc6Amount[5],
                trxn_log->uc6ReferenceNo[0], trxn_log->uc6ReferenceNo[1], trxn_log->uc6ReferenceNo[2], trxn_log->uc6ReferenceNo[3], trxn_log->uc6ReferenceNo[4], trxn_log->uc6ReferenceNo[5],
                trxn_log->uc20Track2Data[0], trxn_log->uc20Track2Data[1], trxn_log->uc20Track2Data[2], trxn_log->uc20Track2Data[3], trxn_log->uc20Track2Data[4],
                trxn_log->uc20Track2Data[5], trxn_log->uc20Track2Data[6], trxn_log->uc20Track2Data[7], trxn_log->uc20Track2Data[8], trxn_log->uc20Track2Data[9],
                trxn_log->uc20Track2Data[10], trxn_log->uc20Track2Data[11], trxn_log->uc20Track2Data[12], trxn_log->uc20Track2Data[13], trxn_log->uc20Track2Data[14],
                trxn_log->uc20Track2Data[15], trxn_log->uc20Track2Data[16], trxn_log->uc20Track2Data[17], trxn_log->uc20Track2Data[18], trxn_log->uc20Track2Data[19],
                trxn_log->ucResult,
                trxn_log->uc2StatusCode[0], trxn_log->uc2StatusCode[1],
                trxn_log->sz33Message
                );
    }
}


// Output trasaction log for debugging

void DebugOutputTrxnLog(void) {
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;

    return;

    msg_type = HEX2_to_UnsignedShort((char *) st_TrxnLog.uc2MsgType);
    proc_code = HEX3_to_Unsignedlong((char *) st_TrxnLog.uc3ProcCode);
    GetTransactionType(&trxn_type, msg_type, proc_code);

    Rprintf("\r\n");
    Rprintf("**************************************************\r\n");
    //	Rprintf("%s Trasaction Log\r\n", TrxnName_tbl[trxn_type-1]);
    Rprintf("Trasaction Log\r\n");
    Rprintf("**************************************************\r\n");
    Rprintf("st_TrxnLog.usMagicNo          = %04X\r\n", st_TrxnLog.usMagicNo);
    Rprintf("st_TrxnLog.usIndex            = %d\r\n", st_TrxnLog.usIndex);
    Rprintf("st_TrxnLog.ulDateTime         = %ld\r\n", st_TrxnLog.ulDateTime);
    Rprintf("st_TrxnLog.ulReversalDateTime = %ld\r\n", st_TrxnLog.ulReversalDateTime);
    Rprintf("st_TrxnLog.usTrxnType         = %d\r\n", st_TrxnLog.usTrxnType);
    Rprintf("st_TrxnLog.usBatchNo          = %d\r\n", st_TrxnLog.usBatchNo);
    Rprintf("st_TrxnLog.usSeqNo            = %d\r\n", st_TrxnLog.usSeqNo);
    Rprintf("st_TrxnLog.usOrigSeqNo        = %d\r\n", st_TrxnLog.usOrigSeqNo);
    Rprintf("st_TrxnLog.usReversalTrxnType = %d\r\n", st_TrxnLog.usReversalTrxnType);
    Rprintf("st_TrxnLog.usTrxnSeqNo        = %d\r\n", st_TrxnLog.usTrxnSeqNo);
    Rprintf("st_TrxnLog.usTrxnBatchNo      = %d\r\n", st_TrxnLog.usTrxnBatchNo);
    Rprintf("st_TrxnLog.ucStatus.uBYTE     = %02X\r\n", st_TrxnLog.ucStatus.uBYTE);

    Debug_Output("st_TrxnLog.uc8MerchantID", (char *) &st_TrxnLog.uc8MerchantID, sizeof (st_TrxnLog.uc8MerchantID), 0);
    Debug_Output("st_TrxnLog.uc20Track2Data", (char *) &st_TrxnLog.uc20Track2Data, sizeof (st_TrxnLog.uc20Track2Data), 0);
    Debug_Output("st_TrxnLog.uc2CVV", (char *) &st_TrxnLog.uc2CVV, sizeof (st_TrxnLog.uc2CVV), 0);
    Debug_Output("st_TrxnLog.uc3OperatorNo", (char *) &st_TrxnLog.uc3OperatorNo, sizeof (st_TrxnLog.uc3OperatorNo), 0);
    Debug_Output("st_TrxnLog.ucSupervisor", (char *) &st_TrxnLog.ucSupervisor, sizeof (st_TrxnLog.ucSupervisor), 0);
    Debug_Output("st_TrxnLog.uc6Amount", (char *) &st_TrxnLog.uc6Amount, sizeof (st_TrxnLog.uc6Amount), 0);
    Debug_Output("st_TrxnLog.uc6Cashback", (char *) &st_TrxnLog.uc6Cashback, sizeof (st_TrxnLog.uc6Cashback), 0);
    Debug_Output("st_TrxnLog.uc6Tip", (char *) &st_TrxnLog.uc6Tip, sizeof (st_TrxnLog.uc6Tip), 0);
    Debug_Output("st_TrxnLog.uc2Budget", (char *) &st_TrxnLog.uc2Budget, sizeof (st_TrxnLog.uc2Budget), 0);
    Debug_Output("st_TrxnLog.ucAccount", (char *) &st_TrxnLog.ucAccount, sizeof (st_TrxnLog.ucAccount), 0);
    Debug_Output("st_TrxnLog.uc8PinBlock", (char *) &st_TrxnLog.uc8PinBlock, sizeof (st_TrxnLog.uc8PinBlock), 0);
    Debug_Output("st_TrxnLog.uc10KSN", (char *) &st_TrxnLog.uc10KSN, sizeof (st_TrxnLog.uc10KSN), 0);
    Debug_Output("st_TrxnLog.ucOffline", (char *) &st_TrxnLog.ucOffline, sizeof (st_TrxnLog.ucOffline), 0);
    Debug_Output("st_TrxnLog.ucManual", (char *) &st_TrxnLog.ucManual, sizeof (st_TrxnLog.ucManual), 0);
    Debug_Output("st_TrxnLog.uc6ReferenceCode", (char *) &st_TrxnLog.uc6ReferenceCode, sizeof (st_TrxnLog.uc6ReferenceCode), 0);
    Debug_Output("st_TrxnLog.uc4OrigTerminalID", (char *) &st_TrxnLog.uc4OrigTerminalID, sizeof (st_TrxnLog.uc4OrigTerminalID), 0);
    Debug_Output("st_TrxnLog.uc6OrigRefNo", (char *) &st_TrxnLog.uc6OrigRefNo, sizeof (st_TrxnLog.uc6OrigRefNo), 0);
    Debug_Output("st_TrxnLog.uc2CurrencyCode", (char *) &st_TrxnLog.uc2CurrencyCode, sizeof (st_TrxnLog.uc2CurrencyCode), 0);
    Debug_Output("st_TrxnLog.uc6ProcessorFee", (char *) &st_TrxnLog.uc6ProcessorFee, sizeof (st_TrxnLog.uc6ProcessorFee), 0);
    Debug_Output("st_TrxnLog.uc6AcquiringFee", (char *) &st_TrxnLog.uc6AcquiringFee, sizeof (st_TrxnLog.uc6AcquiringFee), 0);
    Debug_Output("st_TrxnLog.sz41AdditionalData", (char *) &st_TrxnLog.sz41AdditionalData, sizeof (st_TrxnLog.sz41AdditionalData), 0);

    Debug_Output("st_TrxnLog.ucResult", (char *) &st_TrxnLog.ucResult, sizeof (st_TrxnLog.ucResult), 0);
    Debug_Output("st_TrxnLog.sz33Message", (char *) &st_TrxnLog.sz33Message, sizeof (st_TrxnLog.sz33Message), 0);
    Debug_Output("st_TrxnLog.uc2StatusCode", (char *) &st_TrxnLog.uc2StatusCode, sizeof (st_TrxnLog.uc2StatusCode), 0);
    Debug_Output("st_TrxnLog.uc6ReferenceNo", (char *) &st_TrxnLog.uc6ReferenceNo, sizeof (st_TrxnLog.uc6ReferenceNo), 0);
    Debug_Output("st_TrxnLog.uc6Balance", (char *) &st_TrxnLog.uc6Balance, sizeof (st_TrxnLog.uc6Balance), 0);
    Debug_Output("st_TrxnLog.uc6Available", (char *) &st_TrxnLog.uc6Available, sizeof (st_TrxnLog.uc6Available), 0);
    Debug_Output("st_TrxnLog.sz256Data", (char *) &st_TrxnLog.sz256Data, sizeof (st_TrxnLog.sz256Data), 0);

    Rprintf("st_TrxnLog.usVersion          = %02X\r\n", st_TrxnLog.usVersion);
    Rprintf("st_TrxnLog.usSuffix           = %02X\r\n", st_TrxnLog.usSuffix);
    Rprintf("\r\n");
}

// Get Next Transaction Parameter

void GetNextTrxnParameter(_tDATE_TIME *dt, int mode) {
    int i, min_index, max_index;
    _st_TrxnLog_ *trxn_log;
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    char amount[13], temp[65];

#ifdef USER_DEBUG
    Rprintf("GetNextTrxnParameter()\r\n");
#endif

    if (iFlashMemorySize < 16) {
        lMinLogAddr = FLASH8MB_TRANSACTION_LOG_START_ADDR;
    } else {
        lMinLogAddr = FLASH16MB_TRANSACTION_LOG_START_ADDR;
    }
    lMaxLogAddr = lMinLogAddr + (((long) MAX_TRANSACTION_LOG - 1)*(long) (sizeof (_st_TrxnLog_)));
    usTrxnTotalCount = 0;
    usEodTrxnCount = 0;

    min_index = 10000;
    max_index = 0;
    trxn_log = (_st_TrxnLog_ *) lMinLogAddr;
    //#ifdef USER_DEBUG_LOG
    if (mode) {
        DebugOutputTrxnLogData(trxn_log, 1);
    }
    //#endif
    LoadPOSUtilBuf();
    for (i = 0; i < MAX_TRANSACTION_LOG; i++) {
        if (trxn_log->usMagicNo == TRXN_LOG_MAGIC_NO && trxn_log->usSuffix == TRXN_LOG_SUFFIX) {
            if (mode) {
                //#ifdef USER_DEBUG_LOG
                DebugOutputTrxnLogData(trxn_log, 2);
                //#endif
            }

            // Get minimum transaction log index
            if (trxn_log->usIndex < min_index) {
                min_index = trxn_log->usIndex;
                // Set the pointer of the first transaction log to this pointer
                pstfFirstTrxnLog = trxn_log;
            }
            // Get maximum transaction log index
            if (trxn_log->usIndex > max_index) {
                max_index = trxn_log->usIndex;
                // Set the pointer of the last transaction log to this pointer
                pstfLastTrxnLog = trxn_log;
            }
            usTrxnTotalCount++;
            if (trxn_log->usBatchNo == tPOSUtilBuf.usBatchNo && trxn_log->ucStatus.BIT.EODTxFlag == 1) {
                usEodTrxnCount++;
            }
        }
        trxn_log++;
    }

    // No transaction log or transaction log format is error
    if (max_index <= 0 || max_index > 9999 || min_index <= 0 || min_index > 9999) {
        pstfFirstTrxnLog = (_st_TrxnLog_ *) lMinLogAddr;
        pstfLastTrxnLog = pstfFirstTrxnLog;
        pstfSavingTrxnLog = pstfLastTrxnLog;
        usTrxnLogIndex = 1;
        usEodTrxnCount = 0;
#ifdef USER_DEBUG
        Rprintf("No transaction log\r\n");
        Rprintf("First Log  Last Log  Saving Log  TrxnLogIndex  EodTrxnCount  TrxnTotalCount\r\n");
        Rprintf("%08X   %08X  %08X    %04d          %04d          %04d\r\n", (char *) pstfFirstTrxnLog, (char *) pstfLastTrxnLog, (char *) pstfSavingTrxnLog, usTrxnLogIndex, usEodTrxnCount, usTrxnTotalCount);
#endif
    } else {
        // Transaction log index is reset because that is over 9999
        if ((max_index - min_index) >= MAX_TRANSACTION_LOG) {
            min_index = 10000;
            max_index = 0;
            trxn_log = (_st_TrxnLog_ *) lMinLogAddr;
            for (i = 0; i < MAX_TRANSACTION_LOG; i++) {
                if (trxn_log->usMagicNo == TRXN_LOG_MAGIC_NO && trxn_log->usSuffix == TRXN_LOG_SUFFIX) {
                    if (trxn_log->usIndex >= MAX_TRANSACTION_LOG && trxn_log->usIndex < min_index) { // Get minimum transaction log index
                        min_index = trxn_log->usIndex;
                        pstfFirstTrxnLog = trxn_log; // Get the pointer of the first transaction log
                    }
                    if (trxn_log->usIndex < MAX_TRANSACTION_LOG && trxn_log->usIndex > max_index) { // Get maximum transaction log index
                        max_index = trxn_log->usIndex;
                        pstfLastTrxnLog = trxn_log; // Get the pointer of the last transaction log
                    }
                }
                trxn_log++;
            }
        }

        // Get Current Transaction Log Index
        usTrxnLogIndex = pstfLastTrxnLog->usIndex;

#ifdef USER_DEBUG_LOG
        Rprintf("\r\nThe Last Transaction\r\n");
        DebugOutputTrxnLogData(pstfLastTrxnLog, 3);
        Rprintf("\r\n");
#endif

        ucReversalFlag = 0;
        if (pstfLastTrxnLog->usTrxnType == TRXN_PURCHASE_ONLY &&
                pstfLastTrxnLog->ucStatus.BIT.ReversalFlag == 1 &&
                pstfLastTrxnLog->ucStatus.BIT.EODTxFlag == 1) {
            MSRDisable();
            ucReversalFlag = 1;
            pstfSavingTrxnLog = pstfLastTrxnLog;
#ifdef USER_DEBUG
            Rprintf("First Log  Last Log  Saving Log  TrxnLogIndex  EodTrxnCount  TrxnTotalCount\r\n");
            Rprintf("%08X   %08X  %08X    %04d          %04d          %04d\r\n", (char *) pstfFirstTrxnLog, (char *) pstfLastTrxnLog, (char *) pstfSavingTrxnLog, usTrxnLogIndex, usEodTrxnCount, usTrxnTotalCount);
            Rprintf("\r\nReversal is setted\r\n");
#endif
            return;
        }

        // Increase Transaction Log Index for Next Transaction
        usTrxnLogIndex++;
        if (usTrxnLogIndex > 9999) {
            usTrxnLogIndex = 1;
        }
        pstfSavingTrxnLog = pstfLastTrxnLog;
        // Increase Pointer to Transaction Log for Next Transaction
        pstfSavingTrxnLog++;
        // Transaction log address is greater than maximum transaction log address
        if ((long) pstfSavingTrxnLog > lMaxLogAddr) {
            pstfSavingTrxnLog = (_st_TrxnLog_ *) lMinLogAddr;
        }
#ifdef USER_DEBUG
        Rprintf("First Log  Last Log  Saving Log  TrxnLogIndex  EodTrxnCount  TrxnTotalCount\r\n");
        Rprintf("%08X   %08X  %08X    %04d          %04d          %04d\r\n", (char *) pstfFirstTrxnLog, (char *) pstfLastTrxnLog, (char *) pstfSavingTrxnLog, usTrxnLogIndex, usEodTrxnCount, usTrxnTotalCount);
#endif
    }
}

U16 LoadPOSUtilBuf() {
    LoadFlashPOSUtilInfo();
    memcpy((char *) &tPOSUtilBuf, (char *) tPOSUtilInfo.ptLastLog, sizeof (_tPOS_UTIL));

#ifdef USER_DEBUG
    Rprintf("usBatchNo=%d, usSeqNo=%d\r\n", tPOSUtilBuf.usBatchNo, tPOSUtilBuf.usSeqNo);
#endif

    return 0;
}

U16 SavePOSUtilBuf() {
    WritePOSUtil();
    LoadFlashPOSUtilInfo();
    memcpy((char *) &tPOSUtilBuf, (char *) tPOSUtilInfo.ptLastLog, sizeof (_tPOS_UTIL));

    return 0;
}

// Get Transaction Type from Message Type and Processing Code

void GetTransactionType(unsigned short *trxn_type, unsigned short msg_type, unsigned long proc_code) {
    switch (msg_type) {
        case MTYPE_AUTHORIZATION_REQUEST: // Authorization Request
            switch (proc_code) {
                case PCODE_BILL_PAYMENT_PRELIMINARY:
                    *trxn_type = TRXN_BILL_PAYMENT;
                    break;
            }
            break;

        case MTYPE_FINANCIAL_TRXN_REQUEST: // Financial Transaction Request
            switch (proc_code) {
                case PCODE_DEBIT_BUY:
                    *trxn_type = TRXN_PURCHASE_ONLY;
                    break;
                case PCODE_CREDIT_BUY:
                    *trxn_type = TRXN_PURCHASE_ONLY;
                    break;
                case PCODE_DEBIT_BALANCE_INQUIRY:
                    *trxn_type = TRXN_BALANCE_INQUIRY;
                    break;
                case PCODE_CREDIT_BALANCE_INQUIRY:
                    *trxn_type = TRXN_BALANCE_INQUIRY;
                    break;
                case PCODE_DEBIT_BILL_PAYMENT:
                    *trxn_type = TRXN_BILL_PAYMENT;
                    break;
                case PCODE_CREDIT_BILL_PAYMENT:
                    *trxn_type = TRXN_BILL_PAYMENT;
                    break;
            }
            break;

        case MTYPE_REVERSAL_REQUEST: // Reversal Request
            switch (proc_code) {
                case PCODE_DEBIT_BUY:
                    *trxn_type = TRXN_REVERSAL;
                    break;
                case PCODE_CREDIT_BUY:
                    *trxn_type = TRXN_REVERSAL;
                    break;
            }
            break;

        case MTYPE_SUPERVISORY_TRXN_REQUEST: // Supervisory Transaction Request
            switch (proc_code) {
                case PCODE_LOAD_BLACKLIST:
                    *trxn_type = TRXN_LOAD_BLACKLIST;
                    break;
                case PCODE_EOD:
                    *trxn_type = TRXN_EOD;
                    break;
            }
            break;
    }
}

// Save Tx Transaction Log

void SaveTxTransactionLog(void) {
    char msg_type[5];
    char temp[5];

#ifdef USER_DEBUG
    Rprintf("\r\nSaveTxTransactionLog()\r\n");
    Rprintf("st_TrxnReqData.sz5MsgType = %s\r\n", st_TrxnReqData.sz5MsgType);
    Rprintf("st_TrxnReqData.sz7ProcCode = %s\r\n", st_TrxnReqData.sz7ProcCode);
    Rprintf("st_TrxnReqData.sz13Amount = %s\r\n", st_TrxnReqData.sz13Amount);
#endif
    memset(&st_TrxnLog, 0x00, sizeof (st_TrxnLog));

    st_TrxnLog.usMagicNo = TRXN_LOG_MAGIC_NO;
    st_TrxnLog.usIndex = usTrxnLogIndex;

    // Set Online Transaction Flag
    st_TrxnLog.ucStatus.BIT.OnlineFlag = 1;
    // Set EOD Transaction Flag
    st_TrxnLog.ucStatus.BIT.EODTxFlag = 1;
    // Set Not Received Response Flag
    st_TrxnLog.ucStatus.BIT.NotRxFlag = 1;
    // Set Not Print Receipt #1 Flag
    st_TrxnLog.ucStatus.BIT.NotPrint1Flag = 1;
    // Set Not Print Receipt #2 Flag
    st_TrxnLog.ucStatus.BIT.NotPrint2Flag = 1;
    // Set Reserved for Future Use
    st_TrxnLog.ucStatus.BIT.Reserved = 3;

    // Purchase and Reversal
    if (st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY) {
        // Set Reversal Transaction Flag
        st_TrxnLog.ucStatus.BIT.ReversalFlag = 1;
    } else {
        // Clear Reversal Transaction Flag
        st_TrxnLog.ucStatus.BIT.ReversalFlag = 0;
    }

    st_TrxnLog.usTrxnType = st_TrxnReqData.usTrxnType;
    st_TrxnLog.usBatchNo = st_TrxnReqData.usBatchNo;
    st_TrxnLog.usSeqNo = st_TrxnReqData.usSeqNo;

    str_to_bcd((char *) st_TrxnLog.uc8MerchantID, st_TrxnReqData.sz16MerchantID, 16);

    st_TrxnLog.ulDateTime = st_TrxnReqData.ulDateTime;

    // Copy Track 2 Data
    st_TrxnLog.uc20Track2Data[0] = strlen(st_TrxnReqData.sz42Track2Data);
    str_to_zbcd((char *) &st_TrxnLog.uc20Track2Data[1], &st_TrxnReqData.sz42Track2Data[0], st_TrxnLog.uc20Track2Data[0]);
    /*
    {
            char sz42TmpBuf[42];
	
            // Recover Track 2 Data
            memset(sz42TmpBuf, 0x00, sizeof(sz42TmpBuf));
            zbcd_to_str(sz42TmpBuf, &st_TrxnLog.uc20Track2Data[1], st_TrxnLog.uc20Track2Data[0]);
	
            Rprintf("sz42TmpBuf: %s\r\n", sz42TmpBuf);
	
    }
     */
    str_to_bcd((char *) st_TrxnLog.uc2CVV, st_TrxnReqData.sz4CVV, 4);
    str_to_bcd((char *) st_TrxnLog.uc3OperatorNo, st_TrxnReqData.sz7OperatorNo, 6);

    st_TrxnLog.ucSupervisor = st_TrxnReqData.ucSupervisor;

    str_to_bcd((char *) st_TrxnLog.uc6Amount, st_TrxnReqData.sz13Amount, 12);
    str_to_bcd((char *) st_TrxnLog.uc6Cashback, st_TrxnReqData.sz13Cashback, 12);
    str_to_bcd((char *) st_TrxnLog.uc6Tip, st_TrxnReqData.sz13Tip, 12);
    str_to_bcd((char *) st_TrxnLog.uc2Budget, st_TrxnReqData.sz5Budget, 4);
    st_TrxnLog.ucAccount = st_TrxnReqData.ucAccount;
    str_to_bcd((char *) st_TrxnLog.uc8PinBlock, st_TrxnReqData.sz17PinBlock, 16);
    str_to_bcd((char *) st_TrxnLog.uc10KSN, st_TrxnReqData.sz21KSN, 20);
    st_TrxnLog.ucOffline = st_TrxnReqData.ucOffline;
    st_TrxnLog.ucManual = st_TrxnReqData.ucManual;
    st_TrxnLog.usOrigSeqNo = st_TrxnReqData.usOrigSeqNo;
    str_to_bcd((char *) st_TrxnLog.uc6ReferenceCode, st_TrxnReqData.sz13ReferenceCode, 12);

    str_to_bcd((char *) st_TrxnLog.uc4OrigTerminalID, st_POSSetupInfo.sz9TerminalID, 8); // st_TrxnReqData.sz9OrigTerminalID, 8);
    st_TrxnLog.ulReversalDateTime = st_TrxnReqData.ulReversalDateTime;
    st_TrxnLog.usReversalTrxnType = st_TrxnReqData.usReversalTrxnType;
    str_to_bcd((char *) st_TrxnLog.uc6OrigRefNo, st_TrxnReqData.sz13ReferenceNo, 12);
    str_to_bcd((char *) st_TrxnLog.uc2CurrencyCode, st_TrxnReqData.sz4CurrencyCode, 4);
    str_to_bcd((char *) st_TrxnLog.uc6ProcessorFee, st_TrxnReqData.sz13ProcessorFee, 12);
    str_to_bcd((char *) st_TrxnLog.uc6AcquiringFee, st_TrxnReqData.sz13AcquiringFee, 12);
    strcpy((char *) st_TrxnLog.sz41AdditionalData, st_TrxnReqData.sz41AdditionalData);

    st_TrxnLog.usVersion = TRXN_LOG_VERSION;
    st_TrxnLog.usSuffix = TRXN_LOG_SUFFIX;

    WriteTransactionLog((char *) pstfSavingTrxnLog);
#ifdef USER_DEBUG
    DebugOutputTrxnLog();
#endif
}

// Save Rx Transaction Log

void SaveRxTransactionLog(void) {
    char temp[5];
    char bill_payment_data[1003];

#ifdef USER_DEBUG
    Rprintf("\r\nSaveRxTransactionLog()\r\n");
#endif
    memset(&st_TrxnLog, 0x00, sizeof (st_TrxnLog));
    memcpy(&st_TrxnLog, (char *) pstfSavingTrxnLog, sizeof (st_TrxnLog));

    st_TrxnLog.usMagicNo = TRXN_LOG_MAGIC_NO;
    st_TrxnLog.usIndex = usTrxnLogIndex;

    // Clear Not Received Response Flag
    st_TrxnLog.ucStatus.BIT.NotRxFlag = 0;

    if (st_TrxnRespData.ucResult != '1') { // '1' : Approved
        // ������ OK�� �ƴϸ� EODTxFlag��Ʈ�� 0���� EOD �� reversal STAN�˻����� ����
        // EODTxFlag�� 0�̸� EOD �� Reversal STAN�˻����� ����
        st_TrxnLog.ucStatus.BIT.EODTxFlag = 0;
        st_TrxnLog.ucStatus.BIT.ReversalFlag = 0;
    }

    // 3.  RESULT - Result code for EFT Transaction
    st_TrxnLog.ucResult = st_TrxnRespData.ucResult;
    // 4.  MESSAGE - Result message text
    strcpy(st_TrxnLog.sz33Message, st_TrxnRespData.sz33Message);
    // 5.  STATUS - The status code
    str_to_bcd((char *) st_TrxnLog.uc2StatusCode, st_TrxnRespData.sz4StatusCode, 3);
    // 6.  REFNO - Transaction approval reference number from switch
    str_to_bcd((char *) st_TrxnLog.uc6ReferenceNo, st_TrxnRespData.sz13ReferenceNo, 12);
    // 9.  BALANCE - Balance amount
    str_to_bcd((char *) st_TrxnLog.uc6Balance, st_TrxnRespData.sz13Balance, 12);
    // 10. AVAILABLE - Available amount
    str_to_bcd((char *) st_TrxnLog.uc6Available, st_TrxnRespData.sz13Available, 12);
    // 11. DATA - Mini statement data delimited by the pipe character "|"
    strcpy(st_TrxnLog.sz256Data, st_TrxnRespData.sz256Data);

    st_TrxnLog.usVersion = TRXN_LOG_VERSION;
    st_TrxnLog.usSuffix = TRXN_LOG_SUFFIX;

    WriteTransactionLog((char *) pstfSavingTrxnLog);
#ifdef USER_DEBUG
    DebugOutputTrxnLog();
#endif
}

// Save Print Transaction Log

void SavePrintTransactionLog(_st_TrxnLog_ *trxn_log, int second_prt) {
    char temp[5];

#ifdef USER_DEBUG
    Rprintf("\r\nSavePrintTransactionLog()\r\n");
#endif
    memset(&st_TrxnLog, 0x00, sizeof (st_TrxnLog));

    memcpy(&st_TrxnLog, trxn_log, sizeof (st_TrxnLog));
#ifdef USER_DEBUG
    Rprintf("st_TrxnLog.uc2MsgType = %02X%02X\r\n", st_TrxnLog.uc2MsgType[0], st_TrxnLog.uc2MsgType[1]);
#endif

    if (second_prt == 0) {
        // Clear Reversal Transaction Flag
        st_TrxnLog.ucStatus.BIT.ReversalFlag = 0;
        // Clear Not Print Receipt #1 Flag
        st_TrxnLog.ucStatus.BIT.NotPrint1Flag = 0;
    } else {
        // Clear Not Print Receipt #2 Flag
        st_TrxnLog.ucStatus.BIT.NotPrint2Flag = 0;
    }

    // Clear PIN
    memset(st_TrxnLog.uc16PIN, 0x00, 16);

    WriteTransactionLog((char *) trxn_log);
#ifdef USER_DEBUG
    DebugOutputTrxnLog();
#endif
}

// Save Reprinting Count

void SaveReprintingCount(_st_TrxnLog_ *trxn_log) {
#if 0 // sispp 20111008
#ifdef USER_DEBUG
    Rprintf("\r\nSaveReprintingCount()\r\n");
#endif
    memset(&st_TrxnLog, 0x00, sizeof (st_TrxnLog));

    memcpy(&st_TrxnLog, trxn_log, sizeof (st_TrxnLog));

    // Decrease Reprinting Count of External Dot Printer by shifting left
    st_TrxnLog.ucReprintingCnt >>= 1;

    WriteTransactionLog((char *) trxn_log);
#ifdef USER_DEBUG
    DebugOutputTrxnLog();
#endif
#endif
}

// Save Reversal Transaction Log

void SaveReversalTransactionLog(_st_TrxnLog_ *trxn_log) {
    char msg_type[5];

#ifdef USER_DEBUG
    Rprintf("-- SaveReversalTransactionLog()\r\n");
    Rprintf("trxn_log = %08lX\r\n", (long) trxn_log);
#endif
    memset(&st_TrxnLog, 0x00, sizeof (st_TrxnLog));
    memcpy(&st_TrxnLog, trxn_log, sizeof (st_TrxnLog));

    // Clear Not Received Response Flag
    st_TrxnLog.ucStatus.BIT.NotRxFlag = 0;
    // Clear EOD Transaction Flag
    st_TrxnLog.ucStatus.BIT.EODTxFlag = 0;
    // Clear Reversal Transaction Flag
    st_TrxnLog.ucStatus.BIT.ReversalFlag = 0;

    /*	
            // Set Online Transaction Flag
            st_TrxnLog.ucStatus.BIT.OnlineFlag = 1;
            // Set EOD Transaction Flag
            st_TrxnLog.ucStatus.BIT.EODTxFlag = 1;
            // Set Reversal Transaction Flag
            st_TrxnLog.ucStatus.BIT.ReversalFlag = 1;
            // Set Not Received Response Flag
            st_TrxnLog.ucStatus.BIT.NotRxFlag = 1;
            // Set Not Print Receipt #1 Flag
            st_TrxnLog.ucStatus.BIT.NotPrint1Flag = 1;
            // Set Not Print Receipt #2 Flag
            st_TrxnLog.ucStatus.BIT.NotPrint2Flag = 1;
            // Set Reserved for Future Use
            st_TrxnLog.ucStatus.BIT.Reserved = 3;
	
            // Set Reversal Request to Message Type ID
            sprintf(msg_type, "%04X", MTYPE_REVERSAL_REQUEST);
            str_to_bcd((char *)&st_TrxnLog.uc2MsgType, msg_type, 4);
    #ifdef USER_DEBUG
            DebugOutputTrxnLog();
    #endif
     */

    WriteTransactionLog((char *) trxn_log);
#ifdef USER_DEBUG
    DebugOutputTrxnLog();
#endif
}

// Go to Reversal Mode

void GotoReversalMode(void) {
#ifdef USER_DEBUG
    Rprintf("GotoReversalMode()\r\n");
#endif
    MSRDisable();

    ucReversalFlag = 1;
    usAutoReversal10MSTimer = TIMER_Get10MSTimer();

    if (st_POSSetupInfo.ucComDevice == GSM_MODEM) {
        // "Reversal        ", "1.Reversal      ", "2.Set GSM       ", "3.Print & Clear "
        MainStatusSetting(MSS_REVERSAL, MST_REVERSAL_MODE, M4ReversalMsg_000003, LCD_LINE1, ucLangFlag);
        SetMenuScrollUpDownInfo(1, 1, 1, 3, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReversalMenu_00021]);
    }
}

// Print Reversal Receipt

void PrintReversalReceipt(unsigned short delay_time) {
#ifdef USER_DEBUG
    Rprintf("-- PrintReversalReceipt()\r\n");
#endif
#ifdef USER_DEBUG
    Rprintf("\r\nReversal is setted\r\n");
#endif
    MSRDisable();

    ucReversalFlag = 1;

    TIMER_Wait1MS(delay_time);
    // NO PAPER?
    if (!DetectPaper()) {
        // "Reversal        ", "                ", "Insert paper and", "Press ENTER key "
        MainStatusSetting(MSS_REVERSAL, MST_PRINT_REVERSAL_RECEIPT, M4ReversalMsg_000002, -1, ucLangFlag);
        usReversalPrint10MSTimer = TIMER_Get10MSTimer();
    } else {
        // "Reversal        ", "not finished    ", "correctly       ", "                "
        MainStatusSetting(MSS_REVERSAL, MST_PRINT_REVERSAL_RECEIPT, M4ReversalMsg_000001, -1, ucLangFlag);
        pusServiceAddr++;
        TIMER_Wait1MS(3000);
        usPrintStep = 1;
    }

    ModemClose();
}

// Print Unsuccessful Reversal Receipt

void PrintUnsuccessfulReversalReceipt(void) {
#ifdef USER_DEBUG
    Rprintf("-- PrintUnsuccessfulReversalReceipt()\r\n");
#endif
    ucReversalFlag = 1;
    // NO PAPER?
    if (!DetectPaper()) {
        // "Reversal        ", "is impossible   ", "Insert paper and", "Press ENTER key "
        MainStatusSetting(MSS_REVERSAL, MST_PRINT_UNSUCCESSFUL_REVERSAL_RECEIPT, M4ReversalFailMsg_02, -1, ucLangFlag);
    } else {
        // "Reversal        ", "is impossible   ", "                ", "                "
        MainStatusSetting(MSS_REVERSAL, MST_PRINT_UNSUCCESSFUL_REVERSAL_RECEIPT, M4ReversalFailMsg_01, -1, ucLangFlag);
        pusServiceAddr++;
        usPrintStep = 1;
    }
    Beep_EventSound(ERROR_TONE);
    TIMER_Wait1MS(3000);

    ModemClose();
}

// Perform Reversal Transaction

void PerformReversalTransaction(void) {
    int i;

#ifdef USER_DEBUG
    Rprintf("-- PerformReversalTransaction()\r\n");
#endif

    MSRDisable();

    ucReversalFlag = 1;

#ifdef USER_DEBUG
    Rprintf("\r\nReversal is setted\r\n");
#endif
    // "Reversal        ", "not finished    ", "correctly       ", "                "
    MainStatusSetting(MSS_REVERSAL, MST_REVERSAL, M4ReversalMsg_000001, -1, ucLangFlag);

    ModemClose();

    TIMER_Wait1MS(3000);

    i = GetConnectionConditions(st_POSSetupInfo.ucComDevice, 0, 0);
    if (i) {
        Beep_EventSound(ERROR_TONE);
        DisplayConnectionErrorCondition(i);
        TIMER_WaitKeyPress1MS(5000);

        ucReversalRetryCnt++;
        ucReversalRetryTimePerCnt = 0;
        if (ucReversalRetryCnt < 3) {
            // Go to Reversal Mode
            GotoReversalMode();
        } else {
            ucReversalRetryCnt = 0;
            PrintUnsuccessfulReversalReceipt();
        }
        return;
    }

    InitializeGlobalVariables();

    ucPINInputAndReconnectFlag = 0;

    memset(sz13Amount, 0x00, sizeof (sz13Amount));
    sz13Amount[0] = '0';

    memset(sz19BillID, 0x00, sizeof (sz19BillID));
    memset(sz19PaymentID, 0x00, sizeof (sz19PaymentID));

    MSR_ClearAllCardDataBuffer();
    ClearAllMSRDataBuf();

    if (InitTrxnReqData() < 0) {
        ErrorDisplayAndGoErrorStatus(M4ErrNoBatchNo_00001, -1, ucLangFlag);
        return;
    }
    st_TrxnReqData.usTrxnType = TRXN_REVERSAL;
    //RecoverReversalData(pstfSavingTrxnLog);
    SetReversalReqData(NULL);
    giTransactionType = TRXN_BANK_EFTTRAN;

    sVirtualKey = BTKEY_ENTER;
}

/* */
