
/* FLASH.H */

#include "system.h"


/*******************************************************************************
			Memory map of 8 MBytes program and data flash ROM   
********************************************************************************
Physical address: 0x40000000-0x407FFFFF (8 Mbytes) - cached address
Logical address : 0x30000000-0x307FFFFF (8 Mbytes) - none cached address

* Please use none cached address when you read/write data from/to flash ROM.
* The size of one sector is 64 KBytes.
* The total sector is 128.

=====================  =========================================================
Logical address        Contents
=====================  =========================================================
0x30000000-0x301FFFFF  Program area (2 MBytes)
---------------------  ---------------------------------------------------------
0x30200000-0x30201FFF  "POSSETUP.SYS" (8 KBytes) - parameter
0x30202000-0x3020FFFF  Reserved area for system (56 KBytes) - don't use this area
---------------------  ---------------------------------------------------------
0x30210000-0x3021FFFF  Reserved area for system (64 KBytes) - for compatibility with 128M Flash
---------------------  ---------------------------------------------------------
0x30220000-0x3029CFFF  "TRANSACTION.LOG" (500 KBytes)
                       512 bytes x 1,000 transaction records
0x3029D000-0x3029FFFF  Reserved area for system (12 KBytes) - don't use this area
---------------------  ---------------------------------------------------------
0x302A0000-0x3039FFFF  Free area for user (1 MBytes)
---------------------  ---------------------------------------------------------
0x303A0000-0x303BFFFF  Free area for user (128 KBytes)
EMV parameters & keys

	0x303A0000-0x303A7FFF TRMCAPK_DAT - 32K (TLV)
	0x303A8000-0x303ABFFF gcTrmRevocList 16K (TLV)
	0x303AC000-0x303ADFFF TRMCONF_DAT - 8K (TLV)
	0x303AE000-0x303AFFFF RFU - 8K

	0x303B0000-0x303B03FF eftparams & sessionkeys - 1K (struct)
	0x303B0400-0x303B05FF MasterKey - 512 (struct)
	0x303B0600-0x303B07FF SessionKey - 512 (struct)
	0x303B0800-0x303B0FFF params & sessionkeys - 2K (struct)
	0x303B1000-0x303B1FFF BinTables - 4K (struct)
	0x303B2000-0x303B5FFF AppList & FuncList - 16K (struct)
	0x303B6000-0x303BFFFF gcTrmExcepList(HOTCARD) - 40K (TLV)


#define FLASH8MB_NIBSS_TRMCAPK				0x303A0000L
#define FLASH8MB_NIBSS_REVOCLIST			0x303A8000L
#define FLASH8MB_NIBSS_TRMCONF				0x303AC000L
#define FLASH8MB_NIBSS_EFTPARAMS			0x303B0000L
#define FLASH8MB_NIBSS_MASTERKEY			0x303B0400L
#define FLASH8MB_NIBSS_SESSIONKEY			0x303B0600L
#define FLASH8MB_NIBSS_PARAMS				0x303B0800L
#define FLASH8MB_NIBSS_BINTABLES			0x303B1000L
#define FLASH8MB_NIBSS_APPFUNCLIST			0x303B2000L
#define FLASH8MB_NIBSS_EXCEPLIST			0x303B6000L
#define FLASH8MB_NIBSS_HOTCARD				FLASH8MB_NIBSS_EXCEPLIST


typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	char sz32Name[30];
	char sz128Url[128];
} FUNCLIST;

#define MAX_FUNCLIST_CNT	30

U16 usAppListCnt = 0;	// Power on 시 Flash에서 usMagicNo를 보고 count

typedef struct {
	U16 usMagicNo;							// 0000-0001	Magic number
	U16 usApplId;							// 0002-0003
	char sz32Name[32];						// 0004-0035
	char sz128Url[128];						// 0036-0163
	U32 ulFuncTime;							// 0164-0167
	U16 usDisabled;							// 0168-0169
	U16 usFuncListCnt;						// 0170-0171
	FUNCLIST stFuncList[MAX_FUNCLIST_CNT];	// 0172-4971	160 * 30 = 4800
	U08 RFU[148];							// 4972-5119	RFU
} APPLIST;

#define MAX_APPLIST_CNT		3
APPLIST stAppList[MAX_APPLIST_CNT];	// 15K

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	char sz9InfoDate[9];				// 0002-0010	EFT Param Information Date (YYYYMMDD)
	
	U16 usOnline;						// 0011-0012	ONLINE - Maximum of transactions that can be done offline before connecting online
	U32 ulMaxCashback;					// 0013-0016	MAXCASHBACK - Maximum amount allowed for cash back
	U16 usMinBudgetPeriod;				// 0017-0018	MINBUDGETPERIOD - Minimum budget months allowed
	U16 usMaxBudgetPeriod;				// 0019-0020	MAXBUDGETPERIOD - Maximum budget months allowed
	U32 ulBudgetMinAmount;				// 0021-0024	BUDGETMINAMOUNT - Minimum budget transaction amount allowed
	U32 ulVelocityTime;					// 0025-0028	VELOCITYTIME - Time allowed between transactions from same card
	U08 ucManualOnline;					// 0029-0029	MANUALONLINE - All manual transactions must be done online (Y/N)
	U32 ulUpdateBin;					// 0030-0033	UPDATEBIN - The terminal's bin tables require updating (Y/N)
	U32 ulUpdateHot;					// 0034-0037	UPDATEHOT - The terminal's hot card list requires updating (Y/N)
	U08 ucEodTxnList;					// 0038-0038	EODTXNLIST (Y/N)

	U08 ucMasterKey[32];				// 0039-0070
	U08 ucSessionKey[10][32];			// 0071-0390
	U08 ucMKFlag;						// 0391-0391
	U08 ucSKFlag[10];					// 0392-0401
	char Reserved[3692];				// 0402-4093	Reserved area
	U16 usSuffix;						// 4094-4095	Suffix
} EFTPARAM;

EFTPARAM stEftParam;	// 4K

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	U16 usIndex;						// 0002-0003	Index (0000-9999)
	U08 sz10Pan[10];					// 0004-0013	PAN - The prefix PAN number
	U08 ucLength;						// 0013-0013	LENGTH - The length of the full PAN
	U08 ucCardType;						// 0014-0014	CARDTYPE - The card type
	U32 ulFloor;						// 0015-0018	FLOOR - The minimum payment amount floor limit
	U16 usCheck;						// 0019-0020	CHECK - Binary based combination of check flags
										//				1.  0x0001 - Allowed
										//				2.  0x0002 - Force LUHN check
										//				3.  0x0004 - PIN required
										//				4.  0x0008 - Has card expiry date
										//				5.  0x0010 - Enforce velocity checks
										//				6.  0x0020 - Force online transaction
										//				7.  0x0040 - Use PIN Pad
										//				8.  0x0080 - Service Code
	U16 usAllow;						// 0021-0022	ALLOW - Binary based combination of allowed flags
										//				1.  0x0001 - Allow manual transaction
										//				2.  0x0002 - Allow refund
										//				3.  0x0004 - Allow reversal
										//				4.  0x0008 - Allow budget facility
										//				5.  0x0010 - Allow balance inquiry
										//				6.  0x0020 - Allow cash back
										//				7.  0x0040 - Allow card type
										//				8.  0x0080 - Allow authorization override
										//				9.  0x0100 - Authorization only
										//				10. 0x0200 - Prompt for account
										//				11. 0x0400 - Allow fleet transactions
										//				12. 0x0800 - Allow fuel transactions
	U08 ucKeyIndex;						// 0023-0023	KEYINDEX
	U08 RFU[8];							// 0024-0031	RFU
} BINTABLE;

#define MAX_BINTABLE_CNT	128
BINTABLE stBinTable[MAX_BINTABLE_CNT];	// 4K

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	U08 uc10Pan[10];					// 0002-0011	PAN - uc10Pan[0]: Length, uc10Pan[1~9]: The PAN number
	U08 RFU[4];							// 0012-0015	RFU
} HOTCARD;

#define MAX_HOTCARD_CNT		2560
HOTCARD stHotCard[MAX_HOTCARD_CNT];


---------------------  ---------------------------------------------------------
0x303C0000-0x303FFFFF  POSUTILINFO.SYS (256 KBytes) - POS utility information
---------------------  ---------------------------------------------------------
0x30400000-0x3041FFFF  "TMSBACKUP.DAT" (128 KBytes)
                       Compressed program downloading data backup area for
                       resumed downloading
---------------------  ---------------------------------------------------------
0x30420000-0x304DFFFF  "TMSAPP.ZIP" (768 kBytes)
                       Compressed program & uncompressed parameter downloading
                       area
---------------------  ---------------------------------------------------------
0x304E0000-0x304FFFFF  "TMSPOSSETUP.DAT" (128 KBytes)
                       Uncompressed parameter downloading area
---------------------  ---------------------------------------------------------
0x30500000-0x306FFFFF  "TMSAPP.DAT" (2 MBytes)
                       Uncompressing program area
---------------------  ---------------------------------------------------------
0x30700000-0x307FFFFF  Free area for user (1 MBbytes)
*******************************************************************************/

