/*============================================================================
 *
 *      hal_watchdog.h
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
#ifndef HAL_USIP_WATCHDOG_H
#define HAL_USIP_WATCHDOG_H	


/** 
 * @defgroup HAL_WDT HAL Watchdog Timer  
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the watchdog timer. 
 * 
 * @section hal_wdt Overview
 * 
 * USIP® Professional provides a watchdog timer to secure the code execution. 
 * 
 * The Watchdog Timer prevents the system from locking up due to software 
 * deadlock: 
 * 
 * When used by any application, the watchdog timer counts down at a constant 
 * speed from a preset number. The counting speed is kept constant by a clock 
 * circuit. If the watchdog timer reaches zero before the application recovers, 
 * a signal is sent to designated circuits to perform the desired action. 
 * 
 * \b Features 
 * 
 * \li Reset the system on overflow 
 * \li Interrupt generation 
 * \li External pulse generation 
 * \li Input clock presence watched by security mechanisms 
 * \li Customizable counter clock and restart value 
 * 
 * @addtogroup HAL_WDT
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/


/** Default mode. No action is performed when the timer expires. */
#define HAL_WATCHDOG_MODE_NONE             0
/** 
 * When this mode is set and the time is expired, 
 * the Watchdog Timer performs a soft reset of the system. 
 */
#define HAL_WATCHDOG_MODE_RESET             (1<<0)
/** 
 * When this mode is set and the time is expired, 
 * the Watchdog Timer performs an external pulse. 
 */
#define HAL_WATCHDOG_MODE_EXT_PULSE         (1<<1)    

/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/4 */
#define HAL_WATCHDOG_CLOCK_4       0x0
/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/8 */
#define HAL_WATCHDOG_CLOCK_8       0x1
/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/32 */
#define HAL_WATCHDOG_CLOCK_32      0x2
/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/64 */
#define HAL_WATCHDOG_CLOCK_64      0x3
/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/256 */
#define HAL_WATCHDOG_CLOCK_256     0x4
/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/512 */
#define HAL_WATCHDOG_CLOCK_512     0x5
/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/2048 */
#define HAL_WATCHDOG_CLOCK_2048    0x6
/** Watchdog Timer pre-divisor value of the clock frequency : CPU clock/4096 */
#define HAL_WATCHDOG_CLOCK_4096    0x7
 
/** External pulse set to 8 clock cycles */
#define HAL_WATCHDOG_PULSE_8        0x0
/** External pulse set to 16 clock cycles */
#define HAL_WATCHDOG_PULSE_16       0x1
/** External pulse set to 32 clock cycles */
#define HAL_WATCHDOG_PULSE_32       0x2
/** External pulse set to 64 clock cycles */
#define HAL_WATCHDOG_PULSE_64       0x3
/** External pulse set to 128 clock cycles */
#define HAL_WATCHDOG_PULSE_128      0x4
/** External pulse set to 512 clock cycles */
#define HAL_WATCHDOG_PULSE_512      0x5
/** External pulse set to 1024 clock cycles */
#define HAL_WATCHDOG_PULSE_1024     0x6
/** External pulse set to 2048 clock cycles */
#define HAL_WATCHDOG_PULSE_2048     0x7
  
/** Reset time set to 2 clock cycles */
#define HAL_WATCHDOG_RESET_2        0x0
/** Reset time set to 4 clock cycles */
#define HAL_WATCHDOG_RESET_4        0x1
/** Reset time set to 8 clock cycles */
#define HAL_WATCHDOG_RESET_8        0x2
/** Reset time set to 16 clock cycles */
#define HAL_WATCHDOG_RESET_16       0x3
/** Reset time set to 32 clock cycles */
#define HAL_WATCHDOG_RESET_32       0x4
/** Reset time set to 64 clock cycles */
#define HAL_WATCHDOG_RESET_64       0x5
/** Reset time set to 128 clock cycles */
#define HAL_WATCHDOG_RESET_128      0x6
/** Reset time set to 256 clock cycles */
#define HAL_WATCHDOG_RESET_256      0x7

/** This state indicator is raised while the timer is counting */
#define HAL_WATCHDOG_STATUS_ARMED        (1<<3)
/** This state indicator is raised when the timer has expired */
#define HAL_WATCHDOG_STATUS_EXPIRED      (1<<10)
/** This state indicator is raised when the external pulse occurs */
#define HAL_WATCHDOG_STATUS_EXT_PULSE    (1<<11)

/** The minimum value of the timeout */ 
#define HAL_WATCHDOG_TIMEOUT_MIN  0xFF
/** The maximum value of the timeout */ 
#define HAL_WATCHDOG_TIMEOUT_MAX  0xFFFF


/*----------------------------------------------------------------------------
 * Configuration Structure
 */

