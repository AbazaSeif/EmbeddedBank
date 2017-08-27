/*============================================================================
 *
 *      hal_tlb.h
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
#ifndef _HAL_ARCH_TLB_H_
#define _HAL_ARCH_TLB_H_

/**
 *  
 * @defgroup HAL_TLB HAL TLB Maintenance 
 *
 * The 4KSd core implements a 16 dual-entry, fully associative Joint TLB 
 * (Translation Lookaside Buffer) that maps 32 virtual pages to their 
 * corresponding physical addresses. 
 *
 * This chapter describes the functions related to the TLB memory management 
 * scheme used in the processor core. 
 *  
 * @note For more information about the TLB refer to MIPS32 4KSd Processor Core 
 * Software User’s Manual.  
 * 
 * @{
 */

/*------------------------------------------------------------------------------
 * Defines 
 *----------------------------------------------------------------------------*/

/** The number of entries in the TLB */
#define HAL_TLB_INDEX_MAX       16

#define HAL_TLB_INDEX_RANDOM    (-1)

/** TLB entry page mask value: Set the TLB page size to 1KB */
#define HAL_TLB_PAGE_SIZE_1KB   0x0 
/** TLB entry page mask value: Set the TLB page size to 2KB */
#define HAL_TLB_PAGE_SIZE_2KB   0x1 
/** TLB entry page mask value: Set the TLB page size to 4KB */
#define HAL_TLB_PAGE_SIZE_4KB   0x2 
/** TLB entry page mask value: Set the TLB page size to 16KB */
#define HAL_TLB_PAGE_SIZE_16KB  0x3 
/** TLB entry page mask value: Set the TLB page size to 64KB */
#define HAL_TLB_PAGE_SIZE_64KB  0x4 
/** TLB entry page mask value: Set the TLB page size to 256KB */
#define HAL_TLB_PAGE_SIZE_256KB 0x5 
/** TLB entry page mask value: Set the TLB page size to 1MB */
#define HAL_TLB_PAGE_SIZE_1MB   0x6 
/** TLB entry page mask value: Set the TLB page size to 4MB */
#define HAL_TLB_PAGE_SIZE_4MB   0x7 
/** TLB entry page mask value: Set the TLB page size to 16MB */
#define HAL_TLB_PAGE_SIZE_16MB  0x8 

/** TLB entry attribute: Set the "Read Inhibit" Bit */
#define HAL_TLB_PAGE_READ_INHIBIT    0x80000000
/** TLB entry attribute: Set the "Execute Inhibit" Bit */
#define HAL_TLB_PAGE_EXECUTE_INHIBIT 0x40000000
/** TLB entry attribute: Set the cacheability bits to "Uncached" */
#define HAL_TLB_PAGE_UNCACHED        0x00000010
/** TLB entry attribute: Set the cacheability bits to "Cacheable, noncoherent, 
 *  write-back, write-allocate" */
#define HAL_TLB_PAGE_CACHED          0x00000018
/** TLB entry attribute: Set the "Dirty" or Write-enable Bit */
#define HAL_TLB_PAGE_DIRTY           0x00000004
/** TLB entry attribute: Set the Valid Bit */
#define HAL_TLB_PAGE_VALID           0x00000002
/** TLB entry attribute: Set the Global Bit */
#define HAL_TLB_PAGE_GLOBAL          0x00000001

/*------------------------------------------------------------------------------
 * Functions 
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_LIBROM_NOT_INLINED
#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initialises and invalidates the whole TLB.
 */
void hal_tlb_init( void );

/**
 * The function invalidates the whole TLB.
 */
void hal_tlb_inval_all( void );

/**
 * The function reads the TLB entry with specified by index, and returns 
 * the EntryHi, EntryLo0, EntryLo1 and PageMask parts in *phi, *plo0, *plo1 and *pmsk 
 * respectively.
 */
void 
hal_tlb_ri2( unsigned int *phi, unsigned int *plo0, unsigned int *plo1, 
             unsigned int *pmsk, int index );

/**
 * The function writes hi, lo0, lo1 and msk into the TLB entry specified by index.
 */
void hal_tlb_wi2( unsigned int hi, unsigned int lo0, unsigned int lo1, 
                  unsigned msk, int index );