/*******************************************************************************
			Memory map of 16 MBytes program and data flash ROM   
********************************************************************************
Physical address: 0x40000000-0x40FFFFFF (16 Mbytes) - cached address
Logical address : 0x30000000-0x30FFFFFF (16 Mbytes) - none cached address

* Please use none cached address when you read/write data from/to flash ROM.
* The size of one sector is 128 KBytes.
* The total sector is 128.

=====================  =========================================================
Logical address        Contents
=====================  =========================================================
0x30000000-0x301FFFFF  Program area (2 MBytes)
---------------------  ---------------------------------------------------------
0x30200000-0x30201FFF  "POSSETUP.SYS" (8 KBytes) - parameter
0x30202000-0x3021FFFF  Reserved area for system (120 KBytes) - don't use this area
---------------------  ---------------------------------------------------------
0x30220000-0x3029CFFF  "TRANSACTION.LOG" (500 KBytes)
                       512 bytes x 1,000 transaction records
0x3029D000-0x3029FFFF  Reserved area for system (12 KBytes) - don't use this area
---------------------  ---------------------------------------------------------
0x302A0000-0x3039FFFF  Free area for user (1 MBytes)
---------------------  ---------------------------------------------------------
0x303A0000-0x303BFFFF  Free area for user (128 KBytes)
---------------------  ---------------------------------------------------------
0x303C0000-0x303FFFFF  POSUTILINFO.SYS (256 KBytes) - POS utility information
---------------------  ---------------------------------------------------------
0x30400000-0x3041FFFF  "TMSBACKUP.DAT" (128 KBytes)
                       Compressed program downloading data backup area for
                       resumed downloading
---------------------  ---------------------------------------------------------
0x30420000-0x304DFFFF  "TMSAPP.ZIP" (768 kBytes)
                       Compressed program & uncompressed parameter downloading
                       area
---------------------  ---------------------------------------------------------
0x304E0000-0x304FFFFF  "TMSPOSSETUP.DAT" (128 KBytes)
                       Uncompressed parameter downloading area
---------------------  ---------------------------------------------------------
0x30500000-0x306FFFFF  "TMSAPP.DAT" (2 MBytes)
                       Uncompressing program area
---------------------  ---------------------------------------------------------
0x30700000-0x307FFFFF  Free area for user (1 MBbytes)
---------------------  ---------------------------------------------------------
0x30800000-0x30FFFFFF  Free area for user (8 MBytes)
*******************************************************************************/

