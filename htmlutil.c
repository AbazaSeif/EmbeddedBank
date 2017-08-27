
/*======================================================================*/
/*																		*/
/*							HtmlUtil.c									*/
/*																		*/
/*======================================================================*/

#include "system.h"
#include "extern.h"
#include "include/emv/emv_tag.h"

U16 iStartAt = 0;
U16 giTmpCount = 0;
U16 giApplIdx = 0;
U16 gusApplId = -1;

extern char gbTmpRespBuf[8192];
extern int SHA256_Signature(char *pSignBuf, char *pParams);

int GetApplIdx(int iAppId);


////////////////////////////////////////////////////////
// Define Tag
////////////////////////////////////////////////////////

#define BUF_SIZE  1024
#define MAX_WAIT_TIME 500
#define SKEY_NUM  10
#define KEY_SIZE  32
#define TAG_NUM   139

const char *NIBSS_TAG[TAG_NUM] = {
    "funclist", // 0
    "function", // 1
    "appllist", // 2  Application List section
    "applsvr", // 3  Specific Application section
    "applid", // 4  Application ID (1 = TAMS, 2 = Airtime VoucherVault; 3: EFTPOS
    "name", // 5  Application name
    "url", // 6  The URL to retrieve Remote ApI Call functions for the specific application
    "functime", // 7  The last date/time (in UNIX format) when the function list was last update. This can be used to detect whether the function list must be updated
    "disabled", // 8  Indicates if application is disabled 
    "newkey", // 9  New Key segment
    "masterkey", // 10 New Master Key 
    "getkeys", // 11		
    "cipher", // 12
    "key", // 13
    "no", // 14
    "bintable", // 15 List of bin tables segment
    "bin", // 16 Specific bin record XML segment
    "pan", // 17 The prefix PAN number
    "length", // 18 the length of the full PAN
    "cardtype", // 19 The Card type
    "floor", // 20 The minimum payment amount floor limit
    "check", // 21 Binary based combination of check flags
    "allow", // 22 Binary based combination of allowed flags
    "promptgroup", // 23 Prompt sequence to use for entering data
    "eftparam", // 24 EFT Paramenters segment
    "online", // 25 Maximum of transactions that can be done offline before connecting online
    "maxcashback", // 26
    "minbudgetperiod", // 27
    "maxbudgetperiod", // 28
    "budgetminamount", // 29
    "velocitytime", // 30
    "manualonline", // 31
    "updatebin", // 32
    "updatehot", // 33 The terminal's hot card list requires updating 
    "hotcards", // 34
    "efttotals", // 35 Reconcile segment
    "result", // 36 Reconcile result number (0=OK, other = exception)
    "batchno", // 37 New batch number to use for transactions
    "efttran", // 38
    "tran", // 39
    "message", // 40
    "status", // 41
    "refno", // 42
    "tranno", // 43
    "batchno", // 44
    "fromacc", // 45
    "toacc", // 46
    "balance", // 47 Balance amount
    "available", // 48 Available amount
    "data", // 49 Mini statement data delimited by the pipe character
    "iccresponse", // 50 ICC issuer script that must be sent to the IcC Card after transaction is done. This is typically used by PIN Change to update the Offline PIN
    "param", // 51 Parameter
    "datetime", // 52
    "year", // 53
    "syear", // 54
    "mon", // 55
    "day", // 56
    "hour", // 57
    "min", // 58
    "sec", // 59
    "merchantid", // 60
    "pinreset", // 61
    "updatelogo", // 62
    "updatemenu", // 63
    "replytimeout", // 64
    "currency", // 65
    "fract", // 66
    "prefix", // 67
    "negnum", // 68
    "currcode", // 69
    "decsym", // 70
    "endofday", // 71
    "attendance", // 72
    "agentaccess", // 73
    "eodtime", // 74
    "enabled", // 75
    "conn1", // 76
    "conn2", // 77
    "download", // 78
    "downloadconn", // 79
    "updateprompts", // 80
    "thoussep", // 81
    "countrycode", // 82
    "emv", // 83 /// emv part
    "count", // 84
    "app", // 85
    "index", // 86
    "irn", // 87
    "aid", // 88
    "match", // 89
    "appver", // 90
    "priority", // 91
    "ddol", // 92
    "tdol", // 93
    "tfldom", // 94
    "tflint", // 95
    "thresholddom", // 96
    "thresholdint", // 97
    "maxtargetdom", // 98
    "maxtargetint", // 99
    "targetpercentdom", // 100
    "targetpercentint", // 101
    "tacdefault", // 102
    "tacdenial", // 103
    "taconline", // 104
    "calist", // 105	// emvcapk
    "ca", // 106
    "rid", // 107
    "hashalgo", // 108
    "modulus", // 109
    "exponent", // 110
    "hash", // 111
    "pkalgo", // 112
    "prompts", // 113
    "promptgroup", // 114
    "promptno", // 115
    "prompt", // 116
    "prompttype", // 117
    "promptdisplay", // 118
    "promptlength", // 119
    "promptvar", // 120
    "prompminlength", // 121
    "promptactions", // 122
    "promptseqno", // 123
    "eodtxnlist", // 124
    "keyindex", // 125
    "callhome", // 126
    "menus", // 127
    "menu", // 128
    "item", // 129
    "type", // 130
    "timeout", // 131
    "access", // 132
    "header", // 133
    "footer", // 134
    "error", // 
    "errcode", // 
    "errno", // 
    "errmsg" // 
};

/// Tams function List 
const char *sTAMSFunctionList[] = {
    "AGENTLOGIN",
    "AGENTLOGOUT",
    "CALLHOME",
    "EOD",
    "GETKEYS",
    "GETLOGO",
    "GETMENU",
    "GETPROMPTLIST",
    "NEWKEY",
    "OPERATORREPORT",
    "PARAM",
    "TELLERCARDS"
};

// Voucher FunctionList
const char *sVoucherFunctionList[] = {
    "CANCELORDER",
    "ELECSALE",
    "GETBALANCE",
    "GETSTOCK",
    "ORDER",
    "PARAM",
    "PINLESSORDER",
    "PINLESSRECONTOTAL",
    "PINLESSREVERSAL",
    "PINLESSSTATUS",
    "PINLESSUPLOAD",
    "PRODLIST",
    "REPRINT",
    "RETURNSTOCK",
    "SALES",
    "SPLIST",
    "SPLOGO"
};

// Bank Function List
const char *sBankFunctionList[] = {
    "BINTABLE",
    "BIOTEMPLATE",
    "BIOTRAN",
    "DISTORDER",
    "DISTRETURN",
    "EFTPARAMS",
    "EFTTOTALS",
    "EFTTRAN",
    "EMVAPP",
    "EMVCAPK",
    "EMVREVOKECAPK",
    "EODTXNLIST",
    "HOTCARDS",
    "LINKED",
    "UPLOADTXN"
};

// HTTP Header strings
const char *sHttpReqHeader[9] = {
    "POST", // 0 The Remote API Call and Query string parameters
    "HOST:", // 1 The Domain and port to Connect to (different from each installation)
    "User-Agent:", // 2 TAMS/3.0
    "Accept:", // 3 Informs the server that XML must be returned 
    "Content-Type:", // 4 Informs the server that the client is sending POST data 
    "Terminal", // 5 Terminal ID
    "Sign:", // 6 SHA1 Hash over concatenated string of security key "KEY1"(hex)
    "Content-Length:", // 7 The amount of bytes in the POST data 
    "Post Data" // 8 Large data sent to server, per normal HTTP Post data
};


int gIndex = 0;
// Variables
char tagName[64];
char tagData[512];
int TagStack[128];
int SP = 0; // stack point

