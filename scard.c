#include "system.h"
#include "extern.h"

#include "./include/emv/emv_app.h"
#include "./include/hal/usip/hal_scs.h"
#define EMV_KERNEL

U16 gSysTimer;
int gbLangCode;

char gbRS232TaskStep = 0;
char gbEmvScTaskStep = 0;

extern int giPinTryCnt;
extern int giTrxnNOnFlag;
extern U16 ghResponseCode, gwResponseCode, gwTrmARC;
extern U16 gwCurrencyCode;
extern U08 gbCurrencyExp;
extern U08 gbSignatureFlag;
extern U08 gbPinBlock[8];
extern S08 gbReversalFlag, gbRefundFlag, gbOnLineFlag, gbReferralFlag;
extern S08 gbSaveTrxnRec;
extern S08 gbAmountIN, gbTrxnType, gbPin_Type, gbPin_TypeDone;

extern U32 gdwAmount;
extern U08 Total_Amount[16];
extern char CardNo1[112], CardNo2[52];
extern char gbTmpKeyBuf[20];
extern char gbExtPinPadFound;
extern U08 RxDBUF[2048], TxDBUF[2048];
extern U16 gwModemWait, gwModemTOut, gtwCRC, gtwLRC;

#define LsEnterPAN          44
#define LsEnterYYMM         45
#define LsSwipeCard         46
#define LsInsertCard        47
#define LsAmount            48
#define LsEnterPIN          49
#define LsTrxnResult        50
#define LsEMVuseMSR         51
#define LsEMVuseICC         52
#define LsEMVselect         53
#define LsEMVreading        54
#define LsEMVreferral       55
#define LsEMVOn_Line        56
#define LsEMVOffLine        57
#define LsPINtryLast        58
#define LsPINincorrect      59
#define LsPIN_OK            60
#define LsPINchange         61
#define LsPINconfirm        62
#define LsISSreferral       63
#define LsLCDcontrast       64
#define LsTrxnF5INQ         65
#define LsEnterOnlinePIN    66
#define LsEnterOfflinePIN   67

#define COM_PORT0   0

extern const U08 gcTrmCAPK[];
extern const U08 gcTrmExcepList[];
extern const U08 gcTrmRevocList[];

U16 TraceNr; // Last transaction log ���� ������
U08 SelectedAID[17]; // Transaction Temp
char CardAcceptorMerchantID[15]; // System Info
char CardAcceptorTerminalID[ 8]; // System Info
char TrmAcquirerID[6]; // System Info
char POSSerialNr[8]; // System Info
char TrmCapa[3]; // System Info
char TrmCapaAdditional[5]; // System Info
char TrmType; // System Info
char TrmTCC; // System Info
char TrmMCC[2]; // System Info
char TrmForceOnLine; // System Info
char TrmL2TTAmode; // System Info
U08 SvcCode[3]; // Transaction Temp
U08 CardHolderName[17]; // Transaction Temp

extern int fnD642Bcd(U08 *bcdBuf, D64 dwNo, int nx);
extern void WaitTxDone(int tPort);
extern int dequeue_key();
extern int isDetectCard;
extern void Wait1MS(unsigned short time1ms);


int giPinTryCnt;
int giTrxnNOnFlag = 0;
U16 ghResponseCode = 0, gwResponseCode = 0, gwTrmARC = 0;
U16 gwCurrencyCode = 0;
U08 gbCurrencyExp = 0;
U08 gbSignatureFlag = 0;
U08 gbPinBlock[8];
S08 gbReversalFlag = 0, gbRefundFlag = 0, gbOnLineFlag = 0, gbReferralFlag = 0;
S08 gbSaveTrxnRec = 0, gbValidateBit = 0;
S08 gbAmountIN = 0, gbTrxnType = 0, gbPin_Type = 0, gbPin_TypeDone = 0;

U32 gdwAmount = 0L;
U08 Total_Amount[16];
char CardNo1[112], CardNo2[52];
char gbTmpKeyBuf[20];
char gbExtPinPadFound;
U08 RxDBUF[2048], TxDBUF[2048];

U16 gwModemWait = 0, gwModemTOut = 0, gtwCRC = 0, gtwLRC = 0;
char gbKeyCnt = 0, gbKeyVal = 0;