#define FLASH_START_ADDR							0x30000000L	// 0x30000000-0x307FFFFF: 8 Mbytes
																// 0x30000000-0x30FFFFFF: 16 Mbytes

#define MAX_TRANSACTION_LOG							1000L

#define TMSDOWN_PGM_UPGRADE_MIN_ADDR				0x30000000L

// for Flash 8 Mbytes
#define FLASH8MB_SECTOR_SIZE						0x10000L	// 64 Kytes

#define FLASH8MB_POS_SETUP_INFO_START_ADDR			0x30200000L	// 0x30200000-0x3020FFFF: 8 Kbytes(use) + 56 Kbytes(Reserved)

#define FLASH8MB_TRANSACTION_LOG_START_ADDR			0x30220000L	// 0x30220000-0x3029FFFF: 500 Kbytes(use) + 12 Kbytes(Reserved)
#define FLASH8MB_TRANSACTION_LOG_SECTOR_NO			8

// define flash 8MB POS Util parameters
#define FLASH8MB_POS_UTIL_INFO_MAX_SECTOR			4
#define FLASH8MB_POS_UTIL_INFO_MAX_RECORD_CNT		32			// (64 KB x 4 Sector) / 8 KB = 32
#define FLASH8MB_POS_UTIL_INFO_RECORD_SIZE			2000L		// 8 KBytes
#define FLASH8MB_POS_UTIL_INFO_MAGIC_NO				0x5B5B
#define FLASH8MB_POS_UTIL_INFO_VERSION				0x0001
#define FLASH16MB_POS_UTIL_INFO_SUFFIX				0xB55B
#define FLASH16MB_POS_UTIL_INFO_START_ADDR			0x303C0000L	// 0x303C0000-0x303FFFFF  POSUTILINFO.SYS (256 KBytes) - POS utility information

#define TMSDOWN_PGM_UPGRADE_FLASH8MB_MAX_ADDR		0x307FFFFFL	// 0x30000000-0x307FFFFF: 8 Mbytes

#define TMSDOWN_FLASH8MB_BACKUP_ADDR				0x30400000L	// 0x30400000-0x3041FFFF: 128 Kbytes (2Block)
#define TMSDOWN_FLASH8MB_ZIPPED_PGM_ADDR			0x30420000L	// 0x30420000-0x304DFFFF: 768 Kbytes (12Blocks)
#define TMSDOWN_FLASH8MB_PRARM_ADDR					0x304E0000L	// 0x304E0000-0x304FFFFF: 128 Kbytes (2Block)
#define TMSDOWN_FLASH8MB_UNZIPPED_PGM_ADDR			0x30500000L	// 0x30500000-0x306FFFFF:   2 Mbytes (32Blocks)
#define TMSDOWN_ZIPPED_APP_FLASH8MB_MAX_SIZE		0xC0000L	// 768 Kbytes
#define TMSDOWN_UNZIPPED_APP_FLASH8MB_MAX_SIZE		0x200000L	// 2 Mbytes


// for Flash 16 Mbytes
#define FLASH16MB_SECTOR_SIZE						0x20000L	// 128 Kytes

#define FLASH16MB_POS_SETUP_INFO_START_ADDR			0x30200000L	// 0x30200000-0x3021FFFF: 8 Kbytes(use) + 120 Kbytes(Reserved)

#define FLASH16MB_TRANSACTION_LOG_START_ADDR		0x30220000L	// 0x30220000-0x3029FFFF: 500 Kbytes(use) + 12 Kbytes(Reserved)
#define FLASH16MB_TRANSACTION_LOG_SECTOR_NO			4

// define flash POS Util parameters
#define FLASH16MB_POS_UTIL_INFO_MAX_SECTOR			2
#define FLASH16MB_POS_UTIL_INFO_MAX_RECORD_CNT		32			// (128 KB x 2 Sector) / 8 KB = 32
#define FLASH16MB_POS_UTIL_INFO_RECORD_SIZE			2000L		// 8 KBytes
#define FLASH16MB_POS_UTIL_INFO_MAGIC_NO			0x5B5B
#define FLASH16MB_POS_UTIL_INFO_VERSION				0x0001
#define FLASH16MB_POS_UTIL_INFO_SUFFIX				0xB55B
#define FLASH16MB_POS_UTIL_INFO_START_ADDR			0x303C0000L	// 0x303C0000-0x303FFFFF  POSUTILINFO.SYS (256 KBytes) - POS utility information

#define TMSDOWN_PGM_UPGRADE_FLASH16MB_MAX_ADDR		0x30FFFFFFL	// 0x30000000-0x30FFFFFF: 16 Mbytes

#define TMSDOWN_FLASH16MB_BACKUP_ADDR				0x30400000L	// 0x30400000-0x3041FFFF: 128 Kbytes ( 1 Block)
#define TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR			0x30420000L	// 0x30420000-0x304DFFFF: 768 Kbytes ( 6 Blocks)
#define TMSDOWN_FLASH16MB_PRARM_ADDR				0x304E0000L	// 0x304E0000-0x304FFFFF: 128 Kbytes ( 1 Block)
#define TMSDOWN_FLASH16MB_UNZIPPED_PGM_ADDR			0x30500000	// 0x30500000-0x306FFFFF:   2 Mbytes (16 Blocks)
#define TMSDOWN_ZIPPED_APP_FLASH16MB_MAX_SIZE		0xC0000L	// 768 Kbytes
#define TMSDOWN_UNZIPPED_APP_FLASH16MB_MAX_SIZE		0x200000L	// 2 Mbytes

// TMS Download Information Version
#define TMS_INFO_MAGIC_NO						(unsigned short)0xEDCE
#define TMS_INFO_VERSION						(unsigned short)0x0001
#define TMS_INFO_SUFFIX							(unsigned short)0xECDE


