/*============================================================================
 *
 *      hal_pwm.h
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
#ifndef HAL_USIP_PWM_H
#define HAL_USIP_PWM_H


/**
 *  
 * @defgroup HAL_PWM HAL Pulse Width Modulator
 * The HAL Pulse Width Modulator (PWM) describes the functions related 
 * to the access to the Pulse Width Modulator. 
 * 
 * @section pwm Overview 
 * USIP® Professional provides up to 2 Pulse Width Modulators. 
 * 
 * \b Features
 * 
 * \li Customizable period and duty cycle 
 * \li Interrupt at the end of the period 
 * 
 * @addtogroup HAL_PWM
 *  
 * @{
 */
 

/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** This state indicator is raised while the Pulse Width Modulator is busy */
#define HAL_PWM_STATUS_RUNNING 0x02
/** This state indicator is raised when the Pulse Width Modulator has reached 
 *  the end of its period */
#define HAL_PWM_STATUS_OVERFLOW 0x10
 
/*----------------------------------------------------------------------------
 * Device Enumeration
 */

/** The device enumeration defines the PWM identifiers 
 */
enum hal_pwm_devices
{
    /** Identifier of the first PWM device */
    hal_pwm_dev0 = 0,
    /** Identifier of the second PWM device */
    hal_pwm_dev1,
    /** This constant is used to fix the number of available PWM devices */
    hal_pwm_devices_count
};   

/*----------------------------------------------------------------------------
 * Configuration Structure
 */

/** The configuration structure is used to set up a Pulse Width Modulator. */
typedef struct HAL_PWM_CONFIG
{
	/** Frequency value expressed in Hz (ranging between 1 and the current 
     * system frequency) */
    unsigned int frequency;
    
    /** Pulse width ratio (percentage) */
    unsigned int pulse;   

} HAL_PWM_CONFIG;


/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
 
#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures a Pulse Width Modulator. 
 *  
 * @warning The PWM module shares its clock and hardware reset with the 
 * timer and watchdog modules. It is not actually reset nor activated 
 * if any of these devices is already in use. 
 * 
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 * 
 * @param[in] params        Points on a PWM configuration structure allocated 
 *                          and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_pwm_init( int devnum, HAL_PWM_CONFIG *params );

/**
 * The function disables a Pulse Width Modulator.
 *  
 * @warning The PWM module shares its clock and hardware reset with the 
 * timer and watchdog modules. It is not actually disabled 
 * if any of these devices is still in use. 
 * 
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_pwm_shutdown( int devnum );

/**
 * The function is used to setup a Pulse Width Modulator.
 * 
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 * 
 * @param[in] params        Points on a PWM configuration structure allocated 
 *                          and filled by the caller. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_pwm_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_pwm_set_config( int devnum, HAL_PWM_CONFIG *params );

/**
 * The function starts a Pulse Width Modulator.
 * 
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_pwm_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_pwm_run( int devnum );

/**
 * The function stops a Pulse Width Modulator.
 *
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_pwm_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_pwm_stop( int devnum );

/**
 * The function is used to retrieve the current state of a Pulse Width 
 * Modulator. 
 * 
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 * 
 * @param[in] status        Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the requested device. It is a combination of the 
 *                          following values: 
 *                          @li #HAL_PWM_STATUS_RUNNING
 *                          @li #HAL_PWM_STATUS_OVERFLOW
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_pwm_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_pwm_get_status( int devnum, int *status );

/**
 * The function performs Pulse Width Modulator specific control functions.
 *
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 * 
 * @param[in] cmd           The control function to be performed. 
 * 
 * @param[in,out] data      Pointer on a buffer that contains any data required 
 *                          for the given control function or receives data 
 *                          from that function. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_pwm_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_pwm_ioctl( int devnum, int cmd, void *data );

/**
 * The function registers an interrupt handler for the overflow event.
 * 
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 *  
 * @param[in] handler       Pointer to the interrupt handler function. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_pwm_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_pwm_attach( int devnum, void (*handler)( int ) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * the overflow event.
 * 
 * @param[in] devnum        The PWM identifier (#hal_pwm_devices gives a list 
 *                          of all PWM device identifiers) 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_pwm_devices). 
 * @retval -ERR_ALREADY     Operation already in progress 
 * @retval -ERR_NXIO        Device not configured. Use hal_pwm_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_pwm_detach( int devnum );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_pwm_handler_t)( int devnum );

__hal_defunc2(hal_pwm_init, int, devnum, HAL_PWM_CONFIG *, params);
__hal_defunc1(hal_pwm_shutdown, int, devnum);
__hal_defunc2(hal_pwm_set_config, int, devnum, HAL_PWM_CONFIG *, params);
__hal_defunc1(hal_pwm_run, int, devnum);
__hal_defunc1(hal_pwm_stop, int, devnum);
__hal_defunc2(hal_pwm_get_status, int, devnum, int *, status);
__hal_defunc2(hal_pwm_attach, int, devnum, hal_pwm_handler_t, handler);
__hal_defunc1(hal_pwm_detach, int, devnum);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* HAL_USIP_PWM_H */



