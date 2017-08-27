/*============================================================================
 *
 *      hal_apm.h
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
 * Contributors: Arnaud Ferir 
 * Date:          
 * Purpose:       
 * Description:
 * 
 *==========================================================================*/
#ifndef HAL_USIP_APM_H
#define HAL_USIP_APM_H

/**
 *  
 * @defgroup HAL_APM HAL Advanced Power Manager
 * 
 * This chapter contains descriptions of the functions available to access the 
 * Advanced Power Manager. 
 * 
 * @section hal_apm Overview 
 * 
 * USIP® Professional provides an Advanced Power Manager to reduce power 
 * consumption according to the application requirements. 
 * 
 * \b Features
 * 
 * \li System clock frequency management 
 * \li System operating mode management 
 * \li Peripheral operating mode management 
 * \li Peripheral reset management 
 * 
 * @section clock System clock frequency 
 * 
 * The power consumption of synchronous design is related to the system clock 
 * frequency. The system controller can change the system clock frequency to 
 * reduce the power consumption. 
 * 
 * At hardware reset the system frequency is set to 12MHz. The frequency may 
 * also be changed to 24MHz, 48MHz or 96MHz. 
 * 
 * \note The configuration of some HAL modules is depending on the system 
 * clock frequency. Any clock frequency change should be followed by a 
 * re-configuration of these modules. 
 * 
 * @section smode System operating mode 
 * 
 * The system operating mode can always switch from normal mode to idle mode 
 * (or from normal to idle). I t can also be changed to power down. Once the 
 * system mode is changed to power down, it cannot be changed until a hardware 
 * reset occurs. 
 * 
 * At hardware reset the system mode is always set to normal once the frequency 
 * selection mechanism is over. 
 * 
 * In normal mode all peripherals can be individually activated or powered 
 * down. 
 * 
 * In idle mode all peripherals are powered down except a set of selected ones. 
 * Note that switching to idle mode does force the Core to low power mode. 
 * 
 * @section dmode Peripherals operating mode 
 * 
 * The system controller can stop or (re-)start the system clock on any 
 * peripheral independently from the others. So any peripheral may be 
 * initialized then freezed during peripheral unuse time. 
 * 
 * Peripherals are said to be activated or power down. 
 * 
 * @section reset Peripherals reset 
 * 
 * The software can perform a hardware reset of any peripheral independently 
 * from the others. 
 * 
 * 
 * @addtogroup HAL_APM
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** Identifier associated to the UART device with IrDa capabilities */
#define HAL_APM_UART_0                  (1<<0)
#define HAL_APM_IRDA                    HAL_APM_UART_0                  

/** Identifier associated to the UART device with Modem capabilities */
#define HAL_APM_UART_1                 (1<<1)
#define HAL_APM_MODEM                  HAL_APM_UART_1

/** Identifier associated to the SPI Interface */
#define HAL_APM_SPI                   (1<<2)

/** Identifier associated to the DMA device */
#define HAL_APM_DMA                   (1<<3)

/** Identifier associated to the Keyboard Controller */
#define HAL_APM_KEYBOARD              (1<<4)

/** Identifier associated to the Display Interface */
#define HAL_APM_DISPLAY               (1<<5)

/** Identifier associated to the Timer devices */
#define HAL_APM_TIMER                 (1<<6)

/** Identifier associated to the External Memory Controler */
#define HAL_APM_MEMC                  (1<<7)

/** Identifier associated to the Real-Time Clock 
 * \note This is the same identifier than the Sensors Inputs and Secured 
 * Storage modules */
#define HAL_APM_RTC                   (1<<9)

/** Identifier associated to the Smart Card Slot Interface 0 */
#define HAL_APM_SMARTCARD_0           (1<<10)

/** Identifier associated to the Smart Card Slot Interface 1 */
#define HAL_APM_SMARTCARD_1           (1<<11)

/** Identifier associated to the Smart Card Slot Interface 2 */
#define HAL_APM_SMARTCARD_2           (1<<12)

/** Identifier associated to the Thermal Printer, GPIO, PS2 and Parallel 
 *  interfaces */
#define HAL_APM_GPPTP                 (1<<13)

/** Identifier associated to the I2C Interface */
#define HAL_APM_I2C                   (1<<15)

/** Identifier associated to the USB OTG */
#define HAL_APM_USB                   (1<<19)

/** Identifier associated to the UART Interface 2 */
#define HAL_APM_UART_2                (1<<22)

/** Identifier associated to the UART Interface 3 */
#define HAL_APM_UART_3                (1<<23)

/** Identifier associated to the MSR Interface */
#define HAL_APM_MSR                   (1<<24)

/** Identifier associated to the Smart Card 4MHz Clock 0 */
#define HAL_APM_CLOCK_SMARTCARD_0     (1<<25)

