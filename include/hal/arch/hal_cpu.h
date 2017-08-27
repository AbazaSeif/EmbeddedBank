/*============================================================================
 *
 *      hal_cpu.h
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
#ifndef HAL_CPU_H
#define HAL_CPU_H

#define hal_count_reset()   asm volatile ("mtc0 $0,$9; nop; nop;")
#define hal_count_get(val) asm volatile ("mfc0 $2,$9; nop; nop; sll $2,$2,1;": "=r" (val))

#define hal_break_insert()  asm volatile ("break;")

#define HAL_UINT16_LSB(x)                  ((x) & 0xFF)
#define HAL_UINT16_MSB(x)                  (((x) >> 8) & 0xFF)

#define SWAP32(x) ((x << 24) | ((x & 0x0000FF00) << 8) | ((x & 0x00FF0000) >> 8) | (x >> 24))

#define hal_clock_reset( _period_ )             \
    {                                           \
      asm volatile (                            \
        "mtc0 $0,$9\n"                          \
        "nop; nop; nop\n"                       \
        "mtc0 %0,$11\n"                         \
        "nop; nop; nop\n"                       \
        :                                       \
        : "r"(_period_)                         \
        );                                      \
    }

#define hal_clock_read( _pvalue_ )              \
  {                                             \
    register unsigned int result;               \
    asm volatile (                              \
        "mfc0   %0,$9\n"                        \
        : "=r"(result)                          \
        );                                      \
    *(_pvalue_) = result;                       \
  }


//-----------------------------------------------------------------------------
#endif // HAL_CPU_H