// common
#define TMSDOWN_PARAMETER_MAX_SIZE					8188		// 8188 bytes (8192 - 4 = 8188)
#define TMSDOWN_PARAMETER_MAX_PACKET_CNT			8			// 8 KBytes

#define POS_SETUP_INFO_MAGIC_NO						0x57AA		// POS setup information magic number
#define POS_SETUP_INFO_VERSION_NO					0x0001		// POS setup information version number
#define POS_SETUP_INFO_SUFFIX						0xAA75		// POS setup information suffix


/*******************************************************************************
				Memory map of 2 Mbytes battery backuped data SRAM
********************************************************************************
Physical address: 0x50000000-0x501FFFFF (2 MBytes)

System area     : 0x50000000-0x500FFFFF (1 MBytes)
User area       : 0x50100000-0x501FFFFF (1 MBytes)

======================  ========================================================
Physical address        Contents
======================  ========================================================
0x50000000-0x500FFFFF   System area (1 MBytes)
----------------------  --------------------------------------------------------
0x50100000-0x5011FFFF   Reserved area (128 KBytes)
----------------------  --------------------------------------------------------
0x50120000-0x5012FFFF   "FLASHBACKUPDATA.DAT" (64 KBytes)
                        Flash backup buffer
----------------------  --------------------------------------------------------
0x50130000-0x50130FFF   "FLASHBACKUPINFO.DAT" (4 KBytes, used: 128 Bytes)
                        Flash backup control buffer
----------------------  --------------------------------------------------------
0x50131000-0x501317FF   "TMSINFO.DAT" (2 KBytes)
                        TMS Downloading Information area
----------------------  --------------------------------------------------------
0x50131800-0x501FFFFF   Free area for user (826 KBytes)
*******************************************************************************/
#define SRAM_START_ADDR								0x50000000L	// 0x50000000-0x501FFFFF:   2 Mbytes

//#define SRAM_FLASH_BACKUP_ADDR						0x50100000L	// 0x50100000-0x5010FFFF:  64 Kbytes
//#define SRAM_FLASH_BACKUP_CONTROL_ADDR				0x50110000L	// 0x50110000-0x50110FFF:   4 Kbytes
#define SRAM_FLASH_BACKUP_ADDR						0x50120000L	// 0x50120000-0x5012FFFF:  64 Kbytes
#define SRAM_FLASH_BACKUP_CONTROL_ADDR				0x50130000L	// 0x50130000-0x50130FFF:   4 Kbytes

#define TMSDOWN_INFO_START_ADDR						0x50131000L	// 0x50131000-0x501317FF:   2 Kbytes
#define TMSDOWN_INFO_MAX_BLOCK						2


//#define BACKUP_CONTROL_INFO_MAX						32			// sizeof(_st_FlashBackupControlInfo_) * 32 = 128 * 32 = 4KB
#define BACKUP_CONTROL_INFO_MAX						2			// sizeof(_st_FlashBackupControlInfo_) * 32 = 128 * 32 = 4KB
#define BACKUP_CONTROL_INFO_MAGIC_NO				0x5A55AAA2L	// Backup control information magic number

#define FILE_ID_POS_SETUP							0x00000001L	// POS setup file identifier
#define FILE_ID_TRANSACTION							0x00000002L	// Transaction file identifier
#define FILE_ID_ERASE_TRXN_LOG						0x00000003L	// Erase Transaction Logs file identifier

#define BACKUP_CONTROL_INFO_SAVE_OK_FLAG			0xBBBBEEEEL	// Each Save OK Flag
#define BACKUP_CONTROL_INFO_SUFFIX					0xAAA25A55L	// Backup control information suffix

// TMS Download Information Version
//#define TMSDOWN_INFO_MAGIC_NO						(unsigned short)0x5E5E
//#define TMSDOWN_INFO_VERSION						(unsigned short)0x0001
//#define TMSDOWN_INFO_SUFFIX						(unsigned short)0xE5E5
#define TMSDOWN_INFO_MAGIC_NO						(unsigned short)0xE75E
#define TMSDOWN_INFO_VERSION						(unsigned short)0x0001
#define TMSDOWN_INFO_SUFFIX							(unsigned short)0xE57E



