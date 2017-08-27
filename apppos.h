
/*======================================================================*/
/*																		*/
/*								APPPOS.H								*/
/*																		*/
/*======================================================================*/

#define TRXN_LOG_MAGIC_NO       0x5E5A  // Transaction log magic number
#define TRXN_LOG_SUFFIX        0xA5E5  // Transaction log suffix number
#define TRXN_LOG_VERSION       0x0001  // Transaction log version number


// define Message Type ID
#define MTYPE_AUTHORIZATION_REQUEST     0x0100  // Authorization Request
#define MTYPE_FINANCIAL_TRXN_REQUEST    0x0200  // Financial Transaction Request
#define MTYPE_REVERSAL_REQUEST      0x0400  // Reversal Request
#define MTYPE_SUPERVISORY_TRXN_REQUEST    0x0600  // Supervisory Transaction Request


// define Processing Code of Authorization Request
#define PCODE_BILL_PAYMENT_PRELIMINARY    0x190000 // Bill Payment Preliminary Transaction

// define Processing Code of Financial Transaction Request
#define PCODE_DEBIT_BUY        0x000000 // Debit Buy (MS Card), Special Payment
#define PCODE_CREDIT_BUY       0x003000 // Credit Buy (MS Card/IC Card)
#define PCODE_CANCEL_DEBIT_BUY      0x200000 // Cancel of Debit Buy (MS Card)
#define PCODE_DEBIT_BALANCE_INQUIRY     0x310000 // Debit Balance Inquiry (MS Card)
#define PCODE_CREDIT_BALANCE_INQUIRY    0x313000 // Credit Balance Inquiry (MS Card/IC Card)
#define PCODE_DEBIT_BILL_PAYMENT     0x170000 // Debit Bill Payment (MS Card)
#define PCODE_CREDIT_BILL_PAYMENT     0x173000 // Credit Bill Payment (MS Card/IC Card)

// define Processing Code of Supervisory Transaction Request
#define PCODE_OPEN_STORE       0x010000 // Open Store
#define PCODE_CLOSE_STORE       0x090000 // Close Store
#define PCODE_LOAD_BLACKLIST      0x770000 // Load Blacklist
#define PCODE_EOD         0x880000 // EOD Transaction (End of Date Transaction: settlement for all offline transactions)
#define PCODE_CURRENT_POS_TOTAL      0x120000 // Current POS Total
#define PCODE_PREVIOUS_POS_TOTAL     0x180000 // Previous POS Total
#define PCODE_CLEAR_POS_TOTAL      0x490000 // Clear POS Total
#define PCODE_POS_BALANCE       0x110000 // POS Balance
#define PCODE_CURRENT_STORE_TOTAL     0x100000 // Current Store Total
#define PCODE_PREVIOUS_STORE_TOTAL     0x170000 // Previous Store Total
#define PCODE_CLEAR_STORE_TOTAL      0x480000 // Clear Store Total
#define PCODE_CURRENT_MERCHANT_TOTAL    0x380000 // Current Merchant Total
#define PCODE_PREVIOUS_MERCHANT_TOTAL    0x190000 // Previous Merchant Total
#define PCODE_CLEAR_MERCHANT_TOTAL     0x500000 // Clear Merchant Total
#define PCODE_PRINT_DUPLICATE      0x200000 // Print Duplicate


// define the Type of Application
#define APP_TYPE_NORMAL        0   // Normal Application
#define APP_TYPE_MULTI_MERCHANT      1   // Multi-Merchant Application

// define the Type of Buy
#define BUY_TYPE_NORMAL_BUY       0   // Normal Buy
#define BUY_TYPE_BUY_WITH_EXTRA      1   // Buy with extra additional data
#define BUY_TYPE_BUY_WITH_EXTERNAL_PRINTER   2   // Buy with external printer

// define the Type of Payment
#define PAYMENT_TYPE_BILL_PAYMENT     0x10  // Bill Payment
#define PAYMENT_TYPE_CHECK_BILL_PAYMENT    0x11  // Check Bill Payment
#define PAYMENT_TYPE_SIM_CHARGE      0x20  // SIM Charge

// define the Operator code for SIM Charge
#define OPERATOR_CODE_HAMRAH_AVAL     0   // Hamrah Aval
#define OPERATOR_CODE_IRANCELL      1   // Irancell
#define OPERATOR_CODE_TALIYA      2   // Taliya
#define OPERATOR_CODE_ESPADANA      3   // Espadana

#define OPERATOR_CODE_GLO       0
#define OPERATOR_CODE_MTN       1
#define OPERATOR_CODE_STARCOMMS      2
#define OPERATOR_CODE_ZAIN       3



// define Transaction Menu Type

typedef enum {
    TRXN_MENU_PURCHASE = 0,
    TRXN_MENU_RECHARGE,
    TRXN_MENU_BALANCE,
} _eTRXN_MENU_TYPE;
/*
// define Transaction Type
typedef enum {
        TRXN_NULL = 0,
	
        TRXN_BILL_PAYMENT_PRELIMINARY,
	
        TRXN_DEBIT_BUY,
        TRXN_CREDIT_BUY,
        TRXN_CANCEL_DEBIT_BUY,
        TRXN_DEBIT_BALANCE,
        TRXN_CREDIT_BALANCE,
        TRXN_DEBIT_BILL_PAYMENT,
        TRXN_CREDIT_BILL_PAYMENT,
	
        TRXN_REVERSAL_DEBIT_BUY,
        TRXN_REVERSAL_CREDIT_BUY,
	
        TRXN_OPEN_STORE,
        TRXN_CLOSE_STORE,
        TRXN_LOAD_BLACKLIST,
        TRXN_EOD,
        TRXN_CURRENT_POS_TOTAL,
        TRXN_PREVIOUS_POS_TOTAL,
        TRXN_CLEAR_POS_TOTAL,
        TRXN_POS_BALANCE,
        TRXN_CURRENT_STORE_TOTAL,
        TRXN_PREVIOUS_STORE_TOTAL,
        TRXN_CLEAR_STORE_TOTAL,
        TRXN_CURRENT_MERCHANT_TOTAL,
        TRXN_PREVIOUS_MERCHANT_TOTAL,
        TRXN_CLEAR_MERCHANT_TOTAL,
        TRXN_PRINT_DUPLICATE,
	
        TRXN_LOAD_EMV_PARAMETERS,
        TRXN_LOAD_EMV_CAPKS,

        TRXN_PURCHASE_ONLY,
        TRXN_PURCHASE_WITH_CASHBACK,
        TRXN_CASHBACK_ONLY,
        TRXN_REVERSAL,
        TRXN_REFUND,					// 5
        TRXN_AUTH_ONLY,
        TRXN_BALANCE_INQUIRY,
        TRXN_PIN_CHANGE,
        TRXN_MINI_STATEMENT,
        TRXN_TRANSFER,					// 10
        TRXN_DEPOSIT,
        TRXN_ROLBACK,
        TRXN_PRE_AUTH_PURCHASE = 33,
        TRXN_PRE_AUTH_LIFECYCLE,
        TRXN_PRE_AUTH_ADJUSTMENT,
        TRXN_BILL_PAYMENT = 39,
        TRXN_QUASI_CASH = 44,
        TRXN_WEB_PURCHASE_GOODS_AND_SERVICES = 100,

} _eTRXN_TYPE;
 */

