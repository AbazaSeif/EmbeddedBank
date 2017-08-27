
/*======================================================================*/
/*																		*/
/*								LCDMSG1.H								*/
/*																		*/
/*======================================================================*/

typedef enum {
	M1_____________Dummy = -1,
	
	
	//*******************************************
	//				System Message
	//*******************************************
	M1TestAppMsg_0000001,		// "This is test    ",
	M1TestAppMsg_0000002,		// "appication for  ",
	M1TestAppMsg_0000003,		// "demonstration   ",
	
	M1DemoAppMsg_0000001,		// "This is demo    ",
	M1DemoAppMsg_0000002,		// "appication.     ",
	M1DemoAppMsg_0000003,		// "---- Expire ----",
	M1DemoAppMsg_0000004,		// "   21/03/2011   ",
	
	M1SystemCheckMsg_001,		// "   Initialize   ",
	M1SystemCheckMsg_002,		// "     System     ",
	M1SystemCheckMsg_003,		// " Please Wait... ",
	
	M1UnknownModelMsg_01,		// "This application",
	M1UnknownModelMsg_02,		// "does not support",
	M1UnknownModelMsg_03,		// "unknow model... ",
	
	M1BackupBatErrMsg_01,		// "Please replace a",
	M1BackupBatErrMsg_02,		// "RTC backup      ",
	M1BackupBatErrMsg_03,		// "battery with a  ",
	M1BackupBatErrMsg_04,		// "new one         ",
	
	M1GSMCheckMsg_000001,		// "   Initialize   ",
	M1GSMCheckMsg_000002,		// "   GSM module   ",
	
	
	//*******************************************
	//				Special Functions
	//*******************************************
	M1EnterPassword_0001,		// "Enter Password  ",
	
	M1MaintenanceMenu_01,		// "  Maintenance   ",
	M1MaintenanceMenu_02,		// "1.Setup Terminal",
	M1MaintenanceMenu_03,		// "2.POS Info.     ",
	M1MaintenanceMenu_04,		// "3.Initialize    ",
	M1MaintenanceMenu_05,		// "4.Change PIN    ",
	M1MaintenanceMenu_06,		// "5.Hardware Test ",
	
/*	M1SetupTrmMenu_00001,		// " Setup Terminal ",
	M1SetupTrmMenu_00002,		// "1.Setup Modem   ",
	M1SetupTrmMenu_00003,		// "2.Select App.   ",
	M1SetupTrmMenu_00004,		// "3.Set Parameters",
	M1SetupTrmMenu_00005,		// "4.Activate Menu ",
	M1SetupTrmMenu_00006,		// "5.Set Help Desk ",
	M1SetupTrmMenu_00007,		// "6.Activate TMS  ",
	M1SetupTrmMenu_00008,		// "7.Serial Number ",
*/
	M1SetupTrmMenu_00001,		// " Setup Terminal ",
	M1SetupTrmMenu_00002,		// "1.Setup Modem   ",
	M1SetupTrmMenu_00003,		// "2.Set Parameters",
	M1SetupTrmMenu_00004,		// "3.Download Param",
	M1SetupTrmMenu_00005,		// "4.Serial Number ",
	M1SetupTrmMenu_00006,		// "5.Pinpad KeyLoad",

	M1PinpadTitle_000001,		// "     PINPAD     ",
	M1KeyLoadReady_00001,		// "KEY LOAD READY! ",

	M1ErrNoBatchNo_00001,		// "  No Batch No.  ",
	
	M1SelectModemMenu_01,		// "SELECT MODEM    ",
	M1SelectModemMenu_02,		// "1.Dial-up       ",
	M1SelectModemMenu_03,		// "2.Ethernet      ",
	M1SelectModemMenu_04,		// "3.GSM           ",
	
	M1DialUpModemMenu_01,		// "Dial-up Modem   ",
	M1DialUpModemMenu_02,		// "1.Set Parameters",
	M1DialUpModemMenu_03,		// "2.Access Code   ",
	M1DialUpModemMenu_04,		// "3.Telephone No  ",
	M1DialUpModemMenu_05,		// "4.EOD Access    ",
	M1DialUpModemMenu_06,		// "5.EOD Phone No  ",
	M1DialUpModemMenu_07,		// "6.B.List Access ",
	M1DialUpModemMenu_08,		// "7.B.List Phone  ",
	M1DialUpModemMenu_09,		// "8.TMS Access    ",
	M1DialUpModemMenu_10,		// "9.TMS Phone No  ",
	
	M1DialUpModemSpeed_1,		// "MODEM SPEED     ",
	M1DialUpModemSpeed_2,		// "1.1200BPS       ",
	M1DialUpModemSpeed_3,		// "2.2400BPS       ",
	M1DialingTimeout_001,		// "DIALING TIMEOUT ",
	M1CommTimeout_000001,		// "COMM TIMEOUT    ",
	M1CommMode_000000001,		// "COMM MODE       ",
	M1CommMode_000000002,		// "1.ASYNC         ",
	M1CommMode_000000003,		// "2.SYNC          ",
	M1CommStandard_00001,		// "STANDARD        ",
	M1CommStandard_00002,		// "1.CCITT         ",
	M1CommStandard_00003,		// "2.BELL          ",
	M1DialingMode_000001,		// "DIALING MODE    ",
	M1DialingMode_000002,		// "1.NORMAL MODE   ",
	M1DialingMode_000003,		// "2.BLIND MODE    ",
	M1PulseDial_00000001,		// "PULSE DIAL      ",
	M1NO_000000000000001,		// "1.NO            ",
	M1YES_00000000000001,		// "2.YES           ",
	M1PreDialing_0000001,		// "PRE-DIALING     ",
	
	M1PABXAccess_0000001,		// "PABX ACCESS     ",
	M1PABXAccessCode_001,		// "PABX ACCESS CODE",
	M1CityAccess_0000001,		// "CITY ACCESS     ",
	M1CityAccessCode_001,		// "CITY ACCESS CODE",
	
	M1TrxnTelephoneNo_01,		// "TELEPHONE NO    ",
	
	M1EODTelephoneNo_001,		// "EOD Phone No    ",
	
	M1BListTelephoneNo_1,		// "Black List Phone",
	
	M1TMSTelephoneNo_001,		// "TMS PHONE NO    ",
	
	M1EthernetMenu_00001,		// "Ethernet        ",
	M1EthernetMenu_00002,		// "1.Set Local     ",
	M1EthernetMenu_00003,		// "2.Set Server    ",
	M1EthernetMenu_00004,		// "3.EOD Server    ",
	M1EthernetMenu_00005,		// "4.B.List Server ",
	M1EthernetMenu_00006,		// "5.TMS Server    ",
	
	M1LocalIPAddress_001,		// "LOCAL IP ADDRESS",
	M1SubnetMask_0000001,		// "SUBNET MASK     ",
	M1Gateway_0000000001,		// "GATEWAY         ",
	M1LocalPortNo_000001,		// "LOCAL PORT NO   ",
	M1LocalTimeout_00001,		// "LOCAL TIMEOUT   ",
	M1ActivateSSL_000001,		// "Activate SSL?   ",
	
	M1ServerIPAddress_01,		// "SERVER IP 1     ",
	M1ServerPortNo_00001,		// "SERVER PORT NO 1",
	M1ServerIPAddress_02,		// "SERVER IP 2     ",
	M1ServerPortNo_00002,		// "SERVER PORT NO 2",
	
	M1EODServerIP_000001,		// "EOD IP 1        ",
	M1EODServerPortNo_01,		// "EOD PORT NO 1   ",
	M1EODServerIP_000002,		// "EOD IP 2        ",
	M1EODServerPortNo_02,		// "EOD PORT NO 2   ",
	
	M1BListServerIP_0001,		// "B.List IP 1     ",
	M1BListServerPortNo1,		// "B.List PORT NO 1",
	M1BListServerIP_0002,		// "B.List IP 2     ",
	M1BListServerPortNo2,		// "B.List PORT NO 2",
	
	M1TMSServerIP_000001,		// "TMS IP 1        ",
	M1TMSServerPortNo_01,		// "TMS PORT NO 1   ",
	M1TMSServerIP_000002,		// "TMS IP 2        ",
	M1TMSServerPortNo_02,		// "TMS PORT NO 2   ",
	
	M1StarEqualDot_00001,		// "*='.'           ",
	
	M1GSMMenu_0000000001,		// "    GSM/GPRS    ",
	M1GSMMenu_0000000002,		// "1.Set Parameters",
	M1GSMMenu_0000000003,		// "2.Set Server    ",
	M1GSMMenu_0000000004,		// "3.Set TMS Server",

	M1GSMSelSIM_00000001,		// "Select SIM      ",
	M1GSMSelSIM_00000002,		// "1.SIM1          ",
	M1GSMSelSIM_00000003,		// "2.SIM2          ",
	
	M1GSMInputAPN_000001,		// "Input APN       ",
	M1GSMInputID_0000001,		// "Input Username  ",
	M1GSMInputPWD_000001,		// "Input Password  ",

	M1SelectAppMenu_0001,		// "Select App.     ",
	M1SelectAppMenu_0002,		// "1.Normal App.   ",
	M1SelectAppMenu_0003,		// "2.Multi-Merchant",
	
	M1SetParamMenu_00001,		// "Set Parameters  ",
	M1SetParamMenu_00002,		// "1.Terminal ID   ",
	M1SetParamMenu_00003,		// "2.Store Name    ",
	M1SetParamMenu_00004,		// "3.Sequence No   ",
	M1DownloadParam_0001,		// "Download Params ",
	M1DownloadParam_0002,		// "1.App Lists     ",
	M1DownloadParam_0003,		// "2.Function Lists",
	M1DownloadParam_0004,		// "3.Key Download  ",
	M1DownloadParam_0005,		// "4.EFT Parameters",
	M1DownloadParam_0006,		// "5.EMV Parameters",
	M1DownloadParam_0007,		// "6.Hot Cards     ",

	M1DownFuncList_00001,		// " Function List  ",
	M1DownFuncList_00002,		// "1.Tams          ",
	M1DownFuncList_00003,		// "2.VoucherVault  ",
	M1DownFuncList_00004,		// "3.Banking       ",
	M1DownTrxnKeys_00001,		// "  Key Download  ",
	M1DownTrxnKeys_00002,		// "1.Master Key    ",
	M1DownTrxnKeys_00003,		// "2.Session Key   ",
	M1DownEftParams_0001,		// " EFT Parameters ",
	M1DownEftParams_0002,		// "1.Params        ",
	M1DownEftParams_0003,		// "2.EFT Params    ",
	M1DownEftParams_0004,		// "3.BIN Tables    ",
	M1DownEmvParams_0001,		// " EMV Parameters ",
	M1DownEmvParams_0002,		// "1.EMV APPs      ",
	M1DownEmvParams_0003,		// "2.EMV CAPKs     ",
	M1DownEmvParams_0004,		// "3.Revoke CAPKs  ",

	M1TerminalID_0000001,		// "Terminal ID     ",
	M1MerchantID_0000001,		// "Merchant ID     ",
	M1StoreName_00000001,		// "Store Name      ",
	M1AccountType_000001,		// "Account Type    ",
	M1ExtPrnMenu_0000001,		// "External Prn    ",
	M1ExtPrnMenu_0000002,		// "1.Select Printer",
	M1ExtPrnMenu_0000003,		// "2.Max Prn Copy  ",
	M1ExtPrnMenu_0000004,		// "3.Setup Paper   ",
	M1ExtPrnModelMenu_01,		// "Select Printer  ",
	M1ExtPrnModelMenu_02,		// "1.PR4 SL        ",
	M1ExtPrnModelMenu_03,		// "2.BP-3000       ",
	M1ExtPrnMaxCopy_0001,		// "Max Prn Copy    ",
	M1ExtPrnPaperMenu_01,		// "Setup Paper     ",
	M1ExtPrnPaperMenu_02,		// "1.Left Number   ",
	M1ExtPrnPaperMenu_03,		// "2.Right Number  ",
	M1ExtPrnPaperMenu_04,		// "3.Line Number   ",
	M1ExtPrnPaperLeft_01,		// "Left Number     ",
	M1ExtPrnPaperRight_1,		// "Right Number    ",
	M1ExtPrnPaperLine_01,		// "Line Number     ",
	M1Advertisement_0001,		// "Advertisement 1 ",
	M1Advertisement_0002,		// "Advertisement 2 ",
	M1Advertisement_0003,		// "Advertisement 3 ",
	M1NII_00000000000001,		// "NII             ",
	M1SetOfflineMenu_001,		// "Set Offline     ",
	M1SetOfflineMenu_002,		// "1.Offline No.   ",
	M1SetOfflineMenu_003,		// "2.Offline Amount",
	M1OfflineMaxNo_00001,		// "Offline Number  ",
	M1OfflineMaxAmount_1,		// "Offline Amount  ",
	M1TerminalID1_000001,		// "Terminal ID 1   ",
	M1TerminalID2_000001,		// "Terminal ID 2   ",
	M1TerminalID3_000001,		// "Terminal ID 3   ",
	M1TerminalID4_000001,		// "Terminal ID 4   ",
	M1TerminalID5_000001,		// "Terminal ID 5   ",
	M1TerminalID6_000001,		// "Terminal ID 6   ",
	M1TerminalID7_000001,		// "Terminal ID 7   ",
	M1TerminalID8_000001,		// "Terminal ID 8   ",
	M1MerchantID1_000001,		// "Merchant ID 1   ",
	M1MerchantID2_000001,		// "Merchant ID 2   ",
	M1MerchantID3_000001,		// "Merchant ID 3   ",
	M1MerchantID4_000001,		// "Merchant ID 4   ",
	M1MerchantID5_000001,		// "Merchant ID 5   ",
	M1MerchantID6_000001,		// "Merchant ID 6   ",
	M1MerchantID7_000001,		// "Merchant ID 7   ",
	M1MerchantID8_000001,		// "Merchant ID 8   ",
	M1StoreName1_0000001,		// "Store Name 1    ",
	M1StoreName2_0000001,		// "Store Name 2    ",
	M1StoreName3_0000001,		// "Store Name 3    ",
	M1StoreName4_0000001,		// "Store Name 4    ",
	M1StoreName5_0000001,		// "Store Name 5    ",
	M1StoreName6_0000001,		// "Store Name 6    ",
	M1StoreName7_0000001,		// "Store Name 7    ",
	M1StoreName8_0000001,		// "Store Name 8    ",
	M1MultiMerchMenu_001,		// "Multi-Merchant  ",
	M1MultiMerchMenu_002,		// "1.Set Trxn Name ",
	M1MultiMerchMenu_003,		// "2.Set Amounts   ",
	M1MultiMerchName_001,		// "Trxn Name 1     ",
	M1MultiMerchName_002,		// "Trxn Name 2     ",
	M1MultiMerchName_003,		// "Trxn Name 3     ",
	M1MultiMerchName_004,		// "Trxn Name 4     ",
	M1MultiMerchName_005,		// "Trxn Name 5     ",
	M1MultiMerchName_006,		// "Trxn Name 6     ",
	M1MultiMerchName_007,		// "Trxn Name 7     ",
	M1MultiMerchName_008,		// "Trxn Name 8     ",
	M1SetAmountsMenu_001,		// "Set Amounts     ",
	M1SetAmountsMenu_002,		// "1.Set Amounts 1 ",
	M1SetAmountsMenu_003,		// "2.Set Amounts 2 ",
	M1SetAmountsMenu_004,		// "3.Set Amounts 3 ",
	M1SetAmountsMenu_005,		// "4.Set Amounts 4 ",
	M1SetAmountsMenu_006,		// "5.Set Amounts 5 ",
	M1SetAmountsMenu_007,		// "6.Set Amounts 6 ",
	M1SetAmountsMenu_008,		// "7.Set Amounts 7 ",
	M1SetAmountsMenu_009,		// "8.Set Amounts 8 ",
	M1SetAmount1Menu_001,		// "Set Amounts 1   ",
	M1SetAmount2Menu_001,		// "Set Amounts 2   ",
	M1SetAmount3Menu_001,		// "Set Amounts 3   ",
	M1SetAmount4Menu_001,		// "Set Amounts 4   ",
	M1SetAmount5Menu_001,		// "Set Amounts 5   ",
	M1SetAmount6Menu_001,		// "Set Amounts 6   ",
	M1SetAmount7Menu_001,		// "Set Amounts 7   ",
	M1SetAmount8Menu_001,		// "Set Amounts 8   ",
	M1SetAmountItem_0001,		// "1.Amount 1      ",
	M1SetAmountItem_0002,		// "2.Amount 2      ",
	M1SetAmountItem_0003,		// "3.Amount 3      ",
	M1SetAmountItem_0004,		// "4.Maximum Amount",
	M1SetAmount1_0000001,		// "Amount 1        ",
	M1SetAmount2_0000001,		// "Amount 2        ",
	M1SetAmount3_0000001,		// "Amount 3        ",
	M1SetMaxAmount_00001,		// "Maximum Amount  ",

	M1AllParameters_0001,		// " All Parameters ",
	M1AppFuncLists_00001,		// " App/Func Lists ",
	M1NewKeys_0000000001,		// "    New Keys    ",
	M1ParamBinTable_0001,		// " Param/BinTable ",
	M1EMVParameters_0001,		// " EMV Parameters ",
	M1ToDownload_0000001,		// "to download!    ",
	M1DownloadSuccess_01,		// "Download Success",

	M1AppLists_000000001,		// "    App List    ",
	M1FuncLists_00000001,		// " Function List  ",
	M1MasterKey_00000001,		// "   Master Key   ",
	M1SessionKey_0000001,		// "  Session Key   ",
	M1Params_00000000001,		// "     Params     ",
	M1EftParams_00000001,		// "   EFT Params   ",
	M1BinTables_00000001,		// "   BIN Tables   ",
	M1EmvApps_0000000001,		// "    EMV APPs    ",
	M1EmvCapks_000000001,		// "   EMV CAPKs    ",
	M1RevokeCapks_000001,		// "  Revoke CAPKs  ",
	M1HotCards_000000001,		// "   Hot Cards    ",
	
	M1FarsiMode_00000001,		// "            [FA]",
	M1EnglishMode_000001,		// "            [EN]",
	
	M1ActivateMenu_00001,		// "Activate Menu   ",
	M1ActivateMenu_00002,		// "1.Buy           ",
	M1ActivateMenu_00003,		// "2.Balance       ",
	M1ActivateMenu_00004,		// "3.Bill Payment  ",
	M1ActivateMenu_00005,		// "4.Check Bill Pay",
	M1ActivateMenu_00006,		// "5.SIM Charge    ",
	
	M1ActivateBuyMenu_01,		// "Buy Menu        ",
	M1ActivateBuyMenu_02,		// "1.Normal Buy    ",
	M1ActivateBuyMenu_03,		// "2.Buy with extra",
	M1ActivateBuyMenu_04,		// "3.Buy + ExtPrn  ",
	
	M1NormalBuyActive_01,		// "Normal Buy      ",
	M1ExtraBuyActive_001,		// "Buy with extra  ",
	M1ExtPrnBuyActive_01,		// "Buy + ExtPrn    ",
	M1BalanceActive_0001,		// "Balance         ",
	M1BillPayActive_0001,		// "Bill Payment    ",
	M1CheckBillActive_01,		// "Check Bill Pay  ",
	M1SIMChargeActive_01,		// "SIM Charge      ",
	M1MultiBuyActive_001,		// "Buy (Multi)     ",
	
	M1ActiveMenu_0000001,		// "1.Active        ",
	M1InactiveMenu_00001,		// "2.Inactive      ",
	
	M1BuyTrxnName_000001,		// "Buy Trxn Name   ",
	
	M1HelpDeskPhoneNo_01,		// "Help Desk Tel No",
	
	M1ActivateTMS_000001,		// "Activate TMS?   ",
	
	M1SerialNumber_00001,		// "Serial Number   ",
	M1InputSN_0000000001,		// "Input S/N       ",
	M1ConfirmSN_00000001,		// "Confirm S/N     ",
	
	M1AlphabetMode_00001,		// "           [ALP]",
	M1AlphabetMode_00002,		// "           [alp]",
	M1NumberMode_0000001,		// "           [NUM]",
	
	M1SavingOK_000000001,		// "   Saving OK    ",
	M1SavingError_000001,		// "  Saving Error  ",
	
	M1POSInfoMenu_000001,		// "POS Information ",
	M1POSInfoMenu_000002,		// "1.View Info.    ",
	M1POSInfoMenu_000003,		// "2.Print Info.   ",
	
	M1POSModelName_00001,		// "Model Name      ",
	M1POSSWVersionMsg_01,		// "S/W Version     ",
	M1POSSWDate_00000001,		// "S/W Date        ",
	
	M1PrintPOSInfo_00001,		// "Print Info.     ",
	
	M1NoTrxnLog_00000001,		// "No Trxn Log     ",
	
	M1TransferLog_000001,		// "Transferring    ",
	M1TransferLog_000002,		// "Log...          ",
	M1TransferLog_000003,		// "See RS232 Output",
	
	M1InitializeMenu_001,		// "Initialize      ",
	M1InitializeMenu_002,		// "1.Reset Param.  ",
	M1InitializeMenu_003,		// "2.Reset Merchant",
	M1InitializeMenu_004,		// "3.Erase POS Logs",
	
	M1ResetParameter_001,		// "Reset Parameters",
	
	M1ResetMerchant_0001,		// "Reset Merchant  ",
	
	M1ErasePOSLogs_00001,		// "Erase POS Logs  ",
	
	M1NewPassword_000001,		// "New Password    ",
	M1ConfirmPassword_01,		// "Confirm Password",
	M1MismatchError_0001,		// "Mismatch Error  ",
	M1PasswordChanged_01,		// "Password Changed",
	
	M1HWTestMenu_0000001,		// "Hardware Test   ",
	M1HWTestMenu_0000002,		// "1.Printer Test  ",
	M1HWTestMenu_0000003,		// "2.MSR Test      ",
	M1HWTestMenu_0000004,		// "3.Modem Test    ",
	M1HWTestMenu_0000005,		// "4.IC Card Test  ",
	M1HWTestMenu_0000006,		// "5.Key Test      ",
	M1HWTestMenu_0000007,		// "6.LCD Test      ",
	M1HWTestMenu_0000008,		// "7.RS232 Test    ",
	M1HWTestMenu_0000009,		// "8.RTC Test      ",
	
	M1PrinterTest_000001,		// " <Printer Test> ",
	
	M1MSRTest_0000000001,		// " <MSR Test> [ ] ",
	
	M1ModemTest_00000001,		// "  <Modem Test>  ",
	
	M1ICCardTest_0000001,		// " <IC Card Test> ",
	M1ReadIFMFWVersion_1,		// "Read F/W Version",
	M1SelectSlotNo_00001,		// " Select SLOT[ ] ",
	M1SlotNoRange_000001,		// "     0 - 4      ",
	M1ICCardOKMessage_01,		// "   IC Card OK   ",
	M1ICCardNGMessage_01,		// " IC Card Error! ",
	M1IFMErrorMessage_01,		// "H/W No Response!",
	M1ICCardTestOKMsg_01,		// "IC Card Test OK!",
	M1ICCardTestNGMsg_01,		// "IC Card Test NG!",
	
	M1KeyTest_0000000001,		// "   <KEY Test>   ",
	M1KeyTestOKMsg_00001,		// "  Key Test OK!  ",
	M1KeyTestNGMsg_00001,		// "  Key Test NG!  ",
	
	M1LCDTestMenu_000001,		// "   <LCD Test>   ",
	M1LCDTestMenu_000002,		// "1.Backlight Test",
	M1LCDTestMenu_000003,		// "2.Dot Test      ",
	M1LCDTestMenu_000004,		// "3.Contrast Test ",
	M1LCDBacklightTest_1,		// "<Backlight Test>",
	M1LCDBacklightOff_01,		// " Backlight OFF  ",
	M1LCDBacklightOn_001,		// "  Backlight ON  ",
	M1LCDContrastTest_01,		// "<Contrast  Test>",
	
	M1RS232Test_00000001,		// "  <RS232 Test>  ",
	M1DownloadPort_00001,		// "1.Download -    ",
	M1DownloadPortOK_001,		// "1.Download - OK ",
	M1DownloadPortNG_001,		// "1.Download - NG ",
	M1Serial2Port_000001,		// "2.Serial 2 -    ",
	M1Serial2PortOK_0001,		// "2.Serial 2 - OK ",
	M1Serial2PortNG_0001,		// "2.Serial 2 - NG ",
	
	M1RTCTest_0000000001,		// "   <RTC Test>   ",
	M1RTCTestOK_00000001,		// "     RTC OK     ",
	M1RTCTestNG_00000001,		// "   RTC Error!   ",
	
	
	//*******************************************
	//				F1 Functions
	//*******************************************
/* B sispp 20111013 */
	M1Supervisor_0000001,		// "   Supervisor   ",
	M1Supervisor_0000002,		// "1.Reversal      ",
	M1Supervisor_0000003,		// "2.Balance       ",
	M1Supervisor_0000004,		// "3.End-of-Day    ",
	M1Supervisor_0000005,		// "4.Setup POS     ",
	M1Supervisor_0000006,		// "5.RemoteDownload",
	M1Supervisor_0000007,		// "6.Change PIN    ",

	M1EndOfDay_000000001,		// "   End of Day   ",
	M1EndOfDay_000000002,		// "1.Today         ",
	M1EndOfDay_000000003,		// "2.Print Last Txn",
	M1EndOfDay_000000004,		// "                ",

	M1SVSetupPOS_0000001,		// "Setup POS Status",
	M1SVSetupPOS_0000002,		// "1.Set CallHome  ",
	M1SVSetupPOS_0000003,		// "2.Set Timeout   ",
	M1SVSetupPOS_0000004,		// "3.Set Date      ",
	M1SVSetupPOS_0000005,		// "4.Set Time      ",
	M1SVSetupPOS_0000006,		// "5.Set Contrast  ",
	M1SVSetupPOS_0000007,		// "6.Set Beep Sound",
	
	M1Reversal_000000001,		// "    Reversal    ",
	M1EnterStan_00000001,		// "Enter Stan:     ",
	M1Bracket08_00000001,		// "   [        ]   ",

	M1PastDay_0000000001,		// "    Past Day    ",
	M1EnterDate_00000001,		// "Enter Date in   ",
	M1DDMMYYFmt_00000001,		// "   DDMMYY format",
	M1Bracket08_00000002,		// " [        ]     ",

	M1CallHome_000000001,		// "   Call Home    ",
	M1EnterInterval_0001,		// "Enter Interval  ",
	M1DiscountValue_0001,		// "                ",	// RFU
	
	M1CommTimeout_000001,		// " Comm. Timeout  ",
	M1EnterTimeout_00001,		// "Enter Timeout   ",
	M1TimeoutValue_00001,		// "     [    ]     ",

	M1SetDate_0000000001,		// "Set Date        ",
	M1YYYYMMDD_000000001,		// "    YYYYMMDD    ",
	M1LeftArrow_00000001,		// "=>              ",

	M1SetTime_0000000001,		// "Set Time        ",
	M1hhmmss_00000000001,		// "    hhmmss      ",

	M1LCDContrast_000001,		// "LCD Contrast    ",
	M1DarkLignt_00000001,		// "1:Light 2:Dark  ",
	
	M1BeepSound_00000001,		// "Beep Sound      ",
	M1OFF_00000000000001,		// "1.OFF           ",
	M1ON_000000000000001,		// "2.ON            ",

	M1TMSMenu_0000000001,		// "Remote Download ",
	M1TMSMenu_0000000011,		// "1.TMS Server    ",
	M1TMSMenu_0000000012,		// "2.TMS Download  ",

/* E sispp 20111013 */

	M1MainMenu_000000001,		// "Main Menu       ",
	M1MainMenu_000000002,		// "1.Cashier       ",
	M1MainMenu_000000003,		// "2.Merchant      ",
	M1MainMenu_000000004,		// "3.Setup POS     ",
	
	M1MerchantMenu_00001,		// "Merchant Menu   ",
	M1MerchantMenu_00002,		// "1.Merchant Oper.",
	M1MerchantMenu_00003,		// "2.POS Operations",
	M1MerchantMenu_00004,		// "3.Store Oper.   ",
	M1MerchantMenu_00005,		// "4.EOD Operations",
	M1MerchantMenu_00006,		// "5.Refund        ",
	M1MerchantMenu_00007,		// "6.Change PIN    ",
	M1MerchantMenu_00008,		// "7.Transfer Log  ",
	M1MerchantMenu_00009,		// "8.Set Telephone ",
	M1MerchantMenu_00010,		// "9.RemoteDownload",
	
	M1MerchantMenu_10001,		// "Merchant Menu   ",
	M1MerchantMenu_10002,		// "1.Merchant Oper.",
	M1MerchantMenu_10003,		// "2.POS Operations",
	M1MerchantMenu_10004,		// "3.Store Oper.   ",
	M1MerchantMenu_10005,		// "4.EOD Operations",
	M1MerchantMenu_10006,		// "5.Refund        ",
	M1MerchantMenu_10007,		// "6.Change PIN    ",
	M1MerchantMenu_10008,		// "7.Transfer Log  ",
	M1MerchantMenu_10009,		// "8.Set Ethernet  ",
	M1MerchantMenu_10010,		// "9.RemoteDownload",
	
	M1MerchantMenu_20001,		// "Merchant Menu   ",
	M1MerchantMenu_20002,		// "1.Merchant Oper.",
	M1MerchantMenu_20003,		// "2.POS Operations",
	M1MerchantMenu_20004,		// "3.Store Oper.   ",
	M1MerchantMenu_20005,		// "4.EOD Operations",
	M1MerchantMenu_20006,		// "5.Refund        ",
	M1MerchantMenu_20007,		// "6.Change PIN    ",
	M1MerchantMenu_20008,		// "7.Transfer Log  ",
	M1MerchantMenu_20009,		// "8.Set GSM       ",
	M1MerchantMenu_20010,		// "9.RemoteDownload",
	
	M1MerchantOper_00001,		// "Merchant Oper.  ",
	M1MerchantOper_00002,		// "1.Current Total ",
	M1MerchantOper_00003,		// "2.Previous Total",
	M1MerchantOper_00004,		// "3.Clear Total   ",
	
	M1POSOperations_0001,		// "POS Operations  ",
	M1POSOperations_0002,		// "1.Current Total ",
	M1POSOperations_0003,		// "2.Previous Total",
	M1POSOperations_0004,		// "3.Clear Total   ",
	M1POSOperations_0005,		// "4.POS Balance   ",
	
	M1StoreOperations_01,		// "Store Operations",
	M1StoreOperations_02,		// "1.Current Total ",
	M1StoreOperations_03,		// "2.Previous Total",
	M1StoreOperations_04,		// "3.Clear Total   ",
	M1StoreOperations_05,		// "4.Open Store    ",
	M1StoreOperations_06,		// "5.Close Store   ",
	
	M1EODOperations_0001,		// "EOD Operations  ",
	M1EODOperations_0002,		// "1.Request B.List",
	M1EODOperations_0003,		// "2.EOD           ",
	
	M1SetTelephone_00001,		// "Set Telephone   ",
	M1SetTelephone_00002,		// "1.Access Code   ",
	M1SetTelephone_00003,		// "2.Telephone No  ",
	M1SetTelephone_00004,		// "3.Pulse Dial    ",
	
	M1TMSMenu_0000000002,		// "1.TMS Access    ",
	M1TMSMenu_0000000003,		// "2.TMS Phone No  ",
	M1TMSMenu_0000000004,		// "3.TMS Download  ",
	
	
	//*******************************************
	//				F2 Functions
	//*******************************************
	M1CashierOper_000001,		// "Cashier Oper.   ",
	M1CashierOper_000002,		// "1.Print POS Last",
	M1CashierOper_000003,		// "2.Print Required",
	M1CashierOper_000004,		// "3.Print Last 20 ",
	M1CashierOper_000005,		// "4.Reprint       ",
	M1CashierOper_000006,		// "5.Change PIN    ",
	
	M1ReferenceNo_000001,		// "Reference No.   ",
	
	M1NoTrxnLog_00000001,		// "No Trans. Log   ",
	M1NoMatchedLog_00001,		// "No Matched Log  ",
	M1ExceedReprintCnt_1,		// "Number of       ",
	M1ExceedReprintCnt_2,		// "reprinting has  ",
	M1ExceedReprintCnt_3,		// "exceeded        ",
	
	
	//*******************************************
	//				F3 Functions
	//*******************************************
	M1SetupPOSStatus_001,		// "Setup POS Status",
	M1SetupPOSStatus_002,		// "1.Activate POS  ",
	M1SetupPOSStatus_003,		// "2.Set Language  ",
	M1SetupPOSStatus_004,		// "3.Set Date      ",
	M1SetupPOSStatus_005,		// "4.Set Time      ",
	M1SetupPOSStatus_006,		// "5.Set Contrast  ",
	M1SetupPOSStatus_007,		// "6.Set Beep Sound",
	
	M1SetupPOSStatus_010,		// "1.Deactivate POS",
	M1SetupPOSStatus_011,		// "2.Set Language  ",
	M1SetupPOSStatus_012,		// "3.Set Date      ",
	M1SetupPOSStatus_013,		// "4.Set Time      ",
	M1SetupPOSStatus_014,		// "5.Set Contrast  ",
	M1SetupPOSStatus_015,		// "6.Set Beep Sound",
	
	M1DeactivatePOS_0001,		// "Deactivate POS? ",
	
	M1SetLanguage_000001,		// "Set Language    ",
	M1SetLanguage_000002,		// "1.English       ",
	M1SetLanguage_000003,		// "2.Farsi         ",
	
	M1SelectCalendar_001,		// "Set Date        ",
	M1SelectCalendar_002,		// "1.Iranian Year  ",
	M1SelectCalendar_003,		// "2.Christian Year",
	
	M1IranianYear_000001,		// "Iranian Year    ",
	
	M1ChristianYear_0001,		// "Christian Year  ",
	
	M1DateIsChanged_0001,		// "Date is changed ",
	
	M1TimeIsChanged_0001,		// "Time is changed ",
	
	
	//*******************************************
	//		Password or PIN Error Message
	//*******************************************
	M1WrongPassword_0001,		// "Wrong Password  ",
	
	
	//*******************************************
	//			Transaction Message
	//*******************************************
	M1CustomerTrxnMenu_1,		// "Customer Trans. ",
	
	M1TrxnMenu_000000001,		// " .Purchase      ",
	M1TrxnMenu_000000002,		// " .Recharge      ",
	M1TrxnMenu_000000003,		// " .Buy + ExtPrn  ",
	M1TrxnMenu_000000004,		// " .Balance       ",
	M1TrxnMenu_000000005,		// " .Bill Payment  ",
	M1TrxnMenu_000000006,		// " .Check Bill Pay",
	M1TrxnMenu_000000007,		// " .SIM Charge    ",
	
	M1InputAmount_000001,		// "INPUT AMOUNT    ",
	
	M1EnterYourPIN_00001,		// "Enter your PIN  ",
	
	M1InputCustomerID_01,		// "Customer ID     ",
	
	M1InputBillID_000001,		// "Bill ID         ",
	M1InputPaymentID_001,		// "Payment ID      ",
	
	M1BillID_00000000001,		// "BI:             ",
	M1PaymentID_00000001,		// "PI:             ",
	M1BillPaymentRial_01,		// " Rial",
	M1EnterOrCancel_0001,		// "ENTER or CANCEL?",
	
	M1BillPaymentThis_01,		// "Do you want to  ",
	M1BillPaymentThis_02,		// "pay this bill?  ",
	
	M1BillPaymentMore_01,		// "Do you want to  ",
	M1BillPaymentMore_02,		// "pay another     ",
	M1BillPaymentMore_03,		// "bill?           ",
	
	M1PrintByExtPrn_0001,		// "Do you want to  ",
	M1PrintByExtPrn_0002,		// "send it to the  ",
	M1PrintByExtPrn_0003,		// "extern printer? ",
	
	M1TxDataToExtPrn_001,		// "Sending data to ",
	M1TxDataToExtPrn_002,		// "the external    ",
	M1TxDataToExtPrn_003,		// "printer...      ",
	
	//M1SelCompanyMenu_001,		// "SELECT COMPANY  ",
	//M1SelCompanyMenu_002,		// "1.HAMRAH AVAL   ",
	//M1SelCompanyMenu_003,		// "2.IRANCELL      ",
	//M1SelCompanyMenu_004,		// "3.TALIYA        ",
	//M1SelCompanyMenu_005,		// "4.ESPADANA      ",
	M1SelCompanyMenu_001,		// "GLO             ",
	M1SelCompanyMenu_002,		// "MTN Prepaid     ",
	M1SelCompanyMenu_003,		// "STARCOMMS       ",
	M1SelCompanyMenu_004,		// "ZAIN            ",
	M1SelCompanyMenu_005,		// "RFU             ",
	
	M1SelSIMAmount_00001,		// "GLO 500         ",
	M1SelSIMAmount_00002,		// "GLO 1000        ",
	M1SelSIMAmount_00003,		// "GLO 3000        ",
	M1SelSIMAmount_00004,		// "GLO OTHER       ",
	M1SelSIMAmount_00011,		// "MTN 400         ",
	M1SelSIMAmount_00012,		// "MTN 750         ",
	M1SelSIMAmount_00013,		// "MTN 1500        ",
	M1SelSIMAmount_00014,		// "MTN OTHER       ",
	M1SelSIMAmount_00021,		// "STARCOMMS 500   ",
	M1SelSIMAmount_00022,		// "STARCOMMS OTHER ",
	M1SelSIMAmount_00031,		// "ZAIN 500        ",
	M1SelSIMAmount_00032,		// "ZAIN 1000       ",
	M1SelSIMAmount_00033,		// "ZAIN OTHER      ",
/*
	M1SelSIMAmount_00001,		// "CHARGE AMOUNT   ",
	M1SelSIMAmount_00002,		// "1.    20,000 RLS",
	M1SelSIMAmount_00003,		// "2.    50,000 RLS",
	M1SelSIMAmount_00004,		// "3.   100,000 RLS",
	M1SelSIMAmount_00005,		// "4.   200,000 RLS",
	
	M1SelSIMAmount_00012,		// "1.    20,800 RLS",
	M1SelSIMAmount_00013,		// "2.    52,000 RLS",
	M1SelSIMAmount_00014,		// "3.   104,000 RLS",
*/
	M1Confirmation_00001,		// "--CONFIRMATION--",
	M1SIMAmount20000_001,		// "      20,000 RLS",
	M1SIMAmount20800_001,		// "      20,800 RLS",
	M1SIMAmount50000_001,		// "      50,000 RLS",
	M1SIMAmount52000_001,		// "      52,000 RLS",
	M1SIMAmount100000_01,		// "     100,000 RLS",
	M1SIMAmount104000_01,		// "     104,000 RLS",
	M1SIMAmount200000_01,		// "     200,000 RLS",
	M1HamrahAval_0000001,		// "     HAMRAH AVAL",
	M1Irancell_000000001,		// "        IRANCELL",
	M1Taliya_00000000001,		// "          TALIYA",
	M1Espadana_000000001,		// "        ESPADANA",
	
	M1SelAccountMenu_001,		// "SELECT ACCOUNT  ",
	M1SelAccountMenu_002,		// " .              ",
		
	M1SelAmountMenu_0001,		// "SELECT AMOUNT   ",
	M1SelAmountMenu_0002,		// " .           RLS",
	M1SelAmountMenu_0003,		// " .Other         ",
	
	M1SelAccount_0000001,		// "1.Current       ",
	M1SelAccount_0000002,		// "2.Saving        ",
	M1SelAccount_0000003,		// "3.Credit        ",
	M1SelAccount_0000004,		// "4.Default       ",
	
	M1EnterLast4_0000001,		// "Enter last 4    ",
	M1EnterLast4_0000002,		// "Digits of CardNo",
	M1Bracket06_00000001,		// "    [      ]    ",
	
	M1EnterPhoneNo_00001,		// "Enter Phone No  ",
	M1ConfirmPhoneNo_001,		// "Confirm Phone No",
	M1Bracket14_00000001,		// "[              ]",
	
	//*******************************************
	//		Smart Card Message (Credit Card)
	//*******************************************
	M1IFMnoResponse_0001,		// "IC card         ",
	M1IFMnoResponse_0002,		// "interface module",
	M1IFMnoResponse_0003,		// "doesn't response",
	
	M1SwipeDebitCard_001,		// "Swipe Debit Card",
	M1SwipeDebitCard_002,		// "                ",
	
	M1InvalidAmount_0001,		// "Invalid Amount  ",
	M1InsertYourCard_001,		// "Insert your card",
	M1CardIsDetected_001,		// "Card is detected",
	M1CheckingCard_00001,		// "Checking card...",
	M1CardError_00000001,		// "Card error      ",
	M1InvalidCard_000001,		// "Invalid card    ",
	M1InvalidPIN_0000001,		// "Invalid PIN     ",
	M1ReadingError_00001,		// "Reading error   ",
	M1NotEffective_00001,		// "Not effective   ",
	M1CardHasExpired_001,		// "Card has expired",
	M1CardIsActive_00001,		// "Card is active  ",
	M1IsNotActive_000001,		// "Is not active   ",
	M1AccountBlocked_001,		// "Account blocked ",
	M1IsNotBlocked_00001,		// "Is not blocked  ",
	M1CardIsBlocked_0001,		// "Card is blocked ",
	M1PINNotChanged_0001,		// "PIN not changed ",
	M1MismatchPAN_000001,		// "Mismatch PAN    ",
	
	M1CheckBlackList_001,		// "Checking        ",
	M1CheckBlackList_002,		// "Black List...   ",
	M1NotBlackList_00001,		// "Black List is   ",
	M1NotBlackList_00002,		// "not ready.      ",
	M1NotBlackList_00003,		// "Do you continue?",
	M1NotBlackList_00004,		// "ENTER or CANCEL ",
	M1UpdateCardData_001,		// "Updating smart  ",
	M1UpdateCardData_002,		// "card data...    ",
	M1UpdateCardDataEr_1,		// "Smart card data ",
	M1UpdateCardDataEr_2,		// "is not updated  ",
	M1RequesBlackList_01,		// "Requesting Black",
	M1RequesBlackList_02,		// "List...         ",
	
	M1EjectYourCard_0001,		// "Eject your card ",
	
	M1ReferralCall_00001,		// "1.  goto ON_LINE",
	M1ReferralCall_00002,		// "2.       APPROVE",
	M1ReferralCall_00003,		// "3.       DECLINE",
	M1PleaseSelect_00001,		// "PLEASE SELECT   ",
	
	M1OnlineProc_0000001,		// "On Line Process ",
	M1OfflineProc_000001,		// "OffLine Process ",
	
	M1CardReading_000001,		// "CARD READING... ",
	M1CardDetected_00001,		// "CARD DETECTED.. ",
	M1PleaseWait_0000001,		// "PLEASE WAIT     ",
	M1PleaseEnterPIN_001,		// "PLEASE ENTER PIN",
	M1EnterOnlinePIN_001,		// "   ONLINE PIN   ",
	M1EnterOfflinePIN_01,		// "  OFFLINE PIN   ",
	M1LastPINTry_0000001,		// "LAST PIN TRY!   ",
	M1IncorrectPIN_00001,		// "INCORRECT PIN   ",
	M1TryAgain_000000001,		// "TRY AGAIN       ",
	M1PINOK_000000000001,		// "PIN OK          ",

	M1NoIFMdetected_0001,		// "No IFM detected.",
	M1UseMSR_00000000001,		// "USE MAG STRIPE  ",
	M1IFMdetected_000001,		// "IFM detected....",
	M1UseChipReader_0001,		// "USE CHIP READER ",
	M1EmvApplication_001,		// "EMV APPLICATION ",
	
	M1CallYourBank_00001,		// "CALL YOUR BANK  ",
	M1CancelOrEnter_0001,		// "CANCEL OR ENTER ",
	M1IssuerReferral_001,		// "ISSUER REFERRAL ",

	//*******************************************
	//		Connection Condition Error Message
	//*******************************************
	M1POSNotActive_00001,		// "POS isn't active",
	M1NoTerminalID_00001,		// "No Terminal ID  ",
	M1NoMerchantID_00001,		// "No Merchant ID  ",
	M1NoTransaction_0001,		// "No Transaction  ",
	M1PhoneNumber_000001,		// "Phone Number    ",
	M1NoEOD_000000000001,		// "No EOD          ",
	M1NoBlackList_000001,		// "No Black List   ",
	M1NoTMSServer_000001,		// "No TMS Server   ",
	M1NoLocalIP_00000001,		// "No Local IP     ",
	M1NoSubnetMask_00001,		// "No Subnet Mask  ",
	M1NoGateway_00000001,		// "No Gateway      ",
	M1NoLocalPortNo_0001,		// "No Local Port No",
	M1NoLocalTimeout_001,		// "No Local Timeout",
	M1NoServerIP_0000001,		// "Server IP       ",
	M1NoServerPortNo_001,		// "Server Port No  ",
	M1NoIP_0000000000001,		// "IP              ",
	M1NoPortNo_000000001,		// "Port No         ",
	M1NoPrinterPaper_001,		// "No Printer Paper",
	
	
	//*******************************************
	//	Transaction Active Status Error Message
	//*******************************************
	M1TrxnMenuNotActive1,		// "Transaction menu",
	M1TrxnMenuNotActive2,		// "is not active   ",
	
	M1TrxnNameNotSet0001,		// "Please set the  ",
	M1TrxnNameNotSet0002,		// "transaction     ",
	M1TrxnNameNotSet0003,		// "names           ",
	
	M1TrxnAmountNotSet01,		// "Please set the  ",
	M1TrxnAmountNotSet02,		// "transaction     ",
	M1TrxnAmountNotSet03,		// "amounts         ",
	
	M1TrxnAmountOver0001,		// "Please try again",
	M1TrxnAmountOver0002,		// "Amount has      ",
	M1TrxnAmountOver0003,		// "exceeded maximum",
	M1TrxnAmountOver0004,		// "amount          ",
	
	//*******************************************
	//				Reversal Message
	//*******************************************
	M1ReversalMsg_000001,		// "Reversal        ",
	M1ReversalMsg_000002,		// "not finished    ",
	M1ReversalMsg_000003,		// "correctly       ",
	
	M1ReversalMsg_000004,		// "Insert paper and",
	M1ReversalMsg_000005,		// "Press ENTER key ",
	
	M1ReversalMenu_00001,		// "1.Reversal      ",
	M1ReversalMenu_00002,		// "2.Set Telephone ",
	
	M1ReversalMenu_00011,		// "1.Reversal      ",
	M1ReversalMenu_00012,		// "2.Set Ethernet  ",
	
	M1ReversalMenu_00021,		// "1.Reversal      ",
	M1ReversalMenu_00022,		// "2.Set GSM       ",
	M1ReversalMenu_00023,		// "3.Print & Clear ",
	
	M1ReversalFailMsg_01,		// "Reversal        ",
	M1ReversalFailMsg_02,		// "is impossible   ",
	
	
	//*******************************************
	//				MSR Message
	//*******************************************
	M1InsertSwipeCard_01,		// "Please Insert or",
	M1SwipeYourCard_0001,		// "Swipe your card ",
	M1Track1Error_000001,		// "Track 1 Error!  ",
	M1Track2Error_000001,		// "Track 2 Error!  ",
	M1Track3Error_000001,		// "Track 3 Error!  ",
	M1MSRError_000000001,		// "   MSR Error!   ",
	M1TrackDataError_001,		// "Track Data Error",
	M1TryAgain_000000001,		// "Try again       ",
	
	
	//*******************************************
	//				Modem Message
	//*******************************************
	M1DialUpModemMsg_001,		// "<DIAL-UP MODEM> ",
	M1EthernetMsg_000001,		// "   <ETHERNET>   ",
	M1GSMMsg_00000000001,		// "     <GSM>      ",
	
	M1DialingNow_0000001,		// "  DIALING NOW   ",
	M1RedialingNow_00001,		// " REDIALING NOW  ",
	M1LineConnected_0001,		// " LINE CONNECTED ",
	M1SendingData_000001,		// "SENDING DATA... ",
	M1ReceivingData_0001,		// "RECEIVING DATA..",
	M1ConnectingNow_0001,		// " CONNECTING NOW ",
	M1ReconnectingNow_01,		// "RECONNECTING NOW",
	
	M1ModemNoResponse_01,		// "Modem NoResponse",
	M1ModemError_0000001,		// "Modem Error     ",
	M1S7TimeoutError_001,		// "Timeout(S7)     ",
	M1NoDialToneError_01,		// "No Dial Tone    ",
	M1LineBusyError_0001,		// "Busy            ",
	M1NoCarrierError_001,		// "No Carrier      ",
	M1CommTimeoutError_1,		// "COMM Timeout    ",
	
	M1CommError_00000001,		// "Communication   ",
	M1CommError_00000002,		// "error.          ",
	
	M1SSLTrmCAError_0001,		// "Terminal CA     ",
	M1SSLTrmCAError_0002,		// "certificate data",
	M1SSLTrmCAError_0003,		// "error.          ",
	
	M1SSLInitialError_01,		// "SSL             ",
	M1SSLInitialError_02,		// "initialization  ",
	M1SSLInitialError_03,		// "error.          ",
	
	M1SSLHandshaking_001,		// "SSL             ",
	M1SSLHandshaking_002,		// "handshaking     ",
	M1SSLHandshaking_003,		// "now...          ",
	
	M1SSLHandshakeErr_01,		// "SSL             ",
	M1SSLHandshakeErr_02,		// "handshaking     ",
	M1SSLHandshakeErr_03,		// "error.          ",
	
	M1GSMnoResponse_0001,		// "   GSM module   ",
	M1GSMnoResponse_0002,		// "doesn't response",
	
	M1SIMfailure_0000001,		// "SIM not inserted",
	M1SIMfailure_0000002,		// "or failure      ",
	
	M1SIMisBlocked_00001,		// "SIM is blocked  ",
	
	M1CHV1isRequired_001,		// "CHV1 is required",
	
	M1PUK1isRequired_001,		// "PUK1 is required",
	
	M1CHV2isRequired_001,		// "CHV2 is required",
	
	M1PUK2isRequired_001,		// "PUK2 is required",
	
	M1SIMlockIsRequire_1,		// "SIM lock        ",
	M1SIMlockIsRequire_2,		// "(phone-to-SIM)  ",
	M1SIMlockIsRequire_3,		// "is required     ",
	
	M1NetworkPerRequire1,		// "network         ",
	M1NetworkPerRequire2,		// "personalization ",
	M1NetworkPerRequire3,		// "is required     ",
	
	M1NetworkSubRequire1,		// "network subset  ",
	M1NetworkSubRequire2,		// "is required     ",
	
	M1SVCroviderRequire1,		// "service provider",
	M1SVCroviderRequire2,		// "is required     ",
	
	M1CorporateRequired1,		// "corporate       ",
	M1CorporateRequired2,		// "is required     ",
	
	M1PHSIMPUKRequired_1,		// "PH-SIM PUK      "
	M1PHSIMPUKRequired_2,		// "(master phone   "
	M1PHSIMPUKRequired_3,		// "code) required  "
	
	M1NoSignal_000000001,		// "No Signal       ",
	
	M1NotRegistered_0001,		// "is not          ",
	M1NotRegistered_0002,		// "registered      ",
	
	M1RegisterDenied_001,		// "registration    ",
	M1RegisterDenied_002,		// "denied          ",
	
	M1UnknownRegStatus_1,		// "unknown network ",
	M1UnknownRegStatus_2,		// "status          ",
	
	
	//*******************************************
	//				Print Message
	//*******************************************
	M1CanNotPrintMenu_01,		// "Can not Print!  ",
	M1CanNotPrintMenu_02,		// "1.Reprint       ",
	M1CanNotPrintMenu_03,		// "2.Exit          ",
	
	M1ReprintMsg_0000001,		// "Reprint         ",
	M1PrintingNow_000001,		// "Printing Now... ",
	
	M1CutReceiptMsg_0001,		// "Please cut a    ",
	M1CutReceiptMsg_0002,		// "receipt         ",
	M1PressEnterKey_0001,		// "Press ENTER Key ",
	
	M1ProcessingMsg_0001,		// "Processing...   ",
	M1SelectPrintExit_01,		// "1.Print         ",
	M1SelectPrintExit_02,		// "2.Exit          ",
	
	M1Bill2ndReceipt_001,		// "Second Receipt  ",
	
	
	//*******************************************
	//		Response Code Message
	//*******************************************
	M1ReversalIsClear_01,		// "Reversal        ",
	M1ReversalIsClear_02,		// "is cleared      ",
	
	M1StoreIsOpened_0001,		// "Store is opened ",
	
	M1StoreIsClosed_0001,		// "Store is closed ",
	
	M1BillNotPaid_000001,		// "The Bill has not",
	M1BillNotPaid_000002,		// "been paid before",
	
	M1SoldOutSIM_0000001,		// "SIMs for this   ",
	M1SoldOutSIM_0000002,		// "amount are      ",
	M1SoldOutSIM_0000003,		// "already sold out",
	
	M1RespCode00_0000001,		// "Transaction has ",
	M1RespCode00_0000002,		// "finished        ",
	M1RespCode00_0000003,		// "correctly       ",
	
	M1RespCode02_0000001,		// "Reversal has    ",
	M1RespCode02_0000002,		// "been done before",
	
	M1RespCode03_0000001,		// "Card Acceptor is",
	M1RespCode03_0000002,		// "not identified  ",
	
	M1RespCode06_0000001,		// "System Error    ",
	
	M1RespCode12_0000001,		// "The message is  ",
	M1RespCode12_0000002,		// "not correct for ",
	M1RespCode12_0000003,		// "doing this trxn ",
	
	M1RespCode13_0000001,		// "Amount is not   ",
	M1RespCode13_0000002,		// "correct         ",
	
	M1RespCode14_0000001,		// "Card number is  ",
	M1RespCode14_0000002,		// "not identified  ",
	
	M1RespCode15_0000001,		// "Opened before   ",
	
	M1RespCode16_0000001,		// "Close before    ",
	
	M1RespCode19_0000001,		// "Balance is not  ",
	M1RespCode19_0000002,		// "correct         ",
	
	M1RespCode24_0000001,		// "The EOD trxn has",
	M1RespCode24_0000002,		// "not finished    ",
	M1RespCode24_0000003,		// "correctly       ",
	
	M1RespCode25_0000001,		// "Transaction is  ",
	M1RespCode25_0000002,		// "not acceptable  ",
	
	M1RespCode29_0000001,		// "The EOD trxn is ",
	M1RespCode29_0000002,		// "not done        ",
	
	M1RespCode30_0000001,		// "Format is not   ",
	M1RespCode30_0000002,		// "corret          ",
	
	M1RespCode33_0000001,		// "Card has expired",
	
	M1RespCode34_0000001,		// "The trxn has not",
	M1RespCode34_0000002,		// "been approved   ",
	
	M1RespCode40_0000001,		// "Not identified  ",
	M1RespCode40_0000002,		// "transaction     ",
	
	M1RespCode41_0000001,		// "Restricted card ",
	
	M1RespCode43_0000001,		// "Stolen card     ",
	
	M1RespCode44_0000001,		// "The entered     ",
	M1RespCode44_0000002,		// "information is  ",
	M1RespCode44_0000003,		// "wrong           ",
	
	M1RespCode48_0000001,		// "The Bill has    ",
	M1RespCode48_0000002,		// "been paid before",
	
	M1RespCode51_0000001,		// "Insufficient    ",
	M1RespCode51_0000002,		// "balance         ",
	
	M1RespCode55_0000001,		// "Invalid PIN     ",
	
	M1RespCode56_0000001,		// "Invalid card    ",
	
	M1RespCode57_0000001,		// "Illegal         ",
	M1RespCode57_0000002,		// "transaction     ",
	
	M1RespCode60_0000001,		// "Black list is   ",
	M1RespCode60_0000002,		// "not ready       ",
	
	M1RespCode61_0000001,		// "Amount of trans.",
	M1RespCode61_0000002,		// "has exceeded    ",
	
	M1RespCode62_0000001,		// "Amount of trans.",
	M1RespCode62_0000002,		// "for one day has ",
	M1RespCode62_0000003,		// "exceeded        ",
	
	M1RespCode64_0000001,		// "Transmitted trxn",
	M1RespCode64_0000002,		// "are not correct ",
	
	M1RespCode65_0000001,		// "Number of trans.",
	M1RespCode65_0000002,		// "has exceeded    ",
	
	M1RespCode66_0000001,		// "Number of trans.",
	M1RespCode66_0000002,		// "for one day has ",
	M1RespCode66_0000003,		// "exceeded        ",
	
	M1RespCode68_0000001,		// "Debit is not    ",
	M1RespCode68_0000002,		// "correct         ",
	
	M1RespCode70_0000001,		// "Balance is not  ",
	M1RespCode70_0000002,		// "correct & black ",
	M1RespCode70_0000003,		// "list isn't ready",
	
	M1RespCode71_0000001,		// "Trxns are not   ",
	M1RespCode71_0000002,		// "correct & black ",
	M1RespCode71_0000003,		// "list isn't ready",
	
	M1RespCode75_0000001,		// "No of invalid   ",
	M1RespCode75_0000002,		// "PIN entry       ",
	M1RespCode75_0000003,		// "has exceeded    ",
	
	M1RespCode77_0000001,		// "Financial day is",
	M1RespCode77_0000002,		// "not defined     ",
	
	M1RespCode78_0000001,		// "Card is not     ",
	M1RespCode78_0000002,		// "active          ",
	
	M1RespCode79_0000001,		// "Account has     ",
	M1RespCode79_0000002,		// "not identified  ",
	
	M1RespCode80_0000001,		// "Trxn is not     ",
	M1RespCode80_0000002,		// "accepted due to ",
	M1RespCode80_0000003,		// "account problem ",
	
	M1RespCode81_0000001,		// "Card has been   ",
	M1RespCode81_0000002,		// "canceled        ",
	
	M1RespCode83_0000001,		// "Central system  ",
	M1RespCode83_0000002,		// "is not ready    ",
	
	M1RespCode84_0000001,		// "Central system  ",
	M1RespCode84_0000002,		// "is not active   ",
	
	M1RespCode85_0000001,		// "Central system  ",
	M1RespCode85_0000002,		// "internal error  ",
	
	M1RespCode86_0000001,		// "Trxn is not     ",
	M1RespCode86_0000002,		// "authorized on   ",
	M1RespCode86_0000003,		// "this terminal   ",
	
	M1RespCode87_0000001,		// "System internal ",
	M1RespCode87_0000002,		// "error           ",
	
	M1RespCode88_0000001,		// "System internal ",
	M1RespCode88_0000002,		// "error           ",
	
	M1RespCode89_0000001,		// "System internal ",
	M1RespCode89_0000002,		// "error           ",
	
	M1RespCode90_0000001,		// "Communication   ",
	M1RespCode90_0000002,		// "during process  ",
	M1RespCode90_0000003,		// "is lost         ",
	
	M1RespCode91_0000001,		// "No response from",
	M1RespCode91_0000002,		// "Central system  ",
	
	M1RespCode92_0000001,		// "Transmitter is  ",
	M1RespCode92_0000002,		// "not valid       ",
	
	M1RespCode93_0000001,		// "No response due ",
	M1RespCode93_0000002,		// "to high traffic ",
	M1RespCode93_0000003,		// "in CentralSystem",
	
	M1RespCode94_0000001,		// "Transaction No. ",
	M1RespCode94_0000002,		// "has duplicated  ",
	
	M1RespCode96_0000001,		// "System internal ",
	M1RespCode96_0000002,		// "error           ",
	
	M1RespCodeUnknown_01,		// "Unknown code    ",
	
	M1ServerDataError_01,		// "Server Data Err ",
	
	
	//*******************************************
	//				TMS
	//*******************************************
	M1BaudRateIsLow_0001,		// "Baud rate is low",
	M1ReceivedENQ_000001,		// " Received <ENQ> ",
	M1PgmDownload_000001,		// "PROGRAM DOWNLOAD",
	M1ParamDownload_0001,		// "PARAMETER DOWN  ",
	M1SendCommStart_0001,		// "Send COMM Start ",
	M1RxDownloadEnd_0001,		// "Rx Download End ",
	M1SendDataACK_000001,		// "Send Data <ACK> ",
	M1SendDataNAK_000001,		// "Send Data <NAK> ",
	M1SendEndACK_0000001,		// " Send End <ACK> ",
	M1SendEndNAK_0000001,		// " Send End <NAK> ",
	M1DownloadError_0001,		// " Download Error ",
	M1FileSizeOver_00001,		// "Download File   ",
	M1FileSizeOver_00002,		// "Size Over!      ",
	M1PgmUpgadeAddrErr_1,		// "Program Upgrade ",
	M1PgmUpgadeAddrErr_2,		// "Address Error!  ",
	M1ParamSizeOver_0001,		// "Parameter size  ",
	M1ParamSizeOver_0002,		// "Over!           ",
	M1RxLRCError_0000001,		// " Rx LRC Error ! ",
	M1TxLRCError_0000001,		// " Tx LRC Error ! ",
	M1CommandError_00001,		// "Command Error ! ",
	M1SectorLRCError_001,		// "Sector LRC Error",
	M1PacketSizeOver_001,		// "Data Packet     ",
	M1PacketSizeOver_002,		// "Size Over!      ",
	M1SectorNoError_0001,		// "Sector No. Error",
	M1PacketSizeError_01,		// "Data Packet     ",
	M1PacketSizeError_02,		// "Size Error      ",
	
	M1PgmDownComplete_01,		// "PGMDown Complete",
	M1SizeMismatch_00001,		// "Size mismatch ! ",
	M1FileLRCError_00001,		// "File LRC Error !",
	M1AppSizeOver_000001,		// "Application     ",
	M1AppSizeOver_000002,		// "Size Over!      ",
	M1DataProcessing_001,		// "Data Processing ",
	M1PgmSizeError_00001,		// "PGM Size Error! ",
	M1BIOSNotSupport_001,		// "BIOS Not Support",
	M1LimitationError_01,		// "Limitation Error",
	
	M1PgmUpgradeCheck_01,		// "Program Upgrade ",
	M1PgmUpgradeCheck_02,		// "Checking Now... ",
	
	M1ParamDownComplete1,		// "PARDown Complete",
	M1PgmUpgradeOK_00001,		// "PGM Upgrade OK !",
	M1FileSizeError_0001,		// "File Size Error!",
	M1ParameterUpgrade_1,		// "Parameter       ",
	M1ParameterUpgrade_2,		// "Upgrading Now...",
	
	M1NotSupportParam_01,		// "Sorry, it does  ",
	M1NotSupportParam_02,		// "not support     ",
	M1NotSupportParam_03,		// "parameter       ",
	M1NotSupportParam_04,		// "upgrade now     ",
	
	
	//*******************************************
	//	Space Message
	//*******************************************
	M1_____________Space,		// "                ",
	
} _eMsg1;

/* */
