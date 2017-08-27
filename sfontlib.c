
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "sfontlib.h"

/* Lcd Display Buffer */
#define LDB_TEXT  0
#define LDB_GRAPHIC  1

typedef unsigned char U08;

typedef struct {
    int iValid;
    int iWidth; /* Font Width */
    int iHeight; /* Font Height */
    int iCol; /* LCD_WIDTH / iWidth */
    int iRow; /* LCD_HEIGHT / iHeight */
    int iFirstChar; /* First Character */
    int iLastChar; /* Last Character */
    int iCharSize; /* 1 Character Size */
#ifndef FLEX7000
    U08 FntCharBuf[320]; /* [32][10] for 4*6 font */
    char FntAttrBuf[320]; /* [32][10] for 4*6 font */
#else
    U08 *FntCharBuf;
    char *FntAttrBuf;
#endif
    char *pFntDataAddr;
    int xPos; /* X Position for Text Mode */
    int yPos; /* Y Position for Text Mode */
    /* Extension Font Info */
    int iExtFntType;
    void (*pGetExtFntImg)(int i2BCode, int iFntIdx);
} FONTINFO;

extern int _formatted_write(const char *format, void put_one_char(char, void *),
        void *secret_pointer, va_list ap);

#ifndef FLEX7000
extern void GRA_LOAD(void *, char, char);
#else
extern void UpdateLcd();
#endif

#ifndef FLEX7000
static FONTINFO FontInfo[MAX_FONT_NUM];
static char TextBuf[BYTESPERLINE * LCD_HEIGHT], LcdBmpBuf[BYTESPERLINE * LCD_HEIGHT];
char EXTFONTBUF[128], GraphicBuf[BYTESPERLINE * LCD_HEIGHT], LcdDispBuf[BYTESPERLINE * LCD_HEIGHT];
#else
static int MAX_FONT_NUM = 0;
static int LCD_WIDTH = 0;
static int LCD_HEIGHT = 0;
static int BYTESPERLINE = 0;
static FONTINFO *FontInfo;
static char *TextBuf, *LcdBmpBuf;
char EXTFONTBUF[128], *GraphicBuf, *LcdDispBuf = NULL;
#endif
static char fntmask[64];
static int iDisplayMode, iCurFontIdx;
static const int iFontMask[9] = {
    0xFFFF, /* 11111111 11111111 */
    0xFEFF, /* 11111110 11111111 */
    0xFCFF, /* 11111100 11111111 */
    0xF8FF, /* 11111000 11111111 */
    0xF0FF, /* 11110000 11111111 */
    0xE0FF, /* 11100000 11111111 */
    0xC0FF, /* 11000000 11111111 */
    0x80FF, /* 10000000 11111111 */
    0x00FF /* 00000000 11111111 */
};

static void MakeText2Graphic();
static int PutTextChar(int xpos, int ypos, U08 *pchar, int iFontAttr, int iFntIdx, int iMode);
static void lcd_put_one_char(char c, void *dummy);
static void SwapInt(int* pa, int* pb);
static void Draw8Point(int x0, int y0, int xoff, int yoff);
static void DrawImageA(int xpos, int ypos, int iWidth, int iHeight, char *pSrc, char *pDest, int iAttr, int iDispMode);
int LcdDisplayA(int iMode);

int AddFont(int iFntIdx, int iWidth, int iHeight, int iFirstChar, int iLastChar, char *pFntDataAddr) {
    if (iFntIdx >= MAX_FONT_NUM || iFntIdx < 0)
        return -1;

    FontInfo[iFntIdx].iWidth = iWidth;
    FontInfo[iFntIdx].iHeight = iHeight;
    FontInfo[iFntIdx].iCol = LCD_WIDTH / iWidth;
    FontInfo[iFntIdx].iRow = LCD_HEIGHT / iHeight;
    FontInfo[iFntIdx].iFirstChar = iFirstChar;
    FontInfo[iFntIdx].iLastChar = iLastChar;
    FontInfo[iFntIdx].iCharSize = (int) ((iWidth + 7) / 8) * iHeight;
#ifdef FLEX7000
    FontInfo[iFntIdx].FntCharBuf = (char *) malloc(FontInfo[iFntIdx].iCol * FontInfo[iFntIdx].iRow);
    FontInfo[iFntIdx].FntAttrBuf = (char *) malloc(FontInfo[iFntIdx].iCol * FontInfo[iFntIdx].iRow);
#endif
    memset(FontInfo[iFntIdx].FntCharBuf, 0x00, FontInfo[iFntIdx].iCol * FontInfo[iFntIdx].iRow);
    memset(FontInfo[iFntIdx].FntAttrBuf, 0x00, FontInfo[iFntIdx].iCol * FontInfo[iFntIdx].iRow);
    FontInfo[iFntIdx].pFntDataAddr = pFntDataAddr;
    FontInfo[iFntIdx].iValid = 1;

    return 0;
}