// define NIBSS Transaction Type

typedef enum {
    TRXN_NULL = 0,

    TRXN_PURCHASE_ONLY,
    TRXN_PURCHASE_WITH_CASHBACK,
    TRXN_CASHBACK_ONLY,
    TRXN_REVERSAL,
    TRXN_REFUND, // 5
    TRXN_AUTH_ONLY,
    TRXN_BALANCE_INQUIRY,
    TRXN_PIN_CHANGE,
    TRXN_MINI_STATEMENT,
    TRXN_TRANSFER, // 10
    TRXN_DEPOSIT,
    TRXN_ROLBACK,
    TRXN_PRE_AUTH_PURCHASE = 33,
    TRXN_PRE_AUTH_LIFECYCLE,
    TRXN_PRE_AUTH_ADJUSTMENT,
    TRXN_BILL_PAYMENT = 39,
    TRXN_QUASI_CASH = 44,
    TRXN_WEB_PURCHASE_GOODS_AND_SERVICES = 100,


    TRXN_VENDER_SPECIFIC = 1000,
    TRXN_LOAD_PARAMETERS,
    TRXN_LOAD_BLACKLIST,
    TRXN_EOD,

} _eTRXN_TYPE;


#if 0
// The data structure of transaction log on flash ROM : 512 bytes
// for no version number

typedef struct {
    U16 usMagicNo; // 000-001	Magic number
    U16 usIndex; // 002-003	Index (0001-9999)

    union {
        U08 uBYTE;

        struct {
            U08 Reserved : 2; // bit0-1	Reserved for Future Use
            U08 NotPrint2Flag : 1; // bit2		Not Print Receipt #2 Flag
            U08 NotPrint1Flag : 1; // bit3		Not Print Receipt #1 Flag
            U08 NotRxFlag : 1; // bit4		Not Received Response Flag
            U08 ReversalFlag : 1; // bit5		Reversal Transaction Flag
            U08 EODTxFlag : 1; // bit6		EOD Transaction Flag
            U08 OnlineFlag : 1; // bit7		Online Transaction Flag
        } BIT;
    } ucStatus; // 004		Transaction log status 1

    U08 uc2MsgType[2]; // 005-006	Message Type - BCD
    U08 uc3ProcCode[3]; // 007-009	Processing Code - BCD
    U08 uc6Amount[6]; // 010-015	Amount - BCD
    U08 uc3LocalTime[3]; // 016-018	Local Time (hhmmss) - BCD
    U08 uc4LocalDate[4]; // 019-022	Local Date (YYYYMMDD) - BCD
    U08 uc2ExipreDate[2]; // 023-024	Exipre Date (MMDD) - BCD
    U08 uc2POSEntryMode[2]; // 025-026	POS Entry Mode - BCD
    U08 ucPOSConditionCode; // 027		POS Condition Code - BCD
    U08 uc20Track2Data[20]; // 028-047	Track 2 Data
    //			  uc20Track2Data[0]: unsigned char for number of track 2 data
    //			  uc20Track2Data[1]-uc20Track2Data[19]: digits of track 2 data
    U08 uc6ReferenceNo[6]; // 048-053	Reference No - BCD
    U08 uc6ReversalReferenceNo[6]; // 054-059	Reference No of Reversal - BCD
    U08 uc16PIN[16]; // 060-075	Cardholder's PIN
    U08 uc6AIDRefence[6]; // 076-081	Authorization Identification Reference
    U08 uc6ApprovalCode[6]; // 081-086	Approval Code
    U08 uc2ResponseCode[2]; // 087-088	Response Code
    U08 uc15CardAcceptorID[15]; // 089-104	Card Acceptor Identification Code
    U08 uc25AdditionalResponseData[25]; // 105-129	Additional Response Data
    U08 uc64AdditionalData[64]; // 130-193	Additional Data
    U08 uc10BillID[10]; // 194-203	Bill ID
    //			  uc10BillID[0]: unsigned char for number of Bill ID
    //			  uc10BillID[1]-uc10BillID[9]: Bill ID
    U08 uc10PaymentID[10]; // 204-213	Payment ID
    //			  uc10PaymentID[0]: unsigned char for number of Payment ID
    //			  uc10PaymentID[1]-uc10PaymentID[9]: Payment ID
    /*
    U08 uc123BillPaymentDataBit48[123];			// 214-336	Bill Payment Data Bit 48
    U08 uc101BillPaymentDataBit44[101];			// 337-437	Bill Payment Data Bit 44
     */
    U08 ucBillPaymentType; // 214		Bill Payment Type
    char sz34F11FarsiOrganizationName[34]; // 215-248	Farsi Organization Name
    //	U08 ucMultiMerchantFlag;					// 249		Multi-Merchant Flag
    //	char sz15SubBuyTrxnName[15];				// 250-264	Transaction name of Buy
    //	char sz15BuyTrxnName[15];					// 265-279	Buy transaction name
    U08 RFU1[158 + 31]; // 280-437	Reserved for Future Use

    U08 uc28OrganizationAccount[28]; // 438-465	Organization Account
    char sz9TerminalID[9]; // 466-474	Terminal ID
    char sz16MerchantID[16]; // 475-490	Merchant ID
    U08 ucBuyTrxnType; // 491		Buy transaction type
    U08 ucReprintingCnt; // 492		Reprinting Count
    U08 RFU2[15]; // 493-507	Reserved for Future Use

    U16 usVersion; // 508-509	Suffix
    U16 usSuffix; // 510-511	Suffix
} _st_TrxnLog_;
#endif

