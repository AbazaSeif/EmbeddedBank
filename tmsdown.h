
/*======================================================================*/
/*																		*/
/*								TMSDOWN.H								*/
/*																		*/
/*======================================================================*/

#include "system.h"


// Application Number
#define TMSDOWN_APPLICATION_NO								0

// Program Number of remote downloading
#ifndef SDRAM_VERSION
#define TMSDOWN_PRGOGRAM_NO									1
#else
#define TMSDOWN_PRGOGRAM_NO									11
#endif

// define TMS Communication Time out
#define TMSDOWN_ENQ_WAIT_MAX_TIME							3000		// 30 sec
#define TMSDOWN_HEAD_INFO_RESPONSE_WAIT_MAX_TIME			1200		// 12 sec
#define TMSDOWN_DATA_PACKET_RESPONSE_WAIT_MAX_TIME			1500		// 15 sec

// define TMS Communication Error Maximum Retry Counter
#define TMSDOWN_ERROR_MAX_RETRY							3

// define TMS Auto Downloading Time interval
#define TMSDOWN_AUTO_DOWNLOAD_TIME							180L		// 3 min



extern int iTMSDownInfoBlockIndex;
extern _tTMS_DOWN_INFO tTMSDownloadInfo;					// TMS downloading information buffer

extern long lTMSAutoDownloadTried1SECTimer;
extern long lTMSDownlaodDataPacketMaxBytes;
extern short sTMSDownlaodDataPacketSize;
extern short sTMSDownlaodClusterNoPerSector;
extern short sTMSDownloadSectorNo;
extern unsigned short usTMSDownload10MSTimer;
extern unsigned char ucTMSDownloadFlag;
extern unsigned char ucTMSDownloadRetryCnt;
extern unsigned char ucAutoTMSDownloadDateFlag;
extern unsigned char ucAutoTMSDownloadFirstFlag;
extern unsigned char ucAutoTMSDownloadTimeFlag;


// TMS Download Task
extern void TMSDownloadTask(char com_device, char com_port);

// Clear TMS Download Buffer and Rx Buffer
extern void ClearTMSDownloadBufAndRxBuf(char inc_retry_cnt_flag);

// Set TMS Variables
extern void SetTMSVariables(void);

extern void LoadTMSDownloadInfo(void);
extern void InitializeTMSDownloadInfo(void);
extern void SaveTMSDownloadInfo(void);
extern void SetInitialValueToTMSDownloadInfo(void);
extern void EraseAllDataTMSDownloadInfo(void);
extern int LoadTMSDownloadSectorNo(void);
extern void CheckTMSUpgrade(void);
extern void UpgradeApplication(void);
extern void EraseAppDataTMSDownloadInfo(void);
extern void UpgradePOSParameter(int mode);

extern void WriteApplicationOrParameter1Sector(int mode);

extern void BackupOrRestoreAppDownloadData(int mode, int sector_no);

extern long GetZippedAppFlashSectorTopAddr(int sector_no);

extern void CheckAutoTMSDownloadStart(void);

extern BOOL GetAutoTMSDownloadingDate(void);

#ifdef USER_DEBUG
	extern void Output_TMSDownloadInfo(void);
#endif

/* */
