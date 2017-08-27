
#include "system.h"
#include "extern.h"


//#define PAUSE_DEBUG


//char FlashWriteBuf[65536];
char FlashWriteBuf[131072];
_st_POSSetupInfo_ st_POSSetupInfo; // POS setup information buffer
_st_POSSetupInfo_ *stpFlashPOSSetupInfo; // Pointer to POS setup information of flash ROM
_tPOS_UTIL_INFO tPOSUtilInfo; // POS Util information
_tPOS_UTIL tPOSUtilBuf; // POS Util buffer
int iFlashMemorySize;
int iFlashTrxnLogSectorNo;
long lFlashSectorSize;


void ConvertOldPOSSetupInfoToNew(void);
void LoadPOSSetupInfo(void);
void SetInitialPOSSetupInfo(void);
void InitializePOSSetupInfo(void);
void ResetPOSSetupInfo(void);
void ResetMerchantPassword(void);
void WritePOSSetupInfo(void);
BOOL GetTcpIPLocalParameterChange(void);
void WriteTransactionLog(char *dst);
void EraseAllTransactionLog(void);
int LoadFlashPOSUtilInfo(void);
void WritePOSUtil(void);
#ifdef USER_DEBUG
void PauseUntilEnterkeyPressed(void);
#endif


// Load POS Setup Information

void LoadPOSSetupInfo(void) {
#ifdef USER_DEBUG
    Rprintf("\r\nLoadPOSSetupInfo()\r\n");
#endif

    if (stpFlashPOSSetupInfo->usMagicNo != POS_SETUP_INFO_MAGIC_NO ||
            stpFlashPOSSetupInfo->usSuffix != POS_SETUP_INFO_SUFFIX) {
        InitializePOSSetupInfo();
    } else {
        memcpy((char *) &st_POSSetupInfo, (char *) stpFlashPOSSetupInfo, sizeof (st_POSSetupInfo));
    }
}

// Set Initial POS Setup Information

void SetInitialPOSSetupInfo(void) {
    int i, j;

#ifdef USER_DEBUG
    Rprintf("\r\nSetInitialPOSSetupInfo()\r\n");
#endif

    if (iFlashMemorySize < 16) {
        stpFlashPOSSetupInfo = (_st_POSSetupInfo_ *) FLASH8MB_POS_SETUP_INFO_START_ADDR;
    } else {
        stpFlashPOSSetupInfo = (_st_POSSetupInfo_ *) FLASH16MB_POS_SETUP_INFO_START_ADDR;
    }

    memset((char *) &st_POSSetupInfo, 0x00, sizeof (st_POSSetupInfo));

    st_POSSetupInfo.usMagicNo = POS_SETUP_INFO_MAGIC_NO;
    st_POSSetupInfo.usVersionNo = POS_SETUP_INFO_VERSION_NO;
    strcpy(st_POSSetupInfo.sz9InfoDate, sz9POSSetupInfoDate);

    //strcpy(st_POSSetupInfo.sz9TerminalID, "37000100");
    //strcpy(st_POSSetupInfo.sz16MerchantID, "111111118");

    strcpy(st_POSSetupInfo.sz13MasterPIN, "0000");
    strcpy(st_POSSetupInfo.sz13MerchantPIN, "0000");
    strcpy(st_POSSetupInfo.sz13CashierPIN, "0000");

    st_POSSetupInfo.ucBeep = 1;
    st_POSSetupInfo.ucLCDContrast = 25;

    st_POSSetupInfo.ucModemSpeed = 1; // 0:1200bps, 1:2400bps
    st_POSSetupInfo.ucDialingTimeout = 20;
    st_POSSetupInfo.ucCommTimeout = 60;
    strcpy(st_POSSetupInfo.sz5CallHomeInterval, "1440"); // 24hour
    //st_POSSetupInfo.ucPABXUse = 1;
    //strcpy(st_POSSetupInfo.sz6PABXCode, "9");
    //st_POSSetupInfo.ucCityUse = 1;
    //strcpy(st_POSSetupInfo.sz10CityCode, "0029821");

    // Transaction telephone number (0 - 7)
    //strcpy(st_POSSetupInfo.sz17TrxnTelNo[0], "22257111");		// Real Telephone Number
    //strcpy(st_POSSetupInfo.sz17TrxnTelNo[1], "22257116");
    //strcpy(st_POSSetupInfo.sz17TrxnTelNo[2], "22257121");
    //strcpy(st_POSSetupInfo.sz17TrxnTelNo[3], "22222652");		// Test Telephone Number

    // Terminal Management System(TMS) telephone number (0 - 7)
    //strcpy(st_POSSetupInfo.sz17TMSTelNo[0], "22257111");
    //strcpy(st_POSSetupInfo.sz17TMSTelNo[1], "22257116");
    //strcpy(st_POSSetupInfo.sz17TMSTelNo[2], "22257121");

    // Local parameters for ethernet
    //strcpy(st_POSSetupInfo.sz16LocalIPAddress, "211.63.70.185");
    //strcpy(st_POSSetupInfo.sz16SubnetMask, "255.255.255.224");
    //strcpy(st_POSSetupInfo.sz16Gateway, "211.63.70.161");
    //strcpy(st_POSSetupInfo.sz6LocalPortNo, "12345");
    strcpy(st_POSSetupInfo.sz5LocalTimeout, "20");

    // Transaction parameters for ethernet (0 - 1)
    //strcpy(st_POSSetupInfo.sz16TrxnServerIP[0], "211.63.70.163");
    //strcpy(st_POSSetupInfo.sz6TrxnServerPortNo[0], "12345");

    // Terminal Management System(TMS) parameters for ethernet (0 - 1)
    //strcpy(st_POSSetupInfo.sz16TMSServerIP[0], "211.63.70.163");
    //strcpy(st_POSSetupInfo.sz6TMSServerPortNo[0], "12345");

    strcpy(st_POSSetupInfo.sz4MaxOfflineTrxnNo, "0"); // Maximum offline transaction number of consequent buys for one terminal
    strcpy(st_POSSetupInfo.sz13MaxOfflineTrxnAmount, "0"); // Maximum offline transaction amount of consequent buys for one terminal

    strcpy(st_POSSetupInfo.sz3NII, "01");

    st_POSSetupInfo.ucGsmDialingTimeout = 40;
    strcpy(st_POSSetupInfo.sz10GsmCityCode, "021");
    strcpy(st_POSSetupInfo.sz10GsmTMSCityCode, "021");
    strcpy(st_POSSetupInfo.sz10GsmEODCityCode, "021");
    strcpy(st_POSSetupInfo.sz10GsmBListCityCode, "021");

    st_POSSetupInfo.ucPreDialingFlag = 1;

    st_POSSetupInfo.ucAutoTMSActiveFlag = 0;

    st_POSSetupInfo.usSuffix = POS_SETUP_INFO_SUFFIX;

#if 0 // sispp 20111008
    ucEthernetInitializeFlag = 0;
#endif
}

