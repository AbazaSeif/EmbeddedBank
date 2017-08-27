
/*======================================================================*/
/*																		*/
/*								TMSDOWN.C								*/
/*																		*/
/*======================================================================*/

#include "system.h"
#include "extern.h"


int iTMSDownInfoBlockIndex;
_tTMS_DOWN_INFO tTMSDownloadInfo; // TMS downloading information buffer

long lTMSAutoDownloadTried1SECTimer;
long lTMSDownlaodDataPacketMaxBytes;
short sTMSDownlaodDataPacketSize;
short sTMSDownlaodClusterNoPerSector;
short sTMSDownloadSectorNo;
unsigned short usTMSDownload10MSTimer;
unsigned char ucTMSDownloadFlag;
unsigned char ucTMSDownloadRetryCnt;
unsigned char ucAutoTMSDownloadDateFlag;
unsigned char ucAutoTMSDownloadFirstFlag;
unsigned char ucAutoTMSDownloadTimeFlag;

void TMSDownloadTask(char com_device, char com_port);
void ClearTMSDownloadBufAndRxBuf(char inc_retry_cnt_flag);
void SetTMSVariables(void);
void SaveTMSDownloadInfo(void);
void WriteApplicationOrParameter1Sector(int mode);
void BackupOrRestoreAppDownloadData(int mode, int sector_no);
long GetZippedAppFlashSectorTopAddr(int sector_no);
void CheckAutoTMSDownloadStart(void);
BOOL GetAutoTMSDownloadingDate(void);
#ifdef USER_DEBUG
void Output_TMSDownloadInfo(void);
#endif



// TMS Download Task

void TMSDownloadTask(char com_device, char com_port) {
    long ltemp;
    short i, j, ret;
    char country_code[5];
    char svc_compay_code[5];
    char terminal_maker_code[5];
    char model_name[17];
    char download_addr[17];
    char temp[17];

    if (iTMS_ProcessStep <= 0) {
        return;
    }

    /*
    TMS processing
            Input
                    com_device
                            0: Dial-up modem
                            1: Ethernet
                    com_port
                            serial communication port for TMS
		
            Output
     *rx_buf
                            received data from TMS server
		
            Return Codes
               0: Polling
               1: Received ENQ
               2: Received first character
               3: Received program (and parameter) downloading information
               4: Received parameter downloading information
               5: Received data packet
               6: Received End of communication command
              -1: Rx data LRC error
              -2: Rx data packet LRC error
              -3: Received Tx data LRC error code
              -4: Received Command error code
             -99: Received error message
            -999: "NO CARRIER"
     */
    ret = TMS_Process(com_device, com_port, (char *) ucRxBuf);
    if (iTMS_ProcessStep >= 3 && ret == -999) {
        // "No Carrier      ",
        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1NoCarrierError_001], ucLangFlag);
#ifdef USER_DEBUG
        Rprintf("\r\nNO CARRIER\r\n");