const U08 gcHex2Asc[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

typedef struct {
    U16 BatchNr;
    U16 TraceNr;
    U16 MsgType;
    U16 POSEntryMode;
    U08 zzFlag;
    S08 OnLineFlag;
    U08 Signature;
    U08 POSConditionCode;
    U16 ResponseCode;
    U08 SystemTraceNr[3];
    U08 ProcessingCode[3];
    U08 ApprovalCode[6];
    U08 RetrievalRefNr[12];
    U08 bcdYMDHMS[6]; //YYMMDDHHMMSS, shoule be in order
    U08 AmountTrxn[6];
    U08 Track2Data[20];
    U08 ProcCodeStrNr;
    U08 RespCodeStrNr;
    U08 SelectedAID[17]; //Length 5-16
    U08 CardHolderName[17]; //Length 2-26
    U08 SvcCode[3]; // sispp070213 2CO.038.00
#define ICCbL3_MAX  145
    U08 ICCbL3[2];
    U08 TVR[5];
    U08 TSI[2];
    U08 CVMR[3];
    U08 Reserved[135];
} TTrxnRec;

TTrxnRec gsXRec;

U16 deltaMS(U16 refMS, U16 tBase) {
    long tTms;

    switch (tBase) {
        case 0: tTms = refMS - TIME_BASE0;
            break;
        case 1: tTms = refMS - TIME_BASE1;
            break;
        case 10: tTms = refMS - TIME_BASE10;
            break;
    }
    if (tTms < 0) tTms += 0x10000L;

    return ((U16) tTms);
}

int RdCom(int channel) {
    return RS232_Read(channel);
}

void WrCom(int channel, char *stream, int size) {
    RS232_Write(channel, stream, size);
}

void WaitTxDone(int tPort) {
    int i = 0, n = 0, ub0;

    ub0 = TIME_BASE1;
    if (tPort >= 0 && tPort <= 3) {
        while (1) {
            if (RS232_TX_STATUS(tPort)) break;
            if (deltaMS(ub0, 1) > 200) break;
        }
    }
}

void DebugBUF(U08 *DbgBuf, int DgLen) {
#ifdef DBG_REPORT
    int i = 0;

    if (DbgBuf == NULL) DgLen = 0;
    DBGprt(("[%2d]={", DgLen));
    if (DgLen) {
        if (DgLen > 0x1F) DBGprt(("\r\n\t"));
        while (i < DgLen) {
            DBGprt(("%02X", DbgBuf[i]));
            if (((i++) & 0xF) == 0xF) {
                if ((i & 0xFF) == 0) DBGprt(("\r\n%x\t", i));
                else if ((i & 0x1F) == 0) DBGprt(("\r\n\t"));
                else DBGprt((" "));
            }
        }
    }
    DBGprt(("};\r\n"));
#endif
}

void setDEBUG_COMport(int comport) {
}

int app_UPDATEgsXRec_ICCbL3(void) {
    return 0;
}

/**/

void Lprintf(char y, char x, char *str) {
    LCD_DisplayString(y, x, strlen(str), str, 0);
}

void STRDISP(int no) {
    //	LCDDisplay4Lines(no, -1, 0);
}

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
int gsc_IFMinit(void) {
    //    setDEBUG_COMport(COM_PORT0);
#ifdef BITEL_IC5000_RFM
    CONTROL_POWER_SAVING_STATUS(3, ON); // SMART CARD
    gem_RS232open = 0;
#endif
    pgsSC_STAT = (GSC_STAT *) & gsSC_STAT;
    memset(pgsSC_STAT, 0, sizeof (GSC_STAT));
    //gem_Protocol = TLP_PROTOCOL; //Set TLP Protocol for T=0
    gem_Protocol = GBP_PROTOCOL; //Set GBP Protocol for T=1
    if (!gem_RS232open) {
        //====Open Serial Port 0 at 9600 Baud================
        if (gem_BaudRate < 9600L) gem_BaudRate = 9600L;
#ifdef GEM_IFM_DOUBLE_SPEED
        //====Open Serial Port 0 at 19200Baud================
        if (gem_BaudRate == 9600L) {
            TL_Open(0, gem_BaudRate);
            //Set COM0 speed set done, and configure SIO line
            DBGprt(("SetSIO_Baud(9600(4)->19200(3)"));
            SC_OUTPUT[0] = 0x0A;
            //SC_OUTPUT[1]=0x02; // 38400L
            SC_OUTPUT[1] = 0x03; // 19200L
            //SC_OUTPUT[1]=0x04; //  9600L default
            gsc_cmmdOUTPUTngetRESPONSE(2); // Always Error!
            gem_BaudRate = 19200L;
        }
#endif
        TL_Open(0, gem_BaudRate);
    }

    /*Get Firmware version from Reader   */
    if (gsc_FWversion() != NO_ERR) {
        DBGprt(("\r\n.gsc_FWversion() Error!\r\n"));
        return (-1);
    }

    //Disable TLP compatibility
    //In TLP Mode, the GemCore Firmware adds TA1,TB1,TC1 and TD1 bytes
    //if they are not present in the asynchronous smart card Answer to Reset
    SC_OUTPUT[0] = 0x01;
    SC_OUTPUT[1] = 0x00;
    SC_OUTPUT[2] = 0x00;
    DBGprt(("GEM_SET_MODE"));
    if (gsc_cmmdOUTPUTngetRESPONSE(3) != NO_ERR) return (-1);
    //if(gsc_cmmdOUTPUTngetRESPONSE(2) != NO_ERR) return(-1);

    //Get supported Card Type, Directory
    SC_OUTPUT[0] = 0x17;
    SC_OUTPUT[1] = 0x00;
    DBGprt(("SupportCardType"));
    if (gsc_cmmdOUTPUTngetRESPONSE(2) != NO_ERR) return (-1);

    //Switch Reader into ISO_MODE, EMV_MODE
    SC_OUTPUT[0] = 0x17;
    SC_OUTPUT[1] = 0x00;
    SC_OUTPUT[2] = 0x00; // Just read MODE
    //SC_OUTPUT[0]=0x17; SC_OUTPUT[1]=0x00; SC_OUTPUT[2]=0x47; // ISO_MODE(WinCARD)
    //SC_OUTPUT[0]=0x17; SC_OUTPUT[1]=0x00; SC_OUTPUT[2]=0x45; // EMV_MODE
    DBGprt(("ISO/EMV MODE"));
    if (gsc_cmmdOUTPUTngetRESPONSE(3) != NO_ERR) return (-1);
    if (gsc_Status() < 0) return (-1);

    return (NO_ERR);
}

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/

int gsc_cmmdOUTPUTngetRESPONSE(int cmdLen) {
    gSysTimer = TIME_BASE0; // sispp 070110 2CJ.010.01
    gwSW1SW2 = 0;
    cmdLen = TL_SendReceive((U32) cmdLen, (U08 *) & SC_OUTPUT[0], (U32 *) & giScLen, (U08 *) & gbScBuf[0]);
    if (cmdLen == NO_ERR) return (0);
#ifdef DBG_REPORT
    DRVprt(("<E>GemTL:"));
    switch (cmdLen) {
        case ERR_SCS_CMD_ABORTED: DRVprt(("Command aborted"));
            break;
        case ERR_SCS_CARD_MUTE: DRVprt(("Card mute."));
            break;
        case ERR_SCS_PARITY: DRVprt(("Parity error during an exchange with the card."));
            break;
        case ERR_SCS_OVERRUN: DRVprt(("Card consuming too much current or is short-circuiting"));
            break;
        case ERR_SCS_CARD_ABSENT: DRVprt(("Card absent. There is no card in the smart card interface."));
            break;
        case ERR_SCS_POWER_UP: DRVprt(("Card powered down."));
            break;
        case ERR_SCS_INVALID_ATR: DRVprt(("Error in the card reset response"));
            break;
        case ERR_SCS_BAD_ATR_TCK: DRVprt(("In the card reset response, the Check Character (TCK) is not correct"));
            break;
        case ERR_SCS_PROTOCOL: DRVprt(("Protocol error"));
            break;
        case ERR_SCS_CLASS_NOT_SUPPORTED: DRVprt(("The first byte of command (CLA) is invalid"));
            break;
        case ERR_SCS_PROC_BYTE: DRVprt(("The card sent an invalid procedure byte"));
            break;
        case ERR_SCS_INVALID_SPEED: DRVprt(("Speed (TA1 parameter) not supported"));
            break;
        case ERR_SCS_UNKNOW: DRVprt(("Function not implemented"));
            break;
        case ERR_SCS_INVALID_NAD: DRVprt(("The card sent an invalid NAD (T=1)"));
            break;
        case ERR_SCS_OVERFLOW: DRVprt(("Response too long for the buffer"));
            break;
    }
    DRVprt(("\r\n"));
#endif
    if (gbEmvScTaskStep > 3) {
        memset(pgsSC_STAT, 0, sizeof (GSC_STAT));
        gbEmvScTaskStep = 126; //call goto appEmvTaskEnd;
    }

    return (-1);
}

#define Tag_Reserved 0x00

const int tbl_IccDataList[] = {
    T8b_AppCrytogram, T1b_CryptogramInfoData, Tvb_IssuerAppData, T4b_TrmUnpredictableNo, T2b_ATC,
    T5b_TrmTVR, T3n_TrmTrxnDate, T1n_TrmTrxnType, T6n_TrmAmountAuthorised, T2n_TrmTrxnCurrencyCode,
    Tag_Reserved, T2b_AIP, T2n_TrmCountryCode, T6n_TrmAmountOther, T3b_TrmCapa, Tvv_AID, Tag_Reserved,
    T2a_ARC, T1n_TrmType, T8a_TrmIFD_SerialNo, T1a_TrmTCC, Tvv_DFname, T2b_TrmAppVersionNo,
    Tvn_TrmTrxnSequenceCounter, T3b_TrmCVMR
};

int BuildIccData(char *pBuf) {
    int i, j, iCnt, iLen, tLen, tTag;
    char temp[512];
    U08 *pAdd;

    iCnt = sizeof (tbl_IccDataList) / sizeof (int);
    iLen = 0;
    for (i = 0; i < iCnt; i++) {
        tTag = tbl_IccDataList[i];
        if (tTag != Tag_Reserved) {
            tLen = getDnL(pgbAppBuf, giAppBufLen, tTag, &pAdd);
            if (tLen > 0) {
                bcd2asc(temp, pAdd, tLen * 2);
                for (j = 0; j < tLen * 2; j++) {
                    pBuf[iLen++] = temp[j];
                }
            }
        }
        if (i + 1 < iCnt) {
            pBuf[iLen++] = '|';
        }
    }
    pBuf[iLen] = 0x00;

    return iLen;
}

#ifdef EMV_KERNEL
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

#define AUTO_DETECT_MAIN_SLOT

int CheckSmartCardSlot() {
    if (!gem_RS232open) {
        if (gsc_IFMinit() == NO_ERR) {
            gsc_SetCardTYPEandSLOT(0x02, 0);
        } else {
            TL_Close();
        }
    }
    if (!gem_RS232open)
        return -1;
    if (deltaMS(gwModemWait, 0) > 500) {

        if (TL_GetSlotNo() != 0) {
            TL_SetSlotNo(0);
            gsc_SetCardTYPEandSLOT(0x02, 0);
        }
        gwModemWait = TIME_BASE0;
        if (gsc_Status() != NO_ERR) pgsSC_STAT->CARD = 0;
    }

    return pgsSC_STAT->CARD;
}

void appEmvTask(void) {
    int i, j;

    if (gbEmvScTaskStep < 2) {
        if (gbEmvScTaskStep == 1) return;
#ifdef AUTO_DETECT_MAIN_SLOT
        if ((!gbEmvScTaskStep)&&(usMainStatus == MSS_INITIAL) && (*pusServiceAddr == 0x0000)) {
            if (CheckSmartCardSlot() == 1) {
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
                MainStatusSetting(MSS_CUSTOMER_TRANS, MST_CUSTOMER_TRANS, M4CardDetected_00001, -1, ucLangFlag);
                pusServiceAddr += 2;
                giTransactionType = TRXN_BANK_EFTTRAN;
                st_TrxnReqData.usTrxnType = TRXN_PURCHASE_ONLY;
                gbEmvScTaskStep = 2;
            }
        }
#endif
        return;
    }
    switch (gbEmvScTaskStep) {
        case 2:
            /*--------------------------------------------------------------*/
            /*  Detect IFM. */
            /*--------------------------------------------------------------*/
            TL_Close();
            if (gsc_IFMinit() < 0) {
                DBGprt(("\r\n....Error in gsc_IFMinit()....\r\n"));
                TL_Close();
                LCDDisplay4Lines(M4_____________Space, -1, ucLangFlag);
                LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ICCardNGMessage_01], ucLangFlag);
                Beep_EventSound(ERROR_TONE);
                TIMER_WaitKeyPress1MS(1000);
                sVirtualKey = BTKEY_CANCEL;
                return;
            }
            break;
        case 3:
            /*--------------------------------------------------------------*/
            //Smart Card Power Up,
            //if a Non EMV smart card is inserted the reader will
            // send back error 0xA0.
            // We suppose that the right EMV smart card is used.
            /*--------------------------------------------------------------*/
            /* Define Main Card Type as "EMV Normal Card"*/
            if (gsc_SetCardTYPEandSLOT(0x02, 0) != NO_ERR) {
                if (!pgsSC_STAT->CARD) {
                    DBGprt(("Not Inserted.\r\n"));
                    Wait1MS(500);
                } else { // Card error!
                    if (pgsSC_STAT->pwON) gsc_Power(0);
                    TL_Close();
                    LCDDisplay4Lines(M4_____________Space, -1, ucLangFlag);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ICCardNGMessage_01], ucLangFlag);
                    Beep_EventSound(ERROR_TONE);
                    TIMER_WaitKeyPress1MS(1000);
                    sVirtualKey = BTKEY_CANCEL;
                }
                return;
            }
            break;
        case 4:
            app_SeletedAppTrmParameter(); // AfterTTA-L2
            gbEmvScTaskStep = 11;
            return;
        case 11:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>1.Build Candidate List.\r\n"));
            /*--------------------------------------------------------------*/
            if ((i = app_BuildCandidateList()) < 0) {
                gsc_Status(); // sispp 070305
                if (i == -3) {
                    if (pgsSC_STAT->pwON) gsc_Power(0);
                    TL_Close();
                    LCDDisplay4Lines(M4_____________Space, -1, ucLangFlag);
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ICCardNGMessage_01], ucLangFlag);
                    Beep_EventSound(ERROR_TONE);
                    TIMER_WaitKeyPress1MS(1000);
                    sVirtualKey = BTKEY_CANCEL;
                    return;
                }

                goto appEmvTaskEnd;
            }
            break;
        case 12:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>2.Application Selection.\r\n"));
            /*--------------------------------------------------------------*/
            if (app_ApplicationSelection() < 0) goto appEmvTaskEnd;
            app_SeletedAppTrmParameter(); // AfterTTA-L2
            break;
        case 13:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>3.Get Processing Options.\r\n"));
            /*--------------------------------------------------------------*/
            if ((i = app_GetProcessingOptions()) < 0) goto appEmvTaskEnd;
            else if (i > 0) {
                /*------------------------------------------------*/
                //DBGprt(("Geographic Restrictions applied!->"));
                //DBGprt(("Conditions of use not satisfied.\r\n"));
                /*------------------------------------------------*/
                //DBGprt(("Terminal deletes this application.\r\n"));
                /*------------------------------------------------*/
                //Select other ApplicationSelection()
                gbEmvScTaskStep = 12;
                return;
            }
            break;
        case 14:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>4.Read Application Data.\r\n"));
            /*--------------------------------------------------------------*/
            if (app_ReadApplicationData() < 0) goto appEmvTaskEnd;
            break;


        case 15:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\no>5.Offline Data Authentication.\r\n"));
            /*--------------------------------------------------------------*/
            if (app_OfflineDataAuthentication() <= -5) goto appEmvTaskEnd;
            break;
        case 16:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>6.Processing Restrictions.\r\n"));
            /*--------------------------------------------------------------*/
            app_ProcessRestrictions();

            isDetectCard = 2;
            sVirtualKey = BTKEY_ENTER;
            break;
        case 17:
            // Waiting 'Select account, enter amount'
            // -> gbEmvScTaskStep++
            return;
        case 18:
            if (st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY) {
                strcpy(Total_Amount, st_TrxnReqData.sz13Amount);
                gdwAmount = 0;
                for (i = 0; i < 12; i++) {
                    j = Total_Amount[i];
                    if ((j < 0x30) || (j > 0x39)) break;
                    gdwAmount = gdwAmount * 10L + (U32) (j - 0x30);
                }
                fnD642Bcd((U08 *) & gbTempBuf, gdwAmount, 12);
                pgbAppBufUpdate(T6n_TrmAmountAuthorised, 6, (U08 *) & gbTempBuf);
                j = sizeof (gdwAmount);
                for (i = 0; i < j; i++) gbTempBuf[i] = (gdwAmount >> (8 * (j - 1 - i))) & 0xFF;
                pgbAppBufUpdate(T4b_TrmAmountAuthorised, 6, (U08 *) & gbTempBuf);
            }

            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>7.Cardholder Verification.\r\n"));
            /*--------------------------------------------------------------*/
            if (app_CVMprocess() <= -5) goto appEmvTaskEnd;
            if (pgsTrmTVR->B3b3 == 1) { // 1 = Online PIN entered
                gbEmvScTaskStep = 19;
            } else {
                gbEmvScTaskStep = 25;
            }
            return;
        case 19:
            /*--------------------------------------------------------------*/
            // IF any pre_Authorizarion need, process at this step!
            /*--------------------------------------------------------------*/
            gbEmvScTaskStep = 25;
            return;
        case 25:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>8.Terminal Risk Management.\r\n"));
            /*--------------------------------------------------------------*/
            if (app_TRMprocess() < 0) goto appEmvTaskEnd;
            break;
        case 26:
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>9.Terminal Action Analysis.\r\n"));
            /*--------------------------------------------------------------*/
            if (app_TAAprocess() < 0) goto appEmvTaskEnd;
            break;
        case 27: // This step is fixed!
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>A.Card Action Analysis.\r\n"));
            /*--------------------------------------------------------------*/
            if (app_CAAprocess() < 0) goto appEmvTaskEnd;
            break;
        case 28:
            /*--------------------------------------------------------------*/
            // sispp 100429 SouthAfrica VISA (2CJ.047.00)
            // VISA ADVT User Guide Version 5.1 March 2009
            // Test Case 23 - pgsTrmTVR->B2b5
            // Test Case 31 - pgsTrmTVR->B3b8
            // Test Case 4  - gwTrmARC == TrmARC_Z1
            /*--------------------------------------------------------------*/
            /*
            if(pgsTrmTVR->B2b5 || pgsTrmTVR->B3b8 || gwTrmARC == TrmARC_Z1) {
                gbSaveTrxnRec = 0;
                gbEmvScTaskStep = 100;	// Completion
                break;
            }
             */
            /*--------------------------------------------------------------*/
            DBGprt(("\r\no>B. OnLineProcess.\r\n"));
            /*--------------------------------------------------------------*/
            break;
        case 29:
            /*--------------------------------------------------------------*/
            /*--------------------------------------------------------------*/
            if (app_OnLineProcess() < 0) goto appEmvTaskEnd;
            return;
        case 99: // This step is fixed!
            return;
        case 100: // This step is fixed!
            if (gbOnLineFlag) {
                TL_Open(0, gem_BaudRate);
            }
            break;
        case 101: // This step is fixed!
            /*--------------------------------------------------------------*/
            DBGprt(("\r\nM>C.Completion.\r\n"));
            /*--------------------------------------------------------------*/
            app_Completion();

            if (gbRefundFlag) {
                DBGprt(("Refund processing required.\r\n"));
                //------------------------------------------------------
                // CETECOM_FAIL [2CI.032.00]
                //------------------------------------------------------
                //STRDISP( LsTrxnResult );
                //isoDispTrxnResults(gu32ProcessingCode, 0x3531, 2000); // DECLINE, Wait 2sec
                //------------------------------------------------------
                /* Need to add fallowing... [2CA.054.00]genac2 declined
                Values for Cryptogram Information Data, ATC, Application Cryptogram,
                Issuer Application Data managed by the terminal and included in
                authorization or financial requests or batch data capture shall be in
                accordance with values sent back by the LT              */
                //------------------------------------------------------
                // PCodeRefund : It is system hidden process!
                //Lprintf(2, 0, (char *)&msg_tbl1[gbLangCode][141]);
                //WaitKeyInput();
                //------------------------------------------------------
                /*
                gbOnLineFlag=1; // OnLine process for Refund!
                isoRequestMsgBNK(PCodeRefund);
                gbEmvScTaskStep=99;
                MODEM_open();
                return;
                 */
            }
            break;
        default:
            goto appEmvTaskEnd;
    }

    if (gbEmvScTaskStep > 0) {
        gbEmvScTaskStep++;
        gSysTimer = TIME_BASE0;
        return;
    }

    /*--------------------------------------------------------------*/