/** Identifier associated to the Smart Card 4MHz Clock 1 */
#define HAL_APM_CLOCK_SMARTCARD_1     (1<<26)

/** Identifier associated to the Smart Card 4MHz Clock 2 */
#define HAL_APM_CLOCK_SMARTCARD_2     (1<<27)

/** Identifier associated to the USB 48MHz Clock */
#define HAL_APM_CLOCK_USB             (1<<28)

/** Identifier associated to the ADC Interface */
#define HAL_APM_ADC                   (1<<29)

/** Identifier associated to the entire System */
#define HAL_APM_SYSTEM                (1<<31)


/** Power Policy Mode: Idle 
 *  Selected peripherals in Idle Mode Register are enabled. Usually dedicated 
 *  to safe power mode */
#define HAL_APM_MODE_IDLE         1
/** Power Policy Mode: Active 
 *  Selected peripherals in Active Mode are enabled. Usually dedicated to non 
 *  restrictive power consumption usage */
#define HAL_APM_MODE_NORMAL       2
/** Power Policy Mode: Change frequency 
 *  Transition mode that permits to achieve a system frequency change */
#define HAL_APM_MODE_CHANGE_FREQ  3


/** Device Power Policy Mode: Power down */
#define HAL_APM_DEVICE_MODE_POWER_DOWN   4
/** Device Power Policy Mode: Active 
 *  Selected peripherals are enabled in Active Mode Register. Usually dedicated 
 *  to non restrictive power consumption usage */
#define HAL_APM_DEVICE_MODE_ACTIVE       5


/** Power down wake up: USB Resume */
#define HAL_APM_USB_RESUME        (1<<0)
/** Power down wake up: WAKEUP Pin */
#define HAL_APM_EXT_WAKEUP        (1<<1)

/** Power down wakeup polarity: wake up if full speed resume condition detected 
 *  on USB */
#define HAL_APM_USB_RESUME_FS           (0<<0)
/** Power down wakeup polarity: wake up if low speed resume condition detected 
 *  on USB */
#define HAL_APM_USB_RESUME_LS           (1<<0)
/** Power down wakeup polarity: wake up if low level detected on WAKEUP Pin */
#define HAL_APM_EXT_WAKEUP_LOW          (0<<1)
/** Power down wakeup polarity: wake up if high level detected on WAKEUP Pin */
#define HAL_APM_EXT_WAKEUP_HIGH         (1<<1)


/** System Clock Frequency: 12MHz */
#define HAL_APM_CLOCK_FREQ_12MHz    12000000
/** System Clock Frequency: 24MHz */
#define HAL_APM_CLOCK_FREQ_24MHz    24000000
/** System Clock Frequency: 48MHz */
#define HAL_APM_CLOCK_FREQ_48MHz    48000000
/** System Clock Frequency: 96MHz */
#define HAL_APM_CLOCK_FREQ_96MHz    96000000

/** Number of system clock frequencies */
#define HAL_APM_CLOCK_FREQ_COUNT    4

/** System Clock Frequency: invalid */
#define HAL_APM_CLOCK_FREQ_INVALID      -1

/** This command is used to set the CPU clock frequency to 12 MHz */
#define HAL_APM_IOCTL_SOFT_SET_CPU_TO_12MHz     0
/** This command is used to set the CPU clock frequency to 24 MHz */
#define HAL_APM_IOCTL_SOFT_SET_CPU_TO_24MHz     1
/** This command is used to set the CPU clock frequency to 48 MHz */
#define HAL_APM_IOCTL_SOFT_SET_CPU_TO_48MHz     2
/** This command is used to set the CPU clock frequency to 96 MHz */
#define HAL_APM_IOCTL_SOFT_SET_CPU_TO_96MHz     3

/** This event indicator is raised when a word is received */ 
#define HAL_APM_EVENT_FREQ_CHANGED       0
/** This event indicator is raised when a word is send */ 
#define HAL_APM_EVENT_USB_OVERFLOW       1

/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/
        
#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes the Advanced Power Manager. 
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_init( void );

