/*============================================================================
 *
 *      hal_intr.h
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
#ifndef HAL_USIP_INTR_H
#define HAL_USIP_INTR_H	

/**
 *  
 * @defgroup HAL_INTR HAL Interrupt Controller
 * 
 * This chapter contains descriptions of the functions related to access the 
 * Interrupt Controller. 
 * 
 * @section Overview Overview 
 * 
 * The Interrupt Extension Controller gathers all the interruptions of the 
 * peripherals, gives them a priority level, and sends them to the Interrupt 
 * Controller of the MIPS core. 
 * 
 * \b Features 
 * 
 * \li 6 interrupt priority levels 
 * \li Two interrupt types: IRQ and NMI 
 * \li Peripheral interrupt management 
 * \li External interrupt management: priority and triggering 
 * 
 * @section IRQ IRQ Priorities 
 * 
 * The MIPS 4KSd core offers 6 interrupt levels. The peripheral interrupts are 
 * grouped by hardware but their priority levels are fixed by software. 
 * The exception is the external interrupt pin whose priority can be set up by 
 * software. 
 * 
 * The following table gives the priority of the USIP® Professional peripherals. 
 * 
 * \li Level 5 (highest): RNG, Core-Timer, DMA, GCR, Bus-Error 
 * \li Level 4: PWM/WDT/Timers 
 * \li Level 3: GPIO, USB, Parallel, Printer 
 * \li Level 2: UARTs, I2C, SPI 
 * \li Level 1: Flash controller, Smart Card, UMC 
 * \li Level 0 (Lowest): LCD, Keyboard, PS2, ADC, RTC, F2FD 
 * 
 * @addtogroup HAL_INTR
 * 
 * @{
 */
 

/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/
 
/** This constant is used to retrieve the number of priority level */ 
#define HAL_INTERRUPT_PRIORITY_LEVEL_NUM 6

/** Interrupt vector associated to the UART device with IrDa capabilities */
#define HAL_INTERRUPT_UART_0        0
#define HAL_INTERRUPT_IRDA          HAL_INTERRUPT_UART_0
/** Interrupt vector associated to the UART device with Modem capabilities */
#define HAL_INTERRUPT_UART_1        1
#define HAL_INTERRUPT_MODEM         HAL_INTERRUPT_UART_1
/** Interrupt vector associated to the SPI Interface */
#define HAL_INTERRUPT_SPI           2
/** Interrupt vector associated to the DMA device */
#define HAL_INTERRUPT_DMA           3
/** Interrupt vector associated to the Keyboard Controler */
#define HAL_INTERRUPT_KEYBOARD      4
/** Interrupt vector associated to the Display Interface */
#define HAL_INTERRUPT_DISPLAY       5
/** Interrupt vector associated to the Timer devices */
#define HAL_INTERRUPT_TIMER         6
/** Interrupt vector associated to the External Memory Controler */
#define HAL_INTERRUPT_MEMC          7
/** Interrupt vector associated to the Thermal Printer Interface */
#define HAL_INTERRUPT_PRINTER       8
/** Interrupt vector associated to the Real-Time Clock */
#define HAL_INTERRUPT_RTC           9
/** Interrupt vector associated to the Smart Card Slot Interface 0 */
#define HAL_INTERRUPT_SMARTCARD_0   10
/** Interrupt vector associated to the Smart Card Slot Interface 1 */
#define HAL_INTERRUPT_SMARTCARD_1   11
/** Interrupt vector associated to the Smart Card Slot Interface 2 */
#define HAL_INTERRUPT_SMARTCARD_2   12
/** Interrupt vector associated to the GPIO Interface */
#define HAL_INTERRUPT_GPIO          13
/** Interrupt vector associated to the Non Maskable Interrupt (NMI) */
#define HAL_INTERRUPT_NMI           14
/** Interrupt vector associated to the I2C Interface */
#define HAL_INTERRUPT_I2C           15
/** Interrupt vector associated to the Core Timer */
#define HAL_INTERRUPT_CORE_TIMER    16
/** Interrupt vector associated to the Bus Error */
#define HAL_INTERRUPT_BUS_ERROR     17
/** Interrupt vector associated to the GCR */
#define HAL_INTERRUPT_GCR           18
/** Interrupt vector associated to the USB OTG */
#define HAL_INTERRUPT_USB           19
/** Interrupt vector associated to the PS2 Interface */
#define HAL_INTERRUPT_PS2           20
/** Interrupt vector associated to the Parallel Interface */
#define HAL_INTERRUPT_PARALLEL      21
/** Interrupt vector associated to the UART Interface 2 */
#define HAL_INTERRUPT_UART_2        22
/** Interrupt vector associated to the UART Interface 3 */
#define HAL_INTERRUPT_UART_3        23 
/** Interrupt vector associated to the MSR Interface */
#define HAL_INTERRUPT_MSR           24 
/** Interrupt vector associated to the Internal Flash Memory Controler */
#define HAL_INTERRUPT_FLASH         25
/** Interrupt vector associated to the secure RNG */
#define HAL_INTERRUPT_RNG           26
/** Interrupt vector associated to the External Pin */
#define HAL_INTERRUPT_EXTERN        27
/** Interrupt vector associated to the ADC Interface */
#define HAL_INTERRUPT_ADC           29

/** This constant is used when the raised interrupt vector cannot be associated 
 *  with any device */
#define HAL_INTERRUPT_NONE          (-1)