appEmvTaskEnd:
    /*--------------------------------------------------------------*/
    //Smart Card Power Down
    if (pgsSC_STAT) { // sispp 20100525 T2CA_013.00
        DBGprt(("\r\nsispp - gsc_Power(0)\r\n"));
        gsc_Power(0);
    }
    // Close Serial Port
    if (gem_RS232open) TL_Close();

    if (pgbAppBuf != NULL) {
        DBGprt(("\r\n....Check & see pgbAppBuf[%d]....\r\n", giAppBufLen));
        DEBUG_DOL((pgbAppBuf, giAppBufLen));
        pgbAppBuf = NULL;
        giAppBufLen = 0;
    }
    if (pgbRspBuf != NULL) {
        pgbRspBuf = NULL;
        giRspBufLen = 0;
    }

    if (gbEmvScTaskStep == 102) { // Normal End
        gbEmvScTaskStep = 0;
        if (*pusServiceAddr == 0x5115 || *pusServiceAddr == 0x5205) {
            pusServiceAddr++;
            sVirtualKey = BTKEY_ENTER;
        } else if ((*pusServiceAddr & 0xF000) == 0x9000) {
            sVirtualKey = BTKEY_CANCEL;
        }
    } else {
        if (pgbPOSEntryMode != NULL) *pgbPOSEntryMode = 0x92; // unsuccessful IC read!
        PrintTask();
        if (gbEmvScTaskStep == 127) { // CANCEL key operation
            gbEmvScTaskStep = 0;
        } else
            if (gwSW1SW2 != 0x6A81) { // Application not blocked!
            gbEmvScTaskStep = -1; // Set FallBack
        } else { // Refund
            gbEmvScTaskStep = 0;
        }
    }
    gwModemWait = TIME_BASE0; // sispp060721

    if (pgsTrmTVR != NULL) pgsTrmTVR = NULL;
    if (pgsTrmTSI != NULL) pgsTrmTSI = NULL;

    return;
}


