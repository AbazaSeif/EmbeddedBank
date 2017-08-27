/*============================================================================
 *
 *      hal_dma.h
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
 * Author(s):    Arnaud Ferir 
 * Contributors:  
 * Date:          
 * Purpose:       
 * Description:
 * 
 *==========================================================================*/
#ifndef HAL_USIP_DMA_H
#define HAL_USIP_DMA_H


/**
 *  
 * @defgroup HAL_DMA HAL DMA
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the DMA (Direct Memory Access).
 * 
 * @section Overview Overview 
 * 
 * The USIP® Professional DMA provides automatic one way data transfer between 
 * two entities. They could be indifferently memories or peripherals. These 
 * transfers are done without processor resources. 
 * 
 * \b Features
 * 
 * \li Makes 1D or 2D transfer 
 * \li Runs in FIFO mode (read/write always the same address). 
 * \li Resizes the word. 
 * \li Can run infinitely. 
 * 
 * @addtogroup HAL_DMA
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** status */
/** This status indicator is raised when a bus error occurs */
#define HAL_DMA_STATUS_BUSERR   2
/** This status indicator is raised when the transfer has ended */
#define HAL_DMA_STATUS_TREND    4
/** This status indicator is raised when the transfer is suspended */
#define HAL_DMA_STATUS_TRWAIT   8

/** events */
/** This event indicator is raised when a bus error occurs */
#define HAL_DMA_EVENT_ERR       0
/** This event indicator is raised when the transfer ends */
#define HAL_DMA_EVENT_END       1

/** configuration */
/** This configuration must be chosen to transfer 8-bits data size */
#define HAL_DMA_SIZE_8      0
/** This configuration must be chosen to transfer 16-bits data size */
#define HAL_DMA_SIZE_16     1
/** This configuration must be chosen to transfer 32-bits data size */
#define HAL_DMA_SIZE_32     2
/** This configuration must be chosen to use resize management */
#define HAL_DMA_RESIZE      1
/** This configuration must be chosen to use loop transfer */
#define HAL_DMA_LOOP        1


/*------------------------------------------------------------------------------
 * Control Enumeration
 */

/** The control enumeration defines the type of control performed on the DMA
 */
typedef enum {
	/** Start a DMA transfer */
	HAL_DMA_IOCTL_START,
	/** Suspend a DMA transfer */
	HAL_DMA_IOCTL_SET_WAIT,
	/** Restart a DMA transfer */
	HAL_DMA_IOCTL_CLEAR_WAIT,
	/** Select loop transfer */
	HAL_DMA_IOCTL_SET_LOOP,
	/** Unselect loop transfer */
	HAL_DMA_IOCTL_CLEAR_LOOP,
	/** Get current read address */
	HAL_DMA_IOCTL_GET_CURRENT_READ_ADDRESS,
	/** Get current write address */
	HAL_DMA_IOCTL_GET_CURRENT_WRITE_ADDRESS

} HAL_DMA_CONTROL ;


/*----------------------------------------------------------------------------
 * Configuration structure
 */

/** The configuration structure is used to set up the DMA */
typedef struct HAL_DMA_CONFIG {    
    
    /** Specify the start address of DMA transfer */
    unsigned int    start_address;
    /** Specify the arrival address of DMA transfer */
    unsigned int    arrival_address;

    /** Specify the size of read operations (width). Three sizes are available:
     *  #HAL_DMA_SIZE_8, #HAL_DMA_SIZE_16 or #HAL_DMA_SIZE_32 */
    unsigned int    read_size;
    /** Specify the size of write operations (width). Three sizes are available:
     *  #HAL_DMA_SIZE_8, #HAL_DMA_SIZE_16 or #HAL_DMA_SIZE_32 */
    unsigned int    write_size;
    /** Specify the use of resize management (#HAL_DMA_RESIZE) or (0) */
    unsigned int    resize;
    /** Specify the use of loop transfer (#HAL_DMA_LOOP) or (0) */
    unsigned int    loop;

    /** Specify the number of read operations (length) */
    unsigned short  read_number;
    /** Specify the number of write operations (length) */
    unsigned short  write_number;

    /** Specify the offset between two read operations */
    short           read_offset;
    /** Specify the offset between two write operations */
    short           write_offset;

    /** Specify the offset between two frame read operations */
    short           frame_read_offset;
    /** Specify the offset between two frame write operations */
    short           frame_write_offset;

    /** Specify the frame element number of read operations */
    unsigned short  frame_read_element;
    /** Specify the frame element number of write operations */
    unsigned short  frame_write_element;
      
} HAL_DMA_CONFIG;


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes and configures the DMA. 
 *
 * @param[in] pparams       A pointer on a DMA configuration structure 
 *                          allocated and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_dma_init( HAL_DMA_CONFIG *pparams );

/**
 * This function terminates the use of the DMA.
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_dma_shutdown( void );

/**
 * The function configures the DMA. The configuration is contained into a
 * dedicated structure. 
 *
 * @param[in] pparams       A pointer on a DMA configuration structure 
 *                          allocated and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_dma_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_dma_set_config( HAL_DMA_CONFIG *pparams );

/** 
 * The function provides the current state of the DMA.
 * 
 * @param[out] pstatus      Points on a variable allocated by the caller and 
 *                          and filled by the function with one of the 
 *                          following state indicators: 
 *                          \li #HAL_DMA_STATUS_BUSERR
 *                          \li #HAL_DMA_STATUS_TREND
 *                          \li #HAL_DMA_STATUS_TRWAIT
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_dma_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_dma_get_status( int *pstatus );

/**
 * The function performs a control on on the DMA.
 * parameter.
 * 
 * @param[in] control  	    The control to be performed. It's one of the 
 *                          following values:
 *                          \li #HAL_DMA_IOCTL_START
 *                          \li #HAL_DMA_IOCTL_SET_WAIT
 *                          \li #HAL_DMA_IOCTL_CLEAR_WAIT
 *                          \li #HAL_DMA_IOCTL_SET_LOOP
 *                          \li #HAL_DMA_IOCTL_CLEAR_LOOP
 *                          \li #HAL_DMA_IOCTL_GET_CURRENT_READ_ADDRESS
 *                          \li #HAL_DMA_IOCTL_GET_CURRENT_WRITE_ADDRESS
 * 
 * @param[out] data         Points on a variable that receives data from the 
 *                          given control function. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_dma_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_dma_ioctl( HAL_DMA_CONTROL control, unsigned int *data);

/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_DMA_EVENT_ERR 
 *                          \li #HAL_DMA_EVENT_END 
 * 
 * @param[in] handler       Pointer on the interrupt handler function.
 *                          Its declaration should support the parameter:
 *                          \li \e hevent Occured event
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_dma_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_dma_attach( int event, void (*handler)(int event));

/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_DMA_EVENT_ERR 
 *                          \li #HAL_DMA_EVENT_END 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_dma_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_dma_detach( int event);

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_dma_handler_t)(int event);

__hal_defunc1(hal_dma_init, HAL_DMA_CONFIG *, params);
__hal_defunc0(hal_dma_shutdown, void);
__hal_defunc1(hal_dma_set_config, HAL_DMA_CONFIG *, params);
__hal_defunc1(hal_dma_get_status, int *, status);
__hal_defunc2(hal_dma_ioctl, HAL_DMA_CONTROL, control, unsigned int *, data);
__hal_defunc2(hal_dma_attach, int, event, hal_dma_handler_t, handler);
__hal_defunc1(hal_dma_detach, int, event);

__hal_deisr(hal_dma_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* HAL_USIP_DMA_H */

