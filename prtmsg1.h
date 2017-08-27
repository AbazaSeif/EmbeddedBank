
/*======================================================================*/
/*																		*/
/*								PRTMSC1.H								*/
/*																		*/
/*======================================================================*/

typedef enum {
	P1CardSystem_0000001,		// "  Card System  ",
	
	P1TerminalID_0000001,		// "Terminal ID:",
	P1MerchantID00000001,		// "Merchant ID:",
	P1StoreName_00000001,		// "Store Name :",
	
	P1ModelName_00000001,		// "Model Name :",
	P1POSSerialNo_000001,		// "POS S/N    :",
	P1SRAM_0000000000001,		// "SRAM       :",
	P1SDRAM_000000000001,		// "SDRAM      :",
	P1FlashROM_000000001,		// "Flash ROM  :",
	P1USB_00000000000001,		// "USB        :",
	P1Modem_000000000001,		// "MODEM      :",
	
	P1BIOSVersion_000001,		// "BIOS Ver   :",
	P1SWVersion_00000001,		// "S/W Version:",
	P1SWDate_00000000001,		// "S/W Date   :",
	P1POSSetupVersion_01,		// "Param Ver  :",
	P1POSSetupDate_00001,		// "Param Date :",
	P1DialSignal_0000001,		// "Dial Signal:",
	P1TrxnTel_0000000001,		// "Trans. Tel :",
	P1TMSTel_00000000001,		// "TMS Tel    :",
	P1HelpDeskTel_000001,		// "Help Desk  :",
	
	P1Date_0000000000001,		// "Date       :",
	P1Time_0000000000001,		// "Time       :",
	
	P1BuyTrxn_0000000001,		// "************* BUY **************",
	P1BalanceInquiry_001,		// "*********** BALANCE ************",
	P1BillPayment_000001,		// "********* BILL PAYMENT *********",
	P1HamrahAval_0000001,		// "       -- HAMRAH AVAL --        ",
	P1Irancell_000000001,		// "         -- IRANCELL --         ",
	P1Taliya_00000000001,		// "          -- TALIYA --          ",
	P1Espadana_000000001,		// "         -- ESPADANA --         ",
	P1RefundTrxn_0000001,		// "*********** REFUND *************",
	P1PayTrxn_0000000001,		// "************* PAY **************",
	
	P1CurMerchantTotal_1,		// "**** Current Merchant Total ****",
	P1PreMerchantTotal_1,		// "*** Previous Merchant Total ****",
	P1ClrMerchantTotal_1,		// "***** Clear Merchant Total *****",
	
	P1CurrentPOSTotal_01,		// "****** Current POS Total *******",
	P1PreviousPOSTotal_1,		// "****** Previous POS Total ******",
	P1ClearPOSTotal_0001,		// "******* Clear POS Total ********",
	P1POSCurrentBalance1,		// "***** POS Current Balance ******",
	
	P1CurrentStoreTotal1,		// "***** Current Store Total ******",
	P1PreviousStoreTotal,		// "***** Previous Store Total *****",
	P1ClearStoreTotal_01,		// "****** Clear Store Total *******",
	P1OpeningStore_00001,		// "******** Opening Store *********",
	P1ClosingStore_00001,		// "******** Closing Store *********",
	
	P1Reversal_000000001,		// "*** Reversal ***",
	
	P1ReversalFail_00001,		// "  Reversal for  ",
	P1ReversalFail_00002,		// "  unsuccessful  ",
	P1ReversalFail_00003,		// " transaction is ",
	P1ReversalFail_00004,		// "   impossible   ",
	
	P1PrtLastTrxn_000001,		// "   Print POS Last Transaction   ",
	P1PrtRequiredTrxn_01,		// "   Print Required Transaction   ",
	P1PrtLast20Trxn_0001,		// " Print POS Last 20 Transactions ",
	P1PrtLastTrxn1_00001,		// "Last Transaction",
	
	P1CustomerReceipt_01,		// "       (Customer Receipt)       ",
	P1StoreReceipt_00001,		// "        (Store Receipt)         ",
	P1AccountingReceipt1,		// "      (Accounting Receipt)      ",
	
	P1PAN_00000000000001,		// "PAN        : ",
	P1ApprovalNo_0000001,		// "Approval No:",
	P1ReferenceNo_000001,		// "Ref. No    :",
	P1OrganizationName_1,		// "Organization Name :",
	P1PaymentNo_00000001,		// "Payment No :",
	P1BillID_00000000001,		// "Bill ID    :",
	P1PaymentID_00000001,		// "Payment ID :",
	P1TraceNo_0000000001,		// "Trace No   :",
	P1BatchNo_0000000001,		// "Batch No   :",
	P1SeqNo_000000000001,		// "Seq. No    :",
	P1SerialNo_000000001,		// "Serial No  :",
	P1VoucherNo_00000001,		// "Voucher No",
	P1FarsiNo_0000000001,		// "Farsi No   :",
	P1EnglishNo_00000001,		// "English No :",
	P1BillPayHelpDesk_01,		// "Help Desk  :",
	P1Amount_00000000001,		// "Amount     :",
	P1Rials_000000000001,		// "Rials",
	P1Signature_00000001,		// "Signature  :",
	
	P1CustomerID_0000001,		// "Customer ID:",
	
	P1ExtPrnReprint_0001,		// "(Reprint)",
	P1ExtPrnBranchCode_1,		// " :Branch Code",
	P1ExtPrnOrgName_0001,		// " :Org. Name",
	P1ExtPrnAmount_00001,		// " :Amount",
	P1ExtPrnAccount_0001,		// " :Account",
	P1ExtPrnDateTime_001,		// " :Date & Time",
	P1ExtPrnTraceNo_0001,		// " :Trace No",
	P1ExtPrnCustomerID_1,		// " :Customer ID",
	
	P1Balance_0000000001,		// "Balance    :",
	P1Available_00000001,		// "Available  :",
	
	P1Total_000000000001,		// "Total      :",
	P1MerchantTotalClear,		// "Merchant total sets to zero",
	P1POSTotalCleared_01,		// "POS total sets to zero",
	
	P1CurrentBalance_001,		// "Current Balance :",
	
	P1StoreTotalClear_01,		// "Store total is cleared",
	P1StoreIsOpened_0001,		// "Store is opened",
	P1StoreIsClosed_0001,		// "Store is closed",
	
	P1BillNotPaid_000001,		// "The Bill has not been paid      ",
	P1BillNotPaid_000002,		// "before                          ",
	
	P1SoldOutSIM_0000001,		// "SIMs for this amount are already",
	P1SoldOutSIM_0000002,		// "sold out                        ",
	
	P1SIMChargeMsg_00001,		// "The amount obtains the charge   ",
	P1SIMChargeMsg_00002,		// "with its tax                    ",
	
	P1ThankYou_000000001,		// "           Thank You            ",
	
	P1ErrorMessage_00001,		// "Error Message :",
	
	P1ErrorCode02_000001,		// "Reversal has been done before   ",
	
	P1ErrorCode03_000001,		// "Card Acceptor is not identified ",
	
	P1ErrorCode06_000001,		// "Failure in Central System       ",
	
	P1ErrorCode12_000001,		// "The message is not correct for  ",
	P1ErrorCode12_000002,		// "doing this transaction          ",
	
	P1ErrorCode13_000001,		// "Amount is not correct           ",
	
	P1ErrorCode14_000001,		// "Card number is not identified   ",
	
	P1ErrorCode15_000001,		// "Opened before                   ",
	
	P1ErrorCode16_000001,		// "Closed before                   ",
	
	P1ErrorCode19_000001,		// "Balance is not correct          ",
	
	P1ErrorCode24_000001,		// "The End of Day transaction has  ",
	P1ErrorCode24_000002,		// "not finished correctly          ",
	
	P1ErrorCode25_000001,		// "Transaction is not acceptable   ",
	
	P1ErrorCode29_000001,		// "The End of Day transaction is   ",
	P1ErrorCode29_000002,		// "not done                        ",
	
	P1ErrorCode30_000001,		// "Format is not corret            ",
	
	P1ErrorCode33_000001,		// "Card has expired                ",
	
	P1ErrorCode34_000001,		// "The transaction has not been    ",
	P1ErrorCode34_000002,		// "approved                        ",
	
	P1ErrorCode40_000001,		// "Not identified transaction      ",
	
	P1ErrorCode41_000001,		// "Card is restricted temporarily  ",
	P1ErrorCode41_000002,		// "                                ",
	
	P1ErrorCode43_000001,		// "Stolen card! Restricted         ",
	P1ErrorCode43_000002,		// "                                ",
	
	P1ErrorCode44_000001,		// "The entered information for the ",
	P1ErrorCode44_000002,		// "Bill Payment trxn is wrong      ",
	
	P1ErrorCode48_000001,		// "The Bill has been paid before   ",
	
	P1ErrorCode51_000001,		// "Insufficient balance            ",
	
	P1ErrorCode55_000001,		// "Invalid PIN                     ",
	
	P1ErrorCode56_000001,		// "Invalid card                    ",
	
	P1ErrorCode57_000001,		// "Illegal transaction             ",
	
	P1ErrorCode60_000001,		// "Black list is not ready         ",
	
	P1ErrorCode61_000001,		// "Amount of transaction has       ",
	P1ErrorCode61_000002,		// "exceeded                        ",
	
	P1ErrorCode62_000001,		// "Amount of transaction for one   ",
	P1ErrorCode62_000002,		// "day has exceeded                ",
	
	P1ErrorCode64_000001,		// "Transmitted transactions are not",
	P1ErrorCode64_000002,		// "correct                         ",
	
	P1ErrorCode65_000001,		// "Number of transaction has       ",
	P1ErrorCode65_000002,		// "exceeded                        ",
	
	P1ErrorCode66_000001,		// "Number of transaction for one   ",
	P1ErrorCode66_000002,		// "day has exceeded                ",
	
	P1ErrorCode68_000001,		// "Debit is not correct            ",
	
	P1ErrorCode70_000001,		// "Balance is not correct & black  ",
	P1ErrorCode70_000002,		// "list isn't ready                ",
	
	P1ErrorCode71_000001,		// "Transactions are not correct &  ",
	P1ErrorCode71_000002,		// "black list isn't ready          ",
	
	P1ErrorCode75_000001,		// "No of invalid PIN entry has     ",
	P1ErrorCode75_000002,		// "exceeded                        ",
	
	P1ErrorCode77_000001,		// "Financial day is not defined    ",
	
	P1ErrorCode78_000001,		// "Card is not active              ",
	
	P1ErrorCode79_000001,		// "Account has not identified      ",
	
	P1ErrorCode80_000001,		// "Transaction is not accepted due ",
	P1ErrorCode80_000002,		// "to account problem              ",
	
	P1ErrorCode81_000001,		// "Card has been canceled          ",
	
	P1ErrorCode83_000001,		// "Central system is not ready     ",
	
	P1ErrorCode84_000001,		// "Central system is not active    ",
	
	P1ErrorCode85_000001,		// "Central system internal error   ",
	
	P1ErrorCode86_000001,		// "Transaction is not authorized on",
	P1ErrorCode86_000002,		// "this terminal                   ",
	
	P1ErrorCode87_000001,		// "System internal error           ",
	
	P1ErrorCode88_000001,		// "System internal error           ",
	
	P1ErrorCode89_000001,		// "System internal error           ",
	
	P1ErrorCode90_000001,		// "Communication during process is ",
	P1ErrorCode90_000002,		// "lost                            ",
	
	P1ErrorCode91_000001,		// "No response from Central system ",
	
	P1ErrorCode92_000001,		// "Transmitter is not valid        ",
	
	P1ErrorCode93_000001,		// "No response due to high traffic ",
	P1ErrorCode93_000002,		// "in central system               ",
	
	P1ErrorCode94_000001,		// "Transaction No. has duplicated  ",
	
	P1ErrorCode96_000001,		// "System internal error           ",
	
	P1ErrorCodeUnknown_1,		// "Unknown code                    ",
	
	P1ReversalMsg_000001,		// "*** Unsuccessful Transaction ***",
	P1ReversalMsg_000002,		// "In case your account be charged ",
	P1ReversalMsg_000003,		// "as the result of this           ",
	P1ReversalMsg_000004,		// "unsuccessful transaction, the   ",
	P1ReversalMsg_000005,		// "charged fee will be refunded to ",
	P1ReversalMsg_000006,		// "your account within the next 72 ",
	P1ReversalMsg_000007,		// "hours, unless otherwise you are ",
	P1ReversalMsg_000008,		// "needed to contact with :        ",
	P1ReversalMsg_000009,		// "telephone number for further    ",
	P1ReversalMsg_000010,		// "inquiries within the next 45    ",
	P1ReversalMsg_000011,		// "days.                           ",
	
	P1AllStars_000000001,		// "********************************",
	P1AllDashes_00000001,		// "--------------------------------",
	P1AllEquals_00000001,		// "================================",
	
	P1SoftwareVersion_01,		// "         <Version x.xx>         ",
	
} _ePMsg1;

/* */
