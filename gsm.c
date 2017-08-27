
/*======================================================================*/
/*																		*/
/*								GSM.C									*/
/*																		*/
/*======================================================================*/

#include "system.h"
#include "extern.h"

#define MAX_RETRY_WIPCREATE 10
U16 usWipCmdRetryCnt;

extern int BuildHtmlRequestMessage(int iApiReq, char *pParams, char *pContents);
extern void NIBSS_Parsing(char *xmlBuf, int len, int iApiReq, void *lpDataBuffer);
extern U16 giApplIdx; // for offline testing
extern int BuildQueryString();

int GPRS_bearer_Retry;

int giRequestType;
int giTransactionType;
int *pusReqSequence;
int giRespContentLength;

U08 ucHtmlHeader[2048];
char gbTmpRespBuf[8192];

const int tbl_ReqSequence[][15] = {
    // #define TRXN_NULL						0
    { -1,},
    // #define TRXN_DOWNLOAD_ALL_PARAMETER		1
    { API_GET_APPLIST, API_GET_FUNCLIST, API_TAMS_NEWKEY, API_TAMS_GETKEYS, API_TAMS_PARAM, API_BANK_EFTPARAMS, API_BANK_BINTABLE, API_BANK_EMVAPP, API_BANK_EMVCAPK, API_BANK_EMVREVOKECAPK, API_BANK_HOTCARDS, -1,},
    // #define TRXN_DOWNLOAD_APPLIST			2
    { API_GET_APPLIST, -1,},
    // #define TRXN_DOWNLOAD_FUNCLIST			3
    { API_GET_FUNCLIST, -1,},
    // #define TRXN_DOWNLOAD_MASTERKEY			4
    { API_TAMS_NEWKEY, -1,},
    // #define TRXN_DOWNLOAD_SESSIONKEY			5
    { API_TAMS_GETKEYS, -1,},
    // #define TRXN_DOWNLOAD_PARAM				6
    { API_TAMS_PARAM, -1,},
    // #define TRXN_DOWNLOAD_EFTPARAMS			7
    { API_BANK_EFTPARAMS, -1,},
    // #define TRXN_DOWNLOAD_BINTABLE			8
    { API_BANK_BINTABLE, -1,},
    // #define TRXN_DOWNLOAD_EMVAPP				9
    { API_BANK_EMVAPP, -1,},
    // #define TRXN_DOWNLOAD_EMVCAPK			10
    { API_BANK_EMVCAPK, -1,},
    // #define TRXN_DOWNLOAD_EMVREVOKECAPK		11
    { API_BANK_EMVREVOKECAPK, -1,},
    // #define TRXN_DOWNLOAD_HOTCARDS			12
    { API_BANK_HOTCARDS, -1,},
    // #define TRXN_RESERVED1					13
    { -1,},
    // #define TRXN_RESERVED2					14
    { -1,},
    // #define TRXN_RESERVED3					15
    { -1,},
    // #define TRXN_BANK_EFTTRAN				16
    { API_BANK_EFTTRAN, -1,},
    // #define TRXN_BANK_EFTTOTAL				17
    { API_BANK_EFTTOTALS, -1,},
    // #define TRXN_TAMS_CALLHOME				18
    { API_TAMS_CALLHOME, -1,},
};

int iKeyCnt = 0;



//#undef USER_DEBUG

// Wavecom Q2686

#ifdef USER_DEBUG
#if 0
// +CME ERROR: <err>
//	{ xxx, "1234567890123456789012345678901234567890123456789012345678901234" },
const CMES_T CME_ERROR_CODE[] = {
    //**************************************************************************
    // General error result codes
    //**************************************************************************
    // the GSM recommandation 07.07
    //{   0, "phone failure" },									// Telit GSM Module
    //{   1, "No connection to phone" },							// Telit GSM Module
    //{   2, "phone-adaptor link reserved" },						// Telit GSM Module
    { 3, "Operation not allowed"},
    { 4, "Operation not supported"},
    { 5, "PH-SIM PIN required"},
    { 10, "SIM not inserted"},
    { 11, "SIM PIN required"},
    { 12, "SIM PUK required"},
    { 13, "SIM failure"},
    //{  14, "SIM busy" },										// Telit GSM Module
    //{  15, "SIM wrong" },										// Telit GSM Module
    { 16, "Incorrect password or Bad user PIN"},
    { 17, "SIM PIN2 required"},
    { 18, "SIM PUK2 required"},
    { 20, "Memory full"},
    { 21, "Invalid index"},
    { 22, "Not found"},
    //{  23, "Memory failure" },									// Telit GSM Module
    { 24, "Text string too long"},
    //{  25, "Invalid characters in text string" },				// Telit GSM Module
    { 26, "Dial string too long"},
    { 27, "Invalid characters in dial string"},
    { 30, "No network service"},
    //{  31, "Network timeout" },									// Telit GSM Module
    { 32, "Network not allowed - emergency calls only"},

    // Network personalization PIN required
    { 40, "Network lock"},
    { 42, "Network subset lock"},
    { 44, "Service Provider lock"},
    { 46, "Corporate lock"},

    // GPRS related error reslt codes to failure to perform an Attach
    { 103, "Incorrect MS identity"},
    { 106, "ME is blacklisted by the network"},
    { 107, "ME is not allowed to operate in GPRS"},
    { 111, "ME is not allowed to operate in the requested PLMN"},
    { 112, "MS is not allowed to make location updating in this area"},
    { 113, "Roaming in this location area is not allowed"},

    // GPRS related error reslt codes to failure to Activate a Context and others
    { 132, "service option not supported"},
    { 133, "requested servoce option not subscribed"},
    { 134, "service option temporarily out of order"},
    { 148, "unspecified GPRS error"},
    { 149, "PDP authentication failure"},
    { 150, "invalid mobile class"},

    //**************************************************************************
    // Specific error result codes
    //**************************************************************************
    { 500, "unknown error"},
    { 501, "GPIO cannot be reached by device layer"},
    { 502, "AT command is inconsistent"},
    { 503, "The external interrupt cannot be reached"},
    { 504, "Error during external interrupt treatment"},
    { 505, "The resource has not been reserved"},
    { 512, "MM establishment failure (for SMS)"},
    { 513, "Lower layer failure (for SMS)"},
    { 514, "CP error (for SMS)"},
    { 515, "Please wait, init or command processing in progress"},
    { 517, "SIM Toolkit facility not supported"},
    { 518, "SIM Toolkit indication not received"},
    { 519, "Reset the product to activate"}, // Reset the product to activate or change a new echo cancellation algorithm
    { 520, "Automatic abort about get PLMN list for an incoming call"},
    { 526, "PIN deactivation forbidden with this SIM card"},
    { 527, "Please wait, RR or MM is busy. Retry your selection later"},
    { 528, "Location update failure. Emergency calls only"},
    { 529, "PLMN selection failure. Emergency calls only"},
    { 531, "SMS not sent"},
    { 532, "the flash objects are not erased"}, // The embedded application is activated so the flash objects are not erased
    { 533, "Missing or Unknown APN"},
    { 536, "Class locked"},
    { 537, "Phonebook group full"},
    { 538, "Not Enough Space to copy SMS"},
    { 539, "Invalid SMS"},
    { 541, "Open AT application and AT software version do not match"},
    { 543, "CMUX connection is refused by remote"},
    { 544, "CMUX connection Timeout (no answer from the remote)"},
    { 545, "A CMUX session has been started on a physical UART"},
    { 546, "Emergency call is not allowed without SIM"},
    { 547, "Emergency call is allowed without SIM"},
    { 548, "No flash objects to delete"},
    { 549, "The phone number of the requested phonebook entry is empty"},
    { 550, "Unable to resize the Application & Data storage place"},
    { 551, "Service abort request has failed"},
    { 552, "autodiag or charge indications are already activated"},
    { 553, "The PUK 1 code is burned but PIN 1/CHV 1 code is OK"},
    { 554, "The SIM is blocked (PIN 1/CHV 1 and PUK 1 codes are burned)"},
    { 555, "AT command aborted by a POWER OFF"},
    { 556, "AT command aborted by a SIM Extract"},
    { 558, "The service is already activated by another port"},
    { 559, "Audio Diagnostic was stopped because an incoming call happens"},
    { 560, "Auto Shutdown is already enabled or disabled"},
    { 562, "AT command aborted by an auto answer to an incoming call"},
    { 563, "The charge is not started due to an error"},
    { 650, "General error, Device Services not in good state"},
    { 651, "Communication error"},
    { 652, "Session in progress"},

    //**************************************************************************
    // Error result codes for creating TCP client and server sockets
    //**************************************************************************
    { 800, "invalid option"},
    { 801, "invalid option value"},
    { 802, "not enough memory"},
    { 803, "operation not allowed in the current WIP stack state"}, // already open or operation not allowed in the current WIP stack state
    { 804, "device already open"},
    { 805, "network interface not available"},
    { 806, "operation not allowed on the considered bearer"},

    // bearer connection failure
    { 807, "line busy"},
    { 808, "no answer"},
    { 809, "no carrier"},
    { 810, "no SIM card present"},
    { 811, "SIM not ready"},
    { 812, "GPRS network failure"},
    { 813, "PPP LCP negotiation failed"},
    { 814, "PPP authentication failed"},
    { 815, "PPP IPCP negotiation failed"},
    { 816, "PPP peer terminates session"},
    { 817, "PPP peer does not answer to echo request"},

    { 818, "incoming call refused"},
    { 819, "error on ping channel"},
    { 820, "error writing configuration in FLASH memory"},
    { 821, "error reading configuration in FLASH memory"},

    //822-829, "reserved for future use


    { 830, "bad index"},
    { 831, "bad state"},
    { 832, "bad port number"},
    { 833, "bad port state"},
    { 834, "not implemented"},
    { 835, "option not supported"},
    { 836, "memory allocation error"},
    { 837, "bad protocol"},
    { 838, "no more free socket"},
    { 839, "error during channel creation"},
    { 840, "UDP/TCP socket or FTP/HTTP/SMTP/POP3 session is already active"},
    { 841, "peer closed"},
    { 842, "destination host unreachable"}, // whether host unreachable, Network unreachable, response timeout
    { 843, "connection reset by peer"},
    { 844, "stack already started"},
    { 845, "socket is already reserved/opened by TCP server/client"}, // attempt is made to reserve/create a client socket which is already reserved/opened by TCP server/client
    { 846, "internal error: FCM subscription failure"},

    //847-849, "reserved for future use
    // Wavecom IP v3[1].21
    { 847, "bearer connection failure: WIP_BOPT_GPRS_TIMEOUT time limit expired before GPRS bearer connected"},
    { 848, "impossible to connect to the bearer"},
    { 849, "connection to the bearer has succeeded but a problem has occurred during the data flow establishment"},

    { 850, "initialization failed or unknown reason"},

    //851-859, "reserved for future use

    { 860, "protocol undefined or internal error"},
    { 861, "user name rejected by server"},
    { 862, "password rejected by server"},
    { 863, "protocol delete error"},
    { 864, "protocol list error"},
    { 865, "authentication error"},
    { 866, "server not ready error"},
    { 867, "POP3 email retrieving error"},
    { 868, "POP3 email size error"},

    //869-879, "reserved for future use

    { 880, "SMTP sender email address rejected by server"},
    { 881, "SMTP recipient email address rejected by server"},
    { 882, "SMTP CC recipient email address rejected by server"},
    { 883, "SMTP BCC recipient email address rejected by server"},
    { 884, "SMTP email body send request rejected by server"},

    { -1, "Undefined error"},
};

// +CMS ERROR: <err>
const CMES_T CMS_ERROR_CODE[] = {
    //**************************************************************************
    // Message Service Failure Result Codes
    //**************************************************************************
    // 1 to 127: the GSM recommandation 04.11
    { 1, "Unassigned (unallocated) number"},
    { 8, "Operator determined barring"},
    { 10, "Call barred"},
    { 21, "Short message transfer rejected"},
    { 27, "Destination out of service"},
    { 28, "Unidentified subscriber"},
    { 29, "Facility rejected"},
    { 30, "Unknown subscriber"},
    { 38, "Network out of order"},
    { 41, "Temporary failure"},
    { 42, "Congestion"},
    { 47, "Resources unavailable, unspecified"},
    { 50, "Requested facility not subscribed"},
    { 69, "Requested facility not implemented"},
    { 81, "Invalid short message transfer reference value"},
    { 95, "Invalid message, unspecified"},
    { 96, "Invalid mandatory information"},
    { 97, "Message type non-existent or not implemented"},
    { 98, "Message not compatible with short message protocol state"},
    { 99, "Information element non-existent or not implemented"},
    { 111, "Protocol error, unspecified"},
    { 127, "Inter-working, unspecified"},
    { 301, "SMS service of ME reserved"},
    { 302, "Operation not allowed"},
    { 303, "Operation not supported"},
    { 304, "Invalid PDU mode parameter"},
    { 305, "Invalid text mode parameter"},
    { 310, "SIM not inserted"},
    { 311, "SIM PIN required"},
    { 312, "PH-SIM PIN required"},
    { 313, "SIM failure"},
    { 316, "SIM PUK required"},
    { 317, "SIM PIN2 required"},
    { 318, "SIM PUK2 required"},
    { 321, "Invalid memory index"},
    { 322, "SIM or ME memory full"},
    { 330, "SC address unknown"},
    { 340, "no +CNMA acknowledgement expected"},

    { -1, "Undefined error"},
};
#endif
#endif

const char GPRS_WAVECOM_DISCONNECT_TBL[19] = {
    '\r', '\n', '+', 'C', 'M', 'E', ' ', 'E', 'R', 'R', 'O', 'R', ':', ' ', '8', '4', '3', '\r', '\n'
};

const char GPRS_CINTERION_DISCONNECT_TBL[12] = {
    'N', 'O', ' ', 'C', 'A', 'R', 'R', 'I', 'E', 'R', '\r', '\n'
};

// GSM
unsigned short usGprsTaskStep; // GPRS task step
unsigned short usGprs10MSMaxTimeout; // GPRS 10ms maximum timeout
unsigned short usGprs10MSTimer; // GPRS 10ms timer
unsigned char ucGprsModuleOkFlag; // GPRS module OK flag (0: GSM module doesn't response, 1: GSM module is OK)
unsigned char ucGprsGsmModel; // GPRS/GSM model
unsigned char ucGprsCmdRetryCnt; // GPRS command retry counter
unsigned char ucGprsMaxConnectCnt; // GSM maximum connection counter
unsigned char ucGprsConnectCnt; // GSM connection counter
unsigned char ucGprsPowerOffFlag; // GPRS power off flag
unsigned char ucGprsPowerOnStatus; // GPRS power on status
unsigned char ucGprsBearerOpenedFlag; // GPRS bearer opened flag
unsigned char ucGprsSIMCheckedFlag; // GPRS SIM checked flag
unsigned char ucGprsSIMStatus; // GPRS SIM status
unsigned char ucGsmNetworkRegistrationMode; // GSM network registration mode
unsigned char ucGprsRssiValue; // GPRS RSSI value
unsigned char ucGprsBerValue; // GPRS BER value
unsigned char ucGprsDLESetFlag; // GPRS DLE set flag
unsigned char ucGprsCheckDisconnectCnt; // GPRS check disconnect count
unsigned char ucGprsRssiRetryCnt; // GPRS Check Signal Quality retry counter
unsigned char ucGprsRegistrationStatus; // GPRS registration status
unsigned char ucGprsRegistrationRetryCnt; // GPRS Check the registration status retry counter

unsigned char ucGprsNetworkConnectionStatus; // GPRS Network Connection Status for Cinterion Module
unsigned char sz18GsmOperator[18]; // Operator Identifier/Name [0]:Format '0'=long alpha '1'=short alpha '2'=numeric
unsigned char ucRxTempBuf[8192]; // Rx temporary data buffer
unsigned char ucTxTempBuf[8192]; // Tx temporary data buffer

//#ifdef USER_DEBUG
long lGprsTest1SecStartTimer;
long lGprsTest1SecCheckTimer;
//#endif


void GprsOpen(void);
void GprsPowerOn(unsigned char sim_slot_no);
void GprsPowerOff(void);
void GprsCmdModeWrite(char *stream, int size);
void GprsSendCmdSetTime(unsigned short time_out);
void GprsDisplaySIMErrorMessage(void);
void GprsDisplayAntennaLevelBar(unsigned char rssi);
void GprsTask(void);
void GprsWavecomDisconnect(int iMode);
void GprsCinterionDisconnect(int iMode);
void GprsModuleInitialize(void);
void GprsWavecomTask(void);
void GprsCinterionTask(void);



/*************************************************************************
        GSM Modem
 *************************************************************************/

/* Open GSM */
void GprsOpen(void) {
#ifdef USER_DEBUG
    Rprintf("\r\n%d - GPRS Open\r\n", usGprsTaskStep);
#endif
    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
        // "     <GSM>      ", "                ", "                ", "                "
        LCDDisplay4Lines(M4GSMMsg_00000000001, -1, ucLangFlag);
        if (usGprsTaskStep < 200) {
            if (ucGprsConnectCnt == 0) {
                // "  DIALING NOW   ",
                //LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *)LCD_MSG_TBL1[ucLangFlag][M1DialingNow_0000001], ucLangFlag);
                // " CONNECTING NOW ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ConnectingNow_0001], ucLangFlag);
            } else {
                // " REDIALING NOW  ",
                //LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *)LCD_MSG_TBL1[ucLangFlag][M1RedialingNow_00001], ucLangFlag);
                // "RECONNECTING NOW",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReconnectingNow_01], ucLangFlag);
            }
        } else {
            // " LINE CONNECTED ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1LineConnected_0001], ucLangFlag);
        }
    }
}

/*
GPRS Power On
        Input
                sim_slot_no
                        0 or 1
 */
void GprsPowerOn(unsigned char sim_slot_no) {
#ifdef USER_DEBUG
    Rprintf("\r\nGPRS Power On\r\n");
#endif
    SIM_SELECT(sim_slot_no);
    ucGprsPowerOnStatus = 1;
    ucGprsBearerOpenedFlag = 0;
    CONTROL_POWER_SAVING_STATUS(P_EXT_SERIAL, ON);
    CONTROL_POWER_SAVING_STATUS(P_RF_MODULE, ON);
    CONTROL_POWER_SAVING_STATUS(P_SMART_CARD, ON);
    TIMER_Wait1MS(100);
}

/* GPRS Power Off */
void GprsPowerOff(void) {
#ifdef USER_DEBUG
    Rprintf("\r\nGPRS Power Off\r\n");
#endif
    ucGprsPowerOffFlag = 0;
    ucGprsPowerOnStatus = 0;
    usGprsTaskStep = 0;
    CONTROL_POWER_SAVING_STATUS(P_EXT_SERIAL, OFF);
    CONTROL_POWER_SAVING_STATUS(P_RF_MODULE, OFF);
    CONTROL_POWER_SAVING_STATUS(P_SMART_CARD, OFF);
    TIMER_Wait1MS(100);
}

/*
Transmit data to RS232 port for GSM
        Input
                stream
                        pointer of stream
                size
                        the length of stream
 */
void GprsCmdModeWrite(char *stream, int size) {
    RS232_Write(GPRS_COM_PORT, stream, size);
    iRxCnt = 0;
}

/*
Transmit data in command mode to RS232 port for GSM and set response timeout
        Input
                time_out
                        response timeout
 */
void GprsSendCmdSetTime(unsigned short time_out) {
#ifdef USER_DEBUG
    if (usGprsTaskStep != 62 && usGprsTaskStep != 66)
        Rprintf("%s\r\n", ucTxBuf);
#endif
    GprsCmdModeWrite((char *) &ucTxBuf[0], strlen((char *) ucTxBuf));
    usGprsTaskStep++;
    usGprs10MSTimer = TIMER_Get10MSTimer();
    usGprs10MSMaxTimeout = time_out;
}

/*
Transmit data in data mode to RS232 port for GPRS
        Input
                stream
                        pointer of stream
                size
                        the length of stream
	
        Return Value
                the length of transmitted data to RS232 port
 */
int GprsDataModeWrite(char *stream, int size) {
    int i, j;
    unsigned char ch;

    if (sz17HWInfo[7] == 0x33) {
        for (i = 0, j = 0; i < size; i++) {
            ch = stream[i] & 0xFF;
            if (ucGprsGsmModel == WAVECOM_Q2686) {
                if (ch == ETX || ch == DLE) {
                    ucTxTempBuf[j++] = DLE;
                }
            } else {
                if (ch == ETX) {
                    ucTxTempBuf[j++] = DLE;
                }
            }
            ucTxTempBuf[j++] = ch;
        }
    } else {
        for (i = 0, j = 0; i < size; i++) {
            ch = stream[i] & 0xFF;
            //if (ch == EOT || ch == DLE) {
            //if (ch == DLE) {
            //	ucTxTempBuf[j++] = DLE;
            //}
            ucTxTempBuf[j++] = ch;
        }
    }

#ifdef USER_DEBUG
    //DBGprt(("GprsDataModeWriteg"));
    //DEBUG_BUF(((BYTE *)&ucTxTempBuf[0], j));
#endif

    RS232_Write(GPRS_COM_PORT, ucTxTempBuf, j);
    iRxCnt = 0;

    return (j);
}

int SendRequestMessage(int iApiReq, char *pParams, char *pContents) {
    int iResult = 0;

    if ((iResult = BuildHtmlRequestMessage(iApiReq, pParams, pContents)) < 0) {
        return iResult;
    }

    memset((char *) &st_ErrRespData, 0x00, sizeof (_st_ErrRespData_));

#ifndef TEST_OFFLINE
    GprsDataModeWrite((char *) ucTxBuf, strlen(ucTxBuf));
#endif
#ifdef USER_DEBUG
    Rprintf(ucTxBuf);
#endif

    return iResult;
}

void GprsDisplaySIMErrorMessage(void) {
    switch (ucGprsSIMStatus) {
        case SIM_FAILURE: // SIM not inserted or failure
            // "????????????????", "SIM not inserted", "or failure      ", "                "
            LCDDisplay4Lines(M4SIMfailure_0000001, -1, ucLangFlag);
            break;
        case SIM_BLOCK: // SIM is blocked
            // "????????????????", "SIM is blocked  ", "                ", "                "
            LCDDisplay4Lines(M4SIMisBlocked_00001, -1, ucLangFlag);
            break;
        case SIM_PIN: // CHV1 is required
            // "????????????????", "CHV1 is required", "                ", "                "
            LCDDisplay4Lines(M4CHV1isRequired_001, -1, ucLangFlag);
            break;
        case SIM_PUK: // PUK1 is required
            // "????????????????", "PUK1 is required", "                ", "                "
            LCDDisplay4Lines(M4PUK1isRequired_001, -1, ucLangFlag);
            break;
        case SIM_PIN2: // CHV2 is required
            // "????????????????", "CHV2 is required", "                ", "                "
            LCDDisplay4Lines(M4CHV2isRequired_001, -1, ucLangFlag);
            break;
        case SIM_PUK2: // PUK2 is required
            // "????????????????", "PUK2 is required", "                ", "                "
            LCDDisplay4Lines(M4PUK2isRequired_001, -1, ucLangFlag);
            break;
        case PH_SIM_PIN: // SIM lock (phone-to-SIM) is required
            // "????????????????", "SIM lock        ", "(phone-to-SIM)  ", "is required     "
            LCDDisplay4Lines(M4SIMlockIsRequire_1, -1, ucLangFlag);
            break;
        case PH_NET_PIN: // Network personalization PIN required
        case PH_NET_PUK: // Network personalization PUK required
            // "????????????????", "network         ", "personalization ", "is required     "
            LCDDisplay4Lines(M4NetworkPerRequire1, -1, ucLangFlag);
            break;
        case PH_NET_SUB_PIN: // Network subset personalization PIN required
        case PH_NET_SUB_PUK: // Network subset personalization PUK required
            // "????????????????", "network subset  ", "is required     ", "                "
            LCDDisplay4Lines(M4NetworkSubRequire1, -1, ucLangFlag);
            break;
        case PH_SVC_PROVIDER_PIN: // Service provider personalization PIN required
        case PH_SVC_PROVIDER_PUK: // Service provider personalization PUK required
            // "????????????????", "service provider", "is required     ", "                "
            LCDDisplay4Lines(M4SVCroviderRequire1, -1, ucLangFlag);
            break;
        case PH_CORPORATE_PIN: // Corporate personalization PIN required
        case PH_CORPORATE_PUK: // Corporate personalization PUK required
            // "????????????????", "corporate       ", "is required     ", "                "
            LCDDisplay4Lines(M4CorporateRequired1, -1, ucLangFlag);
            break;
        case PH_SIM_PUK: // PH-SIM PUK (master phone code) required
            // "????????????????", "PH-SIM PUK      ", "(master phone   ", "code) required  "
            LCDDisplay4Lines(M4PHSIMPUKRequired1, -1, ucLangFlag);
            break;
    }
}

/*
Display antenna level bar for GSM
        Input
                rssi
                        the received signal strength indication
 */
void GprsDisplayAntennaLevelBar(unsigned char rssi) {
    int i;

    if (rssi == 99) { // No signal
        i = 0; // Antena all off
    } else if (rssi <= GPRS_ANTENNA_LEVEL_1_LIMIT) { // <= -105dBm
        i = 1; // Antena on
    } else if (rssi <= GPRS_ANTENNA_LEVEL_2_LIMIT) { // <= -93dBm
        i = 2; // Antena and Antena level bar 1 on
    } else if (rssi <= GPRS_ANTENNA_LEVEL_3_LIMIT) { // <= -85dBm
        i = 3; // Antena and Antena level bar 1,2 on
    } else if (rssi <= GPRS_ANTENNA_LEVEL_4_LIMIT) { // <= -75dBm
        i = 4; // Antena and Antena level bar 1,2,3 on
    } else { // >= -73dBm
        i = 5; // Antena and Antena level bar all(1,2,3,4) on
    }

    ICON_DISPLAY(i);
    DisplayAntennaIcon((char *) ANTENNA_ICON_BMP[i]);
}

/*
Check GPRS disconnection
        Return value
                0: GPRS is not disconnected
                1: GPRS is disconnected
 */
