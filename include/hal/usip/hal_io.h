/*============================================================================
 *
 *      hal_io.h
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
 * Contributors:  
 * Date:          
 * Purpose:       HAL device IO register support.
 * Description:
 * 
 *==========================================================================*/
#ifndef HAL_USIP_IO_H
#define HAL_USIP_IO_H

/*-----------------------------------------------------------------------------
 * Some usefull macros
 */
 
/** To convert physical address to virtual address in kernel mode (seg1) */
#define PHYSICAL_TO_KSEG1_ADDRESS(x) ((x) | 0xA0000000)

/** To convert virtual address to physical address in kernel mode (seg1) */
#define K1_VIRTUAL_TO_PHYSICAL_ADDRESS(x) ((x) & ~0xA0000000)


/*-----------------------------------------------------------------------------
 * Peripheral blocks IO space 
 */
 
/** Crypto Interface Control */
#define HAL_CRYPTO_BASE             PHYSICAL_TO_KSEG1_ADDRESS(0x02000400)

/** Universal memory control */
#define HAL_MEMC_BASE               PHYSICAL_TO_KSEG1_ADDRESS(0x02000800)

/** Interrupt Controller */
#define HAL_INTERRUPT_BASE          PHYSICAL_TO_KSEG1_ADDRESS(0x02001000)

/** USB Interface */
#define HAL_USB_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02001400)

/** DMA Controller */
#define HAL_DMA_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02002000)

/** LCD Interface */
#define HAL_DISPLAY_BASE            PHYSICAL_TO_KSEG1_ADDRESS(0x02003000)

/** Smart Card Interface 0 */
#define HAL_SMARTCARD0_BASE         PHYSICAL_TO_KSEG1_ADDRESS(0x02003400)

/** Smart Card Interface 1 */
#define HAL_SMARTCARD1_BASE         PHYSICAL_TO_KSEG1_ADDRESS(0x02003800)

/** Smart Card Interface 2 */
#define HAL_SMARTCARD2_BASE         PHYSICAL_TO_KSEG1_ADDRESS(0x02003C00)

/** Keyboard Controller */
#define HAL_KEYBOARD_BASE           PHYSICAL_TO_KSEG1_ADDRESS(0x02004000)

/** True Random Number Generator */
#define HAL_RNG_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02004400)

/** Global Control Registers */
#define HAL_GCR_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02004800)

/** Timer, PWM and WDT */
#define HAL_TIMER_BASE              PHYSICAL_TO_KSEG1_ADDRESS(0x02005000)
#define HAL_PWM_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02005000)
#define HAL_WATCHDOG_BASE           PHYSICAL_TO_KSEG1_ADDRESS(0x02005000)

/** GPIO */ 
#define HAL_GPIO_BASE               PHYSICAL_TO_KSEG1_ADDRESS(0x02005400)
#define HAL_PARALLEL_BASE           PHYSICAL_TO_KSEG1_ADDRESS(0x02005400)
#define HAL_PS2_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02005400)

/** SPI */
#define HAL_SPI_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02005800)

/** UART (IrDA) */
#define HAL_UART0_BASE              PHYSICAL_TO_KSEG1_ADDRESS(0x02005C00)

/** UART (Modem) */
#define HAL_UART1_BASE              PHYSICAL_TO_KSEG1_ADDRESS(0x02006000)

/** RTC */
#define HAL_RTC_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02006400)

/** UART 2 */
#define HAL_UART2_BASE              PHYSICAL_TO_KSEG1_ADDRESS(0x02006800)

/** UART 3 */
#define HAL_UART3_BASE              PHYSICAL_TO_KSEG1_ADDRESS(0x02006C00)

/** Printer Shifter */
#define HAL_PRINTER_BASE            PHYSICAL_TO_KSEG1_ADDRESS(0x02007000)

/** Magnetic Stripe */
#define HAL_MSR_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02007400)

/** I2C */
#define HAL_I2C_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02007800)

/** ADC Controller */
#define HAL_ADC_BASE                PHYSICAL_TO_KSEG1_ADDRESS(0x02007C00)

/** Fhash Memory Controller */
#define HAL_FLASH_BASE              PHYSICAL_TO_KSEG1_ADDRESS(0x02008000)

/** Different size of register  */
typedef volatile unsigned char  apb_reg8_t;
typedef volatile unsigned short apb_reg16_t;
typedef volatile unsigned int   apb_reg32_t;

typedef volatile unsigned char  ahb_reg8_t;
typedef volatile unsigned short ahb_reg16_t;
typedef volatile unsigned int   ahb_reg32_t;

/*----------------------------------------------------------------------------*/
#endif /* HAL_USIP_IO_H */

