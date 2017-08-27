/*============================================================================
 *
 *      hal_ps2.h
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
 * Contributors:  Arnaud Ferir
 * Date:          
 * Purpose:       
 * Description:   This file contains the PS/2 port generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_PS2_H
#define HAL_USIP_PS2_H


/**
 *  
 * @defgroup HAL_PS2 HAL PS/2 Interface
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the PS/2 interface. 
 * 
 * @section hal_ps2 Overview 
 * 
 * USIP® Professional provides one PS/2 port. This interface is IBM PS/2 or 
 * AT-compatible.
 * 
 * The PS/2 port is a half-duplex bidirectional synchronous serial interface 
 * that may be used to transfer data between a host CPU and a peripheral such 
 * as a keyboard or a mouse. The USIP® Professional PS/2 port can be configured 
 * either as a host side or as a peripheral side. 
 * 
 * \note The PS/2 clock half period configuration is depending on the system 
 * clock frequency. This module should be re-configured if the system clock 
 * frequency is changed (see \link HAL_APM Advanced Power Management \endlink). 
 * 
 * @warning The PS/2 Interface resources are partially shared with the @link 
 * HAL_PRN Thermal Printer Interface @endlink. When more than 6 IO are used for 
 * the stepper motor of the thermal printer interface, the PS/2 interface is 
 * busy and its initialization fails. 
 * 
 * @addtogroup HAL_PS2
 * 
 * @{
 */
 
 
/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** mode */
/** This setting is used to configure the module as a PS/2 Host */ 
#define HAL_PS2_MODE_HOST    0 
/** This setting is used to configure the module as a PS/2 Device */ 
#define HAL_PS2_MODE_DEVICE  1


/** state */
/** This state indicator is raised when the peripheral did not respond with an
 *  acknowledge at the end of the transmit transfer (PS/2 configured as host) */
#define HAL_PS2_H_STATUS_TXERROR      (1<<0)
/** This state indicator is raised when the PS/2 module is sending data
 *  (PS/2 configured as host) */
#define HAL_PS2_H_STATUS_TXBUSY       (1<<1)
/** This state indicator is raised when the transmit register is empty
 *  (PS/2 configured as host) */
#define HAL_PS2_H_STATUS_TXEMPTY      (1<<2)
/** This state indicator reflects the parity bit for the last received data
 *  byte (odd parity, PS/2 configured as host) */
#define HAL_PS2_H_STATUS_RXPARITY     (1<<3)
/** This state indicator is raised when the PS/2 module is receiving data
 *  (PS/2 configured as host) */
#define HAL_PS2_H_STATUS_RXBUSY       (1<<4)
/** This state indicator is raised when the receive register is full
 *  (PS/2 configured as host) */
#define HAL_PS2_H_STATUS_RXFULL       (1<<5)

/** This state indicator is raised when the host inhibits the peripheral from
 *  sending data during the transfer (PS/2 configured as device) */
#define HAL_PS2_D_STATUS_TXABORT      (1<<0)
/** This state indicator is raised when the PS/2 module is sending data
 *  (PS/2 configured as device) */
#define HAL_PS2_D_STATUS_TXBUSY       (1<<1)
/** This state indicator is raised when the transmit register is empty
 *  (PS/2 configured as device) */
#define HAL_PS2_D_STATUS_TXEMPTY      (1<<2)
/** This state indicator is raised when the stop bit was not detected
 *  (PS/2 configured as device) */
#define HAL_PS2_D_STATUS_RXSEND       (1<<3)
/** This status indicator reflects the parity bit for the last received data
 *  byte (odd parity, PS/2 configured as device) */
#define HAL_PS2_D_STATUS_RXPARITY     (1<<4)
/** This state indicator is raised when the PS/2 module is receiving data
 *  (PS/2 configured as device) */
#define HAL_PS2_D_STATUS_RXBUSY       (1<<5)
/** This state indicator is raised when the receive register is full
 *  (PS/2 configured as device) */
#define HAL_PS2_D_STATUS_RXFULL       (1<<6)


/* events */
/** This event indicator is raised when a data has been transmitted */
#define HAL_PS2_EVENT_TX        0
/** This event indicator is raised at the end of transmit transfer 
 *  when the peripheral doesn’t respond with a acknowledge (host side) 
 *  or when the host inhibits the peripheral from sending data (device side) */
#define HAL_PS2_EVENT_TXERROR   1
/** This event indicator is raised when a data has been received */
#define HAL_PS2_EVENT_RX        2
/** This event indicator is raised when the module has not detected the stop
 *  bit (It should only appear when configured as device) */
#define HAL_PS2_EVENT_RXSEND    3


/*----------------------------------------------------------------------------
 * Configuration Structure
 */
     