/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
int app_SeletedAppTrmParameter(void) {
    int pLen, nLen, nTag, oTag, i;
    U08 *pBuf;

    nLen = SelectedAID[0];
    if ((nLen < 5) || (nLen > 16)) { // Only 5-16 bytes
        pgcTrmDATA = (U08 *) FLASH8MB_NIBSS_TRMCONF;
        giTrmDATAsize = getSysDOLsize(pgcTrmDATA);
        return (0); // initial SeletedAppTrmParameter
    }
    for (i = 1; i < 64; i++) {
        gbNthMatch = i;
        if ((pLen = getDnL(pgcTrmDATA, 0, Tvb_TrmAID, &pBuf)) <= 0) return (0);
        if (memcmp((U08 *) & SelectedAID[1], pBuf, pLen) == 0) {
            if (pLen == nLen) break; // no multiple
            if ((pLen < nLen)&&(i > 2)) break; // partial...
        }
    }
    pBuf += pLen;
    giTrmDATAsize -= ((long) pBuf - (long) pgcTrmDATA);
    pgcTrmDATA = pBuf;
    pLen = giTrmDATAsize;
    oTag = 0;
    while (pLen > 0) {
        i = getTnL(pBuf, pLen, &nTag, &nLen);
        if (nTag != Tvb_TrmAID) { // If not Tvb_TrmAID
            if (oTag == 0) oTag = nTag;
            if (nTag == Tag_EOT4) break;
        } else if (oTag) { // If not successive Tvb_TrmAID
            // Restore SeletedAppTrmParameter bytes
            giTrmDATAsize = ((long) pBuf - (long) pgcTrmDATA);
            break;
        }
        i += nLen;
        pLen -= i;
        pBuf += i;
    }

    return (1); // use revised SeletedAppTrmParameter
}

