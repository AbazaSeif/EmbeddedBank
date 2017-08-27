
/*======================================================================*/
/*																		*/
/*								LCDMSG4.H								*/
/*																		*/
/*======================================================================*/

typedef enum {
	//********************************************
	//				System Message
	//********************************************
	// "This is test    ", "appication for  ", "demonstration   ", "                "
	M4TestAppMsg_0000001,
	
	// "This is demo    ", "appication.     ", "---- Expire ----", "   21/03/2011   ",
	M4DemoAppMsg_0000001,
	
	// "   Initialize   ", "     System     ", "                ", " Please Wait... "
	M4SystemCheckMsg_001,
	
	// "This application", "does not support", "unknow model... ", "                "
	M4UnknownModelMsg_01,
	
	// "Please replace a", "RTC backup      ", "battery with a  ", "new one         "
	M4BackupBatErrMsg_01,
	
	// "   Initialize   ", "   GSM module   ", "                ", " Please Wait... "
	M4GSMCheckMsg_000001,
	
	
	//********************************************
	//				Special Functions
	//********************************************
	// "Enter Password  ", "                ", "                ", "                "
	M4EnterPassword_0001,
	
	// "  Maintenance   ", "1.Setup Terminal", "2.POS Info.     ", "3.Initialize    "
	M4MaintenanceMenu_01,
	
	// " Setup Terminal ", "1.Setup Modem   ", "2.Set Parameters", "3.Download Param"
	M4SetupTrmMenu_00001,

	// "SELECT MODEM    ", "1.Dial-up       ", "2.Ethernet      ", "3.GSM           "
	M4SelectModemMenu_01,
	
	// "Dial-up Modem   ", "1.Set Parameters", "2.Access Code   ", "3.Telephone No  "
	M4DialUpModemMenu_01,
	
	// "MODEM SPEED     ", "1.1200BPS       ", "2.2400BPS       ", "                "
	M4DialUpModemSpeed_1,
	// "DIALING TIMEOUT ", "                ", "                ", "                "
	M4DialingTimeout_001,
	// "COMM TIMEOUT    ", "                ", "                ", "                "
	M4CommTimeout_000001,
	// "COMM MODE       ", "1.ASYNC         ", "2.SYNC          ", "                "
	M4CommMode_000000001,
	// "STANDARD        ", "1.CCITT         ", "2.BELL          ", "                "
	M4CommStandard_00001,
	// "DIALING MODE    ", "1.NORMAL MODE   ", "2.BLIND MODE    ", "                "
	M4DialingMode_000001,
	// "PULSE DIAL      ", "1.NO            ", "2.YES           ", "                "
	M4PulseDial_00000001,
	// "PRE-DIALING     ", "1.NO            ", "2.YES           ", "                "
	M4PreDialing_0000001,
	
	// "PABX ACCESS     ", "1.NO            ", "2.YES           ", "                "
	M4PABXAccess_0000001,
	// "PABX ACCESS CODE", "                ", "                ", "                "
	M4PABXAccessCode_001,
	// "CITY ACCESS     ", "1.NO            ", "2.YES           ", "                "
	M4CityAccess_0000001,
	// "CITY ACCESS CODE", "                ", "                ", "                "
	M4CityAccessCode_001,
	
	// "TELEPHONE NO    ", "                ", "                ", "                "
	M4TrxnTelephoneNo_01,
	
	// "EOD Phone No    ", "                ", "                ", "                "
	M4EODTelephoneNo_001,
	
	// "Black List Phone", "                ", "                ", "                "
	M4BListTelephoneNo_1,
	
	// "TMS PHONE NO    ", "                ", "                ", "                "
	M4TMSTelephoneNo_001,
	
	// "Ethernet        ", "1.Set Local     ", "2.Set Server    ", "3.EOD Server    "
	M4EthernetMenu_00001,
	
	// "LOCAL IP ADDRESS", "                ", "                ", "*='.'           "
	M4LocalIPAddress_001,
	// "SUBNET MASK     ", "                ", "                ", "*='.'           "
	M4SubnetMask_0000001,
	// "GATEWAY         ", "                ", "                ", "*='.'           "
	M4Gateway_0000000001,
	// "LOCAL PORT NO   ", "                ", "                ", "                "
	M4LocalPortNo_000001,
	// "LOCAL TIMEOUT   ", "                ", "                ", "                "
	M4LocalTimeout_00001,
	// "Activate SSL?   ", "1.NO            ", "2.YES           ", "                "
	M4ActivateSSL_000001,
	
	// "SERVER IP 1     ", "                ", "                ", "*='.'           "
	M4ServerIPAddress_01,
	// "SERVER PORT NO 1", "                ", "                ", "                "
	M4ServerPortNo_00001,
	// "SERVER IP 2     ", "                ", "                ", "*='.'           "
	M4ServerIPAddress_02,
	// "SERVER PORT NO 2", "                ", "                ", "                "
	M4ServerPortNo_00002,
	
	// "EOD IP 1        ", "                ", "                ", "*='.'           "
	M4EODServerIP_000001,
	// "EOD PORT NO 1   ", "                ", "                ", "                "
	M4EODServerPortNo_01,
	// "EOD IP 2        ", "                ", "                ", "*='.'           "
	M4EODServerIP_000002,
	// "EOD PORT NO 2   ", "                ", "                ", "                "
	M4EODServerPortNo_02,
	
	// "B.List IP 1     ", "                ", "                ", "*='.'           "
	M4BListServerIP_0001,
	// "B.List PORT NO 1", "                ", "                ", "                "
	M4BListServerPortNo1,
	// "B.List IP 2     ", "                ", "                ", "*='.'           "
	M4BListServerIP_0002,
	// "B.List PORT NO 2", "                ", "                ", "                "
	M4BListServerPortNo2,
	
	// "TMS IP 1        ", "                ", "                ", "*='.'           "
	M4TMSServerIP_000001,
	// "TMS PORT NO 1   ", "                ", "                ", "                "
	M4TMSServerPortNo_01,
	// "TMS IP 2        ", "                ", "                ", "*='.'           "
	M4TMSServerIP_000002,
	// "TMS PORT NO 2   ", "                ", "                ", "                "
	M4TMSServerPortNo_02,
	
	// "    GSM/GPRS    ", "1.Set Parameters", "2.Set Server    ", "3.Set TMS Server"
	M4GSMMenu_0000000001,
	
	// "Select SIM      ", "1.SIM1          ", "2.SIM2          ", "                "
	M4GSMSelSIM_00000001,
	
	// "Input APN       ", "                ", "                ", "                "
	M4GSMInputAPN_000001,
	
	// "Input Username  ", "                ", "                ", "                "
	M4GSMInputID_0000001,
	
	// "Input Password  ", "                ", "                ", "                "
	M4GSMInputPWD_000001,
	
	// "Select App.     ", "1.Normal App.   ", "2.Multi-Merchant", "                "
	M4SelectAppMenu_0001,
	
	// "Set Parameters  ", "1.Terminal ID   ", "2.Store Name    ", "3.Sequence No   "
	M4SetParameterMenu_1,
	// "Terminal ID     ", "                ", "                ", "                "
	M4TerminalID_0000001,
	// "Merchant ID     ", "                ", "                ", "                "
	M4MerchantID_0000001,
	// "Store Name      ", "                ", "                ", "                "
	M4StoreName_00000001,
	// "Account Type    ", "                ", "                ", "                "
	M4AccountType_000001,
	// "External Prn    ", "1.Select Printer", "2.Max Prn Copy  ", "3.Setup Paper   "
	M4ExtPrnMenu_0000001,
	// "Select Printer  ", "1.PR4 SL        ", "2.BP-3000       ", "                "
	M4ExtPrnModelMenu_01,
	// "Max Prn Copy    ", "                ", "                ", "                "
	M4ExtPrnMaxCopy_0001,
	// "Setup Paper     ", "1.Left Number   ", "2.Right Number  ", "3.Line Number   "
	M4ExtPrnPaperMenu_01,
	// "Left Number     ", "                ", "                ", "                "
	M4ExtPrnPaperLeft_01,
	// "Right Number    ", "                ", "                ", "                "
	M4ExtPrnPaperRight_1,
	// "Line Number     ", "                ", "                ", "                "
	M4ExtPrnPaperLine_01,
	// "Advertisement 1 ", "                ", "                ", "                "
	M4Advertisement_0001,
	// "Advertisement 2 ", "                ", "                ", "                "
	M4Advertisement_0002,
	// "Advertisement 3 ", "                ", "                ", "                "
	M4Advertisement_0003,
	// "NII             ", "                ", "                ", "                "
	M4NII_00000000000001,
	// "Set Offline     ", "1.Offline No.   ", "2.Offline Amount", "                "
	M4SetOfflineMenu_001,
	// "Offline Number  ", "                ", "                ", "                "
	M4OfflineMaxNo_00001,
	// "Offline Amount  ", "                ", "                ", "                "
	M4OfflineMaxAmount_1,
	// "Terminal ID 1   ", "                ", "                ", "                "
	M4TerminalID1_000001,
	// "Terminal ID 2   ", "                ", "                ", "                "
	M4TerminalID2_000001,
	// "Terminal ID 3   ", "                ", "                ", "                "
	M4TerminalID3_000001,
	// "Terminal ID 4   ", "                ", "                ", "                "
	M4TerminalID4_000001,
	// "Terminal ID 5   ", "                ", "                ", "                "
	M4TerminalID5_000001,
	// "Terminal ID 6   ", "                ", "                ", "                "
	M4TerminalID6_000001,
	// "Terminal ID 7   ", "                ", "                ", "                "
	M4TerminalID7_000001,
	// "Terminal ID 8   ", "                ", "                ", "                "
	M4TerminalID8_000001,
	// "Merchant ID 1   ", "                ", "                ", "                "
	M4MerchantID1_000001,
	// "Merchant ID 2   ", "                ", "                ", "                "
	M4MerchantID2_000001,
	// "Merchant ID 3   ", "                ", "                ", "                "
	M4MerchantID3_000001,
	// "Merchant ID 4   ", "                ", "                ", "                "
	M4MerchantID4_000001,
	// "Merchant ID 5   ", "                ", "                ", "                "
	M4MerchantID5_000001,
	// "Merchant ID 6   ", "                ", "                ", "                "
	M4MerchantID6_000001,
	// "Merchant ID 7   ", "                ", "                ", "                "
	M4MerchantID7_000001,
	// "Merchant ID 8   ", "                ", "                ", "                "
	M4MerchantID8_000001,
	// "Store Name 1    ", "                ", "                ", "                "
	M4StoreName1_0000001,
	// "Store Name 2    ", "                ", "                ", "                "
	M4StoreName2_0000001,
	// "Store Name 3    ", "                ", "                ", "                "
	M4StoreName3_0000001,
	// "Store Name 4    ", "                ", "                ", "                "
	M4StoreName4_0000001,
	// "Store Name 5    ", "                ", "                ", "                "
	M4StoreName5_0000001,
	// "Store Name 6    ", "                ", "                ", "                "
	M4StoreName6_0000001,
	// "Store Name 7    ", "                ", "                ", "                "
	M4StoreName7_0000001,
	// "Store Name 8    ", "                ", "                ", "                "
	M4StoreName8_0000001,
	// "Multi-Merchant  ", "1.Set Trxn Name ", "2.Set Amounts   ", "                "
	M4MultiMerchMenu_001,
	// "Trxn Name 1     ", "                ", "                ", "                "
	M4MultiMerchName_001,
	// "Trxn Name 2     ", "                ", "                ", "                "
	M4MultiMerchName_002,
	// "Trxn Name 3     ", "                ", "                ", "                "
	M4MultiMerchName_003,
	// "Trxn Name 4     ", "                ", "                ", "                "
	M4MultiMerchName_004,
	// "Trxn Name 5     ", "                ", "                ", "                "
	M4MultiMerchName_005,
	// "Trxn Name 6     ", "                ", "                ", "                "
	M4MultiMerchName_006,
	// "Trxn Name 7     ", "                ", "                ", "                "
	M4MultiMerchName_007,
	// "Trxn Name 8     ", "                ", "                ", "                "
	M4MultiMerchName_008,
	// "Set Amounts     ", "1.Set Amounts 1 ", "2.Set Amounts 2 ", "3.Set Amounts 3 ",
	M4SetAmountsMenu_001,
	// "Set Amounts 1   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount1Menu_001,
	// "Set Amounts 2   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount2Menu_001,
	// "Set Amounts 3   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount3Menu_001,
	// "Set Amounts 4   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount4Menu_001,
	// "Set Amounts 5   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount5Menu_001,
	// "Set Amounts 6   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount6Menu_001,
	// "Set Amounts 7   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount7Menu_001,
	// "Set Amounts 8   ", "1.Amount 1      ", "2.Amount 2      ", "3.Amount 3      "
	M4SetAmount8Menu_001,
	// "Amount 1        ", "                ", "                ", "                "
	M4SetAmount1_0000001,
	// "Amount 2        ", "                ", "                ", "                "
	M4SetAmount2_0000001,
	// "Amount 3        ", "                ", "                ", "                "
	M4SetAmount3_0000001,
	// "Maximum Amount  ", "                ", "                ", "                "
	M4SetMaxAmount_00001,
	
	// "Download Params ", "1.App Lists     ", "2.Function Lists", "3.Key Download  "
	M4DownloadParam_0001,
	// " Function List  ", "1.Tams          ", "2.VoucherVault  ", "3.Banking       "
	M4DownFuncList_00001,
	// "  Key Download  ", "1.Master Key    ", "2.Session Key   ", "                "
	M4DownTrxnKeys_00001,
	// " EFT Parameters ", "1.Params        ", "2.EFT Params    ", "3.BIN Tables    "
	M4DownEftParams_0001,
	// " EMV Parameters ", "1.EMV APPs      ", "2.EMV CAPKs     ", "3.Revoke CAPKs  "
	M4DownEmvParams_0001,
	
	// "                ", "                ", "Press ENTER Key ", "to download!    "
	M4ConfirmDownload_01,
	
	// "Activate Menu   ", "1.Buy           ", "2.Balance       ", "3.Bill Payment  "
	M4ActivateMenu_00001,
	
	// "Buy Menu        ", "1.Normal Buy    ", "2.Buy with extra", "3.Buy + ExtPrn  "
	M4ActivateBuyMenu_01,
	
	// "Normal Buy      ", "1.Active        ", "2.Inactive      ", "                "
	M4NormalBuyActive_01,
	
	// "Buy with extra  ", "1.Active        ", "2.Inactive      ", "                "
	M4ExtraBuyActive_001,
	
	// "Buy + ExtPrn    ", "1.Active        ", "2.Inactive      ", "                "
	M4ExtPrnBuyActive_01,
	
	// "Balance         ", "1.Active        ", "2.Inactive      ", "                "
	M4BalanceActive_0001,
	
	// "Bill Payment    ", "1.Active        ", "2.Inactive      ", "                "
	M4BillPayActive_0001,
	
	// "Check Bill Pay  ", "1.Active        ", "2.Inactive      ", "                "
	M4CheckBillActive_01,
	
	// "SIM Charge      ", "1.Active        ", "2.Inactive      ", "                "
	M4SIMChargeActive_01,
	
	// "Buy (Multi)     ", "1.Active        ", "2.Inactive      ", "                "
	M4MultiBuyActive_001,
	
	// "Buy Trxn Name   ", "                ", "                ", "                "
	M4BuyTrxnName_000001,
	
	// "Help Desk Tel No", "                ", "                ", "                "
	M4HelpDeskPhoneNo_01,
	
	// "Activate TMS?   ", "1.NO            ", "2.YES           ", "                "
	M4ActivateTMS_000001,
	
	// "Serial Number   ", "                ", "                ", "                "
	M4SerialNumber_00001,
	
	// "Input S/N       ", "                ", "                ", "                "
	M4InputSN_0000000001,
	
	// "Confirm S/N     ", "                ", "1.NO            ", "2.YES           "
	M4ConfirmSN_00000001,
	
	// "POS Information ", "1.View Info.    ", "2.Print Info.   ", "                "
	M4POSInfoMenu_000001,
	
	// "Terminal ID     ", "                ", "Merchant ID     ", "                "
	M4ViewPOSInfo_000001,
	// "Model Name      ", "                ", "                ", "                "
	M4ViewPOSInfo_000002,
	// "S/W Version     ", "                ", "S/W Date        ", "                "
	M4ViewPOSInfo_000003,
	// "PABX ACCESS     ", "                ", "CITY ACCESS     ", "                "
	M4ViewPOSInfo_000004,
	
	// "Print Info.     ", "                ", "Printing Now... ", "                "
	M4PrintPOSInfo_00001,
	
	// "Transferring    ", "Log...          ", "                ", "See RS232 Output"
	M4TransferLog_000001,
	
	// "Initialize      ", "1.Reset Param.  ", "2.Reset Merchant", "3.Erase POS Logs"
	M4InitializeMenu_001,
	
	// "Reset Parameters", "1.NO            ", "2.YES           ", "                "
	M4ResetParameter_001,
	
	// "Reset Merchant  ", "1.NO            ", "2.YES           ", "                "
	M4ResetMerchant_0001,
	
	// "Erase POS Logs  ", "1.NO            ", "2.YES           ", "                "
	M4ErasePOSLogs_00001,
	
	// "Erase POS Logs  ", "                ", " Please Wait... ", "                "
	M4ErasePOSLogs_00002,
	
	// "New Password    ", "                ", "                ", "                "
	M4NewPassword_000001,
	// "Confirm Password", "                ", "                ", "                "
	M4ConfirmPassword_01,
	
	// "Hardware Test   ", "1.Printer Test  ", "2.MSR Test      ", "3.Modem Test    "
	M4HWTestMenu_0000001,
	
	// " <Printer Test> ", "                ", "Printing Now... ", "                "
	M4PrinterTest_000001,
	
	// " <MSR Test> [ ] ", "                ", "                ", "Swipe your card "
	M4MSRTest_0000000001,
	
	// "  <Modem Test>  ", "                ", "                ", "Press ENTER Key "
	M4ModemTest_00000001,
	
	// " <IC Card Test> ", "                ", "Read F/W Version", "                "
	M4ICCardTest_0000001,
	
	// " <IC Card Test> ", "                ", "IC Card Test OK!", "                "
	M4ICCardTestOKMsg_01,
	
	// " <IC Card Test> ", "                ", "IC Card Test NG!", "                "
	M4ICCardTestNGMsg_01,
	
	// "   <KEY Test>   ", "                ", "  Key Test OK!  ", "                "
	M4KeyTestOKMsg_00001,
	
	// "   <KEY Test>   ", "                ", "  Key Test NG!  ", "                "
	M4KeyTestNGMsg_00001,
	
	// "   <LCD Test>   ", "1.Backlight Test", "2.Dot Test      ", "3.Contrast Test "
	M4LCDTestMenu_000001,
	
	// "<Backlight Test>", "                ", "  Backlight ON  ", "                "
	M4LCDBacklightOff_01,
	
	// "<Contrast  Test>", "                ", "                ", "                "
	M4LCDContrastTest_01,
	
	// "  <RS232 Test>  ", "                ", "                ", "                "
	M4RS232Test_00000001,
	
	// "   <RTC Test>   ", "                ", " Please Wait... ", "                "
	M4RTCTest_0000000001,
	
	
	//*******************************************
	//				F1 Functions
	//*******************************************
/* B sispp 20111013 */
	// "   Supervisor   ", "1.Reversal      ", "2.Balance       ", "3.End-of-Day    "
	M4Supervisor_0000001,
	
	// "   End of Day   ", "1.Today         ", "2.Print Last Txn", "                "
	M4EndOfDay_000000001,
	
	// "Setup POS Status", "1.Set CallHome  ", "2.Set Timeout   ", "3.Set Date      "
	M4SVSetupPOS_0000001,
	
	// "    Reversal    ", "Enter Stan:     ", "[              ]", "                "
	M4Reversal_000000001,
	
	// "    Past Day    ", "Enter Date in   ", "   DDMMYY format", " [        ]     "
	M4PastDay_0000000001,
	
	// "   Call Home    ", "Enter Interval  ", "    [      ]    ", "                "
	M4EnterCallHome_0001,
	
	// " Comm. Timeout  ", "Enter Timeout   ", "     [    ]     ", "                "
	M4EnterCommTimeout_1,
	
	// "Set Date        ", "    YYYYMMDD    ", "                ", "=>              "
	M4SetDate_0000000001,
	
	// "Set Time        ", "    hhmmss      ", "                ", "=>              "
	M4SetTime_0000000001,
	
	// "LCD Contrast    ", "1:Light 2:Dark  ", "                ", "                "
	M4LCDContrast_000001,
	
	// "Beep Sound      ", "1.OFF           ", "2.ON            ", "                "
	M4BeepSound_00000001,
	
	// "Remote Download ", "1.TMS Server    ", "2.TMS Download  ", "                "
	M4TMSMenu_0000000001,
	
	// "SERVER IP 1     ", "                ", "SERVER PORT NO 1", "                "
	M4ViewInfoServer_001,

	// "SERVER IP 2     ", "                ", "SERVER PORT NO 2", "                "
	M4ViewInfoServer_002,

	// "TMS IP 1        ", "                ", "TMS PORT NO 1   ", "                "
	M4ViewInfoTMS_000001,

	// "TMS IP 2        ", "                ", "TMS PORT NO 2   ", "                "
	M4ViewInfoTMS_000002,

	// "     PINPAD     ", "                ", "KEY LOAD READY! ", "                "
	M4PinpadKeyLoad_0001,

	// "                ", "  No Batch No.  ", "                ", "                "
	M4ErrNoBatchNo_00001,

/* E sispp 20111013 */
	
	// "Main Menu       ", "1.Cashier       ", "2.Merchant      ", "                "
	M4MainMenu_000000001,
	
	// "Main Menu       ", "1.Cashier       ", "2.Merchant      ", "3.Setup POS     "
	M4MainMenu_000000002,
	
	// "Merchant Menu   ", "1.Merchant Oper.", "2.POS Operations", "3.Store Oper.   "
	M4MerchantMenu_00001,
	
	// "Merchant Oper.  ", "1.Current Total ", "2.Previous Total", "3.Clear Total   "
	M4MerchantOper_00001,
	
	// "POS Operations  ", "1.Current Total ", "2.Previous Total", "3.Clear Total   "
	M4POSOperations_0001,
	
	// "Store Operations", "1.Current Total ", "2.Previous Total", "3.Clear Total   "
	M4StoreOperations_01,
	
	// "EOD Operations  ", "1.Request B.List", "2.EOD           ", "                "
	M4EODOperations_0001,
	
	// "Set Telephone   ", "1.Access Code   ", "2.Telephone No  ", "3.Pulse Dial    "
	M4SetTelephone_00001,
	
	// "Remote Download ", "1.TMS Server    ", "2.TMS Download  ", "                "
	M4TMSMenu_0000000002,
	
	// "Remote Download ", "1.NO            ", "2.YES           ", "                "
	M4RemoteDownload_001,
	
	
	//*******************************************
	//				F2 Functions
	//*******************************************
	// "Cashier Oper.   ", "1.Print POS Last", "2.Print Required", "3.Print Last 20 "
	M4CashierOper_000001,
	
	// "Reference No.   ", "                ", "                ", "                "
	M4ReferenceNo_000001,
	
	// "Number of       ", "reprinting has  ", "exceeded        ", "                "
	M4ExceedReprintCnt_1,
	
	
	//*******************************************
	//				F3 Functions
	//*******************************************
	// "Setup POS Status", "1.Activate POS  ", "2.Set Language  ", "3.Set Date      "
	M4SetupPOSStatus_001,
	
	// "Setup POS Status", "1.Deactivate POS", "2.Set Language  ", "3.Set Date      "
	M4SetupPOSStatus_002,
	
	// "Deactivate POS? ", "1.NO            ", "2.YES           ", "                "
	M4DeactivatePOS_0001,
	
	// "Set Language    ", "1.English       ", "2.Farsi         ", "                "
	M4SetLanguage_000001,
	
	// "Set Date        ", "1.Iranian Year  ", "2.Christian Year", "                "
	M4SelectCalendar_001,
	
	// "Iranian Year    ", "    YYYYMMDD    ", "                ", "=>              "
	M4IranianYear_000001,
	
	// "Christian Year  ", "    YYYYMMDD    ", "                ", "=>              "
	M4ChristianYear_0001,
	
	// "Set Time        ", "    hhmmss      ", "                ", "=>              "
	M4SetTime_0000000001,
	
	// "LCD Contrast    ", "1:Light 2:Dark  ", "                ", "                "
	M4LCDContrast_000001,
	
	// "Beep Sound      ", "1.OFF           ", "2.ON            ", "                "
	M4BeepSound_00000001,
	
	
	//*******************************************
	//		Password or PIN Error Message
	//*******************************************
	// "????????????????", "????????????????", "????????????????", "Wrong Password  "
	M4WrongPassword_0001,
	
	
	//*******************************************
	//			Transaction Message
	//*******************************************
	// "Customer Trans. ", "                ", "                ", "                "
	M4CustomerTrxnMenu_1,
	
	// "INPUT AMOUNT    ", "                ", "                ", "                "
	M4InputAmount_000001,
	
	// "Enter your PIN  ", "                ", "                ", "                "
	M4EnterYourPIN_00001,
	
	// "Customer ID     ", "                ", "                ", "                "
	M4InputCustomerID_01,
	
	// "Bill ID         ", "                ", "                ", "                "
	M4InputBillID_000001,
	
	// "Payment ID      ", "                ", "                ", "                "
	M4InputPaymentID_001,
	
	// "BI:             ", "PI:             ", "                ", "ENTER or CANCEL?"
	M4ConfirmBillID_0001,
	
	// "Do you want to  ", "pay this bill?  ", "                ", "ENTER or CANCEL?"
	M4BillPaymentThis_01,
	
	// "Do you want to  ", "pay another     ", "bill?           ", "ENTER or CANCEL?"
	M4BillPaymentMore_01,
	
	// "Do you want to  ", "send it to the  ", "extern printer? ", "ENTER or CANCEL?"
	M4PrintByExtPrn_0001,
	
	// "Sending data to ", "the external    ", "printer...      ", " Please Wait... "
	M4TxDataToExtPrn_001,
	
	// "GLO             ", "MTN Prepaid     ", "STARCOMMS       ", "ZAIN            "
	M4SelCompanyMenu_001,
	
	// "GLO 500         ", "GLO 1000        ", "GLO 3000        ", "GLO OTHER       "
	M4SelSIMAmount_00001,

	// "MTN 400         ", "MTN 750         ", "MTN 1500        ", "MTN OTHER       "
	M4SelSIMAmount_00011,

	// "STARCOMMS 500   ", "STARCOMMS OTHER ", "                ", "                "
	M4SelSIMAmount_00021,

	// "ZAIN 500        ", "ZAIN 1000       ", "ZAIN OTHER      ", "                "
	M4SelSIMAmount_00031,
	
	
	// "CHARGE AMOUNT   ", "1.    20,000 RLS", "2.    50,000 RLS", "3.   100,000 RLS"
	M4SelSIMAmount_00001,
	
	// "CHARGE AMOUNT   ", "1.    20,800 RLS", "2.    52,000 RLS", "3.   104,000 RLS"
	M4SelSIMAmount_00002,
	
	// "--CONFIRMATION--", "                ", "                ", "ENTER or CANCEL?"
	M4Confirmation_00001,
	
	// "SELECT ACCOUNT  ", "                ", "                ", "                "
	M4SelAccountMenu_001,
	
	// "SELECT AMOUNT   ", "                ", "                ", "                "
	M4SelAmountMenu_0001,
	
	// "1.Current       ", "2.Saving        ", "3.Credit        ", "4.Default       "
	M4SelAccount_0000001,
	
	// "Enter last 4    ", "Digits of CardNo", "    [      ]    ", "                "
	M4EnterLast4_0000001,
	
	// "Enter Phone No  ", "                ", "[              ]", "                "
	M4EnterPhoneNo_00001,
	
	// "Confirm Phone No", "                ", "[              ]", "                "
	M4ConfirmPhoneNo_001,
	
	// "   Call Home    ", "                ", "Processing...   ", "                "
	M4StartCallHome_0001,
	
	
	//*******************************************
	//		Smart Card Message (Credit Card)
	//*******************************************
	// "                ", "IC card         ", "interface module", "doesn't response"
	M4IFMnoResponse_0001,
	
	// "Swipe Debit Card", "                ", "                ", "                "
	M4SwipeDebitCard_001,
	
	// "Invalid Amount  ", "                ", "                ", "                "
	M4InvalidAmount_0001,
	
	// "Insert your card", "                ", "                ", "                "
	M4InsertYourCard_001,
	
	// "Card is detected", "                ", "                ", "                "
	M4CardIsDetected_001,
	
	// "Checking card...", "                ", "                ", "                "
	M4CheckingCard_00001,
	
	// "Card error      ", "                ", "                ", "                "
	M4CardError_00000001,
	
	// "Invalid card    ", "                ", "                ", "                "
	M4InvalidCard_000001,
	
	// "Invalid PIN     ", "                ", "                ", "                "
	M4InvalidPIN_0000001,
	
	// "Reading error   ", "                ", "                ", "                "
	M4ReadingError_00001,
	
	// "Not effective   ", "                ", "                ", "                "
	M4NotEffective_00001,
	
	// "Card has expired", "                ", "                ", "                "
	M4CardHasExpired_001,
	
	// "Card is active  ", "                ", "                ", "                "
	M4CardIsActive_00001,
	
	// "Is not active   ", "                ", "                ", "                "
	M4IsNotActive_000001,
	
	// "Account blocked ", "                ", "                ", "                "
	M4AccountBlocked_001,
	
	// "Is not blocked  ", "                ", "                ", "                "
	M4IsNotBlocked_00001,
	
	// "Card is blocked ", "                ", "                ", "                "
	M4CardIsBlocked_0001,
	
	// "PIN not changed ", "                ", "                ", "                "
	M4PINNotChanged_0001,
	
	// "Mismatch PAN    ", "                ", "                ", "                "
	M4MismatchPAN_000001,
	
	// "Checking        ", "Black List...   ", "                ", "                "
	M4CheckBlackList_001,
	
	// "Black List is   ", "not ready.      ", "Do you continue?", "ENTER or CANCEL "
	M4NoBlackList_000001,
	
	// "Updating smart  ", "card data...    ", "                ", "                "
	M4UpdateCardData_001,
	
	// "Smart card data ", "is not updated  ", "                ", "                "
	M4UpdateCardDataEr_1,
	
	// "Requesting Black", "List...         ", "                ", "                "
	M4RequesBlackList_01,
	
	// "                ", "Eject your card ", "                ", "                "
	M4EjectYourCard_0001,
	
	// "1.  goto ON_LINE", "2.       APPROVE", "3.       DECLINE", "PLEASE SELECT   "
	M4ReferralCall_00001,
	
	// "On Line Process ", "                ", "                ", "                "
	M4OnlineProc_0000001,
	
	// "OffLine Process ", "                ", "                ", "                "
	M4OfflineProc_000001,
	
	// "                ", "                ", "                ", "PLEASE SELECT   "
	M4PleaseSelect_00001,
	
	// "                ", "                ", "CARD READING... ", "PLEASE WAIT     "
	M4CardReading_000001,
	// "                ", "                ", "CARD DETECTED.. ", "PLEASE WAIT     "
	M4CardDetected_00001,
	
	// "PLEASE ENTER PIN", "                ", "                ", "                "
	M4PleaseEnterPIN_001,
	// "   ONLINE PIN   ", "                ", "                ", "                "
	M4EnterOnlinePIN_001,
	// "  OFFLINE PIN   ", "                ", "                ", "                "
	M4EnterOfflinePIN_01,
	// "LAST PIN TRY!   ", "                ", "                ", "                "
	M4PINTryLast_0000001,
	// "INCORRECT PIN   ", "TRY AGAIN       ", "                ", "                "
	M4IncorrectPIN_00001,
	// "????????????????", "PIN OK          ", "                ", "                "
	M4PINOK_000000000001,
	
	// "                ", "No IFM detected.", "USE MAG STRIPE  ", "                "
	M4NoIFMUseMSR_000001,
	// "                ", "IFM detected....", "USE CHIP READER ", "PLEASE WAIT     "
	M4IFMUseChip_0000001,
	
	// "ISSUER REFERRAL ", "2.       APPROVE", "3.       DECLINE", "PLEASE SELECT   "
	M4IssuerReferral_001,
	
	//*******************************************
	//		Connection Condition Error Message
	//*******************************************
	// "                ", "POS isn't active", "                ", "                "
	M4POSNotActive_00001,
	
	// "                ", "No Terminal ID  ", "                ", "                "
	M4NoTerminalID_00001,
	
	// "                ", "No Merchant ID  ", "                ", "                "
	M4NoMerchantID_00001,
	
	// "                ", "No Transaction  ", "Phone Number    ", "                "
	M4NoTrxnTelNo_000001,
	
	// "                ", "No EOD          ", "Phone Number    ", "                "
	M4NoEODTelNo_0000001,
	
	// "                ", "No Black List   ", "Phone Number    ", "                "
	M4NoBListTelNo_00001,
	
	// "                ", "No TMS Server   ", "Phone Number    ", "                "
	M4NoTMSTelNo_0000001,
	
	// "                ", "No Local IP     ", "                ", "                "
	M4NoLocalIP_00000001,
	
	// "                ", "No Subnet Mask  ", "                ", "                "
	M4NoSubnetMask_00001,
	
	// "                ", "No Gateway      ", "                ", "                "
	M4NoGateway_00000001,
	
	// "                ", "No Local Port No", "                ", "                "
	M4NoLocalPortNo_0001,
	
	// "                ", "No Local Timeout", "                ", "                "
	M4NoLocalTimeout_001,
	
	// "                ", "No Transaction  ", "Server IP       ", "                "
	M4NoServerIP_0000001,
	
	// "                ", "No Transaction  ", "Server Port No  ", "                "
	M4NoServerPortNo_001,
	
	// "                ", "No EOD          ", "Server IP       ", "                "
	M4NoEODIP_0000000001,
	
	// "                ", "No EOD          ", "Server Port No  ", "                "
	M4NoEODPortNo_000001,
	
	// "                ", "No Black List   ", "Server IP       ", "                "
	M4NoBListIP_00000001,
	
	// "                ", "No Black List   ", "Server Port No  ", "                "
	M4NoBListPortNo_0001,
	
	// "                ", "No TMS Server   ", "IP              ", "                "
	M4NoTMSIP_0000000001,
	
	// "                ", "No TMS Server   ", "Port No         ", "                "
	M4NoTMSPortNo_000001,
	
	// "                ", "No Printer Paper", "                ", "                "
	M4NoPrinterPaper_001,
	
	
	//*******************************************
	//	Transaction Active Status Error Message
	//*******************************************
	// "                ", "Transaction menu", "is not active   ", "                "
	M4TrxnMenuNotActive1,
	
	// "Please set the  ", "transaction     ", "names           ", "                "
	M4TrxnNameNotSet0001,
	
	// "Please set the  ", "transaction     ", "amounts         ", "                "
	M4TrxnAmountNotSet01,
	
	// "Please try again", "Amount has      ", "exceeded maximum", "amount          "
	M4TrxnAmountOver0001,
	
	
	//*******************************************
	//				Reversal Message
	//*******************************************
	// "Reversal        ", "not finished    ", "correctly       ", "                "
	M4ReversalMsg_000001,
	
	// "Reversal        ", "                ", "Insert paper and", "Press ENTER key "
	M4ReversalMsg_000002,
	
	// "Reversal        ", "1.Reversal      ", "2.Set Telephone ", "                "
	M4ReversalMenu_00001,
	
	// "Reversal        ", "1.Reversal      ", "2.Set Ethernet  ", "                "
	M4ReversalMenu_00002,
	
	// "Reversal        ", "1.Reversal      ", "2.Set GSM       ", "3.Print & Clear "
	M4ReversalMsg_000003,
	
	// "Reversal        ", "is impossible   ", "                ", "                "
	M4ReversalFailMsg_01,
	
	// "Reversal        ", "is impossible   ", "Insert paper and", "Press ENTER key "
	M4ReversalFailMsg_02,
	
	
	//*******************************************
	//				MSR Message
	//*******************************************
	// "Swipe your card ", "                ", "                ", "Try again       "
	M4SwipeAgain_0000001,
	
	// "                ", "Please Insert or", "Swipe your card ", "                "
	M4InsertSwipeCard_01,
	
	//*******************************************
	//				Modem Message
	//*******************************************
	// "<DIAL-UP MODEM> ", "                ", "                ", "                "
	M4DialUpModemMsg_001,
	
	// "   <ETHERNET>   ", "                ", "                ", "                "
	M4EthernetMsg_000001,
	
	// "     <GSM>      ", "                ", "                ", "                "
	M4GSMMsg_00000000001,
	
	// "????????????????", "   GSM module   ", "doesn't response", "                "
	M4GSMNoResponse_0001,
	
	// "????????????????", "SIM not inserted", "or failure      ", "                "
	M4SIMfailure_0000001,
	
	// "????????????????", "SIM is blocked  ", "                ", "                "
	M4SIMisBlocked_00001,
	
	// "????????????????", "CHV1 is required", "                ", "                "
	M4CHV1isRequired_001,
	
	// "????????????????", "PUK1 is required", "                ", "                "
	M4PUK1isRequired_001,
	
	// "????????????????", "CHV2 is required", "                ", "                "
	M4CHV2isRequired_001,
	
	// "????????????????", "PUK2 is required", "                ", "                "
	M4PUK2isRequired_001,
	
	// "????????????????", "SIM lock        ", "(phone-to-SIM)  ", "is required     "
	M4SIMlockIsRequire_1,
	
	// "????????????????", "network         ", "personalization ", "is required     "
	M4NetworkPerRequire1,
	
	// "????????????????", "network subset  ", "is required     ", "                "
	M4NetworkSubRequire1,
	
	// "????????????????", "service provider", "is required     ", "                "
	M4SVCroviderRequire1,
	
	// "????????????????", "corporate       ", "is required     ", "                "
	M4CorporateRequired1,

	// "????????????????", "PH-SIM PUK      ", "(master phone   ", "code) required  "
	M4PHSIMPUKRequired1,

	// "????????????????", "No Signal       ", "                ", "                "
	M4NoSignal_000000001,
	
	// "????????????????", "is not          ", "registered      ", "                "
	M4NotRegistered_0001,
	
	// "????????????????", "registration    ", "denied          ", "                "
	M4RegisterDenied_001,
	
	// "????????????????", "unknown network ", "status          ", "                "
	M4UnknownRegStatus_1,
	
	
	//*******************************************
	//				Print Message
	//*******************************************
	// "Can not Print!  ", "1.Reprint       ", "2.Exit          ", "                "
	M4CanNotPrintMenu_01,
	
	// "Reprint         ", "                ", "Printing Now... ", "                "
	M4ReprintMsg_0000001,
	
	// "Please cut a    ", "receipt         ", "                ", "Press ENTER Key "
	M4CutReceiptMsg_0001,
	
	// "                ", "                ", "1.Print         ", "2.Exit          "
	M4SelectPrintExit_01,
	
	// "Second Receipt  ", "                ", "1.Print         ", "2.Exit          "
	M4Bill2ndReceipt_001,
	
	
	//*******************************************
	//		Response Code Message
	//*******************************************
	// "????????????????", "Reversal        ", "is cleared      ", "                "
	M4ReversalIsClear_01,
	
	// "????????????????", "                ", "Store is opened ", "                "
	M4StoreIsOpened_0001,
	
	// "????????????????", "                ", "Store is closed ", "                "
	M4StoreIsClosed_0001,
	
	// "????????????????", "The Bill has not", "been paid before", "                "
	M4BillNotPaid_000001,
	
	// "????????????????", "SIMs for this   ", "amount are      ", "already sold out"
	M4SoldOutSIM_0000001,
	
	// "????????????????", "Transaction has ", "finished        ", "correctly       "
	M4RespCode00_0000001,
	
	// "????????????????", "Reversal has    ", "been done before", "                "
	M4RespCode02_0000001,
	
	// "????????????????", "Card Acceptor is", "not identified  ", "                "
	M4RespCode03_0000001,
	
	// "????????????????", "System Error    ", "                ", "                "
	M4RespCode06_0000001,
	
	// "????????????????", "The message is  ", "not correct for ", "doing this trxn "
	M4RespCode12_0000001,
	
	// "????????????????", "Amount is not   ", "correct         ", "                "
	M4RespCode13_0000001,
	
	// "????????????????", "Card number is  ", "not identified  ", "                "
	M4RespCode14_0000001,
	
	// "????????????????", "Opened before   ", "                ", "                "
	M4RespCode15_0000001,
	
	// "????????????????", "Close before    ", "                ", "                "
	M4RespCode16_0000001,
	
	// "????????????????", Balance is not  ", "correct         ", "                "
	M4RespCode19_0000001,
	
	// "????????????????", "The EOD trxn has", "not finished    ", "correctly       "
	M4RespCode24_0000001,
	
	// "????????????????", "Transaction is  ", "not acceptable  ", "                "
	M4RespCode25_0000001,
	
	// "????????????????", "The EOD trxn is ", "not done        ", "                "
	M4RespCode29_0000001,
	
	// "????????????????", "Format is not   ", "corret          ", "                "
	M4RespCode30_0000001,
	
	// "????????????????", "Card has expired", "                ", "                "
	M4RespCode33_0000001,
	
	// "????????????????", "The trxn has not", "been approved   ", "                "
	M4RespCode34_0000001,
	
	// "????????????????", "Not identified  ", "transaction     ", "                "
	M4RespCode40_0000001,
	
	// "????????????????", "Restricted card ", "                ", "                "
	M4RespCode41_0000001,
	
	// "????????????????", "Stolen card     ", "                ", "                "
	M4RespCode43_0000001,
	
	// "????????????????", "The entered     ", "information is  ", "wrong           "
	M4RespCode44_0000001,
	
	// "????????????????", "The Bill has    ", "been paid before", "                "
	M4RespCode48_0000001,
	
	// "????????????????", "Insufficient    ", "balance         ", "                "
	M4RespCode51_0000001,
	
	// "????????????????", "Invalid PIN     ", "                ", "                "
	M4RespCode55_0000001,
	
	// "????????????????", "Invalid card    ", "                ", "                "
	M4RespCode56_0000001,
	
	// "????????????????", "Illegal         ", "transaction     ", "                "
	M4RespCode57_0000001,
	
	// "????????????????", "Black list is   ", "not ready       ", "                "
	M4RespCode60_0000001,
	
	// "????????????????", "Amount of trans.", "has exceeded    ", "                "
	M4RespCode61_0000001,
	
	// "????????????????", "Amount of trans.", "for one day has ", "exceeded        "
	M4RespCode62_0000001,
	
	// "????????????????", "Transmitted trxn", "are not correct ", "                "
	M4RespCode64_0000001,
	
	// "????????????????", "Number of trans.", "has exceeded    ", "                "
	M4RespCode65_0000001,
	
	// "????????????????", "Number of trans.", "for one day has ", "exceeded        "
	M4RespCode66_0000001,
	
	// "????????????????", "Debit is not    ", "correct         ", "                "
	M4RespCode68_0000001,
	
	// "????????????????", "Balance is not  ", "correct & black ", "list isn't ready"
	M4RespCode70_0000001,
	
	// "????????????????", "Trxns are not   ", "correct & black ", "list isn't ready"
	M4RespCode71_0000001,
	
	// "????????????????", "No of invalid   ", "PIN entry       ", "has exceeded    "
	M4RespCode75_0000001,
	
	// "????????????????", "Financial day is", "not defined     ", "                "
	M4RespCode77_0000001,
	
	// "????????????????", "Card is not     ", "active          ", "                "
	M4RespCode78_0000001,
	
	// "????????????????", "Account has     ", "not identified  ", "                "
	M4RespCode79_0000001,
	
	// "????????????????", "Trxn is not     ", "accepted due to ", "account problem "
	M4RespCode80_0000001,
	
	// "????????????????", "Card has been   ", "canceled        ", "                "
	M4RespCode81_0000001,
	
	// "????????????????", "Central system  ", "is not ready    ", "                "
	M4RespCode83_0000001,
	
	// "????????????????", "Central system  ", "is not active   ", "                "
	M4RespCode84_0000001,
	
	// "????????????????", "Central system  ", "internal error  ", "                "
	M4RespCode85_0000001,
	
	// "????????????????", "Trxn is not     ", "authorized on   ", "this terminal   "
	M4RespCode86_0000001,
	
	// "????????????????", "System internal ", "error           ", "                "
	M4RespCode87_0000001,
	
	// "????????????????", "System internal ", "error           ", "                "
	M4RespCode88_0000001,
	
	// "????????????????", "System internal ", "error           ", "                "
	M4RespCode89_0000001,
	
	// "????????????????", "Communication   ", "during process  ", "is lost         "
	M4RespCode90_0000001,
	
	// "????????????????", "No response from", "Central system  ", "                "
	M4RespCode91_0000001,
	
	// "????????????????", "Transmitter is  ", "not valid       ", "                "
	M4RespCode92_0000001,
	
	// "????????????????", "No response due ", "to high traffic ", "in CentralSystem"
	M4RespCode93_0000001,
	
	// "????????????????", "Transaction No. ", "has duplicated  ", "                "
	M4RespCode94_0000001,
	
	// "????????????????", "System internal ", "error           ", "                "
	M4RespCode96_0000001,
	
	// "????????????????", "Unknown code    ", "                ", "                "
	M4RespCodeUnknown_01,
	
	// "????????????????", "Server Data Err ", "                ", "                "
	M4ServerDataError_01,
	
	
	//*******************************************
	//				TMS
	//*******************************************
	// "Sorry, it does  ", "not support     ", "parameter       ", "upgrade now     "
	M4NotSupportParam_01,
	
	
	//*******************************************
	//	Clear LCD screen Message
	//*******************************************
	// "                ", "                ", "                ", "                "
	M4_____________Space,
	
	
	//*******************************************
	//	Retain Previous LCD Message
	//*******************************************
	// "????????????????", "????????????????", "????????????????", "????????????????"
	M4_____________Dummy,
	
} _eMsg4;

/* */