#endif
        iTMS_ProcessStep = 9999;
        return;
    }

    switch (iTMS_ProcessStep) {
        case 1: // Dialing
            ModemOpen(NORMAL_CONNECTION);
            iTMS_ProcessStep++;
            break;
        case 2: // Wait for connection
            break;

        case 3: // Wait for <ENQ>
            if (TIMER_GetElapsed10MSTime(usTMSDownload10MSTimer) >= TMSDOWN_ENQ_WAIT_MAX_TIME) {
#ifdef USER_DEBUG
                Rprintf("\r\nTimeout - <ENQ>\r\n");
#endif
                // " Download Error ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadError_0001], ucLangFlag);
                iTMS_ProcessStep = 9999;
                break;
            }

            if (ret == 1) {
#ifdef USER_DEBUG
                Rprintf("\r\nReceived <ENQ>\r\n");
#endif
                // " Received <ENQ> ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReceivedENQ_000001], ucLangFlag);
                ClearTMSDownloadBufAndRxBuf(0);
                iTMS_ProcessStep = 10;
            }
            break;

        case 10: // Send Resume program (and parameter) or Parameter downloading command
            if (ucTMSDownloadRetryCnt < TMSDOWN_ERROR_MAX_RETRY) {
#ifdef USER_DEBUG
                Rprintf("\r\nSend Resume program (and parameter) or Parameter downloading command\r\n");
#endif
                tTMSDownloadInfo.ucApplicationNo = TMSDOWN_APPLICATION_NO;
                tTMSDownloadInfo.ucProgramNo = TMSDOWN_PRGOGRAM_NO;
                strcpy(tTMSDownloadInfo.sz17ProgramVersion, sz17TMSSWVersion);
                memset(temp, 0x00, sizeof (temp));
                if (GET_PROD_ID(temp) == 0) { // BNI51111200001
                    strcpy(tTMSDownloadInfo.sz17SerialNo, temp);
                } else {
                    strcpy(tTMSDownloadInfo.sz17SerialNo, st_POSSetupInfo.sz9TerminalID);
                }
                sprintf(tTMSDownloadInfo.sz5ParameterVersion, "%04X", st_POSSetupInfo.usVersionNo);
                strcpy(tTMSDownloadInfo.sz9ParameterDate, st_POSSetupInfo.sz9InfoDate);

                strcpy(country_code, "0364"); // Country				: IRAN
                strcpy(svc_compay_code, "0002"); // Service Company		: BMI
                strcpy(terminal_maker_code, "0001"); // Terminal Maker		: BITEL
                strcpy(model_name, sz17TRMModelName); // Terminal Model Name
                strcpy(download_addr, "0000000000000000");

                SaveTMSDownloadInfo();
#ifdef USER_DEBUG
                //Output_TMSDownloadInfo();
                Rprintf("sTMSDownloadSectorNo                     = %d\r\n", sTMSDownloadSectorNo);
#endif
                ClearTMSDownloadBufAndRxBuf(1);
                TMS_SendResumePgmParamDownload(tTMSDownloadInfo.ucProgramNo,
                        country_code, svc_compay_code,
                        terminal_maker_code, model_name,
                        tTMSDownloadInfo.sz17SerialNo,
                        st_POSSetupInfo.sz16MerchantID,
                        tTMSDownloadInfo.sz17ProgramVersion,
                        sz6BIOSVersion, sz17HWInfo, download_addr,
                        tTMSDownloadInfo.sz5ParameterVersion,
                        tTMSDownloadInfo.sz9ParameterDate,
                        tTMSDownloadInfo.lAppReferenceNo,
                        sTMSDownloadSectorNo);
                iTMS_ProcessStep++;
                break;
            }

#ifdef USER_DEBUG
            Rprintf("\r\nDownload Error\r\n");
#endif
            // " Download Error ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadError_0001], ucLangFlag);
            iTMS_ProcessStep = 9999;
            break;
        case 11: // Wait for response of Resume program (and parameter) or Parameter downloading command
            if (TIMER_GetElapsed10MSTime(usTMSDownload10MSTimer) >= TMSDOWN_HEAD_INFO_RESPONSE_WAIT_MAX_TIME) {
#ifdef USER_DEBUG
                Rprintf("\r\nTimeout - Wait for response of Resume program (and parameter) or Parameter downloading command\r\n");
#endif
                iTMS_ProcessStep--;
                break;
            }

            if (ret == 2) {
#ifdef USER_DEBUG
                Rprintf("\r\nReceiving Data..\r\n");
#endif
                // "RECEIVING DATA..",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReceivingData_0001], ucLangFlag);
            } else if (ret == 3) {
#ifdef USER_DEBUG
                Rprintf("\r\nResume program (and parameter) downloading\r\n");
#endif
                LCD_ClearScreen();
                // "PROGRAM DOWNLOAD",
                LCD_DisplayLine(0, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmDownload_000001], ucLangFlag);
                LCD_HighlightLineOn(0);

                if (iFlashMemorySize < 16) {
                    ltemp = TMSDOWN_ZIPPED_APP_FLASH8MB_MAX_SIZE;
                } else {
                    ltemp = TMSDOWN_ZIPPED_APP_FLASH16MB_MAX_SIZE;
                }
                if ((lTMS_PGMPARAMPgmTotalDataSize + lTMS_PGMPARAMParamTotalDataSize) > ltemp) {
#ifdef USER_DEBUG
                    Rprintf("\r\nFile Size overflow\r\n");
#endif
                    // "Download File   ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1FileSizeOver_00001], ucLangFlag);
                    // "Size Over!      ",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1FileSizeOver_00002], ucLangFlag);
                    iTMS_ProcessStep = 9999;
                    return;
                }

                if (iFlashMemorySize < 16) {
                    ltemp = TMSDOWN_PGM_UPGRADE_FLASH8MB_MAX_ADDR;
                } else {
                    ltemp = TMSDOWN_PGM_UPGRADE_FLASH16MB_MAX_ADDR;
                }
                if (lTMS_PGMPARAMPgmUpgradeStartAddr < TMSDOWN_PGM_UPGRADE_MIN_ADDR || lTMS_PGMPARAMPgmUpgradeStartAddr > ltemp) {
#ifdef USER_DEBUG
                    Rprintf("\r\nProgram Start Address Error!\r\n");
#endif
                    // "Program Upgrade ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmUpgadeAddrErr_1], ucLangFlag);
                    // "Address Error!  ",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmUpgadeAddrErr_2], ucLangFlag);
                    iTMS_ProcessStep = 9999;
                    return;
                }

                if (lTMS_PGMPARAMParamTotalDataSize > TMSDOWN_PARAMETER_MAX_SIZE) {
#ifdef USER_DEBUG
                    Rprintf("\r\nParameter Size overflow\r\n");
#endif
                    // "Parameter size  ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ParamSizeOver_0001], ucLangFlag);
                    // "Over!           ",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ParamSizeOver_0002], ucLangFlag);
                    iTMS_ProcessStep = 9999;
                    return;
                }

                tTMSDownloadInfo.ucAppDownNeedFlag = 1;
                if (tTMSDownloadInfo.lAppReferenceNo != lTMS_PGMPARAMReferenceNo) {
                    tTMSDownloadInfo.sAppCurrentSectorNo = 0;
                    tTMSDownloadInfo.sAppWrittenSectorNo = -1;
                }
                tTMSDownloadInfo.lAppPgmUpgradeStartAddr = lTMS_PGMPARAMPgmUpgradeStartAddr;
                tTMSDownloadInfo.lAppPgmTotalDataSize = lTMS_PGMPARAMPgmTotalDataSize;
                tTMSDownloadInfo.lAppParamTotalDataSize = lTMS_PGMPARAMParamTotalDataSize;
                tTMSDownloadInfo.sAppTotalSectorNo = sTMS_PGMPARAMTotalSectorNo;
                tTMSDownloadInfo.usAppTotalLRCData = usTMS_PGMPARAMTotalLRCData;
                tTMSDownloadInfo.lAppReferenceNo = lTMS_PGMPARAMReferenceNo;
                tTMSDownloadInfo.lAppParamDataStartAddr = 0L;
                tTMSDownloadInfo.ulUnzippedPgmSize = 0L;

                // Reset Parameter downloading variables
                tTMSDownloadInfo.ucParamDownNeedFlag = 0;
                tTMSDownloadInfo.sParamTotalSectorNo = 0;
                tTMSDownloadInfo.usParamTotalLRCData = 0;
                tTMSDownloadInfo.sParamCurrentSectorNo = 0;
                tTMSDownloadInfo.sParamWrittenSectorNo = -1;
                tTMSDownloadInfo.lParamTotalDataSize = 0L;

                SaveTMSDownloadInfo();
#ifdef USER_DEBUG
                //Output_TMSDownloadInfo();
#endif
                if (tTMSDownloadInfo.sAppCurrentSectorNo != tTMSDownloadInfo.sAppWrittenSectorNo) {
                    j = tTMSDownloadInfo.sAppCurrentSectorNo;
                } else {
                    j = tTMSDownloadInfo.sAppCurrentSectorNo + 1;
                }
                sprintf(temp, "%d/%d [%d%%]",
                        j,
                        tTMSDownloadInfo.sAppTotalSectorNo,
                        (unsigned int) (j * 100) / tTMSDownloadInfo.sAppTotalSectorNo);
                LCD_DisplayLine(3, CENTER_JUSTIFIED, temp, ucLangFlag);
#ifdef USER_DEBUG
                Rprintf("\r\n%s\r\n", temp);
#endif
                ClearTMSDownloadBufAndRxBuf(0);
                iTMS_ProcessStep = 20;
            } else if (ret == 4) {
#ifdef USER_DEBUG
                Rprintf("\r\nParameter downloading\r\n");
#endif
                // "Sorry, it does  ", "not support     ", "parameter       ", "upgrade now     "
                LCDDisplay4Lines(M4NotSupportParam_01, -1, ucLangFlag);
                EraseAllDataTMSDownloadInfo();
                iTMS_ProcessStep = 9999;
                return;

                LCD_ClearScreen();
                // "PARAMETER DOWN  ",
                LCD_DisplayLine(0, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ParamDownload_0001], ucLangFlag);
                LCD_HighlightLineOn(0);

                if (sTMS_PARAMTotalSectorNo > ((TMSDOWN_PARAMETER_MAX_PACKET_CNT + sTMSDownlaodDataPacketSize - 1) / sTMSDownlaodDataPacketSize)) {
#ifdef USER_DEBUG
                    Rprintf("\r\nFile Size overflow\r\n");
#endif
                    // "Parameter size  ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ParamSizeOver_0001], ucLangFlag);
                    // "Over!           ",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ParamSizeOver_0002], ucLangFlag);
                    iTMS_ProcessStep = 9999;
                    return;
                }

                // Reset Resume program (and parameter) downloading variables
                tTMSDownloadInfo.ucAppDownNeedFlag = 0;
                tTMSDownloadInfo.ucAppBackupOKFlag = 0;
                tTMSDownloadInfo.sAppTotalSectorNo = 0;
                tTMSDownloadInfo.usAppTotalLRCData = 0;
                tTMSDownloadInfo.sAppCurrentSectorNo = 0;
                tTMSDownloadInfo.sAppWrittenSectorNo = -1;
                tTMSDownloadInfo.lAppPgmUpgradeStartAddr = 0L;
                tTMSDownloadInfo.lAppPgmTotalDataSize = 0L;
                tTMSDownloadInfo.lAppParamTotalDataSize = 0L;
                tTMSDownloadInfo.lAppReferenceNo = 0L;
                tTMSDownloadInfo.lAppTotalDataSize = 0L;
                tTMSDownloadInfo.lAppParamDataStartAddr = 0L;
                tTMSDownloadInfo.ulUnzippedPgmSize = 0L;

                tTMSDownloadInfo.ucParamDownNeedFlag = 1;
                tTMSDownloadInfo.sParamTotalSectorNo = sTMS_PARAMTotalSectorNo;
                tTMSDownloadInfo.usParamTotalLRCData = usTMS_PARAMTotalLRCData;
                sTMS_PARAMCurrentSectorNo = 0;
                tTMSDownloadInfo.sParamCurrentSectorNo = sTMS_PARAMCurrentSectorNo;
                tTMSDownloadInfo.sParamWrittenSectorNo = -1;
                tTMSDownloadInfo.lParamTotalDataSize = 0L;

                SaveTMSDownloadInfo();
#ifdef USER_DEBUG
                //Output_TMSDownloadInfo();
#endif
                sprintf(temp, "%d/%d [%d%%]", 0, sTMS_PARAMTotalSectorNo, 0);
                LCD_DisplayLine(3, CENTER_JUSTIFIED, temp, ucLangFlag);
#ifdef USER_DEBUG
                Rprintf("\r\n%s\r\n", temp);