/* The data structure of POS setup information: 8 Kbytes (8192 bytes) */
typedef struct {
	U16 usMagicNo;								// 0000-0001	Magic number
	U16 usVersionNo;							// 0002-0003	POS Setup Information Version number
	char sz9InfoDate[9];						// 0004-0012	POS Setup Information Date (YYYYMMDD)
	
	char sz9TerminalID[9];						// 0013-0021	Terminal ID
	char sz16MerchantID[16];					// 0022-0037	Merchant ID
	char sz33StoreName[33];						// 0038-0070	Store name
	
	char sz13MasterPIN[13];						// 0071-0083	Master(Maintenance) PIN
	char sz13MerchantPIN[13];					// 0084-0096	Merchant PIN
	char sz13CashierPIN[13];					// 0097-0109	Cashier PIN
	
	U08 ucPOSActive;							// 0110			POS Active
	
	U08 ucBeep;									// 0111			0:Beep off, 1:Beep on
	U08 ucLCDContrast;							// 0112			default LCD contrast value is 25
	U08 ucMSRTrack3;							// 0113			0:Track 1&2, 1:Track 2&3
	
	U08 ucComDevice;							// 0114			0:Dialup Modem, 1:Ethernet, 2:GSM
	
	U08 ucModemSpeed;							// 0115			0:1200bps, 1:2400bps
	U08 ucSyncMode;								// 0116			0:Asynchronous, 1:Synchronous
	U08 ucConnectionStandard;					// 0117			0:CCITT, 1:Bell
	U08 ucBlindMode;							// 0118			0:Normal dialing, 1:Blind dialing
	U08 ucPulseDial;							// 0119			0:DTMF, 1:Pulse
	U08 ucDialingTimeout;						// 0120			Dialing timeout (sec)
	U08 ucCommTimeout;							// 0121			Communication timeout (sec)
	
	U08 ucPABXUse;								// 0122			0:Not use PABX, 1:Use PABX
	char sz6PABXCode[6];						// 0123-0128	PABX access code
	U08 ucCityUse;								// 0129			0:Not use city code, 1:Use city code
	char sz10CityCode[10];						// 0130-0139	City code
	char sz17TrxnTelNo[8][17];					// 0140-0275	Transaction telephone numbers
	
	U08 ucTMSPABXUse;							// 0276			0:Not use PABX, 1:Use PABX
	char sz6TMSPABXCode[6];						// 0277-0282	TMS PABX access code
	U08 ucTMSCityUse;							// 0283			0:Not use city code, 1:Use city code
	char sz10TMSCityCode[10];					// 0284-0293	TMS city code
	char sz17TMSTelNo[8][17];					// 0294-0429	TMS telephone numbers
	
	U08 ucEODPABXUse;							// 0430			0:Not use PABX, 1:Use PABX
	char sz6EODPABXCode[6];						// 0431-0436	EOD PABX access code
	U08 ucEODCityUse;							// 0437			0:Not use city code, 1:Use city code
	char sz10EODCityCode[10];					// 0438-0447	EOD city code
	char sz17EODTelNo[3][17];					// 0448-0498	EOD telephone numbers
	
	U08 ucBListPABXUse;							// 0499			0:Not use PABX, 1:Use PABX
	char sz6BListPABXCode[6];					// 0500-0505	Black List PABX access code
	U08 ucBListCityUse;							// 0506			0:Not use city code, 1:Use city code
	char sz10BListCityCode[10];					// 0507-0516	Black List city code
	char sz17BListTelNo[3][17];					// 0517-0567	Black List telephone numbers
	
	char sz16LocalIPAddress[16];				// 0568-0583	Local IP address
	char sz16SubnetMask[16];					// 0584-0599	Subnet Mask
	char sz16Gateway[16];						// 0600-0615	Gateway
	char sz6LocalPortNo[6];						// 0616-0621	Local port number (0-65535)
	char sz5LocalTimeout[5];					// 0622-0626	Local Timeout (0-600 sec)
	
	char sz16TrxnServerIP[2][16];				// 0627-0658	Transaction server IP address
	char sz6TrxnServerPortNo[2][6];				// 0659-0670	Transaction server port number (0-65535)
	
	char sz16TMSServerIP[2][16];				// 0671-0702	TMS server IP address
	char sz6TMSServerPortNo[2][6];				// 0703-0714	TMS server port number (0-65535)
	
	char sz16EODServerIP[2][16];				// 0715-0746	EOD server IP address
	char sz6EODServerPortNo[2][6];				// 0747-0758	EOD server port number (0-65535)
	
	char sz16BListServerIP[2][16];				// 0759-0790	Black List server IP address
	char sz6BListServerPortNo[2][6];			// 0791-0802	Black List server port number (0-65535)
	
	char sz17HelpDeskTelNo[4][17];				// 0803-0870	Help Desk telephone numbers
	
	char sz4MaxOfflineTrxnNo[4];				// 0871-0874	Maximum offline transaction number of consequent buys for one terminal
	char sz13MaxOfflineTrxnAmount[13];			// 0875-0887	Maximum offline transaction amount of consequent buys for one terminal
	
	char sz3NII[3];								// 0888-0890	NII
	
	U08 ucGsmDialingTimeout;					// 0891			GSM Dialing timeout (sec)
	char sz10GsmCityCode[10];					// 0892-0901	GSM City code
	char sz10GsmTMSCityCode[10];				// 0902-0911	GSM TMS city code
	char sz10GsmEODCityCode[10];				// 0912-0921	GSM EOD city code
	char sz10GsmBListCityCode[10];				// 0922-0931	GSM Black List city code
	
	U08 ucBuyActiveFlag;						// 0932			Buy Active Flag
	U08 ucBalanceActiveFlag;					// 0933			Balance Active Flag
	U08 ucBillPaymentActiveFlag;				// 0934			Bill Payment Active Flag
	U08 ucCheckBillPaymentActiveFlag;			// 0935			Check Bill Payment Active Flag
	U08 ucSIMChargeActiveFlag;					// 0936			SIM Charge Active Flag
	U08 ucBuyWithExtraActiveFlag;				// 0937			Buy With Extra Active Flag
	U08 ucBuyExtPrnActiveFlag;					// 0938			Buy With External Printer Active Flag
	U08 uc2TrxnRFUActiveFlag[2];				// 0939-0940	2 Transaction RFU Active Flag
	
	char sz33StoreAdvertisement[3][33];			// 0941-1039	Store Advertisement 1,2,3
	
	char ReservedA[38];							// 1040-1077	Reserved area
	
	U08 ucPreDialingFlag;						// 1078			Pre-dialing Flag

	U08 ucAutoTMSActiveFlag;					// 1079			Automatic TMS Active Flag

	/* sispp 20111013 */
	U08 ucGprsSIMNo;							// 1080
	char sz33GprsAPN[2][33];					// 1081-1146
	char sz33GprsUserName[2][33];				// 1147-1212
	char sz33GprsPassword[2][33];				// 1213-1278

	char sz5CallHomeInterval[5];				// 1279-1283
	char sz9Surcharge[9];						// 1284-1292
	
	char Reserved[6897];						// 1293-8189	Reserved area
	U16 usSuffix;								// 8190-8191	Suffix
} _st_POSSetupInfo_;