void ProcessTagNValue(int tagNum, char *tagData, int iApiReq, void *lpDataBuffer) {
    char str[256];
    int iTagNotFound = 0;

    if (iApiReq == API_GET_APPLIST) {
        APPLIST *pAppList = (APPLIST *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "applid")) {
            pAppList->usApplId = atoi(tagData);

        } else if (!strcmp(NIBSS_TAG[tagNum], "name")) {
            strcpy(pAppList->sz32Name, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "url")) {

            strcpy(pAppList->sz128Url, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "functime")) {
            pAppList->ulFuncTime = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "disabled")) {

            pAppList->usDisabled = tagData[0];

            //gIndex++;
        } else {
            iTagNotFound = 1;
        }
    }//API_GET_APPLIST
    else if (iApiReq == API_GET_FUNCLIST) {
        //FUNCLIST *pFuncList = (FUNCLIST *)lpDataBuffer;
        APPLIST *pAppList = (APPLIST *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "name")) {
            //strncpy(pFuncList->sz32Name, tagData, strlen(tagData));
            //strcpy(pFuncList->sz32Name, tagData);
            strcpy(pAppList->stFuncList[giTmpCount].sz32Name, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "url")) {
            //strncpy(pFuncList->sz128Url, tagData, strlen(tagData));
            //strcpy(pFuncList->sz128Url, tagData);
            strcpy(pAppList->stFuncList[giTmpCount].sz128Url, tagData);
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_TAMS_NEWKEY) {

        MASTERKEY *pMasterKey = (MASTERKEY *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "masterkey")) {
            strncpy(pMasterKey->ucMasterKey, tagData, strlen(tagData));
            pMasterKey->ucMKFlag = 0x5A;
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_TAMS_GETKEYS) {
        SESSIONKEY *pSessionKey = (SESSIONKEY *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "no")) {
            gIndex = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "key")) {
            strncpy(pSessionKey->ucSessionKey[gIndex], tagData, strlen(tagData));
            pSessionKey->ucSKFlag[gIndex] = 0x5A;
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_BANK_EFTPARAMS) {
        EFTPARAMS *pEftParams = (EFTPARAMS *) lpDataBuffer;
        if (!strcmp(NIBSS_TAG[tagNum], "online")) {
            pEftParams->usOnline = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "maxcashback")) {
            pEftParams->ulMaxCashback = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "minbudgetperiod")) {
            pEftParams->usMinBudgetPeriod = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "maxbudgetperiod")) {
            pEftParams->usMaxBudgetPeriod = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "budgetminamount")) {
            pEftParams->ulBudgetMinAmount = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "velocitytime")) {
            pEftParams->ulVelocityTime = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "manualonline")) {
            pEftParams->ucManualOnline = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "updatebin")) // doc �� Ʋ����.
        {
            pEftParams->ulUpdateBin = atol(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "updatehot")) // doc �� Ʋ����.
        {
            pEftParams->ulUpdateHot = atol(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "eodtxnlist")) // doc �� ���� �߰� .
        {
            pEftParams->ucEodTxnList = tagData[0];
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_BANK_BINTABLE) {
        BINTABLE *pBinTable = (BINTABLE *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "pan")) {
            strcpy(pBinTable->sz10Pan, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "length")) {
            pBinTable->ucLength = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "cardtype")) {
            pBinTable->ucCardType = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "floor")) {
            pBinTable->ulFloor = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "check")) {
            pBinTable->usCheck = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "allow")) {
            pBinTable->usAllow = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "keyindex")) {
            pBinTable->ucKeyIndex = atoi(tagData);
            gIndex++;
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_BANK_HOTCARDS) {
        int len;
        HOTCARD *pHotCard = (HOTCARD *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "pan")) {
            len = strlen(tagData);
            pHotCard->uc12Pan[0] = (U08) len;
            asc2bcd(&pHotCard->uc12Pan[1], tagData, len);
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_BANK_EMVAPP) {
        int len;
        U08 temp[256];
        EMVAPP *pEmvApp = (EMVAPP *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "count")) {
            giTmpCount = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "index")) {
            pEmvApp->usIndex = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "aid")) {
            //strncpy(pEmvApp->ucAID, tagData, strlen(tagData));
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucAID[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucAID[1], temp, pEmvApp->ucAID[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "name")) {
            //strncpy(pEmvApp->ucAppLabel, tagData, strlen(tagData));
            pEmvApp->ucAppLabel[0] = strlen(tagData);
            memcpy(&pEmvApp->ucAppLabel[1], tagData, pEmvApp->ucAppLabel[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "appver")) {
            //strncpy(pEmvApp->ucAppVer, tagData, strlen(tagData));
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucAppVer[0] = (len + 1) / 2;
            //memcpy(&pEmvApp->ucAppVer[1], temp, pEmvApp->ucAppVer[0]);
            pEmvApp->ucAppVer[1] = temp[1];
            pEmvApp->ucAppVer[2] = temp[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "ddol")) {
            //strncpy(pEmvApp->ucDDOL, tagData, strlen(tagData));
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucDDOL[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucDDOL[1], temp, pEmvApp->ucDDOL[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "tdol")) {
            //strncpy(pEmvApp->ucTDOL, tagData, strlen(tagData));
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucTDOL[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucTDOL[1], temp, pEmvApp->ucTDOL[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "tfldom")) {
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucTFLDom[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucTFLDom[1], temp, pEmvApp->ucTFLDom[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "tflint")) {
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucTFLInt[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucTFLInt[1], temp, pEmvApp->ucTFLInt[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "thresholddom")) {
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucThresholdDom[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucThresholdDom[1], temp, pEmvApp->ucThresholdDom[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "thresholdint")) {
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucThresholdInt[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucThresholdInt[1], temp, pEmvApp->ucThresholdInt[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "maxtargetdom")) {
            pEmvApp->ucMaxTargetDom = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "maxtargetint")) {
            pEmvApp->ucMaxTargetInt = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "targetpercentdom")) {
            pEmvApp->ucTargetPercentDom = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "targetpercentint")) {
            pEmvApp->ucTargetPercentInt = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "tacdefault")) {
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucTACdefault[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucTACdefault[1], temp, pEmvApp->ucTACdefault[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "tacdenial")) {
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucTACdenial[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucTACdenial[1], temp, pEmvApp->ucTACdenial[0]);
        } else if (!strcmp(NIBSS_TAG[tagNum], "taconline")) {
            len = strlen(tagData);
            asc2bcd(temp, tagData, len);
            pEmvApp->ucTAConline[0] = (len + 1) / 2;
            memcpy(&pEmvApp->ucTAConline[1], temp, pEmvApp->ucTAConline[0]);
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_BANK_EMVCAPK) {
        int len;
        U08 temp[256];
        EMVCAPK *pEmvCapk = (EMVCAPK *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "count")) {
            giTmpCount = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "rid")) {
            len = strlen(tagData);
            asc2bcd(pEmvCapk->ucRID, tagData, len);
        } else if (!strcmp(NIBSS_TAG[tagNum], "index")) {
            //pEmvCapk->ucIndex = atoi(tagData);
            len = strlen(tagData);
            asc2bcd(&pEmvCapk->ucIndex, tagData, len);
        } else if (!strcmp(NIBSS_TAG[tagNum], "exponent")) {
            len = atoi(tagData);
            pEmvCapk->ucExponent[0] = (len >> 24) & 0xFF;
            pEmvCapk->ucExponent[1] = (len >> 16) & 0xFF;
            pEmvCapk->ucExponent[2] = (len >> 8) & 0xFF;
            pEmvCapk->ucExponent[3] = (len >> 0) & 0xFF;
        } else if (!strcmp(NIBSS_TAG[tagNum], "modulus")) {
            len = strlen(tagData);
            asc2bcd(pEmvCapk->ucModulus, tagData, len);
            len = (int) ((len + 1) / 2) * 8;
            pEmvCapk->ucBits[0] = (len >> 8) & 0xFF;
            pEmvCapk->ucBits[1] = (len >> 0) & 0xFF;
        } else if (!strcmp(NIBSS_TAG[tagNum], "pkalgo")) {
            pEmvCapk->ucPkAlgo = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "hash")) {
            len = strlen(tagData);
            pEmvCapk->ucHash[0] = (len + 1) / 2;
            asc2bcd(&pEmvCapk->ucHash[1], tagData, len);
        } else if (!strcmp(NIBSS_TAG[tagNum], "hashalgo")) {
            pEmvCapk->ucHashAlgo = atoi(tagData);
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_BANK_EMVREVOKECAPK) {
        int len;
        U08 temp[256];
        EMVREVOKECAPK *pEmvRevokeCapk = (EMVREVOKECAPK *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "count")) {
            giTmpCount = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "rid")) {
            len = strlen(tagData);
            asc2bcd(pEmvRevokeCapk->ucRID, tagData, len);
        } else if (!strcmp(NIBSS_TAG[tagNum], "index")) {
            //pEmvRevokeCapk->ucIndex = atoi(tagData);
            len = strlen(tagData);
            asc2bcd(&pEmvRevokeCapk->ucIndex, tagData, len);
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_TAMS_PARAM) {
        int len;
        U08 temp[256];
        PARAMS *pParams = (PARAMS *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "year")) {
            pParams->usDTyear = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "syear")) {
            pParams->ucDTsyear = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "mon")) {
            pParams->ucDTmon = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "day")) {
            pParams->ucDTday = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "hour")) {
            pParams->ucDThour = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "min")) {
            pParams->ucDTmin = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "sec")) {
            pParams->ucDTsec = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "merchantid")) {
            strcpy(pParams->szMerchantID, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "header")) {
            strcpy(pParams->szHeader, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "footer")) {
            strcpy(pParams->szFooter, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "pinreset")) {
            pParams->ucPinReset = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "updatelogo")) {
            pParams->ucUpdateLogo = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "updatemenu")) {
            pParams->ucUpdateMenu = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "replytimeout")) {
            pParams->usReplyTimeout = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "currency")) {
            pParams->ucCurrency = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "fract")) {
            pParams->ucFract = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "prefix")) {
            pParams->ucPrefix = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "negnum")) {
            pParams->ucNegNum = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "currcode")) {
            len = strlen(tagData);
            asc2bcd(pParams->ucCurrCode, tagData, len);
        } else if (!strcmp(NIBSS_TAG[tagNum], "decsym")) {
            pParams->ucDecSym = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "thoussep")) {
            pParams->ucThousSep = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "countrycode")) {
            len = strlen(tagData);
            asc2bcd(pParams->ucCountryCode, tagData, len);
        } else if (!strcmp(NIBSS_TAG[tagNum], "endofday")) {
            pParams->usEndofday = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "updateprompts")) {
            pParams->ulUpdatePrompts = atol(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "attendance")) {
            pParams->ucAttendance = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "agentaccess")) {
            pParams->ucAgentAccess = tagData[0];
        } else if (!strcmp(NIBSS_TAG[tagNum], "enabled")) {
            if (TagStack[SP - 1] == 74) { // "eodtime"
                pParams->ucEodtimeEn = tagData[0];
            } else if (TagStack[SP - 1] == 78) { // "download"
                pParams->ucDownloadEn = tagData[0];
            }
        } else if (!strcmp(NIBSS_TAG[tagNum], "conn1")) {
            pParams->usConn1 = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "conn2")) {
            pParams->usConn2 = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "downloadconn")) {
            pParams->usDownloadConn = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "disabled")) {
            pParams->ucDisabled = tagData[0];
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_BANK_EFTTRAN || iApiReq == API_BANK_EFTTOTALS) {
        // <efttran><tran><result>2</result><message>No Switch</message><status>304</status><tranno>1</tranno><batchno>1</batchno></tran></efttran>
        int len;
        U08 temp[256];
        _st_TrxnRespData_ *pTrxnRespData = (_st_TrxnRespData_ *) lpDataBuffer;

        if (!strcmp(NIBSS_TAG[tagNum], "result")) {
            pTrxnRespData->ucResult = tagData[0];
            if (iApiReq == API_BANK_EFTTOTALS) {
                strcpy(pTrxnRespData->sz4StatusCode, tagData);
            }
        } else if (!strcmp(NIBSS_TAG[tagNum], "message")) {
            strcpy(pTrxnRespData->sz33Message, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "status")) {
            strcpy(pTrxnRespData->sz4StatusCode, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "refno")) {
            strcpy(pTrxnRespData->sz13ReferenceNo, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "tranno")) {
            pTrxnRespData->usTrxnSeqNo = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "batchno")) {
            pTrxnRespData->usTrxnBatchNo = atoi(tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "balance")) {
            strcpy(pTrxnRespData->sz13Balance, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "available")) {
            strcpy(pTrxnRespData->sz13Available, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "data")) {
            strcpy(pTrxnRespData->sz256Data, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "iccresponse")) {
            strcpy(pTrxnRespData->sz512IccResponse, tagData);
        } else {
            iTagNotFound = 1;
        }
    } else if (iApiReq == API_TAMS_CALLHOME) {
        iTagNotFound = 1;
    } else {
#ifdef USER_DEBUG
        sprintf(str, "Unknown Request Message %d : tag = %s, %s\r\n", iApiReq, NIBSS_TAG[tagNum], tagData);
        Rprintf(str);
#endif
    }

    if (iTagNotFound == 1) {
        if (!strcmp(NIBSS_TAG[tagNum], "errcode")) {
            strcpy(st_ErrRespData.sz4ErrCode, tagData);
        } else if (!strcmp(NIBSS_TAG[tagNum], "errmsg")) {
            strcpy(st_ErrRespData.sz49ErrMsg, tagData);
        }
    }

    return;
}

int GetTagName(char *tagName) {
    int tagnum = -1;
    int len;

    len = strlen(tagName);

    while (tagName[len - 1] == ' ')// Remove Space
        len--;

    // Match the tagName from the tables
    ///////////////////////////////////////////////
    for (tagnum = 0; tagnum < TAG_NUM; tagnum++) {
        if (len != strlen(NIBSS_TAG[tagnum]))
            continue;
        if (!strncmp(tagName, NIBSS_TAG[tagnum], len))
            return tagnum;
    }

    return -1;
}

int push(int item) {
    if (SP >= 0)
        TagStack[SP++] = item;
    else
        return 0;

    return 1;
}

int pop() {
    if (SP > 0) {
        return TagStack[--SP];
    } else {
        return -1;
    }
}

U08 *pgbTLVBuf;
int giTLVBufLen, giTLVBufTotalLen;

int AddTLVBuf(int uTag, int uLen, U08 *uDat) {
    U08 *pAdd;
    int i;

    if (pgbTLVBuf == NULL)
        return -1;

    if (uTag == Tag_EOT4) { // just Add all Dat
        if (uLen == 0) return 0;
        memcpy((U08 *) & pgbTLVBuf[giTLVBufLen], uDat, uLen);
        giTLVBufLen += uLen;
    } else {
        if (uLen > 0) { // Add Tag,Len,Dat
            if (uTag & 0xFF00) i = 2; // 2 bytes Tag
            else i = 1; // 1 bytes Tag

            if (uLen < 0x80) i += 1; // 1 bytes Len
            else if (uLen < 0x100) i += 2; // 2 bytes Len
            else i += 3; // 3 bytes Len

            if (uTag & 0xFF00) pgbTLVBuf[giTLVBufLen++] = (U08) (uTag >> 8);
            pgbTLVBuf[giTLVBufLen++] = (U08) uTag;

            if (uLen < 0x80) { // 1 bytes Len
                pgbTLVBuf[giTLVBufLen++] = uLen;
            } else if (uLen < 0x100) { // 2 bytes Len
                pgbTLVBuf[giTLVBufLen++] = 0x81;
                pgbTLVBuf[giTLVBufLen++] = uLen;
            } else { // 3 bytes Len
                pgbTLVBuf[giTLVBufLen++] = 0x82;
                pgbTLVBuf[giTLVBufLen++] = (U08) (uLen >> 8);
                pgbTLVBuf[giTLVBufLen++] = (U08) uLen;
            }
            memcpy((U08 *) & pgbTLVBuf[giTLVBufLen], uDat, uLen);
            giTLVBufLen += uLen;
        }
    }

    return 0;
}

void ProcessStartTag(int iApiReq, int tagNum) {
    if (tagNum == 2) { // "appllist"
        giTmpCount = 0;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        pstAppList = (APPLIST *) gbTmpRespBuf;
    } else if (tagNum == 0) { // "funclist"
        giTmpCount = 0;
        //memset(gbTmpRespBuf, 0xFF, sizeof(gbTmpRespBuf));
        memcpy(gbTmpRespBuf, (char *) FLASH8MB_NIBSS_APPFUNCLIST + sizeof (APPLIST) * giApplIdx, sizeof (APPLIST));
        pstAppList = (APPLIST *) gbTmpRespBuf;
    } else if (tagNum == 9) { // "newkey"
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
    } else if (tagNum == 11) { // "getkeys"
        giTmpCount = 0;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
    } else if (tagNum == 24) { // "eftparam"
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        memcpy(gbTmpRespBuf, &stEftParams, sizeof (EFTPARAMS));
    } else if (tagNum == 15) { // "bintable"
        giTmpCount = 0;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
    } else if (tagNum == 34) { // "hotcards"
        iStartAt = 0;
        giTmpCount = 0;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
    } else if (tagNum == 83) { // "emv"
        giTmpCount = 0;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        giTLVBufTotalLen = 0;
    } else if (tagNum == 85) { // "app"
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
    } else if (tagNum == 106) { // "ca"
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
    } else if (tagNum == 105) { // "calist"
        giTmpCount = 0;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        giTLVBufTotalLen = 0;
    } else if (tagNum == 51) { // "param"
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
    } else if (tagNum == 38) { // "efttran"
        memset(gbTmpRespBuf, 0x00, sizeof (gbTmpRespBuf));
    } else if (tagNum == 35) { // "efttotals"
        memset(gbTmpRespBuf, 0x00, sizeof (gbTmpRespBuf));
    } else if (tagNum == 135) { // "error"
        memset((char *) &st_ErrRespData, 0x00, sizeof (_st_ErrRespData_));
    }

}

