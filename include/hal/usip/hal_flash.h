/*============================================================================
 *
 *      hal_flash.h
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
 * Description:  This file contains the Internal Flash Memory generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_FLASH_H
#define HAL_USIP_FLASH_H 

/** @defgroup HAL_FLASH HAL Internal Flash Memory.
 * This chapter contains descriptions of the functions available to access 
 * the Internal Flash Memory. 
 * 
 * @section Overview Overview 
 * 
 * USIP® Professional provides 256 kBytes of internal flash memory and 510 
 * Bytes of OTP flash memory (One-Time Programmable). 
 * 
 * \b Features
 * 
 *  - 256 kBytes of flash accessed within 36 sectors 
 *      - sectors 0 to 3: 32 kBytes 
 *      - sectors 4 to 35: 4 kBytes 
 *      .
 *  - 510 Bytes of OTP flash accessed within 2 sectors 
 *      - sector 0: offset 0x20 to 0xFF 
 *      - sector 1: offset 0x00 to 0xFF 
 *      .
 *  - Any sector may be individualy erased 
 * 
 * @addtogroup HAL_FLASH
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

#define HAL_FLASH_MODULE_ID         0x6

/** This constant is used to retrieve the value of a blank flash memory cell. */
#define HAL_FLASH_BLANK_VALUE       0xFFFFFFFF


#define ERR_FLASH_PROGRAM       MAKE_ERROR(HAL_FLASH_MODULE_ID, 1)
#define ERR_FLASH_ERASE         MAKE_ERROR(HAL_FLASH_MODULE_ID, 2)
#define ERR_FLASH_INTEGRITY     MAKE_ERROR(HAL_FLASH_MODULE_ID, 3)
#define ERR_FLASH_PROTECT       MAKE_ERROR(HAL_FLASH_MODULE_ID, 4)
#define ERR_FLASH_UNPROTECT     MAKE_ERROR(HAL_FLASH_MODULE_ID, 5)
#define ERR_FLASH_NON_BLANK     MAKE_ERROR(HAL_FLASH_MODULE_ID, 6)
/** This internal flash specific error code is returned when the address is not 
 * correct */
#define ERR_FLASH_ADDRESS       MAKE_ERROR(HAL_FLASH_MODULE_ID, 7)
/** This internal flash specific error code is returned when a write or erase 
 * operation occured */
#define ERR_FLASH_TIMEOUT       MAKE_ERROR(HAL_FLASH_MODULE_ID, 8)
#define ERR_FLASH_BUZY          MAKE_ERROR(HAL_FLASH_MODULE_ID, 9)


/** This indicator must be used in hal_flash_get_info() to retrieve information 
 * about the whole flash memory */
#define HAL_FLASH_INFO_SECTOR_ALL 0xBABA

/** */
#define HAL_FLASH_STATE_NONAPPLICABLE  		0	

/** This state indicator is cleared if the requested sector is not 
 * write-protected */
#define HAL_FLASH_STATE_UNPROTECTED    		1

/** This state indicator is set if the requested sector is write-protected */
#define HAL_FLASH_STATE_PROTECTED      		2

/** */
#define HAL_FLASH_STATE_REMAPPED_SECTORS 	3

/** This event indicator is raised when the erase operation has finished */
#define HAL_FLASH_EVENT_ERASE       0

/** This event indicator is raised when the write operation has finished */
#define HAL_FLASH_EVENT_WRITE       1

/** This event indicator is raised when the compute signature operation 
 * has finished */
#define HAL_FLASH_EVENT_SIGN        2


/** Flash status : Total program/erase finished */
#define HAL_FLASH_STATUS_BSYN     (1<<0)  

/** Flash status : Flash bus lock request for program/erase is granted */
#define HAL_FLASH_STATUS_PROGGNT  (1<<1)  

