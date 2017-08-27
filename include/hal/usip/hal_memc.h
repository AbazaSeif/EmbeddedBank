/*============================================================================
 *
 *      hal_memc.h
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
 * Description:  This file contains the Universal Memory Controller 
 *               generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_MEMC_H
#define HAL_USIP_MEMC_H


/**
 *  
 * @defgroup HAL_UMC HAL Universal Memory Controller
 * This chapter contains descriptions of the configuration structures and 
 * the functions available to access the Universal Memory Controller (UMC). 
 * 
 * @section hal_memc Overview 
 * 
 * USIP® Professional supports memory space extension by adding some external 
 * memories. 
 * 
 * The USIP® Professional Universal Memory Controller (UMC) provides a 
 * simplified interface to industry standard dynamic and static memories: SRAM, 
 * SDRAM and flash memories or some others devices such as an Ethernet 
 * controller using a memory bus interface. 
 * 
 * \b Features
 * 
 * \li 16-bit word data path for Dynamic memory interface (SDRAM) 
 * \li Up to 32 Mbytes for SDRAM 
 * \li Dynamic memory self-refresh 
 * \li Programmable burst length of two or eight (SDRAM) 
 * \li Programmable CAS latency of one, two and three (SDMC) 
 * \li Programmable RAS to CAS delay (SDMC) 
 * \li Programmable 12-bit Refresh counter (SDMC) 
 * \li Programmable 5-bit Auto-refresh busy counter (SDMC) 
 * \li Up to four chip selects for asynchronous memories (Flash, SRAM …) 
 * \li Support DQ15/A1 flashes (AMD, ...) 
 * \li Programmable address set up time for every asynchronous memories 
 * \li Programmable Write Enable or Output Enable pulse for every asynchronous 
 * memories 
 * \li Programmable bus turnaround delay for every asynchronous memories 
 * \li Little-endian support 
 * 
 * \note The memories accesses are configured with a time basis that is 
 * depending on the system clock frequency. This module should be re-configured 
 * if the system clock frequency is changed (see \link HAL_APM Advanced Power 
 * Management \endlink). 
 * 
 * @addtogroup HAL_UMC
 * 
 * @{
 */
 

/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** This state indicator is raised when both the Flashes are ready */
#define HAL_MEMC_STATUS_READY    0x00
/** This state indicator is raised when at least one of the Flashes is busy */
#define HAL_MEMC_STATUS_BUSY     0x01

/** Type requested for a FLASH memory configuration */
#define HAL_MEMC_TYPE_FLASH         0
/** Type requested for a SRAM memory configuration */
#define HAL_MEMC_TYPE_SRAM          1
/** Type requested for a SDRAM memory configuration */
#define HAL_MEMC_TYPE_SDRAM         2


/** Set the SDRAM burst length to 2 (two 16-bit words) */
#define HAL_MEMC_SDRAM_BURST_2     0
/** Set the SDRAM burst length to 8  (eight 16-bit words) */
#define HAL_MEMC_SDRAM_BURST_8     1

/** Set the SDRAM size to 2MB */
#define HAL_MEMC_SDRAM_SIZE_2MB     0x0
/** Set the SDRAM size to 8MB */
#define HAL_MEMC_SDRAM_SIZE_8MB     0x1
/** Set the SDRAM size to 16MB */
#define HAL_MEMC_SDRAM_SIZE_16MB    0x2
/** Set the SDRAM size to 32MB */
#define HAL_MEMC_SDRAM_SIZE_32MB    0x3

/** Set the rows number for 2MB SDRAM */
#define HAL_MEMC_SDRAM_ROWS_2MB     2048
/** Set the rows number for 8MB SDRAM */
#define HAL_MEMC_SDRAM_ROWS_8MB     4096
/** Set the rows number for 16MB SDRAM */
#define HAL_MEMC_SDRAM_ROWS_16MB    4096
/** Set the rows number for 32MB SDRAM */
#define HAL_MEMC_SDRAM_ROWS_32MB    8192


/** Mode requested for a DQ15/A1 flash type (AMD flashes, etc.) */
#define HAL_MEMC_ASYNC_MODE_DQ15_A1     1

/** No specific mode */
#define HAL_MEMC_ASYNC_MODE_NONE        0

/** \showinitializer Physical start address of the SDRAM bank */
#define HAL_MEMC_SPACE_SDRAM           0x20000000
/** \showinitializer Physical start address of the SRAM/FLASH bank 0 */
#define HAL_MEMC_SPACE_FLASH0          0x30000000
/** \showinitializer Physical start address of the SRAM/FLASH bank 1 */
#define HAL_MEMC_SPACE_FLASH1          0x40000000
/** \showinitializer Physical start address of the SRAM/FLASH bank 2 */
#define HAL_MEMC_SPACE_FLASH2          0x50000000
/** \showinitializer Physical start address of the SRAM/FLASH bank 3 */
#define HAL_MEMC_SPACE_FLASH3          0x60000000