int AttachExtFont(int iFntIdx, int iExtFntType, void (*pGetExtFntImg)(int, int)) {
    if (iFntIdx >= MAX_FONT_NUM || iFntIdx < 0 || !FontInfo[iFntIdx].iValid) return -1;
    if (!iExtFntType || !pGetExtFntImg) return -1;

    FontInfo[iFntIdx].iExtFntType = iExtFntType;
    FontInfo[iFntIdx].pGetExtFntImg = pGetExtFntImg;

    return 0;
}

void SetDisplayMode(int iDispOnOff, int iTextMode) {
    iDisplayMode = (iDispOnOff & SDM_ONOFF_MASK) | (iTextMode & SDM_TEXT_MASK);
}

int GetDisplayMode() {
    return iDisplayMode;
}

#ifndef FLEX7000

int InitFontInfo() {
#else

int InitFontInfo(int iMaxFontNum, int iLcdWidth, int iLcdHeight) {
    MAX_FONT_NUM = iMaxFontNum;
    LCD_WIDTH = iLcdWidth;
    LCD_HEIGHT = iLcdHeight;
    BYTESPERLINE = (LCD_WIDTH + 7) / 8;

    FontInfo = (FONTINFO *) malloc(sizeof (FONTINFO) * MAX_FONT_NUM);
    TextBuf = (char *) malloc(BYTESPERLINE * LCD_HEIGHT);
    LcdBmpBuf = (char *) malloc(BYTESPERLINE * LCD_HEIGHT);
    GraphicBuf = (char *) malloc(BYTESPERLINE * LCD_HEIGHT);
    LcdDispBuf = (char *) malloc(((BYTESPERLINE + 3) & ~0x03) * LCD_HEIGHT);
#endif

    memset((char *) FontInfo, 0x00, sizeof (FONTINFO) * MAX_FONT_NUM);
    memset(TextBuf, 0x00, BYTESPERLINE * LCD_HEIGHT);
    memset(GraphicBuf, 0x00, BYTESPERLINE * LCD_HEIGHT);
    memset(LcdBmpBuf, 0x00, BYTESPERLINE * LCD_HEIGHT);
    memset(LcdDispBuf, 0x00, ((BYTESPERLINE + 3) & ~0x03) * LCD_HEIGHT);

    return 0;
}

void CloseFontInfo() {
#ifdef FLEX7000
    int i;

    for (i = 0; i < MAX_FONT_NUM; i++) {
        if (FontInfo[i].iValid) {
            free(FontInfo[i].FntCharBuf);
            free(FontInfo[i].FntAttrBuf);
        }
    }
    free(FontInfo);
    free(TextBuf);
    free(LcdBmpBuf);
    free(GraphicBuf);
    free(LcdDispBuf);
#endif
}

int SelectFont(int iFont) {
    if (iFont >= MAX_FONT_NUM || iFont < 0 || !FontInfo[iFont].iValid)
        return -1;
    iCurFontIdx = iFont;

    return iCurFontIdx;
}

void ClrScr(int iMode, int iRedraw) {
    int i;

    if (iMode & CS_TEXT) {
        for (i = 0; i < MAX_FONT_NUM; i++) {
            if (FontInfo[i].iValid) {
                memset(FontInfo[i].FntCharBuf, 0x00, FontInfo[i].iCol * FontInfo[i].iRow);
                memset(FontInfo[i].FntAttrBuf, 0x00, FontInfo[i].iCol * FontInfo[i].iRow);
            }
        }
        memset(TextBuf, 0x00, BYTESPERLINE * LCD_HEIGHT);
    }
    if (iMode & CS_GRAPHIC) {
        memset(GraphicBuf, 0x00, BYTESPERLINE * LCD_HEIGHT);
    }
    memset(LcdDispBuf, 0x00, BYTESPERLINE * LCD_HEIGHT);
    if (iRedraw) LcdDisplay();
}

void ClrScrA(int iMode, int iStart, int iStop) {
    int i, j;
    int iStartRow, iStopRow;

    if (iStart < 0) iStart = 0;
    if (iStop > 7) iStop = 7;
    if (iStop < iStart)
        return;

    if (iMode & CS_TEXT) {
        for (i = 0; i < MAX_FONT_NUM; i++) {
            if (FontInfo[i].iValid) {
                iStartRow = (iStart * 8) / FontInfo[i].iHeight;
                iStopRow = (iStop * 8) / FontInfo[i].iHeight;
                /*
                Rprintf("Font[%d] : H(%d), W(%d), R(%d), C(%d), SR(%d), ER(%d)\r\n", i, FontInfo[i].iHeight, FontInfo[i].iWidth,
                        FontInfo[i].iRow, FontInfo[i].iCol, iStartRow, iStopRow);
                Font[0] : H(16), W(8), R(4), C(16), SR(2), ER(3)
                Font[1] : H(8), W(8), R(8), C(16), SR(4), ER(7)
                Font[2] : H(8), W(6), R(8), C(21), SR(4), ER(7)
                 */
                memset(&FontInfo[i].FntCharBuf[FontInfo[i].iCol * iStartRow], 0x00, FontInfo[i].iCol * (iStopRow - iStartRow + 1));
                memset(&FontInfo[i].FntAttrBuf[FontInfo[i].iCol * iStartRow], 0x00, FontInfo[i].iCol * (iStopRow - iStartRow + 1));
                /*				for(j = 0; j < FontInfo[i].iCol * iStartRow; j++)
                                                        FontInfo[i].FntAttrBuf[j] |= FA_DIRTY;
                                                for(j = FontInfo[i].iCol * (iStopRow + 1); j < FontInfo[i].iCol * FontInfo[i].iRow; j++)
                                                        FontInfo[i].FntAttrBuf[j] |= FA_DIRTY;
                 */
            }
        }
        memset(&TextBuf[BYTESPERLINE * (iStart * 8)], 0x00, BYTESPERLINE * ((iStop - iStart + 1) * 8));
    }
    if (iMode & CS_GRAPHIC) {
        memset(&GraphicBuf[BYTESPERLINE * (iStart * 8)], 0x00, BYTESPERLINE * ((iStop - iStart + 1) * 8));
    }
    memset(LcdDispBuf, 0x00, BYTESPERLINE * LCD_HEIGHT);

    LcdDisplay();
}

static void DrawImageA(int xpos, int ypos, int iWidth, int iHeight, char *pSrc, char *pDest, int iAttr, int iDispMode) {
    int i, j, idx, invert;
    int xdot, xoffset1, xoffset2, iBytePerLine;
    char mask, font, bits;

    iBytePerLine = (iWidth + 7) / 8;
    invert = (iAttr & FA_INVERT) ? 0xFF : 0x00;
    for (i = 0; i < iBytePerLine - 1; i++) fntmask[i] = (char) 0xFF;
    fntmask[i] = (iWidth & 0x07) ? (0xFF00 >> (iWidth & 0x07)) & 0xFF : 0xFF;

    for (j = 0; j < iHeight; j++) {
        for (i = 0, bits = iWidth; i < iBytePerLine; i++, bits -= 8) {
            xdot = xpos + i * 8;
            xoffset1 = xdot & 0x07;
            idx = (xdot + (ypos + j) * BYTESPERLINE * 8) / 8;
            font = *(pSrc + j * iBytePerLine + i) ^ invert;
            if ((iAttr & FA_UNDERLINE) && (j + 1) == iHeight)
                font = 0xFF ^ invert;
            font &= fntmask[i];
            if (!xoffset1) {
                switch (iDispMode & SDM_TEXT_MASK) {
                    case SDM_TEXT_AND: pDest[idx] = (pDest[idx] & ~fntmask[i]) | font;
                        break;
                    case SDM_TEXT_OR: pDest[idx] |= font;
                        break;
                    case SDM_TEXT_XOR: pDest[idx] ^= font;
                        break;
                }
                continue;
            }
            if ((xoffset1 + ((bits & 0xF8) ? 8 : bits)) > 8) {
                mask = (iFontMask[8 - xoffset1] >> 8) & 0xFF;
                switch (iDispMode & SDM_TEXT_MASK) {
                    case SDM_TEXT_AND:
                        pDest[idx] = (pDest[idx] & mask) | ((font >> xoffset1) & ~mask);
                        xoffset2 = (xoffset1 + iWidth) & 0x07;
                        mask = xoffset2 ? ((iFontMask[xoffset2] >> xoffset2) & 0xFF) : 0x00;
                        pDest[idx + 1] = (pDest[idx + 1] & mask) | (font << (8 - xoffset1));
                        break;
                    case SDM_TEXT_OR:
                        pDest[idx] = pDest[idx] | ((font >> xoffset1) & ~mask);
                        pDest[idx + 1] = pDest[idx + 1] | (font << (8 - xoffset1));
                        break;
                    case SDM_TEXT_XOR:
                        pDest[idx] = pDest[idx] ^ ((font >> xoffset1) & ~mask);
                        pDest[idx + 1] = pDest[idx + 1] ^ (font << (8 - xoffset1));
                        break;
                }
            } else {
                mask = (iFontMask[iWidth - 8 * i] >> (xoffset1 + (iWidth - 8 * i))) & 0xFF;
                switch (iDispMode & SDM_TEXT_MASK) {
                    case SDM_TEXT_AND: pDest[idx] = (pDest[idx] & mask) | ((font >> xoffset1) & ~mask);
                        break;
                    case SDM_TEXT_OR: pDest[idx] = pDest[idx] | ((font >> xoffset1) & ~mask);
                        break;
                    case SDM_TEXT_XOR: pDest[idx] = pDest[idx] ^ ((font >> xoffset1) & ~mask);
                        break;
                }
            }
        }
    }
}

static int PutTextChar(int xpos, int ypos, U08 *pchar, int iFontAttr, int iFntIdx, int iMode) {
    int iCodeB, iVal2B, iFontWidth, iFontHeight;
    char *iCharOffset, *pOutBuf;

    switch (iMode) {
        case LDB_TEXT: pOutBuf = TextBuf;
            break;
        case LDB_GRAPHIC: pOutBuf = GraphicBuf;
            break;
    }
    if ((*pchar & 0x80) && FontInfo[iFntIdx].iExtFntType) { /* Check 2 Bytes Code */
        iCodeB = 2;
        iVal2B = ((*pchar << 8) | (*(pchar + 1) & 0xFF)) & 0xFFFF;
        FontInfo[iFntIdx].pGetExtFntImg(iVal2B, iFntIdx);
        iCharOffset = EXTFONTBUF;
    } else {
        iCodeB = 1;
        iCharOffset = FontInfo[iFntIdx].pFntDataAddr + (*pchar - FontInfo[iFntIdx].iFirstChar) * FontInfo[iFntIdx].iCharSize;
    }
    iFontWidth = FontInfo[iFntIdx].iWidth * iCodeB;
    iFontHeight = FontInfo[iFntIdx].iHeight;

    DrawImageA(xpos, ypos, iFontWidth, iFontHeight, iCharOffset, pOutBuf, iFontAttr, iDisplayMode);

    return (iCodeB - 1);
}

void LcdDrawBitmapA(int x, int y, int iWidth, int iHeight, char *pSrc, int iDrawMode, int iRedraw) {
    DrawImageA(x, y, iWidth, iHeight, pSrc, GraphicBuf, iDrawMode & 0x04, iDrawMode & 0x03);
    if (iRedraw) LcdDisplay();
}

void GetBitmap(int xpos, int ypos, int iWidth, int iHeight, char *pDest, int iSrc) {
    int i, j, idx, idxdest;
    int xdot, xoffset1, xoffset2, iBytePerLine;
    char mask, bits;
    char *pImgSrc;
    /*
    extern int Rprintf(const char *format, ...);
    Rprintf("TextBuf");
    for(i = 0; i < 1024; i++) {
            if((i % 16) == 0) Rprintf("\r\n");
            Rprintf("%02X ", TextBuf[i] & 0xFF);
    }
    Rprintf("\r\n");
    Rprintf("LcdBmpBuf");
    for(i = 0; i < 1024; i++) {
            if((i % 16) == 0) Rprintf("\r\n");
            Rprintf("%02X ", LcdBmpBuf[i] & 0xFF);
    }
    Rprintf("\r\n");
     */
    pImgSrc = iSrc ? GraphicBuf : LcdBmpBuf;
    iBytePerLine = (iWidth + 7) / 8;

    for (i = 0; i < iBytePerLine - 1; i++) fntmask[i] = (char) 0xFF;
    fntmask[i] = (iWidth & 0x07) ? (0xFF00 >> (iWidth & 0x07)) & 0xFF : 0xFF;

    for (j = 0; j < iHeight; j++) {
        for (i = 0, bits = iWidth; i < iBytePerLine; i++, bits -= 8) {
            xdot = xpos + i * 8;
            xoffset1 = xdot & 0x07;
            idx = (xdot + (ypos + j) * LCD_WIDTH) / 8;
            idxdest = i + j * iBytePerLine;
            if (!xoffset1) {
                pDest[idxdest] = pImgSrc[idx] & fntmask[i];
                continue;
            }
            if ((xoffset1 + ((bits & 0xF8) ? 8 : bits)) > 8) {
                mask = (iFontMask[8 - xoffset1] >> 8) & 0xFF;
                pDest[idxdest] = (pImgSrc[idx] & ~mask) << xoffset1;
                xoffset2 = (xoffset1 + ((bits & 0xF8) ? 8 : bits)) & 0x07;
                mask = (iFontMask[xoffset2] >> xoffset2) & 0xFF;
                pDest[idxdest] |= (pImgSrc[idx + 1] >> (8 - xoffset1)) & ~mask;
            } else {
                mask = (iFontMask[iWidth] >> (xoffset1 + iWidth)) & 0xFF;
                pDest[idxdest] = (pImgSrc[idx] << xoffset1) & ~mask;
            }
        }
    }
}

static void MakeText2Graphic() {
    int i, ch, xpos, ypos, idx, limit;
    U08 tmpbuf[2];

    for (idx = 0; idx < MAX_FONT_NUM; idx++) {
        if (!FontInfo[idx].iValid) continue;
        limit = FontInfo[idx].iRow * FontInfo[idx].iCol;
        for (i = 0; i < limit; i++) {
            if (!(FontInfo[idx].FntAttrBuf[i] & FA_DIRTY)) continue;
            ch = FontInfo[idx].FntCharBuf[i] & 0xFF;
            tmpbuf[0] = 0x00;
            if (!ch) {
                ch = tmpbuf[0] = 0x20;
            }
            if (ch < FontInfo[idx].iFirstChar) continue;
            if (ch > FontInfo[idx].iLastChar) {
                if (!FontInfo[idx].iExtFntType) continue;
                if (!(ch & 0x80)) continue;
            }
            xpos = (i % FontInfo[idx].iCol) * FontInfo[idx].iWidth;
            ypos = (i / FontInfo[idx].iCol) * FontInfo[idx].iHeight;

            FontInfo[idx].FntAttrBuf[i] &= ~FA_DIRTY;

            if (PutTextChar(xpos, ypos, (tmpbuf[0]) ? tmpbuf : &FontInfo[idx].FntCharBuf[i], FontInfo[idx].FntAttrBuf[i], idx, LDB_TEXT))
                FontInfo[idx].FntAttrBuf[++i] &= ~FA_DIRTY;
        }
    }
}

int LcdDisplay() {
    LcdDisplayA(0);
}

int LcdDisplayA(int iMode) {
    int i, j, k, idx, mask, offset0, offset;
    char right = 0, left = BYTESPERLINE - 1, top = LCD_HEIGHT - 1, bottom = 0;
    char ch, iTextMask, iGraphicMask;

    if (!(iDisplayMode & SDM_ONOFF_MASK))
        return 0;
    if (iDisplayMode & SDM_TEXT_ON)
        MakeText2Graphic();

    iTextMask = (iDisplayMode & SDM_TEXT_ON) ? 0xFF : 0x00;
    iGraphicMask = (iDisplayMode & SDM_GRAPHIC_ON) ? 0xFF : 0x00;

    for (j = 0; j < LCD_HEIGHT; j++) { /* ROW 64 */
        for (i = 0; i < BYTESPERLINE; i++) { /* COL 128 / 8 = 16 */
            idx = j * BYTESPERLINE + i;
            ch = (TextBuf[idx] & iTextMask) | (GraphicBuf[idx] & iGraphicMask);
            if (ch != LcdBmpBuf[idx]) {
                LcdBmpBuf[idx] = ch;
                if (i < left) left = i;
                if (i > right) right = i;
                if (j < top) top = j;
                if (j > bottom) bottom = j;
            }
        }
    }

    if (top > bottom || left > right) return 0; /* Not Changed */
    if (!bottom) bottom = top;
    if (!right) right = left;

#ifdef FLEX7000
    j = (BYTESPERLINE + 3) & ~0x03;
    for (i = 0; i < LCD_HEIGHT; i++)
        memcpy(&LcdDispBuf[j * i], &LcdBmpBuf[BYTESPERLINE * i], BYTESPERLINE);
    UpdateLcd();
#else
    /*	top /= 8;
            bottom /= 8;
     */ top = (top / 8) & ~0x01;
    bottom = (bottom / 8) | 0x01;

    /* BMP FORMAT -> LCD FORMAT */
    offset0 = BYTESPERLINE * 7;
    for (i = top; i <= bottom; i++) {
        for (j = left; j <= right; j++) {
            idx = i * BYTESPERLINE * 8 + j;
            for (k = 0; k < 8; k++) {
                mask = 0x0080 >> k;
                for (ch = 0, offset = offset0; offset >= 0; offset -= BYTESPERLINE) {
                    ch = (ch << 1) | ((LcdBmpBuf[idx + offset] & mask) ? 1 : 0);
                }
                LcdDispBuf[i * 16 * 8 + j * 8 + k] = ch;
            }
        }
    }

    if (iMode) return;

    top /= 2;
    bottom /= 2;
    GRA_LOAD(&LcdDispBuf[256 * top], top, bottom - top + 1);
    /*GRA_LOAD(&LcdDispBuf[0], 0, 4);
     */
#endif

    return 0;
}

void SetTextPosA(int x, int y, int iFont) {
    if (iFont == -1) iFont = iCurFontIdx;
    if (!FontInfo[iFont].iValid) return;
    FontInfo[iFont].xPos = x;
    FontInfo[iFont].yPos = y;
}

void GetLcdTextPosA(int *x, int *y, int iFont) {
    if (iFont == -1) iFont = iCurFontIdx;
    if (!FontInfo[iFont].iValid) return;
    *x = FontInfo[iFont].xPos;
    *y = FontInfo[iFont].yPos;
}

void GetLcdTextMetricsA(int *iRow, int *iCol, int iFont) {
    if (iFont == -1) iFont = iCurFontIdx;
    if (!FontInfo[iFont].iValid) return;
    *iRow = FontInfo[iFont].iRow;
    *iCol = FontInfo[iFont].iCol;
}

int LcdTextOutA(int x, int y, char *pStr, int iFontAttr, int iFont, int iRedraw) {
    int i, len, iOffset, iBound;

    if (iFont == -1) iFont = iCurFontIdx;
    if (!FontInfo[iFont].iValid) return 0;
    iOffset = x + y * FontInfo[iFont].iCol;
    iBound = FontInfo[iFont].iRow * FontInfo[iFont].iCol;
    len = strlen(pStr);
    if (len > iBound - iOffset) len = iBound - iOffset;
    for (i = 0; i < len; i++, pStr++) {
        FontInfo[iFont].FntAttrBuf[iOffset + i] = FA_DIRTY | iFontAttr;
        FontInfo[iFont].FntCharBuf[iOffset + i] = *pStr;
    }
    if (iRedraw) LcdDisplay();

    return 0;
}

int SetLcdInvertA(int x, int y, int count, int iMode, int iFont, int iRedraw) {
    int i, iOffset, iBound;

    if (iFont == -1) iFont = iCurFontIdx;
    if (!FontInfo[iFont].iValid) return -1;
    iBound = FontInfo[iFont].iRow * FontInfo[iFont].iCol;
    iOffset = x + y * FontInfo[iFont].iCol;
    for (i = 0; i < count && iOffset < iBound; i++, iOffset++) {
        if (iMode == INV_SET) {
            FontInfo[iFont].FntAttrBuf[iOffset] |= FA_INVERT;
        } else {
            FontInfo[iFont].FntAttrBuf[iOffset] &= ~FA_INVERT;
        }
        FontInfo[iFont].FntAttrBuf[iOffset] |= FA_DIRTY;
    }
    if (iRedraw) LcdDisplay();

    return 0;
}

int SetLcdULineA(int x, int y, int count, int iMode, int iFont, int iRedraw) {
    int i, iOffset, iBound;

    if (iFont == -1) iFont = iCurFontIdx;
    if (!FontInfo[iFont].iValid) return -1;
    iBound = FontInfo[iFont].iRow * FontInfo[iFont].iCol;
    iOffset = x + y * FontInfo[iFont].iCol;
    for (i = 0; i < count && iOffset < iBound; i++, iOffset++) {
        if (iMode == ULINE_SET) {
            FontInfo[iFont].FntAttrBuf[iOffset] |= FA_UNDERLINE;
        } else {
            FontInfo[iFont].FntAttrBuf[iOffset] &= ~FA_UNDERLINE;
        }
        FontInfo[iFont].FntAttrBuf[iOffset] |= FA_DIRTY;
    }
    if (iRedraw) LcdDisplay();

    return 0;
}

static void lcd_put_one_char(char c, void *dummy) {
    int i, iOffset, iBound;

    if (FontInfo[iCurFontIdx].xPos >= FontInfo[iCurFontIdx].iCol) {
        FontInfo[iCurFontIdx].xPos = 0;
        if (c == '\r') return;
        ++FontInfo[iCurFontIdx].yPos;
        if (c == '\n') return;
    }
    iOffset = FontInfo[iCurFontIdx].xPos + FontInfo[iCurFontIdx].yPos * FontInfo[iCurFontIdx].iCol;
    iBound = FontInfo[iCurFontIdx].iRow * FontInfo[iCurFontIdx].iCol;

    if (c == '\n' || c == '\r' || iOffset == iBound) {
        FontInfo[iCurFontIdx].xPos = 0;
        if (c == '\r') return;
        if (FontInfo[iCurFontIdx].yPos + 1 >= FontInfo[iCurFontIdx].iRow) {
            char TmpAttrBuf[1024];
            FontInfo[iCurFontIdx].yPos = FontInfo[iCurFontIdx].iRow - 1;
            for (i = 0; i < iBound; i++)
                if (FontInfo[iCurFontIdx].FntCharBuf[i] || FontInfo[iCurFontIdx].FntAttrBuf[i])
                    TmpAttrBuf[i] = FA_DIRTY;
            memcpy(FontInfo[iCurFontIdx].FntCharBuf, FontInfo[iCurFontIdx].FntCharBuf + FontInfo[iCurFontIdx].iCol, iBound - FontInfo[iCurFontIdx].iCol);
            memset(&FontInfo[iCurFontIdx].FntCharBuf[FontInfo[iCurFontIdx].yPos * FontInfo[iCurFontIdx].iCol], 0x00, FontInfo[iCurFontIdx].iCol);
            memcpy(FontInfo[iCurFontIdx].FntAttrBuf, FontInfo[iCurFontIdx].FntAttrBuf + FontInfo[iCurFontIdx].iCol, iBound - FontInfo[iCurFontIdx].iCol);
            memset(&FontInfo[iCurFontIdx].FntAttrBuf[FontInfo[iCurFontIdx].yPos * FontInfo[iCurFontIdx].iCol], 0x00, FontInfo[iCurFontIdx].iCol);
            for (i = 0; i < iBound; i++)
                if (FontInfo[iCurFontIdx].FntCharBuf[i] || FontInfo[iCurFontIdx].FntAttrBuf[i] || TmpAttrBuf[i])
                    FontInfo[iCurFontIdx].FntAttrBuf[i] |= FA_DIRTY;
        } else {
            FontInfo[iCurFontIdx].yPos += 1;
        }
        if (c == '\n') return;
        iOffset = FontInfo[iCurFontIdx].xPos + FontInfo[iCurFontIdx].yPos * FontInfo[iCurFontIdx].iCol;
    }

    FontInfo[iCurFontIdx].FntAttrBuf[iOffset] |= FA_DIRTY;
    FontInfo[iCurFontIdx].FntCharBuf[iOffset] = (U08) c;
    ++FontInfo[iCurFontIdx].xPos;
}

int lcd_putcharA(int c, int iRedraw) {
    lcd_put_one_char((char) c, NULL);
    if (iRedraw) LcdDisplay();

    return c;
}

int lcd_printf(const char *format, ...) {
    va_list ap;
    int i, nr_of_chars;
    char temp[128];

    va_start(ap, format); /* Variable argument begin */
    nr_of_chars = vsprintf(temp, format, ap);
    for (i = 0; i < nr_of_chars; i++)
        lcd_put_one_char((char) temp[i], NULL);
    va_end(ap); /* Variable argument end */

    return nr_of_chars; /* According to ANSI */
}

int lcd_printfA(const char *format, ...) {
    va_list ap;
    int i, nr_of_chars;
    char temp[128];

    va_start(ap, format); /* Variable argument begin */
    nr_of_chars = vsprintf(temp, format, ap);
    for (i = 0; i < nr_of_chars; i++)
        lcd_put_one_char((char) temp[i], NULL);
    va_end(ap); /* Variable argument end */
    LcdDisplay();

    return nr_of_chars; /* According to ANSI */
}

/* --------------------------------------------------
                                GRAPHIC FUNCTION
   -------------------------------------------------- */

static void SwapInt(int* pa, int* pb) {
    int t = *pa;
    *pa = *pb;
    *pb = t;
}

void LcdDrawPixelA(int x, int y, int mode, int iRedraw) {
    if (mode) {
        GraphicBuf[y * BYTESPERLINE + (x >> 3)] |= 0x01 << (7 - (x & 0x07));
    } else {
        GraphicBuf[y * BYTESPERLINE + (x >> 3)] &= ~(0x01 << (7 - (x & 0x07)));
    }

    if (iRedraw) LcdDisplay();
}

int GetLcdPixel(int x, int y) {
    return (GraphicBuf[y * BYTESPERLINE + (x >> 3)] & (0x01 << (7 - (x & 0x07)))) ? 1 : 0;
}

void LcdDrawLineA(int x0, int y0, int x1, int y1, int iRedraw) {
    int xdiff = x1 - x0;
    int ydiff = y1 - y0;
    int xdiffby2;
    int i;
    char Swapped = 0;

    /* check if no line */
    if (!(xdiff | ydiff)) {
        LcdDrawPixel(x0, y0);
        return;
    }
    /* check if we swap x and y for calculation */
    if (abs(xdiff) < abs(ydiff)) {
        SwapInt(&xdiff, &ydiff);
        SwapInt(&x0, &y0);
        SwapInt(&x1, &y1);
        Swapped = 1;
    }
    /* make sure line direction is positive */
    if (xdiff != abs(xdiff)) {
        xdiff = -xdiff;
        ydiff = -ydiff;
        SwapInt(&x0, &x1);
        SwapInt(&y0, &y1);
    }
    xdiffby2 = xdiff / 2;
    if (ydiff < 0)
        xdiffby2 = -xdiffby2;
    /* Draw pixel by pixel solid */
    for (i = 0; i <= xdiff; i++) {
        long l = ((long) ydiff) * i + xdiffby2;
        int y = (abs(l) < 32767) ? (y0 + ((int) l) / xdiff) : (y0 + l / xdiff);
        if (!Swapped)
            LcdDrawPixel(x0 + i, y);
        else
            LcdDrawPixel(y, x0 + i);
    }
    if (iRedraw) LcdDisplay();
}

void LcdDrawRectA(int x0, int y0, int x1, int y1, int iRedraw) {
    LcdDrawLine(x0, y0, x1, y0);
    LcdDrawLine(x1, y0, x1, y1);
    LcdDrawLine(x1, y1, x0, y1);
    LcdDrawLine(x0, y1, x0, y0);
    if (iRedraw) LcdDisplay();
}

static void Draw8Point(int x0, int y0, int xoff, int yoff) {
    LcdDrawPixel(x0 + xoff, y0 + yoff);
    LcdDrawPixel(x0 - xoff, y0 + yoff);
    LcdDrawPixel(x0 + yoff, y0 + xoff);
    LcdDrawPixel(x0 + yoff, y0 - xoff);
    if (yoff) {
        LcdDrawPixel(x0 + xoff, y0 - yoff);
        LcdDrawPixel(x0 - xoff, y0 - yoff);
        LcdDrawPixel(x0 - yoff, y0 + xoff);
        LcdDrawPixel(x0 - yoff, y0 - xoff);
    }
}

void LcdDrawCircleA(int x0, int y0, int r, int iRedraw) {
    long i;
    int imax = ((long) ((long) r * 707)) / 1000 + 1;
    long sqmax = (long) r * (long) r + (long) r / 2;
    long y = r;
    Draw8Point(x0, y0, r, 0);
    for (i = 1; i <= imax; i++) {
        if ((i * i + y * y) > sqmax) {
            Draw8Point(x0, y0, i, y);
            y--;
        }
        Draw8Point(x0, y0, i, y);
    }
    if (iRedraw) LcdDisplay();
}

void LcdDrawEllipseA(int x0, int y0, int rx, int ry, int iRedraw) {
    long OutConst, Sum, SumY;
    int x, y;
    int xOld;
    unsigned long _rx = rx;
    unsigned long _ry = ry;
    OutConst = _rx * _rx * _ry * _ry /* Constant as explaint above */
            + (_rx * _rx * _ry >> 1); /* To compensate for rounding */
    xOld = x = rx;
    for (y = 0; y <= ry; y++) {
        if (y == ry) {
            x = 0;
        } else {
            SumY = ((long) (rx * rx))*((long) (y * y)); /* Does not change in loop */
            while (Sum = SumY + ((long) (ry * ry))*((long) (x * x)),
                    (x > 0) && (Sum > OutConst)) x--;
        }
        /* Since we draw lines, we can not draw on the first
                iteration
         */
        if (y) {
            LcdDrawLine(x0 - xOld, y0 - y + 1, x0 - x, y0 - y);
            LcdDrawLine(x0 - xOld, y0 + y - 1, x0 - x, y0 + y);
            LcdDrawLine(x0 + xOld, y0 - y + 1, x0 + x, y0 - y);
            LcdDrawLine(x0 + xOld, y0 + y - 1, x0 + x, y0 + y);
        }
        xOld = x;
    }
    if (iRedraw) LcdDisplay();
}

int LcdDrawTextA(int x, int y, char *pStr, int iFontAttr, int iFont, int iRedraw) {
    int i, ch, xpos, ypos, len;

    if (iFont == -1) iFont = iCurFontIdx;
    if (!FontInfo[iFont].iValid) return 0;
    len = strlen(pStr);
    for (i = 0; i < len; i++) {
        ch = pStr[i] & 0xFF;
        if (ch < FontInfo[iFont].iFirstChar) continue;
        if (ch > FontInfo[iFont].iLastChar) {
            if (!FontInfo[iFont].iExtFntType) continue;
            if (!(ch & 0x80)) continue;
        }
        xpos = x + (i % FontInfo[iFont].iCol) * FontInfo[iFont].iWidth;
        ypos = y + (i / FontInfo[iFont].iCol) * FontInfo[iFont].iHeight;
        i += PutTextChar(xpos, ypos, &pStr[i], iFontAttr, iFont, LDB_GRAPHIC);
    }
    if (iRedraw) LcdDisplay();

    return len;
}

#if 0

typedef struct {
    int iGraCnt;
    int iScrWidth;
    int iScrHeight;
    char *pWorkBuf;
    char *pScrImg;
} SCRINFO;

static SCRINFO ScrInfo;

void SetScroll(int iScrWidth, int iScrHeight, char *pWorkBuf, char *pScrImg) {
    ScrInfo.iGraCnt = 0;
    ScrInfo.iScrWidth = ((iScrWidth + 31) / 32) * 32;
    ScrInfo.iScrHeight = iScrHeight;
    ScrInfo.pWorkBuf = pWorkBuf;
    ScrInfo.pScrImg = pScrImg;
}

const unsigned char ScrMask[9] = {
    0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF
};

void DrawScroll(int mode) {
    int i, j, byteoffset, bitoffset, iWidth;

    iWidth = ScrInfo.iScrWidth / 8;
    if (mode) ScrInfo.iGraCnt = 0;
    byteoffset = (ScrInfo.iGraCnt / 8) % 16;
    bitoffset = ScrInfo.iGraCnt % 8;
    for (i = 0; i < ScrInfo.iScrHeight; i++) {
        for (j = 0; j < iWidth; j++) {
            ScrInfo.pWorkBuf[i * 16 + j] = (ScrInfo.pScrImg[i * 16 + ((j + byteoffset) % 16)] << bitoffset) |
                    ((ScrInfo.pScrImg[i * 16 + ((j + 1 + byteoffset) % 16)] >> (8 - bitoffset)) & ScrMask[bitoffset]);
        }
    }

    ScrInfo.iGraCnt = ++ScrInfo.iGraCnt % ScrInfo.iScrWidth;
    LcdDrawBitmap(0, 0, 128, 32, (char *) ScrInfo.pWorkBuf, DBM_AND);
    LcdDisplay();
}
#endif