/** The configuration structure is used to set up the PS/2 port */
typedef struct HAL_PS2_CONFIG 
{
    /** Specify the PS/2 mode: Host (#HAL_PS2_MODE_HOST) or Device 
     *  (#HAL_PS2_MODE_DEVICE) */
    unsigned int mode;  

} HAL_PS2_CONFIG;


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures the PS/2 port. 
 *
 * @warning The PS/2 port shares its clock and hardware reset with the 
 * GPIOs, parallel and thermal printer interfaces. It is not actually reset nor 
 * activated if any of these interfaces is already in use. 
 * 
 * @param[in] pparams		A pointer on PS/2 parameters structure allocated and 
 *                          filled by the caller. 
 *                          
 * @retval -ERR_NO          No error 
 * @retval -ERR_BUSY        Resource busy. Shared resources are already in use. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_ps2_init( HAL_PS2_CONFIG *pparams );


/**
 * The function disables the PS/2 port. 
 * 
 * @warning The PS/2 port shares its clock and hardware reset with the 
 * GPIO, parallel and thermal printer interfaces. It is not actually disabled 
 * if any of these interfaces is still in use. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_ps2_shutdown( void );


/**
 * The function configures the PS/2 port. The configuration is contained into a 
 * dedicated structure. 
 *
 * @param[in] pparams       A pointer on PS/2 parameters structure allocated and 
 *                          filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_ps2_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_ps2_set_config( HAL_PS2_CONFIG *pparams );


/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_PS2_EVENT_RX 
 *                          \li #HAL_PS2_EVENT_RXSEND 
 *                          \li #HAL_PS2_EVENT_TX 
 *                          \li #HAL_PS2_EVENT_TXERROR 
 * 
 * @param[in] handler       Pointer to the interrupt handler function.
 *                          Its declaration should support the parameters:
 *                          \li \e event Occured event
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_ps2_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_ps2_attach( int event, void (*handler)(int event));


/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_PS2_EVENT_RX 
 *                          \li #HAL_PS2_EVENT_RXSEND 
 *                          \li #HAL_PS2_EVENT_TX 
 *                          \li #HAL_PS2_EVENT_TXERROR 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_ps2_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_ps2_detach( int event);


/**
 * The function is used to retrieve the status and interrupt state of PS/2 
 * module. 
 * 
 * @param[out] pstatus 		A pointer on a variable allocated by the caller and 
 *                          filled by the function with the status of PS/2 
 *                          module.
 *                          \n If PS/2 is configured as host, it's one or a
 *                          combination of the following values :
 *                          \li #HAL_PS2_H_STATUS_TXERROR
 *                          \li #HAL_PS2_H_STATUS_TXBUSY
 *                          \li #HAL_PS2_H_STATUS_TXEMPTY
 *                          \li #HAL_PS2_H_STATUS_RXPARITY
 *                          \li #HAL_PS2_H_STATUS_RXBUSY
 *                          \li #HAL_PS2_H_STATUS_RXFULL
 *                          \n If PS/2 is configured as device, it's one or a
 *                          combination of the following values :
 *                          \li #HAL_PS2_D_STATUS_TXABORT
 *                          \li #HAL_PS2_D_STATUS_TXBUSY
 *                          \li #HAL_PS2_D_STATUS_TXEMPTY
 *                          \li #HAL_PS2_D_STATUS_RXSEND
 *                          \li #HAL_PS2_D_STATUS_RXPARITY
 *                          \li #HAL_PS2_D_STATUS_RXBUSY
 *                          \li #HAL_PS2_D_STATUS_RXFULL
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_ps2_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */   
int hal_ps2_get_status( int *pstatus );


/**
 * The function is used to read the PS/2 port.
 * 
 * @param[in] data          A pointer allocated by the caller and filled by the 
 *                          function with the read data. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_ps2_init() first. 
 * @retval -ERR_AGAIN       Try again later 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_ps2_read( unsigned char *data );


/**
 * The function is used to write into the PS/2 port. 
 * 
 * @param[in] data          An data to be sent.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_ps2_init() first. 
 * @retval -ERR_AGAIN       Try again later 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_ps2_write( unsigned char data );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_ps2_handler_t)(int event);

__hal_defunc1(hal_ps2_init, HAL_PS2_CONFIG *, params);
__hal_defunc0(hal_ps2_shutdown, void);
__hal_defunc1(hal_ps2_set_config, HAL_PS2_CONFIG *, params);
__hal_defunc2(hal_ps2_attach, int, event, hal_ps2_handler_t, handler);
__hal_defunc1(hal_ps2_detach, int, event);
__hal_defunc1(hal_ps2_get_status, int *, status);
__hal_defunc1(hal_ps2_read, unsigned char *, data);
__hal_defunc1(hal_ps2_write, unsigned char, data);

__hal_deisr(hal_ps2_h_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/**  @} */

#endif  /* HAL_USIP_PS2_H */

