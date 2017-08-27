/*============================================================================
 *
 *      hal_rng.h
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
#ifndef HAL_USIP_RNG_H
#define HAL_USIP_RNG_H
  
/**
 *  
 * @defgroup HAL_RNG HAL True Random Number Generator
 * This chapter contains descriptions of the functions available to access 
 * the True Random Number Generator (RNG).
 * 
 * @section Overview Overview 
 * 
 * USIP® Professional provides a True Random Number generator that generates 
 * 32-bit Random Numbers that can be used for keys generation. 
 * 
 * This module is optimized to provide a 128-bit Random Number in only four 
 * clock periods. 
 * 
 * \b Features
 * 
 * \li Generate up to 4 32-bits random numbers in only 4 clock period. 
 * \li Interrupt 
 * 
 * @addtogroup HAL_RNG
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** 
 * This status indicator is raised when the RNG register is ready to be read at 
 * least once. 
 */
#define HAL_RNG_STATUS_ONE_RANDOM_READY     (1<<5)

/** 
 * This state indicator is raised when the RNG register is ready to be read 
 * four consecutive times. 
 */
#define HAL_RNG_STATUS_FOUR_RANDOMS_READY   (1<<4)

 
/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes the use of the True Random Number Generator.
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_init( void );

/**
 * The function shutdowns the True Random Number Generator.
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_shutdown( void );

/** 
 * The function provides the current state of the True Random Number Generator.
 * 
 * @param[out] status       Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the True Random Number Generator. It is an orred 
 *                          combination of the following state indicators: 
 *                          \li #HAL_RNG_STATUS_ONE_RANDOM_READY
 *                          \li #HAL_RNG_STATUS_FOUR_RANDOMS_READY
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rng_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_get_status( unsigned int *status );

/** 
 * This function reads a 32-bit random number from the True Random Number 
 * Generator. 
 *
 * @param[in] rand32        Pointer on a variable allocated by the caller and 
 *                          filled by the function with a random number. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rng_init() first. 
 * @retval -ERR_INVAL       Invalid parameter  
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_read( unsigned int *rand32 );

/** 
 * This function reads a 128-bit random number from the True Random Number 
 * Generator. 
 *
 * @param[in] rand128       Pointer on a variable allocated by the caller and 
 *                          filled by the function with a random number. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rng_init() first. 
 * @retval -ERR_INVAL       Invalid parameter  
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_read128( unsigned int *rand128 );

/**
 * The function performs a True Random Number Generator specific control 
 * function.
 * 
 * @param[in] cmd           Requested control function.
 * 
 * @param[in,out] data      Pointer on a buffer allocated by the caller and 
 *                          filled by the caller with any data required for the 
 *                          given control, or filled with data recovered from 
 *                          that control function. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rng_init() first. 
 * @retval -ERR_NOTTY       Inappropriate ioctl for device 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_ioctl( int cmd, void *data );

/**
 * The function registers an interrupt handler for the event raised when 
 * the generator is ready to be read four consecutive times.
 * 
 * @param[in] handler   Pointer to the interrupt handler function.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rng_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_attach( void (*handler)(void) );

/**
 * The function unregisters the interrupt handler for the event raised when 
 * the generator is ready to be read four consecutive times.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rng_init() first. 
 * @retval -ERR_ALREADY     Operation already in progress 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rng_detach( void );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_rng_handler_t)(void);

__hal_defunc0(hal_rng_init, void);
__hal_defunc0(hal_rng_shutdown, void);
__hal_defunc1(hal_rng_get_status, unsigned int *, status);
__hal_defunc1(hal_rng_read, unsigned int *, rand32);
__hal_defunc1(hal_rng_read128, unsigned int *, rand128);
__hal_defunc1(hal_rng_attach, hal_rng_handler_t, handler);
__hal_defunc0(hal_rng_detach, void);

__hal_deisr(hal_rng_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* HAL_USIP_RNG_H */