// Initialize POS Setup Information

void InitializePOSSetupInfo(void) {
#ifdef USER_DEBUG
    Rprintf("\r\nInitializePOSSetupInfo()\r\n");
#endif

    SetInitialPOSSetupInfo();
    WritePOSSetupInfo();
}

// Reset POS Setup Information

void ResetPOSSetupInfo(void) {
    char temp[17];

#ifdef USER_DEBUG
    Rprintf("\r\nResetPOSSetupInfo()\r\n");
#endif

    memcpy(temp, st_POSSetupInfo.sz13MasterPIN, sizeof (st_POSSetupInfo.sz13MasterPIN));
    SetInitialPOSSetupInfo();
    strcpy(st_POSSetupInfo.sz13MasterPIN, temp);
    strcpy(st_POSSetupInfo.sz13MerchantPIN, temp);
    strcpy(st_POSSetupInfo.sz13CashierPIN, temp);
    WritePOSSetupInfo();
}

// Reset Merchant Password

void ResetMerchantPassword(void) {
#ifdef USER_DEBUG
    Rprintf("\r\nResetMerchantPassword()\r\n");
#endif

    strcpy(st_POSSetupInfo.sz13MerchantPIN, "0000");

    WritePOSSetupInfo();
}

// Write POS setup information to flash ROM

void WritePOSSetupInfo(void) {
    int i, ret, gsm_init, gsm_power_off;

    if (memcmp((char *) stpFlashPOSSetupInfo, (char *) &st_POSSetupInfo, sizeof (st_POSSetupInfo))) {
#ifdef USER_DEBUG
        Rprintf("\r\nWritePOSSetupInfo()\r\n");
#endif

#if 0 // sispp 20111008
        if (GetTcpIPLocalParameterChange()) {
            ucEthernetInitializeFlag = 0;
        }
#endif

        gsm_init = 0;
        gsm_power_off = 0;
        if (st_POSSetupInfo.ucComDevice != GSM_MODEM) {
            if (stpFlashPOSSetupInfo->ucComDevice == GSM_MODEM) {
                gsm_power_off = 1;
            }
        } else if (stpFlashPOSSetupInfo->ucComDevice != GSM_MODEM) {
            gsm_init = 1;
        }

        FLASH_WRITE((char *) stpFlashPOSSetupInfo, sizeof (st_POSSetupInfo), (char *) &st_POSSetupInfo);
        // Reload Pos setup information from flash
        memcpy((char *) &st_POSSetupInfo, (char *) stpFlashPOSSetupInfo, sizeof (st_POSSetupInfo));

        if (gsm_power_off) {
            GprsPowerOff();
        } else if (gsm_init) {
            GprsModuleInitialize();
        }
#if 0 // sispp 20111008
        HiSpeedModemReset();
#endif
    }
}