/**
 * The function initializes a TLB entry. 
 *
 * @param[in] index             TLB entry index 
 * 
 * @param[in] pagesize          Page size; one of: 
 *                              \li #HAL_TLB_PAGE_SIZE_1KB 
 *                              \li #HAL_TLB_PAGE_SIZE_2KB 
 *                              \li #HAL_TLB_PAGE_SIZE_4KB 
 *                              \li #HAL_TLB_PAGE_SIZE_16KB 
 *                              \li #HAL_TLB_PAGE_SIZE_64KB 
 *                              \li #HAL_TLB_PAGE_SIZE_256KB 
 *                              \li #HAL_TLB_PAGE_SIZE_1MB 
 *                              \li #HAL_TLB_PAGE_SIZE_4MB 
 *                              \li #HAL_TLB_PAGE_SIZE_16MB 
 * 
 * @param[in] addr_v            Virtual memory address 
 *  
 * @param[in] addr_p0           Even Physical memory address 
 * 
 * @param[in] pageattrib0       Page attributes; orred combination of: 
 *                              \li #HAL_TLB_PAGE_UNCACHED 
 *                              \li #HAL_TLB_PAGE_CACHED 
 *                              \li #HAL_TLB_PAGE_DIRTY 
 *                              \li #HAL_TLB_PAGE_VALID 
 *                              \li #HAL_TLB_PAGE_GLOBAL 
 *                              \li #HAL_TLB_PAGE_READ_INHIBIT
 *                              \li #HAL_TLB_PAGE_EXECUTE_INHIBIT
 *  
 * @param[in] addr_p1           Odd Physical memory address 
 *  
 * @param[in] pageattrib1       Page attributes; orred combination of: 
 *                              \li #HAL_TLB_PAGE_UNCACHED 
 *                              \li #HAL_TLB_PAGE_CACHED 
 *                              \li #HAL_TLB_PAGE_DIRTY 
 *                              \li #HAL_TLB_PAGE_VALID 
 *                              \li #HAL_TLB_PAGE_GLOBAL 
 *                              \li #HAL_TLB_PAGE_READ_INHIBIT
 *                              \li #HAL_TLB_PAGE_EXECUTE_INHIBIT
 * 
 * @retval -ERR_NO              No error 
 * @retval Other                See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_tlb_write2( int index, int pagesize, int addr_v,
                    int addr_p0, int pageattrib0,
                    int addr_p1, int pageattrib1 ) ;
/**
 * The function initializes a TLB entry. 
 *
 * @param[in] index         TLB entry index 
 * 
 * @param[in] pagesize      Page size; one of: 
 *                              \li #HAL_TLB_PAGE_SIZE_1KB 
 *                              \li #HAL_TLB_PAGE_SIZE_2KB 
 *                              \li #HAL_TLB_PAGE_SIZE_4KB 
 *                              \li #HAL_TLB_PAGE_SIZE_16KB 
 *                              \li #HAL_TLB_PAGE_SIZE_64KB 
 *                              \li #HAL_TLB_PAGE_SIZE_256KB 
 *                              \li #HAL_TLB_PAGE_SIZE_1MB 
 *                              \li #HAL_TLB_PAGE_SIZE_4MB 
 *                              \li #HAL_TLB_PAGE_SIZE_16MB 
 *  
 * @param[in] addr_v        Virtual memory address 
 *  
 * @param[in] addr_p        Physical memory address 
 *  
 * @param[in] pageattrib    Page attributes; orred combination of: 
 *                              \li #HAL_TLB_PAGE_UNCACHED 
 *                              \li #HAL_TLB_PAGE_CACHED 
 *                              \li #HAL_TLB_PAGE_DIRTY 
 *                              \li #HAL_TLB_PAGE_VALID 
 *                              \li #HAL_TLB_PAGE_GLOBAL 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_tlb_write( int index, int pagesize, int addr_v, 
                   int addr_p, int pageattrib ); 

/**
 * Writes hi, lo0, lo1 and msk into the TLB entry specified by 
 * the Random register.
 */
void hal_tlb_wr2( unsigned int hi, unsigned int lo0, 
                  unsigned int lo1, unsigned int msk );

/**
 * The function probes the TLB for an entry matching hi and returns its index, 
 * or -1 if not found. If found, then the EntryLo0, EntryLo1 and PageMask parts of 
 * the entry are also returned in *plo0, *plo1 and *pmsk respectively.
 */
int hal_tlb_probe2( unsigned int hi, unsigned int *plo0, 
                    unsigned int *plo1, unsigned int *pmsk );

/**
 * Probes the TLB for an entry matching hi and if present rewrites that entry, 
 * otherwise updates a random entry. A safe way to update the TLB.
 */
int hal_tlb_rwr2( unsigned int hi, unsigned int lo0, 
                  unsigned int lo1, unsigned int msk );


#else

#include <hal/usip/hal_sys.h>

__hal_defunc5(hal_tlb_write, int, index, int, pagesize, int, addr_v, 
                   int, addr_p, int, pageattrib );
__hal_defunc7(hal_tlb_write2, int, index, int, pagesize, int, addr_v, 
                   int, addr_p0, int, pageattrib0,int, addr_p1, int, pageattrib1 );
              
#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif


/** @} */

//-----------------------------------------------------------------------------
#endif // _HAL_ARCH_TLB_H_