// The data structure of transaction log on flash ROM : 512 bytes
// for no version number

typedef struct {
    U16 usMagicNo; // 000-001	Magic number
    U16 usIndex; // 002-003	Index (0001-9999)
    U32 ulDateTime; // 019-022	5.  Date and time - The transaction date and time (UNIX time stamp)
    U32 ulReversalDateTime; // 102-105	23. Reversal Date and time - The date and time of the original transaction (reversal only)
    U16 usTrxnType; // 005-006	1.  Transaction Type
    U16 usBatchNo; // 007-008	2.  Batch Number - The batch number currently in use (see EFT Reconcile)
    U16 usSeqNo; // 009-010	3.  Sequence Number - The sequence number currently in use for the batch
    U16 usOrigSeqNo; // 090-091	19. Original Sequence Number - Original transaction sequence number to reverse
    U16 usReversalTrxnType; // 106-107	24. Reversal Transaction Type - The transaction type to reverse (reversal only)
    U16 usTrxnSeqNo; // 211-212	7.  TRANNO - Transaction sequence number
    U16 usTrxnBatchNo; // 213-214	8.  BATCHNO - Transaction batch number

    union {
        U08 uBYTE;

        struct {
            U08 Reserved : 2; // bit0-1	Reserved for Future Use
            U08 NotPrint2Flag : 1; // bit2		Not Print Receipt #2 Flag
            U08 NotPrint1Flag : 1; // bit3		Not Print Receipt #1 Flag
            U08 NotRxFlag : 1; // bit4		Not Received Response Flag
            U08 ReversalFlag : 1; // bit5		Reversal Transaction Flag
            U08 EODTxFlag : 1; // bit6		EOD Transaction Flag
            U08 OnlineFlag : 1; // bit7		Online Transaction Flag
        } BIT;
    } ucStatus; // 004		Transaction log status 1
    U08 uc8MerchantID[8]; // 011-018	4.  Merchant ID/IRN - The unique TAMS merchant ID number
    U08 uc20Track2Data[20]; // 023-042	6.  Track 2 - Track 2 data in plain-text (not-recommended) or encrypted with 3DES prefixed with
    //			    an "E" (highly recommended)
    //			    uc20Track2Data[0]: unsigned char for number of track 2 data
    //			    uc20Track2Data[1]-uc20Track2Data[19]: digits of track 2 data
    U08 uc2CVV[2]; // 043-044	7.  CVV - CVV data
    U08 uc3OperatorNo[3]; // 045-047	8.  Operator - Terminal operator number
    U08 ucSupervisor; // 048		9.  Supervisor - Indicates if a supervisor is processing the transaction
    U08 uc6Amount[6]; // 049-054	10. Amount - The amount to process
    U08 uc6Cashback[6]; // 055-060	11. Cashback - The cashback amount
    U08 uc6Tip[6]; // 061-066	12. Tip - The tip amount
    U08 uc2Budget[2]; // 067-068	13. Budget - The budget months
    U08 ucAccount; // 069		14. Account - The account type (0=Default, 1=Savings, 2=Cheque/Current, 3=CreditCard)
    U08 uc8PinBlock[8]; // 070-077	15. PIN Block - Encrypted card PIN number block (Hex).
    //				The PIN Block can either be encrypted using the DUKPT scheme, or static 3DES.
    //				DUKPT and 3DES keys must be injected into the POS before a transaction is possible.
    //				Key injection is outside of the scope of the TAMS API, and done using the POS vendor tools.
    U08 uc10KSN[10]; // 078-087	16. Key Serial Number - KSN used for DUKPT translation (leave empty for 3DES encrypted PINBlocks)
    U08 ucOffline; // 088		17. Offline - Indicates if this transaction was done offline (Y/N)
    U08 ucManual; // 089		18. Manual - Indicates if this transaction is a manual transaction (Y/N)
    U08 uc6ReferenceCode[6]; // 092-097	21. Reference code - The reference code, used for reporting purposes. For instance, this can be a
    //				customer name, smartcard number, invoice number, etc.
    U08 uc4OrigTerminalID[4]; // 098-101	22. Original Terminal ID - The original terminal that processed the transaction (reversal only)
    U08 uc6OrigRefNo[6]; // 108-113	25. Reversal Reference Number ? The RefNo (STAN) of the original transaction (reversal only)
    U08 uc2CurrencyCode[2]; // 114-115	26. Currency Code - The currency code of the transaction (e.g. 566)
    U08 uc6ProcessorFee[6]; // 116-121	27. Processor Fee - The processor fee (Optional)
    U08 uc6AcquiringFee[6]; // 122-127	28. Acquiring Fee - The acquiring fee (Optional)
    char sz41AdditionalData[41]; // 128-168	29. Additional Data - Additional data for transaction. This is a pipe "|" delimited list of
    //				KEY=VALUE pairs, used for user reporting purposes only. For instance, this can contain car
    //				registration number (REG=ECH404LAG) or PNR number (PNG=XA03033). The key/value
    //				pairs are not validated or enforced and can contain any values, since this is only for reporting.

    // Response
    U08 ucResult; // 169-169	3.  RESULT - Result code for EFT Transaction
    char sz33Message[33]; // 170-202	4.  MESSAGE - Result message text
    U08 uc2StatusCode[2]; // 203-204	5.  STATUS - The status code
    U08 uc6ReferenceNo[6]; // 205-210	6.  REFNO - Transaction approval reference number from switch

    U08 uc6Balance[6]; // 215-220	9.  BALANCE - Balance amount
    U08 uc6Available[6]; // 221-226	10. AVAILABLE - Available amount
    char sz256Data[256]; // 227-482	11. DATA - Mini statement data delimited by the pipe character "|"

    U08 RFU[25]; // 483-507	Reserved for Future Use

    U16 usVersion; // 508-509	Suffix
    U16 usSuffix; // 510-511	Suffix



    U08 uc2MsgType[2]; // 005-006	Message Type - BCD
    U08 uc3ProcCode[3]; // 007-009	Processing Code - BCD
    //	U08 uc6Amount[6];							// 010-015	Amount - BCD
    U08 uc3LocalTime[3]; // 016-018	Local Time (hhmmss) - BCD
    U08 uc4LocalDate[4]; // 019-022	Local Date (YYYYMMDD) - BCD
    U08 uc2ExipreDate[2]; // 023-024	Exipre Date (MMDD) - BCD
    U08 uc2POSEntryMode[2]; // 025-026	POS Entry Mode - BCD
    U08 ucPOSConditionCode; // 027		POS Condition Code - BCD
    //	U08 uc20Track2Data[20];						// 028-047	Track 2 Data
    //			  uc20Track2Data[0]: unsigned char for number of track 2 data
    //			  uc20Track2Data[1]-uc20Track2Data[19]: digits of track 2 data
    //	U08 uc6ReferenceNo[6];						// 048-053	Reference No - BCD
    U08 uc6ReversalReferenceNo[6]; // 054-059	Reference No of Reversal - BCD
    U08 uc16PIN[16]; // 060-075	Cardholder's PIN
    U08 uc6AIDRefence[6]; // 076-081	Authorization Identification Reference
    U08 uc6ApprovalCode[6]; // 081-086	Approval Code
    U08 uc2ResponseCode[2]; // 087-088	Response Code
    U08 uc15CardAcceptorID[15]; // 089-104	Card Acceptor Identification Code
    U08 uc25AdditionalResponseData[25]; // 105-129	Additional Response Data
    U08 uc64AdditionalData[64]; // 130-193	Additional Data
    U08 uc10BillID[10]; // 194-203	Bill ID
    //			  uc10BillID[0]: unsigned char for number of Bill ID
    //			  uc10BillID[1]-uc10BillID[9]: Bill ID
    U08 uc10PaymentID[10]; // 204-213	Payment ID
    //			  uc10PaymentID[0]: unsigned char for number of Payment ID
    //			  uc10PaymentID[1]-uc10PaymentID[9]: Payment ID
    /*
    U08 uc123BillPaymentDataBit48[123];			// 214-336	Bill Payment Data Bit 48
    U08 uc101BillPaymentDataBit44[101];			// 337-437	Bill Payment Data Bit 44
     */
    U08 ucBillPaymentType; // 214		Bill Payment Type
    char sz34F11FarsiOrganizationName[34]; // 215-248	Farsi Organization Name
    U08 RFU1[158 + 31]; // 249-437	Reserved for Future Use
    U08 uc28OrganizationAccount[28]; // 438-465	Organization Account
    char sz9TerminalID[9]; // 466-474	Terminal ID
    char sz16MerchantID[16]; // 475-490	Merchant ID
    U08 ucBuyTrxnType; // 491		Buy transaction type
    U08 ucReprintingCnt; // 492		Reprinting Count
    //	U08 RFU2[15];								// 493-507	Reserved for Future Use

    //	U16 usVersion;								// 508-509	Suffix
    //	U16 usSuffix;								// 510-511	Suffix
} _st_TrxnLog_;


