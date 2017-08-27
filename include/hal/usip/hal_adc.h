/*============================================================================
 *
 *      hal_adc.h
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
 * Description:  This file contains the ADC Controller generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_ADC_H
#define HAL_USIP_ADC_H

/**
 *  
 * @defgroup HAL_ADC HAL ADC Controller
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the ADC Controller (Analog to Digital 
 * Converter).
 * 
 * @section Overview Overview 
 * 
 * \li 6 input channels selected through an analog multiplexer 
 * \li From 2 to 10-bit resolution conversion, selected on the fly 
 * \li Burst mode 
 * \li Maximum conversion rate 400 k samples/s for 10-bit resolution 
 * \li Power down mode performing minimal power dissipation 
 * \li Internal power management to switch off unused circuitry between 
 * conversion cycles 
 * \li No start-up cycles, no power down/power up recovery time 
 * \li Mixed reference voltage inputs 
 * 
 * @addtogroup HAL_ADC
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/* ADC status */
/** This status indicator is raised when the analog part of the converter is 
 *  off */
#define HAL_ADC_STATUS_POWER_DOWN   0x0010
/** This status indicator is raised when a converted data is available */
#define HAL_ADC_STATUS_END          0x4000

/** This configuration must be chosen to select the reference voltage 0 */
#define HAL_ADC_SEL_VREF0       0
/** This configuration must be chosen to select the reference voltage 1 */
#define HAL_ADC_SEL_VREF1       1

/** This configuration must be chosen to select the normal mode */
#define HAL_ADC_MODE_NORMAL     0
/** This configuration must be chosen to select the burst mode */
#define HAL_ADC_MODE_BURST      1

/** This configuration is the minimal resolution for normal mode */
#define HAL_ADC_RESOLUTION_MIN  2
/** This configuration is the maximal resolution for normal mode */
#define HAL_ADC_RESOLUTION_MAX  10

/** \showinitializer This configuration is the minimal channel number */
#define HAL_ADC_CHANNEL_MIN  0
/** \showinitializer This configuration is the maximal channel number */
#define HAL_ADC_CHANNEL_MAX  5


/*------------------------------------------------------------------------------
   Control Enumeration
*/

/** The control enumeration defines the type of control on the ADC
 */
typedef enum {
	/** Enter power down mode */
	HAL_ADC_IOCTL_SET_POWER_DOWN,
	/** Finish power down mode */
	HAL_ADC_IOCTL_CLEAR_POWER_DOWN,
	/** Select reference voltage 0 */
	HAL_ADC_IOCTL_SET_SELREF0,
	/** Select reference voltage 1 */
	HAL_ADC_IOCTL_SET_SELREF1,
	/** Start a conversion */
	HAL_ADC_IOCTL_START,
	/** Stop the next burst conversion */
	HAL_ADC_IOCTL_STOP_BURST,
	/** Select burst mode */
	HAL_ADC_IOCTL_SET_BURST_MODE,
	/** Unselect burst mode */
	HAL_ADC_IOCTL_CLEAR_BURST_MODE,
	/** Select the input channel */
	HAL_ADC_IOCTL_SELECT_CHANNEL,
	/** Set the conversion resolution in normal mode */
	HAL_ADC_IOCTL_SET_RESOLUTION

} HAL_ADC_CONTROL ;


/*----------------------------------------------------------------------------
 * Configuration structure
 */

/** The configuration structure used to set up the ADC Controller */
typedef struct HAL_ADC_CONFIG {    
    
    /** Specify the reference voltage 
     *  (#HAL_ADC_SEL_VREF0 or #HAL_ADC_SEL_VREF1 ) */
    unsigned int    vref;
    /** Specify the input channel to be converted (from #HAL_ADC_CHANNEL_MIN to 
     *  #HAL_ADC_CHANNEL_MAX) */
    unsigned int    channel;

    /** Specify the resolution from 2 to 9 bits (only if normal mode selected) */
    unsigned int    resolution;

    /** Specify the normal or burst mode 
     *  (#HAL_ADC_MODE_NORMAL or #HAL_ADC_MODE_BURST ) */
    unsigned int    mode;

} HAL_ADC_CONFIG;


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes and configures the ADC controller. The configuration
 * is contained into a dedicated structure. 
 *
 * @param[in] pparams       A pointer on ADC parameters structure allocated and 
 *                          filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_init( HAL_ADC_CONFIG *pparams );

/**
 * This function terminates the use of the ADC controller.
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_shutdown( void );

/**
 * The function configures the ADC controller. The configuration is contained
 * into a dedicated structure. 
 *
 * @param[in] pparams       A pointer on ADC parameters structure allocated and 
 *                          filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_adc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later. Current conversion not finished. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_set_config( HAL_ADC_CONFIG *pparams );

/** 
 * The function provides the current state of the ADC controller.
 * 
 * @param[out] pstatus      A pointer allocated by the caller that receives the 
 *                          current state of the ADC Controller. The value is an 
 *                          orred combination of the following state indicators: 
 *                          \li #HAL_ADC_STATUS_END
 *                          \li #HAL_ADC_STATUS_POWER_DOWN
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_adc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_get_status( int *pstatus );

/**
 * The function performs ADC Controller specific control functions.
 * 
 * @param[in] control        The control to be performed. 
 * 
 * @param[in] data          Any data required for the given control function.
 *                          \li for control #HAL_ADC_IOCTL_SET_RESOLUTION, data 
 *                          filled with the conversion 
 *                          resolution
 *                          \li for control #HAL_ADC_IOCTL_SELECT_CHANNEL, data 
 *                          filled with the channel number 
 *                          \note Parameter data not checked if not required 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_adc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later. Current conversion not finished. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_ioctl( HAL_ADC_CONTROL control, int data);

/**
 * The  function reads the conversion result accordings to the selected mode and
 * resolution.
 * 
 * @param[in] data          A pointer allocated by the caller that receives the 
 *                          conversion result. The LSBits are accurate
 *                          (for example if the conversion resolution is 5,
 *                          the 5 LSBits are accurate)
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_adc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later. Current conversion not finished. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_read(int *data);

/**
 * The function registers an interrupt handler for the ADC Controller interrupt.
 * 
 * @param[in] handler       A pointer on a user interrupt handler 
 * 
 * @retval -ERR_NO         No error
 * @retval -ERR_NXIO        Device not configured. Use hal_adc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later. Current conversion not finished. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_attach( void (*handler)(void) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * the ADC Controller interrupt.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_adc_init() first. 
 * @retval -ERR_AGAIN       Try again later. Current conversion not finished. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_adc_detach( void );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_adc_handler_t)(void);

__hal_defunc1(hal_adc_init, HAL_ADC_CONFIG *, pparams);
__hal_defunc0(hal_adc_shutdown, void);
__hal_defunc1(hal_adc_set_config, HAL_ADC_CONFIG *, pparams);
__hal_defunc1(hal_adc_get_status, int *, pstatus);
__hal_defunc2(hal_adc_ioctl, HAL_ADC_CONTROL, control, int, data);
__hal_defunc1(hal_adc_read, int *, data);
__hal_defunc1(hal_adc_attach, hal_adc_handler_t, handler);
__hal_defunc0(hal_adc_detach, void);

__hal_deisr(hal_adc_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* HAL_USIP_ADC_H */

