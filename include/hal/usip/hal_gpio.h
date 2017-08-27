/*============================================================================
 *
 *      hal_gpio.h
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
 * Author(s):    Arnaud Corria  /  Antoine Namour
 * Contributors: Arnaud Ferir
 * Date:          
 * Purpose:       
 * Description:  General Purpose IO
 * 
 *==========================================================================*/
#ifndef HAL_USIP_GPIO_H
#define HAL_USIP_GPIO_H	


/**
 *  
 * @defgroup HAL_GPIO HAL GPIO
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the GPIO (General Purpose Input/Output). 
 * 
 * @section hal_gpio Overview 
 * 
 * USIP® Professional provides up to 32 General Purpose Input/Output that may 
 * be individually programmed as input or output.
 * 
 * Any GPIO may generate interrupts when configured as an input. These 
 * interrupts may be edge or level triggered. 
 * 
 * @warning The GPIOs [8..15] are shared with the parallel port. When the 
 * parallel port is in use, the GPIOs [8..15] are busy and their initialization 
 * fail. 
 * 
 * @addtogroup HAL_GPIO
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** This size indicator is used to configure only 24 GPIO */
#define HAL_GPIO_SIZE_24    0
/** This size indicator is used to configure the all 32 GPIO */
#define HAL_GPIO_SIZE_32    1

/** This event indicator is used to generate interrupts on high level */
#define HAL_GPIO_EVENT_HIGH_LEVEL       0
/** This event indicator is used to generate interrupts on low level */
#define HAL_GPIO_EVENT_LOW_LEVEL        1
/** This event indicator is used to generate interrupts on rising edge */
#define HAL_GPIO_EVENT_RISING_EDGE      2
/** This event indicator is used to generate interrupts on falling edge */
#define HAL_GPIO_EVENT_FALLING_EDGE     3
/** This event indicator is used to generate interrupts on both edges */
#define HAL_GPIO_EVENT_BOTH_EDGES       4


/*----------------------------------------------------------------------------
 * Control Enumeration
 */

/** The control enumeration defines the type of control on the GPIO 
 */
typedef enum 
{
	/** Set a single GPIO pin */
	HAL_GPIO_IOCTL_SET,

	/** Clear a single GPIO pin */
	HAL_GPIO_IOCTL_CLEAR,

	/** Get a single GPIO pin level */
	HAL_GPIO_IOCTL_GET,

	/** Get the number of GPIO in use (#HAL_GPIO_SIZE_24 or #HAL_GPIO_SIZE_32) */
	HAL_GPIO_IOCTL_GET_SIZE,

	/** Clear a single GPIO pin interrupt */
	HAL_GPIO_IOCTL_CLEAR_INTERRUPT,

} HAL_GPIO_CONTROL ;


/*----------------------------------------------------------------------------
 * Configuration Structure
 */
     
/** The configuration structure is used to set up the GPIO
 * 
 *  Usage: For any data field,
 *  \li bit 0 applies to GPIO pin 0,
 *  \li ...
 *  \li bit 31 applies to GPIO pin 31. */
typedef struct HAL_GPIO_CONFIG 
{
    /** Specify the number of GPIO to be used:
     *  \li #HAL_GPIO_SIZE_32 configure all 32 GPIO for use. 
     *  \li #HAL_GPIO_SIZE_24 configure only GPIO [0..7] and [16..31] (GPIO 
     *  [8..15] are left free for parallel port) */
    unsigned int size;    

    /** Specify GPIO direction: if any bit is set the corresponding GPIO pin is 
     *  configured as an output, otherwise the pin is configured as an input */
    unsigned int direction;    

} HAL_GPIO_CONFIG; 


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures the GPIO. 
 *
 * @warning The GPIO module shares its clock and hardware reset with the 
 * parallel, PS/2 and thermal printer interfaces. It is not actually reset nor 
 * activated if any of these interfaces is already in use. 
 * 
 * @param[in] params        A pointer on GPIO configuration structure allocated 
 *                          and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_gpio_init( HAL_GPIO_CONFIG *params );