int GprsCheckDisconnect(int rxdata) {
    if (sz17HWInfo[7] == 0x33) {
        if (rxdata == GPRS_WAVECOM_DISCONNECT_TBL[ucGprsCheckDisconnectCnt]) {
            ucGprsCheckDisconnectCnt++;
            if (ucGprsCheckDisconnectCnt >= 19) {
                ucGprsCheckDisconnectCnt = 0;
                return 1;
            }
        } else if (rxdata == GPRS_WAVECOM_DISCONNECT_TBL[0]) {
            ucGprsCheckDisconnectCnt = 1;
        } else {
            ucGprsCheckDisconnectCnt = 0;
        }
    } else {
        if (rxdata == GPRS_CINTERION_DISCONNECT_TBL[ucGprsCheckDisconnectCnt]) {
            ucGprsCheckDisconnectCnt++;
            if (ucGprsCheckDisconnectCnt >= 12) {
                ucGprsCheckDisconnectCnt = 0;
                return 1;
            }
        } else if (rxdata == GPRS_CINTERION_DISCONNECT_TBL[0]) {
            ucGprsCheckDisconnectCnt = 1;
        } else {
            ucGprsCheckDisconnectCnt = 0;
        }
    }

    return 0;
}

/* GPRS task */
void GprsTask(void) {
    if (sz17HWInfo[7] == 0x33) {
        GprsWavecomTask();
    } else if (sz17HWInfo[7] == 0x37) {
        GprsCinterionTask();
    }
}

/* GPRS Wavecom task */
void GprsWavecomTask(void) {
    int i, j, k, rxdata, error_code, ret, max_line;
    unsigned char crc;
    char temp[3][256];
#ifdef USER_DEBUG
    static U16 usPrevGprsTaskStep = -1;
#endif

    if (stpFlashPOSSetupInfo->ucComDevice != GSM_MODEM) {
        return;
    }

    if (ucTMSDownloadFlag && usGprsTaskStep >= 200) {
        return;
    }

#ifdef USER_DEBUG
    if (usGprsTaskStep != usPrevGprsTaskStep) {
        if (usGprsTaskStep < 60 || usGprsTaskStep >= 70) {
            //Rprintf("\r\nusGprsTaskStep = %d\r\n", usGprsTaskStep);
        }
        usPrevGprsTaskStep = usGprsTaskStep;
    }
#endif

    // AT Command Mode
    if (usGprsTaskStep < 200) {
        switch (usGprsTaskStep) {
            case 0: // Initial status
#ifdef USER_DEBUG
                //				Rprintf("\r\nInitial Status\r\n");
#endif
                if (ucGprsModuleOkFlag) {
                    if (ucGprsSIMStatus == SIM_CHECK || ucGprsSIMStatus == SIM_READY) {
#ifdef USER_DEBUG
                        //						Rprintf("Open GSM RS232 Port\r\n");
#endif
                        RS232_OpenPort(GPRS_COM_PORT, BPS115200, NONE8BIT, STOP1BIT, 0);

                        memset((char *) &ucTxBuf[0], 0x00, sizeof (ucTxBuf));
                        memset((char *) &ucRxBuf[0], 0x00, sizeof (ucRxBuf));
                        iRxCnt = 0;

                        ucGprsCmdRetryCnt = 0;
                        usGprsTaskStep = 1; // Delay for sending First Echo off command (within 4 seconds after reset)
                    }
                }
                return;
            case 3: // First Echo off command (within 4 seconds after reset)
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Echo off\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "ATE0\r");
                GprsSendCmdSetTime(50);
                break;
            case 5:
                ucGprsCmdRetryCnt = 0;
                if (ucGprsSIMCheckedFlag == 0) {
                    usGprsTaskStep = 10; // Delay for sending Read the SIM status command (within 6 seconds after reset)
                } else {
                    usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                }
                return;

            case 12: // Read the SIM status command (within 6 seconds after reset)
                // Command
                // AT+CPIN?
                //
                // Response
                // +CPIN: <rssi>,<ber>
                //
                // OK
                //
                // +CPIN: READY				- ME is not pending for any password
                // +CPIN: SIM PIN			- CHV1 is required
                // +CPIN: SIM PUK			- PUK1 is required
                // +CPIN: SIM PIN2			- CHV2 is required
                // +CPIN: SIM PUK2			- PUK2 is required
                // +CPIN: PH-SIM PIN		- SIM lock (phone-to-SIM) is required
                // +CPIN: PH-NET PIN		- network personalization is required
                // +CPIN: PH-NETSUB PIN		- network subset is required
                // +CPIN: PH-SERVPROV PIN	- service provider is required
                // +CPIN: PH-CORPORATE PIN	- corporate is required
                //
                // +CME ERROR: <err>	- SIM failure (13) absent (10) etc��
                // +CME ERROR: 10 (SIM not inserted)
                // +CME ERROR: 13 (SIM failure)
                // +CME ERROR: 515 (Please wait, init or command processing in progress)
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Read the SIM status\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CPIN?\r");
                GprsSendCmdSetTime(300);
                break;
            case 16: // Enter PIN command
                // +CME ERROR: 3 (Operation not allowed, PIN previously entered)
                // Enter PUK and new PIN command
                // ex) AT+CPIN=00000000,1234
                // +CME ERROR: 16 (Incorrect PUK)
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Enter PIN\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CPIN=5273\r");
                GprsSendCmdSetTime(600);
                break;
            case 20: // Read selected an operator command
                // Command
                // AT+COPS?
                //
                // Response
                // +COPS: <mode>[,<format>,<oper>]
                //
                // OK
                //
                // <mode>: network registration mode
                // 0: automatic (default value)
                // 1: manual
                // 2: deregistration; ME will be unregistered until <mode>=0 or 1
                //    is selected
                // 3: set only <format> (for read command AT+COPS?)
                // 4: manual/automatic (<oper> shall be present), if manual
                //    selection fails, automatic mode is entered.
                //
                // <format>: format of <oper> field
                // 0: long alphanumeric format <oper>
                // 1: short alphanumeric format <oper>
                // 2: numeric <oper> (default value)
                //
                // <stat>: status of <oper> field
                // 0: unknown
                // 1: available
                // 2: current
                // 3: forbidden
                //
                // <oper>: operator identifier (MCC/MNC in numeric format only for
                //         operator selection)
                // The long alphanumeric format can be up to 16 characters long
                // (for operator names description see "Operator names" section
                // in the present document "Appendixes"; field is "Name").
                // The short alphanumeric format can be up to 10 characters long.
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Read selected an operator command\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+COPS?\r");
                GprsSendCmdSetTime(300);
                break;
            case 24: // Set network registration mode command
                // Command
                // AT+COPS=<mode>[,<format>[,<oper>]]
                //
                // Response
                // OK
                //
                // <mode>: network registration mode
                // 0: automatic (default value)
                // 1: manual
                // 2: deregistration; ME will be unregistered until <mode>=0 or 1
                //    is selected
                // 3: set only <format> (for read command AT+COPS?)
                // 4: manual/automatic (<oper> shall be present), if manual
                //    selection fails, automatic mode is entered.
                //
                // <format>: format of <oper> field
                // 0: long alphanumeric format <oper>
                // 1: short alphanumeric format <oper>
                // 2: numeric <oper> (default value)
                //
                // <stat>: status of <oper> field
                // 0: unknown
                // 1: available
                // 2: current
                // 3: forbidden
                //
                // <oper>: operator identifier (MCC/MNC in numeric format only for
                //         operator selection)
                // The long alphanumeric format can be up to 16 characters long
                // (for operator names description see "Operator names" section
                // in the present document "Appendixes"; field is "Name").
                // The short alphanumeric format can be up to 10 characters long.
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set network registration mode command\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+COPS=0\r");
                GprsSendCmdSetTime(300);
                break;

            case 62: // Check Signal Quality command
                // Command
                // AT+CSQ
                //
                // Response
                // +CSQ: <rssi>,<ber>
                //
                // OK
                //
                // * the received signal strength indication (<rssi>) and the channel bit error rate (<ber>)
                //
                // <rssi>:
                // 0		-113dBm or less
                // 1		-111dBm
                // 2 to 30	-109 to -53dBm / 2dBm per step
                // 		 2: -109dBm,  3: -107dBm,  4: -105dBm,  5: -103dBm,  6: -101dBm,
                // 		 7:  -99dBm,  8:  -97dBm,  9:  -95dBm, 10:  -93dBm, 11:  -91dBm,
                // 		12:  -89dBm, 13:  -87dBm, 14:  -85dBm, 15:  -83dBm, 16:  -81dBm,
                // 		17:  -79dBm, 18:  -77dBm, 19:  -75dBm, 20:  -73dBm, 21:  -71dBm, 
                // 		22:  -69dBm, 23:  -67dBm, 24:  -65dBm, 25:  -63dBm, 26:  -61dBm,
                // 		27:  -59dBm, 28:  -57dBm, 29:  -55dBm, 30:  -53dBm
                // 31		-51dBm or greater
                // 99		not known or not detectable
                //
                // <ber>:
                // 0��7		as RXQUAL values in the table GSM 05.08
                //  0		less than 0.2%
                //  1		0.2% to 0.4%
                //  2		0.4% to 0.8%
                //  3		0.8% to 1.6%
                //  4		1.6% to 3.2%
                //  5		3.2% to 6.4%
                //  6		6.4% to 12.8%
                //  7		more than 12.8%
                // 99		not known or not detectable
#ifdef USER_DEBUG
                //				Rprintf("\r\n%d - Check Signal Quality\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CSQ\r");
                GprsSendCmdSetTime(300);
                break;
            case 66: // Check the registration status command
                // Command
                // AT+CREG?
                //
                // Response
                // +CREG: <mode>,<status>[,<lac>,<cid>]
                //
                // OK
                //
                // <mode>: request operation
                // 0: disable network registration unsolicited result code (default value)
                // 1: enable network registration code result code +CREG: <stat>
                // 2: enable network registration and location information unsolicited result code
                //    +CREG: <stat>,<lac>,<ci> if there is a change of network cell
                //
                // <stat>: network registration state
                // 0: not registered, ME is not currently searching for a new operator
                // 1: registered, home network
                // 2: not registered, ME currently searching for a new operator
                // 3: registration denied
                // 4: unknown
                // 5: registered, roaming
                //
                // <lac>: location area code
                // string type; two byte location area code in hexadecimal format
                // (e.g. "00C3" equals 195 in decimal)
                //
                // <ci>: cell ID
                // string type ; two byte cell ID in hexadecimal format
                //
                // <rejectCause>: network registration denied cause
                // 0: Illegal MS
                // 1: Illegal ME
                // 2: IMSI Unknown
                // 3: Bad network authentication
#ifdef USER_DEBUG
                //				Rprintf("\r\n%d - Check the registration status command\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CREG?\r");
                GprsSendCmdSetTime(300);
                break;

            case 72: // Start the Open AT�� embedded application command
                // +CME ERROR: 541 (since main versions do not match, the Open AT�� application can not be started)
                strcpy(ucTxBuf, "AT+WOPEN=1\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Start the Open AT�� embedded application\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(600);
                break;
            case 76: // Start TCP/IP stack command
                // +CME ERROR: 844 (stack already started)
                strcpy(ucTxBuf, "AT+WIPCFG=1\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Start TCP/IP stack\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 80: // Open General Packet Radio Service(GPRS) bearer command
                // +CME ERROR: 804 (device already open)
                strcpy(ucTxBuf, "AT+WIPBR=1,6\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Open General Packet Radio Service(GPRS) bearer\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 84: // Set Access Point Name(APN) of GPRS bearer command (maximum 96 characters)
                //sprintf(ucTxBuf, "AT+WIPBR=2,6,11,\"%s\"\r", gsSysInfo.sz33GprsAPN[gsSysInfo.ucGprsSIMNo]);
                //sprintf(ucTxBuf, "AT+WIPBR=2,6,11,\"%s\"\r", gsSysInfo.sz33GprsAPN);
                //sprintf(ucTxBuf, "AT+WIPBR=2,6,11,\"mtnirancell\"\r");
                if (strlen(st_POSSetupInfo.sz33GprsAPN[st_POSSetupInfo.ucGprsSIMNo])) {
                    sprintf(ucTxBuf, "AT+WIPBR=2,6,11,\"%s\"\r", st_POSSetupInfo.sz33GprsAPN[st_POSSetupInfo.ucGprsSIMNo]);
                } else {
                    strcpy(ucTxBuf, "AT+WIPBR=2,6,11,\"\"\r");
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set Access Point Name(APN) of GPRS bearer\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 88: // Set User Name command (maximum 64 characters)
                if (strlen(st_POSSetupInfo.sz33GprsUserName[st_POSSetupInfo.ucGprsSIMNo])) {
                    sprintf(ucTxBuf, "AT+WIPBR=2,6,0,\"%s\"\r", st_POSSetupInfo.sz33GprsUserName[st_POSSetupInfo.ucGprsSIMNo]);
                } else {
                    strcpy(ucTxBuf, "AT+WIPBR=2,6,0,\"\"\r");
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set User Name\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 92: // Set password command (maximum 64 characters)
                if (strlen(st_POSSetupInfo.sz33GprsPassword[st_POSSetupInfo.ucGprsSIMNo])) {
                    sprintf(ucTxBuf, "AT+WIPBR=2,6,1,\"%s\"\r", st_POSSetupInfo.sz33GprsPassword[st_POSSetupInfo.ucGprsSIMNo]);
                } else {
                    strcpy(ucTxBuf, "AT+WIPBR=2,6,1,\"\"\r");
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set password\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GPRS_bearer_Retry = 30;
                GprsSendCmdSetTime(300);
                break;
            case 96: // Start GPRS bearer as client command (Check SIM, GPRS network, and bearer connection)
                // +CME ERROR: 803 (already open)
                // +CME ERROR: 812 (GPRS network failure)
                strcpy(ucTxBuf, "AT+WIPBR=4,6,0\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Start GPRS bearer as client\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(6000);
                usWipCmdRetryCnt = 0;
                break;

            case 162: // Create the TCP client socket with index 1 command
                // Note: An unsolicited event +WIPREADY: 2, 1 will be received once the TCP client is ready for usage
                // +CME ERROR: 800 (invalid option)
                // +CME ERROR: 803 (operation not allowed in the current WIP stack state)
                // +CME ERROR: 831 (bad state)
                // +CME ERROR: 842 (destination host unreachable) - Timeout: about 75 seconds
                if (!ucTMSDownloadFlag) {
                    sprintf(ucTxBuf, "AT+WIPCREATE=2,1,\"%s\",%s\r", st_POSSetupInfo.sz16TrxnServerIP[0], st_POSSetupInfo.sz6TrxnServerPortNo[0]);
                } else {
                    sprintf(ucTxBuf, "AT+WIPCREATE=2,1,\"%s\",%s\r", st_POSSetupInfo.sz16TMSServerIP[0], st_POSSetupInfo.sz6TMSServerPortNo[0]);
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Create the TCP client socket\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);

                lGprsTest1SecStartTimer = GetULDateTime();
#endif
                //				GprsSendCmdSetTime(9000);
                GprsSendCmdSetTime(500);
                break;
            case 166: // Read/write from/to a socket command
                // CONNECT
                // +CME ERROR: 831 (bad state)
                // +CME ERROR: 837 (bad protocol)
                // +CME ERROR: 843 (connection reset by peer)
                strcpy(ucTxBuf, "AT+WIPDATA=2,1,1\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Read/write from/to a socket\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(1200);
                break;

            case 180: // Check the GPRS connection counter is over maximum connection counter
                ucGprsConnectCnt++;
#ifdef USER_DEBUG
                Rprintf("ucGprsConnectCnt=%d, ucGprsMaxConnectCnt=%d\n", ucGprsConnectCnt, ucGprsMaxConnectCnt);
#endif
                if (ucGprsConnectCnt < ucGprsMaxConnectCnt) {
                    usGprs10MSTimer = TIMER_Get10MSTimer();
                    usGprsTaskStep++;
                    if (ucTMSDownloadFlag) {
                        iTMS_ProcessStep = 2;
                    }
                } else {
                    usGprsTaskStep = 0;
                    ucGprsConnectCnt = 0;
                    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                        AbnormalProcessingBeforeTx();
                    }
                }
                return;
            case 181: // If reconnecting pause time is elapsed, retry to connect
                if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= GPRS_RECONNECTING_PAUSE_TIME) {
                    usGprsTaskStep++;
                }
                return;
            case 182: // Retry to connect
                usGprsTaskStep = 0;
                ucReqDataReadyFlag = 1;
                ModemOpen(NORMAL_CONNECTION);
                return;

            case 190:
                // strcpy(ucTxBuf, "AT+CFUN=1,0\r");
                strcpy(ucTxBuf, "AT+CFUN=1\r");
#ifdef USER_DEBUG
                //Rprintf("\r\n%d - AT+CFUN=1,0\r\n", usGprsTaskStep);
                Rprintf("\r\n%d - AT+CFUN=1\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(1200);
                break;
            case 192:
                if (++usWipCmdRetryCnt < MAX_RETRY_WIPCREATE) {
                    strcpy(ucTxBuf, "AT+WIPCLOSE=2,1\r");
#ifdef USER_DEBUG
                    Rprintf("\r\n%d - AT+WIPCLOSE=2,1\r\n", usGprsTaskStep);
                    Rprintf("%s\n", ucTxBuf);
#endif
                    GprsSendCmdSetTime(1200);
                } else {
                    ModemClose();
                    usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                }

                break;


            case 1: // Delay for sending First Echo off command (within 4 seconds after reset)
            case 10: // Delay for sending Read the SIM status command (within 6 seconds after reset)
            case 14: // Delay for sending Enter PIN command
            case 18: // Delay for sending Read selected an operator command
            case 22: // Delay for sending Set network registration mode command
            case 60: // Delay for sending Check Signal Quality command
            case 64: // Delay for sending Check the registration status command
            case 70: // Delay for sending Start the Open AT�� embedded application command
            case 74: // Delay for sending Start TCP/IP stack command
            case 78: // Delay for sending Open General Packet Radio Service(GPRS) bearer command
            case 82: // Delay for sending Set Access Point Name(APN) of GPRS bearer command
            case 86: // Delay for sending Set User Name command
            case 90: // Delay for sending Set password command
            case 94: // Delay for sending Start GPRS bearer as client command (Check SIM, GPRS network, and bearer connection)
            case 160: // Delay for sending Create the TCP client socket with index 1 command
            case 164: // Delay for sending Read/write from/to a socket command
                switch (usGprsTaskStep) {
                    case 1: // Delay for sending First Echo off command (within 4 seconds after reset)
                        usGprs10MSMaxTimeout = 20;
                        break;
                    case 10: // Delay for sending Read the SIM status command (within 6 seconds after reset)
                    case 18: // Delay for sending Read selected an operator command
                    case 22: // Delay for sending Set network registration mode command
                    case 60: // Delay for sending Check Signal Quality command
                    case 64: // Delay for sending Check the registration status command
                    case 94: // Delay for sending Start GPRS bearer as client command (Check SIM, GPRS network, and bearer connection)
                        usGprs10MSMaxTimeout = 50; // �����ð��� �ʹ� ������ SIM ���¸� ����� üũ���� ����
                        break;
                    default:
                        //usGprs10MSMaxTimeout = 10;
                        usGprs10MSMaxTimeout = 20;
                        break;
                }
                usGprs10MSTimer = TIMER_Get10MSTimer();
                usGprsTaskStep++;
                break;
        }

        if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= usGprs10MSMaxTimeout) {
            switch (usGprsTaskStep) {
                case 2: // Delay for sending First Echo off command (within 4 seconds after reset)
                case 11: // Delay for sending Read the SIM status command (within 6 seconds after reset)
                case 15: // Delay for sending Enter PIN command
                case 19: // Delay for sending Read selected an operator command
                case 23: // Delay for sending Set network registration mode command
                case 61: // Delay for sending Check Signal Quality command
                case 65: // Delay for sending Check the registration status command
                case 71: // Delay for sending Start the Open AT�� embedded application command
                case 75: // Delay for sending Start TCP/IP stack command
                case 79: // Delay for sending Open General Packet Radio Service(GPRS) bearer command
                case 83: // Delay for sending Set Access Point Name(APN) of GPRS bearer command
                case 87: // Delay for sending Set User Name command
                case 91: // Delay for sending Set password command
                case 95: // Delay for sending Start GPRS bearer as client command (Check SIM, GPRS network, and bearer connection)
                case 161: // Delay for sending Create the TCP client socket with index 1 command
                case 165: // Delay for sending Read/write from/to a socket command
                    usGprsTaskStep++;
                    break;

                case 4: // Waiting for response of First Echo off command (within 4 seconds after reset)
#ifdef USER_DEBUG
                    Rprintf("\r\nE>%d - Timeout[%d]\r\n", usGprsTaskStep, ucGprsCmdRetryCnt);
#endif
                    // (200ms + 500ms) x 9 = 6.3 seconds
                    if (ucGprsCmdRetryCnt >= 8) {
                        ucGprsModuleOkFlag = 0;
                        ucGprsPowerOffFlag = 1;
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("\r\nE>%d - GSM module doesn't response\r\n", usGprsTaskStep);
#endif
                            // "????????????????", "   GSM module   ", "doesn't response", "                "
                            LCDDisplay4Lines(M4GSMNoResponse_0001, -1, ucLangFlag);
                            AbnormalProcessingBeforeTx();
                        } else {
                            ModemClose();
                        }
                    } else {
                        ucGprsCmdRetryCnt++;
                        usGprsTaskStep = 1; // Delay for sending First Echo off command (within 4 seconds after reset)
                    }
                    break;

                case 97:
                    if (GPRS_bearer_Retry-- > 0) {
                        usGprsTaskStep = 96; // Delay for sending Create the TCP client socket with index 1 command
                    } else {
                        ModemClose();
                        usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                    }
                    break;

                case 163: // Waiting for response of Create the TCP client socket with index 1 command
                    usGprsTaskStep = 192;
                    break;

                case 167: // Waiting for response of Read/write from/to a socket command
                    ModemClose();
                    usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                    break;
                default:
                    if (ucGprsCmdRetryCnt < GPRS_MAX_CMD_RETRY) {
                        ucGprsCmdRetryCnt++;
                        usGprsTaskStep -= 3;
                    } else {
                        usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                    }
                    break;
            }
            return;
        }

        if (RS232_CheckRxInput(GPRS_COM_PORT) == 0) {
            return;
        }

        rxdata = RS232_Read(GPRS_COM_PORT) & 0xFF;
#ifdef USER_DEBUG
        if (usGprsTaskStep != 63 && usGprsTaskStep != 67)
            Rprintf("%c", (unsigned char) rxdata);
#endif
        ucRxBuf[iRxCnt] = rxdata;
        iRxCnt++;
        iRxCnt &= 0x1FFF;

        if (iRxCnt >= 2 && ucRxBuf[iRxCnt - 2] == '\r' && ucRxBuf[iRxCnt - 1] == '\n') {
            if (iRxCnt == 4 && !memcmp((char *) &ucRxBuf[0], "OK", 2)) {
                ucGprsCmdRetryCnt = 0;
                switch (usGprsTaskStep) {
                    case 191:
                        usGprsTaskStep = 3;
                        break;
                    case 193:
                        usGprsTaskStep = 162;
                        break;

                    case 4: // Waiting for response of First Echo off command (within 4 seconds after reset)
                    case 73: // Waiting for response of Start the Open AT�� embedded application command
                    case 77: // Waiting for response of Start TCP/IP stack command
                    case 81: // Waiting for response of Open General Packet Radio Service(GPRS) bearer command
                    case 85: // Waiting for response of Set Access Point Name(APN) of GPRS bearer command (maximum 96 characters)
                    case 89: // Waiting for response of Set User Name command (maximum 64 characters)
                    case 93: // Waiting for response of Set password command (maximum 64 characters)
                        usGprsTaskStep++;
                        break;
                    case 17: // Waiting for response of Enter PIN command
                        ucGprsSIMStatus = SIM_READY;
                        usGprsTaskStep = 18; // Delay for sending Read selected an operator command
                        break;
                    case 21: // Waiting for response of Read selected an operator command
                        if (ucGsmNetworkRegistrationMode == 0) {
                            ucGprsSIMCheckedFlag = 1;
                            usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                        } else {
                            usGprsTaskStep++;
                        }
                        break;
                    case 25: // Waiting for response of Set network registration mode command
                        ucGprsSIMCheckedFlag = 1;
                        usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                        break;
                    case 63: // Waiting for response of Check Signal Quality command
                        if (*pusServiceAddr == 0x0000) {
                            // No signal
                            if (ucGprsRssiValue == 99) {
#ifdef USER_DEBUG
                                //Rprintf("\r\nucGprsRssiRetryCnt = %d\r\n", ucGprsRssiRetryCnt);
#endif
                                if (ucGprsRssiRetryCnt & 0x01) {
                                    GprsDisplayAntennaLevelBar(GPRS_ANTENNA_LEVEL_1_LIMIT);
                                } else {
                                    GprsDisplayAntennaLevelBar(ucGprsRssiValue);
                                }
                            } else {
                                GprsDisplayAntennaLevelBar(ucGprsRssiValue);
                            }
                        }

                        // No signal
                        if (ucGprsRssiValue == 99) {
                            // 500ms x 30 = 15 seconds
                            if (ucGprsRssiRetryCnt >= 29) {
#ifdef USER_DEBUG
                                //Rprintf("\r\n%d - No signal\r\n", usGprsTaskStep);
#endif
                                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                    // "????????????????", "No Signal       ", "                ", "                "
                                    LCDDisplay4Lines(M4NoSignal_000000001, -1, ucLangFlag);
                                    ucGprsRssiRetryCnt = 0;
                                    AbnormalProcessingBeforeTx();
                                } else {
                                    ucGprsRssiRetryCnt++;
                                    if (ucGprsRssiRetryCnt > 30) {
                                        ucGprsRssiRetryCnt = 29;
                                    }
                                    usGprsTaskStep -= 3;
                                }
                            } else {
                                ucGprsRssiRetryCnt++;
                                usGprsTaskStep -= 3;
                            }
                        } else {
                            ucGprsRssiRetryCnt = 0;
                            usGprsTaskStep++;
                            // Test for IC5100 GSM
                            //usGprsTaskStep = 60;	// Delay for sending Check Signal Quality command
                        }
                        break;
                    case 67: // Waiting for response of Check the registration status command
                        switch (ucGprsRegistrationStatus) {
                            case 1: // registered, home network
                            case 5: // registered, roaming
#ifdef USER_DEBUG
                                if (ucGprsRegistrationStatus == 1) {
                                    //									Rprintf("\r\n%d - registered, home network\r\n", usGprsTaskStep);
                                } else {
                                    Rprintf("\r\n%d - registered, roaming\r\n", usGprsTaskStep);
                                }
#endif
                                /* sispp 20111012 check point */
                                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                    if (ucGprsBearerOpenedFlag) {
                                        usGprsTaskStep = 160; // Delay for sending Create the TCP client socket with index 1 command
                                        usWipCmdRetryCnt = 0;
                                    } else {
                                        usGprsTaskStep = 70; // Delay for sending Start the Open AT�� embedded application command
                                    }
                                } else {
                                    if (*pusServiceAddr == 0x0000) {
                                        //LCD_DisplayString(0, 12, 4, " GSM", ucLangFlag);
                                        DisplaySimGprsIcon(-1, 1);
                                    }
                                    if (sz18GsmOperator[0] == 0x00) {
                                        usGprsTaskStep = 20;
                                    } else {
                                        usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                                    }
                                }

                                /*
                                                                                                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                                                                                        usGprsTaskStep = 70;	// Delay for sending Change the local serial port character framing used by the DCE command
                                                                                                }
                                                                                                else {
                                                                                                        if (*pusServiceAddr == 0x0000) {
                                                                                                                LCD_DisplayString(0, 12, 4, " GSM", ucLangFlag);
                                                                                                                DisplaySimGprsIcon(-1, 1);
                                                                                                        }
                                                                                                        usGprsTaskStep = 60;	// Delay for sending Check Signal Quality command
                                                                                                }
                                 */
                                ucGprsRegistrationRetryCnt = 0;
                                break;
                            case 0: // not registered, ME is not currently searching for a new operator
                            case 2: // not registered, ME currently searching for a new operator
                            case 3: // registration denied
                            case 4: // unknown
#ifdef USER_DEBUG
                                if (ucGprsRegistrationStatus == 0) {
                                    Rprintf("\r\nE>%d - not registered, ME is not currently searching for a new operator\r\n", usGprsTaskStep);
                                } else if (ucGprsRegistrationStatus == 2) {
                                    Rprintf("\r\nE>%d - not registered, ME currently searching for a new operator\r\n", usGprsTaskStep);
                                } else if (ucGprsRegistrationStatus == 3) {
                                    Rprintf("\r\nE>%d - registration denied\r\n", usGprsTaskStep);
                                } else {
                                    Rprintf("\r\nE>%d - unknown\r\n", usGprsTaskStep);
                                }
#endif
                                if (*pusServiceAddr == 0x0000) {
#ifdef USER_DEBUG
                                    Rprintf("\r\nucGprsRegistrationRetryCnt = %d\r\n", ucGprsRegistrationRetryCnt);
#endif
                                    if (ucGprsRegistrationRetryCnt & 0x01) {
                                        //LCD_DisplayString(0, 12, 4, " GSM", ucLangFlag);
                                        DisplaySimGprsIcon(-1, 1);
                                    } else {
                                        //LCD_DisplayString(0, 12, 4, "    ", ucLangFlag);
                                        DisplaySimGprsIcon(-1, 0);
                                    }
                                }

                                // 500ms x 30 = 15 seconds
                                if (ucGprsRegistrationRetryCnt >= 29) {
                                    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                        if (ucGprsRegistrationStatus == 0 || ucGprsRegistrationStatus == 2) {
                                            // "????????????????", "is not          ", "registered      ", "                "
                                            LCDDisplay4Lines(M4NotRegistered_0001, -1, ucLangFlag);
                                        } else if (ucGprsRegistrationStatus == 3) {
                                            // "????????????????", "registration    ", "denied          ", "                "
                                            LCDDisplay4Lines(M4RegisterDenied_001, -1, ucLangFlag);
                                        } else {
                                            // "????????????????", "unknown network ", "status          ", "                "
                                            LCDDisplay4Lines(M4UnknownRegStatus_1, -1, ucLangFlag);
                                        }
                                        ucGprsRegistrationRetryCnt = 0;
                                        AbnormalProcessingBeforeTx();
                                    } else {
                                        ucGprsRegistrationRetryCnt++;
                                        if (ucGprsRegistrationRetryCnt > 30) {
                                            ucGprsRegistrationRetryCnt = 29;
                                        }
                                        usGprsTaskStep -= 3;
                                    }
                                } else {
                                    ucGprsRegistrationRetryCnt++;
                                    usGprsTaskStep -= 3;
                                }
                                break;
                        }
                        break;
                    case 97: // Waiting for response of Start GPRS bearer as client command (Check SIM, GPRS network, and bearer connection)
                        ucGprsBearerOpenedFlag = 1;
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                            usGprsTaskStep = 160; // Delay for sending Create the TCP client socket with index 1 command
                            usWipCmdRetryCnt = 0;
                        } else {
                            usGprsTaskStep = 60; // Delay for sending Start the Open AT�� embedded application command
                        }
#ifdef USER_DEBUG
                        lGprsTest1SecCheckTimer = GetULDateTime();
                        Rprintf("Elapsed time = %ld\r\n", lGprsTest1SecCheckTimer - lGprsTest1SecStartTimer);
#endif
                        break;

                }
            } else if (iRxCnt >= 15 && !memcmp((char *) &ucRxBuf[0], "+CME ERROR: ", 12)) {
                memset(temp, 0x00, sizeof (temp));
                for (i = 12, j = 0; i < iRxCnt; i++) {
                    if (ucRxBuf[i] == '\r') {
                        break;
                    }
                    temp[0][j++] = ucRxBuf[i];
                }
                error_code = atoi(temp[0]);

                ret = 0;
                switch (error_code) {
                    case 10: // SIM not inserted
                    case 13: // SIM failure
                    case 15: // SIM wrong
                    case 262: // SIM blocked
                    case 556: // AT command aborted by a SIM Extract
                    case 810: // no SIM card present
                        //					case 811:	// SIM not ready
                        ucGprsSIMStatus = SIM_FAILURE;
                        ret = -1; // fatal error
                        break;
                    case 811: // SIM not ready
                        usGprsTaskStep = 190;
                        break;
                        /*					case 40:	// Network lock
                                                                        ucGprsSIMStatus = PH_NET_PIN;
                                                                        ret = -1;	// fatal error
                                                                        break;
                                                                case 42:	// Network subset lock
                                                                        ucGprsSIMStatus = PH_NETSUB_PIN;
                                                                        ret = -1;	// fatal error
                                                                        break;
                                                                case 44:	// Service Provider lock
                                                                        ucGprsSIMStatus = PH_SERVPROV_PIN;
                                                                        ret = -1;	// fatal error
                                                                        break;
                                                                case 46:	// Corporate lock
                                                                        ucGprsSIMStatus = PH_CORPORATE_PIN;
                                                                        ret = -1;	// fatal error
                                                                        break;
                         */ case 40: // Network personalization PIN required
                        ucGprsSIMStatus = PH_NET_PIN;
                        ret = -1; // fatal error
                        break;
                    case 41: // Network personalization PUK required
                        ucGprsSIMStatus = PH_NET_PUK;
                        ret = -1; // fatal error
                        break;
                    case 42: // Network subset personalization PIN required
                        ucGprsSIMStatus = PH_NET_SUB_PIN;
                        ret = -1; // fatal error
                        break;
                    case 43: // Network subset personalization PUK required
                        ucGprsSIMStatus = PH_NET_SUB_PUK;
                        ret = -1; // fatal error
                        break;
                    case 44: // Service provider personalization PIN required
                        ucGprsSIMStatus = PH_SVC_PROVIDER_PIN;
                        ret = -1; // fatal error
                        break;
                    case 45: // Service provider personalization PUK required
                        ucGprsSIMStatus = PH_SVC_PROVIDER_PUK;
                        ret = -1; // fatal error
                        break;
                    case 46: // Corporate personalization PIN required
                        ucGprsSIMStatus = PH_CORPORATE_PIN;
                        ret = -1; // fatal error
                        break;
                    case 47: // Corporate personalization PUK required
                        ucGprsSIMStatus = PH_CORPORATE_PUK;
                        ret = -1; // fatal error
                        break;
                    case 48: // PH-SIM PUK (master phone code) required
                        ucGprsSIMStatus = PH_SIM_PUK;
                        ret = -1; // fatal error
                        break;
                        //case 541:	// since main versions do not match, the Open AT�� application can not be started
                        //	ret = -2;
                        //	break;
                        //case 16:	// Incorrect password or Bad user PIN
                    case 18: // SIM PUK2 required
                        ucGprsSIMStatus = SIM_PUK2;
                        ret = -1; // fatal error
                        break;
                    case 554: // The SIM is blocked (PIN 1/CHV 1 and PUK 1 codes are burned)
                        ucGprsSIMStatus = SIM_BLOCK;
                        ret = -1; // fatal error
                        break;
                    case 515: // Please wait, init or command processing in progress
                        // Waiting for response of Read the SIM status command (within 6 seconds after reset)
                        if (usGprsTaskStep == 13) {
                            // 500ms x 16 = 8.0 seconds
                            if (ucGprsCmdRetryCnt < 15) {
                                ucGprsCmdRetryCnt++;
                                usGprsTaskStep -= 3;
                            } else {
                                ucGprsSIMStatus = SIM_FAILURE;
                                ret = -1; // fatal error
                            }
                        } else {
                            ret = -2;
                        }
                        break;

                    case 844: // stack already started
                        // Waiting for response of Start TCP/IP stack command
                        if (usGprsTaskStep == 77) {
                            usGprsTaskStep++;
                        } else {
                            ret = -2;
                        }
                        break;

                    case 804: // device already open
                        // Waiting for response of Open General Packet Radio Service(GPRS) bearer command
                        if (usGprsTaskStep == 81) {
                            usGprsTaskStep++;
                        } else {
                            ret = -2;
                        }
                        break;

                    case 803: // already open or operation not allowed in the current WIP stack state
                        // Waiting for response of Start GPRS bearer as client command (Check SIM, GPRS network, and bearer connection)
                        if (usGprsTaskStep == 97) {
                            ucGprsBearerOpenedFlag = 1;
                            if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                usGprsTaskStep = 160; // Delay for sending Create the TCP client socket with index 1 command
                            } else {
                                usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                            }
                        } else {
                            ucGprsBearerOpenedFlag = 0;
                            ret = -2;
                        }
                        break;

                    case 812: // GPRS network failure
                        if (usGprsTaskStep == 97) {
                            usGprs10MSTimer = TIMER_Get10MSTimer();
                            usGprs10MSMaxTimeout = 100;
                            break;
                        }
                        ucGprsBearerOpenedFlag = 0;
                        ret = -2;
                        break;

                    case 807: // line busy
                    case 808: // no answer
                    case 809: // no carrier
                    case 813: // PPP LCP negotiation failed
                    case 814: // PPP authentication failed
                    case 815: // PPP IPCP negotiation failed
                    case 816: // PPP peer terminates session
                    case 817: // PPP peer does not answer to echo request
                    case 831: // bad state
                    case 837: // bad protocol
                    case 839: // error during channel creation
                    case 841: // peer closed
                    case 847: // bearer connection failure: WIP_BOPT_GPRS_TIMEOUT time limit expired before GPRS bearer connected
                    case 848: // impossible to connect to the bearer
                    case 849: // connection to the bearer has succeeded but a problem has occurred during the data flow establishment
                        ucGprsBearerOpenedFlag = 0;
                        ret = -2;
                        break;

                    case 842: // destination host unreachable
                        if (usGprsTaskStep == 163) {
                            usGprsTaskStep = 192;
                        } else {
                            ret = -2;
                        }
                        break;

                        //					case 842:	// destination host unreachable
                    case 843: // connection reset by peer
                        ret = -2;
                        break;

                    case 861: // user name rejected by server
                    case 862: // password rejected by server
                        ret = -2;
                        break;

                    case 840:
                        if (usGprsTaskStep == 163) {
                            usGprsTaskStep++;
                        }
                        break;

                    case 850:
                        if (usGprsTaskStep == 77) {
                            usGprsTaskStep = 160;
                        }
                        break;

                    default:
                        // Waiting for response of Read the SIM status command (within 6 seconds after reset)
                        if (usGprsTaskStep == 13) {
                            ucGprsSIMStatus = SIM_FAILURE;
                            ret = -1; // fatal error
                        } else {
                            ret = -2;
                        }
                        break;
                }

#ifdef USER_DEBUG
#if 0
                memset(temp, 0x00, sizeof (temp));
                for (i = 0;; i++) {
                    if (CME_ERROR_CODE[i].error_code == error_code ||
                            CME_ERROR_CODE[i].error_code == -1) {
                        strcpy(temp[0], CME_ERROR_CODE[i].error_msg);
                        break;
                    }
                }
                Rprintf("%s\r\n", temp[0]);
#endif
#endif

                if (ret) {
                    if (ret == -1) { // fatal error
                        ucGprsPowerOffFlag = 1;
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("SIM Error!!\r\n");
#endif
                            GprsDisplaySIMErrorMessage();
                            AbnormalProcessingBeforeTx();
                        } else {
                            ModemClose();
                        }
                    } else {
                        //if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                        if (ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("Modem Error!!\r\n");
#endif
                            // "Modem Error     ",
                            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ModemError_0000001], ucLangFlag);
                            AbnormalProcessingBeforeTx();
                        } else {
                            if (usGprsTaskStep >= 163 && usGprsTaskStep <= 167) {
                                ModemClose();
                            }
                            usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                        }
                    }
                }
            } else if (iRxCnt >= 15 && !memcmp((char *) &ucRxBuf[0], "+CMS ERROR: ", 12)) {

            } else if (iRxCnt >= 14 && !memcmp((char *) &ucRxBuf[0], "+CPIN: ", 7)) {
                // Waiting for response of Read the SIM status command (within 6 seconds after reset)
                if (usGprsTaskStep == 13) {
                    memset(temp, 0x00, sizeof (temp));
                    for (i = 7, j = 0; i < iRxCnt; i++) {
                        if (ucRxBuf[i] == '\r') {
                            break;
                        }
                        temp[0][j++] = ucRxBuf[i];
                    }

                    if (!strcmp(temp[0], "READY")) {
                        ucGprsSIMStatus = SIM_READY;
                    } else if (!strcmp(temp[0], "SIM PIN")) {
                        ucGprsSIMStatus = SIM_PIN;
                    } else if (!strcmp(temp[0], "SIM PUK")) {
                        ucGprsSIMStatus = SIM_PUK;
                    } else if (!strcmp(temp[0], "SIM PIN2")) {
                        ucGprsSIMStatus = SIM_PIN2;
                    } else if (!strcmp(temp[0], "SIM PUK2")) {
                        ucGprsSIMStatus = SIM_PUK2;
                    } else if (!strcmp(temp[0], "PH-SIM PIN")) {
                        ucGprsSIMStatus = PH_SIM_PIN;
                    } else if (!strcmp(temp[0], "PH-NET PIN")) {
                        ucGprsSIMStatus = PH_NET_PIN;
                    } else if (!strcmp(temp[0], "PH-NETSUB PIN")) {
                        ucGprsSIMStatus = PH_NET_SUB_PIN;
                    } else if (!strcmp(temp[0], "PH-SERVPROV PIN")) {
                        ucGprsSIMStatus = PH_SVC_PROVIDER_PIN;
                    } else if (!strcmp(temp[0], "PH-CORPORATE PIN")) {
                        ucGprsSIMStatus = PH_CORPORATE_PIN;
                    }

                    if (ucGprsSIMStatus == SIM_READY) {
                        ucGprsSIMCheckedFlag = 1;
                        ucGprsCmdRetryCnt = 0;
                        usGprsTaskStep = 18; // Delay for sending Read selected an operator command
                    }                        // for test
                        //else if (ucGprsSIMStatus == SIM_PIN) {
                        //	ucGprsSIMStatus = SIM_CHECK;
                        //	ucGprsCmdRetryCnt = 0;
                        //	usGprsTaskStep++;
                        //}
                        //
                    else {
                        ucGprsPowerOffFlag = 1;
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("SIM Error!!\r\n");
#endif
                            GprsDisplaySIMErrorMessage();
                            AbnormalProcessingBeforeTx();
                        } else {
                            ModemClose();
                        }
                    }
                }
            } else if (iRxCnt >= 10 && !memcmp((char *) &ucRxBuf[0], "+COPS: ", 7)) {
                // Waiting for response of Read selected an operator command
                if (usGprsTaskStep == 21) {
                    memset(temp, 0x00, sizeof (temp));
                    for (i = 7, j = k = 0; i < iRxCnt; i++) {
                        if (ucRxBuf[i] == ',') {
                            k++;
                            j = 0;
                            continue;
                        } else if (ucRxBuf[i] == '\r') {
                            break;
                        }
                        temp[k][j++] = ucRxBuf[i];
                    }
                    ucGsmNetworkRegistrationMode = atoi(temp[0]);
                    memset(sz18GsmOperator, 0x00, sizeof (sz18GsmOperator));
                    if (k == 2) {
                        sz18GsmOperator[0] = temp[1][0];
                        strcpy(&sz18GsmOperator[1], temp[2]);
                    }
                }
            } else if (iRxCnt >= 11 && !memcmp((char *) &ucRxBuf[0], "+CSQ: ", 6)) {
                // Waiting for response of Check Signal Quality command
                if (usGprsTaskStep == 63) {
                    memset(temp, 0x00, sizeof (temp));
                    for (i = 6, j = 0, k = 0; i < iRxCnt; i++) {
                        if (ucRxBuf[i] == ',') {
                            k++;
                            if (k < 2) {
                                j = 0;
                                continue;
                            } else {
                                break;
                            }
                        } else if (ucRxBuf[i] == '\r') {
                            break;
                        }
                        temp[k][j++] = ucRxBuf[i];
                    }
#ifdef USER_DEBUG
                    if (ucGprsRssiValue != atoi(temp[0])) {
                        Rprintf("+CSQ: %d,%d\r\n", atoi(temp[0]), atoi(temp[1]));
                    }
#endif
                    ucGprsRssiValue = atoi(temp[0]);
                    ucGprsBerValue = atoi(temp[1]);
                }
            } else if (iRxCnt >= 12 && !memcmp((char *) &ucRxBuf[0], "+CREG: ", 7)) {
                // Waiting for response of Check the registration status command
                if (usGprsTaskStep == 67) {
                    memset(temp, 0x00, sizeof (temp));
                    temp[0][0] = ucRxBuf[9];
                    ucGprsRegistrationStatus = atoi(temp[0]);
                }
            } else if (iRxCnt >= 15 && !memcmp((char *) &ucRxBuf[0], "+WIPREADY:", 10)) {
                // +WIPREADY: 2,1 or +WIPREADY: 2, 1
                // Waiting for response of Create the TCP client socket with index 1 command
                if (usGprsTaskStep == 163) {
                    usGprsTaskStep++;
#ifdef USER_DEBUG
                    lGprsTest1SecCheckTimer = GetULDateTime();
                    Rprintf("Elapsed time = %ld\r\n", lGprsTest1SecCheckTimer - lGprsTest1SecStartTimer);
#endif
                }
            } else if (iRxCnt >= 9 && !memcmp((char *) &ucRxBuf[0], "CONNECT", 7)) {
                // Waiting for response of Read/write from/to a socket command
                if (usGprsTaskStep == 167) {
                    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                        // " LINE CONNECTED ",
                        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1LineConnected_0001], ucLangFlag);
