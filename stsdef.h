
#define MSS_INITIAL      0xF000  // Initial Status
#define MSS_SPECIAL_FUNC    0xF001  // Special Functions: Setup Modem Parameters, Setup Date and Time, Setup Others
#define MSS_F1_FUNC      0xF100  // F1 Functions
#define MSS_F1_REVERSAL_TRANS   0xF101  // Reversal
#define MSS_F1_REFUND_TRANS    0xF140  // Refund
#define MSS_F2_FUNC      0xF200  // F2 Functions
#define MSS_F3_FUNC      0xF300  // F3 Functions: Setup POS Status, Set Language
#define MSS_CUSTOMER_TRANS    0xF400  // Customer Trans.
#define MSS_PURCHASE     0xF401  // Purchase
#define MSS_BALANCE      0xF402  // Balance
#define MSS_RECHARGE     0xF403  // Bill Payment
#define MSS_REVERSAL     0xF500  // Reversal
#define MSS_CALLHOME     0xF501

typedef enum {
    MST_INITIAL = 0, // Initial Status

    MST_SPECIAL, // Special Functions

    MST_SETUP_TERMINAL, // Select Setup Terminal Menu

    MST_SETUP_GSM, // Setup GSM Parameters

    MST_SETUP_SET_PARAM, // Set Parameters

    MST_SETUP_HELP_DESK_PHONE_NO, // Set Help Desk Telephone No

    MST_SETUP_POS_SERIAL_NO, // POS Serial Number

    MST_SETUP_DOWNLOAD_PARAMETERS, // Download All Parameters
    MST_TAMS_CALLHOME, // CallHome

    MST_SETUP_POS_INFO, // POS Information

    MST_SETUP_INITIALIZE, // Initialize

    MST_SETUP_CHANGE_MASTER_PIN, // Change Master's Password

    MST_SETUP_HW_TEST, // Hardware Test
    MST_PRINTER_TEST, // Printer Test
    MST_MSR_TEST, // MSR Test
    MST_MODEM_TEST, // Modem Test
    MST_ICCARD_TEST, // IC Card Test
    MST_KEY_TEST, // Key Test
    MST_LCD_TEST, // LCD Test
    MST_RS232_TEST, // RS232 Test
    MST_RTC_TEST, // RTC Test


    MST_F1_FUNC, // F1 Functions

    //	MST_F1_MERCHANTOPER,							// Select Merchant Operations menu item
    MST_F1_REVERSAL_TRANS, // Supervisor Menu - Select Reversal menu item
    //	MST_F1_CUR_MERCHANT_TOTAL,						// Current Merchant Total
    MST_F1_ENDOFDAY, // Supervisor Menu - Select End-of-Day menu item
    MST_F1_EOD_TODAY, // Supervisor Menu - End-of-Day - Today
    MST_F1_EOD_REPRINT, // Supervisor Menu - End-of-Day - Reprint
    MST_F1_EOD_PASTDAY, // Supervisor Menu - End-of-Day - PastDay

    MST_F1_CHANGE_MERCHANT_PIN, // Change Merchant's Password

    MST_F1_REMOTEDOWNLOAD, // Remote Download


    MST_F3_FUNC, // F3 Functions

    MST_F3_SET_CALLHOME, // Set Call Home
    MST_F3_SET_COMM_TIMEOUT, // Set Comm Timeout
    MST_F3_SET_DATE, // Set Date
    MST_F3_SET_TIME, // Set Time
    MST_F3_SET_CONTRAST, // Set LCD Contrast
    MST_F3_SET_BEEP_SOUND, // Set Beep Sound


    MST_CUSTOMER_TRANS, // 36 Select Customer Trans.

    MST_BUY, // Buy
    MST_BALANCE_INQUIRY, // Balance Inquiry
    MST_BILL_PAYMENT, // Bill Payment
    MST_SIM_CHARGE, // SIM Charge


    MST_PRINT_REVERSAL_RECEIPT, // Print Reversal Receipt
    MST_REVERSAL_MODE, // Reversal Mode
    MST_REVERSAL, // Reversal
    MST_REVERSAL_SETTELEPHONE, // Set Telephone
    MST_PRINT_UNSUCCESSFUL_REVERSAL_RECEIPT, // Print Unsuccessful Reversal Receipt

} _eMainService;

/* */
