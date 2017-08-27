/*============================================================================
 *
 *      hal_cache.h
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
#ifndef _HAL_CACHE_H_
#define _HAL_CACHE_H_

/**
 *  
 * @defgroup HAL_CACHE HAL Cache Maintenance 
 * 
 * The MIPS32 4KSd processor core supports 8k bytes Data cache and 8k bytes 
 * instruction cache.
 * 
 * This chapter describes the functions related to the maintenance of caches 
 * present in the processor. 
 * 
 * @note For more information about the caches refer to MIPS32 4KSd Processor 
 * Core Software User’s Manual. 
 * 
 * @{
 */
 
/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Cache dimensions.
 */

/** Size of data cache in bytes */
#define HAL_DCACHE_SIZE                 (8*1024) 
/** Size of a data cache line */
#define HAL_DCACHE_LINE_SIZE            16       
/** Associativity of the data cache */
#define HAL_DCACHE_WAYS                 4        
/** Number of data cache sets */
#define HAL_DCACHE_SETS                 128

/** Size of the instruction cache in bytes */
#define HAL_ICACHE_SIZE                 (8*1024) 
/** Size of a instruction cache line */
#define HAL_ICACHE_LINE_SIZE            16     
/** Associativity of the instruction cache */  
#define HAL_ICACHE_WAYS                 4        
/** Number of instruction cache sets */
#define HAL_ICACHE_SETS                 128


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

//#define CONFIG_LIBROM_NOT_INLINED

#ifdef CONFIG_LIBROM_NOT_INLINED

/** 
 * The function initialises the caches. The function could be called after a 
 * hardware reset and before using the caches, otherwise they may be in an 
 * inconsistent state. This is normally called by the standard reset code. 
 * Do not call it from application code, as it may invalidate dirty cache lines 
 * in a writeback cache, without actually writing them back to memory.
*/
void hal_cache_init( void );

/**
 * The function is used to enable the instruction and data caches.
 */
void hal_cache_enable( void );

/**
 * The function is used to disable the instruction and data caches.
 */
void hal_cache_disable( void );

/**
 * The function invalidates all entries from all instruction caches.
 * 
 * @note Separate data caches are unchanged.
 */   
void hal_icache_flush( void );

/**
 * The function loads the contents of the given address range into the 
 * instruction cache and then locks the cache so that it stays there.
 *
 * @param[in] addr_v   Virtual address to operate on.
 * @param[in] n        Region size to operate on.
 * 
 */
void hal_icache_lock( void *addr_v, int n );


/**
 * The function is used to undo a previous lock operation.
 * 
 * @param[in]  addr_v   Virtual address to operate on.
 * @param[in]  n        Region size to operate on.
 * 
 */
void hal_icache_unlock( void *addr_v, int n );


/** 
 * The function invalidates cache lines in the given range without writing to 
 * memory. 
 * 
 * @param[in]  addr_v   Virtual address to operate on.
 * @param[in]  n        Region size to operate on.
 * 
 */
void hal_icache_clean( void *addr_v, int n );

/**
 * The function invalidates all entries from all data caches.
 * 
 * @note Separate instruction caches are unchanged.
 */   
void hal_dcache_flush( void );

/**
 * The function invalidate cache lines in the given range without writing to memory..
 *
 * @param[in]  addr_v   Virtual address to operate on.
 * @param[in]  n        Region size to operate on.
 * 
 */
void hal_dcache_clean( void *addr_v, int n );

/**
 * The function loads the contents of the given address range into the data cache
 * and then locks the cache so that it stays there.
 *
 * @param[in]  addr_v   Virtual address to operate on.
 * @param[in]  n        Region size to operate on.
 * 
 */
void hal_dcache_lock( void *addr_v, int n );


/**
 * The function is used to undo a previous lock operation.
 * 
 * @param[in] addr_v   Virtual address to operate on.
 * @param[in] n        Region size to operate on.
 * 
 */
void hal_dcache_unlock( void *addr_v, int n );

#else

#include <hal/usip/hal_sys.h>

__hal_defunc0(hal_cache_enable, void);
__hal_defunc0(hal_cache_disable, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _HAL_CACHE_H_ */