#endif //#ifdef EMV_KERNEL

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
D64 app_getPANamounts(void) {
    D64 Amounts = 0.0;

#if 0
    /*Calculate total amount of samePAN in this BATCH. RSBON_CODE */
    pXRec = NULL;
    while (1) {
        if (isoGetPanRecords(&CardNo2[0]) < 0) break;
        if (pXRec->zzFlag != gczzFlag_z) break;
        Amounts += fnBcd2D64((U08 *) & pXRec->AmountTrxn, 12);
        pXRec--;
    }
    pXRec = NULL;
#endif

    return (Amounts);
}

int isoStrPANnExpDate(char *pPAN) {
    char i, j, cd;

    i = j = 1;
    while (1) {
        if ((cd = CardNo2[i]) == 0) break;
        if ((cd == 0x3F) || (cd == '=')) break;
        pPAN[j++] = CardNo2[i++];
    }
    pPAN[0] = (j - 1);
    pPAN[j++] = 0; // Null string
    while (1) {
        if ((CardNo2[i] >= '0') && (CardNo2[i] <= '9')) break;
        i++;
    }
    pPAN[j++] = CardNo2[i++];
    pPAN[j++] = CardNo2[i++];
    pPAN[j++] = CardNo2[i++];
    pPAN[j++] = CardNo2[i++];
    pPAN[j] = 0; // Null string

    return ((int) pPAN[0]);
}

