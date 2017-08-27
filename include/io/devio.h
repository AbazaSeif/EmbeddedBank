/*============================================================================
 *
 *      devio.h
 *
 *      Device I/O
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
 * Description:   Describe low level I/O interfaces.  
 * 
 *==========================================================================*/
#ifndef _IO_DEVIO_H_
#define _IO_DEVIO_H_

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *io_handle_t;

void io_init(void);

// Lookup a device and return it's handle
int io_lookup(const char *name, 
                        io_handle_t *handle);
                        
                        
int io_ioctl(io_handle_t handle, unsigned int cmd, void *data);

// Write data to a device
int io_write(io_handle_t handle, 
                       const void *buf, 
                       unsigned int *len);
// Read data from a device
int io_read(io_handle_t handle, 
                      void *buf, 
                      unsigned int *len);
// Write data to a block device
int io_bwrite(io_handle_t handle, 
                       const void *buf, 
                       unsigned int *len,
                       unsigned int pos);
// Read data from a block device
int io_bread(io_handle_t handle, 
                      void *buf, 
                      unsigned int *len,
                      unsigned int pos);
// Get the configuration of a device
int io_get_config(io_handle_t handle, 
                            unsigned int key,
                            void *buf, 
                            unsigned int *len);
// Change the configuration of a device
int io_set_config(io_handle_t handle, 
                            unsigned int key,
                            const void *buf, 
                            unsigned int *len);
// Test a device for readiness    
int io_select(io_handle_t handle,
                       unsigned int which,
                       unsigned int info);

#ifdef __cplusplus
}
#endif

#endif  /* _IO_DEVIO_H_ */

