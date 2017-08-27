/*============================================================================
 *
 *      hal_timer.h
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
 * Description:  This file contains the Timer generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_TIMER_H
#define HAL_USIP_TIMER_H


/**
 * 
 * @defgroup HAL_TMR HAL Timer
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the timers. 
 * 
 * @section hal_timer Overview
 * 
 * USIP® Professional provides up to 4 16-bits timers/counters. 
 * 
 * \b Features 
 * 
 * \li 4 Timers/Counters 
 * \li 4 independent prescalers (2^n, 0 <= n <= 15) 
 * \li Auto-reload (timer mode) 
 * \li Count up/down (counter mode) 
 * \li Interrupt on timer overflow 
 * \li Interrupt on up-counter match value reaching 
 * \li Interrupt on down-counter overflow 
 * 
 * @addtogroup HAL_TMR
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** Single Run Timer Mode */
#define HAL_TIMER_MODE_SINGLE_RUN       0
/** Auto-reload Timer Mode */
#define HAL_TIMER_MODE_AUTO_RELOAD      2
/** Counter Down Mode */
#define HAL_TIMER_MODE_COUNTER_DOWN     0
/** Counter Up Mode */
#define HAL_TIMER_MODE_COUNTER_UP       4

/** Timer pre-divisor value of the clock frequency : CPU clock/1 */ 
#define HAL_TIMER_CLOCK_1       0x0
/** Timer pre-divisor value of the clock frequency : CPU clock/2 */
#define HAL_TIMER_CLOCK_2       0x1
/** Timer pre-divisor value of the clock frequency : CPU clock/4 */
#define HAL_TIMER_CLOCK_4       0x2
/** Timer pre-divisor value of the clock frequency : CPU clock/8 */
#define HAL_TIMER_CLOCK_8       0x3
/** Timer pre-divisor value of the clock frequency : CPU clock/16 */
#define HAL_TIMER_CLOCK_16      0x4
/** Timer pre-divisor value of the clock frequency : CPU clock/32 */
#define HAL_TIMER_CLOCK_32      0x5
/** Timer pre-divisor value of the clock frequency : CPU clock/64 */
#define HAL_TIMER_CLOCK_64      0x6
/** Timer pre-divisor value of the clock frequency : CPU clock/128 */
#define HAL_TIMER_CLOCK_128     0x7
/** Timer pre-divisor value of the clock frequency : CPU clock/256 */
#define HAL_TIMER_CLOCK_256     0x8
/** Timer pre-divisor value of the clock frequency : CPU clock/512 */
#define HAL_TIMER_CLOCK_512     0x9
/** Timer pre-divisor value of the clock frequency : CPU clock/1024 */
#define HAL_TIMER_CLOCK_1024    0xA
/** Timer pre-divisor value of the clock frequency : CPU clock/2048 */
#define HAL_TIMER_CLOCK_2048    0xB
/** Timer pre-divisor value of the clock frequency : CPU clock/4096 */
#define HAL_TIMER_CLOCK_4096    0xC

/** Maximum of a timer counter value */
#define HAL_TIMER_VALUE_MAX              0xFFFF

/** Timer state : The timer is not counting */
#define HAL_TIMER_STATUS_IDLE    0
/** Timer state : The timer is busy */
#define HAL_TIMER_STATUS_RUNNING (1<<0)
/** Timer state : The timer has reached the value 0 if it counts down
 *  or it reaches the alarm value if it counts up */
#define HAL_TIMER_STATUS_OVERFLOW (1<<8)

#define HAL_TIMER_IOCTL_SET_MODE        0
#define HAL_TIMER_IOCTL_GET_MODE        1
#define HAL_TIMER_IOCTL_SET_TIMEOUT     2
#define HAL_TIMER_IOCTL_GET_TIMEOUT     3
#define HAL_TIMER_IOCTL_SET_CLOCK       4
 
/*----------------------------------------------------------------------------
 * Device Enumeration
 */

/** The device enumeration defines the timer identifiers 
 */
enum hal_timer_devices 
{
    /** Identifier of the timer 0 */
    hal_timer_dev0 = 0,
    /** Identifier of the timer 1 */
    hal_timer_dev1,
    /** Identifier of the timer 2 */
    hal_timer_dev2,
    /** Identifier of the timer 3 */
    hal_timer_dev3,
    /** This constant is used to retrieve the number of available timers */
    hal_timer_devices_count
};   


/*----------------------------------------------------------------------------
 * Configuration Structure
 */