/** First interrupt vector */
#define HAL_INTERRUPT_MIN            0
/** Last interrupt vector */
#define HAL_INTERRUPT_MAX            (HAL_INTERRUPT_ADC)
/** Number of interrupt vectors */
#define HAL_INTERRUPT_COUNT          (HAL_INTERRUPT_MAX-HAL_INTERRUPT_MIN+1)


/** Interrupt priority channel 5 (highest priority) */
#define HAL_INTERRUPT_PRIORITY_CHANNEL_5  5
/** Interrupt priority channel 4 */
#define HAL_INTERRUPT_PRIORITY_CHANNEL_4  4
/** Interrupt priority channel 3 */
#define HAL_INTERRUPT_PRIORITY_CHANNEL_3  3
/** Interrupt priority channel 2 */
#define HAL_INTERRUPT_PRIORITY_CHANNEL_2  2
/** Interrupt priority channel 1 */
#define HAL_INTERRUPT_PRIORITY_CHANNEL_1  1
/** Interrupt priority channel 0 (lowest priority) */
#define HAL_INTERRUPT_PRIORITY_CHANNEL_0  0
    
#define HAL_INTERRUPT_PRIORITY_CHANNEL_VERY_LOW   0
#define HAL_INTERRUPT_PRIORITY_CHANNEL_VERY_HIGH  5
#define HAL_INTERRUPT_PRIORITY_CHANNEL_LOW   1
#define HAL_INTERRUPT_PRIORITY_CHANNEL_HIGH  4

/** Low level detection */
#define HAL_INTERRUPT_MODE_LOW_LEVEL          0

/** Falling edge detection */
#define HAL_INTERRUPT_MODE_FALLING_EDGE       1

/** High level detection */
#define HAL_INTERRUPT_MODE_HIGH_LEVEL         2

/** Rising edge detection */
#define HAL_INTERRUPT_MODE_RISING_EDGE        3


/*----------------------------------------------------------------------------
 * Configuration Structure
 */

/** The configuration structure used to set up the external interrupt */
typedef struct {
  
    /** Priority channel : 0 (low) to 5 (high) */
    unsigned int channel;
   
    /** Detection mode, possible values are :
     *      \li #HAL_INTERRUPT_MODE_LOW_LEVEL
     *      \li #HAL_INTERRUPT_MODE_FALLING_EDGE
     *      \li #HAL_INTERRUPT_MODE_HIGH_LEVEL
     *      \li #HAL_INTERRUPT_MODE_RISING_EDGE
     */
    unsigned int mode;
   
} HAL_INTERRUPT_CONFIG ;
 

    
    
/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The function is used to enable interrupts. 
 * 
 * @retval -ERR_NO          No error 
 * 
 */
inline static int hal_interrupt_enable( void )
{      
    asm("ei");
    return 0;  
}

/**
 * The function is used to disable interrupts. 
 * 
 * @retval -ERR_NO          No error 
 * 
 */
inline static int hal_interrupt_disable( void )
{
    asm("di");
    return 0;  
}

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function is used to mask a specific interrupt. 
 * 
 * @param[in] vector        Vector number associated to the interrupt to be 
 *                          disabled. 
 * 
 */
int hal_interrupt_mask( int vector );

/**
 * The function is used to unmask a specific interrupt. 
 * 
 * @param[in] vector        Vector number associated to the interrupt to be 
 *                          enabled. 
 * 
 */  
int hal_interrupt_unmask( int vector );

/** 
 * The function configures the external interrupt behaviour.
 * 
 * @param[in] params        Pointer on a configuration structure allocated 
 *                          and filled by the caller.
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */ 
int hal_interrupt_set_config( HAL_INTERRUPT_CONFIG *params );

/** 
 * The function assigns a copy of the ISR to the location pointed to by isr. 
 * 
 * @param[in] vector        Vector number associated to the ISR to be retrieved 
 * 
 * @param[out] isr          Pointer on a ISR allocated by the caller and filled 
 *                          by the function with the current ISR of the 
 *                          requested vector number. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *   
 */
int hal_interrupt_get_isr( int vector, unsigned int *isr );

/** 
 * The function is used to decode the vector number. It retrieves the vector 
 * number of the raised interrupt. 
 * 
 * @param level the priority level 
 * 
 * @retval -ERR_INVAL       Vector number not found 
 * @retval Other            Vector number of the raised interrupt 
 *  
 */
int hal_interrupt_decode( int level );

/** 
 * The function registers an Interrupt Service Routine (ISR) to a given vector. 
 * When an interrupt occurs on this vector the ISR is called. 
 * 
 * @param[in] vector        Vector number associated to the ISR to be attached. 
 * 
 * @param[in] isr           Pointer to the ISR function. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * 
 */
int hal_interrupt_attach( int vector, void (*isr)(void) );

/** 
 * The function unregisters an Interrupt Service Routine (ISR). 
 * 
 * @param[in] vector        Vector number associated to the ISR to be detached. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 *   
 */
int hal_interrupt_detach( int vector );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_interrupt_isr_t)(void);
 
__hal_defunc1(hal_interrupt_mask, int, vector);
__hal_defunc1(hal_interrupt_unmask, int , vector);
__hal_defunc1(hal_interrupt_set_config, HAL_INTERRUPT_CONFIG *, params);
__hal_defunc2(hal_interrupt_get_isr, int, vector, unsigned int *, isr);
__hal_defunc2(hal_interrupt_attach, int, vector, hal_interrupt_isr_t, isr);
__hal_defunc1(hal_interrupt_detach, int, vector);
__hal_defunc1(hal_interrupt_decode, int, level);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* HAL_USIP_INTR_H */   
	

