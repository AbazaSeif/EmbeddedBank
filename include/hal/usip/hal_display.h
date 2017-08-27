/*============================================================================
 *
 *      hal_display.h
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
 * Description:   This file contains the LCD Interface generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_DISPLAY_H
#define HAL_USIP_DISPLAY_H


/**
 * @defgroup HAL_LCD HAL Display Interface.
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the LCD Interface (Liquid Cristal Display). 
 * 
 * @section Overview Overview 
 * 
 * USIP® Professional provides an interface for LCD controllers. This display 
 * interface supports all LCD controllers which have pin function compatibility 
 * with HD44780. 
 * 
 * \b Features
 * 
 * \li 4 and 8 bits modes. 
 * \li 3 control lines.
 * \li Automatic busy state polling. 
 * \li Configurable timing. 
 * 
 * @addtogroup HAL_LCD
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/
 
/** This state indicator is raised when a data is transmitted */
#define HAL_DISPLAY_STATUS_TX_DONE       (1<<0)
/** This state indicator is raised when a data is received */
#define HAL_DISPLAY_STATUS_RX_DONE       (1<<1)
/** This state indicator is raised when the interface is ready to 
 * send/receive data */
#define HAL_DISPLAY_STATUS_READY         (1<<2)

/** This event indicator is raised when a word is received */ 
#define HAL_DISPLAY_EVENT_TX_DONE       (0)
/** This event indicator is raised when a word is send */ 
#define HAL_DISPLAY_EVENT_RX_DONE       (1)

/** Command code to set the CD pin value. */
#define HAL_DISPLAY_IOCTL_SET_CD    0
/** Command code to set the RW pin value. */
#define HAL_DISPLAY_IOCTL_SET_RW    1
/** Command code to use the E pin, if auto-enable mode not selected then set 
 * the E pin value, if auto-enable mode selected then select the pulse polarity 
 * of the E pin. 
 */
#define HAL_DISPLAY_IOCTL_SET_E    2
/** Command code to get the CD pin. */
#define HAL_DISPLAY_IOCTL_GET_CD    3
/** Command code to get the RW pin. */
#define HAL_DISPLAY_IOCTL_GET_RW    4
/** Command code to get the E pin. */
#define HAL_DISPLAY_IOCTL_GET_E    5
/** Command code to start a read procedure. */
#define HAL_DISPLAY_IOCTL_START_READ    6

/** This configuration is used to set the transmitted data to 4-bit width */ 
#define HAL_DISPLAY_BUS_WIDTH_4   4
/** This configuration is used to set the transmitted data to 8-bit width */
#define HAL_DISPLAY_BUS_WIDTH_8   8

/** This configuration is used to set the manual management of the enable 
 *  signal */
#define HAL_DISPLAY_MODE_MANUAL             0x00
/** This configuration is used to set the automatic management of the enable 
 *  signal */
#define HAL_DISPLAY_MODE_AUTO               0x01

/** This configuration is used to set how the enable signal must be driven 
 * when the automatic mode is selected : the signal is active high */
#define HAL_DISPLAY_MODE_E_HIGH             0x00

/** This configuration is used to set how the enable signal must be driven 
 * when the automatic mode is selected : the signal is active low */
#define HAL_DISPLAY_MODE_E_LOW              0x10


/*----------------------------------------------------------------------------
 * Configuration Structure
 */
 
/** The configuration structure used to set up the LCD Interface */
typedef struct HAL_DISPLAY_CONFIG
{
  /** 
   * Specify the mode. Available value is an OR combinaison of :
   *    \li #HAL_DISPLAY_MODE_MANUAL
   *    \li #HAL_DISPLAY_MODE_AUTO
   *    \li #HAL_DISPLAY_MODE_E_LOW
   *    \li #HAL_DISPLAY_MODE_E_HIGH
   */
  int mode; 

  /** 
   * Specify the data bus width. Available values are:
   *    \li #HAL_DISPLAY_BUS_WIDTH_4
   *    \li #HAL_DISPLAY_BUS_WIDTH_8
   */
  int buswidth;

  /** Specify the enable period in ns */
  int period;

} HAL_DISPLAY_CONFIG;