#endif
                ClearTMSDownloadBufAndRxBuf(0);
                iTMS_ProcessStep = 120;
            } else if (ret == -1) {
#ifdef USER_DEBUG
                Rprintf("\r\nRx LRC Error !\r\n");
#endif
                // " Rx LRC Error ! ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1RxLRCError_0000001], ucLangFlag);
                iTMS_ProcessStep--;
            } else if (ret == -3) {
#ifdef USER_DEBUG
                Rprintf("\r\nTx LRC Error !\r\n");
#endif
                // " Tx LRC Error ! ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1TxLRCError_0000001], ucLangFlag);
                iTMS_ProcessStep--;
            } else if (ret == -4) {
#ifdef USER_DEBUG
                Rprintf("\r\nCommand Error !\r\n");
#endif
                // "Command Error ! ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1CommandError_00001], ucLangFlag);
                iTMS_ProcessStep--;
            } else if (ret == -99) {
#ifdef USER_DEBUG
                Rprintf("\r\n%s\r\n", sz65TMS_ErrorMsg);
#endif
                // Error Message Display
                LCD_ClearScreen();
                j = strlen(sz65TMS_ErrorMsg);
                for (i = 0; i < 4; i++) {
                    LCD_DisplayLine(i, LEFT_JUSTIFIED, &sz65TMS_ErrorMsg[i * 16], ucLangFlag);
                    if (j <= 16) {
                        j -= 16;
                        if (j <= 0) {
                            break;
                        }
                    }
                }

                EraseAllDataTMSDownloadInfo();
                iTMS_ProcessStep = 9999;
            }
            break;

        case 20: // Send Start Communication command (Resume program (and parameter) downloading)
        case 120: // Send Start Communication command (Parameter downloading)
        case 30: // Send <ACK> of Data packet command (Resume program (and parameter) downloading)
        case 130: // Send <ACK> of Data packet command (Parameter downloading)
        case 31: // Send <NAK> of Data packet command (Resume program (and parameter) downloading)
        case 131: // Send <NAK> of Data packet command (Parameter downloading)
            if (ucTMSDownloadRetryCnt < TMSDOWN_ERROR_MAX_RETRY) {
                if (iTMS_ProcessStep == 20 || iTMS_ProcessStep == 120) {
#ifdef USER_DEBUG
                    Rprintf("\r\nSend Start communication command\r\n");
#endif
                    // "Send COMM Start ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SendCommStart_0001], ucLangFlag);
                    ClearTMSDownloadBufAndRxBuf(1);
                    TMS_SendDownloadStart();
                    iTMS_ProcessStep++;
                } else if (iTMS_ProcessStep == 30 || iTMS_ProcessStep == 130) {
#ifdef USER_DEBUG
                    Rprintf("\r\nSend <ACK> of Data packet command\r\n");
#endif
                    // "Send Data <ACK> ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SendDataACK_000001], ucLangFlag);
                    ClearTMSDownloadBufAndRxBuf(1);
                    if (iTMS_ProcessStep == 30) {
                        TMS_SendDownloadDataAckNak(tTMSDownloadInfo.sAppCurrentSectorNo, ACK);
                    } else {
                        TMS_SendDownloadDataAckNak(tTMSDownloadInfo.sParamCurrentSectorNo, ACK);
                    }
                    iTMS_ProcessStep += 2;
                } else {
#ifdef USER_DEBUG
                    Rprintf("\r\nSend <NAK> of Data packet command\r\n");
#endif
                    // "Send Data <NAK> ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SendDataNAK_000001], ucLangFlag);
                    ClearTMSDownloadBufAndRxBuf(1);
                    if (iTMS_ProcessStep == 31) {
                        TMS_SendDownloadDataAckNak(tTMSDownloadInfo.sAppCurrentSectorNo, NAK);
                    } else {
                        TMS_SendDownloadDataAckNak(tTMSDownloadInfo.sParamCurrentSectorNo, NAK);
                    }
                    iTMS_ProcessStep += 2;
                }
                break;
            }

#ifdef USER_DEBUG
            Rprintf("\r\nDownload Error\r\n");
#endif
            // " Download Error ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DownloadError_0001], ucLangFlag);
            iTMS_ProcessStep = 9999;
            break;

        case 21: // Wait for response of Start communication command (Resume program (and parameter) downloading)
        case 121: // Wait for response of Start communication command (Parameter downloading)
        case 32: // Wait for response of Data packet, <ACK>, <NAK>, or End of communication command (Resume program (and parameter) downloading)
        case 132: // Wait for response of Data packet, <ACK>, <NAK>, or End of communication command (Parameter downloading)
        case 33: // Wait for response of Data packet, <ACK>, <NAK>, or End of communication command (Resume program (and parameter) downloading)
        case 133: // Wait for response of Data packet, <ACK>, <NAK>, or End of communication command (Parameter downloading)
            if (TIMER_GetElapsed10MSTime(usTMSDownload10MSTimer) >= TMSDOWN_DATA_PACKET_RESPONSE_WAIT_MAX_TIME) {
                if (iTMS_ProcessStep == 21 || iTMS_ProcessStep == 121) {
#ifdef USER_DEBUG
                    Rprintf("\r\nTimeout - Wait for response of Start communication command\r\n");
#endif
                    iTMS_ProcessStep--;
                } else if (iTMS_ProcessStep == 32 || iTMS_ProcessStep == 33) {
#ifdef USER_DEBUG
                    Rprintf("\r\nTimeout - Wait for response of Data packet, <ACK>, <NAK>, or End of communication command\r\n");
#endif
                    iTMS_ProcessStep = 31;
                } else {
#ifdef USER_DEBUG
                    Rprintf("\r\nTimeout - Wait for response of Data packet, <ACK>, <NAK>, or End of communication command\r\n");
#endif
                    iTMS_ProcessStep = 131;
                }
                break;
            }

            if (ret == 2) {
#ifdef USER_DEBUG
                Rprintf("\r\nReceiving Data..\r\n");
#endif
                // "RECEIVING DATA..",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1ReceivingData_0001], ucLangFlag);
            } else if (ret == 5) {
                if ((long) sTMS_SectorDownloadDataSize > lTMSDownlaodDataPacketMaxBytes) {
#ifdef USER_DEBUG
                    Rprintf("\r\nData Packet Size Over\r\n");
#endif
                    // "Data Packet     ",
                    LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PacketSizeOver_001], ucLangFlag);
                    // "Size Over!      ",
                    LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PacketSizeOver_002], ucLangFlag);
                    if (iTMS_ProcessStep == 21 || iTMS_ProcessStep == 121) {
                        iTMS_ProcessStep--;
                    } else if (iTMS_ProcessStep == 32 || iTMS_ProcessStep == 33) {
                        iTMS_ProcessStep = 31;
                    } else {
                        iTMS_ProcessStep = 131;
                    }
                    return;
                }

                if (iTMS_ProcessStep == 21 || iTMS_ProcessStep == 32 || iTMS_ProcessStep == 33) {
                    if (sTMS_PGMPARAMCurrentSectorNo != tTMSDownloadInfo.sAppWrittenSectorNo &&
                            sTMS_PGMPARAMCurrentSectorNo != (tTMSDownloadInfo.sAppWrittenSectorNo + 1)) {
#ifdef USER_DEBUG
                        Rprintf("\r\nSector No. Error\r\n");
#endif
                        // "Sector No. Error",
                        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SectorNoError_0001], ucLangFlag);
                        if (iTMS_ProcessStep == 21) {
                            iTMS_ProcessStep--;
                        } else {
                            iTMS_ProcessStep = 31;
                        }
                        return;
                    }

                    if (sTMS_PGMPARAMCurrentSectorNo == (tTMSDownloadInfo.sAppWrittenSectorNo + 1)) {
                        if (sTMS_PGMPARAMCurrentSectorNo < (tTMSDownloadInfo.sAppTotalSectorNo - 1)) {
                            if ((long) sTMS_SectorDownloadDataSize != lTMSDownlaodDataPacketMaxBytes) {
#ifdef USER_DEBUG
                                Rprintf("\r\nData Packet Size Error\r\n");
#endif
                                // "Data Packet     ",
                                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PacketSizeError_01], ucLangFlag);
                                // "Size Error      ",
                                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PacketSizeError_02], ucLangFlag);
                                if (iTMS_ProcessStep == 21) {
                                    iTMS_ProcessStep--;
                                } else {
                                    iTMS_ProcessStep = 31;
                                }
                                return;
                            }
                        }

                        tTMSDownloadInfo.sAppCurrentSectorNo = sTMS_PGMPARAMCurrentSectorNo;
                        SaveTMSDownloadInfo();

                        // First erase a sector
                        i = tTMSDownloadInfo.sAppCurrentSectorNo % sTMSDownlaodClusterNoPerSector;
                        if (i == 0) {
                            ltemp = GetZippedAppFlashSectorTopAddr(tTMSDownloadInfo.sAppCurrentSectorNo);
#ifdef USER_DEBUG
                            Rprintf("\r\nGet Flash 1 Sector Blank Status\r\n");
#endif
                            if (!MEMLIB_GetFlash1SectorBlankStatus((char *) ltemp)) {
#ifdef USER_DEBUG
                                Rprintf("\r\nErase a sector\r\n");
#endif
                                FLASH_SECTOR_ERASE((char *) ltemp);
#ifdef USER_DEBUG
                                Rprintf("Erase a sector OK - 0x%08lX\r\n", ltemp);
#endif
                            }
                        }
                        // Write 1Sector data
                        WriteApplicationOrParameter1Sector(1);

                        if (sTMS_PGMPARAMCurrentSectorNo == 0) {
                            tTMSDownloadInfo.lAppTotalDataSize = 0L;
                        }
                        tTMSDownloadInfo.lAppTotalDataSize += sTMS_SectorDownloadDataSize;
                        tTMSDownloadInfo.sAppWrittenSectorNo = tTMSDownloadInfo.sAppCurrentSectorNo;
                        SaveTMSDownloadInfo();

                        sprintf(temp, "%d/%d [%d%%]",
                                tTMSDownloadInfo.sAppCurrentSectorNo + 1,
                                tTMSDownloadInfo.sAppTotalSectorNo,
                                (unsigned int) ((tTMSDownloadInfo.sAppCurrentSectorNo + 1) * 100) / tTMSDownloadInfo.sAppTotalSectorNo);
                        LCD_DisplayLine(3, CENTER_JUSTIFIED, temp, ucLangFlag);