void ProcessEndTag(int iApiReq, int tagNum) {
    int i;
    U08 temp[512];

    if (tagNum == 2) { // "appllist"
        pstAppList = (APPLIST *) FLASH8MB_NIBSS_APPFUNCLIST;
        usAppListCnt = giTmpCount;
        /*
                        {
                                int l;
                                for(l = 0; l < usAppListCnt; l++) {
                                        Rprintf("APPLIST[%d]\r\n", l);
                                        Rprintf("usApplId: %d\r\n", pstAppList[l].usApplId);
                                        Rprintf("sz32Name: %s\r\n", pstAppList[l].sz32Name);
                                        Rprintf("sz128Url: %s\r\n", pstAppList[l].sz128Url);
                                        Rprintf("ulFuncTime: %ld\r\n", pstAppList[l].ulFuncTime);
                                        Rprintf("usDisabled: %d\r\n", pstAppList[l].usDisabled);
                                }
                        }
         */
        //FLASH_WRITE((char *)FLASH8MB_NIBSS_APPFUNCLIST, sizeof(APPLIST) * MAX_APPLIST_CNT, (char *)&stAppList[0]);
    } else if (tagNum == 3) { // "applsvr"
        if (giTmpCount == 0) {
            memset(FlashWriteBuf, 0xFF, 16384);
            FLASH_WRITE((char *) FLASH8MB_NIBSS_APPFUNCLIST, 16384, FlashWriteBuf);
        }
        pstAppList->usMagicNo = MAGICNO_APPLIST;
        FLASH_WRITE((char *) FLASH8MB_NIBSS_APPFUNCLIST + sizeof (APPLIST) * giTmpCount, sizeof (APPLIST), (char *) pstAppList);
        //		memcpy(&stAppList[giTmpCount], gbTmpRespBuf, sizeof(APPLIST));
        usAppListCnt = ++giTmpCount;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        pstAppList = (APPLIST *) gbTmpRespBuf;
    } else if (tagNum == 0) { // "funclist"
        pstAppList->usFuncListCnt = giTmpCount;
        /*
                        {
                                int l;
                                Rprintf("giApplIdx = %d\r\n", giApplIdx);
                                for(l = 0; l < pstAppList->usFuncListCnt; l++) {
                                        Rprintf("%d:[%s] %s\r\n", l, pstAppList->stFuncList[l].sz32Name, pstAppList->stFuncList[l].sz128Url);
                                }
                        }
         */
        //FLASH_WRITE((char *)FLASH8MB_NIBSS_APPFUNCLIST, sizeof(APPLIST) * MAX_APPLIST_CNT, (char *)&stAppList[0]);
        FLASH_WRITE((char *) FLASH8MB_NIBSS_APPFUNCLIST + sizeof (APPLIST) * giApplIdx, sizeof (APPLIST), (char *) pstAppList);
        pstAppList = (APPLIST *) FLASH8MB_NIBSS_APPFUNCLIST;
    } else if (tagNum == 1) { // "function"
        // �տ� ���� function�� üũ�ؼ� ������ �н�, Ʋ���� ������Ʈ, ������ �߰�
        for (i = 0; i < giTmpCount; i++) {
            if (!strcmp(pstAppList->stFuncList[i].sz32Name, pstAppList->stFuncList[giTmpCount].sz32Name)) {
                break;
            }
        }
        if (i == giTmpCount) {
            pstAppList->stFuncList[giTmpCount].usMagicNo = MAGICNO_FUNCLIST;
            pstAppList->usFuncListCnt = ++giTmpCount;
        }
        /*
                        memcpy(&stAppList[giApplIdx].stFuncList[giTmpCount], gbTmpRespBuf, sizeof(FUNCLIST));
                        memset(gbTmpRespBuf, 0xFF, sizeof(gbTmpRespBuf));
                        stAppList[giApplIdx].stFuncList[giTmpCount].usMagicNo = MAGICNO_FUNCLIST;
                        stAppList[giApplIdx].usFuncListCnt = -1;
                        giTmpCount++;
         */
    } else if (tagNum == 10) { // "masterkey"
    } else if (tagNum == 9) { // "newkey"
        memcpy(stMasterKey.ucMasterKey, ((MASTERKEY *) gbTmpRespBuf)->ucMasterKey, sizeof (stMasterKey.ucMasterKey));
        stMasterKey.ucMKFlag = ((MASTERKEY *) gbTmpRespBuf)->ucMKFlag;
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        stMasterKey.usMagicNo = MAGICNO_MASTERKEY;
        /*
                        {
                                int l;
                                Rprintf("stMasterKey.ucMKFlag = %02X\r\nstMasterKey.ucMasterKey = ", stMasterKey.ucMKFlag);
                                for(l = 0; l < 32; l++) {
                                        Rprintf("%c", stMasterKey.ucMasterKey[l] & 0xFF);
                                }
                                Rprintf("\r\n");
                        }
         */
        FLASH_WRITE((char *) FLASH8MB_NIBSS_MASTERKEY, sizeof (MASTERKEY), (char *) &stMasterKey);
    } else if (tagNum == 12) { // "cipher"
    } else if (tagNum == 11) { // "getkeys"
        memcpy(stSessionKey.ucSessionKey, ((SESSIONKEY *) gbTmpRespBuf)->ucSessionKey, sizeof (stSessionKey.ucSessionKey));
        memcpy(stSessionKey.ucSKFlag, ((SESSIONKEY *) gbTmpRespBuf)->ucSKFlag, sizeof (stSessionKey.ucSKFlag));
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        stSessionKey.usMagicNo = MAGICNO_SESSIONKEY;
        /*
                        {
                                int l, m;
                                for(m = 0; m < 10; m++) {
                                        Rprintf("stSessionKey.ucSKFlag[%d] = %02X\r\n", m, stSessionKey.ucSKFlag[m]);
                                        if(stSessionKey.ucSKFlag[m] != 0x5A)
                                                continue;
                                        for(l = 0; l < 32; l++) {
                                                Rprintf("%c", stSessionKey.ucSessionKey[m][l] & 0xFF);
                                        }
                                        Rprintf("\r\n");
                                }
                        }
         */
        FLASH_WRITE((char *) FLASH8MB_NIBSS_SESSIONKEY, sizeof (SESSIONKEY), (char *) &stSessionKey);
    } else if (tagNum == 24) { // "eftparam"
        memcpy(&stEftParams, gbTmpRespBuf, sizeof (EFTPARAMS));
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        stEftParams.usMagicNo = MAGICNO_EFTPARAMS;
        /*
                        {
                                Rprintf("stEftParams.usOnline = %d\r\n", stEftParams.usOnline);
                                Rprintf("stEftParams.ulMaxCashback = %ld\r\n", stEftParams.ulMaxCashback);
                                Rprintf("stEftParams.usMinBudgetPeriod = %d\r\n", stEftParams.usMinBudgetPeriod);
                                Rprintf("stEftParams.usMaxBudgetPeriod = %d\r\n", stEftParams.usMaxBudgetPeriod);
                                Rprintf("stEftParams.ulBudgetMinAmount = %ld\r\n", stEftParams.ulBudgetMinAmount);
                                Rprintf("stEftParams.ulVelocityTime = %ld\r\n", stEftParams.ulVelocityTime);
                                Rprintf("stEftParams.ucManualOnline = %c\r\n", stEftParams.ucManualOnline);
                                Rprintf("stEftParams.ulUpdateBin = %ld\r\n", stEftParams.ulUpdateBin);
                                Rprintf("stEftParams.ulUpdateHot = %ld\r\n", stEftParams.ulUpdateHot);
                                Rprintf("stEftParams.ucEodTxnList = %c\r\n", stEftParams.ucEodTxnList);
                        }
         */
        FLASH_WRITE((char *) FLASH8MB_NIBSS_EFTPARAMS, sizeof (EFTPARAMS), (char *) &stEftParams);
    } else if (tagNum == 16) { // "bin"
        memcpy(&stBinTable[giTmpCount], gbTmpRespBuf, sizeof (BINTABLE));
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        stBinTable[giTmpCount].usIndex = giTmpCount;
        stBinTable[giTmpCount].usMagicNo = MAGICNO_BINTABLE;
        /*
                        {
                                int l;

                                Rprintf("stBinTable[%d].usIndex = %d\r\n", giTmpCount, stBinTable[giTmpCount].usIndex);
                                Rprintf("stBinTable[%d].sz10Pan = ", giTmpCount);
                                for(l = 0; l < 10; l++) {
                                        Rprintf("%c", stBinTable[giTmpCount].sz10Pan[l] & 0xFF);
                                }
                                Rprintf("\r\n");
                                Rprintf("stBinTable[%d].ucLength = %d\r\n", giTmpCount, stBinTable[giTmpCount].ucLength);
                                Rprintf("stBinTable[%d].ucCardType = %d\r\n", giTmpCount, stBinTable[giTmpCount].ucCardType);
                                Rprintf("stBinTable[%d].ulFloor = %ld\r\n", giTmpCount, stBinTable[giTmpCount].ulFloor);
                                Rprintf("stBinTable[%d].usCheck = %d\r\n", giTmpCount, stBinTable[giTmpCount].usCheck);
                                Rprintf("stBinTable[%d].usAllow = %d\r\n", giTmpCount, stBinTable[giTmpCount].usAllow);
                                Rprintf("stBinTable[%d].ucKeyIndex = %d\r\n", giTmpCount, stBinTable[giTmpCount].ucKeyIndex);
                        }
         */
        giTmpCount++;
    } else if (tagNum == 15) { // "bintable"
        usBinTableCnt = giTmpCount;
        FLASH_WRITE((char *) FLASH8MB_NIBSS_BINTABLES, sizeof (BINTABLE) * MAX_BINTABLE_CNT, (char *) stBinTable);
    } else if (tagNum == 17) { // "pan"
        if (iApiReq == API_BANK_HOTCARDS) {
            memcpy(&stHotCard[iStartAt + giTmpCount], gbTmpRespBuf, sizeof (HOTCARD));
            memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
            stHotCard[iStartAt + giTmpCount].usIndex = iStartAt + giTmpCount;
            stHotCard[iStartAt + giTmpCount].usMagicNo = MAGICNO_HOTCARD;
            giTmpCount++;
        }
    } else if (tagNum == 34) { // "hotcards"
        usHotCardsCnt = giTmpCount;
        FLASH_WRITE((char *) FLASH8MB_NIBSS_HOTCARD, sizeof (HOTCARD) * MAX_HOTCARD_CNT, (char *) stHotCard);
    } else if (tagNum == 85) { // "app"
        memcpy(&stEmvApp, gbTmpRespBuf, sizeof (EMVAPP));
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        pgbTLVBuf = gbTmpRespBuf;
        giTLVBufLen = 0;
        AddTLVBuf(Tvb_TrmAID, stEmvApp.ucAID[0], &stEmvApp.ucAID[1]);
        AddTLVBuf(Tva_AppLabel, stEmvApp.ucAppLabel[0], &stEmvApp.ucAppLabel[1]);
        AddTLVBuf(T2n_TrmCountryCode, 2, "\x05\x66");
        AddTLVBuf(T2b_TrmAppVersionNo, stEmvApp.ucAppVer[0], &stEmvApp.ucAppVer[1]);
        AddTLVBuf(T5b_IAC_Denial, stEmvApp.ucTACdenial[0], &stEmvApp.ucTACdenial[1]);
        AddTLVBuf(T5b_IAC_Online, stEmvApp.ucTAConline[0], &stEmvApp.ucTAConline[1]);
        AddTLVBuf(T5b_IACdefault, stEmvApp.ucTACdefault[0], &stEmvApp.ucTACdefault[1]);
        AddTLVBuf(Tvb_TDOL, stEmvApp.ucTDOL[0], &stEmvApp.ucTDOL[1]);
        AddTLVBuf(Tvb_DDOL, stEmvApp.ucDDOL[0], &stEmvApp.ucDDOL[1]);
        memcpy(temp, &stEmvApp.ucTFLDom[1], stEmvApp.ucTFLDom[0]);
        memcpy(&temp[stEmvApp.ucTFLDom[0]], &stEmvApp.ucTFLInt[1], stEmvApp.ucTFLInt[0]);
        AddTLVBuf(T4b_TrmFloorLimit, stEmvApp.ucTFLDom[0] + stEmvApp.ucTFLInt[0], temp);
        temp[0] = stEmvApp.ucTargetPercentDom;
        temp[1] = stEmvApp.ucMaxTargetDom;
        memcpy(&temp[2], &stEmvApp.ucThresholdDom[1], stEmvApp.ucThresholdDom[0]);
        temp[6] = stEmvApp.ucTargetPercentInt;
        temp[7] = stEmvApp.ucMaxTargetInt;
        memcpy(&temp[8], &stEmvApp.ucThresholdInt[1], stEmvApp.ucThresholdInt[0]);
        AddTLVBuf(Tvb_TrmRiskManagementData, 12, temp);
        AddTLVBuf(T2a_ARC, 2, "\x30\x30");
        AddTLVBuf(Tag_EOT4, 8, "\x00\xFF\xFF\x00\x00\xFF\xFF\x00");
        /*
                        {
                                int m;
                                Rprintf("\r\npgbTLVBuf:\r\n");
                                for(m = 0; m < giTLVBufLen; m++) {
                                        Rprintf("%02X ", pgbTLVBuf[m]);
                                }
                                Rprintf("\r\n");
                        }
         */
        FLASH_WRITE((char *) FLASH8MB_NIBSS_TRMCONF + giTLVBufTotalLen, giTLVBufLen, (char *) pgbTLVBuf);
        giTLVBufTotalLen += giTLVBufLen;
        /*
        Start Tag <emv> - flash clear 0xFF ( char FlashWriteBuf[131072]; )
        Start Tag <app> - gbTmpRespBuf clear, tlvbuf clear, len clear
        rcving data - AddTLVBuf
        End Tag </app> - flash write pgbTLVBuf and dummy bytes
        End Tag </emv> - flash write TagEOT4,0x00

        Start Tag <calist> - flash clear 0xFF ( char FlashWriteBuf[131072]; )
        Start Tag <ca> - gbTmpRespBuf clear, tlvbuf clear, len clear
        rcving data - AddTLVBuf
        End Tag </ca> - flash write pgbTLVBuf
        End Tag </calist> - flash write TagEOT4,0x00

        <calist>
                <count>10</count>
                <ca>
                </ca>
        </calist>
         */
    } else if (tagNum == 83) { // "emv"
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        pgbTLVBuf = gbTmpRespBuf;
        giTLVBufLen = 0;
        if (giTmpCount > 0) {
            AddTLVBuf(Tag_EOT4, 2, "\x04\x00");
            FLASH_WRITE((char *) FLASH8MB_NIBSS_TRMCONF + giTLVBufTotalLen, giTLVBufLen, (char *) pgbTLVBuf);
        }
        giTLVBufTotalLen += giTLVBufLen;
    } else if (tagNum == 106) { // "ca"
        int len;
        if (iApiReq == API_BANK_EMVCAPK) {
            memcpy(&stEmvCapk, gbTmpRespBuf, sizeof (EMVCAPK));
            memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
            pgbTLVBuf = gbTmpRespBuf;
            giTLVBufLen = 0;

            memcpy(stEmvCapk.ucCSN, "\x00\x10\x00", 3);
            len = (stEmvCapk.ucBits[0] << 8) | stEmvCapk.ucBits[1];
            len = 15 + (len + 7) / 8;
            memcpy(temp, &stEmvCapk, len);
            temp[len++] = stEmvCapk.ucPkAlgo;
            if (stEmvCapk.ucHash[0] > 0) {
                memcpy(&temp[len], &stEmvCapk.ucHash[1], stEmvCapk.ucHash[0]);
                len += stEmvCapk.ucHash[0];
                temp[len++] = stEmvCapk.ucHashAlgo;
            }
            AddTLVBuf(Tvb_TrmCAPK, len, temp);
            /*      	
                                    {
                                            int m;
                                            Rprintf("\r\nTvb_TrmCAPK pgbTLVBuf[%d]:\r\n", giTLVBufLen);
                                            for(m = 0; m < giTLVBufLen; m++) {
                                                    Rprintf("%02X ", pgbTLVBuf[m]);
                                            }
                                            Rprintf("\r\n");
                                    }
             */
            FLASH_WRITE((char *) FLASH8MB_NIBSS_TRMCAPK + giTLVBufTotalLen, giTLVBufLen, (char *) pgbTLVBuf);
            giTLVBufTotalLen += giTLVBufLen;
        } else if (iApiReq == API_BANK_EMVREVOKECAPK) {
            memcpy(&stEmvCapk, gbTmpRespBuf, sizeof (EMVCAPK));
            memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
            pgbTLVBuf = gbTmpRespBuf;
            giTLVBufLen = 0;

            //const U08 gcTrmRevocList[] = {		//(Terminal Revocation List,RID[5],CAPKI[1],CSN[3])
            // /* Tvb_TrmCAPK    */	0x18,       9, 0xA0,0x00,0x00,0x00,0x04,0x96,0x12,0x34,0x56,

            memcpy(stEmvCapk.ucCSN, "\x00\x10\x00", 3);
            AddTLVBuf(Tvb_TrmCAPK, sizeof (EMVREVOKECAPK), (char *) &stEmvRevokeCapk);
            /*      	
                                    {
                                            int m;
                                            Rprintf("\r\nTvb_TrmCAPK pgbTLVBuf[%d]:\r\n", giTLVBufLen);
                                            for(m = 0; m < giTLVBufLen; m++) {
                                                    Rprintf("%02X ", pgbTLVBuf[m]);
                                            }
                                            Rprintf("\r\n");
                                    }
             */
            FLASH_WRITE((char *) FLASH8MB_NIBSS_REVOCLIST + giTLVBufTotalLen, giTLVBufLen, (char *) pgbTLVBuf);
            giTLVBufTotalLen += giTLVBufLen;
        }
    } else if (tagNum == 105) { // "calist"
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        pgbTLVBuf = gbTmpRespBuf;
        giTLVBufLen = 0;
        if (giTmpCount > 0) {
            AddTLVBuf(Tag_EOT4, 2, "\x04\x00");
            if (iApiReq == API_BANK_EMVCAPK) {
                FLASH_WRITE((char *) FLASH8MB_NIBSS_TRMCAPK + giTLVBufTotalLen, giTLVBufLen, (char *) pgbTLVBuf);
            } else if (iApiReq == API_BANK_EMVREVOKECAPK) {
                FLASH_WRITE((char *) FLASH8MB_NIBSS_REVOCLIST + giTLVBufTotalLen, giTLVBufLen, (char *) pgbTLVBuf);
            }
        }
        giTLVBufTotalLen += giTLVBufLen;
    } else if (tagNum == 84) { // "count"
        if (iApiReq == API_BANK_EMVAPP) {
            if (giTmpCount > 0) {
                memset(FlashWriteBuf, 0xFF, 8192);
                FLASH_WRITE((char *) FLASH8MB_NIBSS_TRMCONF, 8192, FlashWriteBuf);
            }
        }
        if (iApiReq == API_BANK_EMVCAPK) {
            if (giTmpCount > 0) {
                memset(FlashWriteBuf, 0xFF, 32768);
                FLASH_WRITE((char *) FLASH8MB_NIBSS_TRMCAPK, 32768, FlashWriteBuf);
            }
        }
        if (iApiReq == API_BANK_EMVREVOKECAPK) {
            if (giTmpCount > 0) {
                memset(FlashWriteBuf, 0xFF, 16384);
                FLASH_WRITE((char *) FLASH8MB_NIBSS_REVOCLIST, 16384, FlashWriteBuf);
            }
        }
    } else if (tagNum == 51) { // "param"
        memcpy(&stParams, gbTmpRespBuf, sizeof (PARAMS));
        memset(gbTmpRespBuf, 0xFF, sizeof (gbTmpRespBuf));
        stParams.usMagicNo = MAGICNO_PARAMS;
        /*
                        {
                                Rprintf("stParams DateTime = %d,%d,%d,%d,%d,%d,%d\r\n", stParams.usDTyear, stParams.ucDTsyear,
                                        stParams.ucDTmon, stParams.ucDTday, stParams.ucDThour, stParams.ucDTmin, stParams.ucDTsec);
                                Rprintf("stParams.szMerchantID = %s\r\n", stParams.szMerchantID);
                                Rprintf("stParams.ucPinReset = %c\r\n", stParams.ucPinReset);
                                Rprintf("stParams.ucUpdateLogo = %c\r\n", stParams.ucUpdateLogo);
                                Rprintf("stParams.ucUpdateMenu = %c\r\n", stParams.ucUpdateMenu);
                                Rprintf("stParams.usReplyTimeout = %d\r\n", stParams.usReplyTimeout);
                                Rprintf("stParams.ucCurrency = %c\r\n", stParams.ucCurrency);
                                Rprintf("stParams.ucFract = %d\r\n", stParams.ucFract);
                                Rprintf("stParams.ucPrefix = %c\r\n", stParams.ucPrefix);
                                Rprintf("stParams.ucNegNum = %d\r\n", stParams.ucNegNum);

                                Rprintf("stParams.ucCurrCode = %02X%02X\r\n", stParams.ucCurrCode[0], stParams.ucCurrCode[1]);
                                Rprintf("stParams.ucDecSym = %c\r\n", stParams.ucDecSym);
                                Rprintf("stParams.ucThousSep = %c\r\n", stParams.ucThousSep);
                                Rprintf("stParams.ucCountryCode = %02X%02X\r\n", stParams.ucCountryCode[0], stParams.ucCountryCode[1]);
                                Rprintf("stParams.usEndofday = %d\r\n", stParams.usEndofday);
                                Rprintf("stParams.ulUpdatePrompts = %ld\r\n", stParams.ulUpdatePrompts);
                                Rprintf("stParams.ucAttendance = %c\r\n", stParams.ucAttendance);

                                Rprintf("stParams.ucAgentAccess = %c\r\n", stParams.ucAgentAccess);
                                Rprintf("stParams.usConn1 = %d\r\n", stParams.usConn1);
                                Rprintf("stParams.usConn2 = %d\r\n", stParams.usConn2);
                                Rprintf("stParams.ucDownloadEn = %c\r\n", stParams.ucDownloadEn);
                                Rprintf("stParams.usDownloadConn = %d\r\n", stParams.usDownloadConn);
                                Rprintf("stParams.ucDisabled = %c\r\n", stParams.ucDisabled);
                        }
         */
        FLASH_WRITE((char *) FLASH8MB_NIBSS_PARAMS, sizeof (PARAMS), (char *) &stParams);
    } else if (tagNum == 38) { // "efttran"
        memcpy(&st_TrxnRespData, gbTmpRespBuf, sizeof (_st_TrxnRespData_));
#ifdef USER_DEBUG
        Rprintf("st_TrxnRespData.ucResult=%c\r\n", st_TrxnRespData.ucResult);
        Rprintf("st_TrxnRespData.sz33Message=%s\r\n", st_TrxnRespData.sz33Message);
        Rprintf("st_TrxnRespData.sz4StatusCode=%s\r\n", st_TrxnRespData.sz4StatusCode);
        Rprintf("st_TrxnRespData.sz13ReferenceNo=%s\r\n", st_TrxnRespData.sz13ReferenceNo);
        Rprintf("st_TrxnRespData.usTrxnSeqNo=%d\r\n", st_TrxnRespData.usTrxnSeqNo);
        Rprintf("st_TrxnRespData.usTrxnBatchNo=%d\r\n", st_TrxnRespData.usTrxnBatchNo);
        Rprintf("st_TrxnRespData.sz13Balance=%s\r\n", st_TrxnRespData.sz13Balance);
        Rprintf("st_TrxnRespData.sz13Available=%s\r\n", st_TrxnRespData.sz13Available);
        Rprintf("st_TrxnRespData.sz256Data=%s\r\n", st_TrxnRespData.sz256Data);
        Rprintf("st_TrxnRespData.sz512IccResponse=%s\r\n", st_TrxnRespData.sz512IccResponse);
#endif
    } else if (tagNum == 35) { // "efttotals"
        memcpy(&st_TrxnRespData, gbTmpRespBuf, sizeof (_st_TrxnRespData_));
    } else if (tagNum == 135) { // "error"
        st_ErrRespData.iErrFlag = 1;
    }
}