/*
// The data structure of transaction request data
typedef struct {
        char c9Header[9];							// Header
        //char sz5Header[5];							// Header
        char sz5MsgType[5];							// Message Type
        char sz20PAN[20];							// PAN
        char sz7ProcCode[7];						// Processing code
        char sz13Amount[13];						// Amount
        char sz7LocalTime[7];						// Local Time (hhmmss)
        char sz9LocalDate[9];						// Local Date (YYYYMMDD)
        char sz5ExpiryDate[5];						// Expired Date (MMDD)
        char sz4POSEntryMode[4];					// POS Entry Mode
        char sz3POSConditionCode[3];				// POS Condition Code
        char sz39Track2Data[39];					// Track 2 Data
                                                                                                //   sz39Track2Data[0]: unsigned char for number of track 2 data
                                                                                                //   sz39Track2Data[1]-uc20Track2Data[37]: digits of track 2 data
        char sz13ReferenceNo[13];					// Reference No
        char sz9TerminalID[9];						// Terminal ID
        char sz41Additional[41];					// Additional
        char sz17PIN[17];							// Cardholder's PIN("0200", "0400")
        char sz2OnlineTrxn[2];						// "0": Offline Transaction, "1": Online Transaction
        U08 ucBillPaymentType;						// Bill Payment Type
        char sz19BillID[19];						// Bill ID
        char sz19PaymentID[19];						// Payment ID
        char F048aL3_sz1003BillPaymentData1[1003];	// Bill Payment Data 1 (Bit 48)
        char F121aL3_sz1003BillPaymentData2[1003];	// Bill Payment Data 2 (Bit 121)
        char sz29OrganizationAccount[29];			// Organization Account
        U08 ucBuyTrxnType;							// Buy transaction type
        char sz3POSAppVersion[3];					// POS application version
        char sz16MerchantID[16];					// Merchant ID
        char sz17MAC[17];							// MAC
//	U08 ucMultiMerchantFlag;					// Multi-Merchant Flag
//	char sz15SubBuyTrxnName[15];				// Sub-buy Transaction name for Multi-Merchant
//	char sz15BuyTrxnName[15];					// Buy transaction name
} _st_TrxnReqData_;
 */

// The data structure of NIBSS transaction request data