#ifdef USER_DEBUG
                        Rprintf("\r\n%s\r\n", temp);
#endif
                    }
                } else {
                    if (sTMS_PARAMCurrentSectorNo != tTMSDownloadInfo.sParamWrittenSectorNo &&
                            sTMS_PARAMCurrentSectorNo != (tTMSDownloadInfo.sParamWrittenSectorNo + 1)) {
#ifdef USER_DEBUG
                        Rprintf("\r\nSector No. Error\r\n");
#endif
                        // "Sector No. Error",
                        LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SectorNoError_0001], ucLangFlag);
                        if (iTMS_ProcessStep == 121) {
                            iTMS_ProcessStep--;
                        } else {
                            iTMS_ProcessStep = 131;
                        }
                        return;
                    }

                    if (sTMS_PARAMCurrentSectorNo == (tTMSDownloadInfo.sParamWrittenSectorNo + 1)) {
                        if (sTMS_PARAMCurrentSectorNo < (tTMSDownloadInfo.sParamTotalSectorNo - 1)) {
                            if ((long) sTMS_SectorDownloadDataSize != lTMSDownlaodDataPacketMaxBytes) {
                                // "Data Packet     ",
                                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PacketSizeError_01], ucLangFlag);
                                // "Size Error      ",
                                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PacketSizeError_02], ucLangFlag);
#ifdef USER_DEBUG
                                Rprintf("\r\nData Packet Size Error\r\n");
#endif
                                if (iTMS_ProcessStep == 121) {
                                    iTMS_ProcessStep--;
                                } else {
                                    iTMS_ProcessStep = 131;
                                }
                                return;
                            }
                        }

                        // First erase a sector
                        if (sTMS_PARAMCurrentSectorNo == 0) {
                            if (iFlashMemorySize < 16) {
                                ltemp = TMSDOWN_FLASH8MB_PRARM_ADDR;
                            } else {
                                ltemp = TMSDOWN_FLASH16MB_PRARM_ADDR;
                            }
#ifdef USER_DEBUG
                            Rprintf("\r\nGet Flash 1 Sector Blank Status\r\n");
#endif
                            if (!MEMLIB_GetFlash1SectorBlankStatus((char *) ltemp)) {
#ifdef USER_DEBUG
                                Rprintf("\r\nErase a sector\r\n");
#endif
                                FLASH_SECTOR_ERASE((char *) ltemp);
#ifdef USER_DEBUG
                                Rprintf("Erase a sector OK - 0x%08lX\r\n", ltemp);
#endif
                            }
                        }

                        tTMSDownloadInfo.sParamCurrentSectorNo = sTMS_PARAMCurrentSectorNo;
                        SaveTMSDownloadInfo();

                        // Write 1Sector data
                        WriteApplicationOrParameter1Sector(0);

                        if (sTMS_PARAMCurrentSectorNo == 0) {
                            tTMSDownloadInfo.lParamTotalDataSize = 0L;
                        }
                        tTMSDownloadInfo.lParamTotalDataSize += sTMS_SectorDownloadDataSize;
                        tTMSDownloadInfo.sParamWrittenSectorNo = tTMSDownloadInfo.sParamCurrentSectorNo;
                        SaveTMSDownloadInfo();

                        sprintf(temp, "%d/%d [%d%%]",
                                sTMS_PARAMCurrentSectorNo + 1,
                                sTMS_PARAMTotalSectorNo,
                                (unsigned int) ((sTMS_PARAMCurrentSectorNo + 1) * 100) / sTMS_PARAMTotalSectorNo);
                        LCD_DisplayLine(3, CENTER_JUSTIFIED, temp, ucLangFlag);
#ifdef USER_DEBUG
                        Rprintf("\r\n%s\r\n", temp);
#endif
                    }
                }
                ClearTMSDownloadBufAndRxBuf(0);
                if (iTMS_ProcessStep == 21 || iTMS_ProcessStep == 32 || iTMS_ProcessStep == 33) {
                    iTMS_ProcessStep = 30;
                } else {
                    iTMS_ProcessStep = 130;
                }
            } else if (ret == 6) {
#ifdef USER_DEBUG
                Rprintf("\r\nRx End of communication command\r\n");
#endif
                // "Rx Download End ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1RxDownloadEnd_0001], ucLangFlag);
                ClearTMSDownloadBufAndRxBuf(0);
                if (iTMS_ProcessStep == 32) {
                    iTMS_ProcessStep = 40;
                } else {
                    iTMS_ProcessStep = 140;
                }
            } else if (ret == -1) {
#ifdef USER_DEBUG
                Rprintf("\r\nRx LRC Error !\r\n");
#endif
                // " Rx LRC Error ! ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1RxLRCError_0000001], ucLangFlag);
                if (iTMS_ProcessStep == 21 || iTMS_ProcessStep == 121) {
                    iTMS_ProcessStep--;
                } else if (iTMS_ProcessStep == 32 || iTMS_ProcessStep == 33) {
                    iTMS_ProcessStep = 31;
                } else {
                    iTMS_ProcessStep = 131;
                }
            } else if (ret == -2) {
#ifdef USER_DEBUG
                Rprintf("\r\nSector LRC Error\r\n");
#endif
                // "Sector LRC Error",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SectorLRCError_001], ucLangFlag);
                if (iTMS_ProcessStep == 21 || iTMS_ProcessStep == 121) {
                    iTMS_ProcessStep--;
                } else if (iTMS_ProcessStep == 32 || iTMS_ProcessStep == 33) {
                    iTMS_ProcessStep = 31;
                } else {
                    iTMS_ProcessStep = 131;
                }
            } else if (ret == -3) {
#ifdef USER_DEBUG
                Rprintf("\r\nTx LRC Error !\r\n");
#endif
                // " Tx LRC Error ! ",
                LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1TxLRCError_0000001], ucLangFlag);
                if (iTMS_ProcessStep == 21 || iTMS_ProcessStep == 121) {
                    iTMS_ProcessStep--;
                } else {
                    iTMS_ProcessStep -= 2;
                }
            }
            break;

        case 40: // Send <ACK> End of communication command (Resume program (and parameter) downloading)
        case 140: // Send <ACK> End of communication command (Parameter downloading)
            // " Send End <ACK> ",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SendEndACK_0000001], ucLangFlag);
#ifdef USER_DEBUG
            Rprintf("\r\nSend End <ACK>\r\n");
#endif
            TMS_SendDownloadEndAckNak(ACK);

            TIMER_Wait1MS(2000);
            ModemClose();
            TIMER_Wait1MS(1000);

            if (iTMS_ProcessStep == 40) {
                UpgradeApplication(); // Program download completed
            } else {
                UpgradePOSParameter(0); // Parameter download completed
            }

            ClearTMSDownloadBufAndRxBuf(0);
            ucTMSDownloadFlag = 0;
            sVirtualKey = BTKEY_CANCEL;
            break;

        case 9999: // Error display
            ClearTMSDownloadBufAndRxBuf(0);
            ModemClose();
            ucTMSDownloadFlag = 0;
            TIMER_WaitKeyPress1MS(5000);
            sVirtualKey = BTKEY_CANCEL;
            break;
    }
}

// Clear TMS Download Buffer and Rx Buffer

void ClearTMSDownloadBufAndRxBuf(char inc_retry_cnt_flag) {
    TMS_ClearBuf();
    memset(ucRxBuf, 0x00, sizeof (ucRxBuf));
    if (!inc_retry_cnt_flag) {
        ucTMSDownloadRetryCnt = 0;
    } else {
        ucTMSDownloadRetryCnt++;
    }
    usTMSDownload10MSTimer = TIMER_Get10MSTimer();
}