BOOL GetTcpIPLocalParameterChange(void) {
    if (strcmp(st_POSSetupInfo.sz16LocalIPAddress, stpFlashPOSSetupInfo->sz16LocalIPAddress)) {
        return TRUE;
    }
    if (strcmp(st_POSSetupInfo.sz16SubnetMask, stpFlashPOSSetupInfo->sz16SubnetMask)) {
        return TRUE;
    }
    if (strcmp(st_POSSetupInfo.sz16Gateway, stpFlashPOSSetupInfo->sz16Gateway)) {
        return TRUE;
    }
    if (strcmp(st_POSSetupInfo.sz6LocalPortNo, stpFlashPOSSetupInfo->sz6LocalPortNo)) {
        return TRUE;
    }
    if (strcmp(st_POSSetupInfo.sz5LocalTimeout, stpFlashPOSSetupInfo->sz5LocalTimeout)) {
        return TRUE;
    }
    return FALSE;
}

// Write Transaction Log

void WriteTransactionLog(char *dst) {
#ifdef USER_DEBUG
    Rprintf("\r\nWriteTransactionLog(%p)\r\n", dst);
#endif

    FLASH_WRITE((char *) dst, sizeof (st_TrxnLog), (char *) &st_TrxnLog);
}

// Erase All Transaction Log

void EraseAllTransactionLog(void) {
    int i;
    char *ptr;

    if (iFlashMemorySize < 16) {
        ptr = (char *) FLASH8MB_TRANSACTION_LOG_START_ADDR;
    } else {
        ptr = (char *) FLASH16MB_TRANSACTION_LOG_START_ADDR;
    }

    for (i = 0; i < iFlashTrxnLogSectorNo; i++) {
        if (!MEMLIB_GetFlash1SectorBlankStatus(ptr)) {
            FLASH_SECTOR_ERASE(ptr);
#ifdef USER_DEBUG
            if (!MEMLIB_GetFlash1SectorBlankStatus(ptr)) {
                Rprintf("E> Erase Error\r\n");
            } else {
                Rprintf("Erased\r\n");
            }
#endif
        }
        ptr += lFlashSectorSize;
    }
}