typedef struct {
    U16 usTrxnType; // 1.  Transaction Type
    U16 usBatchNo; // 2.  Batch Number - The batch number currently in use (see EFT Reconcile)
    U16 usSeqNo; // 3.  Sequence Number - The sequence number currently in use for the batch.
    //     Sequence numbers must be incremented with each transaction.
    char sz16MerchantID[16]; // 4.  Merchant ID/IRN - The unique TAMS merchant ID number
    U32 ulDateTime; // 5.  Date and time - The transaction date and time (UNIX time stamp)
    char sz42Track2Data[42]; // 6.  Track 2 - Track 2 data in plain-text (not-recommended) or encrypted with 3DES prefixed with
    //     an "E" (highly recommended)
    //     sz39Track2Data[0]: unsigned char for number of track 2 data
    //     sz39Track2Data[1]-uc20Track2Data[37]: digits of track 2 data
    char sz4CVV[4]; // 7.  CVV - CVV data (Optional)
    char sz7OperatorNo[7]; // 8.  Operator - Terminal operator number
    U08 ucSupervisor; // 9.  Supervisor - Indicates if a supervisor is processing the transaction
    char sz13Amount[13]; // 10. Amount - The amount to process
    char sz13Cashback[13]; // 11. Cashback - The cashback amount (Optional)
    char sz13Tip[13]; // 12. Tip - The tip amount (Optional)
    char sz5Budget[5]; // 13. Budget - The budget months (Optional)
    U08 ucAccount; // 14. Account - The account type (0=Default, 1=Savings, 2=Cheque/Current, 3=CreditCard)
    char sz17PinBlock[17]; // 15. PIN Block - Encrypted card PIN number block (Hex).
    //     The PIN Block can either be encrypted using the DUKPT scheme, or static 3DES.
    //     DUKPT and 3DES keys must be injected into the POS before a transaction is possible.
    //     Key injection is outside of the scope of the TAMS API, and done using the POS vendor tools.
    char sz21KSN[21]; // 16. Key Serial Number - KSN used for DUKPT translation (leave empty for 3DES encrypted PINBlocks)
    U08 ucOffline; // 17. Offline - Indicates if this transaction was done offline (Y/N)
    U08 ucManual; // 18. Manual - Indicates if this transaction is a manual transaction (Y/N)
    U16 usOrigSeqNo; // 19. Original Sequence Number - Original transaction sequence number to reverse
    U08 RFU_F20; // 20. Reserved for future use.
    char sz13ReferenceCode[13]; // 21. Reference code - The reference code, used for reporting purposes. For instance, this can be a
    //     customer name, smartcard number, invoice number, etc. (Optional)
    char sz9OrigTerminalID[9]; // 22. Original Terminal ID - The original terminal that processed the transaction (reversal only)
    U32 ulReversalDateTime; // 23. Reversal Date and time - The date and time of the original transaction (reversal only)
    U16 usReversalTrxnType; // 24. Reversal Transaction Type - The transaction type to reverse (reversal only)
    char sz13ReferenceNo[13]; // 25. Reversal Reference Number ? The RefNo (STAN) of the original transaction (reversal only)
    char sz4CurrencyCode[4]; // 26. Currency Code - The currency code of the transaction (e.g. 566)
    char sz13ProcessorFee[13]; // 27. Processor Fee - The processor fee (Optional)
    char sz13AcquiringFee[13]; // 28. Acquiring Fee - The acquiring fee (Optional)
    char sz41AdditionalData[41]; // 29. Additional Data - Additional data for transaction. This is a pipe "|" delimited list of
    //     KEY=VALUE pairs, used for user reporting purposes only. For instance, this can contain car
    //     registration number (REG=ECH404LAG) or PNR number (PNG=XA03033). The key/value
    //     pairs are not validated or enforced and can contain any values, since this is only for reporting.
    U08 RFU_F30; // 30. Reserved for future use.
    U08 RFU_F31; // 31. Reserved for future use.
    U08 RFU_F32; // 32. Reserved for future use.
    U08 RFU_F33; // 33. Reserved for future use.
    char sz512IccData[512]; // 34. ICC Data (in HEX) delimited by pipe "|" characters, each position contains:
    //     1.  Cryptogram - T8b_AppCrytogram
    //     2.  CryptogramInformationData - T1b_CryptogramInfoData
    //     3.  IssuerApplicationData - Tvb_IssuerAppData
    //     4.  UnpredictableNumber - T4b_TrmUnpredictableNo
    //     5.  ApplicationTransactionCounter - T2b_ATC
    //     6.  TerminalVerificationResult - T5b_TrmTVR
    //     7.  TransactionDate - T3n_TrmTrxnDate
    //     8.  TransactionType - T1n_TrmTrxnType
    //     9.  AmountAuthorization - T6n_TrmAmountAuthorised
    //     10. TransactionCurrencyCode - T2n_TrmTrxnCurrencyCode
    //     11. Reserved
    //     12. ApplicationInterchangeProfile - T2b_AIP
    //     13. TerminalCountryCode - T2n_TrmCountryCode
    //     14. AmountOther - T6n_TrmAmountOther
    //     15. TerminalCapabilities - T3b_TrmCapa
    //     16. ApplicationIdentication - Tvv_AID
    //     17. Reserved
    //     18. CardAuthenticatorResultCode - T2a_ARC
    //     19. TerminalType - T1n_TrmType
    //     20. InterfaceDeviceSerialNumber - T8a_TrmIFD_SerialNo
    //     21. TransactionCategory - T1a_TrmTCC
    //     22. DedicatedFileName (Optional) - Tvv_DFname
    //     23. TerminalIdentificationVersionNumber - T2b_TrmAppVersionNo
    //     24. TransactionSequenceNumber (Optional) - Tvn_TrmTrxnSequenceCounter
    //     25. CVMResult - T3b_TrmCVMR
    U08 uc6AuthID[6]; // 35. Auth ID - The Pre-Auth ID for Adjustments and Completion



    char c9Header[9]; // Header
    //char sz5Header[5];							// Header
    char sz5MsgType[5]; // Message Type
    char sz20PAN[20]; // PAN
    char sz7ProcCode[7]; // Processing code
    //	char sz13Amount[13];						// Amount
    char sz7LocalTime[7]; // Local Time (hhmmss)
    char sz9LocalDate[9]; // Local Date (YYYYMMDD)
    char sz5ExpiryDate[5]; // Expired Date (MMDD)
    char sz4POSEntryMode[4]; // POS Entry Mode
    char sz3POSConditionCode[3]; // POS Condition Code
    char sz39Track2Data[39]; // Track 2 Data
    //   sz39Track2Data[0]: unsigned char for number of track 2 data
    //   sz39Track2Data[1]-uc20Track2Data[37]: digits of track 2 data
    //	char sz13ReferenceNo[13];					// Reference No
    char sz9TerminalID[9]; // Terminal ID
    char sz41Additional[41]; // Additional
    char sz17PIN[17]; // Cardholder's PIN("0200", "0400")
    char sz2OnlineTrxn[2]; // "0": Offline Transaction, "1": Online Transaction
    U08 ucBillPaymentType; // Bill Payment Type
    char sz19BillID[19]; // Bill ID
    char sz19PaymentID[19]; // Payment ID
    char F048aL3_sz1003BillPaymentData1[1003]; // Bill Payment Data 1 (Bit 48)
    char F121aL3_sz1003BillPaymentData2[1003]; // Bill Payment Data 2 (Bit 121)
    char sz29OrganizationAccount[29]; // Organization Account
    U08 ucBuyTrxnType; // Buy transaction type
    char sz3POSAppVersion[3]; // POS application version
    //	char sz16MerchantID[16];					// Merchant ID
    char sz17MAC[17]; // MAC
    //	U08 ucMultiMerchantFlag;					// Multi-Merchant Flag
    //	char sz15SubBuyTrxnName[15];				// Sub-buy Transaction name for Multi-Merchant
    //	char sz15BuyTrxnName[15];					// Buy transaction name
} _st_TrxnReqData_;

