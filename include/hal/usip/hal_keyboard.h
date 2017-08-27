/*============================================================================
 *
 *      hal_keyboard.h
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
 * Contributors:  Stephane Royo
 * Date:          
 * Purpose:       
 * Description:   This file contains the Keyboard Interface generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_KEYBOARD_H
#define HAL_USIP_KEYBOARD_H	


/**
 * @defgroup HAL_KBD HAL Keyboard Interface 
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the Keyboard Interface. 
 * 
 * @section Overview Overview 
 * 
 * USIP® Professional provides a 12x12 Matrix Keyboard controller with hardware 
 * scanning and de-bouncing features. 
 * 
 * USIP® Professional also provides a GPIO mode. The keyboard controller is 
 * by-passed and the keyboard pins are directly controlled by GPIO registers. 
 * 
 * \b Features
 * 
 * \li Interfaced keyboards have up to 144 keys.
 * \li Part of the keyboard can be disabled.
 * \li Up to 4 keys can be pushed at the same time.
 * \li Detection of pushed and released operations.
 * \li When a key is released, the register is erased for more security.
 * \li De-bouncing process
 * \li Security features included
 * 
 * \b Hardware \b Configuration
 * 
 * The keyboard interface is used to detect a key pushed. 24 I/O are used to 
 * connect a keyboard. Each pin can be configured as an input or output (line 
 * or column).
 * 
 * THe software configuration consists of one single parameter: the number of 
 * outputs. This parameter depends on the physiscal keyboard connection.
 * 
 * \b Example\b : keypad 4*4 
 * 
 * 4 outputs of the Keyboard Interface are connected to the keypad. The number 
 * of output parameter must then be 4. 
 * 
 * <tt>
 *       O >-+-+-+-+ \n
 *       O >-+-+-+-+ \n
 *       O >-+-+-+-+ \n
 *       O >-+-+-+-+ \n
 *       I <-+ | | | \n
 *       I <---+ | | \n
 *       I <-----+ | \n
 *       I <-------+ \n
 * </tt>
 * 
 * @addtogroup HAL_KBD
 * 
 * @{
 */

 
/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** 
 * This state indicator is raised when more than 4 keys have been pressed 
 * in the same time or more than 4 key events (push or release) have been 
 * registered but the keys have not been read.  
 */
#define HAL_KEYBOARD_STATUS_OVERFLOW        (1<<1)
/** This state indicator is raised when a key is pushed    */
#define HAL_KEYBOARD_STATUS_KEY_PUSHED      (1<<2)
/** This state indicator is raised when a key is released */
#define HAL_KEYBOARD_STATUS_KEY_RELEASED    (1<<3)
/** This state indicator is raised when a key is released */
#define HAL_KEYBOARD_STATUS_GPIO_CHANGED    (1<<8)

/** 
 * This event indicator is raised when more than 4 keys have been pressed 
 * in the same time or more than 4 key events (push or release) have been 
 * registered but the keys have not been read.  
 */
#define HAL_KEYBOARD_EVENT_OVERFLOW         0
/** This event indicator is raised when a key is pushed    */
#define HAL_KEYBOARD_EVENT_KEY_PUSHED       1 
/** This event indicator is raised when a key is released */
#define HAL_KEYBOARD_EVENT_KEY_RELEASED     2
/** This event indicator is raised when GPIO3 or GPIO4 has changed */
#define HAL_KEYBOARD_EVENT_GPIO_CHANGED     3
/** The number of maximum output */
#define HAL_KEYBOARD_OUTPUT_MAX 24
 
/** 
 * The auto clear mode is activated, even if only the interrupt on key 
 * pusched are enabled, the key released event will are not registered into 
 * key register 
 */
#define HAL_KEYBOARD_MODE_AUTOCLEAR       (1<<4)
/** The auto clear mode is not activated  */
#define HAL_KEYBOARD_MODE_MANUAL            0
/** The GPIO mode is activated  */
#define HAL_KEYBOARD_MODE_GPIO            0xFF

   
/** Command code to enable or disable the Keyboard Interface */
#define HAL_KEYBOARD_IOCTL_SET_KBDEN            0
/** Command code to enable or disable the key pressed interrupt */
#define HAL_KEYBOARD_IOCTL_SET_PUSIEN           1
/** Command code to enable or disable the key released interrupt */
#define HAL_KEYBOARD_IOCTL_SET_RELIEN           2
/** Command code to enable or disable the interrupt that occurs when more than 
 *  4 keys are pressed at the same time */
#define HAL_KEYBOARD_IOCTL_SET_OVERIEN          3
/** Command code to control the CLEAR bit of control register 3 
 * (If set with RELIEN cleared, when the key is released the corresponding 
 * register is cleared) */