#ifdef USER_DEBUG
                        lGprsTest1SecCheckTimer = GetULDateTime();
                        Rprintf("Elapsed time = %ld\r\n", lGprsTest1SecCheckTimer - lGprsTest1SecStartTimer);
#endif
                    }

                    usGprs10MSMaxTimeout = (unsigned short) (st_POSSetupInfo.ucCommTimeout) * 100;
                    usGprs10MSTimer = TIMER_Get10MSTimer();
                    ucReqDataReadyFlag = 1;
                    usGprsTaskStep = 201; // Wait for data setup & Sending Data
                    if (iTMS_ProcessStep == 2) {
                        usTMSDownload10MSTimer = TIMER_Get10MSTimer();
                        iTMS_ProcessStep = 3;
                    }
                }
                iRxCnt = 0;
            } else if (iRxCnt == 12 && !memcmp((char *) &ucRxBuf[0], "NO CARRIER", 10)) {
#ifdef USER_DEBUG
                Rprintf("\r\nE>%d - No Carrier\r\n", usGprsTaskStep);
#endif
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "No Carrier      ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1NoCarrierError_001], ucLangFlag);
                }
                usGprsTaskStep = 0;
                ModemClose();
                usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
            } else if (iRxCnt == 11 && !memcmp((char *) &ucRxBuf[0], "NO ANSWER", 9)) {
                // about 65 seconds
#ifdef USER_DEBUG
                Rprintf("\r\nE>%d - No Answer\r\n", usGprsTaskStep);
#endif
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "Timeout(S7)     ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1S7TimeoutError_001], ucLangFlag);
                }
                ModemClose();
                usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
            } else if (iRxCnt == 6 && !memcmp((char *) &ucRxBuf[0], "BUSY", 4)) {
#ifdef USER_DEBUG
                Rprintf("\r\nE>%d - BUSY\r\n", usGprsTaskStep);
#endif
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "Busy            ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1LineBusyError_0001], ucLangFlag);
                }
                ModemClose();
                usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
            } else if (iRxCnt == 7 && !memcmp((char *) &ucRxBuf[0], "ERROR", 5)) {
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "Modem Error     ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ModemError_0000001], ucLangFlag);
                    AbnormalProcessingBeforeTx();
                } else {
                    ModemClose();
                }
            }
            memset((char *) &ucRxBuf[0], 0, iRxCnt);
            iRxCnt = 0;
        }
        return;
    }

    // Data Mode
    if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= usGprs10MSMaxTimeout) {
#ifdef USER_DEBUG
        Rprintf("usGprs10MSTimer=%d, usGprs10MSMaxTimeout=%d, Elapsed=%d\r\n", usGprs10MSTimer, usGprs10MSMaxTimeout, TIMER_GetElapsed10MSTime(usGprs10MSTimer));
        Rprintf("\r\nE>%d - COMM Timeout\r\n", usGprsTaskStep);
#endif

        if (ucReqDataReadyFlag || ucReqDataTxFlag) {
            // "COMM Timeout    ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1CommTimeoutError_1], ucLangFlag);
        }

        if (giTransactionType == TRXN_BANK_EFTTRAN && ucReqDataTxFlag) {
            AbnormalProcessingAfterTx();
        } else {
            ModemClose();
            usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
        }
        return;
    }


    // Send Request Data if Request Data is ready
    if ((usGprsTaskStep == 201 || usGprsTaskStep == 205) && ucReqDataReadyFlag) {
        ucReqDataReadyFlag = 0;

        // "SENDING DATA... ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SendingData_000001], ucLangFlag);

        if (usGprsTaskStep == 201) {
            pusReqSequence = (int *) tbl_ReqSequence[giTransactionType];
            giRequestType = *pusReqSequence;
        }

        BuildQueryString();

        if (*pusReqSequence == API_BANK_EFTTRAN) {
            //tPOSUtilBuf.usBatchNo = st_TrxnReqData.usBatchNo;
            tPOSUtilBuf.usSeqNo++;
            SavePOSUtilBuf();
            if (st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY || st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
                if (ucReversalFlag == 0) {
                    SaveTxTransactionLog();
                }
            }
        }

        SendRequestMessage(giRequestType, ucTrxnTxBuf, "");
        ucReqDataTxFlag = 1;
        iRxCnt = 0;
        iKeyCnt = 0;

        ucGprsDLESetFlag = 0;

        usGprs10MSTimer = TIMER_Get10MSTimer();
        usGprsTaskStep = 202;

        usGprs10MSMaxTimeout = (unsigned short) (st_POSSetupInfo.ucCommTimeout) * 100;
        //usGprs10MSMaxTimeout = 1000;
        //Rprintf("usGprs10MSTimer=%d, usGprs10MSMaxTimeout=%d\r\n", usGprs10MSTimer, usGprs10MSMaxTimeout);

        //return;

#ifdef TEST_OFFLINE

        // "RECEIVING DATA..",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReceivingData_0001], ucLangFlag);
        if (giTransactionType == TRXN_BANK_EFTTRAN) {
            //	strcpy(&ucRxBuf[0], "<efttran><tran><result>1</result><message>Approved</message><status>000</status><refno>000000002443</refno><tranno>171</tranno><batchno>5</batchno><balance>N -100.00</balance><available>N 100.00</available></tran></efttran>");
            //	strcpy(&ucRxBuf[0], "<efttran><tran><result>1</result><message>Approved</message><status>000</status><refno>000000354236</refno><tranno>4</tranno><batchno>3</batchno><fromacc>0028416874</fromacc><iccresponse>9120CB18FBEB008000000000000000000000</iccresponse></tran></efttran>");
            strcpy(&ucRxBuf[0], "<efttran><tran><result>1</result><message>Approved</message><status>000</status><refno>000000372061</refno><tranno>5</tranno><batchno>3</batchno><fromacc>209073150201005900</fromacc><iccresponse>91147746DCCBB9D8BBEF0012</iccresponse><authid>366422</authid></tran></efttran>");
            /*
                    if(st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY)
                            return;
                    if(st_TrxnReqData.usTrxnType == TRXN_BALANCE_INQUIRY)
                            return;
                    strcpy(&ucRxBuf[0], "<efttran><tran><result>2</result><message>Transaction not found</message><status>302</status><tranno>4</tranno><batchno>6</batchno></tran></efttran>");
             */

        } else if (giTransactionType == TRXN_BANK_EFTTOTAL) {
            strcpy(&ucRxBuf[0], "<efttotals><result>0</result><batchno>7</batchno></efttotals>");
        } else if (giTransactionType == TRXN_TAMS_CALLHOME) {
            //strcpy(&ucRxBuf[0], "<error><errcode>5</errcode><errmsg>Request could not be authenticated</errmsg></error>");
            strcpy(&ucRxBuf[0], "<callhome />");
        } else {
            if (*pusReqSequence == API_GET_APPLIST) {
                strcpy(&ucRxBuf[0], "<appllist><applsvr><applid>1</applid><name>Tams</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr><applsvr><applid>2</applid><name>VoucherVault</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr><applsvr><applid>3</applid><name>Banking</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr></appllist>");
            } else if (*pusReqSequence == API_GET_FUNCLIST) {
                if (pstAppList[giApplIdx].usApplId == 1) {
                    strcpy(&ucRxBuf[0], "<funclist><function><name>AGENTLOGIN</name><url>http://41.58.130.139/tams/tams/devinterface/agentlogin.php</url></function><function><name>AGENTLOGOUT</name><url>http://41.58.130.139/tams/tams/devinterface/agentlogout.php</url></function><function><name>CALLHOME</name><url>http://41.58.130.139/tams/tams/devinterface/callhome.php</url></function><function><name>EOD</name><url>http://41.58.130.139/tams/tams/devinterface/eod.php</url></function><function><name>GETKEYS</name><url>http://41.58.130.139/tams/tams/devinterface/getkeys.php</url></function><function><name>GETLOGO</name><url>http://41.58.130.139/tams/tams/devinterface/getlogo.php</url></function><function><name>GETMENU</name><url>http://41.58.130.139/tams/tams/devinterface/getmenu.php</url></function><function><name>GETPROMPTLIST</name><url>http://41.58.130.139/tams/tams/devinterface/getpromptlist.php</url></function><function><name>NEWKEY</name><url>http://41.58.130.139/tams/tams/devinterface/newkey.php</url></function><function><name>OPERATORREPORT</name><url>http://41.58.130.139/tams/tams/devinterface/operatorreport.php</url></function><function><name>PARAM</name><url>http://41.58.130.139/tams/tams/devinterface/getparams.php</url></function><function><name>TELLERCARDS</name><url>http://41.58.130.139/tams/tams/devinterface/tellercards.php</url></function></funclist>");
                } else if (pstAppList[giApplIdx].usApplId == 2) {
                    strcpy(&ucRxBuf[0], "<funclist><function><name>CANCELORDER</name><url>http://41.58.130.139/tams/vouchervault/devinterface/cancelorder.php</url></function><function><name>ELECSALE</name><url>http://41.58.130.139/tams/vouchervault/devinterface/electricityorder.php</url></function><function><name>GETBALANCE</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getbalance.php</url></function><function><name>GETSTOCK</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getstock.php</url></function><function><name>ORDER</name><url>http://41.58.130.139/tams/vouchervault/devinterface/order.php</url></function><function><name>PARAM</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getparams.php</url></function><function><name>PINLESSORDER</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessorder.php</url></function><function><name>PINLESSRECONTOTAL</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessrecontotal.php</url></function><function><name>PINLESSREVERSAL</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessreversal.php</url></function><function><name>PINLESSSTATUS</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessstatus.php</url></function><function><name>PINLESSUPLOAD</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessupload.php</url></function><function><name>PRODLIST</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getprodlist.php</url></function><function><name>REPRINT</name><url>http://41.58.130.139/tams/vouchervault/devinterface/reprint.php</url></function><function><name>RETURNSTOCK</name><url>http://41.58.130.139/tams/vouchervault/devinterface/returnstock.php</url></function><function><name>SALES</name><url>http://41.58.130.139/tams/vouchervault/devinterface/sales.php</url></function><function><name>SPLIST</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getsplist.php</url></function><function><name>SPLOGO</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getsplogo.php</url></function></funclist>");
                } else if (pstAppList[giApplIdx].usApplId == 3) {
                    strcpy(&ucRxBuf[0], "<funclist><function><name>BINTABLE</name><url>http://41.58.130.139/tams/eftpos/devinterface/bintables.php</url></function><function><name>BIOTEMPLATE</name><url>http://41.58.130.139/tams/eftpos/devinterface/biotemplate.php</url></function><function><name>BIOTRAN</name><url>http://41.58.130.139/tams/eftpos/devinterface/biotran.php</url></function><function><name>DISTORDER</name><url>http://41.58.130.139/tams/eftpos/devinterface/distorder.php</url></function><function><name>DISTRETURN</name><url>http://41.58.130.139/tams/eftpos/devinterface/distreturn.php</url></function><function><name>EFTPARAMS</name><url>http://41.58.130.139/tams/eftpos/devinterface/eftparams.php</url></function><function><name>EFTTOTALS</name><url>http://41.58.130.139/tams/eftpos/devinterface/efttotals.php</url></function><function><name>EFTTRAN</name><url>http://41.58.130.139/tams/eftpos/devinterface/transaction.php</url></function><function><name>EMVAPP</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvapp.php</url></function><function><name>EMVCAPK</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvcapk.php</url></function><function><name>EMVREVOKECAPK</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvrevokecapk.php</url></function><function><name>EODTXNLIST</name><url>http://41.58.130.139/tams/eftpos/devinterface/txnlist.php</url></function><function><name>HOTCARDS</name><url>http://41.58.130.139/tams/eftpos/devinterface/hotcards.php</url></function><function><name>LINKED</name><url>http://41.58.130.139/tams/eftpos/devinterface/linked.php</url></function><function><name>UPLOADTXN</name><url>http://41.58.130.139/tams/eftpos/devinterface/uploadtxn.php</url></function></funclist>");
                }
            } else if (*pusReqSequence == API_TAMS_NEWKEY) {
                strcpy(&ucRxBuf[0], "<newkey><masterkey>9777c6788f5ee44cfee794612dc1f696</masterkey></newkey>");
            } else if (*pusReqSequence == API_TAMS_GETKEYS) {
                strcpy(&ucRxBuf[0], "<getkeys><cipher><no>0</no><key>019554019f4051c882b37c682bfb738a</key></cipher><cipher><no>1</no><key>24a6474789c0dcfbe6dcba7089124b92</key></cipher><cipher><no>2</no><key>08458a95de4b0337391b1c7c189f99de</key></cipher><cipher><no>3</no><key>1a1a8db92fa0e5ced51b3f66c128814d</key></cipher><cipher><no>4</no><key>0be32ce22dec665256eb105aed59de6a</key></cipher><cipher><no>5</no><key>fb05616934587afd3c3f4e342d380d3b</key></cipher><cipher><no>6</no><key>beccacac36deecdeb90f579a01c82db4</key></cipher><cipher><no>7</no><key>07d256cd4a03dae88ec00647952d2a0d</key></cipher><cipher><no>8</no><key>afee2a2c7a70756071f1b475a2283b39</key></cipher><cipher><no>9</no><key>a6ab7ad64c70a2aa30856730bea5ca3d</key></cipher></getkeys>");
            } else if (*pusReqSequence == API_TAMS_PARAM) {
                strcpy(&ucRxBuf[0], "<param><datetime><year>2012</year><syear>12</syear><mon>01</mon><day>18</day><hour>00</hour><min>32</min><sec>46</sec></datetime><merchantid>74</merchantid><header>bangar</header><footer>welcome</footer><pinreset>N</pinreset><updatelogo>N</updatelogo><updatemenu>N</updatemenu><replytimeout>60</replytimeout><currency>N</currency><fract>2</fract><prefix>Y</prefix><negnum>2</negnum><currcode>0566</currcode><decsym>.</decsym><thoussep>,</thoussep><countrycode>0566</countrycode><endofday>23</endofday><updateprompts>1326843166</updateprompts><attendance>N</attendance><agentaccess>N</agentaccess><eodtime><enabled>N</enabled></eodtime><conn1>0</conn1><conn2>0</conn2><download><enabled>N</enabled><downloadconn>0</downloadconn></download><disabled>N</disabled></param>");
            } else if (*pusReqSequence == API_BANK_EFTPARAMS) {
                strcpy(&ucRxBuf[0], "<eftparam><online>1</online><maxcashback>0</maxcashback><minbudgetperiod>6</minbudgetperiod><maxbudgetperiod>60</maxbudgetperiod><budgetminamount>0</budgetminamount><velocitytime>1</velocitytime><manualonline>N</manualonline><eodtxnlist>N</eodtxnlist></eftparam>");
            } else if (*pusReqSequence == API_BANK_BINTABLE) {
                strcpy(&ucRxBuf[0], "<bintable><bin><pan>9</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>0</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>84896</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>639587</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>639139</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>546097</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>541333</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>540463</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>539983</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>539923</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>530519</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>518791</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506120</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506119</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>125</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506118</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506117</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506111</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>61</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>506110</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506109</pan><length>18</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506108</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506105</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506101</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>3775</allow><keyindex>2</keyindex></bin><bin><pan>502192</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>13</check><allow>767</allow><keyindex>2</keyindex></bin><bin><pan>492181</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>476173</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>471415</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>57</check><allow>4096</allow><keyindex>2</keyindex></bin><bin><pan>470655</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>458536</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>446272</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>442434</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>428691</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>3775</allow><keyindex>2</keyindex></bin><bin><pan>427876</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>57</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>427011</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>422584</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>417059</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>413103</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>412053</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin></bintable>");
            } else if (*pusReqSequence == API_BANK_EMVAPP) {
                //strcpy(&ucRxBuf[0], "<emv><count>6</count><app><index>0</index><irn>1</irn><aid>A0000000032010</aid><match>0</match><name>Visa Electron</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>1</index><irn>2</irn><aid>A0000000031010</aid><match>0</match><name>Visa Credit</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>2</index><irn>3</irn><aid>A0000000041010</aid><match>0</match><name>MasterCard</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>3</index><irn>4</irn><aid>A0000000042010</aid><match>0</match><name>MasterCard Maestro</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>4</index><irn>5</irn><aid>A0000003710001</aid><match>0</match><name>Interswitch Verve</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>5</index><irn>6</irn><aid>A0000004540010</aid><match>0</match><name>eTranzact Genesis</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app></emv>");
                strcpy(&ucRxBuf[0], "<emv><count>7</count><app><index>0</index><irn>1</irn><aid>A0000000032010</aid><match>0</match><name>Visa Electron</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>1</index><irn>2</irn><aid>A0000000031010</aid><match>0</match><name>Visa Credit</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>2</index><irn>3</irn><aid>A0000000041010</aid><match>0</match><name>MasterCard</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>3</index><irn>4</irn><aid>A0000000042010</aid><match>0</match><name>MasterCard Maestro</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>4</index><irn>5</irn><aid>A0000003710001</aid><match>0</match><name>Interswitch Verve</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>5</index><irn>6</irn><aid>A0000004540010</aid><match>0</match><name>eTranzact Genesis</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>6</index><irn>7</irn><aid>A000000003</aid><match>0</match><name>Visa</name><appver>0100</appver><priority>1</priority><ddol>9F02069F03069F3704</ddol><tdol>9F02069F03068A02</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app></emv>");
            } else if (*pusReqSequence == API_BANK_EMVCAPK) {
                strcpy(&ucRxBuf[0], "<calist><count>10</count><ca><index>01</index><irn>1</irn><name>1</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>C696034213D7D8546984579D1D0F0EA519CFF8DEFFC429354CF3A871A6F7183F1228DA5C7470C055387100CB935A712C4E2864DF5D64BA93FE7E63E71F25B1E5F5298575EBE1C63AA617706917911DC2A75AC28B251C7EF40F2365912490B939BCA2124A30A28F54402C34AECA331AB67E1E79B285DD5771B5D9FF79EA630B75</modulus><exponent>03</exponent><hash>D34A6A776011C7E7CE3AEC5F03AD2F8CFC5503CC</hash><pkalgo>1</pkalgo></ca><ca><index>07</index><irn>2</irn><name>2</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>A89F25A56FA6DA258C8CA8B40427D927B4A1EB4D7EA326BBB12F97DED70AE5E4480FC9C5E8A972177110A1CC318D06D2F8F5C4844AC5FA79A4DC470BB11ED635699C17081B90F1B984F12E92C1C529276D8AF8EC7F28492097D8CD5BECEA16FE4088F6CFAB4A1B42328A1B996F9278B0B7E3311CA5EF856C2F888474B83612A82E4E00D0CD4069A6783140433D50725F</modulus><exponent>03</exponent><hash>B4BC56CC4E88324932CBC643D6898F6FE593B172</hash><pkalgo>1</pkalgo></ca><ca><index>08</index><irn>3</irn><name>3</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>D9FD6ED75D51D0E30664BD157023EAA1FFA871E4DA65672B863D255E81E137A51DE4F72BCC9E44ACE12127F87E263D3AF9DD9CF35CA4A7B01E907000BA85D24954C2FCA3074825DDD4C0C8F186CB020F683E02F2DEAD3969133F06F7845166ACEB57CA0FC2603445469811D293BFEFBAFAB57631B3DD91E796BF850A25012F1AE38F05AA5C4D6D03B1DC2E568612785938BBC9B3CD3A910C1DA55A5A9218ACE0F7A21287752682F15832A678D6E1ED0B</modulus><exponent>03</exponent><hash>20D213126955DE205ADC2FD2822BD22DE21CF9A8</hash><pkalgo>1</pkalgo></ca><ca><index>09</index><irn>4</irn><name>4</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>9D912248DE0A4E39C1A7DDE3F6D2588992C1A4095AFBD1824D1BA74847F2BC4926D2EFD904B4B54954CD189A54C5D1179654F8F9B0D2AB5F0357EB642FEDA95D3912C6576945FAB897E7062CAA44A4AA06B8FE6E3DBA18AF6AE3738E30429EE9BE03427C9D64F695FA8CAB4BFE376853EA34AD1D76BFCAD15908C077FFE6DC5521ECEF5D278A96E26F57359FFAEDA19434B937F1AD999DC5C41EB11935B44C18100E857F431A4A5A6BB65114F174C2D7B59FDF237D6BB1DD0916E644D709DED56481477C75D95CDD68254615F7740EC07F330AC5D67BCD75BF23D28A140826C026DBDE971A37CD3EF9B8DF644AC385010501EFC6509D7A41</modulus><exponent>03</exponent><hash>1FF80A40173F52D7D27E0F26A146A1C8CCB29046</hash><pkalgo>1</pkalgo></ca><ca><index>55</index><irn>5</irn><name>5</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>8B2BCDC1495920A5051AB3D6506E3BFDDC946A5F03957497A4836BE735227D3FDA33FB227A4DA15093845E8A08B392471CE0BEB588D6A3EB8571C2767350C387AF8E452BCD6F9A4848D835C08EDD91DE3A61B7D13FCA77B4628334792812289D5876226501D71B3EE4516351B017BD88C494F966383458273ABF0C40E7421F5F</modulus><exponent>03</exponent><hash>B0365792C471147B3FEA46608675DE7D16701661</hash><pkalgo>1</pkalgo></ca><ca><index>08</index><irn>6</irn><name>6</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>D9FD6ED75D51D0E30664BD157023EAA1FFA871E4DA65672B863D255E81E137A51DE4F72BCC9E44ACE12127F87E263D3AF9DD9CF35CA4A7B01E907000BA85D24954C2FCA3074825DDD4C0C8F186CB020F683E02F2DEAD3969133F06F7845166ACEB57CA0FC2603445469811D293BFEFBAFAB57631B3DD91E796BF850A25012F1AE38F05AA5C4D6D03B1DC2E568612785938BBC9B3CD3A910C1DA55A5A9218ACE0F7A21287752682F15832A678D6E1ED0B</modulus><exponent>03</exponent><hash>20D213126955DE205ADC2FD2822BD22DE21CF9A8</hash><pkalgo>1</pkalgo></ca><ca><index>99</index><irn>7</irn><name>7</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>AB79FCC9520896967E776E64444E5DCDD6E13611874F3985722520425295EEA4BD0C2781DE7F31CD3D041F565F747306EED62954B17EDABA3A6C5B85A1DE1BEB9A34141AF38FCF8279C9DEA0D5A6710D08DB4124F041 945587E20359BAB47B7575AD94262D4B25F264AF33DEDCF28E09615E937DE32EDC03C54445FE7E382777</modulus><exponent>03</exponent><hash>4ABFFD6B1C51212D05552E431C5B17007D2F5E6D</hash><pkalgo>1</pkalgo></ca><ca><index>95</index><irn>8</irn><name>8</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>BE9E1FA5E9A803852999C4AB432DB28600DCD9DAB76DFAAA47355A0FE37B1508AC6BF38860D3C6C2E5B12A3CAAF2A7005A7241EBAA7771112C74CF9A0634652FBCA0E5980C54A64761EA101A114E0F0B5572ADD57D010B7C9C887E104CA4EE1272DA66D997B9A90B5A6D624AB6C57E73C8F919000EB5F684898EF8C3DBEFB330C62660BED88EA78E909AFF05F6DA627B</modulus><exponent>03</exponent><hash>EE1511CEC71020A9B90443B37B1D5F6E703030F6</hash><pkalgo>1</pkalgo></ca><ca><index>92</index><irn>9</irn><name>9</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>996AF56F569187D09293C14810450ED8EE3357397B18A2458EFAA92DA3B6DF6514EC060195318FD43BE9B8F0CC669E3F844057CBDDF8BDA191BB64473BC8DC9A730DB8F6B4EDE3924186FFD9B8C7735789C23A36BA0B8AF65372EB57EA5D89E7D14E9C7B6B557460F10885DA16AC923F15AF3758F0F03EBD3C5C2C949CBA306DB44E6A2C076C5F67E281D7EF56785DC4D75945E491F01918800A9E2DC66F60080566CE0DAF8D17EAD46AD8E30A247C9F</modulus><exponent>03</exponent><hash>429C954A3859CEF91295F663C963E582ED6EB253</hash><pkalgo>1</pkalgo></ca><ca><index>94</index><irn>11</irn><name>11</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>ACD2B12302EE644F3F835ABD1FC7A6F62CCE48FFEC622AA8EF062BEF6FB8BA8BC68BBF6AB5870EED579BC3973E121303D34841A796D6DCBC41DBF9E52C4609795C0CCF7EE86FA1D5CB041071ED2C51D2202F63F1156C58A92D38BC60BDF424E1776E2BC9648078A03B36FB554375FC53D57C73F5160EA59F3AFC5398EC7B67758D65C9BFF7828B6B82D4BE124A416AB7301914311EA462C19F771F31B3B57336000DFF732D3B83DE07052D730354D297BEC72871DCCF0E193F171ABA27EE464C6A97690943D59BDABB2A27EB71CEEBDAFA1176046478FD62FEC452D5CA393296530AA3F41927ADFE434A2DF2AE3054F8840657A26E0FC617</modulus><exponent>03</exponent><hash>C4A3C43CCF87327D136B804160E47D43B60E6E0F</hash><pkalgo>1</pkalgo></ca></calist>");
            } else if (*pusReqSequence == API_BANK_EMVREVOKECAPK) {
                strcpy(&ucRxBuf[0], "<calist><count>0</count></calist>");
            } else if (*pusReqSequence == API_BANK_HOTCARDS) {
                strcpy(&ucRxBuf[0], "<hotcards />");
            }
        }

        iRxCnt = strlen(ucRxBuf);
        Rprintf("ucRxBuf[%d]=%s\r\n", iRxCnt, ucRxBuf);
        NIBSS_Parsing((char *) &ucRxBuf[0], iRxCnt, giRequestType, &gbTmpRespBuf);

        ucReqDataTxFlag = 0;
        ucReqDataReadyFlag = 0;
        // Function List �� App������ŭ ����
        if (st_ErrRespData.iErrFlag == 1) {
            if (giRequestType == API_TAMS_NEWKEY) {
                giRequestType = *(++pusReqSequence);
            } else {
                giRequestType = -1;
            }
        } else if (giRequestType == API_GET_APPLIST) {
            giApplIdx = 0;
            giRequestType = *(++pusReqSequence);
        } else if (giRequestType == API_GET_FUNCLIST) {
            if (++giApplIdx < usAppListCnt) {
                // ApplId = pstAppList[giApplIdx].usApplId;
                // 1175 55 3590 125 1070 1400 4582 2470 7050
            } else {
                giRequestType = *(++pusReqSequence);
            }
        } else if (giRequestType == API_BANK_EFTTOTALS) {
            /*
                                            if(st_TrxnRespData.ucResult == '0') {
                                                    if(st_TrxnRespData.usTrxnBatchNo != tPOSUtilBuf.usBatchNo) {
                                                            // �ܸ����� Batch Number�� ���� Batch Number�� Ʋ���� ���� ������ ����, Sequence Number�� �ʱ�ȭ
                                                            tPOSUtilBuf.usBatchNo = st_TrxnRespData.usTrxnBatchNo;
                                                            tPOSUtilBuf.usSeqNo = 0;
                                                            SavePOSUtilBuf();
                                                            // Batch Printing��? - Request/Response Data�� �̿��ؼ� Printing
                                                            EraseAllTransactionLog();
                                                    }
                                            }
             */
            giRequestType = *(++pusReqSequence);
        } else if (giRequestType == API_BANK_EFTTRAN) {
            /*				if(st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY || st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
                                                    SaveRxTransactionLog();
                                            }
             */ if (st_TrxnRespData.ucResult != '1') {
                giRequestType = -1;
            } else {
                giRequestType = *(++pusReqSequence);
            }
        } else {
            giRequestType = *(++pusReqSequence);
        }
        memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
        iRxCnt = 0;
        if (giRequestType < 0) {
            OnlineTrxnResultProcessing();
            /*
                                            // ������� - Communication completed
                                            ModemClose();
                                            pusServiceAddr++;
                                            sVirtualKey = BTKEY_ENTER;
                                            // usGprsTaskStep = 206;
             */ //		break;
        } else {
            ucReqDataReadyFlag = 1;
            usGprsTaskStep = 205;
        }

#endif













        return;
    }

    if (RS232_CheckRxInput(GPRS_COM_PORT) == 0) {
        return;
    }

    rxdata = RS232_Read(GPRS_COM_PORT) & 0xFF;