/**
 * The function terminates the use of the Advanced Power Manager. 
 *  
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_shutdown( void );

/** 
 * The function sets the system's clock frequency. 
 * 
 * @param[in] freq          New value of the clock frequency. Possible values 
 *                          are: 
 *                          \li #HAL_APM_CLOCK_FREQ_12MHz 
 *                          \li #HAL_APM_CLOCK_FREQ_24MHz 
 *                          \li #HAL_APM_CLOCK_FREQ_48MHz 
 *                          \li #HAL_APM_CLOCK_FREQ_96MHz 
 * 
 * \note The function uses the frequency toggle interrupt. 
 * 
 * \note The function includes the re-initialization of the HAL internal flash 
 * memory module. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_apm_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_set_clock_frequency( unsigned int freq );
 
/** 
 * The function is used to retrieve the current system's clock frequency. 
 * 
 * @param[out] freq         Pointer on a variable allocated by the caller and 
 *                          filled by the function with the value of the clock 
 *                          frequency. Possible values are: 
 *                          \li #HAL_APM_CLOCK_FREQ_12MHz 
 *                          \li #HAL_APM_CLOCK_FREQ_24MHz 
 *                          \li #HAL_APM_CLOCK_FREQ_48MHz 
 *                          \li #HAL_APM_CLOCK_FREQ_96MHz 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_get_clock_frequency( unsigned int *freq );

/** 
 * The function changes the system's global operating mode to the utra low power
 * consumption. 
 * 
 * @param[in] event         Wake-up events. Orred value of: 
 *                              \li #HAL_APM_USB_RESUME 
 *                              \li #HAL_APM_EXT_WAKEUP 
 *
 * @param[in] polarity      Wake-up event polarity. Orred value of: 
 *                              \li #HAL_APM_USB_RESUME_FS 
 *                              \li #HAL_APM_USB_RESUME_LS 
 *                              \li #HAL_APM_EXT_WAKEUP_LOW 
 *                              \li #HAL_APM_EXT_WAKEUP_HIGH 
 *
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_set_cpu_mode_ultra_low_power( unsigned int event,
                                          unsigned int polarity );

/** 
 * The function changes the system's global operating mode to normal. 
 *
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_set_cpu_mode_normal( void );

/** 
 * The function changes the system's global operating mode to idle. 
 * 
 * @param[in] devmask       Orred value of all devices that must be powered 
 *                          during idle mode 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_set_cpu_mode_idle( unsigned int devmask );

/** 
 * The function is used to retrieve the system's global operating mode.
 *
 * @param[in] mode          Pointer on a variable allocated by the caller and 
 *                          filled by the function with the system's global 
 *                          operating mode. Possible values are: 
 *                          \li #HAL_APM_MODE_IDLE 
 *                          \li #HAL_APM_MODE_NORMAL 
 *                          \li #HAL_APM_MODE_CHANGE_FREQ 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_get_cpu_mode( unsigned int *mode );

/** 
 * The function is used to change a device's power policy mode. 
 * 
 * @param[in] devnum        Device identifier. Possible values are: 
 *                          \li #HAL_APM_UART_0 
 *                          \li #HAL_APM_UART_1 
 *                          \li #HAL_APM_SPI 
 *                          \li #HAL_APM_DMA 
 *                          \li #HAL_APM_KEYBOARD 
 *                          \li #HAL_APM_DISPLAY 
 *                          \li #HAL_APM_TIMER 
 *                          \li #HAL_APM_MEMC 
 *                          \li #HAL_APM_SMARTCARD_0 
 *                          \li #HAL_APM_SMARTCARD_1 
 *                          \li #HAL_APM_SMARTCARD_2 
 *                          \li #HAL_APM_GPPTP 
 *                          \li #HAL_APM_I2C 
 *                          \li #HAL_APM_USB 
 *                          \li #HAL_APM_UART_2 
 *                          \li #HAL_APM_UART_3 
 *                          \li #HAL_APM_MSR 
 *                          \li #HAL_APM_CLOCK_SMARTCARD_0 
 *                          \li #HAL_APM_CLOCK_SMARTCARD_1 
 *                          \li #HAL_APM_CLOCK_SMARTCARD_2 
 *                          \li #HAL_APM_CLOCK_USB 
 *                          \li #HAL_APM_ADC 
 * 
 * @param[in] mode          Power mode to set. Possible values are: 
 *                          \li #HAL_APM_DEVICE_MODE_POWER_DOWN 
 *                          \li #HAL_APM_DEVICE_MODE_ACTIVE 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_set_device_mode( unsigned int devnum, unsigned int mode );

/** 
 * The function is used to retrieve a device's power policy mode.
 *
 * @param[in] devnum        Device identifier. Possible values are: 
 *                          \li #HAL_APM_UART_0 
 *                          \li #HAL_APM_UART_1 
 *                          \li #HAL_APM_SPI 
 *                          \li #HAL_APM_DMA 
 *                          \li #HAL_APM_KEYBOARD 
 *                          \li #HAL_APM_DISPLAY 
 *                          \li #HAL_APM_TIMER 
 *                          \li #HAL_APM_MEMC 
 *                          \li #HAL_APM_SMARTCARD_0 
 *                          \li #HAL_APM_SMARTCARD_1 
 *                          \li #HAL_APM_SMARTCARD_2 
 *                          \li #HAL_APM_GPPTP 
 *                          \li #HAL_APM_I2C 
 *                          \li #HAL_APM_USB 
 *                          \li #HAL_APM_UART_2 
 *                          \li #HAL_APM_UART_3 
 *                          \li #HAL_APM_MSR 
 *                          \li #HAL_APM_CLOCK_SMARTCARD_0 
 *                          \li #HAL_APM_CLOCK_SMARTCARD_1 
 *                          \li #HAL_APM_CLOCK_SMARTCARD_2 
 *                          \li #HAL_APM_CLOCK_USB 
 *                          \li #HAL_APM_ADC 
 * 
 * @param[in] mode          Pointer on a variable allocated by the caller and 
 *                          filled by the function with the power mode of the 
 *                          device. Possible values are: 
 *                          \li #HAL_APM_DEVICE_MODE_POWER_DOWN 
 *                          \li #HAL_APM_DEVICE_MODE_ACTIVE 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_get_device_mode( unsigned int devnum, unsigned int *mode );

/**
 * The function resets a specific device. 
 *  
 * @param[in] devnum        Device identifier. Possible values are: 
 *                          \li #HAL_APM_UART_0 
 *                          \li #HAL_APM_UART_1 
 *                          \li #HAL_APM_SPI 
 *                          \li #HAL_APM_DMA 
 *                          \li #HAL_APM_KEYBOARD 
 *                          \li #HAL_APM_DISPLAY 
 *                          \li #HAL_APM_TIMER 
 *                          \li #HAL_APM_MEMC 
 *                          \li #HAL_APM_RTC 
 *                          \li #HAL_APM_SMARTCARD_0 
 *                          \li #HAL_APM_SMARTCARD_1 
 *                          \li #HAL_APM_SMARTCARD_2  
 *                          \li #HAL_APM_GPPTP 
 *                          \li #HAL_APM_I2C 
 *                          \li #HAL_APM_USB 
 *                          \li #HAL_APM_UART_2 
 *                          \li #HAL_APM_UART_3 
 *                          \li #HAL_APM_MSR 
 *                          \li #HAL_APM_ADC 
 *                          \li #HAL_APM_SYSTEM 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_reset_device( unsigned int devnum );

/**
 * The function registers an interrupt handler for a type of event 
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_APM_EVENT_FREQ_CHANGED 
 *                          \li #HAL_APM_EVENT_USB_OVERFLOW 
 * 
 * @param[in] handler       Pointer to the interrupt handler function 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_apm_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_attach( int event, void (*handler)(void) );

/**
 * The function unregisters an interrupt handler for a type of event 
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_APM_EVENT_FREQ_CHANGED 
 *                          \li #HAL_APM_EVENT_USB_OVERFLOW 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_apm_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_detach( int event );

/**
 * The function performs Power Manager specific control functions. 
 * 
 * @param[in] cmd           Requested control function. It can be one of the 
 *                          following values: 
 *                          \li #HAL_APM_IOCTL_SOFT_SET_CPU_TO_12MHz 
 *                          \li #HAL_APM_IOCTL_SOFT_SET_CPU_TO_24MHz 
 *                          \li #HAL_APM_IOCTL_SOFT_SET_CPU_TO_48MHz 
 *                          \li #HAL_APM_IOCTL_SOFT_SET_CPU_TO_96MHz 
 * 
 * @param[in,out] data      Points on a variable allocated by the caller that 
 *                          contains any data required for the given control 
 *                          function or receives data from that function. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NOTTY       Inappropriate ioctl for device   
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_apm_ioctl( int cmd, void *data );

/**
 * The function is the interrupt service routine function for the 
 * Advanced Power Manager. 
 */