void NIBSS_Parsing(char *xmlBuf, int len, int iApiReq, void *lpDataBuffer) {
    int i, j, k = 0;
    BOOL rightB = FALSE;
    BOOL leftB = FALSE;
    BOOL isData = FALSE;
    BOOL startXML = FALSE;
    int tagNum = -1;
    int savedTag = -1;
    //CString str;
    char ch;
    char str[256];

    memset(tagName, 0x0, sizeof (tagName));
    memset(tagData, 0x0, sizeof (tagData));

    for (i = 0; i < len; i++) {
        //ch = tempbuf[i];
        ch = xmlBuf[i];

        //str.Format("%c",ch);
        //AfxMessageBox(str);
        ///////////////////////
        // find tag and data 
        ///////////////////////
        if (ch == '<') {
            // find tag 
            leftB = TRUE;
            rightB = FALSE;
            j = 0;
        } else {
            if (ch == '>') {
                leftB = FALSE;
                j = 0;

                ////////////////////////////
                // find tag Name
                ////////////////////////////
                if (startXML) {
                    startXML = FALSE;
                    memset(tagName, 0x0, sizeof (tagName));
                    j = 0;
                    continue;
                }

                //str.Format("GetTage Name %s",tagName);
                //AfxMessageBox(str);

                tagNum = GetTagName(tagName);
                if (tagNum == -1) {
                    // not Matching return as errort
                    //str.Format("NO Matched Tag Found => %s", tagName);
                    //AfxMessageBox(str);
#ifdef USER_DEBUG
                    sprintf(str, "NO Matched Tag Found => %s\r\n", tagName);
                    Rprintf(str);
#endif
                    memset(tagName, 0x0, sizeof (tagName));

                    //					return;
                    continue;
                }

                if (rightB) { // End Tag
                    savedTag = pop();
                    rightB = FALSE;

                    if (savedTag != tagNum) {
                        // Error message Mismatch
                        if (savedTag == -1) {
                            ////////////////////////////////////////
                            // <TagName />
                            // �ϳ��� ������ ��쵵 �ִ�.
                            ////////////////////////////////////////////
                        } else {
#ifdef USER_DEBUG
                            Rprintf("Mismatching !\r\n");
#endif
                        }

                        return;
                    }

                    isData = FALSE;

                    if (strlen(tagData)) {
                        //////////////////////////////////////////////////////
                        // Send Tage and its data to somewhere which is needed 
                        // ProcessTagNValue(tagNum, tagData,  iApiReq,  lpDataBuffer);
                        ProcessTagNValue(tagNum, tagData, iApiReq, gbTmpRespBuf);
                        //////////////////////////////////////////////////////
                        k = 0;
                        memset(tagData, 0x0, sizeof (tagData));
                    } else {
                        memset(tagData, 0x0, sizeof (tagData));
                        k = 0;
                    }

                    ProcessEndTag(iApiReq, tagNum);
                } else {
                    ProcessStartTag(iApiReq, tagNum);

                    isData = TRUE;
                    push(tagNum);
                    memset(tagData, 0x0, sizeof (tagData));
                    k = 0;
                }

                memset(tagName, 0x0, sizeof (tagName));
            } else if (leftB) // <
            {
                if (ch == '/') {
                    rightB = TRUE;
                } else if (ch == '?') {
                    if (startXML) {
                        //startXML = false;
                    } else {
                        startXML = TRUE;
                    }
                } else {
                    tagName[j++] = ch;
                }
            } else// if(isData)
            {
                if (isalnum(ch)) {
                    tagData[k++] = ch;
                } else if ((ch == '"') || (ch == '?') || (ch == ':') || (ch == '.')\
					|| (ch == '/') || (ch == '|') || (ch == ',') || (ch == '~') || (ch == '-') \
					|| (ch == '&') || (ch == '=') || (ch == '_') || (ch == ' ')) {
                    tagData[k++] = ch;
                }
            }
        }
    }
}

