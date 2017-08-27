/*============================================================================
 *
 *      hal_storage.h
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
#ifndef HAL_USIP_STORAGE_H
#define HAL_USIP_STORAGE_H

   
/**
 *  
 * @defgroup HAL_STO HAL Security Storage
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the security storage module. 
 * 
 * @section Overview Overview 
 * 
 * USIP® Professional provides a set of 16 secured 32-bits registers known as 
 * Battery-Powered Keys.
 * 
 * The Battery-Powered Keys are powered by the power supply used for the RTC 
 * operation. They are connected to the security sensors and then automatically 
 * erased when any attack is detected. 
 * 
 * Due to their design the Battery-Powered Keys are recommended for the 
 * cryptographic AES key storage. 
 * 
 * \b Features 
 * 
 * \li Volatile memory area safe powered 
 * \li Protected by USIP® Professional security mechanisms 
 * 
 * \warning The Battery-Powered Keys and the USIP® Professional core work in 
 * different clock domains. The read and write operations in registers of this 
 * module may be temporarily locked. 
 * 
 * @addtogroup HAL_STO
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/** 
 * This function reads byte data from the Security Storage Memory. 
 *
 * @param[out] data         Pointer on a array allocated by the caller and 
 *                          filled by the function with the read data. 
 * 
 * @param[in] offset        Data offset (bytes) from the base address of the 
 *                          Security Storage Memory. 
 * 
 * @param[in] size          Data size (bytes). 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_storage_read( unsigned char *data, int offset, int size );

/** 
 * This function writes byte data to the Security Storage Memory. 
 *
 * @param[in] data          Pointer on a array allocated and filled by the 
 *                          caller with the data to be written. 
 * 
 * @param[in] offset        Data offset (bytes) from the base address of the 
 *                          Security Storage Memory. 
 * 
 * @param[in] size          Data size (bytes). 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_storage_write( unsigned char *data, int offset, int size );

#else

#include <hal/usip/hal_sys.h>

__hal_defunc3(hal_storage_write, unsigned char *, data, int, offset, int, size);
__hal_defunc3(hal_storage_read, unsigned char *, data, int, offset, int, size);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* HAL_USIP_STORAGE_H */

