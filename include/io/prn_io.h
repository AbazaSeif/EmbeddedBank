/*============================================================================
 *
 *      prn_io.h
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
 * Contributors:  
 * Date:          
 * Purpose:       
 * Description:
 * 
 *==========================================================================*/
#ifndef _PRN_IO_H_
#define _PRN_IO_H_ 

#include <io/devio.h>

/** @defgroup Thermal Printer 
 *  
 *  @{
 */
 
#define PRINTER_IOCTL_GET_NUM_DOT  0x1
#define PRINTER_IOCTL_STEP         0x2


/**
 * Initializes the printer.
 *
 * This function is called during the initialization process.
 *
 *
 * @return  0 if the operation is successful, non-null otherwise.
 *
 */
int prn_init( const char *name, io_handle_t *handle );


/**
 * Terminates the printer.
 *
 * This function is called during the termination process.
 *
 *
 * @return  0 if the operation is successful, non-null otherwise.
 *
 * @note     All the storages are closed when this function is called.
 * 
 */
int prn_shutdown( io_handle_t handle );




int prn_ioctl( io_handle_t handle, int command, void *param );

int prn_write( io_handle_t handle, unsigned char *data, int length );

int prn_puts( io_handle_t handle, char *str );


/** @} */
#endif  /* _PRN_IO_H_ */