/* Total 256 Bytes */
/* If a variable type is short or unsigned short, it must be located even address(0, 2, 4, ...).
   If you assign a variable in odd address, it will be located the next address
   by Eclipse c compiler.
   If a variable type is long, unsigned long(0, 4, 8, ...), int or unsigned int, it must be
   located 4th address.
   If you don't assign a variable in 4th address, it will be located the next 4th
   address by Eclipse c compiler.
   Therefore data structure size will be changed. */
typedef struct
{															// Start End Address
	unsigned short usMagicNo;								// 0000-0001
	unsigned short usVersion;								// 0002-0003
	
	unsigned char ucApplicationNo;							// 0004
	unsigned char ucProgramNo;								// 0005
	char sz17ProgramVersion[17];							// 0006-0022
	char sz17SerialNo[17];									// 0023-0039
	char sz5ParameterVersion[5];							// 0040-0044
	char sz9ParameterDate[9];								// 0045-0053
	char sz9UpgradedDate[9];								// 0054-0062
	
	unsigned char ucAppDownNeedFlag;						// 0063
	unsigned char ucAppBackupOKFlag;						// 0064
	char cRFU01;											// 0065
	short sAppTotalSectorNo;								// 0066-0067
	unsigned short usAppTotalLRCData;						// 0068-0069
	short sAppCurrentSectorNo;								// 0070-0071
	short sAppWrittenSectorNo;								// 0072-0073
	short sRFU1;											// 0074-0075
	long lAppPgmUpgradeStartAddr;							// 0076-0079
	long lAppPgmTotalDataSize;								// 0080-0083
	long lAppParamTotalDataSize;							// 0084-0087
	long lAppReferenceNo;									// 0088-0091
	long lAppTotalDataSize;									// 0092-0095
	long lAppParamDataStartAddr;							// 0096-0099
	unsigned long ulUnzippedPgmSize;						// 0100-0103
	
	unsigned char ucParamDownNeedFlag;						// 0104
	char cRFU02;											// 0105
	short sParamTotalSectorNo;								// 0106-0107
	unsigned short usParamTotalLRCData;						// 0108-0109
	short sParamCurrentSectorNo;							// 0110-0111
	short sParamWrittenSectorNo;							// 0112-0113
	short sRFU02;											// 0114-0115
	long lParamTotalDataSize;								// 0116-0119
	
	char Reserved[134];										// 0120-0253
	
	unsigned short usSuffixFlag;							// 0254-0255
} _tTMS_DOWN_INFO;

// POS Util - 8192 bytes (8 Kbytes)
/* If a variable type is short or unsigned short, it must be located even address.
   If you assign a variable in odd address, it will be located the next address
   by Eclipse c compiler.
   If a variable type is long, unsigned long, int or unsigned int, it must be
   located 4th address.
   If you don't assign a variable in 4th address, it will be located the next 4th
   address by Eclipse c compiler.
   Therefore the size of data structure will be changed. */
typedef struct {
	U16 usMagicNo;								// 0000-0001	Magic Number
	U16 usVersion;								// 0002-0003	Version
	U16 usIndex;								// 0004-0005	Index (0001-9999)
	
	U16 usBatchNo;								// 0006-0007	Transaction Batch Number
	U16 usSeqNo;								// 0008-0009	Transaction Sequence Number

	U16 usReserved1;							// 0010-0011	Reserved for Future Use
	U32 ulLastCallHomeTime;						// 0012-0015	UL Time of Last Call Home
	char Reserved1[1008];						// 0016-1023	Reserved for Future Use
	
	_tTMS_DOWN_INFO tTMSDownloadInfo;			// 1024-1279	TMS Download Information
	
	char Reseverd2[6910];						// 1280-8189	Reserved for Future Use
	U16 usSuffix;								// 8190-8191	Suffix
} _tPOS_UTIL;

typedef struct {
	long lMinInfoAddr;							// Minimum POS util address of flash ROM
	long lMaxInfoAddr;							// Maximum POS util address of flash ROM
	_tPOS_UTIL *ptFirstLog;						// Pointer to first POS util address of flash ROM
	_tPOS_UTIL *ptLastLog;						// Pointer to last POS util address of flash ROM
	_tPOS_UTIL *ptSavingLog;					// Pointer to saving POS util address of flash ROM
	unsigned short usUtilIndex;					// POS util index
} _tPOS_UTIL_INFO;


/* The data structure of Flash backup control information: 64 bytes */
typedef struct {
	U32 ulMagicNo;								// 00-03	Magic number
	U32 ulFileID;								// 04-07	File ID
	U32 ulSaveAddr;								// 08-11	Save address
	U32 ulDataSize;								// 12-15	The size of data to will be saved
	U32 ulSaveBackupOKFlag;						// 16-19	Save Backup Data OK Flag
	U32 ulSaveRestoreOKFlag;					// 20-23	Save Restore Data OK Flag
	U32 ulBackupDataCheckSum;					// 24-27	Backup Data CheckSum
	U32 ulControlInfoCheckSum;					// 28-31	Control Info CheckSum
	char Reserved[28];							// 32-59	Reserved area
	U32 ulSuffix;								// 60-63	Suffix
} _st_FlashBackupControlInfo_;


//extern char FlashWriteBuf[65536];
extern char FlashWriteBuf[131072];
extern _st_POSSetupInfo_ st_POSSetupInfo;						// POS setup information buffer
extern _st_POSSetupInfo_ *stpFlashPOSSetupInfo;					// Pointer to POS setup information of flash ROM
extern _tPOS_UTIL_INFO tPOSUtilInfo;							// POS Util information
extern _tPOS_UTIL tPOSUtilBuf;									// POS Util buffer
extern int iFlashMemorySize;
extern int iFlashTrxnLogSectorNo;
extern long lFlashSectorSize;


