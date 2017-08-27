/*============================================================================
 *
 *      hal_parallel.h
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
 * Author(s):    Arnaud Ferir 
 * Contributors:  
 * Date:          
 * Purpose:       
 * Description:  HAL for SPP (IEEE1284 Parallel Port) 
 * 
 *==========================================================================*/
#ifndef HAL_USIP_PARALLEL_H
#define HAL_USIP_PARALLEL_H


/**
 *  
 * @defgroup HAL_SPP HAL Parallel Interface
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the Standard Parallel Port (SPP). 
 *  
 * @section hal_parallel Overview 
 * 
 * USIP® Professional provides a parallel interface that supports the 
 * compatibility, nibble and byte mode according to the IEEE 1284 standard. It 
 * also supports device ID requests. 
 * 
 * @warning The SPP resources are shared with the @link HAL_GPIO GPIOs @endlink 
 * interface. When the GPIO [8..15] are in use, the parallel port is busy and 
 * its initialization fail. 
 * 
 * @warning The SPP resources are shared with the @link HAL_PRN Thermal Printer 
 * @endlink interface. When the Thermal Printer is in use, the parallel port is 
 * busy and its initialization fail. 
 * 
 * <b> Forward transfer mode </b>
 * 
 * The Compatibility mode is the forward communication mode and supports all 
 * Host-to-peripheral transfers (USIP Professional to Device). 
 * 
 * <b> Reverse transfer modes </b>
 * 
 * The reverse modes supports all Peripheral-to-host transfers (Device to USIP 
 * Professional). 
 * 
 * The parallel port provides two reverse commuynication modes: 
 * \li Nibble mode (This is the default reverse communication mode.)
 * \li Byte mode
 * 
 * <b> Device ID request </b>
 * 
 * The device identifier request is a way to identify the peripheral linked to 
 * the parallel port. When sent to the device this request gets a 
 * case-sensitive string of ASCII characters that specifies the device 
 * characteristics and/or its capabilities. 
 * 
 * The device identifier request uses the forward and reverse communication 
 * mode. The reverse transfer mode must then be chosen before sending a device 
 * identifier request.
 * 
 * \note The configuration of this module includes a time reference that is 
 * depending on the system clock frequency. This module should then be 
 * re-configured if the system clock frequency is changed (see \link HAL_APM 
 * Advanced Power Management \endlink). 
 * 
 * @addtogroup HAL_SPP
 * 
 * @{
 */
 
 
/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** Reverse Mode */
/** This configuration must be chosen to use nibble reverse mode */
#define HAL_PARALLEL_MODE_NIBBLE    1
/** This configuration must be chosen to use byte reverse mode */
#define HAL_PARALLEL_MODE_BYTE      2

/** State */
/** This state indicator is raised when a negociation phase fails  */
#define HAL_PARALLEL_STATUS_RX_NEG				0x0020
/** This state indicator is raised when the receive register is full and ready
 *  to be read */
#define HAL_PARALLEL_STATUS_RX_FULL				0x0010
/** This state indicator is raised when a new data is available for another
 *  reverse transfer from the peripheral */
#define HAL_PARALLEL_STATUS_RX_NW_DATA_AV		0x0008
/** This state indicator is raised when the parallel port is currently receiving
 *  or waiting for data */
#define HAL_PARALLEL_STATUS_RX_BUSY				0x0004
/** This state indicator is raised when the transmit register is empty */
#define HAL_PARALLEL_STATUS_TX_EMPTY			0x0002
/** This state indicator is raised when the parallel port is currently sending 
 *  data */
#define HAL_PARALLEL_STATUS_TX_BUSY				0x0001

/** Events */
/** This event indicator is raised when a data has been sent */
#define HAL_PARALLEL_EVENT_TX        0
/** This event indicator is raised at the end of a reverse tansfer when the
 *  negociation phase failed */
#define HAL_PARALLEL_EVENT_RX_ERROR  1
/** This event indicator is raised at the end of a reverse transfer when a data
 *  has been received */
#define HAL_PARALLEL_EVENT_RX_DATA   2
/** This event indicator is raised at the end of a reverse transfer when no data
 *  has been received (reverse idle state) */
#define HAL_PARALLEL_EVENT_RX_IDLE   3
/** This event indicator is raised in the reverse idle state when a new data is
 *  available */
#define HAL_PARALLEL_EVENT_RX_NEW    4


/*------------------------------------------------------------------------------
   Control Enumeration
*/

/** The control enumeration defines the type of control on the parallel port
 */
typedef enum {
	/** Start a reverse transfer (nibble or byte mode) */
	HAL_PARALLEL_IOCTL_RX_RD = 1,
	/** Set device ID request bit */
	HAL_PARALLEL_IOCTL_SET_DEVICE_ID_REQ,
	/** Clear device ID request bit */
	HAL_PARALLEL_IOCTL_CLEAR_DEVICE_ID_REQ

} HAL_PARALLEL_CONTROL ;


/*----------------------------------------------------------------------------
 * Configuration Structure
 */
     