/*----------------------------------------------------------------------------
 * Device Enumeration
 */

/** The device enumeration defines the bank numbers 
 */
enum hal_memc_devices
{
    /** Identifier of the Bank number 0 for the SDRAM */
   hal_memc_dev0 = 0,
    /** Identifier of the Bank number 1 for the SRAM/FLASH 0 */
   hal_memc_dev1,
    /** Identifier of the Bank number 2 for the SRAM/FLASH 1 */
   hal_memc_dev2,
    /** Identifier of the Bank number 3 for the SRAM/FLASH 2 */
   hal_memc_dev3,
    /** Identifier of the Bank number 4 for the SRAM/FLASH 3 */
   hal_memc_dev4,
    /** Max number of bank */
   hal_memc_devices_count 
};

/*----------------------------------------------------------------------------
 * Configuration Structures
 */

/** The configuration structure used to set up the External Memory Controller */
typedef struct HAL_MEMC_CONFIG
{
    /** 
     * Specify the memory type: 
     *      \li #HAL_MEMC_TYPE_SDRAM
     *      \li #HAL_MEMC_TYPE_FLASH 
     *      \li #HAL_MEMC_TYPE_SRAM
     */
    int type;
    
    /** Specify the start offset of non encrypted area 
     * (must be 64KB aligned) */
    unsigned int start;     
    
    /** Specify the end offset of the non encrypted area 
     * (must be 64KB aligned) */
    unsigned int end;
    
    /** 
     * Point on an initialized memory configuration structure, depending on the 
     * type of memory used: 
     * \li #HAL_MEMC_SDRAM_CONFIG for SDRAM 
     * \li #HAL_MEMC_ASYNC_CONFIG for asynchronous memories 
     */
    void *config;
    
} HAL_MEMC_CONFIG;
 

/** The configuration structure used to set up SDRAM */
typedef struct HAL_MEMC_SDRAM_CONFIG
{
    /** Burst length: #HAL_MEMC_SDRAM_BURST_2 or #HAL_MEMC_SDRAM_BURST_8 */
    unsigned int burst;
      
    /** SDRAM size: #HAL_MEMC_SDRAM_SIZE_2MB, #HAL_MEMC_SDRAM_SIZE_8MB, 
     * #HAL_MEMC_SDRAM_SIZE_16MB or #HAL_MEMC_SDRAM_SIZE_32MB */
    unsigned int size;
    
    /** Rows number per bank: #HAL_MEMC_SDRAM_ROWS_2MB, 
     * #HAL_MEMC_SDRAM_ROWS_8MB, #HAL_MEMC_SDRAM_ROWS_16MB or 
     * #HAL_MEMC_SDRAM_ROWS_32MB */
    unsigned int rows; 
    
    /** Refresh Command delay (tRC) time in ns */
    unsigned int t_RC;
     
    /** RAS to CAS delay (tRCD) in ns */
    unsigned int t_RCD;     
    
    /** Refresh period (tREF) in ns */
    unsigned int t_REF; 
    
    /** Row precharge time (tRP) in ns */
    unsigned int t_RP; 
    
    /** CAS latency (the delay, in clock cycles, between the registration of 
     * a READ command and the availability of the first output data)\n 
     * One of 1, 2 or 3 clock cycles. */
    unsigned int t_CL; 
    
    /** Load mode register command to active or refresh command delay (in clock), 
     * also called tMRD */
    unsigned int t_MRD; 
    
} HAL_MEMC_SDRAM_CONFIG;


/** The configuration structure used to set up asynchronous memories. */
typedef struct HAL_MEMC_ASYNC_CONFIG
{
    /** Mode for Flash memory. Possible values :      
     *      @li #HAL_MEMC_ASYNC_MODE_DQ15_A1     
     *      @li #HAL_MEMC_ASYNC_MODE_NONE
     */
    unsigned int mode;
    
    /** Setup time : The time between the beginning of a memory cycle (CE low,
     *  address valid) and the activation of the read or write strobe in ns.
     */
    unsigned int setup;
      
    /** Strobe time : The time between the activation and deactivation of 
     * the Read Enable or Write Enable in ns.
     */
    unsigned int strobe;
    
    /** Hold time : The time between the deactivation of the read or write 
     *  strobe and the end of the cycle, which can be either an address change 
     * or the deactivation of the CE signal in ns.
     */
    unsigned int hold;
   
} HAL_MEMC_ASYNC_CONFIG;


/*----------------------------------------------------------------------------
 * Control Enumeration
 */

/** The control enumeration defines the type of control on the GPIO 
 */
typedef enum 
{
    /** Set configuration register value for selected device */
    HAL_MEMC_IOCTL_SET_REGISTER,

} HAL_MEMC_CONTROL;


/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif 
 
#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function sets up the AES 128-bit key used to secure the external memory 
 * access. The AES 128-bit key must be set before call to any other functions. 
 * 
 * @param[in] key           Pointer allocated and filled by the caller with the 
 *                          128-bit AES key. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_memc_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */
int hal_memc_set_key( void *key );

/**
 * The function resets, activates and configures a specified memory bank of the 
 * External Memory Controller. 
 *
 * @warning The UMC shares its clock and hardware reset with the cryptographic 
 * interface. It is not actually reset nor activated if any other memory bank 
 * or the cryptographic interface is already in use. 
 * 
 * @param[in] devnum        Memory bank identifier (#hal_memc_devices gives a 
 *                          list of all memory bank identifiers) 
 * 
 * @param[in] params        Pointer on a EMC configuration structure allocated 
 *                          and filled by the caller. 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_memc_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_memc_init( int devnum, HAL_MEMC_CONFIG *params );

/**
 * The function disables a specified memory bank of the External Memory 
 * Controller. 
 * 
 * @warning The UMC shares its clock and hardware reset with the cryptographic 
 * interface. It is not actually disabled if any other memory bank or the 
 * cryptographic interface is still in use. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_memc_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_memc_shutdown( int devnum );

/** 
 * The function configures the access to a specified memory bank. 
 * 
 * @param[in] devnum        Memory bank identifier (#hal_memc_devices gives a 
 *                          list of all memory bank identifiers) 
 * 
 * @param[in] params        Pointer on a EMC configuration structure allocated 
 *                          and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_memc_init() first. 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_memc_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_memc_set_config( int devnum, HAL_MEMC_CONFIG *params );

/** 
 * The function provides the current state of a specified memory bank.
 * 
 * @param[in] devnum        Memory bank identifier (#hal_memc_devices gives a 
 *                          list of all memory bank identifiers) 
 * 
 * @param[out] status       Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the External Memory Controller. Upon success, it 
 *                          receives one of the following state indicators: 
 *                          \li #HAL_MEMC_STATUS_READY
 *                          \li #HAL_MEMC_STATUS_BUSY
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_memc_init() first. 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_memc_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_memc_get_status( int devnum, int *status );

/**
 * The function performs External Memory Controller specific control functions.
 *
 * @param[in] devnum        Memory bank identifier (#hal_memc_devices gives a 
 *                          list of all memory bank identifiers) 
 * 
 * @param[in] cmd           Requested control function 
 * 
 * @param[in,out] data      Pointer on a variable allocated by the caller and 
 *                          filled by the caller with data requested for the 
 *                          control function or by the function with data 
 *                          retrieved from the control function: 
 *                          \li #HAL_MEMC_IOCTL_SET_REGISTER: the value to be 
 *                          written in the UMC register bits related to the 
 *                          selected memory bank (Any data concerning 
 *                          #hal_memc_dev1 or #hal_memc_dev3 will be anded with 
 *                          0x00003FFF. Any data concerning #hal_memc_dev2 or 
 *                          #hal_memc_dev4 will be anded with 0x0FFFC000.) 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_memc_init() first. 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_memc_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NOTTY       Inappropriate ioctl for device 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_memc_ioctl( int devnum, HAL_MEMC_CONTROL cmd, void *data );

/**
 * The function registers a handler for the interrupt raised with the rising 
 * edge of the Ready/Busy signal of a Flash (at the end of an erase/program 
 * sequence). 
 *
 * @param[in] devnum        Memory bank identifier (#hal_memc_devices gives a 
 *                          list of all memory bank identifiers) 
 * 
 * @param[in] handler       Pointer to the interrupt handler function. 
 *                          Its declaration should support the parameter:
 *                          \li \e devnum Device identifier
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_memc_init() first. 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_memc_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_memc_attach( int devnum, void (*handler)(int devnum) );

/**
 * The function unregisters the handler for the interrupt raised with the 
 * rising edge of the Ready/Busy signal of a Flash ( at the end of an 
 * erase/program sequence). 
 * 
 * @param[in] devnum        Memory bank identifier (#hal_memc_devices gives a 
 *                          list of all memory bank identifiers) 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_memc_init() first. 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_memc_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_memc_detach( int devnum );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_memc_handler_t)(int devnum);

__hal_defunc1(hal_memc_set_key, void *, key);
__hal_defunc2(hal_memc_init, int, devnum, HAL_MEMC_CONFIG *, params);
__hal_defunc1(hal_memc_shutdown, int, devnum);
__hal_defunc2(hal_memc_set_config, int, devnum, HAL_MEMC_CONFIG *, params);
__hal_defunc2(hal_memc_get_status, int, devnum, int *, status);
__hal_defunc3(hal_memc_ioctl, int, devnum, HAL_MEMC_CONTROL, cmd, void *, data);
__hal_defunc2(hal_memc_attach, int, devnum, hal_memc_handler_t, handler);
__hal_defunc1(hal_memc_detach, int, devnum);
        
__hal_deisr(hal_memc_isr, void);
     
#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/**  @}  */

#endif  /* HAL_USIP_MEMC_H */

