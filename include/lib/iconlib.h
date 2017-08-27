
/*======================================================================*/
/*																		*/
/*								ICONLIB.H								*/
/*																		*/
/*======================================================================*/

#ifndef ICONLIB_H
#define ICONLIB_H

#ifdef __cplusplus
extern "C" {
#endif


extern const char ANTENNA_ICON_BMP[][2*16];

extern void DisplayGraphics(char start_ypos, char start_xpos, char line_cnt, char x_cnt, char *image);

extern void DisplayAntennaIcon(char *stream);

extern void DisplaySimGprsIcon(int iSimFlag, int iGprsFlag);

extern void DisplayProcessingBar(char line, int percentage);

extern void DisplayInitialImage();

#ifdef __cplusplus
}
#endif

#endif	/* ICONLIB_H */

/* */