// Set TMS Variables

void SetTMSVariables(void) {
    // Set TMS data packet size to 4
    //sTMSDownlaodDataPacketSize = 4;
    sTMSDownlaodDataPacketSize = 2; // 2048 Nigeria Paymaster
    if (iFlashMemorySize < 16) {
        // Get cluster number per a sector (64 kbytes / 4 kbytes = 16)
        sTMSDownlaodClusterNoPerSector = 64 / sTMSDownlaodDataPacketSize;
    } else {
        // Get cluster number per a sector (128 kbytes / 4 kbytes = 32)
        sTMSDownlaodClusterNoPerSector = 128 / sTMSDownlaodDataPacketSize;
    }
    // Get maximum packet data bytes (1024 bytes x 4 = 4096 bytes)
    lTMSDownlaodDataPacketMaxBytes = 1024L * sTMSDownlaodDataPacketSize;
}

// Load Program Download Information

void LoadTMSDownloadInfo(void) {
#ifdef USER_DEBUG
    Rprintf("LoadTMSDownloadInfo()\r\n");
#endif

    LoadFlashPOSUtilInfo();
    if (tPOSUtilInfo.ptLastLog->tTMSDownloadInfo.usMagicNo != TMS_INFO_MAGIC_NO ||
            tPOSUtilInfo.ptLastLog->tTMSDownloadInfo.usSuffixFlag != TMS_INFO_SUFFIX) {
        InitializeTMSDownloadInfo();
    } else {
        memcpy((char *) &tPOSUtilBuf, (char *) tPOSUtilInfo.ptLastLog, sizeof (_tPOS_UTIL));
        memcpy((char *) &tTMSDownloadInfo, (char *) &tPOSUtilBuf.tTMSDownloadInfo, sizeof (tTMSDownloadInfo));

#ifdef USER_DEBUG
        Output_TMSDownloadInfo();
#endif

        CheckTMSUpgrade();
    }
}

// Initialize TMS Downloading Information

void InitializeTMSDownloadInfo(void) {
#ifdef USER_DEBUG
    Rprintf("InitializeTMSDownloadInfo()\r\n");
#endif

    EraseAllDataTMSDownloadInfo();
}

// Save TMS Downloading Information

void SaveTMSDownloadInfo(void) {
    LoadFlashPOSUtilInfo();
    memcpy((char *) &tPOSUtilBuf, (char *) tPOSUtilInfo.ptLastLog, sizeof (_tPOS_UTIL));
    memcpy((char *) &tPOSUtilBuf.tTMSDownloadInfo, (char *) &tTMSDownloadInfo, sizeof (tTMSDownloadInfo));
    WritePOSUtil();
    LoadFlashPOSUtilInfo();

    memcpy((char *) &tPOSUtilBuf, (char *) tPOSUtilInfo.ptLastLog, sizeof (_tPOS_UTIL));
    memcpy((char *) &tTMSDownloadInfo, (char *) &tPOSUtilBuf.tTMSDownloadInfo, sizeof (tTMSDownloadInfo));
}

// Set Initial Value To TMS Downloading Information

void SetInitialValueToTMSDownloadInfo(void) {
    char temp[17];

#ifdef USER_DEBUG
    Rprintf("Set Initial Value To TMS Downloading Information\r\n");
#endif
    // Clear All TMS Downloading Information
    memset((char *) &tTMSDownloadInfo, 0x00, sizeof (tTMSDownloadInfo));

    tTMSDownloadInfo.usMagicNo = TMS_INFO_MAGIC_NO;
    tTMSDownloadInfo.usVersion = TMS_INFO_VERSION;
    tTMSDownloadInfo.ucApplicationNo = TMSDOWN_APPLICATION_NO;
    tTMSDownloadInfo.ucProgramNo = TMSDOWN_PRGOGRAM_NO;
    strcpy(tTMSDownloadInfo.sz17ProgramVersion, sz17TMSSWVersion);
    memset(temp, 0x00, sizeof (temp));
    if (GET_PROD_ID(temp) == 0) { // BNI51111200001
        strcpy(tTMSDownloadInfo.sz17SerialNo, temp);
    } else {
        strcpy(tTMSDownloadInfo.sz17SerialNo, st_POSSetupInfo.sz9TerminalID);
    }
    sprintf(tTMSDownloadInfo.sz5ParameterVersion, "%04X", st_POSSetupInfo.usVersionNo);
    strcpy(tTMSDownloadInfo.sz9ParameterDate, st_POSSetupInfo.sz9InfoDate);

    // Save last updated date
    RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
    sprintf(tTMSDownloadInfo.sz9UpgradedDate, "%02X%02X%02X%02X",
            RealTime.CLKYEARH, RealTime.CLKYEARL, RealTime.CLKMONTH, RealTime.CLKDATE);

    tTMSDownloadInfo.sAppWrittenSectorNo = -1;
    tTMSDownloadInfo.sParamWrittenSectorNo = -1;
    tTMSDownloadInfo.usSuffixFlag = TMS_INFO_SUFFIX;
}

// Erase All Data of TMS Downloading Information

void EraseAllDataTMSDownloadInfo(void) {
#ifdef USER_DEBUG
    Rprintf("Erase All Data of TMS Downloading Information\r\n");
#endif
    SetInitialValueToTMSDownloadInfo();
    SaveTMSDownloadInfo();
#ifdef USER_DEBUG
    Output_TMSDownloadInfo();
#endif
}

// Load TMS Download Sector Number

int LoadTMSDownloadSectorNo(void) {
    int i, j;
    long ltemp;

#ifdef USER_DEBUG
    Rprintf("LoadTMSDownloadSectorNo()\r\n");
#endif

    if (tTMSDownloadInfo.sAppCurrentSectorNo != tTMSDownloadInfo.sAppWrittenSectorNo) {
        i = tTMSDownloadInfo.sAppCurrentSectorNo % sTMSDownlaodClusterNoPerSector;
        if (i != 0) {
#ifdef USER_DEBUG
            Rprintf("\r\n");
            Rprintf("tTMSDownloadInfo.sAppCurrentSectorNo = %d\r\n", tTMSDownloadInfo.sAppCurrentSectorNo);
            Rprintf("tTMSDownloadInfo.sAppWrittenSectorNo = %d\r\n", tTMSDownloadInfo.sAppWrittenSectorNo);
            Rprintf("i = %d\r\n", i);
            Rprintf("Program Download Data Recovering\r\n");
#endif
            if (tTMSDownloadInfo.ucAppBackupOKFlag != 1) {
                // Copy current sector data to backup sector
                BackupOrRestoreAppDownloadData(0, tTMSDownloadInfo.sAppCurrentSectorNo);

                tTMSDownloadInfo.ucAppBackupOKFlag = 1;
                SaveTMSDownloadInfo();
            }

            // Restore current sector data from backup sector
            BackupOrRestoreAppDownloadData(1, tTMSDownloadInfo.sAppCurrentSectorNo);

            tTMSDownloadInfo.sAppCurrentSectorNo = tTMSDownloadInfo.sAppWrittenSectorNo;
            tTMSDownloadInfo.ucAppBackupOKFlag = 0;
            SaveTMSDownloadInfo();

            sTMSDownloadSectorNo = tTMSDownloadInfo.sAppCurrentSectorNo + 1;
        } else {
            if (tTMSDownloadInfo.sAppCurrentSectorNo != 0) {
                tTMSDownloadInfo.sAppCurrentSectorNo = tTMSDownloadInfo.sAppWrittenSectorNo;
                SaveTMSDownloadInfo();

                sTMSDownloadSectorNo = tTMSDownloadInfo.sAppCurrentSectorNo + 1;
            } else {
                sTMSDownloadSectorNo = tTMSDownloadInfo.sAppCurrentSectorNo;
            }
        }
    } else {
        // Program (and parameter) downloading is completed
        if (tTMSDownloadInfo.ucAppDownNeedFlag == 1 && tTMSDownloadInfo.sAppWrittenSectorNo >= (tTMSDownloadInfo.sAppTotalSectorNo - 1)) {
            return 1;
        } else {
            sTMSDownloadSectorNo = tTMSDownloadInfo.sAppCurrentSectorNo + 1;
        }
    }

    if (tTMSDownloadInfo.sAppWrittenSectorNo != -1) {
        ltemp = (long) (tTMSDownloadInfo.sAppWrittenSectorNo + 1) * lTMSDownlaodDataPacketMaxBytes;
        if (ltemp > tTMSDownloadInfo.lAppPgmTotalDataSize) {
            i = (tTMSDownloadInfo.lAppPgmTotalDataSize / lTMSDownlaodDataPacketMaxBytes) % sTMSDownlaodClusterNoPerSector;
            j = tTMSDownloadInfo.lAppPgmTotalDataSize % lTMSDownlaodDataPacketMaxBytes;
            if (i != 0 || j != 0) {
#ifdef USER_DEBUG
                Rprintf("\r\n");
                Rprintf("tTMSDownloadInfo.sAppWrittenSectorNo = %d\r\n", tTMSDownloadInfo.sAppWrittenSectorNo);
                Rprintf("i = %d\r\n", i);
                Rprintf("Program Download Data Recovering\r\n");
#endif
                i = tTMSDownloadInfo.lAppPgmTotalDataSize / lTMSDownlaodDataPacketMaxBytes;
                if (tTMSDownloadInfo.ucAppBackupOKFlag != 1) {
                    // Copy current sector data to backup sector
                    BackupOrRestoreAppDownloadData(0, i);

                    tTMSDownloadInfo.ucAppBackupOKFlag = 1;
                    SaveTMSDownloadInfo();
                }

                // Restore current sector data from backup sector
                BackupOrRestoreAppDownloadData(1, i);

                tTMSDownloadInfo.lAppTotalDataSize = (long) i * lTMSDownlaodDataPacketMaxBytes;
                tTMSDownloadInfo.sAppCurrentSectorNo = i - 1;
                tTMSDownloadInfo.sAppWrittenSectorNo = i - 1;
                tTMSDownloadInfo.ucAppBackupOKFlag = 0;
                SaveTMSDownloadInfo();

                sTMSDownloadSectorNo = tTMSDownloadInfo.sAppCurrentSectorNo + 1;
            }
        }
    }

    return 0;
}