/**
 * This function disables the GPIO. 
 * 
 * @warning The GPIO module shares its clock and hardware reset with the 
 * parallel, PS/2 and thermal printer interfaces. It is not actually disabled 
 * if any of these interfaces is still in use. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_gpio_shutdown( void );


/**
 * The function configures the GPIO. 
 *
 * @param[in] params        A pointer on GPIO configuration structure allocated 
 *                          and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_gpio_init() first. 
 * @retval -ERR_BUSY        Resource busy. Shared resources are already in use. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_gpio_set_config( HAL_GPIO_CONFIG *params );


/**
 * The function performs a specific control on the GPIO. 
 * 
 * @param[in] control  		The control to be performed. 
 * 
 * @param[in,out] data  	Point to a variable allocated by the caller that is 
 *                          used depending on the control function: 
 *                          \li #HAL_GPIO_IOCTL_GET_SIZE: data filled by the 
 *                          function with the number of GPIO currently used 
 *                          (#HAL_GPIO_SIZE_24 or #HAL_GPIO_SIZE_32).
 *                          \li #HAL_GPIO_IOCTL_GET: data filled by the caller 
 *                          with the GPIO pin number (0 to 31). This data will 
 *                          finally be filled by the function with 1 if the 
 *                          requested GPIO is set or with 0 if the GPIO is 
 *                          cleared. 
 *                          \li #HAL_GPIO_IOCTL_SET: data filled by the caller 
 *                          with the GPIO pin number (0 to 31). 
 *                          \li #HAL_GPIO_IOCTL_CLEAR: data filled by the caller 
 *                          with the GPIO pin number (0 to 31). 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_gpio_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_DEVNOSUPP   Device does not support this operation. Check the 
 *                          configuration of the specified GPIOs.
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_gpio_ioctl( HAL_GPIO_CONTROL control, int * data );


/**
 * The function registers an interrupt handler for a single GPIO configured as
 * an input.
 * 
 * @param[in] gpio          Single GPIO number (0 to 31). The requested GPIO 
 *                          should previously be configured as an input. 
 * 
 * @param[in] event         Event type. Possible values are following: 
 *                          \li #HAL_GPIO_EVENT_HIGH_LEVEL 
 *                          \li #HAL_GPIO_EVENT_LOW_LEVEL 
 *                          \li #HAL_GPIO_EVENT_RISING_EDGE 
 *                          \li #HAL_GPIO_EVENT_FALLING_EDGE 
 *                          \li #HAL_GPIO_EVENT_BOTH_EDGES 
 * 
 * @param[in] handler       Pointer to the interrupt handler function.
 *                          Its declaration should support the parameters:
 *                          \li \e gpio GPIO number that caused the interrupt 
 *                          \li \e event Type of event that caused the 
 *                          interrupt 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_gpio_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_DEVNOSUPP   Device does not support this operation. Check the 
 *                          configuration of the specified GPIOs.
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_gpio_attach( int gpio, int event, void (*handler)(int gpio,int event));


/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] gpio          Single GPIO number (0 to 31). 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_gpio_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_gpio_detach( int gpio);


/**
 * The function reads all the GPIO at the same time. 
 * 
 * @param[out] data	 		A pointer on a variable allocated by the caller and 
 * 							filled by the function with the read data. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_gpio_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_gpio_read( unsigned int *data );


/**
 * The function writes into all the GPIO at the same time. Only GPIO configured 
 * as outputs will be written. 
 * 
 * @param[in] data			The data to be written into the GPIO (bit 0 of the 
 *                          data will be written on GPIO pin 0, aso). 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_gpio_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_gpio_write( unsigned int data );

#else

#include <hal/usip/hal_sys.h>

typedef  void (*hal_gpio_handler_t)(int gpio,int event);

__hal_defunc1(hal_gpio_init, HAL_GPIO_CONFIG *, params);
__hal_defunc0(hal_gpio_shutdown, void);
__hal_defunc1(hal_gpio_set_config, HAL_GPIO_CONFIG *, params);
__hal_defunc2(hal_gpio_ioctl, HAL_GPIO_CONTROL, control, int *, data);
__hal_defunc3(hal_gpio_attach, int, gpio, int, event, hal_gpio_handler_t, handler);
__hal_defunc1(hal_gpio_detach, int, gpio);
__hal_defunc1(hal_gpio_read, unsigned int *, data);
__hal_defunc1(hal_gpio_write, unsigned int, data);
        
__hal_deisr(hal_gpio_isr, void);
      
#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* HAL_USIP_GPIO_H */
	

