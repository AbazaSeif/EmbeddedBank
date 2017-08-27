
/*======================================================================*/
/*																		*/
/*									UTILS.H								*/
/*																		*/
/*======================================================================*/

extern short sStartDisplayMenuLine;
extern short sSelectedMenuItemLine;
extern short sSelectedMenuItemNo;
extern short sTotalMenuItemNo;
extern char *psz17FirstMenuItemMsgAddr;


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
extern void MenuScrollUpDown(char start_line, short *selected_item_no, short *selected_item_line, short max_item, char *msg_start_addr, char input_key, char lang);

extern void SetMenuScrollUpDownInfo(char start_line, short selected_item_no, short selected_item_line, short max_item, char *msg_start_addr);

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
extern void LCDDisplay4Lines(short DisplayMsgNo, char HighlightLine, char lang);

// Get a null terminalted Alphabet and Number string by keypad
extern void InputAlpNoString(char YPos, char XPos, char MaxInputCnt, char InputKey, char *str);

// Initialize Alphabet and Number input parameters
extern void InitializeAlpNoInputParameter(unsigned char alphabet_mode);

/* */
