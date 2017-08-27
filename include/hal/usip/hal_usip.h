/*============================================================================
 *
 *      hal_usip.h
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
 * Purpose:       
 * Description:   
 * 
 *==========================================================================*/
#ifndef HAL_USIP_H
#define HAL_USIP_H
   
/*--------------------------------------------------------------------------*/

/**
 * @mainpage USIP® Professional<BR>Hardware Abstraction Layer<BR>Reference Manual 
 * 
 * @image html innova0.png
 * 
 * 
 * @section Scope Scope
 * This document describes the contents of the USIP®  Professional HAL Library 
 * and explains its use.
 *
 * @section Introduction Introduction
 * The Hardware Abstraction Layer (HAL) is an implementation presenting 
 * a consistent interface between the hardware and the upper layers.
 *
 * The HAL simplifies building applications by providing a collection of 
 * functions, macros, and symbols used to configure and control on-chip 
 * peripherals.
 * 
 * @section Design_overview Design overview
 * 
 * The HAL interface has been designed with the following goals in mind. 
 * 
 * @subsection Modularity 
 * Given the variety of customer needs, the HAL interface has been designed 
 * to be flexible in architecture in such a way that undesired components could 
 * be taken away. 
 * 
 * @subsection OS Independent 
 * Given the fact that large numbers of devices in the market today don’t use 
 * any operating system, the HAL has been implemented not to use any operating 
 * system dependent features such as events, semaphores, messages Etc. 
 * 
 * @subsection Optimization
 * One of the goals of embedded software design is to achieve the target 
 * functionality with minimum code size and minimum components required for 
 * the product design. 
 * 
 * @subsection Performance 
 * The HAL has been designed to keep the top performance by virtue of the fact 
 * that it provides tight interaction with hardware.
 * 
 * @section Device_Management Device Management
 * The Hardware Abstraction Layer provides a device handler for each peripheral. 
 * The following handlers are available: 
 *
 * 
 *  -# @link HAL_ADC        HAL Analog To Digital Converter. @endlink 
 *  -# @link HAL_APM        HAL Advanced Power Manager. @endlink 
 *  -# @link HAL_CRYPTO     HAL Cryptographic Interface. @endlink
 *  -# @link HAL_LCD        HAL Display Interface. @endlink 
 *  -# @link HAL_DMA        HAL Direct Memory Access. @endlink 
 *  -# @link HAL_FLASH      HAL Flash Memory Access. @endlink 
 *  -# @link HAL_GPIO       HAL General Purpose Input/Output. @endlink 
 *  -# @link HAL_I2C        HAL I2C Interface. @endlink 
 *  -# @link HAL_INTR       HAL Interrupt Controller. @endlink
 *  -# @link HAL_KBD        HAL Keyboard Interface. @endlink
 *  -# @link HAL_MSR        HAL Magnetic Stripe Interface. @endlink
 *  -# @link HAL_SPP        HAL Parallel Interface. @endlink
 *  -# @link HAL_PS2        HAL PS/2 Interface. @endlink
 *  -# @link HAL_PWM        HAL Pulse Width Modulator. @endlink
 *  -# @link HAL_RTC        HAL Real-Time Clock. @endlink
 *  -# @link HAL_STO        HAL Security Storage. @endlink
 *  -# @link HAL_SENSOR     HAL Sensor Inputs. @endlink 
 *  -# @link HAL_SCS        HAL Smart Card Slot Interface. @endlink
 *  -# @link HAL_SPI        HAL SPI Interface. @endlink
 *  -# @link HAL_PRN        HAL Thermal Printer Interface. @endlink
 *  -# @link HAL_TMR        HAL Timer. @endlink
 *  -# @link HAL_RNG        HAL True Random Number Generator. @endlink
 *  -# @link HAL_UART       HAL Universal Asynchronous Receiver Transmitter. @endlink
 *  -# @link HAL_UMC        HAL Universal Memory Controller. @endlink
 *  -# @link HAL_USB        HAL Universal Serial Bus (USB OTG). @endlink
 *  -# @link HAL_WDT        HAL Watchdog Timer. @endlink
 * 
 * @section CPU_Management CPU Management
 * USIP® Professional is based on a MIPS32 4KSd core. The Hardware Abstraction 
 * Layer provides also a set of support functions with which to initialise and 
 * maintain the processor’s caches, TLB and coprocessor registers.
 * 
 *  \li @link HAL_CACHE HAL Cache Maintenance. @endlink
 *  \li @link HAL_TLB HAL TLB Maintenance. @endlink
 * 
 *
 * @section License License 
 * 
 * @htmlinclude license.html 
 * 
 * 
 * @section Reference Reference 
 * 
 * @htmlinclude reference.html 
 * 
 * 
 */
 
 

/*--------------------------------------------------------------------------*/
#endif /* HAL_USIP_H */