/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes and configures the LCD Interface.
 *  
 * @param[in] params        Pointer on a LCD configuration structure allocated 
 *                          and filled by the caller.
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_init( HAL_DISPLAY_CONFIG *params );

/**
 * The function terminates the use of the LCD Interface.
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_shutdown( void );

/** 
 * The function configures the LCD Interface.
 * 
 * @param[in] params        Pointer on a LCD configuration structure allocated 
 *                          and filled by the caller.
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_display_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */ 
int hal_display_set_config( HAL_DISPLAY_CONFIG *params );

/** 
 * The function provides the current state of the LCD Interface.
 * 
 * @param[out] status       Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the LCD interface. It is an orred combination of 
 *                          the following values: 
 *                          \li #HAL_DISPLAY_STATUS_READY
 *                          \li #HAL_DISPLAY_STATUS_TX_DONE
 *                          \li #HAL_DISPLAY_STATUS_RX_DONE
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_display_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_get_status( int *status );

/** 
 * The function writes a data to the LCD Interface output.
 * 
 * @param[in] data          The data to write.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_display_init() 
 *                          first. 
 * @retval -ERR_AGAIN       Try again later. Idle state in auto-enable mode. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_write( unsigned char data );

/** 
 * This function reads a data from the LCD Interface input.
 *
 * @param[out] data         A pointer allocated by the caller and filled by the 
 *                          function with the read data.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_display_init() 
 *                          first. 
 * @retval -ERR_AGAIN       Try again later. Idle state in auto-enable mode. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_read( unsigned char *data );

/**
 * The function performs LCD Interface specific control functions.
 * 
 * @param[in] cmd           The control function to be performed. It is one of 
 *                          the following values: 
 *                          \li #HAL_DISPLAY_IOCTL_SET_CD 
 *                          \li #HAL_DISPLAY_IOCTL_SET_RW 
 *                          \li #HAL_DISPLAY_IOCTL_SET_E 
 *                          \li #HAL_DISPLAY_IOCTL_GET_CD 
 *                          \li #HAL_DISPLAY_IOCTL_GET_RW 
 *                          \li #HAL_DISPLAY_IOCTL_GET_E 
 *                          \li #HAL_DISPLAY_IOCTL_START_READ 
 * 
 * @param[in,out] data      Points to a buffer that contains any data required 
 *                          for the given control function or receives data 
 *                          from this function.
 *                          \li set control functions: the specified signal is 
 *                          cleared if data pointer is null, set otherwise 
 *                          \li get control function: data is filled with 0 if 
 *                          the specified signal is cleared, or with a non-null 
 *                          value if the specified signal is set. 
 *                          \li start function: data not used 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_display_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NOTTY       Inappropriate ioctl for device 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_ioctl( int cmd, void *data );

/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_DISPLAY_EVENT_RX_DONE
 *                          \li #HAL_DISPLAY_EVENT_TX_DONE
 * 
 * @param[in] handler       Pointer to the interrupt handler function.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_display_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_attach( int event, void (*handler)(int) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_DISPLAY_EVENT_RX_DONE
 *                          \li #HAL_DISPLAY_EVENT_TX_DONE
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_display_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_ALREADY     Operation already in progress 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_display_detach( int event );
   

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_display_handler_t)(int event);

__hal_defunc1(hal_display_init, HAL_DISPLAY_CONFIG *, params);
__hal_defunc0(hal_display_shutdown, void);
__hal_defunc1(hal_display_set_config, HAL_DISPLAY_CONFIG *, params);
__hal_defunc1(hal_display_get_status, int *, status);
__hal_defunc1(hal_display_write, char, data);
__hal_defunc1(hal_display_read, char *, data);
__hal_defunc2(hal_display_ioctl, int, cmd, void *, data);
__hal_defunc2(hal_display_attach, int, event, hal_display_handler_t, handler);
__hal_defunc1(hal_display_detach, int, event);

__hal_deisr(hal_display_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */
                
#ifdef __cplusplus
}
#endif

/** @} */

#endif  /*  HAL_USIP_DISPLAY_H */
	