/*
// The data structure of transaction response data
typedef struct {
        //char sz5Header[5];							// Header
        char c9Header[9];							// Header
        char sz5MsgType[5];							// Message Type
        char sz20PAN[20];							// PAN("0210", "0410") or Merchant Name("0610")
        char sz7ProcCode[7];						// Processing code
        char sz13Amount[13];						// Amount("0210", "0410") or Filler("0610")
        char sz7AIDRefence[7];						// Authorization Identification Reference("0210", "0410") or Trace("0610")
        char sz13ReferenceNo[13];					// Reference No
        char sz7ApprovalCode[7];					// Approval Code
        char sz3ResponseCode[3];					// Response Code
        char sz16CardAcceptorIDCode[16];			// Card Acceptor Identification Code
        char sz26AdditionalResponseData[26];		// Additional Response Data
        char sz65AdditionalData[65];				// Additional Data("0210", "0610":58 Bytes, "0410":2 Bytes)
        char F048aL3_sz1003BillPaymentData1[1003];	// Bill Payment Data 1 (Bit 48)
        char F121aL3_sz1003BillPaymentData2[1003];	// Bill Payment Data 2 (Bit 121)
        char sz29OrganizationAccount[29];			// Organization Account
        char sz17MAC[17];							// MAC
} _st_TrxnRespData_;
 */

// The data structure of NIBSS transaction response data

typedef struct {
    char c10EFTTRAN[10]; // 1.  EFTTRAN - The EFT transaction result list segment
    char c10TRAN[10]; // 2.  TRAN - EFT Transaction result
    char ucResult; // 3.  RESULT - Result code for EFT Transaction
    //     1. 0 - Pending
    //     2. 1 - Approved
    //     3. 2 - Declined
    //     4. 3 - Reconciled
    //     5. 4 - Rollback
    char sz33Message[33]; // 4.  MESSAGE - Result message text
    U08 sz4StatusCode[4]; // 5.  STATUS - The status code
    //     1.  0   - OK
    //     2.  300 - Invalid Terminal
    //     3.  301 - Invalid Batch
    //     4.  302 - Transaction Not Found
    //     5.  303 - Transaction Already Exists
    //     6.  304 - No Switch
    //     7.  305 - Invalid Merchant Account
    //     8.  306 - Invalid Auth Code
    //     9.  307 - System Unavailable
    //     10. 308 - Validation Error (Transaction query string parameter validation T[...] failed)
    //     11. 309 - Invalid amount
    //     12. 310 - Invalid card
    //     13. 311 - Pickup card
    //     14. 312 - Wrong card type
    //     15. 313 - Invalid account
    //     16. 314 - Insufficient funds
    //     17. 315 - Card expired
    //     18. 316 - Limit exceeded
    //     19. 317 - PIN error
    //     20. 318 - Transaction mismatch
    //     21. 319 - Hotcard
    //     22. 320 - Manual transaction not allowed
    //     23. 321 - Refund transaction not allowed
    //     24. 322 - Reversal transaction not allowed
    //     25. 323 - Budget transaction not allowed
    //     26. 324 - Cashback transaction not allowed
    //     27. 325 - Authorization override not allowed
    //     28. 326 - Authorization only transaction not allowed
    //     29. 327 - PIN change failed
    //     30. 328 - Transaction already reversed
    //     31. 329 - No open batch for processor
    //     32. 330 - Currency conversion error
    //     33. 331 - HSM error
    //     34. 332 - Call
    //     35. 333 - DUKPT serial error
    //     36. 334 - Transaction not authorized by bank
    //     37. 335 - Unknown 3D secure client
    //     38. 336 - 3D Secure Issuer not found
    //     39. 337 - 3D Secure transaction not allowed
    //     40. 338 - Budget period limit error
    //     41. 339 - Budget amount too small
    //     42. 340 - Cashback amount too big
    //     43. 341 - Routing Error
    //     44. 398 - Parameters error
    //     45. 399 - System error
    char sz13ReferenceNo[13]; // 6.  REFNO - Transaction approval reference number from switch
    U16 usTrxnSeqNo; // 7.  TRANNO - Transaction sequence number
    U16 usTrxnBatchNo; // 8.  BATCHNO - Transaction batch number
    char sz13Balance[13]; // 9.  BALANCE - Balance amount
    char sz13Available[13]; // 10. AVAILABLE - Available amount
    char sz256Data[256]; // 11. DATA - Mini statement data delimited by the pipe character "|"
    char sz512IccResponse[512]; // 12. ICCRESPONSE - ICC issuer script that must be sent to the ICC Card after transaction is done. This
    //     is typically used by PIN Change to update the Offline PIN, but may be used for other transaction
    //     types as well, depending on the card scheme and switch.





    char c9Header[9]; // Header
    char sz5MsgType[5]; // Message Type
    char sz20PAN[20]; // PAN("0210", "0410") or Merchant Name("0610")
    char sz7ProcCode[7]; // Processing code
    char sz13Amount[13]; // Amount("0210", "0410") or Filler("0610")
    char sz7AIDRefence[7]; // Authorization Identification Reference("0210", "0410") or Trace("0610")
    //	char sz13ReferenceNo[13];					// Reference No
    char sz7ApprovalCode[7]; // Approval Code
    char sz3ResponseCode[3]; // Response Code
    char sz16CardAcceptorIDCode[16]; // Card Acceptor Identification Code
    char sz26AdditionalResponseData[26]; // Additional Response Data
    char sz65AdditionalData[65]; // Additional Data("0210", "0610":58 Bytes, "0410":2 Bytes)
    char F048aL3_sz1003BillPaymentData1[1003]; // Bill Payment Data 1 (Bit 48)
    char F121aL3_sz1003BillPaymentData2[1003]; // Bill Payment Data 2 (Bit 121)
    char sz29OrganizationAccount[29]; // Organization Account
    char sz17MAC[17]; // MAC
} _st_TrxnRespData_;