/*--------------------------------------------------------------------------*/
int app_InitReferralCall(void) {
    LCDDisplay4Lines(M4_____________Space, -1, ucLangFlag);
    Lprintf(0, 0, (char *) LCD_MSG_TBL1[ucLangFlag][M1CallYourBank_00001]); // "CALL YOUR BANK  ",
    isoStrPANnExpDate((char *) &CardNo1[0]);
    Lprintf(1, 0, (char *) &CardNo1[1]); // Card No Display
    if (CardNo1[0] > 16) {
        Lprintf(2, 0, (char *) &CardNo1[17]);
    }
    Lprintf(3, 0, (char *) LCD_MSG_TBL1[ucLangFlag][M1CancelOrEnter_0001]); // "CANCEL OR ENTER ",
    LCD_BLINKING(CURBOX_ON, 0, 0, 16);

    APIprt(("PAN=%s", (char *) &CardNo1[1]));
    while (1) {
        dequeue_key();
        if (gbKeyVal == BTKEY_ENTER) break;
        else if (gbKeyVal == BTKEY_CANCEL) return (-1);
    }

    return (0);
}

int OnLineProcessSub(int iReferral) {
    int key;

    if (iReferral) {
        APIprt(("Referral Processing!\r\n"));
        if (app_InitReferralCall() < 0) return (-1);
        LCDDisplay4Lines(M4ReferralCall_00001, -1, ucLangFlag);
        LCD_BLINKING(CURBOX_ON, 0, 0, 16);
        gbReferralFlag = BTKEY_1;
        while (1) {
            key = dequeue_key();
            if ((key >= BTKEY_1) && (key <= BTKEY_3)) {
                if (gbReferralFlag != key) {
                    LCD_BLINKING(CURBOX_OFF, (gbReferralFlag - 1), 0, 16);
                    LCD_BLINKING(CURBOX_ON, (key - 1), 0, 16);
                    gbReferralFlag = key;
                }
            } else if (key == BTKEY_ENTER) {
                if (gbReferralFlag == BTKEY_1) { //"    goto ON_LINE", //124
                    gwTrmARC = 0; //shall not set ARC book4 2.5.2.1
                    gbTempBuf[0] = (gwTrmARC >> 8) & 0xFF;
                    gbTempBuf[1] = gwTrmARC & 0xFF;
                    pgbAppBufUpdate(T2a_ARC, 2, gbTempBuf);
                    gbOnLineFlag = 1;
                } else if (gbReferralFlag == BTKEY_2) { //" OffLINE APPROVE", //125
                    gwResponseCode = 0x3030;
                } else if (gbReferralFlag == BTKEY_3) { //" OffLINE DECLINE", //126
                    gwResponseCode = 0x3531;
                }
                break;
            } else if (key == BTKEY_CANCEL) {
                return (-1);
            }
        }
    }

    if (gbOnLineFlag == 1) {
        LCDDisplay4Lines(M4OnlineProc_0000001, -1, ucLangFlag);
        gbEmvScTaskStep = 99;
        sVirtualKey = BTKEY_ENTER;
        // MODEM_open();  // for none predialing
        // Start Communication...
        return (0);
    } else {
        LCDDisplay4Lines(M4OfflineProc_000001, -1, ucLangFlag);
        gbEmvScTaskStep = 100;
    }

    return (0);
}

void CompletionSub() {
    U08 *pAdd;
    int key, pLen;

    APIprt(("Isseur Referral!\r\n"));
    if (app_InitReferralCall() < 0); //return(-1);
    LCDDisplay4Lines(M4IssuerReferral_001, -1, ucLangFlag);

    LCD_BLINKING(CURBOX_ON, 1, 0, 16);
    pLen = BTKEY_2;
    while (1) {
        key = dequeue_key();
        if ((key >= BTKEY_2) && (key <= BTKEY_3)) {
            if (pLen != key) {
                LCD_BLINKING(CURBOX_OFF, (pLen - 1), 0, 16);
                LCD_BLINKING(CURBOX_ON, (key - 1), 0, 16);
                pLen = key;
            }
        } else if (key == BTKEY_ENTER) {
            if (pLen == BTKEY_2) { //"    APPROVE     ", //125
                gwResponseCode = 0x3030;
            } else
                if (pLen == BTKEY_3) { //"    DECLINE     ", //126
                gwResponseCode = 0x3531;
            }
            //------------------------------------------------
            // Change ResponseCode for ISSUER REFERRAL.
            //------------------------------------------------
            if (getDnL(pgcTrmDATA, 0, T2a_ARC, &pAdd) == 2) {
                pAdd[0] = (gwResponseCode >> 8) & 0xFF;
                pAdd[1] = (gwResponseCode & 0xFF);
            }
            break;
        }
    }
}