/** The configuration structure is used to set up a Watchdog Timer */
typedef struct HAL_WATCHDOG_CONFIG
{
    /** Watchdog Timer mode, can be an OR combinaison of :
     * @li #HAL_WATCHDOG_MODE_NONE 
     * @li #HAL_WATCHDOG_MODE_RESET  
     * @li #HAL_WATCHDOG_MODE_EXT_PULSE 
     */
    unsigned int mode;      
    
    /** Prescaler value, this parameter is used to divide the clock by : 
     *  @li #HAL_WATCHDOG_CLOCK_4
     *  @li #HAL_WATCHDOG_CLOCK_8
     *  @li #HAL_WATCHDOG_CLOCK_32
     *  @li #HAL_WATCHDOG_CLOCK_64
     *  @li #HAL_WATCHDOG_CLOCK_256
     *  @li #HAL_WATCHDOG_CLOCK_512
     *  @li #HAL_WATCHDOG_CLOCK_2048
     *  @li #HAL_WATCHDOG_CLOCK_4096
     */
    unsigned int clock;
    
    /** The timer initial countdown value. */
    unsigned int timeout;   
    
    /** Time of external pulse in clock cycles : 
     * @li #HAL_WATCHDOG_PULSE_8
     * @li #HAL_WATCHDOG_PULSE_16
     * @li #HAL_WATCHDOG_PULSE_32
     * @li #HAL_WATCHDOG_PULSE_64
     * @li #HAL_WATCHDOG_PULSE_128
     * @li #HAL_WATCHDOG_PULSE_512
     * @li #HAL_WATCHDOG_PULSE_1024
     * @li #HAL_WATCHDOG_PULSE_2048
     */
    unsigned int pulse;
    
    /** Time of internal reset in clock cycles : 
     * @li #HAL_WATCHDOG_RESET_2
     * @li #HAL_WATCHDOG_RESET_4
     * @li #HAL_WATCHDOG_RESET_8
     * @li #HAL_WATCHDOG_RESET_16
     * @li #HAL_WATCHDOG_RESET_32
     * @li #HAL_WATCHDOG_RESET_64
     * @li #HAL_WATCHDOG_RESET_128
     * @li #HAL_WATCHDOG_RESET_256
     */
    unsigned int reset;
    
} HAL_WATCHDOG_CONFIG;


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
 
#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures the Watchdog Timer. 
 * 
 * @warning The watchdog shares its clock and hardware reset with the 
 * PWM and timer modules. It is not actually reset nor activated 
 * if any of these devices is already in use. 
 * 
 * @param[in] params        Pointer on a watchdog timer configuration structure 
 *                          allocated and filled by the caller. 
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_watchdog_init( HAL_WATCHDOG_CONFIG *params );

/**
 * The function disables the Watchdog Timer. 
 *  
 * @warning The watchdog shares its clock and hardware reset with the 
 * PWM and timer modules. It is not actually disabled 
 * if any of these devices is still in use. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_watchdog_shutdown( void );

/**
 * The function is used to set up the Watchdog Timer. 
 * 
 * @param[in] params        Pointer on a watchdog timer configuration structure 
 *                          allocated and filled by the caller. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_watchdog_set_config( HAL_WATCHDOG_CONFIG *params );

/**
 * The function starts/restarts the Watchdog Timer. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */ 
int hal_watchdog_rearm( void );

/**
 * The function stops the Watchdog Timer. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *  
 */
int hal_watchdog_disarm( void );

/**
 * The function retrieves the current value of the Watchdog Timer. 
 * 
 * @param[out] value        Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current value of 
 *                          the counter. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_watchdog_read( int *value );

/**
 * The function retrieves the current Watchdog Timer state. 
 * 
 * @param[out] status       Pointer allocated by the caller and filled by the 
 *                          function with the current device state. It is an
 *                          orred combination of the following values: 
 *                          \li #HAL_WATCHDOG_STATUS_ARMED 
 *                          \li #HAL_WATCHDOG_STATUS_EXPIRED 
 *                          \li #HAL_WATCHDOG_STATUS_EXT_PULSE 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_watchdog_get_status( int *status );

/**
 * The function performs Watchdog Timer specific control functions.
 * 
 * @param[in] cmd           Requested control function. 
 * 
 * @param[in,out] data      Points to a buffer that contains any data required 
 *                          for the given control function or receives data 
 *                          from that function. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_watchdog_ioctl( int cmd, void *data );

/**
 * The function registers an interrupt handler for the overflow event. 
 * 
 * @param[in] handler       Pointer on the interrupt handler function. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_watchdog_attach( void (*handler)( void ) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * the overflow event. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_watchdog_init() 
 *                          first. 
 * @retval -ERR_ALREADY     Operation already in progress 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_watchdog_detach( void );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_watchdog_handler_t)( void );

__hal_defunc1(hal_watchdog_init, HAL_WATCHDOG_CONFIG *, params);
__hal_defunc0(hal_watchdog_shutdown, void);
__hal_defunc1(hal_watchdog_set_config, HAL_WATCHDOG_CONFIG *, params);
__hal_defunc0(hal_watchdog_rearm, void);
__hal_defunc0(hal_watchdog_disarm, void);
__hal_defunc1(hal_watchdog_read, int *, value);
__hal_defunc1(hal_watchdog_get_status, int *, status);
__hal_defunc1(hal_watchdog_attach, hal_watchdog_handler_t, handler);
__hal_defunc0(hal_watchdog_detach, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* HAL_USIP_WATCHDOG_H */
	

