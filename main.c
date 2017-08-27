#include "system.h"
#include "extern.h"
#include "include/emv/emv_app.h"

extern U16 gwCurrencyCode;
extern U08 gbCurrencyExp;




int iModelName;
unsigned char ucLangFlag;
unsigned char ucCurrencyExp;
char sz6BIOSVersion[6];
char sz17HWInfo[17];
char sz17ProgramVersion[17];
char sz17ProgramDate[17];
char sz17TMSSWVersion[17];
char sz17TRMModelName[17];
char sz9POSSetupInfoDate[9];
char sz5LCDDisplayProgramVersion[5];

#ifdef USER_DEBUG
void Output_SystemInfomation(void);
#endif

extern void InitEmvLib();
extern void InitPinpadDrv(int iLine);
extern void appEmvTask(void);
extern void InitFlashParameters();

int main(void) {
    int i, j, k, key;
    int year, month, date;
    unsigned long proc_code;
    unsigned short msg_type;
    unsigned short trxn_type;
    char temp[65];

    // Set language to English
    ucLangFlag = 0;

    // Set user LCD font
    USE_LCDFONT((char *) NULL, 0);
    // Set user printer font
    USE_PRTFONT((char *) NULL, 0);

    // Set LCD contrast to 25
    LCD_CONT(25);

    //            "   Initialize   ", "     System     ", "                ", " Please Wait... "
    MainStatusSetting(MSS_INITIAL, MST_INITIAL, M4SystemCheckMsg_001, -1, ucLangFlag);
    pusServiceAddr++;

    // LCD back light turn on time working after key depressed (0 - 255)
    // 0: do not use this function and back light on off will control
    //    by "BACK_ONOFF" function
    // 1 to 255 (second): Set back light on time
    CONTROL_POWER_SAVING_STATUS(0, 0);
    // LCD on
    LCD_ON();
    // LCD backlight on
    BACK_ONOFF(ON);
    /*
    {
            int i;
            char buf[16];
            for(i = 0; i < 128; i += 8) {
                    memcpy(&buf[i], "\x01\x03\x07\x0F\x1F\x3F\x7F\xFF", 8);
            }

    //	memset(buf, 0x51, sizeof(buf));
            for(i = 0; i < 128; i += 4) {
                    GRADATA_LOAD(&buf[i], 0, i, 4);
            }
    }
    while(1)
            ;
     */
    // Set serial buffer size to 8 KBytes
    SET_BUFFER_SIZE_8K();

    // Get BIOS version
    SYSINFO_GetBiosVersion(sz6BIOSVersion);
    // Get hardware information
    SYSINFO_GetHWInformation(sz17HWInfo);

    // Enable key sound
    Beep_KeySoundEnable();
    // Enable event sound
    Beep_EventSoundEnable();

    switch (sz17HWInfo[3]) {
        case 0x30: iFlashMemorySize = 0;
            break;
        case 0x34: iFlashMemorySize = 2;
            break;
        case 0x35: iFlashMemorySize = 4;
            break;
        case 0x36:
        case 0x37: iFlashMemorySize = 8;
            break;
        case 0x38: iFlashMemorySize = 16;
            break;
        default: iFlashMemorySize = 0;
            break;
    }
    if (iFlashMemorySize < 16) {
        lFlashSectorSize = FLASH8MB_SECTOR_SIZE;
        iFlashTrxnLogSectorNo = FLASH8MB_TRANSACTION_LOG_SECTOR_NO;
    } else {
        lFlashSectorSize = FLASH16MB_SECTOR_SIZE;
        iFlashTrxnLogSectorNo = FLASH16MB_TRANSACTION_LOG_SECTOR_NO;
    }
    MEMLIB_SetFlashSectorSize(lFlashSectorSize);
    Unzip_SetFlashSectorSize(lFlashSectorSize);

    if (iFlashMemorySize < 8) {
        // "This application", "does not support", "unknow model... ", "                "
        LCDDisplay4Lines(M4UnknownModelMsg_01, -1, ucLangFlag);
        for (i = 0; i < 3; i++) {
            Beep_EventSound(ERROR_TONE);
            TIMER_Wait1MS(1500);
        }
        while (1) {
            TIMER_Wait1MS(1000);
        }
    }

    temp[0] = sz17HWInfo[9];
    temp[1] = sz17HWInfo[10];
    temp[2] = 0x00;
    switch (atoi(temp)) {
        case 31: iModelName = IC3100PE;
            break;
            //case 33:	iModelName = IC3300P; break;
        case 51: iModelName = IC5100P;
            break;
            //case 60:	iModelName = IC6000P; break;
        default: iModelName = UNKNOWN_MODEL;
            break;
    }

    if (iModelName == IC5100P) {
        // Set paper feeding key to BTKEY_UPARROW_IC5100P key
        SAVE_PRINT_KEY(BTKEY_UPARROW_IC5100P);

        // Set printing density
        ucPRTDensity = 10;

#ifndef SDRAM_VERSION
        strcpy(sz17ProgramVersion, "IC5100P  PMP1.00"); // PayMaster Payment
        strcpy(sz17ProgramDate, "2012/05/02      ");
        strcpy(sz17TMSSWVersion, "1.0.0           ");
        strcpy(sz17TRMModelName, "IC5100P         ");
        strcpy(sz9POSSetupInfoDate, "20120502");
        strcpy(sz5LCDDisplayProgramVersion, "1.00");
#else
        strcpy(sz17ProgramVersion, "IC5100SD PMP1.00");
        strcpy(sz17ProgramDate, "2012/05/02      ");
        strcpy(sz17TMSSWVersion, "1.0.0           ");
        strcpy(sz17TRMModelName, "IC5100SD        ");
        strcpy(sz9POSSetupInfoDate, "20120502");
        strcpy(sz5LCDDisplayProgramVersion, "1.00");
#endif
    } else {
        // "This application", "does not support", "unknow model... ", "                "
        LCDDisplay4Lines(M4UnknownModelMsg_01, -1, ucLangFlag);
        for (i = 0; i < 3; i++) {
            Beep_EventSound(ERROR_TONE);
            TIMER_Wait1MS(1500);
        }
        while (1) {
            TIMER_Wait1MS(1000);
        }
    }

#ifdef USER_DEBUG
    OpenDebugPort(COM0, BPS115200, NONE8BIT, STOP1BIT, 0);
#else
    DisableDebugOutput();
#endif

    // for debugging
#ifdef USER_DEBUG
    Output_SystemInfomation();
#endif

#ifdef ERASE_DATA_ROM_OPTION
    EraseDataROM();
#endif

    // Check and get date&time from RTC
    i = RTC_GetDateTime(&RealTime, GREGORIAN_CALENDAR);

    sprintf(temp, "%02X%02X%02X%02X%02X%02X%02X",
            RealTime.CLKYEARH, RealTime.CLKYEARL, RealTime.CLKMONTH, RealTime.CLKDATE,
            RealTime.CLKHOUR, RealTime.CLKMIN, RealTime.CLKSEC);
    j = RTC_CheckGregorianInputDateTime(temp);

    if (i == 0 || j == 0) {
        //InitializeRTCDateTime();
        SetRTCDateTimeWhenPowerIsTurnedOn();
    } else {
        Beep_EventSound(OK_TONE);
        TIMER_Wait1MS(500);
    }
#ifdef USER_DEBUG
    Rprintf("\r\n");
    Rprintf("Date & Time          : %02X%02X/%02X/%02X %02X:%02X:%02X - %d[%s]\r\n",
            RealTime.CLKYEARH, RealTime.CLKYEARL, RealTime.CLKMONTH, RealTime.CLKDATE,
            RealTime.CLKHOUR, RealTime.CLKMIN, RealTime.CLKSEC,
            RealTime.CLKDAY, DAY_STR_TBL[RealTime.CLKDAY % 7]);

    Rprintf("\r\n");
#endif

    if (iFlashMemorySize < 16) {
        stpFlashPOSSetupInfo = (_st_POSSetupInfo_ *) FLASH8MB_POS_SETUP_INFO_START_ADDR;
    } else {
        stpFlashPOSSetupInfo = (_st_POSSetupInfo_ *) FLASH16MB_POS_SETUP_INFO_START_ADDR;
    }

    // Load POS Setup Information
    LoadPOSSetupInfo();

    // Set default values if parameters are incorrect
    k = 0;
    // Setup LCD Contrast
    if (st_POSSetupInfo.ucLCDContrast < MIN_LCD_CONTRAST || st_POSSetupInfo.ucLCDContrast > MAX_LCD_CONTRAST) {
        st_POSSetupInfo.ucLCDContrast = 25;
        k = 1;
    }
    // Setup MSR Track
    if (st_POSSetupInfo.ucMSRTrack3 != 0) {
        // Set MSR track to 1&2
        st_POSSetupInfo.ucMSRTrack3 = 0;
        k = 1;
    }
    // Setup GSM modem
    if (st_POSSetupInfo.ucComDevice != GSM_MODEM) {
        // Set modem to GSM_MODEM
        st_POSSetupInfo.ucComDevice = GSM_MODEM;
        k = 1;
    }

    if (k) {
        WritePOSSetupInfo();
    }

    // Enable or disable key sound by st_POSSetupInfo.ucBeep
    if (st_POSSetupInfo.ucBeep) {
        Beep_KeySoundEnable();
    } else {
        Beep_KeySoundDisable();
    }

    // Set LCD contrast to st_POSSetupInfo.ucLCDContrast
    LCD_CONT(st_POSSetupInfo.ucLCDContrast);

    // 0 : Track 1 & 2 used (H/W - DEFAULT) 
    // 1 : Track 2 & 3 H/W installed (option)
    // 2 : Track 1&2&3 H/W installed (option)
    // 3 : Track 1&2&3 H/W installed (option for JIS-II)
    // MSR TYPE
    // 0x33:Uniform Triple, 0x34:MagTek Triple
    if (sz17HWInfo[6] == 0x33 || sz17HWInfo[6] == 0x34) {
        ucMSRTrack = 2;
    } else {
        ucMSRTrack = st_POSSetupInfo.ucMSRTrack3;
    }
    TRACK_SETUP(ucMSRTrack);

    // Set currency exponent to 2
    ucCurrencyExp = 2;

#ifdef SAVE_TEST_TRXN_LOG
    // Save Transaction Logs for test
    //SaveTestTrxnLogs(999);
#endif

    // Set TMS Variables
    SetTMSVariables();

    // Initialize TMS Downloading Information
    //InitializeTMSDownloadInfo();

    // Load TMS Downloading Information
    LoadTMSDownloadInfo();

    if (st_POSSetupInfo.ucComDevice == GSM_MODEM) {
        GprsModuleInitialize();
    }

    // Begin Initialize EMV Functions
    //	InitCrc16(4);  /* Only[0-4], for NAC6000 = 4 */

    //	FlashFileInit(); - EMV Param(TrmConf, TrmCapk) ������ �ٿ�ε� �޵��� �޼���
    InitFlashParameters();
    /*
    {
            int i;
            char *ptr = (char *)0x303A0000;
            char temp[17];
	
            for(i = 0; i < 0x20000; i++) {
                    if((i % 16) == 0) {
                            if(i != 0) {
                                    temp[16] = 0x00;
                                    Rprintf("%s", temp);
                            }
                            Rprintf("\r\n%08X: ", &ptr[i]);
                    }
                    Rprintf("%02X ", ptr[i] & 0xFF);
                    temp[i % 16] = (ptr[i] >= 0x20 && ptr[i] <= 0x7E)? (ptr[i] & 0xFF): '.';
            }
	
    }
     */

    InitEmvLib();
    gwCurrencyCode = ISO3166_NG; //(ISO3166_NG = 0x566 NGA NIGERIA)
    gbCurrencyExp = 2;
    InitPinpadDrv(3);
    // End Initialize EMV Functions

    CancelKeyService();

    // Set LCD backlight on flag
    ucLCDBacklightOnFlag = 1;
    // Get LCD backlight on start time
    usLCDBackLightOn10MSTimer = TIMER_Get10MSTimer();

    // Set first automatic TMS downloading flag
    ucAutoTMSDownloadFirstFlag = 1;

    // Get Next Transaction Parameter
#ifdef USER_DEBUG
    GetNextTrxnParameter(&RealTime, 1); // for debug of transaction log
#else
    GetNextTrxnParameter(&RealTime, 0);
#endif
    if (ucReversalFlag) {
        Rprintf("There is an unsuccessful transaction on the last log.\r\n");
        GotoReversalMode();
        //PerformReversalTransaction();
    }

#ifdef AUTO_MODEM_TEST
    usModemAutoTest10MSTimer = TIMER_Get10MSTimer();
#endif
    /*
            st_POSSetupInfo.ucGprsSIMNo = 0;
            strcpy(st_POSSetupInfo.sz33GprsAPN[0], "web.gprs.mtnnigeria.net");
            strcpy(st_POSSetupInfo.sz33GprsUserName[0], "gprs");
            strcpy(st_POSSetupInfo.sz33GprsPassword[0], "gprs");
    //	strcpy(st_POSSetupInfo.sz33GprsAPN[0], "glosecure");
    //	strcpy(st_POSSetupInfo.sz33GprsUserName[0], "web");
    //	strcpy(st_POSSetupInfo.sz33GprsPassword[0], "web");
            strcpy(st_POSSetupInfo.sz33GprsAPN[1], "web.gprs.mtnnigeria.net");
            strcpy(st_POSSetupInfo.sz33GprsUserName[1], "gprs");
            strcpy(st_POSSetupInfo.sz33GprsPassword[1], "gprs");
	
            strcpy(st_POSSetupInfo.sz16TrxnServerIP[0], "41.58.130.139");
            strcpy(st_POSSetupInfo.sz6TrxnServerPortNo[0], "80");
            strcpy(st_POSSetupInfo.sz16TrxnServerIP[1], "41.58.130.139");
            strcpy(st_POSSetupInfo.sz6TrxnServerPortNo[1], "80");
	
            st_POSSetupInfo.ucCommTimeout = 60;
     */
    while (1) {
        KeyTask();
        appEmvTask();
        RTCTask();
        MSRTask();
        ModemTask();
        RS232Task();
        PrintTask();
    }

    return 0;
}