#define HAL_KEYBOARD_IOCTL_SET_CLEAR            4
/** Command code to select the time range of de-bouncing. */
#define HAL_KEYBOARD_IOCTL_SET_DEBOUNCING_TIME  5
/** Command code to use or bypass the keyboard controller. (If the keyboard 
 *  controller is bypassed, the keyboard pins are controlled by the GPIO 
 *  registers.) */
#define HAL_KEYBOARD_IOCTL_SET_GPIOEN           6
/** Command code to enable or disable the GPIO3 or GPIO4 registers change 
 *  interrupt. */
#define HAL_KEYBOARD_IOCTL_SET_GPIOIE           7

/** Command code to set the GPIO1 register value: GPIO pins [0..15] are 
 *  controlled by GPIO1 register bits [0..15]. A pin is in high impedance if 
 *  its control bit is set or cleared if its control bit is cleared (output 
 *  control) */
#define HAL_KEYBOARD_IOCTL_SET_GPIO1            8
/** Command code to set the GPIO2 register value: GPIO pins [16..23] are 
 *  controlled by GPIO2 register bits [0..7]. A pin is in high impedance if its 
 *  control bit is set or cleared if its control bit is cleared (output 
 *  control) */
#define HAL_KEYBOARD_IOCTL_SET_GPIO2            9
/** Command code to get the GPIO1 register value (output control) */
#define HAL_KEYBOARD_IOCTL_GET_GPIO1            12
/** Command code to get the GPIO2 register value (output control) */
#define HAL_KEYBOARD_IOCTL_GET_GPIO2            13
/** Command code to get the GPIO3 register value: GPIO pins [0..15] can be read 
 *  from GPIO3 register bits [0..15] (input read) */
#define HAL_KEYBOARD_IOCTL_GET_GPIO3            14
/** Command code to get the GPIO4 register value: GPIO pins [16..23] can be read 
 *  from GPIO4 register bits [0..7] (input read) */
#define HAL_KEYBOARD_IOCTL_GET_GPIO4            15

/** Command code to set the GPIO3 or GPIO4 register changed flag */
#define HAL_KEYBOARD_IOCTL_SET_GPIOF            16
/** Command code to get the GPIO3 or GPIO4 register changed flag */
#define HAL_KEYBOARD_IOCTL_GET_GPIOF            17


/*----------------------------------------------------------------------------
 * Configuration Structure
 */

/** The configuration structure used to set up the Keyboard Interface */
typedef struct HAL_KEYBOARD_CONFIG 
{    
    /** Specify the number of outputs */
    unsigned int   output; 
 
   /** Specify the mode of use. Possible values are :
    *  @li #HAL_KEYBOARD_MODE_AUTOCLEAR
    *  @li #HAL_KEYBOARD_MODE_MANUAL
    *  @li #HAL_KEYBOARD_MODE_GPIO
    * 
    */                
    unsigned int    mode; 
      
} HAL_KEYBOARD_CONFIG;


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures the Keyboard Interface. 
 * 
 * @param[in] params        Pointer to an initialized configuration structure 
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_init( HAL_KEYBOARD_CONFIG *params );