// Convert Old POS Setup Info To New
extern void ConvertOldPOSSetupInfoToNew(void);

// Load POS Setup Information
extern void LoadPOSSetupInfo(void);

// Set Initial POS Setup Information
extern void SetInitialPOSSetupInfo(void);

// Initialize POS Setup Information
extern void InitializePOSSetupInfo(void);

// Reset POS Setup Information
extern void ResetPOSSetupInfo(void);

// Reset Merchant Password
extern void ResetMerchantPassword(void);

// Write POS Setup Information to flash ROM
extern void WritePOSSetupInfo(void);

extern BOOL GetTcpIPLocalParameterChange(void);

// Write Transaction Log
extern void WriteTransactionLog(char *dst);

// Erase All Transaction Log
extern void EraseAllTransactionLog(void);

extern int LoadFlashPOSUtilInfo(void);

extern void WritePOSUtil(void);

#ifdef USER_DEBUG
	extern void PauseUntilEnterkeyPressed();
#endif


#define FLASH8MB_NIBSS_TRMCAPK				0x303A0000L
#define FLASH8MB_NIBSS_REVOCLIST			0x303A8000L
#define FLASH8MB_NIBSS_TRMCONF				0x303AC000L
#define FLASH8MB_NIBSS_EFTPARAMS			0x303B0000L
#define FLASH8MB_NIBSS_MASTERKEY			0x303B0400L
#define FLASH8MB_NIBSS_SESSIONKEY			0x303B0600L
#define FLASH8MB_NIBSS_PARAMS				0x303B0800L
#define FLASH8MB_NIBSS_BINTABLES			0x303B1000L
#define FLASH8MB_NIBSS_APPFUNCLIST			0x303B2000L
#define FLASH8MB_NIBSS_EXCEPLIST			0x303B6000L
#define FLASH8MB_NIBSS_HOTCARD				FLASH8MB_NIBSS_EXCEPLIST

#define MAGICNO_APPLIST						0x55AA
#define MAGICNO_FUNCLIST					0x55AA
#define MAGICNO_MASTERKEY					0x55AA
#define MAGICNO_SESSIONKEY					0x55AA
#define MAGICNO_EFTPARAMS					0x55AA
#define MAGICNO_BINTABLE					0x55AA
#define MAGICNO_HOTCARD						0x55AA
#define MAGICNO_PARAMS						0x55AA

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	char sz32Name[30];
	char sz128Url[128];
} FUNCLIST;

#define MAX_FUNCLIST_CNT	30

typedef struct {
	U16 usMagicNo;							// 0000-0001	Magic number
	U16 usApplId;							// 0002-0003
	char sz32Name[32];						// 0004-0035
	char sz128Url[128];						// 0036-0163
	U32 ulFuncTime;							// 0164-0167
	U16 usDisabled;							// 0168-0169
	U16 usFuncListCnt;						// 0170-0171
	FUNCLIST stFuncList[MAX_FUNCLIST_CNT];	// 0172-4971	160 * 30 = 4800
	U08 RFU[148];							// 4972-5119	RFU
} APPLIST;

