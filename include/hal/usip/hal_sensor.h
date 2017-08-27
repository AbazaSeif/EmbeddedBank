/*============================================================================
 *
 *      hal_sensor.h
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
 * Description:
 * 
 *==========================================================================*/
#ifndef HAL_USIP_SENSOR_H
#define HAL_USIP_SENSOR_H

   
/**
 *  
 * @defgroup HAL_SENSOR HAL Sensor Inputs 
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the Internal/External Sensor Inputs. 
 * 
 * @section hal_sensor Overview 
 * 
 * USIP® Professional provides security mechanisms that may be connected to 
 * external sensors responsible of the environment integrity. These sensors 
 * must provide a digital output signal. 
 * 
 * \attention The signal provided by sensors must be ready before locking the 
 * configuration and starting the external sensors watching. No changes in 
 * configuration are allowed after locking. 
 * 
 * \b Features 
 * 
 * - Up to 12 external sensor inputs 
 * - Fault digital level selectable for each input 
 * - Setup locked by hardware
 * - Active in all operating mode 
 * 
 * \warning The External Sensor Inputs and the USIP® Professional core work in 
 * different clock domains. The read and write operations in registers of this 
 * module may be temporarily locked. 
 * 
 * @addtogroup HAL_SENSOR
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** This indicator should be used to access the RTC Power Sensor or to retrieve 
 * its state */
#define HAL_SENSOR_INTERNAL_POWRTC  (1<<1)
/** This indicator should be used to access the RTC Frequency Sensor or to 
 * retrieve its state */
#define HAL_SENSOR_INTERNAL_FREQRTC (1<<2)
/** This indicator should be used to access the Temperature Sensor or to 
 * retrieve its state */
#define HAL_SENSOR_INTERNAL_TEMP    (1<<3)
/** This indicator should be used to access the Shield Sensor or to retrieve 
 * its state */
#define HAL_SENSOR_INTERNAL_SHIELD  (1<<4)

/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL0        (1<<5)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL1        (1<<6)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL2        (1<<7)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL3        (1<<8)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL4        (1<<9)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL5        (1<<10)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL6        (1<<11)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL7        (1<<12)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL8        (1<<13)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL9        (1<<14)
/** This indicator should be used to access the External Sensor 0 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL10       (1<<15)
/** This indicator should be used to access the External Sensor 11 or to get 
 * its state */
#define HAL_SENSOR_EXTERNAL11       (1<<16)

/** This indicator should be used to configure the External Sensors as dynamic 
 * sensors */
#define HAL_SENSOR_EXTERNAL_DYNAMIC (1<<17)

/** This indicator is raised when the Internal Sensor configuration is locked */
#define HAL_SENSOR_INTERNAL_LOCK                 (1<<30)
/** This indicator should be used to lock the External Sensors and is is raised 
 * when the External Sensor configuration is locked  */
#define HAL_SENSOR_EXTERNAL_LOCK                 (1<<31)

/*------------------------------------------------------------------------------
   Control Enumeration
*/

/** The control enumeration defines the type of control on the sensors
 */
typedef enum {
    /** Write into ESIALR: External Sensor Input Assertion Level register */
    HAL_SENSOR_IOCTL_WRITE_ESIALR,
    /** Write into ISIER: Internal Sensor Interrupt Enable register */
    HAL_SENSOR_IOCTL_WRITE_ISIER,
    /** Write into ESIER: External Sensor Input Enable register */
    HAL_SENSOR_IOCTL_WRITE_ESIER,
    /** Read from ESIALR: External Sensor Input Assertion Level register */
    HAL_SENSOR_IOCTL_READ_ESIALR,
    /** Read from ISIER: Internal Sensor Interrupt Enable register */
    HAL_SENSOR_IOCTL_READ_ISIER,
    /** Read from ISISR: Internal Sensor Interrupt Status register */
    HAL_SENSOR_IOCTL_READ_ISISR,
    /** Read from ESIER: External Sensor Input Enable register */
    HAL_SENSOR_IOCTL_READ_ESIER,
    /** 
     * Adjust the delay (µs) in the Internal Sensors enabling sequence: 
     *  -# enable the power supply 
     *  -# wait until the sensor is stable 
     *  -# enable the sensor monitoring 
     * 
     * Default value: 10000 µs 
     */
    HAL_SENSOR_IOCTL_SET_DELAY

} HAL_SENSOR_CONTROL ;


/*----------------------------------------------------------------------------
 * Configuration structure
 */

/** 
 * The configuration structure used to set up the Internal and External Sensors 
 * 
 */
typedef struct
{
    /** 
     * External Sensors Configuration\n
     * One of: 
     *  \li For Static Sensors: Set bit(s) 5 to 16 to select high level 
     *  activation for external sensor(s) 1 to 11 resp. 
     *  \li For Dynamic Sensors: #HAL_SENSOR_EXTERNAL_DYNAMIC
     */
    unsigned int external;

    /** 
     * Internal and External Sensors to be activated\n 
     * Orred combination of: 
     *  \li #HAL_SENSOR_INTERNAL_POWRTC 
     *  \li #HAL_SENSOR_INTERNAL_FREQRTC 
     *  \li #HAL_SENSOR_INTERNAL_TEMP 
     *  \li #HAL_SENSOR_INTERNAL_SHIELD 
     *  \li #HAL_SENSOR_EXTERNAL0 
     *  \li ...
     *  \li #HAL_SENSOR_EXTERNAL11 
     * 
     * No Sensors activated if 0 
     */
    unsigned int active;

    /**
     * Internal and External Sensor configuration Lock\n
     * Orred combination of: 
     *  \li #HAL_SENSOR_INTERNAL_LOCK 
     *  \li #HAL_SENSOR_EXTERNAL_LOCK 
     * 
     * No Sensor locked if 0 
     */
    unsigned int lock;
    
} HAL_SENSOR_CONFIG;


/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function configures the Internal/External Sensors watching. 
 * 
 * @param[in] params        Points on a configuration structure allocated and 
 *                          filled by the caller. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. Clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_sensor_set_config( HAL_SENSOR_CONFIG *params );


/**
 * The function retrieves the current state of the Internal/External Sensors. 
 * 
 * @param[in] status        Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the device. It is an orred combination of the 
 *                          following values: 
 *                          \li #HAL_SENSOR_INTERNAL_POWRTC 
 *                          \li #HAL_SENSOR_INTERNAL_FREQRTC 
 *                          \li #HAL_SENSOR_INTERNAL_TEMP 
 *                          \li #HAL_SENSOR_INTERNAL_SHIELD 
 *                          \li bits 5 to 16 reflect the state of the external 
 *                          sensors 0 to 11: bit raised when the corresponding 
 *                          sensor is activated. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. Clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_sensor_get_status( unsigned int *status );

/**
 * The function performs Internal/External Sensors specific control functions. 
 * 
 * @param[in] control       The control function to be performed. 
 * 
 * @param[in,out] data      Pointer on a buffer that contains any data required 
 *                          for the given control function or receives data 
 *                          from that function. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_INTR        Operation interrupted 
 * @retval -ERR_TIMEDOUT    Operation timed out. Clock may be missing. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_sensor_ioctl( HAL_SENSOR_CONTROL control, void *data );

#else

#include <hal/usip/hal_sys.h>

__hal_defunc1(hal_sensor_set_config, HAL_SENSOR_CONFIG *, params);
__hal_defunc1(hal_sensor_get_status, unsigned int *, status);
__hal_defunc2(hal_sensor_ioctl, HAL_SENSOR_CONTROL, control, void *, data);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* HAL_USIP_SENSOR_H */

