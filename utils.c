
/*======================================================================*/
/*																		*/
/*									UTILS.C								*/
/*																		*/
/*======================================================================*/

#include "system.h"
#include "extern.h"


//#define UTILS_DEBUG


static const char ALP_tbl[2][10][4] = {
    {
        {'-', ',', ' ', 0x00}, // '0'
        {'Q', 'Z', '.', 0x00}, // '1'
        {'A', 'B', 'C', 0x00}, // '2'
        {'D', 'E', 'F', 0x00}, // '3'
        {'G', 'H', 'I', 0x00}, // '4'
        {'J', 'K', 'L', 0x00}, // '5'
        {'M', 'N', 'O', 0x00}, // '6'
        {'P', 'R', 'S', 0x00}, // '7'
        {'T', 'U', 'V', 0x00}, // '8'
        {'W', 'X', 'Y', 0x00} // '9'
    },
    {
        {'-', ',', ' ', 0x00}, // '0'
        {'q', 'z', '.', 0x00}, // '1'
        {'a', 'b', 'c', 0x00}, // '2'
        {'d', 'e', 'f', 0x00}, // '3'
        {'g', 'h', 'i', 0x00}, // '4'
        {'j', 'k', 'l', 0x00}, // '5'
        {'m', 'n', 'o', 0x00}, // '6'
        {'p', 'r', 's', 0x00}, // '7'
        {'t', 'u', 'v', 0x00}, // '8'
        {'w', 'x', 'y', 0x00} // '9'
    }
};

short sStartDisplayMenuLine;
short sSelectedMenuItemLine;
short sSelectedMenuItemNo;
short sTotalMenuItemNo;
char *psz17FirstMenuItemMsgAddr;

static unsigned char ucALPInputMode;
static unsigned char ucALPKeyInputFlag;
static unsigned char ucPreALPKey;
static unsigned char ucALPIndex;


void MenuScrollUpDown(char start_line, short *selected_item_no, short *selected_item_line, short max_item, char *msg_start_addr, char input_key, char lang);
void SetMenuScrollUpDownInfo(char start_line, short selected_item_no, short selected_item_line, short max_item, char *msg_start_addr);
void LCDDisplay4Lines(short DisplayMsgNo, char HighlightLine, char lang);
void InputAlpNoString(char YPos, char XPos, char MaxInputCnt, char InputKey, char *str);
void InitializeAlpNoInputParameter(unsigned char alphabet_mode);

