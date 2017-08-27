/*============================================================================
 *
 *      hal_msr.h
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
 * Description:  This file contains the Magnetic Stripe Reader Interface 
 *               generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_MSR_H
#define HAL_USIP_MSR_H

/**
 *  
 * @defgroup HAL_MSR HAL Magnetic Stripe Reader (MSR).
 * 
 * This chapter contains descriptions of the configuration structure, 
 * and functions available to access the Magnetic Stripe Reader Interface.
 *
 * @section Overview Overview 
 * 
 * USIP® Professional provides 3 magnetic head interfaces, that can retrieve 
 * data from magnetic stripe cards according to the ISO 7811 standard. They are 
 * designed to read any track encoded using an F/2F recording technique. 
 * 
 * @section Usage Usage  
 * 
 * Data may be read from a 32-bit register: 
 * \li when a 32-bits data is ready, 
 * \li when a end of acquisition was detected: less than 32 bits of data are ready 
 * (the data are right-aligned). 
 * 
 * These events may be detected by polling or interrupt. 
 * 
 * \warning If some ready data are not read before the next data are ready, the 
 * first data are lost. 
 * 
 * @addtogroup HAL_MSR
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** This state indicator is raised when a data is ready and the end of the 
 *  acquisition was detected */ 
#define HAL_MSR_STATUS_DATA_EOA             0x01
/** This state indicator is raised when a data is ready */ 
#define HAL_MSR_STATUS_DATA_READY           0x02

/** This event indicator is raised when a data is ready and the end of the 
 *  acquisition was detected */ 
#define HAL_MSR_EVENT_DATA_EOA              0x00
/** This event indicator is raised when a data is ready */ 
#define HAL_MSR_EVENT_DATA_READY            0x01

/*----------------------------------------------------------------------------
 * Device Enumeration
 */

/** The device enumeration defines the MSR heads */
typedef enum hal_msr_devices
{
    /** Identifier of the MSR 0 */
    hal_msr_dev0 = 0,
    /** Identifier of the MSR 1 */
    hal_msr_dev1,
    /** Identifier of the MSR 2 */
    hal_msr_dev2,
    /** Max. number of MSR devices */
    hal_msr_devices_count
    
} hal_msr_devices; 


/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes a Magnetic Stripe device. 
 *
 * @param[in] devnum        The MSR Interface identifier (#hal_msr_devices 
 *                          gives a list of all MSR device identifiers) 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_msr_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_msr_init( int devnum );

/**
 * The function terminates the use of a particular Magnetic Stripe device. 
 *
 * @param[in] devnum        The MSR Interface identifier (#hal_msr_devices 
 *                          gives a list of all MSR device identifiers) 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_msr_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_msr_shutdown( int devnum );

/**
 * This function is used to retrieve the state of Magnetic Stripe device. 
 *
 * @param[in] devnum        The MSR Interface identifier (#hal_msr_devices 
 *                          gives a list of all MSR device identifiers) 
 * 
 * @param[out] status       Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current status of 
 *                          the requested MSR device. It is an orred 
 *                          combination of the following values: 
 *                          \li #HAL_MSR_STATUS_DATA_READY 
 *                          \li #HAL_MSR_STATUS_DATA_EOA 
 *                      
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_msr_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_msr_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_msr_get_status( int devnum, int *status );

/**
 * The function is used to read a data received from a Magnetic Stripe Reader. 
 *
 * @param[in] devnum        The MSR Interface identifier (#hal_msr_devices 
 *                          gives a list of all MSR device identifiers) 
 * 
 * @param[out] data         Pointer on a variable allocated by the caller and 
 *                          filled by the function with the read data. 
 *
 * @param[out] bits         Pointer on a variable allocated by the caller and 
 *                          filled by the function with the number of avalaible 
 *                          read bits.
 *                      
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_msr_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_msr_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later. No data available. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_msr_read( int devnum, unsigned int *data, unsigned int *bits );


/**
 * The function performs Magnetic Stripe Interface specific control functions.
 *
 * @param[in] devnum        The MSR Interface identifier (#hal_msr_devices 
 *                          gives a list of all MSR device identifiers) 
 * 
 * @param[in] cmd           Requested control function. 
 * 
 * @param[in,out] data      Pointer on a variable allocated by the caller that 
 *                          contains any data required for the given control 
 *                          function or receives data from that function. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_msr_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_msr_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_msr_ioctl( int devnum, int cmd, void *data );


/**
 * The function registers an interrupt handler for a type of event. 
 * 
 * @param[in] devnum        The MSR Interface identifier (#hal_msr_devices 
 *                          gives a list of all MSR device identifiers) 
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_MSR_EVENT_DATA_READY 
 *                          \li #HAL_MSR_EVENT_DATA_EOA 
 * 
 * @param[in] handler       Pointer on the interrupt handler function. 
 *                          Its declaration should support the parameters:
 *                          \li \e devnum Device identifier
 *                          \li \e event Occured event
 * 
 * @retval positive         No error. Address of previous handler. 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_msr_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_msr_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_msr_attach( int devnum, int event, 
                    void (*handler)(int devnum, int event) );

/**
 * The function unregisters an interrupt handler that is used to process a 
 * particular event. 
 * 
 * @param[in] devnum        The MSR Interface identifier (#hal_msr_devices 
 *                          gives a list of all MSR device identifiers) 
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_MSR_EVENT_DATA_READY 
 *                          \li #HAL_MSR_EVENT_DATA_EOA 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_msr_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_msr_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_ALREADY     Operation already in progress
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_msr_detach( int devnum, int event );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_msr_handler_t)(int devnum, int event);

__hal_defunc1(hal_msr_init, int, devnum);
__hal_defunc1(hal_msr_shutdown, int, devnum);
__hal_defunc2(hal_msr_get_status, int, devnum, int *, status);
__hal_defunc3(hal_msr_read, int, devnum, unsigned int *, data, unsigned int *, bits);
__hal_defunc3(hal_msr_attach, int, devnum, int, event, hal_msr_handler_t, handler);
__hal_defunc2(hal_msr_detach, int, devnum, int, event);

__hal_deisr(hal_msr_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

/**  @} */

#ifdef __cplusplus
}
#endif

#endif  /* HAL_USIP_MSR_H */