void hal_apm_isr( void );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_apm_handler_t)(void);

__hal_defunc0(hal_apm_init, void);
__hal_defunc0(hal_apm_shutdown,void);
__hal_defunc1(hal_apm_set_clock_frequency, unsigned int, freq);
__hal_defunc1(hal_apm_get_clock_frequency, unsigned int *,freq);
__hal_defunc2(hal_apm_set_cpu_mode_ultra_low_power, unsigned int, event, unsigned int, polarity);
__hal_defunc0(hal_apm_set_cpu_mode_normal, void);
__hal_defunc1(hal_apm_set_cpu_mode_idle, unsigned int, devmask);
__hal_defunc1(hal_apm_get_cpu_mode, unsigned int *, mode);
__hal_defunc2(hal_apm_set_device_mode, unsigned int, devnum, unsigned int, mode);
__hal_defunc2(hal_apm_get_device_mode, unsigned int, devnum, unsigned int *, mode);
__hal_defunc1(hal_apm_reset_device, unsigned int, devnum);
__hal_defunc2(hal_apm_attach, int, event, hal_apm_handler_t, handler);
__hal_defunc1(hal_apm_detach, int, event);
__hal_defunc2(hal_apm_ioctl, int, cmd, void *, data);

__hal_deisr(hal_apm_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */


/** @} */


#ifdef __cplusplus
}
#endif

#endif /* HAL_USIP_APM_H */

