
/*======================================================================*/
/*																		*/
/*								GSM.H									*/
/*																		*/
/*======================================================================*/

// GSM/GPRS modem

//#define TEST_OFFLINE
/*
#define SISPP_TEST
#ifdef SISPP_TEST
#define GPRS_COM_PORT								COM0	// Internal Serial Port
#else
#define GPRS_COM_PORT								COM1	// Internal Serial Port
#endif
*/
#define GPRS_COM_PORT								COM1	// Internal Serial Port

#define WAVECOM_Q24PLUS								0
#define WAVECOM_Q2686								1
#define CINTERION_BG2								2

#define GPRS_MAX_CMD_RETRY							3
#define GPRS_MAX_CONNECT_COUNT						2
#define GPRS_MAX_DISCONNECT_RETRY					1
#define GPRS_RECONNECTING_PAUSE_TIME				200		// 2 sec

#define P_RF_MODULE									2
#define P_SMART_CARD								3
#define P_EXT_SERIAL								4

#define SIM_CHECK									0		// ME is checking the SIM
#define SIM_READY									1		// ME is not pending for any password (SIM is ready)
#define SIM_FAILURE									2		// SIM not inserted or failure
#define SIM_BLOCK									3		// SIM is blocked
#define SIM_PIN										4		// CHV1 is required
#define SIM_PUK										5		// PUK1 is required
#define SIM_PIN2									6		// CHV2 is required
#define SIM_PUK2									7		// PUK2 is required
#define PH_SIM_PIN									8		// SIM lock (phone-to-SIM) is required
#define PH_NET_PIN									9		// Network personalization PIN required
#define PH_NET_PUK									10		// Network personalization PUK required
#define PH_NET_SUB_PIN								11		// Network subset personalization PIN required
#define PH_NET_SUB_PUK								12		// Network subset personalization PUK required
#define PH_SVC_PROVIDER_PIN							13		// Service provider personalization PIN required
#define PH_SVC_PROVIDER_PUK							14		// Service provider personalization PUK required
#define PH_CORPORATE_PIN							15		// Corporate personalization PIN required
#define PH_CORPORATE_PUK							16		// Corporate personalization PUK required
#define PH_SIM_PUK									17		// PH-SIM PUK (master phone code) required


#define GPRS_ANTENNA_LEVEL_1_LIMIT					4		// <= -105dBm
#define GPRS_ANTENNA_LEVEL_2_LIMIT					10		// <= -93dBm
#define GPRS_ANTENNA_LEVEL_3_LIMIT					14		// <= -85dBm
#define GPRS_ANTENNA_LEVEL_4_LIMIT					19		// <= -75dBm


#ifdef USER_DEBUG
#if 0
typedef struct {
	short error_code;
	char error_msg[128];
} CMES_T;


extern const CMES_T CME_ERROR_CODE[];
extern const CMES_T CMS_ERROR_CODE[];
#endif
#endif


// GSM
extern unsigned short usGprsTaskStep;				// GSM task step
extern unsigned short usGprs10MSMaxTimeout;			// GSM 10ms maximum timeout
extern unsigned short usGprs10MSTimer;				// GSM 10ms timer
extern unsigned char ucGprsModuleOkFlag;			// GSM module OK flag (0: GSM module doesn't response, 1: GSM module is OK)
extern unsigned char ucGsmSerialMode;				// GSM serial mode  (0: 8bits none, 1: 7bits even)
extern unsigned char ucGprsGsmModel;				// GSM model
extern unsigned char ucGprsCmdRetryCnt;				// GSM command retry counter
extern unsigned char ucGprsMaxConnectCnt;			// GSM maximum connection counter
extern unsigned char ucGprsConnectCnt;				// GSM connection counter
extern unsigned char ucGprsPowerOffFlag;			// GSM power off flag
extern unsigned char ucGprsSIMCheckedFlag;			// GSM SIM checked flag
extern unsigned char ucGprsSIMStatus;				// GSM SIM status
extern unsigned char ucGsmNetworkRegistrationMode;	// GSM network registration mode
extern unsigned char ucGprsRssiValue;				// GSM RSSI value
extern unsigned char ucGprsBerValue;				// GSM BER value
extern unsigned char ucGprsRssiRetryCnt;			// GSM Check Signal Quality retry counter
extern unsigned char ucGprsRegistrationStatus;		// GSM registration status
extern unsigned char ucGprsRegistrationRetryCnt;	// GSM Check the registration status retry counter

extern int giTransactionType;


/* Open GSM */
extern void GprsOpen(void);

/*
GSM Power On
	Input
		sim_slot_no
			0 or 1
*/
extern void GprsPowerOn(unsigned char sim_slot_no);

/* GSM Power Off */
extern void GprsPowerOff(void);

/*
Transmit data to RS232 port for GSM
	Input
		stream
			pointer of stream
		size
			the length of stream
*/
extern void GprsCmdModeWrite(char *stream, int size);

/*
Transmit data in command mode to RS232 port for GSM and set response timeout
	Input
		time_out
			response timeout
*/
extern void GprsSendCmdSetTime(unsigned short time_out);

extern void GprsDisplaySIMErrorMessage(void);

/*
Display antenna level bar for GSM
	Input
		rssi
			the received signal strength indication
*/
extern void GprsDisplayAntennaLevelBar(unsigned char rssi);

/* GSM task */
extern void GprsTask(void);

/* Disconnect GSM */
extern void GprsDisconnect(int iMode);

/* Initialize GSM module */
extern void GprsModuleInitialize(void);

/* */
