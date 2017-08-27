#ifndef SFONTLIB_H
#define SFONTLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#define FLEX5100

#ifndef FLEX7000
	#define MAX_FONT_NUM	10
	#define LCD_WIDTH		128
	#define LCD_HEIGHT		64
	#define BYTESPERLINE	16
#endif

/* Font Attribute */
#define FA_DIRTY		0x01
#define FA_UNDERLINE	0x02
#define FA_INVERT		0x04

/* Set Display Mode */
#define SDM_TEXT_MASK	0x03
#define SDM_TEXT_AND	0x00
#define SDM_TEXT_OR		0x01
#define SDM_TEXT_XOR	0x02

#define SDM_ONOFF_MASK	0x0C
#define SDM_TEXT_ON		0x04
#define SDM_TEXT_OFF	0x00
#define SDM_GRAPHIC_ON	0x08
#define SDM_GRAPHIC_OFF	0x00

/* Clear Screen Mode */
#define CS_TEXT			0x01
#define CS_GRAPHIC		0x02
#define CS_ALL			0x03

/* Draw Bitmap Mode */
#define DBM_INVERT	0x04
#define DBM_AND		0x00
#define DBM_OR		0x01
#define DBM_XOR		0x02

/* Set Invert Mode */
#define INV_SET			0x01
#define INV_CLEAR		0x00

/* Set Under Line Mode */
#define ULINE_SET		0x01
#define ULINE_CLEAR		0x00

extern int AddFont(int iFntIdx, int iWidth, int iHeight, int iFirstChar, int iLastChar, char *pFntDataAddr);
extern int AttachExtFont(int iFntIdx, int iExtFntType, void (*pGetExtFntImg)(int, int));
extern void SetDisplayMode(int iDispOnOff, int iTextMode);
extern int GetDisplayMode();
#ifndef FLEX7000
extern int InitFontInfo();
#else
extern int InitFontInfo(int iMaxFontNum, int iLcdWidth, int iLcdHeight);
extern void CloseFontInfo();
#endif

extern int LcdDisplay();
extern void ClrScr(int iMode, int iRedraw);
extern int SelectFont(int iFont);
extern int LcdTextOutA(int x, int y, char *pStr, int iFontAttr, int iFont, int iRedraw);
extern int SetLcdInvertA(int x, int y, int count, int iMode, int iFont, int iRedraw);
extern int SetLcdULineA(int x, int y, int count, int iMode, int iFont, int iRedraw);
extern void SetLcdTextPosA(int x, int y, int iFont);
extern void GetLcdTextPosA(int *x, int *y, int iFont);
extern void GetLcdTextMetricsA(int *iRow, int *iCol, int iFont);
extern int lcd_printfA(const char *format, ...);	/* iRedraw == TRUE */
extern int lcd_printf(const char *format, ...);		/* iRedraw == FALSE */
extern int lcd_putcharA(int c, int iRedraw);

extern void LcdDrawPixelA(int x, int y, int mode, int iRedraw);
extern void LcdDrawLineA(int x0, int y0, int x1, int y1, int iRedraw);
extern void LcdDrawRectA(int x0, int y0, int x1, int y1, int iRedraw);
extern void LcdDrawCircleA(int x0, int y0, int r, int iRedraw);
extern void LcdDrawEllipseA(int x0, int y0, int rx, int ry, int iRedraw);
extern void LcdDrawBitmapA(int x, int y, int iWidth, int iHeight, char *pSrc, int iDrawMode, int iRedraw);
extern void GetBitmap(int xpos, int ypos, int iWidth, int iHeight, char *pDest, int iSrc);
extern int LcdDrawTextA(int x, int y, char *pStr, int iFontAttr, int iFont, int iRedraw);
extern int GetLcdPixel(int x, int y);

/* Function Define */
/* if(iFont == -1) iFont = current font */
#define LcdTextOut(a, b, c)				LcdTextOutA(a, b, c, 0, -1, 0)
#define SetLcdInvert(a, b, c)			SetLcdInvertA(a, b, c, 1, -1, 0)
#define SetLcdULine(a, b, c)			SetLcdULineA(a, b, c, 1, -1, 0)
#define SetLcdTextPos(a, b)				SetLcdTextPosA(a, b, -1)
#define GetLcdTextPos(a, b)				GetLcdTextPosA(a, b, -1)
#define GetLcdTextMetrics(a, b)			GetLcdTextMetricsA(a, b, -1)
#define lcd_putchar(a)					lcd_putcharA(a, 0)

#define LcdDrawText(a, b, c)			LcdDrawTextA(a, b, c, 0, -1, 0)
#define LcdDrawPixel(a, b)				LcdDrawPixelA(a, b, 1, 0)
#define LcdDrawLine(a, b, c, d)			LcdDrawLineA(a, b, c, d, 0)
#define LcdDrawRect(a, b, c, d)			LcdDrawRectA(a, b, c, d, 0)
#define LcdDrawCircle(a, b, c)			LcdDrawCircleA(a, b, c, 0)
#define LcdDrawEllipse(a, b, c, d)		LcdDrawEllipseA(a, b, c, d, 0)
#define LcdDrawBitmap(a, b, c, d, e, f)	LcdDrawBitmapA(a, b, c, d, e, f, 0)

#ifndef FLEX7000
extern char EXTFONTBUF[128], GraphicBuf[1024];
#else
extern char EXTFONTBUF[128], *GraphicBuf, *LcdDispBuf;
#endif

#ifndef FALSE
	#define FALSE	1
#endif
#ifndef TRUE
	#define TRUE	1
#endif

#ifdef __cplusplus
}
#endif

#endif
