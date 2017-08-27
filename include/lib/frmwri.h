
/*======================================================================*/
/*																		*/
/*								FRMWRI.H								*/
/*																		*/
/*======================================================================*/

#ifndef FRMWRI_H
#define FRMWRI_H

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------*/
/*                                                                      */
/*                        - _formatted_write -                          */
/*                                                                      */
/* This routine forms the core and entry of the formatter.  The con-    */
/* version performed conforms to the ANSI specification for "printf".   */
/*----------------------------------------------------------------------*/
extern int _formatted_write(const char *format, void put_one_char(char, void *),
							void *secret_pointer, va_list ap);


#ifdef __cplusplus
}
#endif

#endif	/* FRMWRI_H */

/* */