// Check TMS Upgrade

void CheckTMSUpgrade(void) {
    // Program upgrading is completed
    if (tTMSDownloadInfo.ucAppDownNeedFlag == 1 &&
            tTMSDownloadInfo.sAppWrittenSectorNo >= (tTMSDownloadInfo.sAppTotalSectorNo - 1) &&
            tTMSDownloadInfo.ulUnzippedPgmSize != 0L) {
        // "Program Upgrade ",
        LCD_DisplayLine(0, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmUpgradeCheck_01], ucLangFlag);
        // "Checking Now... ",
        LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmUpgradeCheck_02], ucLangFlag);
#ifdef USER_DEBUG 
        Rprintf("Program Upgrade Checking Now...\r\n");
#endif

        if (!memcmp((char *) tTMSDownloadInfo.lAppPgmUpgradeStartAddr, (char *) TMSDOWN_FLASH16MB_UNZIPPED_PGM_ADDR, tTMSDownloadInfo.ulUnzippedPgmSize)) {
            //EraseAppDataTMSDownloadInfo();

            // "PGM Upgrade OK !",
            LCD_DisplayLine(2, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmUpgradeOK_00001], ucLangFlag);
#ifdef USER_DEBUG
            Rprintf("PGM Upgrade OK !\r\n");
#endif
            EraseAllDataTMSDownloadInfo();
            TIMER_WaitKeyPress1MS(2500);
            ENTER_RESET();
            return;
        } else {
#ifdef USER_DEBUG 
            Rprintf("Program is not upgraded\r\n");
#endif
        }
    }

    // Program (and parameter) downloading is completed
    if (LoadTMSDownloadSectorNo()) {
        UpgradeApplication();
    }

    // The POS's parameter upgrade is needed, when the POS is rebooted after program upgrading is completed
    if (tTMSDownloadInfo.lAppParamTotalDataSize != 0L && tTMSDownloadInfo.lAppParamDataStartAddr != 0L) {
        UpgradePOSParameter(1);
    }

    // The POS's parameter upgrade is needed, when the POS is rebooted after parameter downloading is completed
    if (tTMSDownloadInfo.sParamWrittenSectorNo >= (tTMSDownloadInfo.sParamTotalSectorNo - 1) && tTMSDownloadInfo.lParamTotalDataSize != 0L) {
        UpgradePOSParameter(0);
    }
}

// Upgrade Application

void UpgradeApplication(void) {
    long ltemp;
    unsigned long org_file_size;
    int i;
    unsigned int lrc;
    unsigned char *ptr;

    // Program (and parameter) downloading is completed
    LCD_ClearScreen();
    // "PGMDown Complete",
    LCD_DisplayLine(0, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmDownComplete_01], ucLangFlag);

#ifdef USER_DEBUG
    Rprintf("\r\n");
    Rprintf("PGMDown Complete\r\n");
    Rprintf("Total File Data Size     = %ld\r\n", tTMSDownloadInfo.lAppPgmTotalDataSize + tTMSDownloadInfo.lAppParamTotalDataSize);
    Rprintf("Total Received Data Size = %ld\r\n", tTMSDownloadInfo.lAppTotalDataSize);
#endif

    if (tTMSDownloadInfo.lAppTotalDataSize != (tTMSDownloadInfo.lAppPgmTotalDataSize + tTMSDownloadInfo.lAppParamTotalDataSize)) {
        // "Size mismatch ! ",
        LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1SizeMismatch_00001], ucLangFlag);
#ifdef USER_DEBUG
        Rprintf("Size mismatch !\r\n");
        PauseUntilEnterkeyPressed();
#endif
    } else {
#ifdef USER_DEBUG
        ltemp = TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR + tTMSDownloadInfo.lAppPgmTotalDataSize;
        Debug_Output("Parameter", (unsigned char *) ltemp, tTMSDownloadInfo.lAppParamTotalDataSize, 0);
#endif

        lrc = TMS_CalDownloadROMFileLRC((unsigned char *) TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR, tTMSDownloadInfo.lAppTotalDataSize);

#ifdef USER_DEBUG
        Rprintf("Received LRC   = %04X\r\n", tTMSDownloadInfo.usAppTotalLRCData);
        Rprintf("Calculated LRC = %04X\r\n", lrc);
#endif

        if (lrc != tTMSDownloadInfo.usAppTotalLRCData) {
            // "File LRC Error !",
            LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1FileLRCError_00001], ucLangFlag);
#ifdef USER_DEBUG
            Rprintf("File LRC Error !\r\n");
            PauseUntilEnterkeyPressed();
#endif
        } else {
            // Get uncompressed size
            ltemp = TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR + tTMSDownloadInfo.lAppPgmTotalDataSize - 1;

            ptr = (unsigned char *) ltemp;
            ltemp = *ptr & 0xFF;
            ltemp = (ltemp << 24) & 0xFF000000;
            org_file_size = ltemp;
            ptr--;
            ltemp = *ptr & 0xFF;
            ltemp = (ltemp << 16) & 0x00FF0000;
            org_file_size |= ltemp;
            ptr--;
            ltemp = *ptr & 0xFF;
            ltemp = (ltemp << 8) & 0x0000FF00;
            org_file_size |= ltemp;
            ptr--;
            ltemp = *ptr & 0x000000FF;
            org_file_size |= ltemp;

#ifdef USER_DEBUG
            PauseUntilEnterkeyPressed();
#endif

            if (tTMSDownloadInfo.lAppParamTotalDataSize != 0L) {
                tTMSDownloadInfo.lAppParamDataStartAddr = TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR + tTMSDownloadInfo.lAppPgmTotalDataSize;
                SaveTMSDownloadInfo();
            }
#ifdef USER_DEBUG
            Rprintf("Program Upgrade Start Address = 0x%08lX\r\n", tTMSDownloadInfo.lAppPgmUpgradeStartAddr);
            Rprintf("Program Data Start Address    = 0x%08lX\r\n", TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR);
            Rprintf("Parameter Data Start Address  = 0x%08lX\r\n", tTMSDownloadInfo.lAppParamDataStartAddr);
#endif

            // "Data Processing ",
            LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1DataProcessing_001], ucLangFlag);
#ifdef USER_DEBUG
            Rprintf("Data Processing now...\r\n");
#endif

            ltemp = Decompress(tTMSDownloadInfo.lAppPgmTotalDataSize, (char*) TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR, (unsigned char*) TMSDOWN_FLASH16MB_UNZIPPED_PGM_ADDR, org_file_size, 2);

#ifdef USER_DEBUG
            Rprintf("Original File Size = %ld\r\n", org_file_size);
            Rprintf("Unzipped File Size = %ld\r\n", ltemp);