int GetHostAndMethod(int iApiReq, char *pHostAddr, char *pMethodName) {
    int iFuncClass, iAppIdx, iFuncIndex;
    int i, iCnt, isFound = FALSE;
    char sz32Name[30], sz128Url[128];
    char *ptr;

    iFuncClass = (iApiReq >> 12) & 0x0F;
    iFuncIndex = iApiReq & 0x0FFF;
    if (iFuncClass == 0) {
        if (iFuncIndex == 0) {
            // static url
            strcpy(pHostAddr, "41.58.130.139:80"); // entered from special function
            strcpy(pMethodName, "/tams/appllist.php"); // entered from special function
            return 0;
        } else if (iFuncIndex == 1) {
            // based on the url element of the application list
            strcpy(sz128Url, pstAppList[giApplIdx].sz128Url);
            isFound = TRUE;
        }
    } else if (iFuncClass == 1) {
        iAppIdx = 0;
        strcpy(sz32Name, sTAMSFunctionList[iFuncIndex]);
    } else if (iFuncClass == 2) {
        iAppIdx = 1;
        strcpy(sz32Name, sVoucherFunctionList[iFuncIndex]);
    } else if (iFuncClass == 3) {
        iAppIdx = 2;
        strcpy(sz32Name, sBankFunctionList[iFuncIndex]);
    }
    if (isFound == FALSE) {
        //		Rprintf("sz32Name = %s\r\n", sz32Name);
        //		Rprintf("iAppIdx = %d, usFuncListCnt = %d\r\n", iAppIdx, pstAppList[iAppIdx].usFuncListCnt);
        iCnt = pstAppList[iAppIdx].usFuncListCnt;
        if (iCnt <= 0 || iCnt > MAX_FUNCLIST_CNT)
            iCnt = 0;
        for (i = 0; i < iCnt; i++) {
            if (!strcmp(pstAppList[iAppIdx].stFuncList[i].sz32Name, sz32Name)) {
                isFound = TRUE;
                strcpy(sz128Url, pstAppList[iAppIdx].stFuncList[i].sz128Url);
                break;
            }
        }
    }
    if (isFound == FALSE) {
        // ERROR
        return -1;
    }

    if (memcmp(sz128Url, "http://", 7) != 0) {
        // ERROR
        return -2;
    }
    if ((ptr = strchr(&sz128Url[7], '/')) == NULL) {
        // ERROR
        return -2;
    }
    i = ptr - &sz128Url[7];
    memcpy(pHostAddr, &sz128Url[7], i);
    pHostAddr[i] = 0x00;
    strcpy(pMethodName, ptr);

    return 0;
}

extern char *pfnAsc2Hex(U08 *hexBuf, U08 *ascBuf, int nx);

int BuildHtmlRequestMessage(int iApiReq, char *pParams, char *pContents) {
    int i, len;
    char szHostAddr[64], szMethodName[2048];
    char temp[256];
    char msg[256], sign[256];

    if (GetHostAndMethod(iApiReq, szHostAddr, szMethodName) != 0) {
#ifdef USER_DEBUG
        Rprintf("Can not find the function!\r\n");
#endif
        return -1;
    }
    if (pParams) {
        if (strlen(pParams) > 0) {
            strcat(szMethodName, "?");
            strcat(szMethodName, pParams);
        }
    }
    sprintf((char *) ucTxBuf, "POST %s HTTP/1.1\r\n", szMethodName);

    sprintf(temp, "Host: %s\r\n", szHostAddr);
    strcat((char *) ucTxBuf, temp);
    strcat((char *) ucTxBuf, "User-Agent: TAMS/3.0\r\n");
    strcat((char *) ucTxBuf, "Accept: application/xml\r\n");
    strcat((char *) ucTxBuf, "Content-Type: application/x-www-form-urlencoded\r\n");
    sprintf(temp, "Terminal: %s\r\n", st_POSSetupInfo.sz9TerminalID); // "20500022" for testing
    strcat((char *) ucTxBuf, temp);

    pfnAsc2Hex(msg, stSessionKey.ucSessionKey[0], 32);

    SHA256_Signature(sign, pParams);
    sprintf(temp, "Sign: S%s\r\n", sign);
    strcat((char *) ucTxBuf, temp);

    len = strlen(pContents);
    sprintf(temp, "Content-Length: %d\r\n", len);
    strcat((char *) ucTxBuf, temp);
    strcat((char *) ucTxBuf, "\r\n");
    if (len) {
        strcat((char *) ucTxBuf, pContents);
    }

    return strlen(ucTxBuf);
}

int GetApplIdx(int iAppId) {
    int i;

    for (i = 0; i < MAX_APPLIST_CNT; i++) {
        //		if(stAppList[i].usMagicNo != MAGICNO_APPLIST)
        //			continue;
        if (iAppId == pstAppList[i].usApplId)
            break;
    }
    if (i == MAX_APPLIST_CNT)
        return -1;

    return i;
}










// 256 
#define SHA256_DIGEST_LENGTH 32
#define SHA256_BLOCK_LENGTH  64

// 384 
#define  SHA384_BLOCK_LENGTH   128 
#define  SHA384_DIGEST_LENGTH   48 


// 512
#define SHA512_DIGEST_LENGTH 64 
#define SHA512_BLOCK_LENGTH  128 

#define SHA256_SHORT_BLOCK_LENGTH (SHA256_BLOCK_LENGTH - 8)
#define SHA384_SHORT_BLOCK_LENGTH (SHA384_BLOCK_LENGTH - 16)
#define SHA512_SHORT_BLOCK_LENGTH (SHA512_BLOCK_LENGTH - 16)

// SHA1
#define SHA1_DIGEST_STRING_LENGTH 21
#define SHA256_DIGEST_STRING_LENGTH   (SHA256_DIGEST_LENGTH * 2 + 1) 
#define  SHA384_DIGEST_STRING_LENGTH  (SHA384_DIGEST_LENGTH * 2 + 1) 
#define SHA512_DIGEST_STRING_LENGTH   (SHA512_DIGEST_LENGTH * 2 + 1) 


#define __int8 char
#define __int32 int
#define __int64 long long

typedef unsigned __int8 sha2_byte; /* Exactly 1 byte */
typedef unsigned __int32 sha2_word32; /* Exactly 4 bytes */
typedef unsigned __int64 sha2_word64; /* Exactly 8 bytes */
typedef unsigned char byte; /* Exactly 8 bytes */


/* Shift-right (used in SHA-256, SHA-384, and SHA-512): */
#define R(b,x)   ((x) >> (b))
/* 32-bit Rotate-right (used in SHA-256): */
#define _S32(b,x) (((x) >> (b)) | ((x) << (32 - (b))))
/* 64-bit Rotate-right (used in SHA-384 and SHA-512): */
#define _S64(b,x) (((x) >> (b)) | ((x) << (64 - (b))))

/* Two of six logical functions used in SHA-256, SHA-384, and SHA-512: */
#define Ch(x,y,z) (((x) & (y)) ^ ((~(x)) & (z)))
#define Maj(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))


/* Four of six logical functions used in SHA-256: */
#define Sigma0_256(x) (_S32(2,  (x)) ^ _S32(13, (x)) ^ _S32(22, (x)))
#define Sigma1_256(x) (_S32(6,  (x)) ^ _S32(11, (x)) ^ _S32(25, (x)))
#define sigma0_256(x) (_S32(7,  (x)) ^ _S32(18, (x)) ^ R(3 ,   (x)))
#define sigma1_256(x) (_S32(17, (x)) ^ _S32(19, (x)) ^ R(10,   (x)))

/* Four of six logical functions used in SHA-384 and SHA-512: */
#define Sigma0_512(x) (_S64(28, (x)) ^ _S64(34, (x)) ^ _S64(39, (x)))
#define Sigma1_512(x) (_S64(14, (x)) ^ _S64(18, (x)) ^ _S64(41, (x)))
#define sigma0_512(x) (_S64( 1, (x)) ^ _S64( 8, (x)) ^ R( 7,   (x)))
#define sigma1_512(x) (_S64(19, (x)) ^ _S64(61, (x)) ^ R( 6,   (x)))

typedef struct _SHA256_CTX {
    unsigned __int32 state[8];
    unsigned __int64 bitcount;
    unsigned __int8 buffer[SHA256_BLOCK_LENGTH];
} SHA256_CTX;

typedef struct _SHA512_CTX {
    unsigned __int64 state[8];
    unsigned __int64 bitcount[2];
    unsigned __int8 buffer[SHA512_BLOCK_LENGTH];
} SHA512_CTX;

typedef SHA512_CTX SHA384_CTX;

static const char *sha2_hex_digits = "0123456789abcdef";


const static sha2_word32 K256[64] = {
    0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
    0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
    0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
    0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
    0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
    0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
    0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
    0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
    0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
    0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
    0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
    0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
    0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
    0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
    0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
    0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL
};

const static sha2_word32 sha256_initial_hash_value[8] = {
    0x6a09e667UL,
    0xbb67ae85UL,
    0x3c6ef372UL,
    0xa54ff53aUL,
    0x510e527fUL,
    0x9b05688cUL,
    0x1f83d9abUL,
    0x5be0cd19UL
};

/*
 * Macro for incrementally adding the unsigned 64-bit integer n to the
 * unsigned 128-bit integer (represented using a two-element array of
 * 64-bit words):
 */
#define ADDINC128(w,n) { \
        (w)[0] += (sha2_word64)(n); \
        if ((w)[0] < (n)) { \
                (w)[1]++; \
        } \
}


#define REVERSE32(w,x) { \
        sha2_word32 tmp = (w); \
        tmp = (tmp >> 16) | (tmp << 16); \
        (x) = ((tmp & 0xff00ff00UL) >> 8) | ((tmp & 0x00ff00ffUL) << 8); \
}
#define REVERSE64(w,x) { \
        sha2_word64 tmp = (w); \
        tmp = (tmp >> 32) | (tmp << 32); \
        tmp = ((tmp & 0xff00ff00ff00ff00ULL) >> 8) | \
              ((tmp & 0x00ff00ff00ff00ffULL) << 8); \
        (x) = ((tmp & 0xffff0000ffff0000ULL) >> 16) | \
              ((tmp & 0x0000ffff0000ffffULL) << 16); \
}


#if BYTE_ORDER == LITTLE_ENDIAN

#define ROUND256_0_TO_15(a,b,c,d,e,f,g,h) \
        REVERSE32(*data++, W256[j]); \
        T1 = (h) + Sigma1_256(e) + Ch((e), (f), (g)) + \
             K256[j] + W256[j]; \
        (d) += T1; \
        (h) = T1 + Sigma0_256(a) + Maj((a), (b), (c)); \
        j++


#else /* BYTE_ORDER == LITTLE_ENDIAN */

#define ROUND256_0_TO_15(a,b,c,d,e,f,g,h) \
        T1 = (h) + Sigma1_256(e) + Ch((e), (f), (g)) + \
             K256[j] + (W256[j] = *data++); \
        (d) += T1; \
        (h) = T1 + Sigma0_256(a) + Maj((a), (b), (c)); \
        j++

#endif /* BYTE_ORDER == LITTLE_ENDIAN */


#define ROUND256(a,b,c,d,e,f,g,h) \
        s0 = W256[(j+1)&0x0f]; \
        s0 = sigma0_256(s0); \
        s1 = W256[(j+14)&0x0f]; \
        s1 = sigma1_256(s1); \
        T1 = (h) + Sigma1_256(e) + Ch((e), (f), (g)) + K256[j] + \
             (W256[j&0x0f] += s1 + W256[(j+9)&0x0f] + s0); \
        (d) += T1; \
        (h) = T1 + Sigma0_256(a) + Maj((a), (b), (c)); \
        j++