// The data structure of transaction log Database

typedef struct {
    U32 ulIndex; // Index of transaction log Database (0: No Data, 1 to 1000: Data is existed)
    _st_TrxnLog_ *pstTrxnLogAddr; // Pointer to transaction log
} _st_TrxnLogDB_;

typedef struct {
    int iErrFlag;
    char sz4ErrCode[4];
    char sz49ErrMsg[49];
} _st_ErrRespData_;

typedef struct {
    U16 BATCHNO;
    U16 T, PC, PRC, RC, RRC;
    U32 A, PV, PRV, RV, RRV;
} _st_EndOfDay_;


#ifdef USER_DEBUG
extern const char TrxnName_tbl[][64];
#endif
extern const unsigned short ResponseCode_tbl[];
extern const unsigned char REPRINTER_COUNT_TO_LOG_COUNT_TBL[];

extern _st_TrxnLog_ st_TrxnLog; // Transaction log buffer
extern _st_TrxnLog_ *pstfFirstTrxnLog; // Pointer to first transaction log address of flash ROM
extern _st_TrxnLog_ *pstfLastTrxnLog; // Pointer to last transaction log address of flash ROM
extern _st_TrxnLog_ *pstfSavingTrxnLog; // Pointer to saving transaction log address of flash ROM
extern _st_TrxnLog_ *pstfTempTrxnLog; // Pointer to temporary transaction log address of flash ROM
extern _st_TrxnReqData_ st_TrxnReqData; // Transaction request buffer
extern _st_TrxnReqData_ st_ReversalTrxnReqData; // Reversal transaction request buffer
extern _st_TrxnRespData_ st_TrxnRespData; // Transaction response buffer
extern _st_TrxnLogDB_ st_TrxnLogDB[MAX_TRANSACTION_LOG]; // Transaction log DB buffer
extern _st_ErrRespData_ st_ErrRespData; // Transaction(Parameter download) error response buffer
extern _st_EndOfDay_ st_EndOfDay;


extern double dBuyAmount; // Buy amount
extern double dRefundAmout; // Refund amount
extern double dDebitBuyAmount; // Debit buy amount
extern double dCreditBuyAmout; // Credit buy amount
extern int iStartDBCtrlIndex; // Start DB control index
extern int iMaxDBCtrlIndex; // Maximum DB control index
extern unsigned long ulPCode; // Processing Code
extern unsigned long ulBackupPCode; // Back-up Processing Code
extern long lMinLogAddr; // Minimum transaction log address of flash ROM
extern long lMaxLogAddr; // Maximum transaction log address of flash ROM
extern unsigned short usMsgType; // Message type
extern unsigned short usBackupMsgType; // Back-up Message type
extern unsigned short usTransType; // Transaction type
extern unsigned short usBackupTransType; // Back-up Transaction type
extern unsigned short usTrxnLogIndex; // Transaction log index
extern unsigned short usTrxnTotalCount; // Total transaction log count
extern unsigned short usEodTrxnCount; // Eod Transaction log count
extern unsigned short usResponseCode; // Response code
extern unsigned char ucReversalFlag; // Reversal flag
extern unsigned char ucReversalRetryCnt; // Reversal retry count
extern unsigned char ucReversalRetryTimePerCnt; // Reversal retry time per a count
extern unsigned char ucBuyTrxnType; // Buy transaction type
extern unsigned char ucBlackListExistFlag; // Black list exist flag
extern unsigned char ucSIMChargeOperatorCode; // SIM charge operator code
extern unsigned char ucPINInputAndReconnectFlag; // PIN Input and Reconnect Flag
extern unsigned char ucMultiMerchantSelectedNo; // Multi-Merchant Selected Number
extern char sz9BackupTerminalID[9]; // Back-up Terminal ID
extern char sz9BackupMerchantID[16]; // Back-up Merchant ID
extern char sz13Amount[13]; // Transaction amount buffer
extern char sz13CardPIN[13]; // Transaction card PIN buffer
extern char sz17EncypritedCardPIN[17]; // Transaction encyprited card PIN buffer
extern char sz19BillID[19]; // Bill ID buffer
extern char sz19PaymentID[19]; // Payment ID buffer
extern char F048aL3_sz1003BillPaymentData1[1003]; // Bill Payment Data 1 (Bit 48) buffer
extern char F121aL3_sz1003BillPaymentData2[1003]; // Bill Payment Data 2 (Bit 121) buffer
extern char sz29OrganizationAccount[29]; // Organization account buffer
extern char c9ActiveTrxnMenuType[9]; // Active transaction menu type
extern char sz17ActiveTrxnMenuMsg[9][17]; // Active transaction menu message buffer
extern char sz12PhoneNo[12]; // Phone Number buffer



// Get Next Transaction Parameter
extern void GetNextTrxnParameter(_tDATE_TIME *dt, int mode);

// Get Next Reference No Counter
extern unsigned short GetNextReferenceNoCounter(_tDATE_TIME *dt);