/** The configuration structure used to set up a timer device. */
typedef struct HAL_TIMER_CONFIG
{
    /** Timer mode, this parameter can be an OR combination of:
     *  @li #HAL_TIMER_MODE_SINGLE_RUN  
     *  @li #HAL_TIMER_MODE_AUTO_RELOAD
     *  @li #HAL_TIMER_MODE_COUNTER_DOWN
     *  @li #HAL_TIMER_MODE_COUNTER_UP
     */
    unsigned int mode;      
    
    /** Prescaler value, this parameter is used to divide the clock by: 
     * @li #HAL_TIMER_CLOCK_1
     * @li #HAL_TIMER_CLOCK_2
     * @li #HAL_TIMER_CLOCK_4
     * @li #HAL_TIMER_CLOCK_8
     * @li #HAL_TIMER_CLOCK_16
     * @li #HAL_TIMER_CLOCK_32
     * @li #HAL_TIMER_CLOCK_64
     * @li #HAL_TIMER_CLOCK_128
     * @li #HAL_TIMER_CLOCK_256
     * @li #HAL_TIMER_CLOCK_512
     * @li #HAL_TIMER_CLOCK_1024
     * @li #HAL_TIMER_CLOCK_2048
     * @li #HAL_TIMER_CLOCK_4096
     */
    unsigned int clock;
    
    /** Time out value (this value is anded with 0xFFF0) */
    unsigned int timeout;   
        
} HAL_TIMER_CONFIG;


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
 
#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures a timer. 
 *  
 * @warning The timer module shares its clock and hardware reset with the 
 * PWM and watchdog modules. It is not actually reset nor activated 
 * if any of these devices is already in use. 
 * 
 * @param[in] devnum        The timer identifier  (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 *
 * @param[in] params        Points on a timer configuration structure allocated 
 *                          and filled by the caller. 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_timer_init( int devnum, HAL_TIMER_CONFIG *params );

/**
 * The function disables a timer. 
 * 
 * @warning The timer module shares its clock and hardware reset with the 
 * PWM and watchdog modules. It is not actually disabled 
 * if any of these devices is still in use. 
 * 
 * @param[in] devnum        The timer identifier  (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_timer_shutdown( int devnum );

/**
 * The function is used to setup a timer.
 * 
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 * 
 * @param[in] params        Points on a timer configuration structure allocated 
 *                          and filled by the caller. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_timer_set_config( int devnum, HAL_TIMER_CONFIG *params );

/**
 * The function is used to retrieve a current timer state.
 * 
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 * 
 * @param[out] status       Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the specified device. It can be one or an orred 
 *                          combination of the following values: 
 *                          @li #HAL_TIMER_STATUS_RUNNING
 *                          @li #HAL_TIMER_STATUS_OVERFLOW
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_timer_get_status( int devnum, int *status );

/**
 * The function starts a requested timer counting.
 * 
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_timer_run( int devnum );

/**
 * The function stops the requested timer previously started by hal_timer_run().
 *
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_timer_stop( int devnum );

/**
 * This function is used to retrieve the current value of a timer.
 * 
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 * 
 * @param[out] value        Valid pointer to the current device value.
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_timer_read( int devnum, int *value );

/**
 * The function registers an interrupt handler for the overflow event:
 *  @li when a timer reaches the value 0 if it counts down. 
 *  @li when a timer reaches the alarm value if it counts up.
 * 
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 *  
 * @param[in] handler       Pointer to the interrupt handler function.
 *                          Its declaration should support the parameters:
 *                          \li \e devnum Device identifier
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_timer_attach( int devnum, void (*handler)( int ) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * the overflow event.
 * 
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval -ERR_ALREADY     Operation already in progress 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_timer_detach( int devnum );

/**
 * The function performs Timer specific control functions.
 *
 * @param[in] devnum        The timer identifier (#hal_timer_devices gives a 
 *                          list of all timer device identifiers).
 * 
 * @param[in] cmd           Requested control function.
 * 
 * @param[in,out] data      Points to a buffer that contains any data required 
 *                          for the given control function or receives data from 
 *                          that function.
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_timer_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_timer_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_timer_ioctl( int devnum, int cmd, void *data );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_timer_handler_t)( int );

__hal_defunc2(hal_timer_init, int, devnum, HAL_TIMER_CONFIG *, params);
__hal_defunc1(hal_timer_shutdown, int, devnum);
__hal_defunc2(hal_timer_set_config, int, devnum, HAL_TIMER_CONFIG *, params);
__hal_defunc2(hal_timer_get_status, int, devnum, int *, status);
__hal_defunc1(hal_timer_run, int, devnum);
__hal_defunc1(hal_timer_stop, int, devnum);
__hal_defunc2(hal_timer_read, int, devnum, int *, value);
__hal_defunc2(hal_timer_attach, int, devnum, hal_timer_handler_t, handler);
__hal_defunc1(hal_timer_detach, int, devnum);
__hal_defunc3(hal_timer_ioctl, int, devnum, int, cmd, void *, data);

__hal_deisr(hal_timer_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */


#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* HAL_USIP_TIMER_H */

