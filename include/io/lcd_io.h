/*============================================================================
 *
 *      lcd_io.h
 *
 *      
 *
 *==========================================================================*/
/*============================================================================
 * 
 * Copyright (c) 2002-2006 Innova Card.
 * All Rights Reserved.
 *
 * This software is the confidential and proprietary information of
 * Innova Card ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with Innova Card.
 *
 * Innova Card makes no representations or warranties about the suitability of 
 * the software, either express or implied, including but not limited to 
 * the implied warranties of merchantability, fitness for a particular purpose, 
 * or non-infrigement. Innova Card shall not be liable for any damages suffered 
 * by licensee as the result of using, modifying or distributing this software 
 * or its derivatives.
 * 
 *==========================================================================*/
/*============================================================================
 * 
 * Author(s):    Arnaud Corria 
 * Contributors:  Remy Fugier (Trusted Logic)
 * Date:          
 * Purpose:       
 * Description:
 * 
 *==========================================================================*/
#ifndef _LCD_IO_H_
#define _LCD_IO_H_	

#include <io/devio.h>

typedef struct {
  
  unsigned int value;
  unsigned int x;
  unsigned int y;
  
} lcd_pixel_t;

typedef struct {

  int length;
  unsigned char * pBuffer;
  
} lcd_buffer_t;

#define LCD_IOCTL_SET_POS   0
#define LCD_IOCTL_GET_POS   1
#define LCD_IOCTL_SET_PIXEL 2
#define LCD_IOCTL_GET_PIXEL 3
#define LCD_IOCTL_MOVETO    4
#define LCD_IOCTL_WRITE_BUFFER 5



/*-----------------------------------------------------------------------------
 * FUNCTIONS
 * ---------------------------------------------------------------------------*/

/* Basic initialization and error handling */
/*-----------------------------------------*/

/** 
 * The function initializes the display module.
 * 
 */
int lcd_init( const char *name, io_handle_t *handle );

/**
 * The function initializes display and output an error message at the center 
 * of the display.
 * 
 */
int lcd_puterr( const char *name, io_handle_t *handle, const char *msg );

/**
 * The function releases the display resources.
 * 
 */
int lcd_shutdown( io_handle_t *handle );

/**
 * The function turns off LCD screen
 * 
 */
int lcd_power_off( io_handle_t *handle );
    
/**
 * The function turns on LCD screen
 * 
 */
int lcd_power_on( io_handle_t *handle );

/* Basic text functions */
/*----------------------*/

/**
 * The function prints a string. 
 *
 */
int lcd_puts( io_handle_t handle, const char *str );

/**
 * The function prints a character. 
 *
 */
int lcd_putc( io_handle_t handle, const char c );

/**     
 * The function sets the cursor position in character coordinates.
 * 
 */
int lcd_set_pos( io_handle_t handle, int pos );

/**     
 * The function gets the cursor position in character coordinates.
 * 
 */
int lcd_get_pos( io_handle_t handle, int *pos );

/* Basic graphic functions */
/*-------------------------*/

/**     
 * The function writes a pixel.
 * 
 */
int lcd_set_pixel( io_handle_t handle, int x, int y );

/**     
 * The function clears a pixel.
 * 
 */
int lcd_clear_pixel( io_handle_t handle, int x, int y );

/**     
 * The function reads a pixel.
 * 
 */
int lcd_get_pixel( io_handle_t handle, int x, int y );

/**
 * The function writes a bitmap.
 *
 */
int lcd_write(  io_handle_t handle, unsigned char *pBuffer, int length);

#endif  /* _LCD_IO_H_ */
	