const static sha2_word64 sha512_initial_hash_value[8] = {
    0x6a09e667f3bcc908ULL,
    0xbb67ae8584caa73bULL,
    0x3c6ef372fe94f82bULL,
    0xa54ff53a5f1d36f1ULL,
    0x510e527fade682d1ULL,
    0x9b05688c2b3e6c1fULL,
    0x1f83d9abfb41bd6bULL,
    0x5be0cd19137e2179ULL
};

/* Hash constant words K for SHA-384 and SHA-512: */
const static sha2_word64 K512[80] = {
    0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
    0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
    0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
    0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
    0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
    0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
    0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
    0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
    0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
    0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
    0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
    0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
    0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
    0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
    0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
    0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
    0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
    0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
    0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
    0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
    0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
    0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
    0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
    0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
    0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
    0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
    0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
    0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
    0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
    0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
    0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
    0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
    0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
    0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
    0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
    0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
    0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
    0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};

/* Initial hash value H for SHA-384 */
const static sha2_word64 sha384_initial_hash_value[8] = {
    0xcbbb9d5dc1059ed8ULL,
    0x629a292a367cd507ULL,
    0x9159015a3070dd17ULL,
    0x152fecd8f70e5939ULL,
    0x67332667ffc00b31ULL,
    0x8eb44a8768581511ULL,
    0xdb0c2e0d64f98fa7ULL,
    0x47b5481dbefa4fa4ULL
};




#ifndef _RC4_H_
#define _RC4_H_

struct rc4_state {
    u_char perm[256];
    u_char index1;
    u_char index2;
};

typedef struct _RC_STATE {
    u_char perm[256];
    u_char index1;
    u_char index2;
} RC_STATE;

void rc4_init(struct rc4_state * const state, const u_char *key, int keylen);
void rc4_crypt(struct rc4_state * const state, const u_char *inbuf, u_char *outbuf, int buflen);

#endif

#if 1
///////////////////////////// RC4 /////////////////////

static __inline void
swap_bytes(u_char *a, u_char *b) {
    u_char temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Initialize an RC4 state buffer using the supplied key,
 * which can have arbitrary length.
 */
void rc4_init(struct rc4_state * const state, const u_char *key, int keylen) {
    u_char j;
    int i;

    /* Initialize state with identity permutation */
    for (i = 0; i < 256; i++)
        state->perm[i] = (u_char) i;

    state->index1 = 0;
    state->index2 = 0;

    /* Randomize the permutation using key data */
    for (j = i = 0; i < 256; i++) {
        j += state->perm[i] + key[i % keylen];
        swap_bytes(&state->perm[i], &state->perm[j]);
    }
}

/*
 * Encrypt some data using the supplied RC4 state buffer.
 * The input and output buffers may be the same buffer.
 * Since RC4 is a stream cypher, this function is used
 * for both encryption and decryption.
 */
void
rc4_crypt(struct rc4_state * const state,
        const u_char *inbuf, u_char *outbuf, int buflen) {
    int i;
    u_char j;

    for (i = 0; i < buflen; i++) {

        /* Update modification indicies */
        state->index1++;
        state->index2 += state->perm[state->index1];

        /* Modify permutation */
        swap_bytes(&state->perm[state->index1],
                &state->perm[state->index2]);

        /* Encrypt/decrypt next byte */
        j = state->perm[state->index1] + state->perm[state->index2];
        outbuf[i] = inbuf[i] ^ state->perm[j];
    }
}
#endif


///////////////////////// New SHA256 from BSD ////////////////

/*** SHA-256: *********************************************************/

void SHA256_Transform(SHA256_CTX* context, const sha2_word32* data) {
    sha2_word32 a, b, c, d, e, f, g, h, s0, s1;
    sha2_word32 T1, *W256;
    int j;


    W256 = (sha2_word32*) context->buffer;


    /* Initialize registers with the prev. intermediate value */
    a = context->state[0];
    b = context->state[1];
    c = context->state[2];
    d = context->state[3];
    e = context->state[4];
    f = context->state[5];
    g = context->state[6];
    h = context->state[7];

    j = 0;
    do {
        /* Rounds 0 to 15 (unrolled): */
        ROUND256_0_TO_15(a, b, c, d, e, f, g, h);
        ROUND256_0_TO_15(h, a, b, c, d, e, f, g);
        ROUND256_0_TO_15(g, h, a, b, c, d, e, f);
        ROUND256_0_TO_15(f, g, h, a, b, c, d, e);
        ROUND256_0_TO_15(e, f, g, h, a, b, c, d);
        ROUND256_0_TO_15(d, e, f, g, h, a, b, c);
        ROUND256_0_TO_15(c, d, e, f, g, h, a, b);
        ROUND256_0_TO_15(b, c, d, e, f, g, h, a);
    } while (j < 16);

    /* Now for the remaining rounds to 64: */
    do {
        ROUND256(a, b, c, d, e, f, g, h);
        ROUND256(h, a, b, c, d, e, f, g);
        ROUND256(g, h, a, b, c, d, e, f);
        ROUND256(f, g, h, a, b, c, d, e);
        ROUND256(e, f, g, h, a, b, c, d);
        ROUND256(d, e, f, g, h, a, b, c);
        ROUND256(c, d, e, f, g, h, a, b);
        ROUND256(b, c, d, e, f, g, h, a);
    } while (j < 64);

    /* Compute the current intermediate hash value */
    context->state[0] += a;
    context->state[1] += b;
    context->state[2] += c;
    context->state[3] += d;
    context->state[4] += e;
    context->state[5] += f;
    context->state[6] += g;
    context->state[7] += h;

    /* Clean up */
    a = b = c = d = e = f = g = h = T1 = 0;
}

void SHA256_Init(SHA256_CTX* context) {
    if (context == (SHA256_CTX*) 0) {
        return;
    }

    memcpy(context->state, sha256_initial_hash_value, SHA256_DIGEST_LENGTH);
    memset(context->buffer, 0x00, SHA256_BLOCK_LENGTH);

    context->bitcount = 0;

}

void SHA256_Update(SHA256_CTX* context, const sha2_byte *data, size_t len) {
    unsigned int freespace, usedspace;

    if (len == 0) {
        /* Calling with no data is valid - we do nothing */
        return;
    }

    /* Sanity check: */
    //ASSERT(context != (SHA256_CTX*)0 && data != (sha2_byte*)0);

    usedspace = (context->bitcount >> 3) % SHA256_BLOCK_LENGTH;
    if (usedspace > 0) {
        /* Calculate how much free space is available in the buffer */
        freespace = SHA256_BLOCK_LENGTH - usedspace;

        if (len >= freespace) {
            /* Fill the buffer completely and process it */
            //bcopy(data, &context->buffer[usedspace], freespace);
            memcpy(&context->buffer[usedspace], data, freespace);
            context->bitcount += freespace << 3;
            len -= freespace;
            data += freespace;
            SHA256_Transform(context, (sha2_word32*) context->buffer);
        } else {
            /* The buffer is not yet full */
            //bcopy(data, &context->buffer[usedspace], len);
            memcpy(&context->buffer[usedspace], data, len);
            context->bitcount += len << 3;
            /* Clean up: */
            usedspace = freespace = 0;
            return;
        }
    }
    while (len >= SHA256_BLOCK_LENGTH) {
        /* Process as many complete blocks as we can */
        SHA256_Transform(context, (const sha2_word32*) data);
        context->bitcount += SHA256_BLOCK_LENGTH << 3;
        len -= SHA256_BLOCK_LENGTH;
        data += SHA256_BLOCK_LENGTH;
    }
    if (len > 0) {
        /* There's left-overs, so save 'em */
        //bcopy(data, context->buffer, len);
        memcpy(context->buffer, data, len);
        context->bitcount += len << 3;
    }
    /* Clean up: */
    usedspace = freespace = 0;
}

void SHA256_Final(sha2_byte digest[], SHA256_CTX* context) {
    sha2_word32 *d = (sha2_word32*) digest;
    unsigned int usedspace;

    /* Sanity check: */
    //ASSERT(context != (SHA256_CTX*)0);

    /* If no digest buffer is passed, we don't bother doing this: */
    if (digest != (sha2_byte*) 0) {
        usedspace = (context->bitcount >> 3) % SHA256_BLOCK_LENGTH;
#if BYTE_ORDER == LITTLE_ENDIAN
        /* Convert FROM host byte order */
        REVERSE64(context->bitcount, context->bitcount);
#endif
        if (usedspace > 0) {
            /* Begin padding with a 1 bit: */
            context->buffer[usedspace++] = 0x80;

            if (usedspace < SHA256_SHORT_BLOCK_LENGTH) {
                /* Set-up for the last transform: */
                //bzero(&context->buffer[usedspace], SHA256_SHORT_BLOCK_LENGTH - usedspace);
                memset(&context->buffer[usedspace], 0x00, SHA256_SHORT_BLOCK_LENGTH - usedspace);
            } else {
                if (usedspace < SHA256_BLOCK_LENGTH) {
                    //bzero(&context->buffer[usedspace], SHA256_BLOCK_LENGTH - usedspace);
                    memset(&context->buffer[usedspace], 0x00, SHA256_BLOCK_LENGTH - usedspace);
                }
                /* Do second-to-last transform: */
                SHA256_Transform(context, (sha2_word32*) context->buffer);

                /* And set-up for the last transform: */
                //bzero(context->buffer, SHA256_SHORT_BLOCK_LENGTH);
                memset(context->buffer, 0x00, SHA256_SHORT_BLOCK_LENGTH);
            }
        } else {
            /* Set-up for the last transform: */
            //bzero(context->buffer, SHA256_SHORT_BLOCK_LENGTH);
            memset(context->buffer, 0x00, SHA256_SHORT_BLOCK_LENGTH);

            /* Begin padding with a 1 bit: */
            *context->buffer = 0x80;
        }
        /* Set the bit count: */
        *(sha2_word64*)&context->buffer[SHA256_SHORT_BLOCK_LENGTH] = context->bitcount;

        /* Final transform: */
        SHA256_Transform(context, (sha2_word32*) context->buffer);

#if BYTE_ORDER == LITTLE_ENDIAN
        {
            /* Convert TO host byte order */
            int j;
            for (j = 0; j < 8; j++) {
                REVERSE32(context->state[j], context->state[j]);
                *d++ = context->state[j];
            }
        }
#else
        bcopy(context->state, d, SHA256_DIGEST_LENGTH);
#endif
    }

    /* Clean up state data: */
    //bzero(context, sizeof(context));
    memset(context, 0x00, sizeof (context));
    usedspace = 0;
}

char *SHA256_End(SHA256_CTX* context, char buffer[]) {
    sha2_byte digest[SHA256_DIGEST_LENGTH], *d = digest;
    int i;

    /* Sanity check: */
    //ASSERT(context != (SHA256_CTX*)0);

    if (buffer != (char*) 0) {
        SHA256_Final(digest, context);

        for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            *buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
            *buffer++ = sha2_hex_digits[*d & 0x0f];
            d++;
        }
        *buffer = (char) 0;
    } else {
        //bzero(context, sizeof(context));
        memset(context, 0x00, sizeof (context));
    }
    //bzero(digest, SHA256_DIGEST_LENGTH);
    memset(digest, 0x00, SHA256_DIGEST_LENGTH);
    return buffer;
}


// strret = SHA256_Data((sha2_byte *)BinEncSessionKey, 16, digest256, requestBody);
///////////////////////// SHA256 Main ///////////////////////////////////////////////// 

char* SHA256_Data(sha2_byte* data, size_t len, char digest[SHA256_DIGEST_STRING_LENGTH], const char *Body) {
    SHA256_CTX context;

    SHA256_Init(&context);
    SHA256_Update(&context, data, len);
    if (Body != NULL) {
        SHA256_Update(&context, (sha2_byte *) Body, strlen(Body));
    }
    return SHA256_End(&context, digest);
}