int LoadFlashPOSUtilInfo(void) {
    int i, min_index, max_index;
    char *ptr;
    _tPOS_UTIL *info;

#ifdef USER_DEBUG
    Rprintf("\r\n");
    Rprintf("LoadFlashPOSUtil()\r\n");
#endif
    tPOSUtilInfo.lMinInfoAddr = FLASH16MB_POS_UTIL_INFO_START_ADDR;
    tPOSUtilInfo.lMaxInfoAddr = tPOSUtilInfo.lMinInfoAddr + (((long) FLASH16MB_POS_UTIL_INFO_MAX_RECORD_CNT - 1)*(long) (sizeof (_tPOS_UTIL)));
#ifdef USER_DEBUG
    Rprintf("tPOSUtilInfo.lMinInfoAddr = 0x%08lX\r\n", tPOSUtilInfo.lMinInfoAddr);
    Rprintf("tPOSUtilInfo.lMaxInfoAddr = 0x%08lX\r\n", tPOSUtilInfo.lMaxInfoAddr);
#endif

    min_index = 10000;
    max_index = 0;
    info = (_tPOS_UTIL *) tPOSUtilInfo.lMinInfoAddr;
    for (i = 0; i < FLASH16MB_POS_UTIL_INFO_MAX_RECORD_CNT; i++) {
        if (info->usMagicNo == FLASH16MB_POS_UTIL_INFO_MAGIC_NO && info->usSuffix == FLASH16MB_POS_UTIL_INFO_SUFFIX) {
            // Get minimum POS Util index
            if (info->usIndex < min_index) {
                min_index = info->usIndex;
                // Set the pointer of the first POS Util to this pointer
                tPOSUtilInfo.ptFirstLog = info;
            }
            // Get maximum POS Util index
            if (info->usIndex > max_index) {
                max_index = info->usIndex;
                // Set the pointer of the last POS Util to this pointer
                tPOSUtilInfo.ptLastLog = info;
            }
        }
        info++;
    }

#ifdef USER_DEBUG
    Rprintf("min_index = %d\r\n", min_index);
    Rprintf("max_index = %d\r\n", max_index);
#endif
    // No POS Util or POS Util format is incorrect
    if (max_index <= 0 || max_index > 9999 || min_index <= 0 || min_index > 9999) {
#ifdef USER_DEBUG
        Rprintf("No POS Util\r\n");
#endif
        // erase sectors of POS Util for fast writing
        ptr = (char *) FLASH16MB_POS_UTIL_INFO_START_ADDR;
        for (i = 0; i < FLASH16MB_POS_UTIL_INFO_MAX_SECTOR; i++) {
            if (MEMLIB_GetFlash1SectorBlankStatus(ptr) == 0) {
                FLASH_SECTOR_ERASE(ptr);
            }
            ptr += lFlashSectorSize;
        }

        tPOSUtilInfo.ptFirstLog = (_tPOS_UTIL *) tPOSUtilInfo.lMinInfoAddr;
        tPOSUtilInfo.ptLastLog = tPOSUtilInfo.ptFirstLog;
        tPOSUtilInfo.ptSavingLog = tPOSUtilInfo.ptFirstLog;
        tPOSUtilInfo.usUtilIndex = 0;

        // Initialize the POS Util
        memset((char *) &tPOSUtilBuf, 0x00, sizeof (tPOSUtilBuf));
        tPOSUtilBuf.usMagicNo = FLASH16MB_POS_UTIL_INFO_MAGIC_NO;
        tPOSUtilBuf.usVersion = FLASH16MB_POS_UTIL_INFO_VERSION;
        tPOSUtilBuf.usIndex = tPOSUtilInfo.usUtilIndex;
        tPOSUtilBuf.usBatchNo = 0;
        tPOSUtilBuf.usSeqNo = 0;
        tPOSUtilBuf.ulLastCallHomeTime = 0;

        tPOSUtilBuf.usSuffix = FLASH16MB_POS_UTIL_INFO_SUFFIX;
        WritePOSUtil();

        tPOSUtilInfo.ptSavingLog++;
        tPOSUtilInfo.usUtilIndex = tPOSUtilBuf.usIndex;
    } else {
        // POS Util index is reset because it is over 9999
        if ((max_index - min_index) >= FLASH16MB_POS_UTIL_INFO_MAX_RECORD_CNT) {
#ifdef USER_DEBUG
            Rprintf("POS Util index is reset because it is over 9999\r\n");
#endif
            min_index = 10000;
            max_index = 0;
            info = (_tPOS_UTIL *) tPOSUtilInfo.lMinInfoAddr;
            for (i = 0; i < FLASH16MB_POS_UTIL_INFO_MAX_RECORD_CNT; i++) {
                if (info->usMagicNo == FLASH16MB_POS_UTIL_INFO_MAGIC_NO && info->usSuffix == FLASH16MB_POS_UTIL_INFO_SUFFIX) {
                    // Get minimum POS Util index
                    if (info->usIndex >= FLASH16MB_POS_UTIL_INFO_MAX_RECORD_CNT && info->usIndex < min_index) {
                        min_index = info->usIndex;
                        // Set the pointer of the first POS Util to this pointer
                        tPOSUtilInfo.ptFirstLog = info;
                    }
                    // Get maximum POS Util index
                    if (info->usIndex < FLASH16MB_POS_UTIL_INFO_MAX_RECORD_CNT && info->usIndex > max_index) {
                        max_index = info->usIndex;
                        // Set the pointer of the last POS Util to this pointer
                        tPOSUtilInfo.ptLastLog = info;
                    }
                }
                info++;
            }
        }

        tPOSUtilInfo.ptSavingLog = tPOSUtilInfo.ptLastLog + 1;
        // Saving POS Util address is great than maximum POS Util address
        if ((long) tPOSUtilInfo.ptSavingLog > tPOSUtilInfo.lMaxInfoAddr) {
#ifdef USER_DEBUG
            Rprintf("Saving POS Util address is great than maximum POS Util address\r\n");
#endif
            tPOSUtilInfo.ptSavingLog = (_tPOS_UTIL *) tPOSUtilInfo.lMinInfoAddr;
        }

        // if the saving log address is the start address of a sector, erase this sector for fast writing
        if (((long) tPOSUtilInfo.ptSavingLog % lFlashSectorSize) == 0) {
            ptr = (char *) ((long) tPOSUtilInfo.ptSavingLog);
            if (MEMLIB_GetFlash1SectorBlankStatus(ptr) == 0) {
                FLASH_SECTOR_ERASE(ptr);
            }
        }

        tPOSUtilInfo.usUtilIndex = max_index;
    }

#ifdef USER_DEBUG
    Rprintf("\r\n");
    Rprintf("Index MinLog   MaxLog   FirstLog LastLog  SavingLog\r\n");
    Rprintf("%04d  ", tPOSUtilInfo.usUtilIndex);
    Rprintf("%08lX ", tPOSUtilInfo.lMinInfoAddr);
    Rprintf("%08lX ", tPOSUtilInfo.lMaxInfoAddr);
    Rprintf("%08lX ", (long) tPOSUtilInfo.ptFirstLog);
    Rprintf("%08lX ", (long) tPOSUtilInfo.ptLastLog);
    Rprintf("%08lX  ", (long) tPOSUtilInfo.ptSavingLog);
    Rprintf("\r\n");
    Rprintf("\r\n");
#endif

    return 0;
}

