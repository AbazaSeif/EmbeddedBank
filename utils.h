
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
				     1. 입력한 번호가 메뉴 화면 내의 메뉴 아이템 중에 있을 경우 선택바만
				        해당되는 메뉴 화면의 라인에 위치시킨다.
				     2. 입력한 번호가 메뉴 화면 내의 메뉴 아이템 번호보다 작을 경우
				        입력한 번호의 메뉴 아이템부터 메뉴 화면의 라인 수 만큼 메뉴 아이템을
				        메뉴 화면에 표시하고, 선택바를 메뉴 화면의 첫번째 라인에 위치시킨다.
				     3. 입력한 번호가 메뉴 화면 내의 메뉴 아이템 번호보다 클 경우
				        입력한 번호의 메뉴 아이템까지 메뉴 화면의 라인 수 만큼 메뉴 아이템을
				        메뉴 화면에 표시하고, 선택바를 메뉴 화면의 마지막 라인에 위치시킨다.
				*  : Scroll up
				     1. 선택바가 첫번째 메뉴 아이템에 위치해 있으면 마지막 메뉴 아이템에서
				        메뉴 화면의 라인 수 만큼 메뉴 아이템을 메뉴 화면에 표시하고,
				        선택바를 메뉴 화면의 마지막 라인에 위치시킨다.
				     2. 선택바가 메뉴 화면의 첫번째 라인에 위치해 있으면 각 메뉴 아이템들을
				        한 칸씩 아래로 이동시키고, 선택바를 메뉴 화면의 첫번째 라인에 위치시킨다.
				     3. 선택바가 메뉴 화면의 첫번째 라인에 위치해 있지 않으면 선택바를 한 칸
				        위로 이동다.
				#  : Scroll down
				     1. 선택바가 마지막 메뉴 아이템에 위치해 있으면 첫번째 메뉴 아이템부터
				        메뉴 화면의 라인 수 만큼 메뉴 아이템을 메뉴 화면에 표시하고,
				        선택바를 메뉴 화면의 첫번째 라인에 위치시킨다.
				     2. 선택바가 메뉴 화면의 마지막 라인에 위치해 있으면 각 메뉴 아이템들을
				        한 칸씩 위로 이동시키고, 선택바를 메뉴 화면의 마지막 라인에 위치시킨다.
				     3. 선택바가 메뉴 화면의 마지막 라인에 위치해 있지 않으면 선택바를 한 칸
				        아래로 이동다.
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