/** The configuration structure is used to set up the Parallel Interface */
typedef struct HAL_PARALLEL_CONFIG {
  
    /** Parallel reverse channel mode, two modes are available:
     *  \li Nibble mode (#HAL_PARALLEL_MODE_NIBBLE) 
     *  \li Byte mode (#HAL_PARALLEL_MODE_BYTE) */
    unsigned int mode;    

//    /** Parallel cycle number of PCLK
//     *  It provides the cycle number of PCLK clock to achieve a while of 0.5 µs.
//     *  It is a 6-bits wide register. */
//    unsigned int rts_clock;

} HAL_PARALLEL_CONFIG; 


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures the parallel port. 
 * 
 * @warning The parallel port shares its clock and hardware reset with the 
 * GPIO, PS/2 and thermal printer interfaces. It is not actually reset nor 
 * activated if any of these interfaces is already in use. 
 * 
 * @param[in] pparams       A pointer on a parallel parameters structure 
 *                          allocated and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_BUSY        Resource busy. Shared resources are already in use. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_parallel_init( HAL_PARALLEL_CONFIG *pparams );


/**
 * The function disables the parallel port. 
 * 
 * @warning The parallel port shares its clock and hardware reset with the 
 * GPIO, PS/2 and thermal printer interfaces. It is not actually disabled 
 * if any of these interfaces is still in use. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_parallel_shutdown( void );


/**
 * The function configures the parallel port. The configuration is contained 
 * into a dedicated structure. 
 *
 * @param[in] pparams       A pointer on a parallel parameters structure 
 *                          allocated and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_parallel_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_parallel_set_config( HAL_PARALLEL_CONFIG *pparams );


/**
 * The function performs a specific control on the parallel port.
 * 
 * @param[in] control  		The control to be performed. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_parallel_init() 
 *                          first. 
 * @retval -ERR_AGAIN       Try again later 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_parallel_ioctl( HAL_PARALLEL_CONTROL control);


/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_PARALLEL_EVENT_TX 
 *                          \li #HAL_PARALLEL_EVENT_RX_ERROR 
 *                          \li #HAL_PARALLEL_EVENT_RX_DATA 
 *                          \li #HAL_PARALLEL_EVENT_RX_IDLE 
 *                          \li #HAL_PARALLEL_EVENT_RX_NEW 
 * 
 * @param[in] handler       Pointer to the interrupt handler function. 
 *                          Its declaration should support the parameters: 
 *                          \li \e event Occured event 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_parallel_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_parallel_attach( int event, void (*handler)(int event));


/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_PARALLEL_EVENT_TX 
 *                          \li #HAL_PARALLEL_EVENT_RX_ERROR 
 *                          \li #HAL_PARALLEL_EVENT_RX_DATA 
 *                          \li #HAL_PARALLEL_EVENT_RX_IDLE 
 *                          \li #HAL_PARALLEL_EVENT_RX_NEW 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_parallel_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_parallel_detach( int event);


/**
 * The function is used to retrieve the status of the parallel port. 
 * 
 * @param[out] pstatus      A pointer on a variable allocated by the caller and 
 *                          filled by the function with the status of parallel
 *                          port. It's one or a combination of the following
 *                          values :
 *                          \li #HAL_PARALLEL_STATUS_RX_NEG
 *                          \li #HAL_PARALLEL_STATUS_RX_FULL
 *                          \li #HAL_PARALLEL_STATUS_RX_NW_DATA_AV
 *                          \li #HAL_PARALLEL_STATUS_RX_BUSY
 *                          \li #HAL_PARALLEL_STATUS_TX_EMPTY
 *                          \li #HAL_PARALLEL_STATUS_TX_BUSY
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_parallel_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */   
int hal_parallel_get_status( unsigned int *pstatus );


/**
 * The function is used to read the parallel port.
 * 
 * @param[in] data          A pointer on a variable allocated by the caller and 
 *                          filled by the function with the read data. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_parallel_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */                                
int hal_parallel_read( unsigned char *data );


/**
 * The function is used to write into the parallel port. 
 * 
 * @param[in] data          The data to send. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_parallel_init() 
 *                          first. 
 * @retval -ERR_AGAIN       Try again later 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_parallel_write( unsigned char data );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_parallel_handler_t)(int event);

__hal_defunc1(hal_parallel_init, HAL_PARALLEL_CONFIG *, params);
__hal_defunc0(hal_parallel_shutdown, void);
__hal_defunc1(hal_parallel_set_config, HAL_PARALLEL_CONFIG *, params);
__hal_defunc1(hal_parallel_ioctl, HAL_PARALLEL_CONTROL, control);
__hal_defunc2(hal_parallel_attach, int, event, hal_parallel_handler_t, handler);
__hal_defunc1(hal_parallel_detach, int, event);
__hal_defunc1(hal_parallel_get_status, unsigned int *, status);
__hal_defunc1(hal_parallel_read, unsigned char *, data);
__hal_defunc1(hal_parallel_write, unsigned char, data);

__hal_deisr(hal_parallel_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/**  @} */

#endif /* HAL_USIP_PARALLEL_H */