#ifdef USER_DEBUG
    if ((giTransactionType == TRXN_BANK_EFTTRAN) || (giTransactionType == TRXN_BANK_EFTTOTAL)) {
        Rprintf("%c", (unsigned char) rxdata);
    }
#endif
    // Check disconnection
    if (GprsCheckDisconnect(rxdata)) {
#ifdef USER_DEBUG
        Rprintf("\r\nE>%d - NO CARRIER\r\n", usGprsTaskStep);
#endif

        if (ucReqDataReadyFlag || ucReqDataTxFlag) {
            // "No Carrier      ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1NoCarrierError_001], ucLangFlag);
        }

        usGprsTaskStep = 0;
        if (ucReqDataTxFlag) {
            AbnormalProcessingAfterTx();
        } else {
            ModemClose();
            usGprsTaskStep = 100; // Modem Reset & Check the modem connection counter is over maximum connection counter
        }
        return;
    }

    ucRxBuf[iRxCnt] = rxdata;
    iRxCnt++;
    iRxCnt &= 0x1FFF;

    if (ucGprsDLESetFlag == 0) {
        if (rxdata == DLE) {
            ucGprsDLESetFlag = 1;
        }
    } else {
        if (ucGprsGsmModel == WAVECOM_Q2686) {
            if (rxdata == ETX || rxdata == DLE) {
                ucRxBuf[iRxCnt - 2] = rxdata;
                ucRxBuf[iRxCnt - 1] = 0x00;
                iRxCnt--;
            }
        } else {
            if (rxdata == ETX) {
                ucRxBuf[iRxCnt - 2] = rxdata;
                ucRxBuf[iRxCnt - 1] = 0x00;
                iRxCnt--;
            }
        }
        ucGprsDLESetFlag = 0;
    }

    switch (usGprsTaskStep) {
        case 200:
            usGprsTaskStep++;
            break;
        case 201: // Wait for Tx
            iRxCnt = 0;
            usGprsTaskStep++;
            break;

        case 202: // Receiving HTTP Response Code
            if (iRxCnt >= 2 && !memcmp(&ucRxBuf[iRxCnt - 2], "\x0D\x0A", 2)) {
                //Rprintf("Receiving HTTP Response Code\r\n");
                char *ptr;
                ucRxBuf[iRxCnt] = 0x00;
                if (ptr = strstr(&ucRxBuf[0], "HTTP/")) { // ex) HTTP/1.1 200 OK
                    if (ptr[9] != '2') { // 2xx : CODE FOR SUCCESS
                        memcpy(temp[0], &ptr[9], 3);
                        temp[0][3] = 0x00;
                        ptr[iRxCnt - 2] = 0x00;
                        strcpy(temp[1], &ptr[13]);
                        LCD_ClearScreen();
                        LCD_DisplayString(0, 0, strlen(&ptr[13]), &ptr[13], ucLangFlag);
                        LCD_DisplayLine(0, LEFT_JUSTIFIED, (char *) temp[0], ucLangFlag);
                        LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) temp[1], ucLangFlag);
                        if (strlen(temp[1]) > 16) {
                            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) &temp[1][16], ucLangFlag);
                            if (strlen(temp[1]) > 24)
                                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) &temp[1][24], ucLangFlag);
                        }
                        ModemClose();
                        // Ʈ�����(PURCHASE)�� ��� �α׿� ��ȿó��??? Reversal???
                        if (giTransactionType == TRXN_BANK_EFTTRAN) {
                            AbnormalProcessingAfterTx();
                        }
                        ucReqDataTxFlag = 0;
                        break;
                    }
                    memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
                    iRxCnt = 0;
                    // "RECEIVING DATA..",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReceivingData_0001], ucLangFlag);
                    usGprsTaskStep++;
                }
            }
            break;
        case 203: // Receiving HTTP Response Header
            if (iRxCnt >= 4 && !memcmp(&ucRxBuf[iRxCnt - 4], "\x0D\x0A\x0D\x0A", 4)) {
                //Rprintf("Receiving HTTP Response Header\r\n");

                {
                    int i, in, len;
                    char *ptr;
                    ptr = strstr(&ucRxBuf[0], "Content-Length:");
                    // null
                    for (i = in = len = 0; ptr[i] != 0x0D; i++) {
                        if (in == 0 && ptr[i] >= '0' && ptr[i] <= '9') {
                            in = 1;
                        }
                        if (in == 1) {
                            if (ptr[i] >= '0' && ptr[i] <= '9') {
                                len = len * 10 + ptr[i] - '0';
                            } else {
                                in = 0;
                                break;
                            }
                        }
                    }
                    giRespContentLength = len;
                }

                // End of HTTP Header
                memcpy(&ucHtmlHeader[0], &ucRxBuf[0], iRxCnt);
                // ProcessHttpHeader giRespContentLength
                memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
                iRxCnt = 0;
                usGprsTaskStep++;
                break;
            }
            break;
        case 204: // Receiving HTTP Response Body
            /*
            {
                    char temp[128];
                    sprintf(temp, "%d, %d", iRxCnt, giRespContentLength);
                    LCD_DisplayString(0, 0, strlen(temp), temp, ucLangFlag);
            }
             */
            if (iRxCnt < giRespContentLength)
                break;
            //Rprintf("Receiving HTTP Response Body\r\n");
            // �������� ó��
            ucReqDataTxFlag = 0;
            NIBSS_Parsing((char *) &ucRxBuf[0], iRxCnt, giRequestType, &gbTmpRespBuf);
            // Function List �� App������ŭ ����
            if (st_ErrRespData.iErrFlag == 1) {
                if (giRequestType == API_TAMS_NEWKEY) {
                    giRequestType = *(++pusReqSequence);
                } else {
                    giRequestType = -1;
                }
            } else if (giRequestType == API_GET_APPLIST) {
                giApplIdx = 0;
                giRequestType = *(++pusReqSequence);
            } else if (giRequestType == API_GET_FUNCLIST) {
                if (++giApplIdx < usAppListCnt) {
                    // ApplId = pstAppList[giApplIdx].usApplId;
                    // 1175 55 3590 125 1070 1400 4582 2470 7050
                } else {
                    giRequestType = *(++pusReqSequence);
                }
            } else if (giRequestType == API_BANK_EFTTOTALS) {
                giRequestType = *(++pusReqSequence);
            } else if (giRequestType == API_BANK_EFTTRAN) {
                if (st_TrxnRespData.ucResult != '1') {
                    giRequestType = -1;
                } else {
                    giRequestType = *(++pusReqSequence);
                }
            } else {
                giRequestType = *(++pusReqSequence);
            }
            memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
            iRxCnt = 0;
            if (giRequestType < 0) {
                OnlineTrxnResultProcessing();
                break;
            }
            ucReqDataReadyFlag = 1;
            usGprsTaskStep = 205;
            /*
                    // SEND ETX for disconnecting and reconnect to the server
                    RS232_Write(GPRS_COM_PORT, "\x03", 1);
                    usGprsTaskStep = 170;
             */
            break;
    }
}