#endif
            if (org_file_size != ltemp) {
                // "PGM Size Error! ",
                LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1PgmSizeError_00001], ucLangFlag);
#ifdef USER_DEBUG
                Rprintf("Program size mismatch !\r\n");
                PauseUntilEnterkeyPressed();
#endif
            } else {
                tTMSDownloadInfo.ulUnzippedPgmSize = org_file_size;
                SaveTMSDownloadInfo();
#ifdef USER_DEBUG
                PauseUntilEnterkeyPressed();
#endif

                i = WRITE_APP_PROGRAM(ltemp, (char *) TMSDOWN_FLASH16MB_UNZIPPED_PGM_ADDR, (char *) tTMSDownloadInfo.lAppPgmUpgradeStartAddr, 0x00);
                if (i == 1) {
                    // "BIOS Not Support",
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1BIOSNotSupport_001], ucLangFlag);
#ifdef USER_DEBUG
                    Rprintf("BIOS Not Support\r\n");
                    PauseUntilEnterkeyPressed();
#endif
                } else {
                    // "Limitation Error",
                    LCD_DisplayLine(1, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1LimitationError_01], ucLangFlag);
#ifdef USER_DEBUG
                    Rprintf("Limitation Error\r\n");
                    PauseUntilEnterkeyPressed();
#endif
                }
            }
        }
    }

    EraseAllDataTMSDownloadInfo();

    TIMER_WaitKeyPress1MS(5000);
    ENTER_RESET();
}

// Erase Program Data of TMS Downloading Information

void EraseAppDataTMSDownloadInfo(void) {
#ifdef USER_DEBUG
    Rprintf("Erase Program Data of TMS Downloading Information\r\n");
#endif
    // Save last updated date
    RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);
    sprintf(tTMSDownloadInfo.sz9UpgradedDate, "%02X%02X%02X%02X",
            RealTime.CLKYEARH, RealTime.CLKYEARL, RealTime.CLKMONTH, RealTime.CLKDATE);

    // Erase Only Program Downloading Information
    tTMSDownloadInfo.ucAppDownNeedFlag = 0;
    tTMSDownloadInfo.ucAppBackupOKFlag = 0;
    tTMSDownloadInfo.sAppTotalSectorNo = 0;
    tTMSDownloadInfo.usAppTotalLRCData = 0;
    tTMSDownloadInfo.sAppCurrentSectorNo = 0;
    tTMSDownloadInfo.sAppWrittenSectorNo = -1;
    tTMSDownloadInfo.lAppPgmUpgradeStartAddr = 0L;
    tTMSDownloadInfo.lAppPgmTotalDataSize = 0L;
    tTMSDownloadInfo.lAppReferenceNo = 0L;
    tTMSDownloadInfo.lAppTotalDataSize = 0L;
    tTMSDownloadInfo.ulUnzippedPgmSize = 0L;

    SaveTMSDownloadInfo();
#ifdef USER_DEBUG
    Output_TMSDownloadInfo();
#endif
}

/*
Upgrade POS Parameter
        Input
                mode
                        0: Upgrade POS Parameter by parameter downloading
                        1: Upgrade POS Parameter by program (and parameter) downloading
 */
void UpgradePOSParameter(int mode) {
    int i;
    unsigned int lrc;
    U08 *ptr;

    // "Sorry, it does  ", "not support     ", "parameter       ", "upgrade now     "
    /*	LCDDisplay4Lines(M4NotSupportParam_01, -1, ucLangFlag);
            EraseAllDataTMSDownloadInfo();
            TIMER_WaitKeyPress1MS(2500);
            ENTER_RESET();
     */
    return;
}

// mode = 0 : Parameter download
// mode = 1 : Program (and parameter) download

void WriteApplicationOrParameter1Sector(int mode) {
    long ltemp;

    // Write one sector data
    if (mode) {
        if (iFlashMemorySize < 16) {
            ltemp = TMSDOWN_FLASH8MB_ZIPPED_PGM_ADDR;
        } else {
            ltemp = TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR;
        }
        ltemp += ((long) tTMSDownloadInfo.sAppCurrentSectorNo * lTMSDownlaodDataPacketMaxBytes);
#ifdef USER_DEBUG
        Rprintf("Writing program\r\n");
#endif
    } else {
        if (iFlashMemorySize < 16) {
            ltemp = TMSDOWN_FLASH8MB_PRARM_ADDR;
        } else {
            ltemp = TMSDOWN_FLASH16MB_PRARM_ADDR;
        }
        ltemp += ((long) tTMSDownloadInfo.sParamCurrentSectorNo * lTMSDownlaodDataPacketMaxBytes);
#ifdef USER_DEBUG
        Rprintf("Writing parameter\r\n");
#endif
    }

    FLASH_WRITE((char *) ltemp, (long) sTMS_SectorDownloadDataSize, (char *) ucRxBuf);
#ifdef USER_DEBUG
    Rprintf("Writing OK - 0x%08lX\r\n", ltemp);
#endif
}

// mode : 0 = Backup, 1 = Restore

void BackupOrRestoreAppDownloadData(int mode, int sector_no) {
    int i, size;
    long ltemp, ltemp1, src_start, dst_start;

    ltemp = GetZippedAppFlashSectorTopAddr(sector_no);
    if (iFlashMemorySize < 16) {
        ltemp1 = TMSDOWN_FLASH8MB_BACKUP_ADDR;
    } else {
        ltemp1 = TMSDOWN_FLASH16MB_BACKUP_ADDR;
    }
    if (mode == 0) {
        src_start = ltemp;
        dst_start = ltemp1;
    } else {
        src_start = ltemp1;
        dst_start = ltemp;
    }

    // Erase destination sector
    if (!MEMLIB_GetFlash1SectorBlankStatus((char *) dst_start)) {
#ifdef USER_DEBUG
        Rprintf("Erase a sector   - 0x%08lX\r\n", dst_start);
#endif
        FLASH_SECTOR_ERASE((char *) dst_start);
#ifdef USER_DEBUG
        Rprintf("Erase a sector OK - 0x%08lX\r\n", dst_start);
#endif
    }

    // Copy current sector data to backup sector
    // Restore current sector data from backup sector
    size = sector_no % sTMSDownlaodClusterNoPerSector;
    ltemp1 = (long) size * lTMSDownlaodDataPacketMaxBytes;

#ifdef USER_DEBUG
    Rprintf("Read %dKBytes Data: 0x%08lX-0x%08lX\r\n", (int) (ltemp1 / 1024), src_start, src_start + ltemp1 - 1);
#endif
    memset(FlashWriteBuf, 0xFF, sizeof (FlashWriteBuf));
    // Read (size)Kbytes data from source sector
    memcpy((char *) FlashWriteBuf, (char *) src_start, ltemp1);

#ifdef USER_DEBUG
    Rprintf("Copy %dKBytes Data: 0x%08lX-0x%08lX\r\n", (int) (ltemp1 / 1024), dst_start, dst_start + ltemp1 - 1);
#endif
    // Write (size)Kbytes data to destination sector
    FLASH_WRITE((char *) dst_start, ltemp1, (char *) FlashWriteBuf);

#ifdef USER_DEBUG
    Rprintf("\r\n");
#endif
}

long GetZippedAppFlashSectorTopAddr(int sector_no) {
    long ltemp, zipped_addr;

    if (iFlashMemorySize < 16) {
        zipped_addr = TMSDOWN_FLASH8MB_ZIPPED_PGM_ADDR;
    } else {
        zipped_addr = TMSDOWN_FLASH16MB_ZIPPED_PGM_ADDR;
    }
    ltemp = (long) sector_no / sTMSDownlaodClusterNoPerSector;
    ltemp *= (long) sTMSDownlaodClusterNoPerSector;
    ltemp *= lTMSDownlaodDataPacketMaxBytes;
    ltemp += zipped_addr;

    return ltemp;
}