/** Flash status : Flash ready flag raised if one of the following conditions is true,
 * \li synchronous read is completed
 * \li program/erase is suspended, read can start
 * \li program/erase has finished
 */
#define HAL_FLASH_STATUS_READY    (1<<2)  

/** Flash status : Positive high voltage is generated during program/erase */
#define HAL_FLASH_STATUS_HVONP    (1<<3)  

/** Flash status : Negative high voltage is generated during program/erase */
#define HAL_FLASH_STATUS_HVONN    (1<<4) 

/** Flash status : bit error was detected and correct */
#define HAL_FLASH_STATUS_ERROR    (1<<5)  

/** Flash status : All 0 check/pattern check passed */
#define HAL_FLASH_STATUS_CHECK0   (1<<6)  

/** Flash status : All 1 check/pattern check passed */
#define HAL_FLASH_STATUS_CHECK1   (1<<7)  

/*----------------------------------------------------------------------------
 * Information Structure
 */

/** 
 * The structure is used to retrieve informations about a specific sector or
 * about the whole flash memory. 
 */
typedef struct
{
    /** The sector number OR the number of sector in the whole flash memory */
    unsigned int sector;
    
    /** Base offset of the sector OR base address of the flash memory */
    unsigned int base;  
    
    /** Size of the sector OR size of the whole flash memory */
    unsigned int size;  
      
    /** State of the requested sector: 
     * \li #HAL_FLASH_STATE_NONAPPLICABLE 
     * \li #HAL_FLASH_STATE_REMAPPED_SECTORS 
     * \li #HAL_FLASH_STATE_UNPROTECTED 
     * \li #HAL_FLASH_STATE_PROTECTED 
     */  
    unsigned int state;
      
} HAL_FLASH_INFO;
 

/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function is used to retrieve information about a specified sector,
 * or about the whole flash memory (depend on the sector value).
 *
 * @param[in] sector        The sector number (0 to 35), if the parameter is 
 *                          equal to #HAL_FLASH_INFO_SECTOR_ALL, the returned 
 *                          informations are about the whole flash memory. 
 *
 * @param[out] param        A valid pointer to the informations.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_ADDRESS Invalid flash address 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */
int hal_flash_get_info( unsigned int sector, HAL_FLASH_INFO *param );

/**
 * The function erases the specified sector.
 *
 * @param[in] sector        Number of sector to erase (0 to 35) 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Flash not initialized 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_TIMEOUT Operation timed out 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_flash_erase( unsigned int sector );  


/**
 * The function locks the specified sector.
 *
 * @param[in] sector        Number of the sector to lock (0 to 35) 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Flash not initialized 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_TIMEOUT Operation timed out 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_flash_lock( unsigned int sector );

/**
 * The function writes a data buffer into the flash memory.
 *
 * The HAL implementation can assume that the specified sector was previously
 * erased by hal_flash_erase().
 *
 * @param[in] addr          Address to write in the Flash memory.
 *
 * @param[in] data          A pointer on the buffer containing the data to write.
 * 
 * @param[in] size          The length of the data to write. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Flash not initialized 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_ADDRESS Invalid flash address 
 * @retval -ERR_FLASH_TIMEOUT Operation timed out 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_flash_write( void *addr, void *data, unsigned int size );

/**
 * The function reads a data buffer from the flash memory.
 *
 * @param[in] data          A pointer on the data buffer to read.
 * 
 * @param[in] addr          Address to read in the Flash memory.
 * 
 * @param[in] size          The length of the data to read. 
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Flash not initialized 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_ADDRESS Invalid flash address 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */
int hal_flash_read( unsigned char *data, unsigned char *addr, int size );


/**
 * The function computes a 128-bit signature of the flash memory contents using 
 * the build-in signature generator. 
 *
 * @param[out] signature128 Pointer on the buffer that receive the signature result
 * 
 * @param[in] addr          start address 
 * 
 * @param[in] size          area size 
 * 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_ADDRESS Invalid flash address 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */
int hal_flash_sign128( void *addr, int size, unsigned int *signature128 );

/**
 * The function computes a 16-bit signature of the flash memory contents. 
 *
 * @param[out] signature16  Pointer on the buffer that receive the signature result
 * 
 * @param[in] addr          start address 
 * 
 * @param[in] size          area size 
 * 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_ADDRESS Invalid flash address 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */
int hal_flash_sign16( void *addr, int size, unsigned short *signature16 );

int hal_flash_otp_sign128( unsigned int offset, int size, unsigned int *signature128 );
int hal_flash_otp_sign16( unsigned int offset, int size, unsigned short *signature16 );


/**
 * The function writes a data buffer into the flash OTP memory. 
 * 
 * @param[in] offset        Offset of data to write in the Flash OTP memory 
 * 
 * @param[in] data          Pointer on the buffer containing the data to write 
 * 
 * @param[in] size          The length of the data to write 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_FLASH_ADDRESS Invalid flash address 
 * @retval -ERR_FLASH_TIMEOUT Operation timed out 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_flash_otp_write( unsigned int offset, void *data, int size );

/**
 * The function reads a data buffer from the flash OTP memory 
 * 
 * @param[in] data          A pointer on the data buffer to read 
 * 
 * @param[in] offset        Offset of data to read in the Flash OTP memory 
 * 
 * @param[in] size          The length of the data to read 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_FLASH_ADDRESS Invalid flash address 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_flash_otp_read( void *data,  unsigned int offset, int size );

/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_FLASH_EVENT_ERASE 
 *                          \li #HAL_FLASH_EVENT_WRITE 
 *                          \li #HAL_FLASH_EVENT_SIGN 
 * 
 * @param[in] handler       Pointer to the interrupt handler function.
 *                          Its declaration should support the parameters:
 *                          \li \e event Occured event
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Flash not initialized 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_flash_attach( int event, void (*handler)(int event) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_FLASH_EVENT_ERASE 
 *                          \li #HAL_FLASH_EVENT_WRITE 
 *                          \li #HAL_FLASH_EVENT_SIGN 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Flash not initialized 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_flash_detach( int event );

int hal_flash_suspend( void );
int hal_flash_resume( void );
int hal_flash_get_status( unsigned int *status );
int hal_flash_erase_sectors( unsigned int n, unsigned int *s );

/** @} */

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_flash_handler_t)(int event);

__hal_defunc2(hal_flash_get_info, unsigned int, sector, HAL_FLASH_INFO *, param);
__hal_defunc1(hal_flash_erase, unsigned int, sector);  
__hal_defunc1(hal_flash_lock, unsigned int, sector);
__hal_defunc3(hal_flash_write, void *, addr, void *, data, unsigned int, size);
__hal_defunc3(hal_flash_read, unsigned char *, data, unsigned char *, addr, int, size);
__hal_defunc3(hal_flash_sign16, void *, addr, int, size, unsigned int *, data);
__hal_defunc3(hal_flash_sign128, void *, addr, int, size, unsigned int *, data);
__hal_defunc3(hal_flash_otp_write, unsigned int, offset, void *, data, int, size);
__hal_defunc3(hal_flash_otp_read, void *, data, unsigned int, offset, int, size );
__hal_defunc2(hal_flash_attach, int, event, hal_flash_handler_t, handler);
__hal_defunc1(hal_flash_detach, int, event);
__hal_defunc0(hal_flash_suspend, void);
__hal_defunc0(hal_flash_resume, void);
__hal_defunc1(hal_flash_get_status, unsigned int *, status);
__hal_defunc0(hal_flash_otp_erase, void); /* For 400J only */
          
__hal_deisr(hal_flash_isr, void);
  
#endif /* CONFIG_LIBROM_NOT_INLINED */


#ifdef __cplusplus
}
#endif

#endif  /* HAL_USIP_FLASH_H */