/* Disconnect GPRS bearer */
void GprsDisconnect(int iMode) {
    if (sz17HWInfo[7] == 0x33) {
        GprsWavecomDisconnect(iMode);
    } else if (sz17HWInfo[7] == 0x37) {
        GprsCinterionDisconnect(iMode);
    }
}

/* Disconnect GSM */
void GprsWavecomDisconnect(int iMode) {
    int rxdata, escape_cnt;

#ifdef USER_DEBUG
    Rprintf("\r\n%d - GprsWavecomDisconnect()\r\n", usGprsTaskStep);
#endif
    if (!ucGprsPowerOnStatus) {
        usGprsTaskStep = 0;
        return;
    }
    usGprsTaskStep = (iMode == 0) ? 210 : 214;

#ifdef TEST_OFFLINE
    usGprsTaskStep = 216;
#endif

    escape_cnt = 0;
    while (1) {
        switch (usGprsTaskStep) {
            case 210: // Escape command
                // Note: An unsolicited event +WIPPEERCLOSE= 2,1 will be received once the TCP client is closed
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Escape\r\n", usGprsTaskStep);
#endif
                // guard time: 1 second
                TIMER_Wait1MS(1200);
                strcpy((char *) &ucTxBuf[0], "+++");
                GprsSendCmdSetTime(300);
                break;
            case 212: //  Delay for sending Close a socket command
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Delay for sending Close a socket command\r\n", usGprsTaskStep);
#endif
                usGprs10MSTimer = TIMER_Get10MSTimer();
                usGprs10MSMaxTimeout = 20;
                usGprsTaskStep++;
                break;
            case 214: // Disconnect command
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Disonnect\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+WIPCLOSE=2,1\r");
                GprsSendCmdSetTime(300);
                break;
            case 216: // Close GSM
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Close GPRS(%d)\r\n", usGprsTaskStep, ucGprsPowerOffFlag);
#endif
                if (ucGprsPowerOffFlag) {
                    GprsPowerOff();
                }
                usGprsTaskStep = 0;
                return;
        }

        if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= usGprs10MSMaxTimeout) {
#ifdef USER_DEBUG
            Rprintf("\r\n%d - Timeout\r\n", usGprsTaskStep);
#endif
            if (usGprsTaskStep == 211 && escape_cnt < GPRS_MAX_DISCONNECT_RETRY) {
                escape_cnt++;
                usGprsTaskStep--;
            } else {
                usGprsTaskStep++;
            }
            iRxCnt = 0;
            continue;
        }

        if (RS232_CheckRxInput(GPRS_COM_PORT) == 0) {
            continue;
        }

        rxdata = RS232_Read(GPRS_COM_PORT) & 0xFF;
#ifdef USER_DEBUG
        Rprintf("%c", (unsigned char) rxdata);
#endif
        ucRxBuf[iRxCnt] = rxdata;
        iRxCnt++;
        iRxCnt &= 0x1FFF;

        if (GprsCheckDisconnect(rxdata)) {
#ifdef USER_DEBUG
            Rprintf("\r\nE> %d - NO CARRIER\r\n", usGprsTaskStep);
#endif
            if (usGprsTaskStep == 211) {
                usGprsTaskStep++;
                iRxCnt = 0;
            }
        } else if (iRxCnt >= 2 && ucRxBuf[iRxCnt - 2] == '\r' && ucRxBuf[iRxCnt - 1] == '\n') {
            if (iRxCnt == 4 && !memcmp((char *) &ucRxBuf[0], "OK", 2)) {
                usGprsTaskStep++;
            } else if (iRxCnt >= 20 && !memcmp((char *) &ucRxBuf[0], "+WIPPEERCLOSE: ", 15)) {
                if (usGprsTaskStep == 211) {
                    usGprsTaskStep++;
                }
            }
            memset((char *) &ucRxBuf[0], 0, iRxCnt);
            iRxCnt = 0;
        }
    }
}

/* Disconnect GPRS Cinterion Module */
void GprsCinterionDisconnect(int iMode) {
    int rxdata, escape_cnt;

#ifdef USER_DEBUG
    Rprintf("\r\n%d - GprsDisconnect()\r\n", usGprsTaskStep);
#endif
    if (!ucGprsPowerOnStatus) {
        usGprsTaskStep = 0;
        return;
    }
    usGprsTaskStep = (iMode == 0) ? 210 : 214;

#ifdef TEST_OFFLINE
    usGprsTaskStep = 216;
#endif

    escape_cnt = 0;
    while (1) {
        switch (usGprsTaskStep) {
            case 210: // Escape command
                // Note: An unsolicited event +WIPPEERCLOSE= 2,1 will be received once the TCP client is closed
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Escape\r\n", usGprsTaskStep);
#endif
                // guard time: 1 second
                TIMER_Wait1MS(1200);
                strcpy((char *) &ucTxBuf[0], "+++");
                GprsSendCmdSetTime(300);
                break;
            case 212: //  Delay for sending Close a socket command
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Delay for sending Close a socket command\r\n", usGprsTaskStep);
#endif
                usGprs10MSTimer = TIMER_Get10MSTimer();
                usGprs10MSMaxTimeout = 20;
                usGprsTaskStep++;
                break;
            case 214: // Close a socket command -> OK or ERROR
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Close a socket\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT^SISC=0\r");
                GprsSendCmdSetTime(300);
                break;
            case 216: // Close GPRS
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Close GPRS\r\n", usGprsTaskStep);
#endif
                if (ucGprsPowerOffFlag) {
                    GprsPowerOff();
                }
                usGprsTaskStep = 0;
                return;
        }

        if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= usGprs10MSMaxTimeout) {
#ifdef USER_DEBUG
            Rprintf("\r\n%d - Timeout\r\n", usGprsTaskStep);
#endif
            if (usGprsTaskStep == 211 && escape_cnt < GPRS_MAX_DISCONNECT_RETRY) {
                escape_cnt++;
                usGprsTaskStep--;
            } else {
                usGprsTaskStep++;
            }
            iRxCnt = 0;
            continue;
        }

        if (RS232_CheckRxInput(GPRS_COM_PORT) == 0) {
            continue;
        }

        rxdata = RS232_Read(GPRS_COM_PORT) & 0xFF;
#ifdef USER_DEBUG
        Rprintf("%c", (unsigned char) rxdata);
#endif
        ucRxBuf[iRxCnt] = rxdata;
        iRxCnt++;
        iRxCnt &= 0x1FFF;

        if (GprsCheckDisconnect(rxdata)) {
#ifdef USER_DEBUG
            Rprintf("\r\nE> %d - NO CARRIER\r\n", usGprsTaskStep);
#endif
            if (usGprsTaskStep == 211) {
                usGprsTaskStep++;
                iRxCnt = 0;
            }
        } else if (iRxCnt >= 2 && ucRxBuf[iRxCnt - 2] == '\r' && ucRxBuf[iRxCnt - 1] == '\n') {
            if (iRxCnt == 4 && !memcmp((char *) &ucRxBuf[0], "OK", 2)) {
                usGprsTaskStep++;
            } else if (iRxCnt >= 15 && !memcmp((char *) &ucRxBuf[0], "+CME ERROR: ", 12)) {
                if (usGprsTaskStep == 211) {
                    usGprsTaskStep++;
                }
            }
            memset((char *) &ucRxBuf[0], 0, iRxCnt);
            iRxCnt = 0;
        }
    }
}

/* Initialize GPRS module */
void GprsModuleInitialize(void) {
    int i, ret;

#ifdef USER_DEBUG
    Rprintf("\r\nInitialize GSM\r\n");
#endif
    // "   Initialize   ", "   GSM module   ", "                ", " Please Wait... "
    LCDDisplay4Lines(M4GSMCheckMsg_000001, -1, ucLangFlag);
    GprsPowerOff();
    GprsPowerOn(0);
    if (sz17HWInfo[7] == 0x33) {
        ret = GprsWavecomInitialization(2);
    } else if (sz17HWInfo[7] == 0x37) {
        ret = GprsCinterionInitialization(2);
    } else {
        ret = -3;
    }
#ifdef USER_DEBUG
    Rprintf("\r\nret = %d\r\n", ret);
#endif
    if (ret == 0) {
        ucGprsModuleOkFlag = 1;
        Beep_EventSound(OK_TONE);
        TIMER_Wait1MS(500);
    } else {
        ucGprsModuleOkFlag = 0;
#ifdef USER_DEBUG
        Rprintf("\r\nE>GSM module doesn't response\r\n");
#endif
        LCD_ClearScreen();
        // "????????????????", "   GSM module   ", "doesn't response", "                "
        LCDDisplay4Lines(M4GSMNoResponse_0001, -1, ucLangFlag);
        GprsPowerOff();
        for (i = 0; i < 3; i++) {
            Beep_EventSound(ERROR_TONE);
            TIMER_Wait1MS(2000);
        }
        TIMER_WaitKeyPress1MS(5000);
    }

    ucGprsSIMCheckedFlag = 0;
    ucGprsSIMStatus = SIM_CHECK;
    ucGprsRssiValue = 99;
    ucGprsBerValue = 99;
    ucGprsRssiRetryCnt = 0;
    ucGprsRegistrationStatus = 0;
    ucGprsRegistrationRetryCnt = 0;

    memset((char *) &ucTxBuf[0], 0x00, sizeof (ucTxBuf));
    memset((char *) &ucRxBuf[0], 0x00, sizeof (ucRxBuf));
    iRxCnt = 0;

    usGprsTaskStep = 0;
    ucGprsCmdRetryCnt = 0;

    // Get LCD backlight on start time
    usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();
    usAutoInitial10MSTimer = TIMER_Get10MSTimer();
}

/* */