/*
Scroll up/down menu, highlight on selected item and get its number
        Input
                start_line
                        start display line number (0 up to 3)
                selected_item_no
                        pointer of selected item number (1 up to max_item)
                selected_item_line
                        pointer of selected item line number (1 up to max_item)
                max_item
                        maximum item number of scroll up/down menu (1 up to 9)
                msg_start_addr
                        pointer of the first item message
                input_key
                        inputted key value
                                1-9: Item number (1 up to max_item)
                                     1. �Է��� ��ȣ�� �޴� ȭ�� ���� �޴� ������ �߿� ���� ��� ���ùٸ�
                                        �ش�Ǵ� �޴� ȭ���� ���ο� ��ġ��Ų��.
                                     2. �Է��� ��ȣ�� �޴� ȭ�� ���� �޴� ������ ��ȣ���� ���� ���
                                        �Է��� ��ȣ�� �޴� �����ۺ��� �޴� ȭ���� ���� �� ��ŭ �޴� ��������
                                        �޴� ȭ�鿡 ǥ���ϰ�, ���ùٸ� �޴� ȭ���� ù��° ���ο� ��ġ��Ų��.
                                     3. �Է��� ��ȣ�� �޴� ȭ�� ���� �޴� ������ ��ȣ���� Ŭ ���
                                        �Է��� ��ȣ�� �޴� �����۱��� �޴� ȭ���� ���� �� ��ŭ �޴� ��������
                                        �޴� ȭ�鿡 ǥ���ϰ�, ���ùٸ� �޴� ȭ���� ������ ���ο� ��ġ��Ų��.
 *  : Scroll up
                                     1. ���ùٰ� ù��° �޴� �����ۿ� ��ġ�� ������ ������ �޴� �����ۿ���
                                        �޴� ȭ���� ���� �� ��ŭ �޴� �������� �޴� ȭ�鿡 ǥ���ϰ�,
                                        ���ùٸ� �޴� ȭ���� ������ ���ο� ��ġ��Ų��.
                                     2. ���ùٰ� �޴� ȭ���� ù��° ���ο� ��ġ�� ������ �� �޴� �����۵���
                                        �� ĭ�� �Ʒ��� �̵���Ű��, ���ùٸ� �޴� ȭ���� ù��° ���ο� ��ġ��Ų��.
                                     3. ���ùٰ� �޴� ȭ���� ù��° ���ο� ��ġ�� ���� ������ ���ùٸ� �� ĭ
                                        ���� �̵���.
                                #  : Scroll down
                                     1. ���ùٰ� ������ �޴� �����ۿ� ��ġ�� ������ ù��° �޴� �����ۺ���
                                        �޴� ȭ���� ���� �� ��ŭ �޴� �������� �޴� ȭ�鿡 ǥ���ϰ�,
                                        ���ùٸ� �޴� ȭ���� ù��° ���ο� ��ġ��Ų��.
                                     2. ���ùٰ� �޴� ȭ���� ������ ���ο� ��ġ�� ������ �� �޴� �����۵���
                                        �� ĭ�� ���� �̵���Ű��, ���ùٸ� �޴� ȭ���� ������ ���ο� ��ġ��Ų��.
                                     3. ���ùٰ� �޴� ȭ���� ������ ���ο� ��ġ�� ���� ������ ���ùٸ� �� ĭ
                                        �Ʒ��� �̵���.
                lang
                        display language number
                                0: English
                                1: Farsi
	
        Output
                selected_item_no
                        pointer of selected item number (1 up to max_item)
 */