void hexStringToByteArray(char *hexstring, unsigned char *out) {
    int i = 0;
    int len;
    int j = 0;

    len = strlen(hexstring);

    if (hexstring == NULL || len <= 0)
        return;

    //char stringvectorCAP[]="0123456789ABCDEF";
    char stringvector[] = "0123456789abcdef";
    byte bytevector[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    //byte *out = new BYTE[16];
    //unsigned char out[16];
    int index;

    while (i < len - 1) {
        byte ch = 0x00;

        for (index = 0; index < 16; index++) {
            if (hexstring[i] == stringvector[index]) {
                break;
            }
        }
        //Convert high nibble charater to a hex byte
        ch = (byte) (ch | bytevector[index]);
        ch = (byte) (ch << 4);

        //Convert the low nibble to a hexbyte
        for (index = 0; index < 16; index++) {
            if (hexstring[i + 1] == stringvector[index]) {
                break;
            }
        }

        ch = (byte) (ch | bytevector[index]);
        out[i / 2] = ch;
        i++;
        i++;
    }

    return;
}

char *MasterKeyTID = "7d0c456606ed1edef3232ed742a7289f0000000020500022";

int GetValueOnly(char *pValueOnly, char *pParams) {
    int len, idx;
    char *pEntrySep, *pKeyValSep;
    char *pCurPos;

    idx = 0;
    pCurPos = pParams;
    while (1) {
        if ((pKeyValSep = strchr(pCurPos, '=')) == NULL) { // No more key-value-pair
            pValueOnly[idx] = 0x00;
            break;
        }
        pEntrySep = strchr(pCurPos, '&');
        if (pEntrySep == NULL) { // No more entries
            pValueOnly[idx] = 0x00;
            strcat(pValueOnly, pKeyValSep + 1);
            idx += strlen(pKeyValSep + 1);
            break;
        }
        len = pEntrySep - (pKeyValSep + 1);
        memcpy(&pValueOnly[idx], pKeyValSep + 1, len);
        idx += len;
        pCurPos = pEntrySep + 1;
    }

    return idx;
}

//�׽�Ʈ �� �Ǵ� �͹̳� ID
//const char MasterKey[33] = "d944f8a45468da2f0f77a41ac04aea36";
//const char TerminalID[17] = "0000000020500022";

//const char MasterKey[33] = "3febe4a400c7b17081b87b8889c4f9c8";
//const char TerminalID[17] = "0000000000987654";

//const char MasterKey[33] = "9777c6788f5ee44cfee794612dc1f696";
//const char TerminalID[17] = "12345678";

int GetDecryptedSessionKey(int iIndex, char *pOutBuf) {
    int i, len;
    int KeySize = 16;
    int MasterKeyLength = 32;
    char MasterKeyNTermID[33];
    unsigned char tempBinSessionKey[17];
    unsigned char KeyOutBuf[17];
    struct rc4_state state;

    memset(MasterKeyNTermID, 0x0, sizeof (MasterKeyNTermID));

    asc2bcd(MasterKeyNTermID, pstMasterKey->ucMasterKey, 32);
    memset(&MasterKeyNTermID[16], '0', 16);
    len = strlen(st_POSSetupInfo.sz9TerminalID);
    strcpy(&MasterKeyNTermID[16 + 16 - len], st_POSSetupInfo.sz9TerminalID);

    rc4_init(&state, (u_char *) MasterKeyNTermID, MasterKeyLength);
    for (i = 0; i < iIndex + 1; i++) {
        memset(tempBinSessionKey, 0x00, sizeof (tempBinSessionKey));
        memset(KeyOutBuf, 0x00, sizeof (KeyOutBuf));
        asc2bcd(tempBinSessionKey, stSessionKey.ucSessionKey[i], 32);
        rc4_crypt(&state, tempBinSessionKey, &KeyOutBuf[0], KeySize);
    }

    memcpy(pOutBuf, KeyOutBuf, KeySize);

    return 0;
}

int SHA256_Signature(char *pSignBuf, char *pParams) {
    int i, j, k, len;
    char digest256[SHA256_DIGEST_STRING_LENGTH];
    unsigned char KeyOutBuf[17];
    struct rc4_state state;

    /*
    memcpy(stSessionKey.ucSessionKey[0], "5eba733841d62738dd848de4119eb33e", 32);
    memcpy(stSessionKey.ucSessionKey[1], "af9503c4e151a65af80cef41bbebab3b", 32);
    memcpy(stSessionKey.ucSessionKey[2], "df2c9e8e0eb5af3f7a03cd3e46d6d758", 32);
    memcpy(stSessionKey.ucSessionKey[3], "c27ab03fadcabe2a40bac47da3de1fa1", 32);
    memcpy(stSessionKey.ucSessionKey[4], "2a81ca0f6948fe4b56a0753f37beb5fd", 32);
    memcpy(stSessionKey.ucSessionKey[5], "f3a4d46eab5dcbf0db44ae51f81ba0f4", 32);
    memcpy(stSessionKey.ucSessionKey[6], "3e874fc53e595769416b7cf3c187df3e", 32);
    memcpy(stSessionKey.ucSessionKey[7], "5bf0e67e4001cd587a31f58a45e6c7ee", 32);
    memcpy(stSessionKey.ucSessionKey[8], "c7f17a70d3543cbbdda6a0aeb2bbf9cd", 32);
    memcpy(stSessionKey.ucSessionKey[9], "b14085304f832f5ca3c7a452fbbbfb22", 32);
     */
    GetDecryptedSessionKey(1, KeyOutBuf);
    memset(&gbTmpRespBuf[0], 0x00, sizeof (gbTmpRespBuf));
    if (strlen(pParams) > 0) {
        GetValueOnly(&gbTmpRespBuf[0], pParams);
    }
    SHA256_Data((sha2_byte *) KeyOutBuf, 16, digest256, &gbTmpRespBuf[0]);

    if (pSignBuf) {
        memcpy(pSignBuf, digest256, SHA256_DIGEST_STRING_LENGTH);
    }

    return 0;
}

int GetEncryptedTrack2(char *pTrack2, char *pOutBuf) {
    int i, len;
    struct rc4_state state;
    unsigned char KeyOutBuf[128];
    char SKey[16];

    GetDecryptedSessionKey(2, SKey);
    len = strlen(pTrack2);
    rc4_init(&state, (u_char *) SKey, 16);
    rc4_crypt(&state, (u_char *) pTrack2, KeyOutBuf, len);

    for (i = 0; i < len; i++) {
        sprintf(&pOutBuf[i * 2], "%02X", KeyOutBuf[i] & 0xFF);
    }
    pOutBuf[i * 2] = 0x00;

    return 0;
}

#if 0

const char RespAppList[2048] = "<appllist><applsvr><applid>1</applid><name>Tams</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr><applsvr><applid>2</applid><name>VoucherVault</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr><applsvr><applid>3</applid><name>Banking</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr></appllist>";
const char RespFuncList[2048] = "<funclist><function><name>BINTABLE</name><url>http://41.58.130.139/tams/eftpos/devinterface/bintables.php</url></function><function><name>BIOTEMPLATE</name><url>http://41.58.130.139/tams/eftpos/devinterface/biotemplate.php</url></function><function><name>BIOTRAN</name><url>http://41.58.130.139/tams/eftpos/devinterface/biotran.php</url></function><function><name>DISTORDER</name><url>http://41.58.130.139/tams/eftpos/devinterface/distorder.php</url></function><function><name>DISTRETURN</name><url>http://41.58.130.139/tams/eftpos/devinterface/distreturn.php</url></function><function><name>EFTPARAMS</name><url>http://41.58.130.139/tams/eftpos/devinterface/eftparams.php</url></function><function><name>EFTTOTALS</name><url>http://41.58.130.139/tams/eftpos/devinterface/efttotals.php</url></function><function><name>EFTTRAN</name><url>http://41.58.130.139/tams/eftpos/devinterface/transaction.php</url></function><function><name>EMVAPP</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvapp.php</url></function><function><name>EMVCAPK</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvcapk.php</url></function><function><name>EMVREVOKECAPK</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvrevokecapk.php</url></function><function><name>EODTXNLIST</name><url>http://41.58.130.139/tams/eftpos/devinterface/txnlist.php</url></function><function><name>HOTCARDS</name><url>http://41.58.130.139/tams/eftpos/devinterface/hotcards.php</url></function><function><name>LINKED</name><url>http://41.58.130.139/tams/eftpos/devinterface/linked.php</url></function><function><name>UPLOADTXN</name><url>http://41.58.130.139/tams/eftpos/devinterface/uploadtxn.php</url></function></funclist>";
const char RespNewKey[2048] = "<newkey><masterkey>9777c6788f5ee44cfee794612dc1f696</masterkey></newkey>";
//const char RespGetKey[2048] = "<getkeys><cipher><no>0</no><key>9af9272716f60dc7d40d164b7aa56129</key></cipher><cipher><no>1</no><key>c989e9e439ab4d73fb33b549ebcbed16</key></cipher><cipher><no>2</no><key>bfca244ca3a2ef99833a6a5dfb9adfff</key></cipher><cipher><no>3</no><key>616f61f7df1e35fce8be08000e5b4edd</key></cipher><cipher><no>4</no><key>654dbfa37ca9af2e91082a4413dc5621</key></cipher><cipher><no>5</no><key>d89854e6ab10fd3b78d0a7fae3767eeb</key></cipher><cipher><no>6</no><key>529210d90e5ddc92b36e1163665fc054</key></cipher><cipher><no>7</no><key>19735e6aeb0f64b617d715e0f7c9d664</key></cipher><cipher><no>8</no><key>6090cd4f5c0117ca849da1fd0f5038bd</key></cipher><cipher><no>9</no><key>f3f9009c9bd309fd7d93cadd4a2b97d5</key></cipher></getkeys>";
const char RespGetKey[2048] = "<getkeys><cipher><no>0</no><key>a34ba29583b1cf5b750a23ba011ac47d</key></cipher><cipher><no>1</no><key>7326ba48019a4d3dada0c69614b40392</key></cipher><cipher><no>2</no><key>38a8366080eae6c343c1001da7d3d6aa</key></cipher><cipher><no>3</no><key>39888c066a42733187b58a95fa4a2c75</key></cipher><cipher><no>4</no><key>54127e8fe21d4ed02012eb226a26789c</key></cipher><cipher><no>5</no><key>5b90154e81b46a87a36c8da1b65d02fd</key></cipher><cipher><no>6</no><key>77644629757ed174e86f2f3ac301856a</key></cipher><cipher><no>7</no><key>32d097aab93395afe3a79bc7b6f6a66e</key></cipher><cipher><no>8</no><key>f1e6e288b00aba1e86c06af6963d715c</key></cipher><cipher><no>9</no><key>b17601f2ac2b60049763a0b6b3f111ce</key></cipher></getkeys>";
const char RespEftParams[2048] = "<eftparam><online>0</online><maxcashback>0</maxcashback><minbudgetperiod>0</minbudgetperiod><maxbudgetperiod>60</maxbudgetperiod><budgetminamount>0</budgetminamount><velocitytime>0</velocitytime><manualonline>N</manualonline><updatebin>1315221795</updatebin><updatehot>1253782759</updatehot><eodtxnlist>Y</eodtxnlist></eftparam>";
const char RespBinTable[2048] = "<bintable><bin><pan>506120</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>1</keyindex></bin><bin><pan>412053</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>125</check><allow>4031</allow><keyindex>1</keyindex></bin></bintable>";
const char RespHotCard[2048] = "<hotcards><pan>4565123412341111</pan><pan>4424349999968937</pan><pan>4565123412342222</pan><pan>4565123412343333</pan><pan>4565123412344444</pan></hotcards>";
const char RespEmvApp[4096] = "<emv><count>6</count><app><index>0</index><irn>1</irn><aid>A0000000032010</aid><match>0</match><name>Visa Electron</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>1</index><irn>2</irn><aid>A0000000031010</aid><match>0</match><name>Visa Credit</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>2</index><irn>3</irn><aid>A0000000041010</aid><match>0</match><name>MasterCard</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>3</index><irn>4</irn><aid>A0000000042010</aid><match>0</match><name>MasterCard Maestro</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>4</index><irn>5</irn><aid>A0000003710001</aid><match>0</match><name>Interswitch Verve</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>5</index><irn>6</irn><aid>A0000004540010</aid><match>0</match><name>eTranzact Genesis</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app></emv>";
const char RespEmvCapk[8192] = "<calist><count>10</count><ca><index>01</index><irn>1</irn><name>1</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>C696034213D7D8546984579D1D0F0EA519CFF8DEFFC429354CF3A871A6F7183F1228DA5C7470C055387100CB935A712C4E2864DF5D64BA93FE7E63E71F25B1E5F5298575EBE1C63AA617706917911DC2A75AC28B251C7EF40F2365912490B939BCA2124A30A28F54402C34AECA331AB67E1E79B285DD5771B5D9FF79EA630B75</modulus><exponent>03</exponent><hash>D34A6A776011C7E7CE3AEC5F03AD2F8CFC5503CC</hash><pkalgo>1</pkalgo></ca><ca><index>07</index><irn>2</irn><name>2</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>A89F25A56FA6DA258C8CA8B40427D927B4A1EB4D7EA326BBB12F97DED70AE5E4480FC9C5E8A972177110A1CC318D06D2F8F5C4844AC5FA79A4DC470BB11ED635699C17081B90F1B984F12E92C1C529276D8AF8EC7F28492097D8CD5BECEA16FE4088F6CFAB4A1B42328A1B996F9278B0B7E3311CA5EF856C2F888474B83612A82E4E00D0CD4069A6783140433D50725F</modulus><exponent>03</exponent><hash>B4BC56CC4E88324932CBC643D6898F6FE593B172</hash><pkalgo>1</pkalgo></ca><ca><index>08</index><irn>3</irn><name>3</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>D9FD6ED75D51D0E30664BD157023EAA1FFA871E4DA65672B863D255E81E137A51DE4F72BCC9E44ACE12127F87E263D3AF9DD9CF35CA4A7B01E907000BA85D24954C2FCA3074825DDD4C0C8F186CB020F683E02F2DEAD3969133F06F7845166ACEB57CA0FC2603445469811D293BFEFBAFAB57631B3DD91E796BF850A25012F1AE38F05AA5C4D6D03B1DC2E568612785938BBC9B3CD3A910C1DA55A5A9218ACE0F7A21287752682F15832A678D6E1ED0B</modulus><exponent>03</exponent><hash>20D213126955DE205ADC2FD2822BD22DE21CF9A8</hash><pkalgo>1</pkalgo></ca><ca><index>09</index><irn>4</irn><name>4</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>9D912248DE0A4E39C1A7DDE3F6D2588992C1A4095AFBD1824D1BA74847F2BC4926D2EFD904B4B54954CD189A54C5D1179654F8F9B0D2AB5F0357EB642FEDA95D3912C6576945FAB897E7062CAA44A4AA06B8FE6E3DBA18AF6AE3738E30429EE9BE03427C9D64F695FA8CAB4BFE376853EA34AD1D76BFCAD15908C077FFE6DC5521ECEF5D278A96E26F57359FFAEDA19434B937F1AD999DC5C41EB11935B44C18100E857F431A4A5A6BB65114F174C2D7B59FDF237D6BB1DD0916E644D709DED56481477C75D95CDD68254615F7740EC07F330AC5D67BCD75BF23D28A140826C026DBDE971A37CD3EF9B8DF644AC385010501EFC6509D7A41</modulus><exponent>03</exponent><hash>1FF80A40173F52D7D27E0F26A146A1C8CCB29046</hash><pkalgo>1</pkalgo></ca><ca><index>55</index><irn>5</irn><name>5</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>8B2BCDC1495920A5051AB3D6506E3BFDDC946A5F03957497A4836BE735227D3FDA33FB227A4DA15093845E8A08B392471CE0BEB588D6A3EB8571C2767350C387AF8E452BCD6F9A4848D835C08EDD91DE3A61B7D13FCA77B4628334792812289D5876226501D71B3EE4516351B017BD88C494F966383458273ABF0C40E7421F5F</modulus><exponent>03</exponent><hash>B0365792C471147B3FEA46608675DE7D16701661</hash><pkalgo>1</pkalgo></ca><ca><index>08</index><irn>6</irn><name>6</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>D9FD6ED75D51D0E30664BD157023EAA1FFA871E4DA65672B863D255E81E137A51DE4F72BCC9E44ACE12127F87E263D3AF9DD9CF35CA4A7B01E907000BA85D24954C2FCA3074825DDD4C0C8F186CB020F683E02F2DEAD3969133F06F7845166ACEB57CA0FC2603445469811D293BFEFBAFAB57631B3DD91E796BF850A25012F1AE38F05AA5C4D6D03B1DC2E568612785938BBC9B3CD3A910C1DA55A5A9218ACE0F7A21287752682F15832A678D6E1ED0B</modulus><exponent>03</exponent><hash>20D213126955DE205ADC2FD2822BD22DE21CF9A8</hash><pkalgo>1</pkalgo></ca><ca><index>99</index><irn>7</irn><name>7</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>AB79FCC9520896967E776E64444E5DCDD6E13611874F3985722520425295EEA4BD0C2781DE7F31CD3D041F565F747306EED62954B17EDABA3A6C5B85A1DE1BEB9A34141AF38FCF8279C9DEA0D5A6710D08DB4124F041 945587E20359BAB47B7575AD94262D4B25F264AF33DEDCF28E09615E937DE32EDC03C54445FE7E382777</modulus><exponent>03</exponent><hash>4ABFFD6B1C51212D05552E431C5B17007D2F5E6D</hash><pkalgo>1</pkalgo></ca><ca><index>95</index><irn>8</irn><name>8</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>BE9E1FA5E9A803852999C4AB432DB28600DCD9DAB76DFAAA47355A0FE37B1508AC6BF38860D3C6C2E5B12A3CAAF2A7005A7241EBAA7771112C74CF9A0634652FBCA0E5980C54A64761EA101A114E0F0B5572ADD57D010B7C9C887E104CA4EE1272DA66D997B9A90B5A6D624AB6C57E73C8F919000EB5F684898EF8C3DBEFB330C62660BED88EA78E909AFF05F6DA627B</modulus><exponent>03</exponent><hash>EE1511CEC71020A9B90443B37B1D5F6E703030F6</hash><pkalgo>1</pkalgo></ca><ca><index>92</index><irn>9</irn><name>9</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>996AF56F569187D09293C14810450ED8EE3357397B18A2458EFAA92DA3B6DF6514EC060195318FD43BE9B8F0CC669E3F844057CBDDF8BDA191BB64473BC8DC9A730DB8F6B4EDE3924186FFD9B8C7735789C23A36BA0B8AF65372EB57EA5D89E7D14E9C7B6B557460F10885DA16AC923F15AF3758F0F03EBD3C5C2C949CBA306DB44E6A2C076C5F67E281D7EF56785DC4D75945E491F01918800A9E2DC66F60080566CE0DAF8D17EAD46AD8E30A247C9F</modulus><exponent>03</exponent><hash>429C954A3859CEF91295F663C963E582ED6EB253</hash><pkalgo>1</pkalgo></ca><ca><index>94</index><irn>11</irn><name>11</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>ACD2B12302EE644F3F835ABD1FC7A6F62CCE48FFEC622AA8EF062BEF6FB8BA8BC68BBF6AB5870EED579BC3973E121303D34841A796D6DCBC41DBF9E52C4609795C0CCF7EE86FA1D5CB041071ED2C51D2202F63F1156C58A92D38BC60BDF424E1776E2BC9648078A03B36FB554375FC53D57C73F5160EA59F3AFC5398EC7B67758D65C9BFF7828B6B82D4BE124A416AB7301914311EA462C19F771F31B3B57336000DFF732D3B83DE07052D730354D297BEC72871DCCF0E193F171ABA27EE464C6A97690943D59BDABB2A27EB71CEEBDAFA1176046478FD62FEC452D5CA393296530AA3F41927ADFE434A2DF2AE3054F8840657A26E0FC617</modulus><exponent>03</exponent><hash>C4A3C43CCF87327D136B804160E47D43B60E6E0F</hash><pkalgo>1</pkalgo></ca></calist>";
const char RespGetParams[2048] = "<param><datetime><year>2011</year><syear>11</syear><mon>09</mon><day>05</day><hour>12</hour><min>58</min><sec>39</sec></datetime><merchantid>2</merchantid><pinreset>Y</pinreset><updatelogo>N</updatelogo><updatemenu>N</updatemenu><replytimeout>60</replytimeout><currency>N</currency><fract>2</fract><prefix>Y</prefix><negnum>2</negnum><currcode>566</currcode><decsym>.</decsym><thoussep>,</thoussep><countrycode>0566</countrycode><endofday>72</endofday><updateprompts>1315223919</updateprompts><attendance>N</attendance><agentaccess>N</agentaccess><eodtime><enabled>N</enabled></eodtime><conn1>0</conn1><conn2>0</conn2><download><enabled>N</enabled><downloadconn>0</downloadconn></download><disabled>N</disabled></param>";

int TestParsing() {
    int i, j, len;
    int reqType;
    U16 iAppId = 0;

    char szHostAddr[256], szMethodName[256];
    char sign[256];
    /*
    SendRequestMessage(API_GET_APPLIST, "", "");
    SendRequestMessage(API_GET_FUNCLIST, "", "CONTENTS TEST\r\n");
    SendRequestMessage(API_TAMS_PARAM, "?ver=3.8.23&serial=8400NG43AF02008801428551", "");
     */
    reqType = API_TAMS_GETKEYS;
    NIBSS_Parsing((char *) RespGetKey, strlen(RespGetKey), reqType, &gbTmpRespBuf);


    memcpy(sign, pstMasterKey->ucMasterKey, 32);
    sign[32] = 0x00;
    Rprintf("MasterKey=%s\r\n", sign);

    SHA256_Signature(sign, "");
    Rprintf("Sign: %s\r\n", sign);

    {
        struct rc4_state state;
        unsigned char KeyOutBuf[128];
        char SKey[16];
        char *Track2 = "5061200300103988118D1402601072131861|5061200300103988118F"; // 57byte
        GetDecryptedSessionKey(2, SKey);
        len = strlen(Track2);
        rc4_init(&state, (u_char *) SKey, 16);
        rc4_crypt(&state, (u_char *) Track2, KeyOutBuf, len);

        Rprintf("Track2: ");
        for (i = 0; i < len; i++) {
            Rprintf("%02X ", KeyOutBuf[i] & 0xFF);
        }
        Rprintf("\r\n");

        GetEncryptedTrack2(Track2, KeyOutBuf);
        Rprintf("TRACK2: %s\r\n", KeyOutBuf);
    }


    return 0;

    /*
    memset(szHostAddr, 0x00, sizeof(szHostAddr));
    memset(szMethodName, 0x00, sizeof(szMethodName));
    GetHostAndMethod(API_GET_APPLIST, szHostAddr, szMethodName);
    Rprintf("szHostAddr = %s\r\n", szHostAddr);
    Rprintf("szMethodName = %s\r\n", szMethodName);
    memset(szHostAddr, 0x00, sizeof(szHostAddr));
    memset(szMethodName, 0x00, sizeof(szMethodName));
    GetHostAndMethod(API_GET_FUNCLIST, szHostAddr, szMethodName);
    Rprintf("szHostAddr = %s\r\n", szHostAddr);
    Rprintf("szMethodName = %s\r\n", szMethodName);

    memset(szHostAddr, 0x00, sizeof(szHostAddr)); memset(szMethodName, 0x00, sizeof(szMethodName));
    GetHostAndMethod(API_BANK_BINTABLE, szHostAddr, szMethodName);
    Rprintf("szHostAddr = %s\r\n", szHostAddr); Rprintf("szMethodName = %s\r\n", szMethodName);
    memset(szHostAddr, 0x00, sizeof(szHostAddr)); memset(szMethodName, 0x00, sizeof(szMethodName));
    GetHostAndMethod(API_BANK_BIOTEMPLATE, szHostAddr, szMethodName);
    Rprintf("szHostAddr = %s\r\n", szHostAddr); Rprintf("szMethodName = %s\r\n", szMethodName);
    memset(szHostAddr, 0x00, sizeof(szHostAddr)); memset(szMethodName, 0x00, sizeof(szMethodName));
    GetHostAndMethod(API_BANK_BIOTRAN, szHostAddr, szMethodName);
    Rprintf("szHostAddr = %s\r\n", szHostAddr); Rprintf("szMethodName = %s\r\n", szMethodName);
    memset(szHostAddr, 0x00, sizeof(szHostAddr)); memset(szMethodName, 0x00, sizeof(szMethodName));
    GetHostAndMethod(API_BANK_DISTORDER, szHostAddr, szMethodName);
    Rprintf("szHostAddr = %s\r\n", szHostAddr); Rprintf("szMethodName = %s\r\n", szMethodName);
    memset(szHostAddr, 0x00, sizeof(szHostAddr)); memset(szMethodName, 0x00, sizeof(szMethodName));
    GetHostAndMethod(API_BANK_DISTRETURN, szHostAddr, szMethodName);
    Rprintf("szHostAddr = %s\r\n", szHostAddr); Rprintf("szMethodName = %s\r\n", szMethodName);
     */

    strcpy((char *) RespAppList, "<hotcards />");

    reqType = API_GET_APPLIST;
    NIBSS_Parsing((char *) RespAppList, strlen(RespAppList), reqType, &gbTmpRespBuf);
    return 0;

    reqType = API_GET_FUNCLIST;
    iAppId = 3;
    giApplIdx = GetApplIdx(iAppId);

    NIBSS_Parsing((char *) RespFuncList, strlen(RespFuncList), reqType, &gbTmpRespBuf);
    /*
    {
            int i, j;
            char *ptr;
	
            for(i = 0; i < MAX_APPLIST_CNT; i++) {
                    ptr = (char *)FLASH8MB_NIBSS_APPFUNCLIST + sizeof(APPLIST) * i;
                    for(j = 0; j < sizeof(APPLIST); j++) {
                            if((j % 16) == 0) {
                                    Rprintf("\r\n%08X: ", ptr);
                            }
                            Rprintf("%02X ", *ptr++ & 0xFF);
                    }
            }
    }
     */
    /*
            reqType = API_TAMS_NEWKEY;
            NIBSS_Parsing((char *)RespNewKey, strlen(RespNewKey), reqType, &gbTmpRespBuf);

            reqType = API_TAMS_GETKEYS;
            NIBSS_Parsing((char *)RespGetKey, strlen(RespGetKey), reqType, &gbTmpRespBuf);
	
            reqType = API_BANK_EFTPARAMS;
            NIBSS_Parsing((char *)RespEftParams, strlen(RespEftParams), reqType, &gbTmpRespBuf);
	
            reqType = API_BANK_BINTABLE;
            NIBSS_Parsing((char *)RespBinTable, strlen(RespBinTable), reqType, &gbTmpRespBuf);

            reqType = API_BANK_HOTCARDS;
            NIBSS_Parsing((char *)RespHotCard, strlen(RespHotCard), reqType, &gbTmpRespBuf);
	
            reqType = API_BANK_EMVAPP;
            NIBSS_Parsing((char *)RespEmvApp, strlen(RespEmvApp), reqType, &gbTmpRespBuf);
	
            reqType = API_BANK_EMVCAPK;
            NIBSS_Parsing((char *)RespEmvCapk, strlen(RespEmvCapk), reqType, &gbTmpRespBuf);

            reqType = API_TAMS_PARAM;
            NIBSS_Parsing((char *)RespGetParams, strlen(RespGetParams), reqType, &gbTmpRespBuf);
     */
    return 0;
}

#endif
