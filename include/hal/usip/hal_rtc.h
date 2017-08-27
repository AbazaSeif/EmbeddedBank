/*============================================================================
 *
 *      hal_rtc.h
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
#ifndef HAL_USIP_RTC_H
#define HAL_USIP_RTC_H	

/** 
 * 
 * @defgroup HAL_RTC HAL Real Time Clock 
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the Real-Time Clock (RTC).
 * 
 * @section Overview Overview 
 * 
 * USIP® Professional provides a real-time clock. This RTC is battery-powered 
 * and maintains the current time even when the system is turned off. The time 
 * values are for:
 * \li the year, month and date, 
 * \li the hours, minutes, seconds and milliseconds. 
 * 
 * \b Features
 * 
 * \li Independent of the main power 
 * \li Leap year management 
 * \li 1/8-second resolution 
 * \li Programmable alarm 
 * \li Interrupt 
 * 
 * \warning The RTC and the USIP® Professional core work in different clock 
 * domains. The read and write operations in registers of this module may be 
 * temporarily locked. 
 * 
 * @addtogroup HAL_RTC
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** This configuration indicates the 24 hours mode */
#define HAL_RTC_MODE_24H        0 

/** This configuration indicates the 12 hours mode with AM flag */
#define HAL_RTC_MODE_12H_AM     1

/** This configuration indicates the 12 hours mode with PM flag */
#define HAL_RTC_MODE_12H_PM     3

/** This state indicator is raised when the real_time clock is running. */
#define HAL_RTC_STATUS_RUNNING          (1<<0)
/** This state indicator is raised when the alarm is programmed. */
#define HAL_RTC_STATUS_ALARM_SET        (1<<1)
/** This state indicator is raised when the alarm is raised. */
#define HAL_RTC_STATUS_ALARM_RAISED     (1<<16)

/** This command is used to run the real-time counting */
#define HAL_RTC_IOCTL_RUN               1
/** This command is used to stop the real-time counting */
#define HAL_RTC_IOCTL_STOP              2

/*----------------------------------------------------------------------------
 * Configuration structure
 */

/** The configuration structure used to set up the Real-Time Clock and to 
 *  define a system time. */
typedef struct HAL_RTC_TIME
{
    /** Specify the year (allowed values between 0 and 4095) */
    unsigned int year;
    
    /** Specify the month (allowed values between 1 and 12) */
    unsigned int month;
    
    /** Specify the day of month (allowed values between 1 and 31) */  
    unsigned int mday;
    
    /** Specify the day of week (allowed values between 1 and 7, Sunday=1) */
    unsigned int wday;
    
    /** Specify the hours (allowed values between 0 and 23) */
    unsigned int hour;
    
    /** Specify the minutes (allowed values between 0 and 59) */
    unsigned int minute;
    
    /** Specify the seconds (allowed values between 0 and 59) */
    unsigned int second;
     
    /** Specify the milli-seconds (allowed values between 0 and 999) 
     * 
     * @note The millisecond parameter value is rounded down to the lowest 1/8 
     * second */
    unsigned int millis;
    
    /**
     * Mode and AM/PM Indicator: 
     * @li #HAL_RTC_MODE_24H 
     * @li #HAL_RTC_MODE_12H_AM 
     * @li #HAL_RTC_MODE_12H_PM
     */                            
    unsigned int mode;
    
} HAL_RTC_TIME;

/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes the Real-time Clock. 
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */       
int hal_rtc_init( void );
    
/**
 * This function retrieves the system time from the Real-Time Clock.
 * 
 * @param[in] time          Pointer on a RTC configuration structure allocated 
 *                          by the caller and filled by the function with the 
 *                          current system time. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rtc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rtc_get_time( HAL_RTC_TIME *time );

/**
 * The function sets up the system time in the Real-Time Clock.
 * 
 * @param[in] time          Pointer on a RTC configuration structure allocated 
 *                          and filled by the caller with the new system time. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rtc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 * @note The millisecond parameter value is rounded down to the lowest 1/8 
 * second 
 * 
 */  
int hal_rtc_set_time( HAL_RTC_TIME *time );

/**
 * The function programs an alarm in the Real-Time Clock 
 * 
 * @param[in] time          Pointer on a RTC configuration structure allocated 
 *                          and filled by the caller with the alarm time 
 * 
 * @note The fields year and month are not used 
 * 
 * @note The other fields should be filled with bad values to be disabled in 
 * Real Time Alarm Registers 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rtc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rtc_set_alarm( HAL_RTC_TIME *time );

/** 
 * The function retrieves the current state of the Real-Time Clock and clears 
 * the alarm if raised. 
 * 
 * @param[out] status       Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the RTC. It is an orred combination of the 
 *                          following values: 
 *                          \li #HAL_RTC_STATUS_RUNNING 
 *                          \li #HAL_RTC_STATUS_ALARM_SET
 *                          \li #HAL_RTC_STATUS_ALARM_RAISED
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rtc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rtc_get_status( int *status );

/**
 * The function performs Real-Time Clock specific control functions.
 * 
 * @param[in] cmd           The control function to be performed, that can be 
 *                          one of the following: 
 *                          \li #HAL_RTC_IOCTL_RUN 
 *                          \li #HAL_RTC_IOCTL_STOP 
 * 
 * @param[in,out] data      Pointer on a buffer that contains any data required 
 *                          for the given control function or receives data 
 *                          from that function. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rtc_init() first. 
 * @retval -ERR_NOTTY       Inappropriate ioctl for device 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rtc_ioctl( int cmd, void *data );

/**
 * The function registers an interrupt handler for the alarm raised event. 
 *  
 * @param[in] handler       Pointer to the interrupt handler function. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rtc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rtc_attach( void (*handler)( void ) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * the alarm raised event. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_rtc_init() first. 
 * @retval -ERR_ALREADY     Operation already in progress 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. RTC clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_rtc_detach( void );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_rtc_handler_t)( void );

__hal_defunc0(hal_rtc_init, void);
__hal_defunc1(hal_rtc_get_time, HAL_RTC_TIME *, time);
__hal_defunc1(hal_rtc_set_time, HAL_RTC_TIME *, time);
__hal_defunc1(hal_rtc_set_alarm, HAL_RTC_TIME *, time);
__hal_defunc1(hal_rtc_get_status, int *, status);
__hal_defunc2(hal_rtc_ioctl, int, cmd, void *, data);
__hal_defunc1(hal_rtc_attach, hal_rtc_handler_t, handler);
__hal_defunc0(hal_rtc_detach, void);

__hal_deisr(hal_rtc_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/**  @} */

#endif  /* HAL_USIP_RTC_H */
	