void MenuScrollUpDown(char start_line, short *selected_item_no, short *selected_item_line, short max_item, char *msg_start_addr, char input_key, char lang) {
    short i, max_lcd_line, max_disp_item_no;
    short disp_cnt, top_item_no, msg_disp_start_no;

    if (input_key <= 0 || (input_key > max_item && input_key != BTKEY_ASTERISK && input_key != BTKEY_SHARP)) {
        return;
    }

    // Maximum line number of LCD
    max_lcd_line = 4;
    // Maximum display item number on LCD
    start_line &= 0x03;
    max_disp_item_no = max_lcd_line - start_line;

    // Set disp_cnt to max_item
    disp_cnt = max_item;
    // If disp_cnt is greater than max_disp_item_no, set disp_cnt to max_disp_item_no
    if (disp_cnt > max_disp_item_no) {
        disp_cnt = max_disp_item_no;
    }

    switch (input_key) {
        case BTKEY_ASTERISK: // Scroll up
            // Decrease selected_item_no
            *selected_item_no -= 1;

            // If previous selected_item_no is the first menu item
            if (*selected_item_no <= 0) {
                // Set selected_item_no to max_item
                *selected_item_no = max_item;
                // Calculate top_item_no
                top_item_no = *selected_item_no - (disp_cnt - 1);
                // If top_item_no is less than or equal to zero, set top_item_no to one
                if (top_item_no <= 0) {
                    top_item_no = 1;
                }
                // Set selected_item_line to the last line of menu window
                *selected_item_line = start_line + (disp_cnt - 1);
            }                // If previous selected_item_no is not the first menu item
            else {
                // If previous selected_item_line is the first line of menu window
                if (*selected_item_line <= start_line) {
                    // Set top_item_no to selected_item_no
                    top_item_no = *selected_item_no;
                    // Set selected_item_line to the first line of menu window
                    *selected_item_line = start_line;
                }                    // If previous selected_item_line is not the first line of menu window
                else {
                    // Calculate top_item_no
                    top_item_no = (*selected_item_no + 1) - (*selected_item_line - start_line);
                    // If top_item_no is less than or equal to zero, set top_item_no to one
                    if (top_item_no <= 0) {
                        top_item_no = 1;
                    }
                    // Calculate selected_item_line
                    *selected_item_line = start_line + (*selected_item_no - top_item_no);
                }
            }
            break;

        case BTKEY_SHARP: // Scroll down
            // Increase selected_item_no
            *selected_item_no += 1;

            // If previous selected_item_no is the last menu item
            if (*selected_item_no > max_item) {
                // Set selected_item_no to one
                *selected_item_no = 1;
                // Set top_item_no to one
                top_item_no = 1;
                // Set selected_item_line to the first line of menu window
                *selected_item_line = start_line;
            }                // If previous selected_item_no is not the last menu item
            else {
                // If previous selected_item_line is the last line of menu window
                if (*selected_item_line >= (start_line + (disp_cnt - 1))) {
                    // Calculate top_item_no
                    top_item_no = *selected_item_no - (disp_cnt - 1);
                    // If top_item_no is less than or equal to zero, set top_item_no to one
                    if (top_item_no <= 0) {
                        top_item_no = 1;
                    }
                    // Set selected_item_line to the last line of menu window
                    *selected_item_line = start_line + (disp_cnt - 1);
                }                    // If previous selected_item_line is not the last line of menu window
                else {
                    // Calculate top_item_no
                    top_item_no = (*selected_item_no - 1) - (*selected_item_line - start_line);
                    // If top_item_no is less than or equal to zero, set top_item_no to one
                    if (top_item_no <= 0) {
                        top_item_no = 1;
                    }
                    // Calculate selected_item_line
                    *selected_item_line = start_line + (*selected_item_no - top_item_no);
                }
            }
            break;

        default: // Press item number
            // Return if selected_item_no is equal to input_key
            //if (*selected_item_no == input_key) {
            //	return;
            //}

            // Calculate top_item_no
            top_item_no = *selected_item_no - (*selected_item_line - start_line);
            // If top_item_no is less than or equal to zero, set top_item_no to one
            if (top_item_no <= 0) {
                top_item_no = 1;
            }
            // Set selected_item_no to input_key
            *selected_item_no = input_key;

            // If input_key is within menu item numbers of menu window
            if (input_key >= top_item_no && input_key <= (top_item_no + (disp_cnt - 1))) {
                // Calculate selected_item_line
                *selected_item_line = start_line + (*selected_item_no - top_item_no);
            }                // If input_key is not within menu item numbers of menu window
            else {
                // If input_key is less than top_item_no
                if (input_key < top_item_no) {
                    // Set top_item_no to selected_item_no
                    top_item_no = *selected_item_no;
                    // Set selected_item_line to the first line of menu window
                    *selected_item_line = start_line;
                }                    // If input_key is greater than top_item_no+(disp_cnt-1)
                else {
                    // Calculate top_item_no
                    top_item_no = *selected_item_no - (disp_cnt - 1);
                    // If top_item_no is less than or equal to zero, set top_item_no to one
                    if (top_item_no <= 0) {
                        top_item_no = 1;
                    }
                    // Set selected_item_line to the last line of menu window
                    *selected_item_line = start_line + (disp_cnt - 1);
                }
            }
            break;
    }

    // Calculate first display item message mumber
    msg_disp_start_no = top_item_no - 1;
    // Display item messages
    for (i = 0; i < disp_cnt; i++) {
        LCD_DisplayLine(i + start_line, LEFT_JUSTIFIED, msg_start_addr + (msg_disp_start_no + i)*17, lang);
    }
    // Highlight on one LCD line
    LCD_HighlightLineOn(*selected_item_line);
}

void SetMenuScrollUpDownInfo(char start_line, short selected_item_no, short selected_item_line, short max_item, char *msg_start_addr) {
    sStartDisplayMenuLine = start_line;
    sSelectedMenuItemNo = selected_item_no;
    sSelectedMenuItemLine = selected_item_line;
    sTotalMenuItemNo = max_item;
    psz17FirstMenuItemMsgAddr = msg_start_addr;
}

/*
Display 4 line messages on LCD
        Input
                DisplayMsgNo
                        message number for displaying of 4 lines LCD messages
                HighlightLine
                        less than 0: Don't care
                        0 up to 3  : Highlight on for specific line
                lang
                        display language number
                                0: English
                                1: Farsi
 */
