
/*======================================================================*/
/*																		*/
/*									UNZIP.H								*/
/*																		*/
/*======================================================================*/

#ifndef UNZIP_H
#define UNZIP_H

#ifdef __cplusplus
extern "C" {
#endif


extern long Decompress(long compress_len, char *compress_data, unsigned char *uncompress_data, long uncompress_len, char disp_line);

extern void Unzip_SetFlashSectorSize(long sector_size);


#ifdef __cplusplus
}
#endif

#endif	/* UNZIP_H */

/* */