// Get Transaction Type from Message Type and Processing Code
extern void GetTransactionType(unsigned short *trxn_type, unsigned short msg_type, unsigned long proc_code);

// Save Tx Transaction Log
extern void SaveTxTransactionLog(void);

// Save Rx Transaction Log
extern void SaveRxTransactionLog(void);

// Save Print Transaction Log
extern void SavePrintTransactionLog(_st_TrxnLog_ *trxn_log, int second_prt);

// Save Reprinting Count
extern void SaveReprintingCount(_st_TrxnLog_ *trxn_log);

// Save Reversal Transaction Log
extern void SaveReversalTransactionLog(_st_TrxnLog_ *trxn_log);

// Go to Reversal Mode
extern void GotoReversalMode(void);

// Print Reversal Receipt
extern void PrintReversalReceipt(unsigned short delay_time);

// Print Unsuccessful Reversal Receipt
extern void PrintUnsuccessfulReversalReceipt(void);

// Perform Reversal Transaction
extern void PerformReversalTransaction(void);

// Recover Reversal Data
extern void RecoverReversalData(_st_TrxnLog_ *trxn_log);

// Get POS Balance Data
extern void GetPOSBalanceData(void);

#ifdef USER_DEBUG
// Output Transaction Log data for debugging
extern void DebugOutputTrxnLogData(_st_TrxnLog_ *trxn_log, int mode);

// Output trasaction log for debugging
extern void DebugOutputTrxnLog(void);

// Output request data for debugging
extern void DebugOutputTrxnReqData(void);

// Output response data for debugging
extern void DebugOutputTrxnRespData(void);
#endif

#ifdef SAVE_TEST_TRXN_LOG
// Save Transaction Logs for test
extern void SaveTestTrxnLogs(int log_cnt);
#endif

extern U16 LoadPOSUtilBuf();
extern U16 SavePOSUtilBuf();

#define API_GET_APPLIST     0x0000
#define API_GET_FUNCLIST    0x0001

#define API_TAMS_AGENTLOGIN    0x1000
#define API_TAMS_AGENTLOGOUT   0x1001
#define API_TAMS_CALLHOME    0x1002
#define API_TAMS_EOD     0x1003
#define API_TAMS_GETKEYS    0x1004
#define API_TAMS_GETLOGO    0x1005
#define API_TAMS_GETMENU    0x1006
#define API_TAMS_GETPROMPTLIST   0x1007
#define API_TAMS_NEWKEY     0x1008
#define API_TAMS_OPERATORREPORT   0x1009
#define API_TAMS_PARAM     0x100A
#define API_TAMS_TELLERCARDS   0x100B

#define API_VOUCHER_CANCELORDER   0x2000
#define API_VOUCHER_ELECSALE   0x2001
#define API_VOUCHER_GETBALANCE   0x2002
#define API_VOUCHER_GETSTOCK   0x2003
#define API_VOUCHER_ORDER    0x2004
#define API_VOUCHER_PARAM    0x2005
#define API_VOUCHER_PINLESSORDER  0x2006
#define API_VOUCHER_PINLESSRECONTOTAL 0x2007
#define API_VOUCHER_PINLESSREVERSAL  0x2008
#define API_VOUCHER_PINLESSSTATUS  0x2009
#define API_VOUCHER_PINLESSUPLOAD  0x200A
#define API_VOUCHER_PRODLIST   0x200B
#define API_VOUCHER_REPRINT    0x200C
#define API_VOUCHER_RETURNSTOCK   0x200D
#define API_VOUCHER_SALES    0x200E
#define API_VOUCHER_SPLIST    0x200F
#define API_VOUCHER_SPLOGO    0x2010

#define API_BANK_BINTABLE    0x3000
#define API_BANK_BIOTEMPLATE   0x3001
#define API_BANK_BIOTRAN    0x3002
#define API_BANK_DISTORDER    0x3003
#define API_BANK_DISTRETURN    0x3004
#define API_BANK_EFTPARAMS    0x3005
#define API_BANK_EFTTOTALS    0x3006
#define API_BANK_EFTTRAN    0x3007
#define API_BANK_EMVAPP     0x3008
#define API_BANK_EMVCAPK    0x3009
#define API_BANK_EMVREVOKECAPK   0x300A
#define API_BANK_EODTXNLIST    0x300B
#define API_BANK_HOTCARDS    0x300C
#define API_BANK_LINKED     0x300D
#define API_BANK_UPLOADTXN    0x300E
/*
#define TRXN_NULL						0
#define TRXN_DOWNLOAD_ALL_PARAMETER		1
#define TRXN_DOWNLOAD_APPFUNCLIST		2
#define TRXN_DOWNLOAD_KEY				3
#define TRXN_DOWNLOAD_PARAMETER			4
#define TRXN_DOWNLOAD_EMV_PARAMETER		5
#define TRXN_DOWNLOAD_HOTCARD			6
#define TRXN_BANK_EFTTRAN				7
#define TRXN_BANK_EFTTOTAL				8
#define TRXN_TAMS_CALLHOME				9
 */
#define TRXN_NULL      0
#define TRXN_DOWNLOAD_ALL_PARAMETER  1
#define TRXN_DOWNLOAD_APPLIST   2
#define TRXN_DOWNLOAD_FUNCLIST   3
#define TRXN_DOWNLOAD_MASTERKEY   4
#define TRXN_DOWNLOAD_SESSIONKEY  5
#define TRXN_DOWNLOAD_PARAM    6
#define TRXN_DOWNLOAD_EFTPARAMS   7
#define TRXN_DOWNLOAD_BINTABLE   8
#define TRXN_DOWNLOAD_EMVAPP   9
#define TRXN_DOWNLOAD_EMVCAPK   10
#define TRXN_DOWNLOAD_EMVREVOKECAPK  11
#define TRXN_DOWNLOAD_HOTCARDS   12
#define TRXN_RESERVED1     13
#define TRXN_RESERVED2     14
#define TRXN_RESERVED3     15
#define TRXN_BANK_EFTTRAN    16
#define TRXN_BANK_EFTTOTAL    17
#define TRXN_TAMS_CALLHOME    18

extern long lCallHome1SECTimer;


/* */