#define MAX_APPLIST_CNT		3

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	char sz10InfoDate[10];				// 0002-0011	EFT Param Information Date (YYYYMMDD)
	
	U16 usOnline;						// 0011-0012	ONLINE - Maximum of transactions that can be done offline before connecting online
	U08 ucDummy1[2];					// for byte align
	U32 ulMaxCashback;					// 0013-0016	MAXCASHBACK - Maximum amount allowed for cash back
	U16 usMinBudgetPeriod;				// 0017-0018	MINBUDGETPERIOD - Minimum budget months allowed
	U16 usMaxBudgetPeriod;				// 0019-0020	MAXBUDGETPERIOD - Maximum budget months allowed
	U32 ulBudgetMinAmount;				// 0021-0024	BUDGETMINAMOUNT - Minimum budget transaction amount allowed
	U32 ulVelocityTime;					// 0025-0028	VELOCITYTIME - Time allowed between transactions from same card
	U08 ucManualOnline;					// 0029-0029	MANUALONLINE - All manual transactions must be done online (Y/N)
	U08 ucDummy2[3];					// for byte align
	U32 ulUpdateBin;					// 0030-0033	UPDATEBIN - The terminal's bin tables require updating (Y/N)
	U32 ulUpdateHot;					// 0034-0037	UPDATEHOT - The terminal's hot card list requires updating (Y/N)
	U08 ucEodTxnList;					// 0038-0038	EODTXNLIST (Y/N)

	char Reserved[977];					// 0039-1021	Reserved area
	U16 usSuffix;						// 1022-1023	Suffix
} EFTPARAMS;

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	
	U08 ucMKFlag;						// 0002-0002
	U08 ucMasterKey[32];				// 0003-0034
	
	char Reserved[475];					// 0035-0509	Reserved area
	
	U16 usSuffix;						// 0510-0511	Suffix
} MASTERKEY;

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	
	U08 ucSKFlag[10];					// 0002-0011
	U08 ucSessionKey[10][32];			// 0012-0331
	
	char Reserved[178];					// 0332-0509	Reserved area
	
	U16 usSuffix;						// 0510-0511	Suffix
} SESSIONKEY;

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	
	U16 usDTyear;						// 0002-0003
	U08 ucDTsyear;						// 0004-0004
	U08 ucDTmon;						// 0005-0005
	U08 ucDTday;						// 0006-0006
	U08 ucDThour;						// 0007-0007
	U08 ucDTmin;						// 0008-0008
	U08 ucDTsec;						// 0009-0009
	U08 szMerchantID[17];				// 0010-0026
	U08 ucPinReset;						// 0027-0027
	U08 ucUpdateLogo;					// 0028-0028
	U08 ucUpdateMenu;					// 0029-0029
	U16 usReplyTimeout;					// 0030-0031
	U08 ucCurrency;						// 0032-0032
	U08 ucFract;						// 0033-0033
	U08 ucPrefix;						// 0034-0034
	U08 ucNegNum;						// 0035-0035
	U08 ucCurrCode[2];					// 0036-0037
	U08 ucDecSym;						// 0038-0038
	U08 ucThousSep;						// 0039-0039
	U08 ucCountryCode[2];				// 0040-0041
	U16 usEndofday;						// 0042-0043
	U32 ulUpdatePrompts;				// 0044-0047
	U08 ucAttendance;					// 0048-0048
	U08 ucAgentAccess;					// 0049-0049
	U08 ucEodtimeEn;					// 0050-0050
	U08 ucDownloadEn;					// 0055-0055
	U16 usConn1;						// 0051-0052
	U16 usConn2;						// 0053-0054
	U16 usDownloadConn;					// 0056-0057
	U08 ucDisabled;						// 0058-0058
	U08 szHeader[33];					// 0059-0091
	U08 szFooter[33];					// 0092-0124
	
	char Reserved[1921];				// 0125-2045	Reserved area
	
	U16 usSuffix;						// 2046-2047	Suffix
} PARAMS;

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	U16 usIndex;						// 0002-0003	Index (0000-9999)
	U08 sz10Pan[10];					// 0004-0013	PAN - The prefix PAN number
	U08 ucLength;						// 0014-0014	LENGTH - The length of the full PAN
	U08 ucCardType;						// 0015-0015	CARDTYPE - The card type
	U32 ulFloor;						// 0016-0019	FLOOR - The minimum payment amount floor limit
	U16 usCheck;						// 0020-0021	CHECK - Binary based combination of check flags
										//				1.  0x0001 - Allowed
										//				2.  0x0002 - Force LUHN check
										//				3.  0x0004 - PIN required
										//				4.  0x0008 - Has card expiry date
										//				5.  0x0010 - Enforce velocity checks
										//				6.  0x0020 - Force online transaction
										//				7.  0x0040 - Use PIN Pad
										//				8.  0x0080 - Service Code
	U16 usAllow;						// 0022-0023	ALLOW - Binary based combination of allowed flags
										//				1.  0x0001 - Allow manual transaction
										//				2.  0x0002 - Allow refund
										//				3.  0x0004 - Allow reversal
										//				4.  0x0008 - Allow budget facility
										//				5.  0x0010 - Allow balance inquiry
										//				6.  0x0020 - Allow cash back
										//				7.  0x0040 - Allow card type
										//				8.  0x0080 - Allow authorization override
										//				9.  0x0100 - Authorization only
										//				10. 0x0200 - Prompt for account
										//				11. 0x0400 - Allow fleet transactions
										//				12. 0x0800 - Allow fuel transactions
	U08 ucKeyIndex;						// 0024-0024	KEYINDEX
	U08 RFU[7];							// 0025-0031	RFU
} BINTABLE;

#define MAX_BINTABLE_CNT	128

typedef struct {
	U16 usMagicNo;						// 0000-0001	Magic number
	U16 usIndex;						// 0002-0003	Index (StartAt + Count)
	U08 uc12Pan[12];					// 0004-0015	PAN - uc12Pan[0]: Length, uc12Pan[1~11]: The PAN number
} HOTCARD;

#define MAX_HOTCARD_CNT		2560

typedef struct {
	U16 usMagicNo;
	U16 usIndex;
	U08 ucAID[16];
	U08 ucAppLabel[32];
	U08 ucAppVer[4];
	U08 ucDDOL[64];
	U08 ucTDOL[64];
	U08 ucTFLDom[8];
	U08 ucTFLInt[8];
	U08 ucThresholdDom[4];
	U08 ucThresholdInt[4];
	U08 ucMaxTargetDom;
	U08 ucMaxTargetInt;
	U08 ucTargetPercentDom;
	U08 ucTargetPercentInt;
	U08 ucTACdefault[10];
	U08 ucTACdenial[10];
	U08 ucTAConline[10];
} EMVAPP;

typedef struct {
	U08 ucRID[5];				// RID  : 5 bytes
	U08 ucIndex;				// Index: 1 byte
	U08 ucCSN[3];				// CSN  : 3 bytes
	U08 ucExponent[4];			// exponent: 4 byte
	U08 ucBits[2];				// bits : 2 byte
	U08 ucModulus[256];			// modulus = (bits+7)/8
	U08 ucPkAlgo;				// PkAlgo: 1 byte
	U08 ucHash[65];				// Hash : Len(1)+Hash(64)
	U08 ucHashAlgo;				// HashAlgo: 1 byte
} EMVCAPK;

typedef struct {
	U08 ucRID[5];				// RID  : 5 bytes
	U08 ucIndex;				// Index: 1 byte
	U08 ucCSN[3];				// CSN  : 3 bytes
} EMVREVOKECAPK;


extern APPLIST stAppList[MAX_APPLIST_CNT];
extern APPLIST *pstAppList;
extern FUNCLIST *pstFuncList;
extern EFTPARAMS stEftParams;
extern MASTERKEY stMasterKey;
extern MASTERKEY *pstMasterKey;
extern SESSIONKEY stSessionKey;
extern PARAMS stParams;
extern PARAMS *pstParams;
extern BINTABLE stBinTable[MAX_BINTABLE_CNT];
extern BINTABLE *pstBinTable;
extern HOTCARD stHotCard[MAX_HOTCARD_CNT];
extern HOTCARD *pstHotCard;
extern EMVAPP stEmvApp;
extern EMVCAPK stEmvCapk;
extern EMVREVOKECAPK stEmvRevokeCapk;

extern U16 usAppListCnt;
extern U16 usBinTableCnt;
extern U16 usHotCardsCnt;

/* */