void CheckAutoTMSDownloadStart(void) {
    int i;
    char temp[17];

    // Check Terminal ID
    if (strlen(st_POSSetupInfo.sz9TerminalID) != 8) {
        return;
    }

    // Check Merchant ID
    /*	if (strlen(st_POSSetupInfo.sz16MerchantID) == 0) {
                    return;
            }
     */
    if (GetAutoTMSDownloadingDate()) {
        if (ucAutoTMSDownloadDateFlag == 0) {
#ifdef USER_DEBUG
            Rprintf("Over ten days elapsed after last updating\r\n");
#endif
            ucAutoTMSDownloadDateFlag = 1;
        }
    } else {
        ucAutoTMSDownloadDateFlag = 0;
        ucAutoTMSDownloadFirstFlag = 1;
    }

    if (ucAutoTMSDownloadDateFlag) {
        if (ucAutoTMSDownloadFirstFlag == 0) {
            if (TIMER_GetElapsed1SECTime(lTMSAutoDownloadTried1SECTimer) >= TMSDOWN_AUTO_DOWNLOAD_TIME) {
                ucAutoTMSDownloadTimeFlag = 1;
            } else {
                ucAutoTMSDownloadTimeFlag = 0;
            }
        }

        if (ucAutoTMSDownloadFirstFlag || ucAutoTMSDownloadTimeFlag) {
            // "????????????????", "????????????????", "????????????????", "????????????????"
            MainStatusSetting(MSS_F1_FUNC, MST_F1_REMOTEDOWNLOAD, M4_____________Dummy, -1, ucLangFlag);

            if (st_POSSetupInfo.ucComDevice == DIAL_UP_MODEM) {
                pusServiceAddr += 9;
            } else if (st_POSSetupInfo.ucComDevice == ETHERNET_MODEM) {
                pusServiceAddr += 16;
            } else {
                pusServiceAddr += 22;
            }

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
        }
    }
}

BOOL GetAutoTMSDownloadingDate(void) {
    long cur_date, upgraded_date, difference_date;
    unsigned short year;
    char temp[17];
    _tDATE_TIME dt1, dt2;

    RTC_GetDateTime(&dt1, GREGORIAN_CALENDAR);
    sprintf(temp, "%02X%02X", dt1.CLKYEARH, dt1.CLKYEARL);
    year = atoi(temp) - 1;
    cur_date = (long) year * 365;
    cur_date += ((year / 4) - (year / 100) +(year / 400));
    cur_date += RTC_GetGregorianDays(&dt1);

    dt2.CLKYEARH = ((tTMSDownloadInfo.sz9UpgradedDate[0] & 0x0F) << 4) | (tTMSDownloadInfo.sz9UpgradedDate[1] & 0x0F);
    dt2.CLKYEARL = ((tTMSDownloadInfo.sz9UpgradedDate[2] & 0x0F) << 4) | (tTMSDownloadInfo.sz9UpgradedDate[3] & 0x0F);
    dt2.CLKMONTH = ((tTMSDownloadInfo.sz9UpgradedDate[4] & 0x01) << 4) | (tTMSDownloadInfo.sz9UpgradedDate[5] & 0x0F);
    dt2.CLKDATE = ((tTMSDownloadInfo.sz9UpgradedDate[6] & 0x03) << 4) | (tTMSDownloadInfo.sz9UpgradedDate[7] & 0x0F);
    sprintf(temp, "%02X%02X", dt2.CLKYEARH, dt2.CLKYEARL);
    year = atoi(temp) - 1;
    upgraded_date = (long) year * 365;
    upgraded_date += ((year / 4) - (year / 100) +(year / 400));
    upgraded_date += RTC_GetGregorianDays(&dt2);

    if (cur_date >= upgraded_date) {
        difference_date = cur_date - upgraded_date;
        if (difference_date >= 10L) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        // Save last updated date with current date because updated date is later than current date.
        sprintf(tTMSDownloadInfo.sz9UpgradedDate, "%02X%02X%02X%02X",
                dt1.CLKYEARH, dt1.CLKYEARL, dt1.CLKMONTH, dt1.CLKDATE);
        SaveTMSDownloadInfo();
#ifdef USER_DEBUG
        Output_TMSDownloadInfo();
#endif
        return FALSE;
    }
}

#ifdef USER_DEBUG

void Output_TMSDownloadInfo(void) {
    Rprintf("\r\n");
    Rprintf("**************************************************************\r\n");
    Rprintf(">>              TMS Downloading Information                <<\r\n");
    Rprintf("**************************************************************\r\n");
    Rprintf("tTMSDownloadInfo.usMagicNo               = %04X\r\n", tTMSDownloadInfo.usMagicNo);
    Rprintf("tTMSDownloadInfo.usVersion               = %04X\r\n", tTMSDownloadInfo.usVersion);

    Rprintf("tTMSDownloadInfo.ucApplicationNo         = %d\r\n", tTMSDownloadInfo.ucApplicationNo);
    Rprintf("tTMSDownloadInfo.ucProgramNo             = %d\r\n", tTMSDownloadInfo.ucProgramNo);
    Rprintf("tTMSDownloadInfo.sz17ProgramVersion      = %s\r\n", tTMSDownloadInfo.sz17ProgramVersion);
    Rprintf("tTMSDownloadInfo.sz17SerialNo            = %s\r\n", tTMSDownloadInfo.sz17SerialNo);
    Rprintf("tTMSDownloadInfo.sz5ParameterVersion     = %s\r\n", tTMSDownloadInfo.sz5ParameterVersion);
    Rprintf("tTMSDownloadInfo.sz9ParameterDate        = %s\r\n", tTMSDownloadInfo.sz9ParameterDate);
    Rprintf("tTMSDownloadInfo.sz9UpgradedDate         = %s\r\n", tTMSDownloadInfo.sz9UpgradedDate);

    Rprintf("tTMSDownloadInfo.ucAppDownNeedFlag       = %d\r\n", tTMSDownloadInfo.ucAppDownNeedFlag);
    Rprintf("tTMSDownloadInfo.ucAppBackupOKFlag       = %d\r\n", tTMSDownloadInfo.ucAppBackupOKFlag);
    Rprintf("tTMSDownloadInfo.sAppTotalSectorNo       = %d\r\n", tTMSDownloadInfo.sAppTotalSectorNo);
    Rprintf("tTMSDownloadInfo.usAppTotalLRCData       = %04X\r\n", tTMSDownloadInfo.usAppTotalLRCData);
    Rprintf("tTMSDownloadInfo.sAppCurrentSectorNo     = %d\r\n", tTMSDownloadInfo.sAppCurrentSectorNo);
    Rprintf("tTMSDownloadInfo.sAppWrittenSectorNo     = %d\r\n", tTMSDownloadInfo.sAppWrittenSectorNo);
    Rprintf("tTMSDownloadInfo.lAppPgmUpgradeStartAddr = %08lX\r\n", tTMSDownloadInfo.lAppPgmUpgradeStartAddr);
    Rprintf("tTMSDownloadInfo.lAppPgmTotalDataSize    = %ld\r\n", tTMSDownloadInfo.lAppPgmTotalDataSize);
    Rprintf("tTMSDownloadInfo.lAppParamTotalDataSize  = %ld\r\n", tTMSDownloadInfo.lAppParamTotalDataSize);
    Rprintf("tTMSDownloadInfo.lAppReferenceNo         = %08lX\r\n", tTMSDownloadInfo.lAppReferenceNo);
    Rprintf("tTMSDownloadInfo.lAppTotalDataSize       = %ld\r\n", tTMSDownloadInfo.lAppTotalDataSize);
    Rprintf("tTMSDownloadInfo.lAppParamDataStartAddr  = %08lX\r\n", tTMSDownloadInfo.lAppParamDataStartAddr);
    Rprintf("tTMSDownloadInfo.ulUnzippedPgmSize       = %ld\r\n", tTMSDownloadInfo.ulUnzippedPgmSize);

    Rprintf("tTMSDownloadInfo.ucParamDownNeedFlag     = %d\r\n", tTMSDownloadInfo.ucParamDownNeedFlag);
    Rprintf("tTMSDownloadInfo.sParamTotalSectorNo     = %d\r\n", tTMSDownloadInfo.sParamTotalSectorNo);
    Rprintf("tTMSDownloadInfo.usParamTotalLRCData     = %04X\r\n", tTMSDownloadInfo.usParamTotalLRCData);
    Rprintf("tTMSDownloadInfo.sParamCurrentSectorNo   = %d\r\n", tTMSDownloadInfo.sParamCurrentSectorNo);
    Rprintf("tTMSDownloadInfo.sParamWrittenSectorNo   = %d\r\n", tTMSDownloadInfo.sParamWrittenSectorNo);
    Rprintf("tTMSDownloadInfo.lParamTotalDataSize     = %ld\r\n", tTMSDownloadInfo.lParamTotalDataSize);

    Rprintf("tTMSDownloadInfo.usSuffixFlag            = %04X\r\n", tTMSDownloadInfo.usSuffixFlag);
}
#endif

/* */