void GprsCinterionTask(void) {
    int i, j, k, rxdata, error_code, ret, max_line;
    unsigned char crc;
    char temp[3][256];
#ifdef USER_DEBUG
    static U16 usPrevGprsTaskStep = -1;
#endif
    if (stpFlashPOSSetupInfo->ucComDevice != GSM_MODEM) {
        return;
    }

    if (ucTMSDownloadFlag && usGprsTaskStep >= 200) {
        return;
    }

#ifdef USER_DEBUG
    if (usGprsTaskStep != usPrevGprsTaskStep) {
        if (usGprsTaskStep < 60 || usGprsTaskStep >= 70) {
            Rprintf("\r\nusGprsTaskStep = %d\r\n", usGprsTaskStep);
        }
        usPrevGprsTaskStep = usGprsTaskStep;
    }
#endif

    // AT Command Mode
    if (usGprsTaskStep < 200) {
        switch (usGprsTaskStep) {
            case 0: // Initial status
#ifdef USER_DEBUG
                //				Rprintf("\r\nInitial Status\r\n");
#endif
                if (ucGprsModuleOkFlag) {
                    if (ucGprsSIMStatus == SIM_CHECK || ucGprsSIMStatus == SIM_READY) {
#ifdef USER_DEBUG
                        //						Rprintf("Open GSM RS232 Port\r\n");
#endif
                        RS232_OpenPort(GPRS_COM_PORT, BPS115200, NONE8BIT, STOP1BIT, 0);

                        memset((char *) &ucTxBuf[0], 0x00, sizeof (ucTxBuf));
                        memset((char *) &ucRxBuf[0], 0x00, sizeof (ucRxBuf));
                        iRxCnt = 0;

                        ucGprsCmdRetryCnt = 0;
                        usGprsTaskStep = 1; // Delay for sending First Echo off command (within 4 seconds after reset)
                    }
                }
                return;
            case 3: // First Echo off command (within 4 seconds after reset)
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Echo off\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "ATE0\r");
                GprsSendCmdSetTime(50);
                break;
            case 5:
                ucGprsCmdRetryCnt = 0;
                if (ucGprsSIMCheckedFlag == 0) {
                    usGprsTaskStep = 10; // Delay for sending Read the SIM status command (within 6 seconds after reset)
                } else {
                    usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                }
                return;

            case 12: // Read the SIM status command (within 6 seconds after reset)
                // Command
                // AT+CPIN?
                //
                // Response
                // +CPIN: <rssi>,<ber>
                //
                // OK
                //
                // +CPIN: READY				- ME is not pending for any password
                // +CPIN: SIM PIN			- CHV1 is required
                // +CPIN: SIM PUK			- PUK1 is required
                // +CPIN: SIM PIN2			- CHV2 is required
                // +CPIN: SIM PUK2			- PUK2 is required
                // +CPIN: PH-SIM PIN		- SIM lock (phone-to-SIM) is required
                // +CPIN: PH-NET PIN		- network personalization is required
                // +CPIN: PH-NETSUB PIN		- network subset is required
                // +CPIN: PH-SERVPROV PIN	- service provider is required
                // +CPIN: PH-CORPORATE PIN	- corporate is required
                //
                // +CME ERROR: <err>	- SIM failure (13) absent (10) etc��
                // +CME ERROR: 10 (SIM not inserted)
                // +CME ERROR: 13 (SIM failure)
                // +CME ERROR: 515 (Please wait, init or command processing in progress)
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Read the SIM status\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CPIN?\r");
                GprsSendCmdSetTime(300);
                break;
            case 16: // Enter PIN command
                // +CME ERROR: 3 (Operation not allowed, PIN previously entered)
                // Enter PUK and new PIN command
                // ex) AT+CPIN=00000000,1234
                // +CME ERROR: 16 (Incorrect PUK)
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Enter PIN\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CPIN=5273\r");
                GprsSendCmdSetTime(600);
                break;
            case 20: // Read selected an operator command
                // Command
                // AT+COPS?
                //
                // Response
                // +COPS: <mode>[,<format>,<oper>]
                //
                // OK
                //
                // <mode>: network registration mode
                // 0: automatic (default value)
                // 1: manual
                // 2: deregistration; ME will be unregistered until <mode>=0 or 1
                //    is selected
                // 3: set only <format> (for read command AT+COPS?)
                // 4: manual/automatic (<oper> shall be present), if manual
                //    selection fails, automatic mode is entered.
                //
                // <format>: format of <oper> field
                // 0: long alphanumeric format <oper>
                // 1: short alphanumeric format <oper>
                // 2: numeric <oper> (default value)
                //
                // <stat>: status of <oper> field
                // 0: unknown
                // 1: available
                // 2: current
                // 3: forbidden
                //
                // <oper>: operator identifier (MCC/MNC in numeric format only for
                //         operator selection)
                // The long alphanumeric format can be up to 16 characters long
                // (for operator names description see "Operator names" section
                // in the present document "Appendixes"; field is "Name").
                // The short alphanumeric format can be up to 10 characters long.
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Read selected an operator command\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+COPS?\r");
                GprsSendCmdSetTime(300);
                break;
            case 24: // Set network registration mode command
                // Command
                // AT+COPS=<mode>[,<format>[,<oper>]]
                //
                // Response
                // OK
                //
                // <mode>: network registration mode
                // 0: automatic (default value)
                // 1: manual
                // 2: deregistration; ME will be unregistered until <mode>=0 or 1
                //    is selected
                // 3: set only <format> (for read command AT+COPS?)
                // 4: manual/automatic (<oper> shall be present), if manual
                //    selection fails, automatic mode is entered.
                //
                // <format>: format of <oper> field
                // 0: long alphanumeric format <oper>
                // 1: short alphanumeric format <oper>
                // 2: numeric <oper> (default value)
                //
                // <stat>: status of <oper> field
                // 0: unknown
                // 1: available
                // 2: current
                // 3: forbidden
                //
                // <oper>: operator identifier (MCC/MNC in numeric format only for
                //         operator selection)
                // The long alphanumeric format can be up to 16 characters long
                // (for operator names description see "Operator names" section
                // in the present document "Appendixes"; field is "Name").
                // The short alphanumeric format can be up to 10 characters long.
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set network registration mode command\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+COPS=0\r");
                GprsSendCmdSetTime(300);
                break;

            case 62: // Check Signal Quality command
                // Command
                // AT+CSQ
                //
                // Response
                // +CSQ: <rssi>,<ber>
                //
                // OK
                //
                // * the received signal strength indication (<rssi>) and the channel bit error rate (<ber>)
                //
                // <rssi>:
                // 0		-113dBm or less
                // 1		-111dBm
                // 2 to 30	-109 to -53dBm / 2dBm per step
                // 		 2: -109dBm,  3: -107dBm,  4: -105dBm,  5: -103dBm,  6: -101dBm,
                // 		 7:  -99dBm,  8:  -97dBm,  9:  -95dBm, 10:  -93dBm, 11:  -91dBm,
                // 		12:  -89dBm, 13:  -87dBm, 14:  -85dBm, 15:  -83dBm, 16:  -81dBm,
                // 		17:  -79dBm, 18:  -77dBm, 19:  -75dBm, 20:  -73dBm, 21:  -71dBm, 
                // 		22:  -69dBm, 23:  -67dBm, 24:  -65dBm, 25:  -63dBm, 26:  -61dBm,
                // 		27:  -59dBm, 28:  -57dBm, 29:  -55dBm, 30:  -53dBm
                // 31		-51dBm or greater
                // 99		not known or not detectable
                //
                // <ber>:
                // 0��7		as RXQUAL values in the table GSM 05.08
                //  0		less than 0.2%
                //  1		0.2% to 0.4%
                //  2		0.4% to 0.8%
                //  3		0.8% to 1.6%
                //  4		1.6% to 3.2%
                //  5		3.2% to 6.4%
                //  6		6.4% to 12.8%
                //  7		more than 12.8%
                // 99		not known or not detectable
#ifdef USER_DEBUG
                //				Rprintf("\r\n%d - Check Signal Quality\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CSQ\r");
                GprsSendCmdSetTime(300);
                break;
            case 66: // Check the registration status command
                // Command
                // AT+CREG?
                //
                // Response
                // +CREG: <mode>,<status>[,<lac>,<cid>]
                //
                // OK
                //
                // <mode>: request operation
                // 0: disable network registration unsolicited result code (default value)
                // 1: enable network registration code result code +CREG: <stat>
                // 2: enable network registration and location information unsolicited result code
                //    +CREG: <stat>,<lac>,<ci> if there is a change of network cell
                //
                // <stat>: network registration state
                // 0: not registered, ME is not currently searching for a new operator
                // 1: registered, home network
                // 2: not registered, ME currently searching for a new operator
                // 3: registration denied
                // 4: unknown
                // 5: registered, roaming
                //
                // <lac>: location area code
                // string type; two byte location area code in hexadecimal format
                // (e.g. "00C3" equals 195 in decimal)
                //
                // <ci>: cell ID
                // string type ; two byte cell ID in hexadecimal format
                //
                // <rejectCause>: network registration denied cause
                // 0: Illegal MS
                // 1: Illegal ME
                // 2: IMSI Unknown
                // 3: Bad network authentication
#ifdef USER_DEBUG
                //				Rprintf("\r\n%d - Check the registration status command\r\n", usGprsTaskStep);
#endif
                strcpy((char *) &ucTxBuf[0], "AT+CREG?\r");
                GprsSendCmdSetTime(300);
                break;

            case 72: // Set GPRS connection to Internet Connection Setup Profile
                // AT^SICS=<conProfileId>, <conParmTag>, <conParmValue>
                //
                // <conProfileId>(num)
                // 0...5		Internet connection profile identifier.
                // 				The <conProfileId> identifies all parameters of a connection profile, and,
                // 				when a service profile is created with AT^SISS the <conProfileId> needs
                // 				to be set as "conId" value of the AT^SISS parameter <srvParmTag>.
                //
                // <conParmTag>(str)
                // "conType"	Type of Internet connection.
                // 				For supported values of <conParmValue> refer to <conParmValue-conType>.
                // Supported connection type values in <conParmValue> for <conParmTag> value "conType".
                // "CSD"		Circuit-switched data call.
                // "GPRS0"		GPRS connection.
                // 				Settings of GPRS related commands are not used, e.g. AT+CGDCONT. When a
                // 				service based on a GPRS connection profile is started after entering AT^SISO
                // 				BG2-W automatically tries to attach to the GPRS. Yet, the only exception is
                // 				AT+CGATT which can be used any time to detach from the GPRS and thus disconnect
                // 				the bearer opened with AT^SISO.
                // "none"		Clears the connection profile.
                strcpy(ucTxBuf, "AT^SICS=0,CONTYPE,GPRS0\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set GPRS connection to Internet Connection Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 76: // Set 8 bit ASCII Data Mode to Internet Connection Setup Profile
                // AT^SICS=<conProfileId>, <conParmTag>, <conParmValue>
                //
                // <conProfileId>(num)
                // 0...5		Internet connection profile identifier.
                // 				The <conProfileId> identifies all parameters of a connection profile, and,
                // 				when a service profile is created with AT^SISS the <conProfileId> needs
                // 				to be set as "conId" value of the AT^SISS parameter <srvParmTag>.
                //
                // <conParmTag>(str)
                // "alphabet"	Selects the character set for input and output of string parameters within a profile.
                // 				The selected value is bound to the specific profile. This means that different
                // 				profiles may use different alphabets. Unlike other parameters the alphabet can
                // 				be changed no matter whether the <conParmTag> value "conType" has been set.
                // 				For supported values of <conParmValue> refer to <conParmValuealphabet>.
                // Character set selectable with <conParmValue> for <conParmTag> value "alphabet".
                // ["0"]		Character set determined with AT+CSCS applies.
                // "1"			International Reference Alphabet (IRA, seven bit ASCII) applies.
                strcpy(ucTxBuf, "AT^SICS=0,ALPHABET,1\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set 8 bit ASCII Data Mode to Internet Connection Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 80: // Set Inactivity timeout value to Internet Connection Setup Profile
                // AT^SICS=<conProfileId>, <conParmTag>, <conParmValue>
                //
                // <conProfileId>(num)
                // 0...5		Internet connection profile identifier.
                // 				The <conProfileId> identifies all parameters of a connection profile, and,
                // 				when a service profile is created with AT^SISS the <conProfileId> needs
                // 				to be set as "conId" value of the AT^SISS parameter <srvParmTag>.
                //
                // <conParmTag>(str)
                // "inactTO"	Inactivity timeout value in seconds: 0 ... 2^16-1, default = 20
                // 				Number of seconds the bearer remains open although the service no longer
                // 				needs the bearer connection.
                // 				Do not set the timeout value below 3 sec. This may result in problems when
                // 				using the <eodFlag> (set in the last AT^SISW command to terminate an
                // 				upload data stream).
                strcpy(ucTxBuf, "AT^SICS=0,INACTTO,65535\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set Inactivity timeout value to Internet Connection Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 84: // Set Access Point Name(APN) to Internet Connection Setup Profile (maximum 100 characters)
                // AT^SICS=<conProfileId>, <conParmTag>, <conParmValue>
                //
                // <conProfileId>(num)
                // 0...5		Internet connection profile identifier.
                // 				The <conProfileId> identifies all parameters of a connection profile, and,
                // 				when a service profile is created with AT^SISS the <conProfileId> needs
                // 				to be set as "conId" value of the AT^SISS parameter <srvParmTag>.
                //
                // <conParmTag>(str)
                // "apn"		Access point name string value: maximum 100 characters (where "" is default).
                if (strlen(st_POSSetupInfo.sz33GprsAPN[st_POSSetupInfo.ucGprsSIMNo])) {
                    sprintf(ucTxBuf, "AT^SICS=0,APN,\"%s\"\r", st_POSSetupInfo.sz33GprsAPN[st_POSSetupInfo.ucGprsSIMNo]);
                } else {
                    strcpy(ucTxBuf, "AT^SICS=0,APN,\"\"\r");
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set Access Point Name(APN) to Internet Connection Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 88: // Set User Name to Internet Connection Setup Profile (maximum 32 characters)
                // AT^SICS=<conProfileId>, <conParmTag>, <conParmValue>
                //
                // <conProfileId>(num)
                // 0...5		Internet connection profile identifier.
                // 				The <conProfileId> identifies all parameters of a connection profile, and,
                // 				when a service profile is created with AT^SISS the <conProfileId> needs
                // 				to be set as "conId" value of the AT^SISS parameter <srvParmTag>.
                //
                // <conParmTag>(str)
                // "user"		User name string: maximum 32 characters (where "" is default).
                if (strlen(st_POSSetupInfo.sz33GprsUserName[st_POSSetupInfo.ucGprsSIMNo])) {
                    sprintf(ucTxBuf, "AT^SICS=0,USER,\"%s\"\r", st_POSSetupInfo.sz33GprsUserName[st_POSSetupInfo.ucGprsSIMNo]);
                } else {
                    strcpy(ucTxBuf, "AT^SICS=0,USER,\"\"\r");
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set User Name to Internet Connection Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 92: // Set Password to Internet Connection Setup Profile (maximum 32 characters)
                // AT^SICS=<conProfileId>, <conParmTag>, <conParmValue>
                //
                // <conProfileId>(num)
                // 0...5		Internet connection profile identifier.
                // 				The <conProfileId> identifies all parameters of a connection profile, and,
                // 				when a service profile is created with AT^SISS the <conProfileId> needs
                // 				to be set as "conId" value of the AT^SISS parameter <srvParmTag>.
                //
                // <conParmTag>(str)
                // "passwd"		Password string: maximum 32 characters (where ***** is default).
                if (strlen(st_POSSetupInfo.sz33GprsPassword[st_POSSetupInfo.ucGprsSIMNo])) {
                    sprintf(ucTxBuf, "AT^SICS=0,PASSWD,\"%s\"\r", st_POSSetupInfo.sz33GprsPassword[st_POSSetupInfo.ucGprsSIMNo]);
                } else {
                    strcpy(ucTxBuf, "AT^SICS=0,PASSWD,\"\"\r");
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set Password to Internet Connection Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 96: // Set Transparent Mode to Internet Service Setup Profile
                // AT^SISS=<srvProfileId>, <srvParmTag>, <srvParmValue>
                //
                // <srvProfileId>(num)
                // 0...9		Internet service profile identifier.
                // 				The <srvProfileId> is used to reference all parameters related to the same service profile. Furthermore,
                // 				when using the AT commands AT^SISO, AT^SISR, AT^SISW, AT^SIST and AT^SISC the <srvProfileId>
                // 				is needed to select a specific service profile.
                //
                // <srvParmTag>(str)
                // srvType		Type of Internet service to be configured with consecutive usage of AT^SISS.
                // 				For supported values of <srvParmValue> refer to <srvParmValue-srvType>.
                // Supported Internet service type values in <srvParmValue> for <srvParmTag> value "srvType".
                // Before changing the "srvType" of an existing service profile be sure that the profile is closed. To verify the connection
                // state of the service profile enter the read command AT^SISI. Only when <srvState>=2 is returned
                // for this specific service profile you can change its service type.
                // "Socket"			BG2-W acting as client or server (listener) for TCP or UDP.
                // 					If BG2-W is TCP listener at least two service profiles are required. The first
                // 					socket profile must be configured as listener. The second service profile will be
                // 					dynamically assigned when a socket connection request from a remote client
                // 					is incoming. For this purpose, one service profile must be left free (= not configured
                // 					with AT^SISS). An incoming socket connection request will be indicated
                // 					by the "^SIS" URC, with the next free <srvProfileId> shown inside
                // 					the URC as parameter <urcInfoId>. The connection request can be
                // 					accepted or rejected by using the commands AT^SISO or AT^SISC and the ID
                // 					retrieved from the "^SIS".
                // "Transparent"	BG2-W acting as Transparent TCP socket client.
                // "Ftp"			BG2-W acting as FTP client.
                // "none"			Reset Internet service profile settings. Operation is not allowed if profile is in
                // 					use, i.e. it was activated via AT^SISO.
                strcpy(ucTxBuf, "AT^SISS=0,SRVTYPE,TRANSPARENT\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set Transparent Mode to Internet Service Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 100: // Set 8 bit ASCII Data Mode to Internet Service Setup Profile
                // AT^SISS=<srvProfileId>, <srvParmTag>, <srvParmValue>
                //
                // <srvProfileId>(num)
                // 0...9		Internet service profile identifier.
                // 				The <srvProfileId> is used to reference all parameters related to the same service profile. Furthermore,
                // 				when using the AT commands AT^SISO, AT^SISR, AT^SISW, AT^SIST and AT^SISC the <srvProfileId>
                // 				is needed to select a specific service profile.
                //
                // <srvParmTag>(str)
                // alphabet		Selects the character set for input and output of string parameters within a profile.
                // 				The selected value is bound to the specific profile. This means that different
                // 				profiles may use different alphabets. Unlike other parameters the alphabet can
                // 				be changed no matter whether the <srvParmTag> value "srvType" has been set.
                // 				For supported values of <srvParmValue> refer to <srvParmValuealphabet>.
                // Supported string parameter character set selections in <srvParmValue> for <srvParmTag> value "alphabet".
                // ["0"]		Applicable character set is determined by current setting of AT+CSCS.
                // "1"			International Reference Alphabet (IRA, seven bit ASCII).
                strcpy(ucTxBuf, "AT^SISS=0,ALPHABET,1\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set 8 bit ASCII Data Mode to Internet Service Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 104: // Set Internet connection profile to be used to Internet Service Setup Profile
                // AT^SISS=<srvProfileId>, <srvParmTag>, <srvParmValue>
                //
                // <srvProfileId>(num)
                // 0...9		Internet service profile identifier.
                // 				The <srvProfileId> is used to reference all parameters related to the same service profile. Furthermore,
                // 				when using the AT commands AT^SISO, AT^SISR, AT^SISW, AT^SIST and AT^SISC the <srvProfileId>
                // 				is needed to select a specific service profile.
                //
                // <srvParmTag>(str)
                // conId		Internet connection profile to be used, for details refer AT^SICS.
                strcpy(ucTxBuf, "AT^SISS=0,CONID,0\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set Internet connection profile to be used to Internet Service Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;

            case 162: // Checking Connection Profile Status
                // AT^SICI=<conProfileId>
                // Response(s)?
                // ^SICI: <conProfileId>,<conState>,<numServices>,<conAddr>
                // OK
                // ERROR
                // +CME ERROR: <err>
                //
                // <conProfileId>(num)
                // 0 ... 5		Internet connection profile identifier as defined by AT^SICS (<conProfileId>).
                //
                // <conState>(num)
                // State of the Internet connection profile.
                // 0			Down - Internet connection is defined but not connected.
                // 1			Connecting - A service has been opened and so the Internet connection is initated.
                // 2			Up - Internet connection is established and usable by one or more services.
                // 3			Limited Up - Internet connection is established, but temporarily no network coverage.
                // 				This state applies only to GPRS profiles (it does not occur with CSD).
                // 4			Closing - Internet connection is terminating.
                //
                // <numServices>(num)
                // 0 ... 9		Number of services using this Internet connection profile.
                //
                // <conAddr>(str)
                // Local IP address of the Internet connection profile (empty if no address is associated yet).
                //
                // Notes
                // - Before opening a service profile based on a connection profile recently used, check with AT^SICI that the
                //   previous connection was properly closed. If AT^SICI confirms that the connection profile is in <conState>
                //   0 (Down) the connection profile may be used again.
                // - If AT^SICI is used simultaneously on different instances only one request can be handled at a time. On the
                //   other instance(s) "+CME ERROR: operation temporary not allowed" will be displayed. If so, repeat the command
                //   on this instance.
                // - After closing the last service which uses this connection profile, parameter value <numServices> is
                //   decreased after the expiry of the inactivity timeout "inactTO" of AT^SICS only.
                ucGprsNetworkConnectionStatus = 5;
                sprintf(ucTxBuf, "AT^SICI=0\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Checking Connection Profile Status\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 166: // Set the URL to Internet Service Setup Profile
                // AT^SISS=<srvProfileId>, <srvParmTag>, <srvParmValue>
                //
                // <srvProfileId>(num)
                // 0...9		Internet service profile identifier.
                // 				The <srvProfileId> is used to reference all parameters related to the same service profile. Furthermore,
                // 				when using the AT commands AT^SISO, AT^SISR, AT^SISW, AT^SIST and AT^SISC the <srvProfileId>
                // 				is needed to select a specific service profile.
                //
                // <srvParmTag>(str)
                // address		String value containing the URL for the specific service:
                // 				1. Socket
                // 				   - Socket type TCP client URL
                // 				     "socktcp://'host':'remote tcpPort'
                // 				   - Socket type TCP server URL
                // 				     "socktcp://listener:'local tcpPort' "
                // 				   - Socket type UDP client URL
                // 				     "sockudp://'host':'remote udpPort'[;size='byte'][;port='word']"
                // 				     Parameter "size" (optional):
                // 				     0: PDU size is variable (default).
                // 				     1 ... 1460: Fixed PDU size in bytes.
                // 				     Parameter "port" (optional):
                // 				     0: Port number will be assigned from service (default).
                // 				     1 ... 216-1: defines the local port number for the UDP client.
                // 				2. Transparent
                // 				   "'host':'remote TcpPort'[;timer=100][;etx=<etxChar>]"
                // 				   Parameter "timer" (optional): 20 ... 500 milliseconds in steps of 20. Default
                // 				   if parameter is not specified: 100ms. The parameter configures the Nagle
                // 				   algorithm, which is used in transparent access mode.
                // 				   Parameter "etx" (optional): Specifies the character used to change from
                // 				   transparent access mode to AT command mode.
                // 				   Range of <etxChar>: 1 ...15, 17 ... 255. 16 is not allowed because defined
                // 				   as DLE (0x10).
                // 				   If value is not set no escaping is configured, thus requiring either +++ or
                // 				   DTR ON-OFF transition for changing to AT command mode. If value is set,
                // 				   the transmitted bytes are parsed for the DLE (0x10) character followed by
                // 				   the specified <etxChar> value. If both characters are found the service
                // 				   returns to AT command mode without transmitting these two bytes. This
                // 				   behavior differs from +++ handling, where +++ is transmitted over the air.
                // 				   If you wish to send DLE characters as normal text string within your payload
                // 				   data the characters shall be doubled (DLE DLE).
                // 				3. FTP
                // 				   - FTP client URL (get)
                // 				     "ftp://'user':'password'@'host':'tcpPort'/'url-path' [;type='a|i|d'] "
                // 				     Refer to "IETF-RFC 1738".
                // 				   - FTP client URL (put)
                // 				     "ftpput://'user':'password'@'host':'tcpPort'/'url-path'/'element name'
                // 				     [;type='a|i'][;mode='u|a|d'] "
                // 				   Used parameters:
                // 				   "host" is mandatory, all other parameters are optional.
                // 				   If "password" is set then "user" must be set as well.
                // 				   If "user" is omitted the string "anonymous" is selected for "user" and "password".
                // 				   If "password" is omitted the password request is served by an empty string.
                // 				   If "tcpPort" is omitted the service connects to the FTP default port 21.
                // 				   If "url-path" contains only the IP address a directory listing is requested.
                // 				   If "url-path" contains the IP address and has a slash '/' appended a detailed
                // 				   directory listing is requested.
                // 				   "type": [a)scii | i)mage | d)irectory]
                // 				   "mode": [u)nique | a)ppend | d)elete]
                // 				   "u)nique" selects the FTP Store Unique command to create a file name
                // 				   unique to the current directory. If the file name is assigned by the server
                // 				   then the "^SIS" URC will appear, indicating <urcInfoId> 2100 and the
                // 				   file name.
                // 				   "d)elete" clears given 'element name'.
                // 				   If "mode" is omitted "replace mode" is default setting.
                if (!ucTMSDownloadFlag) {
                    sprintf(ucTxBuf, "AT^SISS=0,ADDRESS,\"%s:%s\"\r", st_POSSetupInfo.sz16TrxnServerIP[0], st_POSSetupInfo.sz6TrxnServerPortNo[0]);
                } else {
                    sprintf(ucTxBuf, "AT^SISS=0,ADDRESS,\"%s:%s\"\r", st_POSSetupInfo.sz16TMSServerIP[0], st_POSSetupInfo.sz6TMSServerPortNo[0]);
                }
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Set the URL to Internet Service Setup Profile\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(300);
                break;
            case 170: // Internet Service Open
                // AT^SISO=<srvProfileId>
                // 0 ... 9		specified with AT^SISS.
                // Note: An unsolicited event ^SISW: 0, 1 will be received once the TCP client is ready for usage
                // +CME ERROR: 3 (Operation not allowed) - it must close this socket and open a socket again
                // +CME ERROR: 616 (network is down) - it must close this socket and open a socket again
                // ^SIS: 0, 0, 18, "For TCP/IP sockets, the socket is not connected"
                // ^SIS: 0, 0, 20, "Connection timed out"
                // ...
                sprintf(ucTxBuf, "AT^SISO=0\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Internet Service Open\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);

                lGprsTest1SecStartTimer = GetULDateTime();
#endif
                GprsSendCmdSetTime(9000);
                break;
            case 174: // Enter Transparent Access Mode
                // AT^SIST=<srvProfileId>
                // Response(s)
                // CONNECT
                // (indicates that ME has entered transparent access mode)
                // OK
                // ERROR
                // +CME ERROR: <err>
                strcpy(ucTxBuf, "AT^SIST=0\r");
#ifdef USER_DEBUG
                Rprintf("\r\n%d - Enter Transparent Access Mode\r\n", usGprsTaskStep);
                Rprintf("%s\n", ucTxBuf);
#endif
                GprsSendCmdSetTime(1200);
                //GprsSendCmdSetTime(6000);
                break;

            case 180: // Check the GPRS connection counter is over maximum connection counter
                ucGprsConnectCnt++;
                if (ucGprsConnectCnt < ucGprsMaxConnectCnt) {
                    usGprs10MSTimer = TIMER_Get10MSTimer();
                    usGprsTaskStep++;
                    if (ucTMSDownloadFlag) {
                        iTMS_ProcessStep = 2;
                    }
                } else {
                    usGprsTaskStep = 0;
                    ucGprsConnectCnt = 0;
                    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                        AbnormalProcessingBeforeTx();
                    }
                }
                return;
            case 181: // If reconnecting pause time is elapsed, retry to connect
                if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= GPRS_RECONNECTING_PAUSE_TIME) {
                    usGprsTaskStep++;
                }
                return;
            case 182: // Retry to connect
                usGprsTaskStep = 0;
                ucReqDataReadyFlag = 1;
                ModemOpen(NORMAL_CONNECTION);
                return;

            case 1: // Delay for sending First Echo off command (within 4 seconds after reset)
            case 10: // Delay for sending Read the SIM status command (within 6 seconds after reset)
            case 14: // Delay for sending Enter PIN command
            case 18: // Delay for sending Read selected an operator command
            case 22: // Delay for sending Set network registration mode command
            case 60: // Delay for sending Check Signal Quality command
            case 64: // Delay for sending Check the registration status command
            case 70: // Delay for sending Set GPRS connection to Internet Connection Setup Profile
            case 74: // Delay for sending Set 8 bit ASCII Data Mode to Internet Connection Setup Profile
            case 78: // Delay for sending Set Inactivity timeout value to Internet Connection Setup Profile
            case 82: // Delay for sending Set Access Point Name(APN) to Internet Connection Setup Profile
            case 86: // Delay for sending Set User Name to Internet Connection Setup Profile
            case 90: // Delay for sending Set Password to Internet Connection Setup Profile
            case 94: // Delay for sending Set Transparent Mode to Internet Service Setup Profile
            case 98: // Delay for sending Set 8 bit ASCII Data Mode to Internet Service Setup Profile
            case 102: // Delay for sending Set Internet connection profile to be used to Internet Service Setup Profile
            case 160: // Delay for sending Checking Connection Profile Status
            case 164: // Delay for sending Set the URL to Internet Service Setup Profile
            case 168: // Delay for sending Internet Service Open
            case 172: // Delay for sending Enter Transparent Access Mode
                switch (usGprsTaskStep) {
                    case 1: // Delay for sending First Echo off command (within 4 seconds after reset)
                        usGprs10MSMaxTimeout = 20;
                        break;
                    case 10: // Delay for sending Read the SIM status command (within 6 seconds after reset)
                    case 18: // Delay for sending Read selected an operator command
                    case 22: // Delay for sending Set network registration mode command
                    case 60: // Delay for sending Check Signal Quality command
                    case 64: // Delay for sending Check the registration status command
                    case 160: // Delay for sending Checking Connection Profile Status
                        usGprs10MSMaxTimeout = 50; // �����ð��� �ʹ� ������ SIM ���¸� ����� üũ���� ����
                        break;
                    default:
                        //usGprs10MSMaxTimeout = 10;
                        usGprs10MSMaxTimeout = 20;
                        break;
                }
                usGprs10MSTimer = TIMER_Get10MSTimer();
                usGprsTaskStep++;
                break;
        }

        if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= usGprs10MSMaxTimeout) {
            switch (usGprsTaskStep) {
                case 2: // Delay for sending First Echo off command (within 4 seconds after reset)
                case 11: // Delay for sending Read the SIM status command (within 6 seconds after reset)
                case 15: // Delay for sending Enter PIN command
                case 19: // Delay for sending Read selected an operator command
                case 23: // Delay for sending Set network registration mode command
                case 61: // Delay for sending Check Signal Quality command
                case 65: // Delay for sending Check the registration status command
                case 71: // Delay for sending Set GPRS connection to Internet Connection Setup Profile
                case 75: // Delay for sending Set 8 bit ASCII Data Mode to Internet Connection Setup Profile
                case 79: // Delay for sending Set Inactivity timeout value to Internet Connection Setup Profile
                case 83: // Delay for sending Set Access Point Name(APN) to Internet Connection Setup Profile
                case 87: // Delay for sending Set User Name to Internet Connection Setup Profile
                case 91: // Delay for sending Set Password to Internet Connection Setup Profile
                case 95: // Delay for sending Set Transparent Mode to Internet Service Setup Profile
                case 99: // Delay for sending Set 8 bit ASCII Data Mode to Internet Service Setup Profile
                case 103: // Delay for sending Set Internet connection profile to be used to Internet Service Setup Profile
                case 161: // Delay for sending Checking Connection Profile Status
                case 165: // Delay for sending Set the URL to Internet Service Setup Profile
                case 169: // Delay for sending Internet Service Open
                case 173: // Delay for sending Enter Transparent Access Mode
                    usGprsTaskStep++;
                    break;
                case 4: // Waiting for response of First Echo off command (within 4 seconds after reset)
#ifdef USER_DEBUG
                    Rprintf("\r\nE>%d - Timeout[%d]\r\n", usGprsTaskStep, ucGprsCmdRetryCnt);
#endif
                    // (200ms + 500ms) x 9 = 6.3 seconds
                    if (ucGprsCmdRetryCnt >= 8) {
                        ucGprsModuleOkFlag = 0;
                        ucGprsPowerOffFlag = 1;
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("\r\nE>%d - GSM module doesn't response\r\n", usGprsTaskStep);
#endif
                            // "????????????????", "   GSM module   ", "doesn't response", "                "
                            LCDDisplay4Lines(M4GSMNoResponse_0001, -1, ucLangFlag);
                            AbnormalProcessingBeforeTx();
                        } else {
                            ModemClose();
                        }
                    } else {
                        ucGprsCmdRetryCnt++;
                        usGprsTaskStep = 1; // Delay for sending First Echo off command (within 4 seconds after reset)
                    }
                    break;

                case 171: // Waiting for response of Internet Service Open
                case 175: // Waiting for response of Enter Transparent Access Mode
                    ModemClose();
                    usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                    break;
                default:
                    if (ucGprsCmdRetryCnt < GPRS_MAX_CMD_RETRY) {
                        ucGprsCmdRetryCnt++;
                        usGprsTaskStep -= 3;
                    } else {
                        usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                    }
                    break;
            }
            return;
        }

        if (RS232_CheckRxInput(GPRS_COM_PORT) == 0) {
            return;
        }

        rxdata = RS232_Read(GPRS_COM_PORT) & 0xFF;
#ifdef USER_DEBUG
        if (usGprsTaskStep != 63 && usGprsTaskStep != 67)
            Rprintf("%c", (unsigned char) rxdata);
#endif
        ucRxBuf[iRxCnt] = rxdata;
        iRxCnt++;
        iRxCnt &= 0x1FFF;

        if (iRxCnt >= 2 && ucRxBuf[iRxCnt - 2] == '\r' && ucRxBuf[iRxCnt - 1] == '\n') {
            if (iRxCnt == 4 && !memcmp((char *) &ucRxBuf[0], "OK", 2)) {
                ucGprsCmdRetryCnt = 0;
                switch (usGprsTaskStep) {
                    case 4: // Waiting for response of First Echo off command (within 4 seconds after reset)
                    case 73: // Waiting for response of Set GPRS connection to Internet Connection Setup Profile
                    case 77: // Waiting for response of Set 8 bit ASCII Data Mode to Internet Connection Setup Profile
                    case 81: // Waiting for response of Set Inactivity timeout value to Internet Connection Setup Profile
                    case 85: // Waiting for response of Set Access Point Name(APN) to Internet Connection Setup Profile (maximum 100 characters)
                    case 89: // Waiting for response of Set User Name to Internet Connection Setup Profile (maximum 32 characters)
                    case 93: // Waiting for response of Set Password to Internet Connection Setup Profile (maximum 32 characters)
                    case 97: // Waiting for response of Set Transparent Mode to Internet Service Setup Profile
                    case 101: // Waiting for response of Set 8 bit ASCII Data Mode to Internet Service Setup Profile
                        usGprsTaskStep++;
                        break;
                    case 17: // Waiting for response of Enter PIN command
                        ucGprsSIMStatus = SIM_READY;
                        usGprsTaskStep = 18; // Delay for sending Read selected an operator command
                        break;
                    case 21: // Waiting for response of Read selected an operator command
                        if (ucGsmNetworkRegistrationMode == 0) {
                            ucGprsSIMCheckedFlag = 1;
                            usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                        } else {
                            usGprsTaskStep++;
                        }
                        break;
                    case 25: // Waiting for response of Set network registration mode command
                        ucGprsSIMCheckedFlag = 1;
                        usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                        break;
                    case 63: // Waiting for response of Check Signal Quality command
                        if (*pusServiceAddr == 0x0000) {
                            // No signal
                            if (ucGprsRssiValue == 99) {
#ifdef USER_DEBUG
                                //Rprintf("\r\nucGprsRssiRetryCnt = %d\r\n", ucGprsRssiRetryCnt);
#endif
                                if (ucGprsRssiRetryCnt & 0x01) {
                                    GprsDisplayAntennaLevelBar(GPRS_ANTENNA_LEVEL_1_LIMIT);
                                } else {
                                    GprsDisplayAntennaLevelBar(ucGprsRssiValue);
                                }
                            } else {
                                GprsDisplayAntennaLevelBar(ucGprsRssiValue);
                            }
                        }

                        // No signal
                        if (ucGprsRssiValue == 99) {
                            // 500ms x 30 = 15 seconds
                            if (ucGprsRssiRetryCnt >= 29) {
#ifdef USER_DEBUG
                                //Rprintf("\r\n%d - No signal\r\n", usGprsTaskStep);
#endif
                                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                    // "????????????????", "No Signal       ", "                ", "                "
                                    LCDDisplay4Lines(M4NoSignal_000000001, -1, ucLangFlag);
                                    ucGprsRssiRetryCnt = 0;
                                    AbnormalProcessingBeforeTx();
                                } else {
                                    ucGprsRssiRetryCnt++;
                                    if (ucGprsRssiRetryCnt > 30) {
                                        ucGprsRssiRetryCnt = 29;
                                    }
                                    usGprsTaskStep -= 3;
                                }
                            } else {
                                ucGprsRssiRetryCnt++;
                                usGprsTaskStep -= 3;
                            }
                        } else {
                            ucGprsRssiRetryCnt = 0;
                            usGprsTaskStep++;
                            // Test for IC5100 GSM
                            //usGprsTaskStep = 60;	// Delay for sending Check Signal Quality command
                        }
                        break;
                    case 67: // Waiting for response of Check the registration status command
                        switch (ucGprsRegistrationStatus) {
                            case 1: // registered, home network
                            case 5: // registered, roaming
#ifdef USER_DEBUG
                                if (ucGprsRegistrationStatus == 1) {
                                    //									Rprintf("\r\n%d - registered, home network\r\n", usGprsTaskStep);
                                } else {
                                    Rprintf("\r\n%d - registered, roaming\r\n", usGprsTaskStep);
                                }
#endif
                                /* sispp 20111012 check point */
                                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                    if (ucGprsBearerOpenedFlag) {
                                        usGprsTaskStep = 160; // Delay for sending Create the TCP client socket with index 1 command
                                    } else {
                                        usGprsTaskStep = 70; // Delay for sending Start the Open AT�� embedded application command
                                    }
                                } else {
                                    if (*pusServiceAddr == 0x0000) {
                                        //LCD_DisplayString(0, 12, 4, " GSM", ucLangFlag);
                                        DisplaySimGprsIcon(-1, 1);
                                    }
                                    if (sz18GsmOperator[0] == 0x00) {
                                        usGprsTaskStep = 20;
                                    } else {
                                        usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                                    }
                                }

                                /*
                                                                                                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                                                                                        usGprsTaskStep = 70;	// Delay for sending Change the local serial port character framing used by the DCE command
                                                                                                }
                                                                                                else {
                                                                                                        if (*pusServiceAddr == 0x0000) {
                                                                                                                LCD_DisplayString(0, 12, 4, " GSM", ucLangFlag);
                                                                                                                DisplaySimGprsIcon(-1, 1);
                                                                                                        }
                                                                                                        usGprsTaskStep = 60;	// Delay for sending Check Signal Quality command
                                                                                                }
                                 */
                                ucGprsRegistrationRetryCnt = 0;
                                break;
                            case 0: // not registered, ME is not currently searching for a new operator
                            case 2: // not registered, ME currently searching for a new operator
                            case 3: // registration denied
                            case 4: // unknown
#ifdef USER_DEBUG
                                if (ucGprsRegistrationStatus == 0) {
                                    Rprintf("\r\nE>%d - not registered, ME is not currently searching for a new operator\r\n", usGprsTaskStep);
                                } else if (ucGprsRegistrationStatus == 2) {
                                    Rprintf("\r\nE>%d - not registered, ME currently searching for a new operator\r\n", usGprsTaskStep);
                                } else if (ucGprsRegistrationStatus == 3) {
                                    Rprintf("\r\nE>%d - registration denied\r\n", usGprsTaskStep);
                                } else {
                                    Rprintf("\r\nE>%d - unknown\r\n", usGprsTaskStep);
                                }
#endif
                                if (*pusServiceAddr == 0x0000) {
#ifdef USER_DEBUG
                                    Rprintf("\r\nucGprsRegistrationRetryCnt = %d\r\n", ucGprsRegistrationRetryCnt);
#endif
                                    if (ucGprsRegistrationRetryCnt & 0x01) {
                                        //LCD_DisplayString(0, 12, 4, " GSM", ucLangFlag);
                                        DisplaySimGprsIcon(-1, 1);
                                    } else {
                                        //LCD_DisplayString(0, 12, 4, "    ", ucLangFlag);
                                        DisplaySimGprsIcon(-1, 0);
                                    }
                                }

                                // 500ms x 30 = 15 seconds
                                if (ucGprsRegistrationRetryCnt >= 29) {
                                    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                                        if (ucGprsRegistrationStatus == 0 || ucGprsRegistrationStatus == 2) {
                                            // "????????????????", "is not          ", "registered      ", "                "
                                            LCDDisplay4Lines(M4NotRegistered_0001, -1, ucLangFlag);
                                        } else if (ucGprsRegistrationStatus == 3) {
                                            // "????????????????", "registration    ", "denied          ", "                "
                                            LCDDisplay4Lines(M4RegisterDenied_001, -1, ucLangFlag);
                                        } else {
                                            // "????????????????", "unknown network ", "status          ", "                "
                                            LCDDisplay4Lines(M4UnknownRegStatus_1, -1, ucLangFlag);
                                        }
                                        ucGprsRegistrationRetryCnt = 0;
                                        AbnormalProcessingBeforeTx();
                                    } else {
                                        ucGprsRegistrationRetryCnt++;
                                        if (ucGprsRegistrationRetryCnt > 30) {
                                            ucGprsRegistrationRetryCnt = 29;
                                        }
                                        usGprsTaskStep -= 3;
                                    }
                                } else {
                                    ucGprsRegistrationRetryCnt++;
                                    usGprsTaskStep -= 3;
                                }
                                break;
                        }
                        break;

                    case 105: // Waiting for response of Set Internet connection profile to be used to Internet Service Setup Profile
                        ucGprsBearerOpenedFlag = 1;
                        usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
#ifdef USER_DEBUG
                        lGprsTest1SecCheckTimer = GetULDateTime();
                        Rprintf("Elapsed time = %ld\r\n", lGprsTest1SecCheckTimer - lGprsTest1SecStartTimer);
#endif
                        break;
                    case 163: // Waiting for response of Checking Connection Profile Status
#ifdef USER_DEBUG
                        if (ucGprsNetworkConnectionStatus == 0) {
                            Rprintf("\r\n%d - Internet connection is defined but not connected.\r\n", usGprsTaskStep);
                        } else if (ucGprsNetworkConnectionStatus == 1) {
                            Rprintf("\r\n%d - A service has been opened and so the Internet connection is initated.\r\n", usGprsTaskStep);
                        } else if (ucGprsNetworkConnectionStatus == 2) {
                            Rprintf("\r\n%d - Internet connection is established and usable by one or more services.\r\n", usGprsTaskStep);
                        } else if (ucGprsNetworkConnectionStatus == 3) {
                            Rprintf("\r\n%d - Internet connection is established, but temporarily no network coverage.\r\n", usGprsTaskStep);
                        } else if (ucGprsNetworkConnectionStatus == 4) {
                            Rprintf("\r\n%d - Internet connection is terminating.\r\n", usGprsTaskStep);
                        } else {
                            Rprintf("\r\n%d - unknown\r\n", usGprsTaskStep);
                        }
#endif
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                            if (ucGprsNetworkConnectionStatus < 3) {
                                usGprsTaskStep = 164; // Delay for sending Set the URL to Internet Service Setup Profile
                            } else {
                                usGprsTaskStep = 160; // Delay for sending Checking Connection Profile Status
                            }
                        } else {
                            usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                        }
                        break;
                    case 167: // Waiting for response of Set the URL to Internet Service Setup Profile
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                            usGprsTaskStep++;
                        } else {
                            usGprsTaskStep = 60; // Delay for sending Check Signal Quality command
                        }
                        break;
                }
            } else if (iRxCnt >= 14 && !memcmp((char *) &ucRxBuf[0], "+CPIN: ", 7)) {
                // Waiting for response of Read the SIM status command (within 6 seconds after reset)
                if (usGprsTaskStep == 13) {
                    memset(temp, 0x00, sizeof (temp));
                    for (i = 7, j = 0; i < iRxCnt; i++) {
                        if (ucRxBuf[i] == '\r') {
                            break;
                        }
                        temp[0][j++] = ucRxBuf[i];
                    }

                    if (!strcmp(temp[0], "READY")) {
                        ucGprsSIMStatus = SIM_READY;
                    } else if (!strcmp(temp[0], "SIM PIN")) {
                        ucGprsSIMStatus = SIM_PIN;
                    } else if (!strcmp(temp[0], "SIM PUK")) {
                        ucGprsSIMStatus = SIM_PUK;
                    } else if (!strcmp(temp[0], "SIM PIN2")) {
                        ucGprsSIMStatus = SIM_PIN2;
                    } else if (!strcmp(temp[0], "SIM PUK2")) {
                        ucGprsSIMStatus = SIM_PUK2;
                    } else if (!strcmp(temp[0], "PH-SIM PIN")) {
                        ucGprsSIMStatus = PH_SIM_PIN;
                    } else if (!strcmp(temp[0], "PH-NET PIN")) {
                        ucGprsSIMStatus = PH_NET_PIN;
                    } else if (!strcmp(temp[0], "PH-NETSUB PIN")) {
                        ucGprsSIMStatus = PH_NET_SUB_PIN;
                    } else if (!strcmp(temp[0], "PH-SERVPROV PIN")) {
                        ucGprsSIMStatus = PH_SVC_PROVIDER_PIN;
                    } else if (!strcmp(temp[0], "PH-CORPORATE PIN")) {
                        ucGprsSIMStatus = PH_CORPORATE_PIN;
                    }

                    if (ucGprsSIMStatus == SIM_READY) {
                        ucGprsSIMCheckedFlag = 1;
                        ucGprsCmdRetryCnt = 0;
                        usGprsTaskStep = 18; // Delay for sending Read selected an operator command
                    } else {
                        ucGprsPowerOffFlag = 1;
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("SIM Error!!\r\n");
#endif
                            GprsDisplaySIMErrorMessage();
                            AbnormalProcessingBeforeTx();
                        } else {
                            ModemClose();
                        }
                    }
                }
            } else if (iRxCnt >= 11 && !memcmp((char *) &ucRxBuf[0], "+CSQ: ", 6)) {
                // Waiting for response of Check Signal Quality command
                if (usGprsTaskStep == 63) {
                    memset(temp, 0x00, sizeof (temp));
                    for (i = 6, j = 0, k = 0; i < iRxCnt; i++) {
                        if (ucRxBuf[i] == ',') {
                            k++;
                            if (k < 2) {
                                j = 0;
                                continue;
                            } else {
                                break;
                            }
                        } else if (ucRxBuf[i] == '\r') {
                            break;
                        }
                        temp[k][j++] = ucRxBuf[i];
                    }
#ifdef USER_DEBUG
                    if (ucGprsRssiValue != atoi(temp[0])) {
                        Rprintf("+CSQ: %d,%d\r\n", atoi(temp[0]), atoi(temp[1]));
                    }
#endif
                    ucGprsRssiValue = atoi(temp[0]);
                    ucGprsBerValue = atoi(temp[1]);
                }
            } else if (iRxCnt >= 12 && !memcmp((char *) &ucRxBuf[0], "+CREG: ", 7)) {
                // Waiting for response of Check the registration status command
                if (usGprsTaskStep == 67) {
                    memset(temp, 0x00, sizeof (temp));
                    temp[0][0] = ucRxBuf[9];
                    ucGprsRegistrationStatus = atoi(temp[0]);
                }
            } else if (iRxCnt >= 13 && !memcmp((char *) &ucRxBuf[0], "^SISW: ", 7)) {
                // AT^SISW=<srvProfileId>, <reqWriteLength>[, <eodFlag>[, <mode>]]
                // ^SISW: <srvProfileId>, <cnfWriteLength>, <unackData>
                //
                // Unsolicited Result Code
                // ^SISW: <srvProfileId>, <urcCauseId>
                //
                // <srvProfileId>(num)
                // 0 ... 9		specified with AT^SISS.
                //
                // <urcCauseId>(num)
                // 1			The service is ready to accept new user data.
                // 2			Data transfer has been finished successfully and Internet service may be
                //				closed without loss of data.
                // 
                // ^SISW: 0, 1 or ^SISW: 0, 0, 0
                //
                if (ucRxBuf[10] == '1') {
                    // Waiting for response of Internet Service Open
                    if (usGprsTaskStep == 171) {
                        usGprsTaskStep++;
#ifdef USER_DEBUG
                        lGprsTest1SecCheckTimer = GetULDateTime();
                        Rprintf("Elapsed time = %ld\r\n", lGprsTest1SecCheckTimer - lGprsTest1SecStartTimer);
#endif
                    }
                }
            } else if (iRxCnt >= 24 && !memcmp((char *) &ucRxBuf[0], "^SICI: ", 7)) {
                // AT^SICI=<conProfileId>
                // Response(s)?
                // ^SICI: <conProfileId>,<conState>,<numServices>,<conAddr>
                // OK
                // ERROR
                // +CME ERROR: <err>
                //
                // <conProfileId>(num)
                // 0 ... 5		Internet connection profile identifier as defined by AT^SICS (<conProfileId>).
                //
                // <conState>(num)
                // State of the Internet connection profile.
                // 0			Down - Internet connection is defined but not connected.
                // 1			Connecting - A service has been opened and so the Internet connection is initated.
                // 2			Up - Internet connection is established and usable by one or more services.
                // 3			Limited Up - Internet connection is established, but temporarily no network coverage.
                // 				This state applies only to GPRS profiles (it does not occur with CSD).
                // 4			Closing - Internet connection is terminating.
                //
                // <numServices>(num)
                // 0 ... 9		Number of services using this Internet connection profile.
                //
                // <conAddr>(str)
                // Local IP address of the Internet connection profile (empty if no address is associated yet).
                //
                // Notes
                // - Before opening a service profile based on a connection profile recently used, check with AT^SICI that the
                //   previous connection was properly closed. If AT^SICI confirms that the connection profile is in <conState>
                //   0 (Down) the connection profile may be used again.
                // - If AT^SICI is used simultaneously on different instances only one request can be handled at a time. On the
                //   other instance(s) "+CME ERROR: operation temporary not allowed" will be displayed. If so, repeat the command
                //   on this instance.
                // - After closing the last service which uses this connection profile, parameter value <numServices> is
                //   decreased after the expiry of the inactivity timeout "inactTO" of AT^SICS only.

                // Waiting for response of Checking Connection Profile Status
                if (usGprsTaskStep == 163) {
                    ucGprsNetworkConnectionStatus = ucRxBuf[9] - '0';
                }
            } else if (iRxCnt >= 9 && !memcmp((char *) &ucRxBuf[0], "CONNECT", 7)) {
                // Waiting for response of Read/write from/to a socket command
                if (usGprsTaskStep == 175) {
                    if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                        // " LINE CONNECTED ",
                        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1LineConnected_0001], ucLangFlag);
#ifdef USER_DEBUG
                        lGprsTest1SecCheckTimer = GetULDateTime();
                        Rprintf("Elapsed time = %ld\r\n", lGprsTest1SecCheckTimer - lGprsTest1SecStartTimer);
#endif
                    }

                    usGprs10MSMaxTimeout = (unsigned short) (st_POSSetupInfo.ucCommTimeout) * 100;
                    usGprs10MSTimer = TIMER_Get10MSTimer();
                    ucReqDataReadyFlag = 1;
                    usGprsTaskStep = 201; // Wait for data setup & Sending Data
                    if (iTMS_ProcessStep == 2) {
                        usTMSDownload10MSTimer = TIMER_Get10MSTimer();
                        iTMS_ProcessStep = 3;
                    }
                }
                iRxCnt = 0;
            } else if (iRxCnt >= 15 && !memcmp((char *) &ucRxBuf[0], "+CMS ERROR: ", 12)) {

            } else if (iRxCnt >= 15 && !memcmp((char *) &ucRxBuf[0], "+CME ERROR: ", 12)) {
                memset(temp, 0x00, sizeof (temp));
                for (i = 12, j = 0; i < iRxCnt; i++) {
                    if (ucRxBuf[i] == '\r') {
                        break;
                    }
                    temp[0][j++] = ucRxBuf[i];
                }
                error_code = atoi(temp[0]);

                ret = 0;
                switch (error_code) {
                    case 10: // SIM not inserted
                    case 13: // SIM failure
                    case 15: // SIM wrong
                    case 262: // SIM blocked
                        ucGprsSIMStatus = SIM_FAILURE;
                        ret = -1; // fatal error
                        break;
                    case 40: // Network personalization PIN required
                        ucGprsSIMStatus = PH_NET_PIN;
                        ret = -1; // fatal error
                        break;
                    case 41: // Network personalization PUK required
                        ucGprsSIMStatus = PH_NET_PUK;
                        ret = -1; // fatal error
                        break;
                    case 42: // Network subset personalization PIN required
                        ucGprsSIMStatus = PH_NET_SUB_PIN;
                        ret = -1; // fatal error
                        break;
                    case 43: // Network subset personalization PUK required
                        ucGprsSIMStatus = PH_NET_SUB_PUK;
                        ret = -1; // fatal error
                        break;
                    case 44: // Service provider personalization PIN required
                        ucGprsSIMStatus = PH_SVC_PROVIDER_PIN;
                        ret = -1; // fatal error
                        break;
                    case 45: // Service provider personalization PUK required
                        ucGprsSIMStatus = PH_SVC_PROVIDER_PUK;
                        ret = -1; // fatal error
                        break;
                    case 46: // Corporate personalization PIN required
                        ucGprsSIMStatus = PH_CORPORATE_PIN;
                        ret = -1; // fatal error
                        break;
                    case 47: // Corporate personalization PUK required
                        ucGprsSIMStatus = PH_CORPORATE_PUK;
                        ret = -1; // fatal error
                        break;
                    case 48: // PH-SIM PUK (master phone code) required
                        ucGprsSIMStatus = PH_SIM_PUK;
                        ret = -1; // fatal error
                        break;
                    case 18: // SIM PUK2 required
                        ucGprsSIMStatus = SIM_PUK2;
                        ret = -1; // fatal error
                        break;

                    default:
                        ret = -2;
                        break;
                }

#ifdef USER_DEBUG
#if 0
                memset(temp, 0x00, sizeof (temp));
                for (i = 0;; i++) {
                    if (CME_ERROR_CODE[i].error_code == error_code ||
                            CME_ERROR_CODE[i].error_code == -1) {
                        strcpy(temp[0], CME_ERROR_CODE[i].error_msg);
                        break;
                    }
                }
                Rprintf("%s\r\n", temp[0]);
#endif
#endif

                if (ret) {
                    if (ret == -1) { // fatal error
                        ucGprsPowerOffFlag = 1;
                        if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("SIM Error!!\r\n");
#endif
                            GprsDisplaySIMErrorMessage();
                            AbnormalProcessingBeforeTx();
                        } else {
                            ModemClose();
                        }
                    } else {
                        //if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                        if (ucTMSDownloadFlag) {
#ifdef USER_DEBUG
                            Rprintf("Modem Error!!\r\n");
#endif
                            // "Modem Error     ",
                            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ModemError_0000001], ucLangFlag);
                            AbnormalProcessingBeforeTx();
                        } else {
                            // Waiting for response of Set the URL to Internet Service Setup Profile
                            // Delay for sending Internet Service Open
                            // Delay for sending Internet Service Open
                            // Internet Service Open
                            // Waiting for response of Internet Service Open
                            // Delay for sending Enter Transparent Access Mode
                            // Delay for sending Enter Transparent Access Mode
                            // Enter Transparent Access Mode
                            // Waiting for response of Enter Transparent Access Mode
                            if (usGprsTaskStep >= 167 && usGprsTaskStep <= 175) {
                                ModemClose();
                            }
                            usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
                        }
                    }
                }
            } else if (iRxCnt >= 20 && !memcmp((char *) &ucRxBuf[0], "^SIS: ", 6)) {
                // Unsolicited Result Code
                // ^SIS: <srvProfileId>, <urcCause>[, [<urcInfoId>][, <urcInfoText>]]
                //
                // <srvProfileId>(num)
                // 0 ... 9		specified with AT^SISS.
                //
                // <urcCause>(num)
                // URC cause identifier.
                // 0			An event has occurred after opening or while using an Internet service.
                // 				The event number is presented via <urcInfoId> and may be an error, a
                // 				warning, an information element or a note. Optionally additional information
                // 				may be supplied via <urcInfoText>.
                // 1			Indicates that an opened Socket listener service is receiving a connection
                // 				request from a remote client.
                // 				The incoming socket connection is dynamically assigned to the next free Internet
                // 				service profile. In this case, the parameter <urcInfoId> inside the "^SIS"
                // 				URC equals the <srvProfileId> of the dynamically assigned service profile.
                // 				This ID shall be used to accept the connection request with AT^SISO or to
                // 				reject it with AT^SISC.
                // 				The connection status may be requested by using the AT^SISI read or write
                // 				command or the AT^SISO read command. Among other details, the response
                // 				indicates the IP address of the remote client (parameter <remAddr>). This
                // 				may be helpful to decide whether to accept or reject the request.
                // 2			Incoming Socket service client connection has failed. The client request was
                // 				rejected automatically because no free Internet service profile was available.
                //
                // <urcInfoId>(num)
                // Information identifier related to <urcCause>. See tables below for further detail. The <urcInfoId> number
                // ranges indicate the type of information element:
                // 0: Service is working properly.
                // 1 - 2000: Error, service is aborted and enters <srvState>=6 (Down).
                // 2001 - 4000: Information related to progress of service.
                // 4001 - 6000: Warning, but no service abort.
                // 6001 - 8000: Notes
                // Additional information for Socket service: As stated above, if a Socket connection request from a remote client
                // is received (see <urcCause>=1) the <urcInfoId> equals the <srvProfileId> of the dynamically assigned
                // free service profile.
                //
                // <urcInfoText>(str)
                // Information text related to <urcCause>. See tables below for further detail.
                //
                // ^SIS: 0, 0, 18, "For TCP/IP sockets, the socket is not connected"
                // ^SIS: 0, 0, 20, "Connection timed out"
                // ^SIS: 0, 0, 15
                if (usGprsTaskStep == 171) {
                    ModemClose();
                }
                usGprsTaskStep = 180; // Check the GPRS connection counter is over maximum connection counter
            } else if (iRxCnt >= 10 && !memcmp((char *) &ucRxBuf[0], "+COPS: ", 7)) {
                // Waiting for response of Read selected an operator command
                if (usGprsTaskStep == 21) {
                    memset(temp, 0x00, sizeof (temp));
                    for (i = 7, j = k = 0; i < iRxCnt; i++) {
                        if (ucRxBuf[i] == ',') {
                            k++;
                            j = 0;
                            continue;
                        } else if (ucRxBuf[i] == '\r') {
                            break;
                        }
                        temp[k][j++] = ucRxBuf[i];
                    }
                    ucGsmNetworkRegistrationMode = atoi(temp[0]);
                    memset(sz18GsmOperator, 0x00, sizeof (sz18GsmOperator));
                    if (k == 2) {
                        sz18GsmOperator[0] = temp[1][0];
                        strcpy(&sz18GsmOperator[1], temp[2]);
                    }
                }
            } else if (iRxCnt == 12 && !memcmp((char *) &ucRxBuf[0], "NO CARRIER", 10)) {
#ifdef USER_DEBUG
                Rprintf("\r\nE>%d - No Carrier\r\n", usGprsTaskStep);
#endif
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "No Carrier      ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1NoCarrierError_001], ucLangFlag);
                }
                usGprsTaskStep = 0;
                ModemClose();
                usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
            } else if (iRxCnt == 11 && !memcmp((char *) &ucRxBuf[0], "NO ANSWER", 9)) {
                // about 65 seconds
#ifdef USER_DEBUG
                Rprintf("\r\nE>%d - No Answer\r\n", usGprsTaskStep);
#endif
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "Timeout(S7)     ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1S7TimeoutError_001], ucLangFlag);
                }
                ModemClose();
                usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
            } else if (iRxCnt == 6 && !memcmp((char *) &ucRxBuf[0], "BUSY", 4)) {
#ifdef USER_DEBUG
                Rprintf("\r\nE>%d - BUSY\r\n", usGprsTaskStep);
#endif
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "Busy            ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1LineBusyError_0001], ucLangFlag);
                }
                ModemClose();
                usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
            } else if (iRxCnt == 7 && !memcmp((char *) &ucRxBuf[0], "ERROR", 5)) {
                if (ucReqDataReadyFlag || ucTMSDownloadFlag) {
                    // "Modem Error     ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ModemError_0000001], ucLangFlag);
                    AbnormalProcessingBeforeTx();
                } else {
                    ModemClose();
                }
            }
            memset((char *) &ucRxBuf[0], 0, iRxCnt);
            iRxCnt = 0;
        }
        return;
    }

    // Data Mode
    if (TIMER_GetElapsed10MSTime(usGprs10MSTimer) >= usGprs10MSMaxTimeout) {
        Rprintf("usGprs10MSTimer=%d, usGprs10MSMaxTimeout=%d, Elapsed=%d\r\n", usGprs10MSTimer, usGprs10MSMaxTimeout, TIMER_GetElapsed10MSTime(usGprs10MSTimer));
#ifdef USER_DEBUG
        Rprintf("\r\nE>%d - COMM Timeout\r\n", usGprsTaskStep);
#endif

        if (ucReqDataReadyFlag || ucReqDataTxFlag) {
            // "COMM Timeout    ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1CommTimeoutError_1], ucLangFlag);
        }

        if (giTransactionType == TRXN_BANK_EFTTRAN && ucReqDataTxFlag) {
            AbnormalProcessingAfterTx();
        } else {
            ModemClose();
            usGprsTaskStep = 180; // Modem Reset & Check the modem connection counter is over maximum connection counter
        }
        return;
    }


    // Send Request Data if Request Data is ready
    if ((usGprsTaskStep == 201 || usGprsTaskStep == 205) && ucReqDataReadyFlag) {
        ucReqDataReadyFlag = 0;

        // "SENDING DATA... ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SendingData_000001], ucLangFlag);

        if (usGprsTaskStep == 201) {
            pusReqSequence = (int *) tbl_ReqSequence[giTransactionType];
            giRequestType = *pusReqSequence;
        }

        BuildQueryString();

        if (*pusReqSequence == API_BANK_EFTTRAN) {
            //tPOSUtilBuf.usBatchNo = st_TrxnReqData.usBatchNo;
            tPOSUtilBuf.usSeqNo++;
            SavePOSUtilBuf();
            if (st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY || st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
                if (ucReversalFlag == 0) {
                    SaveTxTransactionLog();
                }
            }
        }

        SendRequestMessage(giRequestType, ucTrxnTxBuf, "");
        ucReqDataTxFlag = 1;
        iRxCnt = 0;
        iKeyCnt = 0;

        ucGprsDLESetFlag = 0;

        usGprs10MSTimer = TIMER_Get10MSTimer();
        usGprsTaskStep = 202;

        usGprs10MSMaxTimeout = (unsigned short) (st_POSSetupInfo.ucCommTimeout) * 100;
#ifdef TEST_OFFLINE

        // "RECEIVING DATA..",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReceivingData_0001], ucLangFlag);
        if (giTransactionType == TRXN_BANK_EFTTRAN) {
            //	strcpy(&ucRxBuf[0], "<efttran><tran><result>1</result><message>Approved</message><status>000</status><refno>000000002443</refno><tranno>171</tranno><batchno>5</batchno><balance>N -100.00</balance><available>N 100.00</available></tran></efttran>");
            //	strcpy(&ucRxBuf[0], "<efttran><tran><result>1</result><message>Approved</message><status>000</status><refno>000000354236</refno><tranno>4</tranno><batchno>3</batchno><fromacc>0028416874</fromacc><iccresponse>9120CB18FBEB008000000000000000000000</iccresponse></tran></efttran>");
            strcpy(&ucRxBuf[0], "<efttran><tran><result>1</result><message>Approved</message><status>000</status><refno>000000372061</refno><tranno>5</tranno><batchno>3</batchno><fromacc>209073150201005900</fromacc><iccresponse>91147746DCCBB9D8BBEF0012</iccresponse><authid>366422</authid></tran></efttran>");

            /*
                    if(st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY)
                            return;
                    if(st_TrxnReqData.usTrxnType == TRXN_BALANCE_INQUIRY)
                            return;
                    strcpy(&ucRxBuf[0], "<efttran><tran><result>2</result><message>Transaction not found</message><status>302</status><tranno>4</tranno><batchno>6</batchno></tran></efttran>");
             */

        } else if (giTransactionType == TRXN_BANK_EFTTOTAL) {
            strcpy(&ucRxBuf[0], "<efttotals><result>0</result><batchno>7</batchno></efttotals>");
        } else if (giTransactionType == TRXN_TAMS_CALLHOME) {
            //strcpy(&ucRxBuf[0], "<error><errcode>5</errcode><errmsg>Request could not be authenticated</errmsg></error>");
            strcpy(&ucRxBuf[0], "<callhome />");
        } else {
            if (*pusReqSequence == API_GET_APPLIST) {
                strcpy(&ucRxBuf[0], "<appllist><applsvr><applid>1</applid><name>Tams</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr><applsvr><applid>2</applid><name>VoucherVault</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr><applsvr><applid>3</applid><name>Banking</name><url>http://41.58.130.139/tams/funclist.php</url><functime>1303237297</functime><disabled>N</disabled></applsvr></appllist>");
            } else if (*pusReqSequence == API_GET_FUNCLIST) {
                if (pstAppList[giApplIdx].usApplId == 1) {
                    strcpy(&ucRxBuf[0], "<funclist><function><name>AGENTLOGIN</name><url>http://41.58.130.139/tams/tams/devinterface/agentlogin.php</url></function><function><name>AGENTLOGOUT</name><url>http://41.58.130.139/tams/tams/devinterface/agentlogout.php</url></function><function><name>CALLHOME</name><url>http://41.58.130.139/tams/tams/devinterface/callhome.php</url></function><function><name>EOD</name><url>http://41.58.130.139/tams/tams/devinterface/eod.php</url></function><function><name>GETKEYS</name><url>http://41.58.130.139/tams/tams/devinterface/getkeys.php</url></function><function><name>GETLOGO</name><url>http://41.58.130.139/tams/tams/devinterface/getlogo.php</url></function><function><name>GETMENU</name><url>http://41.58.130.139/tams/tams/devinterface/getmenu.php</url></function><function><name>GETPROMPTLIST</name><url>http://41.58.130.139/tams/tams/devinterface/getpromptlist.php</url></function><function><name>NEWKEY</name><url>http://41.58.130.139/tams/tams/devinterface/newkey.php</url></function><function><name>OPERATORREPORT</name><url>http://41.58.130.139/tams/tams/devinterface/operatorreport.php</url></function><function><name>PARAM</name><url>http://41.58.130.139/tams/tams/devinterface/getparams.php</url></function><function><name>TELLERCARDS</name><url>http://41.58.130.139/tams/tams/devinterface/tellercards.php</url></function></funclist>");
                } else if (pstAppList[giApplIdx].usApplId == 2) {
                    strcpy(&ucRxBuf[0], "<funclist><function><name>CANCELORDER</name><url>http://41.58.130.139/tams/vouchervault/devinterface/cancelorder.php</url></function><function><name>ELECSALE</name><url>http://41.58.130.139/tams/vouchervault/devinterface/electricityorder.php</url></function><function><name>GETBALANCE</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getbalance.php</url></function><function><name>GETSTOCK</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getstock.php</url></function><function><name>ORDER</name><url>http://41.58.130.139/tams/vouchervault/devinterface/order.php</url></function><function><name>PARAM</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getparams.php</url></function><function><name>PINLESSORDER</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessorder.php</url></function><function><name>PINLESSRECONTOTAL</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessrecontotal.php</url></function><function><name>PINLESSREVERSAL</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessreversal.php</url></function><function><name>PINLESSSTATUS</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessstatus.php</url></function><function><name>PINLESSUPLOAD</name><url>http://41.58.130.139/tams/vouchervault/devinterface/pinlessupload.php</url></function><function><name>PRODLIST</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getprodlist.php</url></function><function><name>REPRINT</name><url>http://41.58.130.139/tams/vouchervault/devinterface/reprint.php</url></function><function><name>RETURNSTOCK</name><url>http://41.58.130.139/tams/vouchervault/devinterface/returnstock.php</url></function><function><name>SALES</name><url>http://41.58.130.139/tams/vouchervault/devinterface/sales.php</url></function><function><name>SPLIST</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getsplist.php</url></function><function><name>SPLOGO</name><url>http://41.58.130.139/tams/vouchervault/devinterface/getsplogo.php</url></function></funclist>");
                } else if (pstAppList[giApplIdx].usApplId == 3) {
                    strcpy(&ucRxBuf[0], "<funclist><function><name>BINTABLE</name><url>http://41.58.130.139/tams/eftpos/devinterface/bintables.php</url></function><function><name>BIOTEMPLATE</name><url>http://41.58.130.139/tams/eftpos/devinterface/biotemplate.php</url></function><function><name>BIOTRAN</name><url>http://41.58.130.139/tams/eftpos/devinterface/biotran.php</url></function><function><name>DISTORDER</name><url>http://41.58.130.139/tams/eftpos/devinterface/distorder.php</url></function><function><name>DISTRETURN</name><url>http://41.58.130.139/tams/eftpos/devinterface/distreturn.php</url></function><function><name>EFTPARAMS</name><url>http://41.58.130.139/tams/eftpos/devinterface/eftparams.php</url></function><function><name>EFTTOTALS</name><url>http://41.58.130.139/tams/eftpos/devinterface/efttotals.php</url></function><function><name>EFTTRAN</name><url>http://41.58.130.139/tams/eftpos/devinterface/transaction.php</url></function><function><name>EMVAPP</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvapp.php</url></function><function><name>EMVCAPK</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvcapk.php</url></function><function><name>EMVREVOKECAPK</name><url>http://41.58.130.139/tams/eftpos/devinterface/emvrevokecapk.php</url></function><function><name>EODTXNLIST</name><url>http://41.58.130.139/tams/eftpos/devinterface/txnlist.php</url></function><function><name>HOTCARDS</name><url>http://41.58.130.139/tams/eftpos/devinterface/hotcards.php</url></function><function><name>LINKED</name><url>http://41.58.130.139/tams/eftpos/devinterface/linked.php</url></function><function><name>UPLOADTXN</name><url>http://41.58.130.139/tams/eftpos/devinterface/uploadtxn.php</url></function></funclist>");
                }
            } else if (*pusReqSequence == API_TAMS_NEWKEY) {
                strcpy(&ucRxBuf[0], "<newkey><masterkey>9777c6788f5ee44cfee794612dc1f696</masterkey></newkey>");
            } else if (*pusReqSequence == API_TAMS_GETKEYS) {
                strcpy(&ucRxBuf[0], "<getkeys><cipher><no>0</no><key>019554019f4051c882b37c682bfb738a</key></cipher><cipher><no>1</no><key>24a6474789c0dcfbe6dcba7089124b92</key></cipher><cipher><no>2</no><key>08458a95de4b0337391b1c7c189f99de</key></cipher><cipher><no>3</no><key>1a1a8db92fa0e5ced51b3f66c128814d</key></cipher><cipher><no>4</no><key>0be32ce22dec665256eb105aed59de6a</key></cipher><cipher><no>5</no><key>fb05616934587afd3c3f4e342d380d3b</key></cipher><cipher><no>6</no><key>beccacac36deecdeb90f579a01c82db4</key></cipher><cipher><no>7</no><key>07d256cd4a03dae88ec00647952d2a0d</key></cipher><cipher><no>8</no><key>afee2a2c7a70756071f1b475a2283b39</key></cipher><cipher><no>9</no><key>a6ab7ad64c70a2aa30856730bea5ca3d</key></cipher></getkeys>");
            } else if (*pusReqSequence == API_TAMS_PARAM) {
                strcpy(&ucRxBuf[0], "<param><datetime><year>2012</year><syear>12</syear><mon>01</mon><day>18</day><hour>00</hour><min>32</min><sec>46</sec></datetime><merchantid>74</merchantid><header>bangar</header><footer>welcome</footer><pinreset>N</pinreset><updatelogo>N</updatelogo><updatemenu>N</updatemenu><replytimeout>60</replytimeout><currency>N</currency><fract>2</fract><prefix>Y</prefix><negnum>2</negnum><currcode>0566</currcode><decsym>.</decsym><thoussep>,</thoussep><countrycode>0566</countrycode><endofday>23</endofday><updateprompts>1326843166</updateprompts><attendance>N</attendance><agentaccess>N</agentaccess><eodtime><enabled>N</enabled></eodtime><conn1>0</conn1><conn2>0</conn2><download><enabled>N</enabled><downloadconn>0</downloadconn></download><disabled>N</disabled></param>");
            } else if (*pusReqSequence == API_BANK_EFTPARAMS) {
                strcpy(&ucRxBuf[0], "<eftparam><online>1</online><maxcashback>0</maxcashback><minbudgetperiod>6</minbudgetperiod><maxbudgetperiod>60</maxbudgetperiod><budgetminamount>0</budgetminamount><velocitytime>1</velocitytime><manualonline>N</manualonline><eodtxnlist>N</eodtxnlist></eftparam>");
            } else if (*pusReqSequence == API_BANK_BINTABLE) {
                strcpy(&ucRxBuf[0], "<bintable><bin><pan>9</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>0</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>84896</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>639587</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>639139</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>546097</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>541333</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>540463</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>539983</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>539923</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>530519</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>518791</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506120</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506119</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>125</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506118</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506117</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506111</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>61</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>506110</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506109</pan><length>18</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506108</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>506105</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>506101</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>3775</allow><keyindex>2</keyindex></bin><bin><pan>502192</pan><length>19</length><cardtype>0</cardtype><floor>0</floor><check>13</check><allow>767</allow><keyindex>2</keyindex></bin><bin><pan>492181</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>476173</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>471415</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>57</check><allow>4096</allow><keyindex>2</keyindex></bin><bin><pan>470655</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>458536</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>446272</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>442434</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>428691</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>3775</allow><keyindex>2</keyindex></bin><bin><pan>427876</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>57</check><allow>0</allow><keyindex>2</keyindex></bin><bin><pan>427011</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>422584</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin><bin><pan>417059</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>77</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>413103</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>73</check><allow>4095</allow><keyindex>2</keyindex></bin><bin><pan>412053</pan><length>16</length><cardtype>0</cardtype><floor>0</floor><check>121</check><allow>4031</allow><keyindex>2</keyindex></bin></bintable>");
            } else if (*pusReqSequence == API_BANK_EMVAPP) {
                //strcpy(&ucRxBuf[0], "<emv><count>6</count><app><index>0</index><irn>1</irn><aid>A0000000032010</aid><match>0</match><name>Visa Electron</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>1</index><irn>2</irn><aid>A0000000031010</aid><match>0</match><name>Visa Credit</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>2</index><irn>3</irn><aid>A0000000041010</aid><match>0</match><name>MasterCard</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>3</index><irn>4</irn><aid>A0000000042010</aid><match>0</match><name>MasterCard Maestro</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>4</index><irn>5</irn><aid>A0000003710001</aid><match>0</match><name>Interswitch Verve</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>5</index><irn>6</irn><aid>A0000004540010</aid><match>0</match><name>eTranzact Genesis</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app></emv>");
                strcpy(&ucRxBuf[0], "<emv><count>7</count><app><index>0</index><irn>1</irn><aid>A0000000032010</aid><match>0</match><name>Visa Electron</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>1</index><irn>2</irn><aid>A0000000031010</aid><match>0</match><name>Visa Credit</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>2</index><irn>3</irn><aid>A0000000041010</aid><match>0</match><name>MasterCard</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>3</index><irn>4</irn><aid>A0000000042010</aid><match>0</match><name>MasterCard Maestro</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>4</index><irn>5</irn><aid>A0000003710001</aid><match>0</match><name>Interswitch Verve</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>5</index><irn>6</irn><aid>A0000004540010</aid><match>0</match><name>eTranzact Genesis</name><appver>0100</appver><priority>1</priority><ddol>9F3704</ddol><tdol>9F02065F2A029A039C0195059F3704</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app><app><index>6</index><irn>7</irn><aid>A000000003</aid><match>0</match><name>Visa</name><appver>0100</appver><priority>1</priority><ddol>9F02069F03069F3704</ddol><tdol>9F02069F03068A02</tdol><tfldom>00000000</tfldom><tflint>00000000</tflint><thresholddom>0000</thresholddom><thresholdint>0000</thresholdint><maxtargetdom>20</maxtargetdom><maxtargetint>50</maxtargetint><targetpercentdom>80</targetpercentdom><targetpercentint>70</targetpercentint><tacdefault>D84000A800</tacdefault><tacdenial>0010000000</tacdenial><taconline>D84004F800</taconline></app></emv>");
            } else if (*pusReqSequence == API_BANK_EMVCAPK) {
                strcpy(&ucRxBuf[0], "<calist><count>10</count><ca><index>01</index><irn>1</irn><name>1</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>C696034213D7D8546984579D1D0F0EA519CFF8DEFFC429354CF3A871A6F7183F1228DA5C7470C055387100CB935A712C4E2864DF5D64BA93FE7E63E71F25B1E5F5298575EBE1C63AA617706917911DC2A75AC28B251C7EF40F2365912490B939BCA2124A30A28F54402C34AECA331AB67E1E79B285DD5771B5D9FF79EA630B75</modulus><exponent>03</exponent><hash>D34A6A776011C7E7CE3AEC5F03AD2F8CFC5503CC</hash><pkalgo>1</pkalgo></ca><ca><index>07</index><irn>2</irn><name>2</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>A89F25A56FA6DA258C8CA8B40427D927B4A1EB4D7EA326BBB12F97DED70AE5E4480FC9C5E8A972177110A1CC318D06D2F8F5C4844AC5FA79A4DC470BB11ED635699C17081B90F1B984F12E92C1C529276D8AF8EC7F28492097D8CD5BECEA16FE4088F6CFAB4A1B42328A1B996F9278B0B7E3311CA5EF856C2F888474B83612A82E4E00D0CD4069A6783140433D50725F</modulus><exponent>03</exponent><hash>B4BC56CC4E88324932CBC643D6898F6FE593B172</hash><pkalgo>1</pkalgo></ca><ca><index>08</index><irn>3</irn><name>3</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>D9FD6ED75D51D0E30664BD157023EAA1FFA871E4DA65672B863D255E81E137A51DE4F72BCC9E44ACE12127F87E263D3AF9DD9CF35CA4A7B01E907000BA85D24954C2FCA3074825DDD4C0C8F186CB020F683E02F2DEAD3969133F06F7845166ACEB57CA0FC2603445469811D293BFEFBAFAB57631B3DD91E796BF850A25012F1AE38F05AA5C4D6D03B1DC2E568612785938BBC9B3CD3A910C1DA55A5A9218ACE0F7A21287752682F15832A678D6E1ED0B</modulus><exponent>03</exponent><hash>20D213126955DE205ADC2FD2822BD22DE21CF9A8</hash><pkalgo>1</pkalgo></ca><ca><index>09</index><irn>4</irn><name>4</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>9D912248DE0A4E39C1A7DDE3F6D2588992C1A4095AFBD1824D1BA74847F2BC4926D2EFD904B4B54954CD189A54C5D1179654F8F9B0D2AB5F0357EB642FEDA95D3912C6576945FAB897E7062CAA44A4AA06B8FE6E3DBA18AF6AE3738E30429EE9BE03427C9D64F695FA8CAB4BFE376853EA34AD1D76BFCAD15908C077FFE6DC5521ECEF5D278A96E26F57359FFAEDA19434B937F1AD999DC5C41EB11935B44C18100E857F431A4A5A6BB65114F174C2D7B59FDF237D6BB1DD0916E644D709DED56481477C75D95CDD68254615F7740EC07F330AC5D67BCD75BF23D28A140826C026DBDE971A37CD3EF9B8DF644AC385010501EFC6509D7A41</modulus><exponent>03</exponent><hash>1FF80A40173F52D7D27E0F26A146A1C8CCB29046</hash><pkalgo>1</pkalgo></ca><ca><index>55</index><irn>5</irn><name>5</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>8B2BCDC1495920A5051AB3D6506E3BFDDC946A5F03957497A4836BE735227D3FDA33FB227A4DA15093845E8A08B392471CE0BEB588D6A3EB8571C2767350C387AF8E452BCD6F9A4848D835C08EDD91DE3A61B7D13FCA77B4628334792812289D5876226501D71B3EE4516351B017BD88C494F966383458273ABF0C40E7421F5F</modulus><exponent>03</exponent><hash>B0365792C471147B3FEA46608675DE7D16701661</hash><pkalgo>1</pkalgo></ca><ca><index>08</index><irn>6</irn><name>6</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>D9FD6ED75D51D0E30664BD157023EAA1FFA871E4DA65672B863D255E81E137A51DE4F72BCC9E44ACE12127F87E263D3AF9DD9CF35CA4A7B01E907000BA85D24954C2FCA3074825DDD4C0C8F186CB020F683E02F2DEAD3969133F06F7845166ACEB57CA0FC2603445469811D293BFEFBAFAB57631B3DD91E796BF850A25012F1AE38F05AA5C4D6D03B1DC2E568612785938BBC9B3CD3A910C1DA55A5A9218ACE0F7A21287752682F15832A678D6E1ED0B</modulus><exponent>03</exponent><hash>20D213126955DE205ADC2FD2822BD22DE21CF9A8</hash><pkalgo>1</pkalgo></ca><ca><index>99</index><irn>7</irn><name>7</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>AB79FCC9520896967E776E64444E5DCDD6E13611874F3985722520425295EEA4BD0C2781DE7F31CD3D041F565F747306EED62954B17EDABA3A6C5B85A1DE1BEB9A34141AF38FCF8279C9DEA0D5A6710D08DB4124F041 945587E20359BAB47B7575AD94262D4B25F264AF33DEDCF28E09615E937DE32EDC03C54445FE7E382777</modulus><exponent>03</exponent><hash>4ABFFD6B1C51212D05552E431C5B17007D2F5E6D</hash><pkalgo>1</pkalgo></ca><ca><index>95</index><irn>8</irn><name>8</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>BE9E1FA5E9A803852999C4AB432DB28600DCD9DAB76DFAAA47355A0FE37B1508AC6BF38860D3C6C2E5B12A3CAAF2A7005A7241EBAA7771112C74CF9A0634652FBCA0E5980C54A64761EA101A114E0F0B5572ADD57D010B7C9C887E104CA4EE1272DA66D997B9A90B5A6D624AB6C57E73C8F919000EB5F684898EF8C3DBEFB330C62660BED88EA78E909AFF05F6DA627B</modulus><exponent>03</exponent><hash>EE1511CEC71020A9B90443B37B1D5F6E703030F6</hash><pkalgo>1</pkalgo></ca><ca><index>92</index><irn>9</irn><name>9</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>996AF56F569187D09293C14810450ED8EE3357397B18A2458EFAA92DA3B6DF6514EC060195318FD43BE9B8F0CC669E3F844057CBDDF8BDA191BB64473BC8DC9A730DB8F6B4EDE3924186FFD9B8C7735789C23A36BA0B8AF65372EB57EA5D89E7D14E9C7B6B557460F10885DA16AC923F15AF3758F0F03EBD3C5C2C949CBA306DB44E6A2C076C5F67E281D7EF56785DC4D75945E491F01918800A9E2DC66F60080566CE0DAF8D17EAD46AD8E30A247C9F</modulus><exponent>03</exponent><hash>429C954A3859CEF91295F663C963E582ED6EB253</hash><pkalgo>1</pkalgo></ca><ca><index>94</index><irn>11</irn><name>11</name><rid>A000000003</rid><hashalgo>1</hashalgo><modulus>ACD2B12302EE644F3F835ABD1FC7A6F62CCE48FFEC622AA8EF062BEF6FB8BA8BC68BBF6AB5870EED579BC3973E121303D34841A796D6DCBC41DBF9E52C4609795C0CCF7EE86FA1D5CB041071ED2C51D2202F63F1156C58A92D38BC60BDF424E1776E2BC9648078A03B36FB554375FC53D57C73F5160EA59F3AFC5398EC7B67758D65C9BFF7828B6B82D4BE124A416AB7301914311EA462C19F771F31B3B57336000DFF732D3B83DE07052D730354D297BEC72871DCCF0E193F171ABA27EE464C6A97690943D59BDABB2A27EB71CEEBDAFA1176046478FD62FEC452D5CA393296530AA3F41927ADFE434A2DF2AE3054F8840657A26E0FC617</modulus><exponent>03</exponent><hash>C4A3C43CCF87327D136B804160E47D43B60E6E0F</hash><pkalgo>1</pkalgo></ca></calist>");
            } else if (*pusReqSequence == API_BANK_EMVREVOKECAPK) {
                strcpy(&ucRxBuf[0], "<calist><count>0</count></calist>");
            } else if (*pusReqSequence == API_BANK_HOTCARDS) {
                strcpy(&ucRxBuf[0], "<hotcards />");
            }
        }

        iRxCnt = strlen(ucRxBuf);
        Rprintf("ucRxBuf[%d]=%s\r\n", iRxCnt, ucRxBuf);
        NIBSS_Parsing((char *) &ucRxBuf[0], iRxCnt, giRequestType, &gbTmpRespBuf);

        ucReqDataTxFlag = 0;
        ucReqDataReadyFlag = 0;
        // Function List �� App������ŭ ����
        if (st_ErrRespData.iErrFlag == 1) {
            if (giRequestType == API_TAMS_NEWKEY) {
                giRequestType = *(++pusReqSequence);
            } else {
                giRequestType = -1;
            }
        } else if (giRequestType == API_GET_APPLIST) {
            giApplIdx = 0;
            giRequestType = *(++pusReqSequence);
        } else if (giRequestType == API_GET_FUNCLIST) {
            if (++giApplIdx < usAppListCnt) {
                // ApplId = pstAppList[giApplIdx].usApplId;
                // 1175 55 3590 125 1070 1400 4582 2470 7050
            } else {
                giRequestType = *(++pusReqSequence);
            }
        } else if (giRequestType == API_BANK_EFTTOTALS) {
            /*
                                            if(st_TrxnRespData.ucResult == '0') {
                                                    if(st_TrxnRespData.usTrxnBatchNo != tPOSUtilBuf.usBatchNo) {
                                                            // �ܸ����� Batch Number�� ���� Batch Number�� Ʋ���� ���� ������ ����, Sequence Number�� �ʱ�ȭ
                                                            tPOSUtilBuf.usBatchNo = st_TrxnRespData.usTrxnBatchNo;
                                                            tPOSUtilBuf.usSeqNo = 0;
                                                            SavePOSUtilBuf();
                                                            // Batch Printing��? - Request/Response Data�� �̿��ؼ� Printing
                                                            EraseAllTransactionLog();
                                                    }
                                            }
             */
            giRequestType = *(++pusReqSequence);
        } else if (giRequestType == API_BANK_EFTTRAN) {
            /*				if(st_TrxnReqData.usTrxnType == TRXN_PURCHASE_ONLY || st_TrxnReqData.usTrxnType == TRXN_REVERSAL) {
                                                    SaveRxTransactionLog();
                                            }
             */ if (st_TrxnRespData.ucResult != '1') {
                giRequestType = -1;
            } else {
                giRequestType = *(++pusReqSequence);
            }
        } else {
            giRequestType = *(++pusReqSequence);
        }
        memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
        iRxCnt = 0;
        if (giRequestType < 0) {
            OnlineTrxnResultProcessing();
            /*
                                            // ������� - Communication completed
                                            ModemClose();
                                            pusServiceAddr++;
                                            sVirtualKey = BTKEY_ENTER;
                                            // usGprsTaskStep = 206;
             */ //		break;
        } else {
            ucReqDataReadyFlag = 1;
            usGprsTaskStep = 205;
        }

#endif





        return;
    }

    if (RS232_CheckRxInput(GPRS_COM_PORT) == 0) {
        return;
    }

    rxdata = RS232_Read(GPRS_COM_PORT) & 0xFF;
