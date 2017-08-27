/*============================================================================
 *
 *      kdb_io.h
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
 * Author(s):     Arnaud Corria 
 * Contributors:  
 * Date:          
 * Purpose:       
 * Description:    
 * 
 *==========================================================================*/
#ifndef _KBD_IO_H_
#define _KBD_IO_H_	

#include <io/devio.h>

int kbd_init( const unsigned char *name, io_handle_t *handle );
int kbd_read( io_handle_t handle, unsigned short *key );


#endif  /* _KBD_IO_H_ */
	