/**
 * The function disables the Keyboard Interface. 
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_shutdown( void );

/** 
 * The function configures the Keyboard Interface.
 * 
 * @param[in] params        Pointer to an initialized configuration structure.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_keyboard_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_set_config( HAL_KEYBOARD_CONFIG *params );
 
/** 
 * The function retrieves the current state of the Keyboard Interface.
 * 
 * @param[out] status       Pointer allocated by the caller and filled by the 
 *                          function with the current state of the Keyboard 
 *                          Interface. Upon success, it receives one of the
 *                          following state indicators: 
 *                          \li #HAL_KEYBOARD_STATUS_OVERFLOW
 *                          \li #HAL_KEYBOARD_STATUS_KEY_PUSHED
 *                          \li #HAL_KEYBOARD_STATUS_KEY_RELEASED
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_keyboard_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_get_status( int *status );

/**
 * The function gets the pushed or released key from the Keyboard Interface.
 *
 * @param[out] scancode     Valid pointer to the physical key code.
 * 
 * @param[out] event        Valid pointer to the type of event. 
 *                          Possible values are :
 *                          \li #HAL_KEYBOARD_EVENT_KEY_PUSHED       
 *                          \li #HAL_KEYBOARD_EVENT_KEY_RELEASED    
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_keyboard_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later. No key pushed or released. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_read( int *scancode, int *event );

/**
 * The function writes to the GPIO of the Keyboard Interface.
 *
 * @param[out] data         Data to write on the GPIO.
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_keyboard_init() 
 *                          first. 
 * @retval -ERR_PERM        Not permitted. The keyboard controller pins are 
 *                          controller by GPIO. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_write( unsigned int data );

/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_KEYBOARD_EVENT_OVERFLOW
 *                          \li #HAL_KEYBOARD_EVENT_KEY_PUSHED
 *                          \li #HAL_KEYBOARD_EVENT_KEY_RELEASED
 *                          \li #HAL_KEYBOARD_EVENT_GPIO_CHANGED
 *          
 * 
 * @param[in] handler       Pointer to the interrupt handler function. 
 *                          Its declaration should support the parameters: 
 *                          \li \e event Occured event 
 *                          \li \e key Key scancode 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_keyboard_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_attach( int event, void (*handler)(int event) );
                  
/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_KEYBOARD_EVENT_OVERFLOW
 *                          \li #HAL_KEYBOARD_EVENT_KEY_PUSHED
 *                          \li #HAL_KEYBOARD_EVENT_KEY_RELEASED
 *                          \li #HAL_KEYBOARD_EVENT_GPIO_CHANGED
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_keyboard_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_ALREADY     Operation already in progress
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_detach( int event );

/**
 * The function performs Keyboard Interface specific control functions.
 * 
 * @param[in] cmd           Requested control function. It is one of 
 *                          the following values: 
 *                          \li #HAL_KEYBOARD_IOCTL_SET_KBDEN
 *                          \li #HAL_KEYBOARD_IOCTL_SET_PUSIEN
 *                          \li #HAL_KEYBOARD_IOCTL_SET_RELIEN
 *                          \li #HAL_KEYBOARD_IOCTL_SET_OVERIEN
 *                          \li #HAL_KEYBOARD_IOCTL_SET_CLEAR
 *                          \li #HAL_KEYBOARD_IOCTL_SET_DEBOUNCING_TIME
 *                          \li #HAL_KEYBOARD_IOCTL_SET_GPIOEN
 *                          \li #HAL_KEYBOARD_IOCTL_SET_GPIOIE
 *                          \li #HAL_KEYBOARD_IOCTL_SET_GPIO1
 *                          \li #HAL_KEYBOARD_IOCTL_SET_GPIO2
 *                          \li #HAL_KEYBOARD_IOCTL_GET_GPIO1
 *                          \li #HAL_KEYBOARD_IOCTL_GET_GPIO2
 *                          \li #HAL_KEYBOARD_IOCTL_GET_GPIO3
 *                          \li #HAL_KEYBOARD_IOCTL_GET_GPIO4
 *                          \li #HAL_KEYBOARD_IOCTL_SET_GPIOF
 *                          \li #HAL_KEYBOARD_IOCTL_GET_GPIOF 
 * 
 * @param[in,out] data      Points to a buffer that contains any data required 
 *                          for the given control function or receives data 
 *                          from that function.
 *                          \li set control functions 
 *                          (#HAL_KEYBOARD_IOCTL_SET_KBDEN, 
 *                          #HAL_KEYBOARD_IOCTL_SET_PUSIEN, 
 *                          #HAL_KEYBOARD_IOCTL_SET_RELIEN,
 *                          #HAL_KEYBOARD_IOCTL_SET_OVERIEN,
 *                          #HAL_KEYBOARD_IOCTL_SET_CLEAR,
 *                          #HAL_KEYBOARD_IOCTL_SET_GPIOEN or
 *                          #HAL_KEYBOARD_IOCTL_SET_GPIOIE): the specified 
 *                          control is cleared if data pointer is null, and set 
 *                          otherwise 
 *                          \li set GPIO control functions: the specified GPIO 
 *                          register is filled with the value of data pointer 
 *                          \li get GPIO control functions: data value is 
 *                          filled with the contents of the specified register 
 *                          \li HAL_KEYBOARD_IOCTL_SET_GPIOF: GPIOF bit of 
 *                          status register is cleared if data pointer is null, 
 *                          and set otherwise 
 *                          \li HAL_KEYBOARD_IOCTL_GET_GPIOF: data value is 
 *                          filled with the value of the GPIOF bit of status 
 *                          register 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_keyboard_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_keyboard_ioctl( int cmd, void *data );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_keyboard_handler_t)(int event);

__hal_defunc1(hal_keyboard_init, HAL_KEYBOARD_CONFIG *, params);
__hal_defunc0(hal_keyboard_shutdown, void);
__hal_defunc1(hal_keyboard_set_config, HAL_KEYBOARD_CONFIG *, params);
__hal_defunc1(hal_keyboard_get_status, int *, status);
__hal_defunc2(hal_keyboard_read, int *, scancode, int *, event);
__hal_defunc1(hal_keyboard_write, unsigned int, data);
__hal_defunc2(hal_keyboard_attach, int, event, hal_keyboard_handler_t, handler);
__hal_defunc1(hal_keyboard_detach, int, event);
__hal_defunc2(hal_keyboard_ioctl, int, cmd, void *, data);
     
__hal_deisr(hal_keyboard_isr, void);
         
#endif /* CONFIG_LIBROM_NOT_INLINED */


#ifdef __cplusplus
}
#endif


/** @} */

#endif  /* HAL_USIP_KEYBOARD_H */