#ifdef USER_DEBUG
    if ((giTransactionType == TRXN_BANK_EFTTRAN) || (giTransactionType == TRXN_BANK_EFTTOTAL)) {
        Rprintf("%c", (unsigned char) rxdata);
    }
#endif
    // Check disconnection
    if (GprsCheckDisconnect(rxdata)) {
#ifdef USER_DEBUG
        Rprintf("\r\nE>%d - NO CARRIER\r\n", usGprsTaskStep);
#endif

        if (ucReqDataReadyFlag || ucReqDataTxFlag) {
            // "No Carrier      ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1NoCarrierError_001], ucLangFlag);
        }

        usGprsTaskStep = 0;
        if (ucReqDataTxFlag) {
            AbnormalProcessingAfterTx();
        } else {
            ModemClose();
            usGprsTaskStep = 100; // Modem Reset & Check the modem connection counter is over maximum connection counter
        }
        return;
    }

    ucRxBuf[iRxCnt] = rxdata;
    iRxCnt++;
    iRxCnt &= 0x1FFF;

    switch (usGprsTaskStep) {
        case 200:
            usGprsTaskStep++;
            break;
        case 201: // Wait for Tx
            iRxCnt = 0;
            usGprsTaskStep++;
            break;

        case 202: // Receiving HTTP Response Code
            if (iRxCnt >= 2 && !memcmp(&ucRxBuf[iRxCnt - 2], "\x0D\x0A", 2)) {
                //Rprintf("Receiving HTTP Response Code\r\n");
                char *ptr;
                ucRxBuf[iRxCnt] = 0x00;
                if (ptr = strstr(&ucRxBuf[0], "HTTP/")) { // ex) HTTP/1.1 200 OK
                    if (ptr[9] != '2') { // 2xx : CODE FOR SUCCESS
                        memcpy(temp[0], &ptr[9], 3);
                        temp[0][3] = 0x00;
                        ptr[iRxCnt - 2] = 0x00;
                        strcpy(temp[1], &ptr[13]);
                        LCD_ClearScreen();
                        LCD_DisplayString(0, 0, strlen(&ptr[13]), &ptr[13], ucLangFlag);
                        LCD_DisplayLine(0, LEFT_JUSTIFIED, (char *) temp[0], ucLangFlag);
                        LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) temp[1], ucLangFlag);
                        if (strlen(temp[1]) > 16) {
                            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) &temp[1][16], ucLangFlag);
                            if (strlen(temp[1]) > 24)
                                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) &temp[1][24], ucLangFlag);
                        }
                        ModemClose();
                        // Ʈ�����(PURCHASE)�� ��� �α׿� ��ȿó��??? Reversal???
                        if (giTransactionType == TRXN_BANK_EFTTRAN) {
                            AbnormalProcessingAfterTx();
                        }
                        ucReqDataTxFlag = 0;
                        break;
                    }
                    memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
                    iRxCnt = 0;
                    // "RECEIVING DATA..",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReceivingData_0001], ucLangFlag);
                    usGprsTaskStep++;
                }
            }
            break;
        case 203: // Receiving HTTP Response Header
            if (iRxCnt >= 4 && !memcmp(&ucRxBuf[iRxCnt - 4], "\x0D\x0A\x0D\x0A", 4)) {
                //Rprintf("Receiving HTTP Response Header\r\n");

                {
                    int i, in, len;
                    char *ptr;
                    ptr = strstr(&ucRxBuf[0], "Content-Length:");
                    // null
                    for (i = in = len = 0; ptr[i] != 0x0D; i++) {
                        if (in == 0 && ptr[i] >= '0' && ptr[i] <= '9') {
                            in = 1;
                        }
                        if (in == 1) {
                            if (ptr[i] >= '0' && ptr[i] <= '9') {
                                len = len * 10 + ptr[i] - '0';
                            } else {
                                in = 0;
                                break;
                            }
                        }
                    }
                    giRespContentLength = len;
                }

                // End of HTTP Header
                memcpy(&ucHtmlHeader[0], &ucRxBuf[0], iRxCnt);
                // ProcessHttpHeader giRespContentLength
                memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
                iRxCnt = 0;
                usGprsTaskStep++;
                break;
            }
            break;
        case 204: // Receiving HTTP Response Body
            if (iRxCnt < giRespContentLength)
                break;
            //Rprintf("Received HTTP Response Body\r\n");
            ucReqDataTxFlag = 0;
            NIBSS_Parsing((char *) &ucRxBuf[0], iRxCnt, giRequestType, &gbTmpRespBuf);
            // Function List �� App������ŭ ����
            if (st_ErrRespData.iErrFlag == 1) {
                if (giRequestType == API_TAMS_NEWKEY) {
                    giRequestType = *(++pusReqSequence);
                } else {
                    giRequestType = -1;
                }
            } else if (giRequestType == API_GET_APPLIST) {
                giApplIdx = 0;
                giRequestType = *(++pusReqSequence);
            } else if (giRequestType == API_GET_FUNCLIST) {
                if (++giApplIdx < usAppListCnt) {
                    // ApplId = pstAppList[giApplIdx].usApplId;
                    // 1175 55 3590 125 1070 1400 4582 2470 7050
                } else {
                    giRequestType = *(++pusReqSequence);
                }
            } else if (giRequestType == API_BANK_EFTTOTALS) {
                giRequestType = *(++pusReqSequence);
            } else if (giRequestType == API_BANK_EFTTRAN) {
                if (st_TrxnRespData.ucResult != '1') {
                    giRequestType = -1;
                } else {
                    giRequestType = *(++pusReqSequence);
                }
            } else {
                giRequestType = *(++pusReqSequence);
            }
            memset((char *) &ucRxBuf[0], 0, sizeof (ucRxBuf));
            iRxCnt = 0;
            if (giRequestType < 0) {
                OnlineTrxnResultProcessing();
                break;
            }

            ucReqDataReadyFlag = 1;
            usGprsTaskStep = 205;
            break;
    }
}