void WritePOSUtil(void) {
#ifdef USER_DEBUG
    Rprintf("\r\n");
    Rprintf("WritePOSUtil()\r\n");
#endif
    tPOSUtilBuf.usIndex++;
    if (tPOSUtilBuf.usIndex > 9999) {
        tPOSUtilBuf.usIndex = 1;
    }

    // Write POS util
    FLASH_WRITE((char *) tPOSUtilInfo.ptSavingLog, sizeof (_tPOS_UTIL), (char *) &tPOSUtilBuf);
}

#ifdef USER_DEBUG

void PauseUntilEnterkeyPressed(void) {
    int i;

    Rprintf("Press <ENTER> key\r\n");
    while (1) {
        i = KEYSCAN() & 0xFF;
        if (i == BTKEY_ENTER) {
            break;
        }
    }
}
#endif

APPLIST stAppList[MAX_APPLIST_CNT];
APPLIST *pstAppList;
FUNCLIST *pstFuncList;
EFTPARAMS stEftParams;
MASTERKEY stMasterKey;
MASTERKEY *pstMasterKey;
SESSIONKEY stSessionKey;
PARAMS stParams;
PARAMS *pstParams;
BINTABLE stBinTable[MAX_BINTABLE_CNT];
BINTABLE *pstBinTable;
HOTCARD stHotCard[MAX_HOTCARD_CNT];
HOTCARD *pstHotCard;
EMVAPP stEmvApp;
EMVCAPK stEmvCapk;
EMVREVOKECAPK stEmvRevokeCapk;

U16 usAppListCnt = 0;
U16 usBinTableCnt = 0;
U16 usHotCardsCnt = 0;

void InitFlashParameters() {
    pstAppList = (APPLIST *) FLASH8MB_NIBSS_APPFUNCLIST;
    pstBinTable = (BINTABLE *) FLASH8MB_NIBSS_BINTABLES;
    pstHotCard = (HOTCARD *) FLASH8MB_NIBSS_HOTCARD;
    pstParams = (PARAMS *) FLASH8MB_NIBSS_PARAMS;

    for (usAppListCnt = 0; usAppListCnt < MAX_APPLIST_CNT; usAppListCnt++) {
        if (pstAppList[usAppListCnt].usMagicNo != MAGICNO_APPLIST)
            break;
    }
    for (usBinTableCnt = 0; usBinTableCnt < MAX_BINTABLE_CNT; usBinTableCnt++) {
        if (pstBinTable[usBinTableCnt].usMagicNo != MAGICNO_BINTABLE)
            break;
    }
    for (usHotCardsCnt = 0; usHotCardsCnt < MAX_HOTCARD_CNT; usHotCardsCnt++) {
        if (pstHotCard[usHotCardsCnt].usMagicNo != MAGICNO_HOTCARD)
            break;
    }
#ifdef USER_DEBUG
    Rprintf("usAppListCnt = %d\r\n", usAppListCnt);
    Rprintf("usBinTableCnt = %d\r\n", usBinTableCnt);
    Rprintf("usHotCardsCnt = %d\r\n", usHotCardsCnt);
#endif

    pstMasterKey = (MASTERKEY *) FLASH8MB_NIBSS_MASTERKEY;
    memcpy(&stMasterKey, (char *) FLASH8MB_NIBSS_MASTERKEY, sizeof (stMasterKey));

    memcpy(&stSessionKey, (char *) FLASH8MB_NIBSS_SESSIONKEY, sizeof (stSessionKey));

}

/* */