int app_ApplicationSelection(void) {
    U08 *pAdd;
    int i, n, sNum, key;

    if (app_makeApplicationList() == -1)
        return -1;

    /* ---------------------- */
    // Display in Priority Order
    /* ---------------------- */
    LCDDisplay4Lines(M4PleaseSelect_00001, -1, ucLangFlag);
    pAdd = (U08 *) & gbDestBuf;
    i = n = sNum = 0;
    while ((i++) < gbIccAIDno) {
        if (!pAdd[61]) { // No deleted
            APIprt(("\t[%2X]Priority[%s]sorted[%d]\r\n", pAdd[60], (char *) &pAdd[32], pAdd[62]));
            if (pAdd[62] <= 4) Lprintf((pAdd[62] - 1), 0, (char *) &pAdd[32]);
            if ((pAdd[60] & 0x80) == 0) n = 1; // n=1 : Select Option Terminal_AUTO
            sNum++; // sNum: Display Lines
        }
        pAdd += 64;
    }
    /* ---------------------- */
    // Select by Cardholder
    /* ---------------------- */
    if ((gbIccAIDno > 1) || (n == 0)) { // Select Option is not Terminal_AUTO
        if (SelectedAID[0] != 0) { // not first selection
            i = 3;
            if (sNum < 3) i = 2;
            Lprintf(i, 0, (char *) "TRY AGAIN       "); //"TRY AGAIN       ", // 87
        }
        n = 1;
        LCD_BLINKING(CURBOX_ON, 0, 0, 16);
        while (1) {
            key = dequeue_key();
            if ((key > BTKEY_0) && (key <= sNum)) {
                if (n != key) {
                    if (sNum > 4 && (((n - 1) ^ (key - 1)) & 0x04)) { // Change Page 
                        LCDDisplay4Lines(M4PleaseSelect_00001, -1, ucLangFlag);
                        i = 0;
                        pAdd = (U08 *) & gbDestBuf;
                        while ((i++) < sNum) {
                            if (!pAdd[61]) { // No deleted
                                if ((key > 0x04 && pAdd[62] > 4) || (key <= 0x04 && pAdd[62] <= 4)) {
                                    Lprintf((pAdd[62] - 1) & 0x03, 0, (char *) &pAdd[32]);
                                }
                            }
                            pAdd += 64;
                        }
                    }
                    LCD_BLINKING(CURBOX_OFF, (n - 1) & 0x03, 0, 16);
                    LCD_BLINKING(CURBOX_ON, (key - 1)&0x3, 0, 16);
                    n = key;
                }
            } else if (key == BTKEY_ASTERISK) {
                if (sNum > 4) sVirtualKey = BTKEY_1;
            } else if (key == BTKEY_SHARP) {
                if (sNum > 4) sVirtualKey = BTKEY_5;
            } else if (key == BTKEY_ENTER) break;
            else if (key == BTKEY_CANCEL) return (-1);

        }
    }
    /* ---------------------- */
    APIprt(("ApplicationSelected[%d/%d]\r\n", n, sNum));
    /* ---------------------- */
    pAdd = (U08 *) & gbDestBuf;
    i = 0;
    while ((i++) < gbIccAIDno) {
        if (pAdd[62] == n) { // sort number match?
            memcpy((U08 *) & SelectedAID[0], (U08 *) & pAdd[0], (pAdd[0] + 1));
            LCDDisplay4Lines(M4CardReading_000001, -1, ucLangFlag);
            Lprintf(0, 0, (char *) &pAdd[32]);
            return (0);
        }
        pAdd += 64;
    }

    return (-1);
}

void InitEmvLib() {
    int i;
    char temp[33];

    strcpy(Total_Amount, "0");

    memset(CardAcceptorMerchantID, 0x00, sizeof (CardAcceptorMerchantID));
    i = strlen(pstParams->szMerchantID);
    if (i > 0 && i < 17) {
        strcpy(CardAcceptorMerchantID, pstParams->szMerchantID);
    }
    memset(CardAcceptorTerminalID, 0x00, sizeof (CardAcceptorTerminalID));
    i = strlen(st_POSSetupInfo.sz9TerminalID);
    if (i > 0 && i < 9) {
        strcpy(CardAcceptorTerminalID, st_POSSetupInfo.sz9TerminalID);
    }
    memcpy(TrmAcquirerID, "\x00\x00\x00\x54\x13\x33", 6);
    memset(POSSerialNr, 0x00, sizeof (POSSerialNr));
    if (GET_PROD_ID(temp) == 0) { // BNI51111200001
        strcpy(POSSerialNr, temp);
    } else {
        i = strlen(st_POSSetupInfo.sz9TerminalID);
        if (i > 0 && i < 9) {
            strcpy(POSSerialNr, st_POSSetupInfo.sz9TerminalID);
        }
    }
    memcpy(TrmCapa, "\xE0\xF8\xC0", 3);
    memcpy(TrmCapaAdditional, "\xE0\x00\xB0\xA0\x01", 5);
    TrmType = 0x22;
    TrmTCC = 'R';
    memcpy(TrmMCC, "\x07\x42", 2);
    TrmForceOnLine = 0x00;
    TrmL2TTAmode = 0x00;

    emvref.TraceNr = &TraceNr;
    emvref.SelectedAID = SelectedAID;
    emvref.CardAcceptorMerchantID = CardAcceptorMerchantID;
    emvref.CardAcceptorTerminalID = CardAcceptorTerminalID;
    emvref.TrmAcquirerID = TrmAcquirerID;
    emvref.POSSerialNr = POSSerialNr;
    emvref.TrmCapa = TrmCapa;
    emvref.TrmCapaAdditional = TrmCapaAdditional;
    emvref.TrmType = &TrmType;
    emvref.TrmTCC = &TrmTCC; //Transaction Category Codes(EUROPAY only)
    emvref.TrmMCC = TrmMCC; //Merchant Category Code(Card acceptor business code:ISO)
    emvref.TrmForceOnLine = &TrmForceOnLine;
    emvref.TrmL2TTAmode = &TrmL2TTAmode;
    emvref.SvcCode = SvcCode;
    emvref.CardHolderName = CardHolderName;

    //	SetTrmCAPK((U08 *)gcTrmCAPK);
    //	SetTrmExcepList((U08 *)gcTrmExcepList);
    //	SetTrmRevocList((U08 *)gcTrmRevocList);
    SetTrmCAPK((U08 *) FLASH8MB_NIBSS_TRMCAPK);
    SetTrmExcepList((U08 *) FLASH8MB_NIBSS_EXCEPLIST);
    SetTrmRevocList((U08 *) FLASH8MB_NIBSS_REVOCLIST);
    SetTrmARC(0x5931, 0x5A31, 0x5932, 0x5A32, 0x5933, 0x5A33);
}

