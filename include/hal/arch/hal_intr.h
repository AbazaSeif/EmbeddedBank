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
 * Description: HAL Interrupt and clock support
 * 
 *==========================================================================*/
#ifndef _HAL_INTR_H_
#define _HAL_INTR_H_


//--------------------------------------------------------------------------
// MIPS vectors. 

// These are the exception codes presented in the Cause register and
// correspond to VSRs. These values are the ones to use for HAL_VSR_GET/SET

// External interrupt
#define HAL_VECTOR_INTERRUPT            0
// TLB modification exception
#define HAL_VECTOR_TLB_MOD              1
// TLB miss (Load or IFetch)
#define HAL_VECTOR_TLB_LOAD_REFILL      2
// TLB miss (Store)
#define HAL_VECTOR_TLB_STORE_REFILL     3
// Address error (Load or Ifetch)
#define HAL_VECTOR_LOAD_ADDRESS         4
// Address error (store)
#define HAL_VECTOR_STORE_ADDRESS        5
// Bus error (Ifetch)
#define HAL_VECTOR_IBE                  6
// Bus error (data load or store)
#define HAL_VECTOR_DBE                  7
// System call
#define HAL_VECTOR_SYSTEM_CALL          8
// Break point
#define HAL_VECTOR_BREAKPOINT           9
// Reserved instruction
#define HAL_VECTOR_RESERVED_INSTRUCTION 10
// Coprocessor unusable
#define HAL_VECTOR_COPROCESSOR          11
// Arithmetic overflow
#define HAL_VECTOR_OVERFLOW             12
// Trap 
#define HAL_VECTOR_TRAP                 13
// Reserved
#define HAL_VECTOR_RESERVED_14          14
// Reserved
#define HAL_VECTOR_RESERVED_15          15
// Implementation Specific (COP2)
#define HAL_VECTOR_ISCOP2_1             16
// Implementation Specific (COP2)
#define HAL_VECTOR_ISCOP2_2             17
// Coprocessor 2
#define HAL_VECTOR_COPROCESSOR_2        18
// Reserved
#define HAL_VECTOR_RESERVED_19          19
// Reserved
#define HAL_VECTOR_RESERVED_20          20
// Reserved
#define HAL_VECTOR_RESERVED_21          21
// Reserved
#define HAL_VECTOR_RESERVED_22          22
// Reference to WatchHi/WatchLo address
#define HAL_VECTOR_WATCH_ADDRESS        23
// Machine check
#define HAL_VECTOR_MACHINE_CHECK        24


#define HAL_VSR_MIN                     HAL_VECTOR_INTERRUPT
#define HAL_VSR_MAX                     HAL_VECTOR_MACHINE_CHECK
#define HAL_VSR_COUNT                   (HAL_VSR_MAX-HAL_VSR_MIN+1)

// Exception vectors. These are the values used when passed out to an
// external exception handler using cyg_hal_deliver_exception()

#define HAL_EXCEPTION_DATA_TLBERROR_ACCESS      HAL_VECTOR_TLB_MOD
#define HAL_EXCEPTION_DATA_TLBMISS_ACCESS       HAL_VECTOR_TLB_LOAD_REFILL
#define HAL_EXCEPTION_DATA_TLBMISS_WRITE        HAL_VECTOR_TLB_STORE_REFILL
#define HAL_EXCEPTION_DATA_UNALIGNED_ACCESS     HAL_VECTOR_LOAD_ADDRESS
#define HAL_EXCEPTION_DATA_UNALIGNED_WRITE      HAL_VECTOR_STORE_ADDRESS
#define HAL_EXCEPTION_CODE_ACCESS               HAL_VECTOR_IBE
#define HAL_EXCEPTION_DATA_ACCESS               HAL_VECTOR_DBE
#define HAL_EXCEPTION_SYSTEM_CALL               HAL_VECTOR_SYSTEM_CALL
#define HAL_EXCEPTION_INSTRUCTION_BP            HAL_VECTOR_BREAKPOINT
#define HAL_EXCEPTION_ILLEGAL_INSTRUCTION       HAL_VECTOR_RESERVED_INSTRUCTION
#define HAL_EXCEPTION_COPROCESSOR               HAL_VECTOR_COPROCESSOR
#define HAL_EXCEPTION_OVERFLOW                  HAL_VECTOR_OVERFLOW
#define HAL_EXCEPTION_DIV_BY_ZERO               HAL_VECTOR_DIV_BY_ZERO
#define HAL_EXCEPTION_INTERRUPT                 HAL_VECTOR_BREAKPOINT
    

// Min/Max exception numbers and how many there are
#define HAL_EXCEPTION_MIN                HAL_VSR_MIN
#define HAL_EXCEPTION_MAX                HAL_VSR_MAX

#define HAL_EXCEPTION_COUNT           \
                 ( HAL_EXCEPTION_MAX - HAL_EXCEPTION_MIN + 1 )



// the default for all MIPS variants is to use the 6 bits
// in the cause register.

#define HAL_INTERRUPT_0                0
#define HAL_INTERRUPT_1                1
#define HAL_INTERRUPT_2                2
#define HAL_INTERRUPT_3                3
#define HAL_INTERRUPT_4                4
#define HAL_INTERRUPT_5                5

// Min/Max ISR numbers and how many there are
#define HAL_ISR_MIN                     0
#define HAL_ISR_MAX                     5
#define HAL_ISR_COUNT                   6


/*-----------------------------------------------------------------------------
 * The MIPS Cause register includes two software interrupt bits, which allow 
 * high-priority interrupt handlers to request a new interrupt at a low-priority, 
 * or non-interrupt code to kick-start interrupt-level processing. 
 * 
 * The following functions provide a safe way to switch these interrupts on and off.
 *
 * @note that intrno may only be 0 or 1, and the respective interrupt handlers 
 * must call hal_swi_ack() to remove the interrupt request before they return.
 */ 
void hal_swi_request( unsigned int intrno ); 

void hal_swi_ack( unsigned int intrno );


//--------------------------------------------------------------------------
#endif /* _HAL_INTR_H_ */