void LCDDisplay4Lines(short DisplayMsgNo, char HighlightLine, char lang) {
    short i, j, index;
    char temp[17];
    unsigned char ch;

    LCD_CursorOff();
    for (j = 0; j < 4; j++) {
        index = LCD_MSG_TBL4[DisplayMsgNo][j];
        if ((index & M1_____________Dummy) == M1_____________Dummy) {
            continue;
        }
        memset(temp, 0x00, sizeof (temp));
        if (lang) {
            lang = 1;
        }
        strncpy(temp, LCD_MSG_TBL1[lang][index], 16);
        if (lang) {
            IndianNo2FarsiNo(temp, strlen(temp));
        }
        memcpy(&DSPBUF0[j * 16], temp, 16);
        LCD_DISPLAY(4, j, 0, 16);
    }

    if (HighlightLine >= 0) {
        HighlightLine &= 0x03;
        LCD_HighlightLineOn(HighlightLine);
    }
}

// Get a null terminalted Alphabet and Number string by keypad

void InputAlpNoString(char YPos, char XPos, char MaxInputCnt, char InputKey, char *str) {
    int i;
    char ch, YAdd;

    if (iModelName == IC3100PE) {
        if (InputKey > BTKEY_9 && InputKey != BTKEY_CLEAR && InputKey != BTKEY_SFUNC_IC3100PE) {
            return;
        }
        if (InputKey == BTKEY_SFUNC_IC3100PE) {
            InputKey = 99;
        }
    } else {
        if (InputKey > BTKEY_9 && InputKey != BTKEY_CLEAR && InputKey != BTKEY_SFUNC_IC5100P) {
            return;
        }
        if (InputKey == BTKEY_SFUNC_IC5100P) {
            InputKey = 99;
        }
    }

    LCD_CursorOff();
    switch (InputKey) {
        case BTKEY_CLEAR: // Back Space Key
            i = strlen(str);
            if (i) {
                ucKeyCnt = i - 1;
                YAdd = (XPos + ucKeyCnt) / 16;
                LCD_DisplayChar(YPos + YAdd, XPos + ucKeyCnt - YAdd * 16, ' ', ucLangFlag);
            } else {
                ucKeyCnt = 0;
            }

            if (ucALPInputMode) {
                ucALPKeyInputFlag = 0;
                ucALPIndex = 0;
            }

            str[ucKeyCnt] = 0x00;
            break;

        case 99: // ALP/NUM Toggle Key
            if (ucALPInputMode && ucALPKeyInputFlag) {
                if (ucKeyCnt < MaxInputCnt) {
                    ucKeyCnt++;
                }
            }

            if (ucKeyCnt == 0) {
                for (i = 0; i < MaxInputCnt; i++) {
                    YAdd = (XPos + i) / 16;
                    LCD_DisplayChar(YPos + YAdd, XPos + i - YAdd * 16, ' ', ucLangFlag);
                }
                memset(str, 0x00, MaxInputCnt + 1);
            }

            if (ucALPKeyInputFlag) {
                ucALPKeyInputFlag = 0;
                ucALPIndex = 0;
                str[ucKeyCnt] = 0x00;
                break;
            }

            //ucALPInputMode ^= 0x01;	// ucALPInputMode=0: Number, ucALPInputMode=1: Alphabet
            ucALPInputMode = ++ucALPInputMode % 3; // 0: NUM, 1: ALP, 2: alp
            if (ucALPInputMode) {
                ucALPKeyInputFlag = 0;
                ucALPIndex = 0;
            }

            // Display key input mode
            if (ucALPInputMode == 1) {
                // "           [ALP]",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1AlphabetMode_00001], ucLangFlag);
            } else if (ucALPInputMode == 2) {
                // "           [alp]",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1AlphabetMode_00002], ucLangFlag);
            } else {
                // "           [NUM]",
                LCD_DisplayLine(3, LEFT_JUSTIFIED, (char *) LCD_MSG_TBL1[ucLangFlag][M1NumberMode_0000001], ucLangFlag);
            }

            str[ucKeyCnt] = 0x00;
            break;

        default:
            if (ucKeyCnt >= MaxInputCnt) {
                break;
            }

            if (ucALPInputMode) { // Alpabet key inupt mode
                if (!ucALPKeyInputFlag) { // First alpabet key input
                    if (ucKeyCnt == 0) {
                        for (i = 0; i < MaxInputCnt; i++) {
                            YAdd = (XPos + i) / 16;
                            LCD_DisplayChar(YPos + YAdd, XPos + i - YAdd * 16, ' ', ucLangFlag);
                        }
                        memset(str, 0x00, MaxInputCnt + 1);
                    }
                    ucALPKeyInputFlag = 1;
                    ucPreALPKey = InputKey;
                    ch = ALP_tbl[ucALPInputMode - 1][ucPreALPKey][ucALPIndex];
                    YAdd = (XPos + ucKeyCnt) / 16;
                    LCD_DisplayChar(YPos + YAdd, XPos + ucKeyCnt - YAdd * 16, ch, ucLangFlag);
                    str[ucKeyCnt] = ch;
                    str[ucKeyCnt + 1] = 0x00;
                } else { // Not first alpabet key input
                    if (InputKey == ucPreALPKey) { // Key input value is the same of previous key value
                        ucALPIndex++;
                        ch = ALP_tbl[ucALPInputMode - 1][ucPreALPKey][ucALPIndex];
                        if (ch == 0x00) {
                            ucALPIndex = 0;
                            ch = ALP_tbl[ucALPInputMode - 1][ucPreALPKey][ucALPIndex];
                        }
                        YAdd = (XPos + ucKeyCnt) / 16;
                        LCD_DisplayChar(YPos + YAdd, XPos + ucKeyCnt - YAdd * 16, ch, ucLangFlag);
                        str[ucKeyCnt] = ch;
                        str[ucKeyCnt + 1] = 0x00;
                    } else { // Key input value is not the same of previous key value
                        ucKeyCnt++;
                        str[ucKeyCnt] = 0x00;
                        if (ucKeyCnt < MaxInputCnt) {
                            ucALPIndex = 0;
                            ucPreALPKey = InputKey;
                            ch = ALP_tbl[ucALPInputMode - 1][ucPreALPKey][ucALPIndex];
                            YAdd = (XPos + ucKeyCnt) / 16;
                            LCD_DisplayChar(YPos + YAdd, XPos + ucKeyCnt - YAdd * 16, ch, ucLangFlag);
                            str[ucKeyCnt] = ch;
                            str[ucKeyCnt + 1] = 0x00;
                        }
                    }
                }
            } else { // Numeric key input
                if (ucKeyCnt == 0) {
                    for (i = 0; i < MaxInputCnt; i++) {
                        YAdd = (XPos + i) / 16;
                        LCD_DisplayChar(YPos + YAdd, XPos + i - YAdd * 16, ' ', ucLangFlag);
                    }
                    memset(str, 0x00, MaxInputCnt + 1);
                }

                ch = InputKey + '0';
                YAdd = (XPos + ucKeyCnt) / 16;
                LCD_DisplayChar(YPos + YAdd, XPos + ucKeyCnt - YAdd * 16, ch, ucLangFlag);
                str[ucKeyCnt++] = ch;
                str[ucKeyCnt] = 0x00;
            }
            break;
    }

    if (ucKeyCnt < MaxInputCnt) {
        YAdd = (XPos + ucKeyCnt) / 16;
        LCD_CursorOn(YPos + YAdd, XPos + ucKeyCnt - YAdd * 16);
    }
}

// Initialize Alphabet and Number input parameters

void InitializeAlpNoInputParameter(unsigned char alphabet_mode) {
    if (alphabet_mode == 0) {
        ucALPInputMode = 0;
    } else if (alphabet_mode == 1) {
        ucALPInputMode = 1;
    } else {
        ucALPInputMode = 2;
    }

    ucALPKeyInputFlag = 0;
    ucPreALPKey = BTKEY_NULL;
    ucALPIndex = 0;
}

/* */