void EMVDISP(int no) {
    switch (no) {
        case LsEMVreading:
            LCDDisplay4Lines(M4CardReading_000001, -1, ucLangFlag);
            break;
        case LsEnterPIN:
            LCDDisplay4Lines(M4PleaseEnterPIN_001, -1, ucLangFlag);
            break;
        case LsEnterOnlinePIN:
            LCDDisplay4Lines(M4EnterOnlinePIN_001, -1, ucLangFlag);
            break;
        case LsEnterOfflinePIN:
            LCDDisplay4Lines(M4EnterOfflinePIN_01, -1, ucLangFlag);
            break;
        case LsPINtryLast:
            LCDDisplay4Lines(M4PINTryLast_0000001, -1, ucLangFlag);
            break;
        case LsPIN_OK:
            LCDDisplay4Lines(M4PINOK_000000000001, -1, ucLangFlag);
            break;
        case LsPINincorrect:
            LCDDisplay4Lines(M4IncorrectPIN_00001, -1, ucLangFlag);
            break;
    }
}


/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
int isoCardNo22Track2Data(U08 *pTrac) {
    int i, j, cn2Len;

    cn2Len = CardNo2[0];
    if (cn2Len > 37) cn2Len = 37;
    pTrac[0] = ((cn2Len / 10) << 4) | (cn2Len % 10); //cnL2 format

    i = j = 1;
    while (1) { //convert an->cn format
        if (CardNo2[i] == 0) break;
        if (i & 1) {
            pTrac[j] = (CardNo2[i] << 4);
        } else {
            pTrac[j] |= (CardNo2[i] & 0x0F);
            j++;
        }
        if ((i++) >= cn2Len) break;
    }
    if ((i & 1) == 0) {
        pTrac[j] |= 0x0F;
        i++;
        j++;
    }

    if (cn2Len <= 20) { // TYPING NOTATATION:MAX[19+1]
        pTrac[j++] = 0xDD;
        i += 2;
        pTrac[j] = (CardNo2[i++] << 4);
        pTrac[j] |= (CardNo2[i++]& 0xF);
        j++;
        pTrac[j] = (CardNo2[i++] << 4);
        pTrac[j] |= (CardNo2[i++]& 0xF);
        j++;
    }

    //DBGprt(("isoCardNo22Track2Data")); DEBUG_BUF((pTrac, j));
    return (j); //Bytes including Length in pTrac[0]
}

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
int isoTrack2Data2CardNo2(U08 *pTrac, int nByte, U08 *pCard) {
    int i = 1;

    if (nByte <= 0) {
        nByte = (*pTrac >> 4)*10 + (*pTrac & 0x0F); //cnL2 format
        pTrac++;
    }
    if (nByte > 37) nByte = 37;
    pCard[0] = nByte;
    while (i <= nByte) { //convert cn->an format
        pCard[i++] = (*pTrac >> 4) + 0x30;
        pCard[i++] = (*pTrac & 0xF) + 0x30;
        pTrac++;
    }

    if (pCard[0] <= 20) { // TYPING NOTATATION:MAX[19+1]
        pCard[i++] = '='; // PAD string
        pCard[i++] = '='; // PAD string
        pTrac++;
        pCard[i++] = (*pTrac >> 4) + 0x30; // YY
        pCard[i++] = (*pTrac & 0xF) + 0x30;
        pTrac++;
        pCard[i++] = (*pTrac >> 4) + 0x30; // MM
        pCard[i++] = (*pTrac & 0xF) + 0x30;
    }
    pCard[i] = 0;
    //DBGprt(("isoTrack2Data2CardNo2[%d]=%s\r\n", pCard[0], &pCard[1]));

    return (i);
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

extern int GemSlotNo;

void Wait1MS(unsigned short time1ms) {
    TIMER_Wait1MS(time1ms);
}

void TL_SetSlotNo(U08 slot_no) {
    GemSlotNo = slot_no + 1;
}

U08 TL_GetSlotNo() {
    return GemSlotNo - 1;
}


const U08 gcTrmCAPK[] = {
    /* Tag_EOT4(tEOF) */ Tag_EOT4, 0x00,
};

const U08 gcTrmExcepList[] = {//(Terminal Exception List)
    // /* Tvc_PAN        */	0x5A,       8, 0x54,0x13,0x33,0x90,0x00,0x00,0x15,0x96,
    /* Tag_EOT4(tEOF) */ Tag_EOT4, 0x00,
};

const U08 gcTrmRevocList[] = {//(Terminal Revocation List,RID[5],CAPKI[1],CSN[3])
    // /* Tvb_TrmCAPK    */	0x18,       9, 0xA0,0x00,0x00,0x00,0x04,0x96,0x12,0x34,0x56,
    /* Tag_EOT4(tEOF) */ Tag_EOT4, 0x00,
};

const U08 gcTrmDATA[] = {// This initialize TrmCONFx.DAT file.
    /* Tag_EOT4(tEOF)              */ Tag_EOT4, 0x00,
};