#ifdef USER_DEBUG

void Output_SystemInfomation(void) {
    int i;
    long code_start_addr, code_end_addr;
    long total_code_size, total_code_kbytes;
    long static_code_size, static_code_kbytes;
    long dynamic_code_size, dynamic_code_kbytes;
    char str[65], temp[65];

    Rprintf("\r\n");
    Rprintf("*****************************************************************************\r\n");
    Rprintf("                            System Information\r\n");
    Rprintf("*****************************************************************************\r\n");
    Rprintf("BIOS Version               : %s\r\n", sz6BIOSVersion);
    Rprintf("Hardware Information       : %s\r\n", sz17HWInfo);
    Rprintf("Software Version           : %s\r\n", sz17ProgramVersion);
    Rprintf("Software Date              : %s\r\n", sz17ProgramDate);

    temp[0] = sz17HWInfo[9];
    temp[1] = sz17HWInfo[10];
    temp[2] = 0x00;
#ifndef SDRAM_VERSION
    switch (atoi(temp)) {
        case 31: strcpy(str, "IC3100PE");
            break;
            //case 33:	strcpy(str, "IC3300P"); break;
        case 51: strcpy(str, "IC5100P");
            break;
            //case 60:	strcpy(str, "IC6000"); break;
        default: strcpy(str, "Unknown Code");
            break;
    }
#else
    switch (atoi(temp)) {
        case 31: strcpy(str, "IC3100SD");
            break;
            //case 33:	strcpy(str, "IC3300SD"); break;
        case 51: strcpy(str, "IC5100SD");
            break;
            //case 60:	strcpy(str, "IC6000"); break;
        default: strcpy(str, "Unknown Code");
            break;
    }
#endif
    Rprintf("Model Name                 : %s\r\n", str);

    memset(temp, 0x00, sizeof (temp));
    i = GET_PROD_ID(temp);
    if (i) {
        memset(temp, 0x00, sizeof (temp));
    }
    Rprintf("POS S/N                    : %s\r\n", temp);

    switch (sz17HWInfo[1]) {
        case 0x30: strcpy(temp, "NONE");
            break;
        case 0x34: strcpy(temp, "2 MB");
            break;
        case 0x35: strcpy(temp, "4 MB");
            break;
        case 0x36:
        case 0x37: strcpy(temp, "8 MB");
            break;
        case 0x38: strcpy(temp, "16 MB");
            break;
        default: strcpy(temp, "Unknown Code");
            break;
    }
    Rprintf("SRAM                       : %s\r\n", temp);

    switch (sz17HWInfo[2]) {
        case 0x30: strcpy(temp, "NONE");
            break;
        case 0x34: strcpy(temp, "2 MB");
            break;
        case 0x35: strcpy(temp, "4 MB");
            break;
        case 0x36:
        case 0x37: strcpy(temp, "8 MB");
            break;
        case 0x38: strcpy(temp, "16 MB");
            break;
        default: strcpy(temp, "Unknown Code");
            break;
    }
    Rprintf("SDRAM                      : %s\r\n", temp);

    switch (sz17HWInfo[3]) {
        case 0x30: strcpy(temp, "NONE");
            break;
        case 0x34: strcpy(temp, "2 MB");
            break;
        case 0x35: strcpy(temp, "4 MB");
            break;
        case 0x36:
        case 0x37: strcpy(temp, "8 MB");
            break;
        case 0x38: strcpy(temp, "16 MB");
            break;
        default: strcpy(temp, "Unknown Code");
            break;
    }
    Rprintf("Flash ROM                  : %s\r\n", temp);

    switch (sz17HWInfo[5]) {
        case 0x30: strcpy(temp, "NONE");
            break;
        case 0x31: strcpy(temp, "EXISTED");
            break;
        default: strcpy(temp, "Unknown Code");
            break;
    }
    Rprintf("USB                        : %s\r\n", temp);

    switch (sz17HWInfo[6]) {
        case 0x30: strcpy(temp, "Uniform Dual Track");
            break;
        case 0x33: strcpy(temp, "Uniform Triple Track");
            break;
        case 0x34: strcpy(temp, "MagTek Triple Track");
            break;
        default: strcpy(temp, "Unknown Code");
            break;
    }
    Rprintf("MSR TYPE                   : %s\r\n", temp);

    switch (sz17HWInfo[7]) {
        case 0x30: strcpy(temp, "NONE");
            break;
        case 0x31: strcpy(temp, "Dial-up 2400bps");
            break;
        case 0x32: strcpy(temp, "Dial-up 56Kbps");
            break;
        case 0x33: strcpy(temp, "GSM/GPRS");
            break;
        case 0x34: strcpy(temp, "CDMA");
            break;
        case 0x35:
        case 0x37: strcpy(temp, "56Kbps, GSM/GPRS");
            break;
        case 0x36: strcpy(temp, "FOMA");
            break;
        default: strcpy(temp, "Unknown Code");
            break;
    }
    Rprintf("MODEM                      : %s\r\n", temp);

    switch (sz17HWInfo[8]) {
        case 0x31: strcpy(temp, "BIXOLON");
            break;
        case 0x32: strcpy(temp, "Seiko Epson");
            break;
        default: strcpy(temp, "Unknown Code");
            break;
    }
    Rprintf("PRINTER TYPE               : %s\r\n", temp);

    Rprintf("\r\n");

#ifndef SDRAM_VERSION
    code_start_addr = 0x40000000L;
#else
    code_start_addr = 0x20000000L;
#endif
    Rprintf("Program Start Address      : 0x%08lX\r\n", code_start_addr);
    Rprintf("Dynamic Code Start Address : 0x%08lX\r\n", (long) &REFTABLE);
    if ((long) &__usr_ram_start != (long) &__usr_ram_end) {
        code_end_addr = (long) &__usr_rom_start + ((long) &__usr_ram_end - (long) &__usr_ram_start) - 1;
    } else {
        code_end_addr = (long) &_etext - 1;
    }
    Rprintf("Program End Address        : 0x%08lX\r\n", code_end_addr);

    total_code_size = code_end_addr - code_start_addr + 1;
    total_code_kbytes = total_code_size / 1024;
    if (total_code_size % 1024) {
        total_code_kbytes += 1;
    }
    Rprintf("Total Code Size            : %10ld (%ld Kbytes)\r\n", total_code_size, total_code_kbytes);

    static_code_size = (long) &REFTABLE - code_start_addr;
    static_code_kbytes = static_code_size / 1024;
    if (static_code_size % 1024) {
        static_code_kbytes += 1;
    }
    Rprintf("Static Code Size           : %10ld (%ld Kbytes)\r\n", static_code_size, static_code_kbytes);

    dynamic_code_size = total_code_size - static_code_size;
    dynamic_code_kbytes = dynamic_code_size / 1024;
    if (dynamic_code_size % 1024) {
        dynamic_code_kbytes += 1;
    }
    Rprintf("Dynamic Code Size          : %10ld (%ld Kbytes)\r\n", dynamic_code_size, dynamic_code_kbytes);

    Rprintf("\r\n");
    Rprintf("Transaction Log Structure Size             : %d\r\n", sizeof (st_TrxnLog));
    Rprintf("Transaction Request Data Structure Size    : %d\r\n", sizeof (st_TrxnReqData));
    Rprintf("Transaction Response Data Structure Size   : %d\r\n", sizeof (st_TrxnRespData));
    Rprintf("POS Setup Information Data Size            : %d\r\n", sizeof (st_POSSetupInfo));
    Rprintf("Transaction Database Size                  : %d\r\n", sizeof (st_TrxnLogDB));

    Rprintf("Number of LCD Messages                     : %d\r\n", M1_____________Space + 1);
    Rprintf("Number of Printer Messages                 : %d\r\n", P1SoftwareVersion_01 + 1);

    Rprintf("POS Util buffer Data Size                  : %d\r\n", sizeof (tPOSUtilBuf));
    Rprintf("TMS Information Data Size                 : %d\r\n", sizeof (tTMSDownloadInfo));
}
#endif
