/*============================================================================
 *
 *      config.h
 *
 *      
 *
 *==========================================================================*/
/*============================================================================
 * 
 * Copyright (c) 2002-2003 Innova Card.
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
#ifndef _INFRA_CONFIG_H_
#define _INFRA_CONFIG_H_

#define CONFIG_LIBROM_NOT_INLINED

/* Maturity Level */
#undef CONFIG_MATURITY_LEVEL_DEBUG
#define CONFIG_MATURITY_LEVEL_RELEASE

/* USIP Hardware Revision */
#undef CONFIG_PLATFORM_USIP_IC200
//#define CONFIG_PLATFORM_USIP_IC200

#undef CONFIG_PLATFORM_USIP_IC300
//#define CONFIG_PLATFORM_USIP_IC300

//#undef CONFIG_PLATFORM_USIP_IC400
#define CONFIG_PLATFORM_USIP_IC400


#ifdef CONFIG_PLATFORM_USIP_IC200
/* fix hardware bug on the bridge */
# define FIX_HW_BUG_ON_IC200_APB_BRIDGE()   \
     { volatile unsigned char t;  HAL_READ_UINT8(0xa2003001, t); }
#else
# define FIX_HW_BUG_ON_IC200_APB_BRIDGE()
#endif


/* Startup configuration */
#define CONFIG_STARTUP_MEMORY_ROM    0
#define CONFIG_STARTUP_MEMORY_FLASH  1
#define CONFIG_STARTUP_MEMORY_RAM    2


#ifdef CONFIG_PLATFORM_USIP_IC400
# define CONFIG_STARTUP_TYPE CONFIG_STARTUP_MEMORY_ROM
#else
# define CONFIG_STARTUP_TYPE CONFIG_STARTUP_MEMORY_FLASH
#endif

/*--------------------------------- 
 * General configuration 
 *---------------------------------*/
#define CONFIG_USIP_VERSION_MAJOR       2
#define CONFIG_USIP_VERSION_MINOR       0


#define CONFIG_LIBHAL_VERSION_MAJOR     2
#define CONFIG_LIBHAL_VERSION_MINOR     0


#define CONFIG_LOADER_VERSION_MAJOR     2
#define CONFIG_LOADER_VERSION_MINOR     0

#define CONFIG_LIBEMV_VERSION_MAJOR     1
#define CONFIG_LIBEMV_VERSION_MINOR     2



/*----------------------------------------------------------------------------- 
 * 
 * !!!!!!!!!!!!!!!!!!!   FOR DEBUG PURPOSE   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
 * 
 *----------------------------------------------------------------------------*/
#ifdef CONFIG_MATURITY_LEVEL_DEBUG

/*--------------------------------- 
 * System configuration 
 *---------------------------------*/

/* Manage versions */
# undef CONFIG_USIP_VERSION_MAJOR
# undef CONFIG_USIP_VERSION_MINOR
# define CONFIG_USIP_VERSION_MAJOR       0
# define CONFIG_USIP_VERSION_MINOR       2

# undef CONFIG_LIBHAL_VERSION_MAJOR     
# undef CONFIG_LIBHAL_VERSION_MINOR
# define CONFIG_LIBHAL_VERSION_MAJOR     1
# define CONFIG_LIBHAL_VERSION_MINOR     0
# define CONFIG_LIBHAL_STRING_VERSION    "libhal version 1.1 "  \
                                         "build 051212\n"

# undef CONFIG_LOADER_VERSION_MAJOR     
# undef CONFIG_LOADER_VERSION_MINOR
# define CONFIG_LOADER_VERSION_MAJOR     0
# define CONFIG_LOADER_VERSION_MINOR     3

# undef CONFIG_LIBEMV_VERSION_MAJOR     
# undef CONFIG_LIBEMV_VERSION_MINOR
# define CONFIG_LIBEMV_VERSION_MAJOR     1
# define CONFIG_LIBEMV_VERSION_MINOR     0
# define CONFIG_LIBEMV_STRING_VERSION    "libemv version 1.1 "\
                                         "build 051212\n"

/* Define the debug output used */
#define DIAG_OUTPUT_UART
//#define DIAG_OUTPUT_BUFFER
//#define DIAG_OUTPUT_PS2

/* Define the communication port number used */
#ifdef DIAG_OUTPUT_UART
#define CONFIG_DIAG_SERIAL_PORT         hal_uart_dev3
#define CONFIG_DIAG_SERIAL_BAUDRATE     HAL_UART_BAUDRATE_57600
#endif
/* Define the RAM size used */
#ifdef DIAG_OUTPUT_BUFFER
#define DIAG_OUTPUT_BUFFER_SIZE            0x0400
#endif

#endif /* CONFIG_LOADER_MATURITY_LEVEL_DEBUG */


#endif /* _INFRA_CONFIG_H_ */

