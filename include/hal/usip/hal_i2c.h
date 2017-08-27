/*============================================================================
 *
 *      hal_i2c.h
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
 * Author(s):     Stephane Royo 
 * Contributors:  Arnaud Ferir
 * Date:          
 * Purpose:       
 * Description:
 * 
 *==========================================================================*/
#ifndef __HAL_USIP_I2C_H__
#define __HAL_USIP_I2C_H__	

/** 
 * 
 * @defgroup HAL_I2C HAL I2C Interface
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the I2C bus (Inter Integrated Circuit).
 * 
 * @section hal_i2c Overview 
 * 
 * USIP® Professional provides a I2C port that is compliant with Philips I2C 
 * standard. 
 * 
 * \b Features 
 * 
 * \li I2C bus specification version 2.1 (100Khz and 400Khz) compliant 
 * \li Programmable for both normal (100Khz) and fast bus data rates (400Khz)  
 * \li Programmable as either a master or slave interface 
 * \li Programmable for using a normal or extended addressing (7 or 10 bits) 
 * \li Able of clock synchronization and bus arbitration 
 * \li Fully programmable slave response address 
 * \li 2 FIFOs (RX, TX) 
 * \li Supports I2C bus hold for slow host service 
 * \li Transfer status interrupts and flags 
 * 
 * @section i2c_br Baudrate 
 * 
 * The following table gives an extensive list of the baudrates that can be 
 * generated in master mode. 
 * 
 * @htmlinclude baudrate.html 
 * 
 * The effective baudrate will be the greater baudrate below the value 
 * specified in #HAL_I2C_CONFIG configuration structure. 
 * 
 * \note The transmission speed in master mode is depending on the system 
 * clock frequency. This module should be re-configured if the system clock 
 * frequency is changed (see \link HAL_APM Advanced Power Management \endlink). 
 * 
 * @addtogroup HAL_I2C
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** Mode: Set the device to run in master mode */
#define		HAL_I2C_MODE_MASTER 			1
/** Mode: Set the device to run in slave mode */
#define		HAL_I2C_MODE_SLAVE				0

/** Extra flags: Set the device to run in fast mode */
#define		HAL_I2C_FAST_MODE				0x02
/** Extra flags: Set the I2C address of the device as a ten bit-address */
#define 	HAL_I2C_TEN_BIT_ADDRESSING		0x04
/** Extra flags: Set the communication to start automatically when a word is in 
 *  the transmit FIFO */
#define	 	HAL_I2C_AUTO_START_TX			0x08


/** This state indicator is raised when a transfer is running */
#define 	HAL_I2C_STATE_BUSY				0x01
/** This state indicator is raised when the bus is frozen */
#define 	HAL_I2C_STATE_SLEEP				0x02
/** This state indicator is raised when the slave does not answer the transfer */
#define 	HAL_I2C_STATE_NOANS				0x04
/** This state indicator is raised when the receive FIFO is empty */
#define 	HAL_I2C_STATE_FFREPY			0x10
/** This state indicator is raised when the receive FIFO is full */
#define 	HAL_I2C_STATE_FFRFULL			0x20
/** This state indicator is raised when the transmit FIFO is empty */
#define 	HAL_I2C_STATE_FFTEPY			0x40
/** This state indicator is raised when the transmit FIFO is full */
#define 	HAL_I2C_STATE_FFTFULL			0x80

/** This state indicator is raised when the current transfer is lost (due to
 *  another master) */
#define 	HAL_I2C_STATE_LOST				0x0100
/** This state indicator is raised in master mode when another master attempts
 *  to access the cell */
#define 	HAL_I2C_STATE_BUSST				0x0200
/** This state indicator is raised when the communication ends */
#define 	HAL_I2C_STATE_COMEND			0x0400
/** This state indicator is raised when the current transfer is finished */
#define 	HAL_I2C_STATE_RDYRD				0x0800
/** This state indicator is raised when the receive FIFO has reached the number
 *  of characters specified by #HAL_I2C_IOCTL_FIFORX_THRESHOLD */
#define 	HAL_I2C_STATE_FFRX				0x1000
/** This state indicator is raised when the transmit FIFO is half filled */
#define 	HAL_I2C_STATE_FFTXH				0x4000


/** This event indicator is raised when a lost communication interrupt occured */
#define HAL_I2C_EVENT_LOST     0

/** This event indicator is raised when a bus error interrupt occured */
#define HAL_I2C_EVENT_BUSST    1

/** This event indicator is raised when a communication end interrupt occured */
#define HAL_I2C_EVENT_COMEND   2

/** This event indicator is raised when a ready to read interrupt occured */
#define HAL_I2C_EVENT_RDYRD    3

/** This event indicator is raised when a receive FIFO interrupt occured */
#define HAL_I2C_EVENT_FFRX     4

/** This event indicator is raised when a transmit FIFO interrupt occured
 * 	(one word received) */
#define HAL_I2C_EVENT_FFTXO    5

/** This event indicator is raised when a transmit FIFO interrupt occured 
 * 	(four words received) */
#define HAL_I2C_EVENT_FFTXH    6


/*------------------------------------------------------------------------------
   Control Enumeration
*/

/** The control enumeration defines the type of control on the I2C interface 
 */
typedef enum {
	/** Specifies the threshold of reception fifo */
	HAL_I2C_IOCTL_FIFORX_THRESHOLD = 0x5500,
	
	/** Disables the I2C module but the configuration is maintained. */
	HAL_I2C_IOCTL_DISABLE=0x00C0,
	
	/** Enables the I2C module. */
	HAL_I2C_IOCTL_ENABLE,
	
	/** Activates the ability of I2C to generate a repeated start condition
	 *  when the current transfer ends */
	HAL_I2C_IOCTL_SET_AFREAD,
	
	/** Deactivates the ability of I2C to generate a repeated start condition
	 *  when the current transfer ends */
	HAL_I2C_IOCTL_CLEAR_AFREAD,
	
	/** Reset the transmit FIFO */
	HAL_I2C_IOCTL_RESET_FIFOTX,
	
	/** Activates the auto acknoledgement (usually used in mode SLAVE) */
	HAL_I2C_IOCTL_SET_ACK,
	
	/** Deactivates the auto acknoledgement (usually used in mode SLAVE) */
	HAL_I2C_IOCTL_CLEAR_ACK,
	
	/** Activates the capabilitie of I2C to freeze the bus clock during 
	 *  a reading operation if the transmission FIFO is empty
	 */
	HAL_I2C_IOCTL_SET_CLKMNG,
	
	/** Deactivates the capabilitie of I2C to freeze the bus clock during 
	 *  a reading operation if the transmission FIFO is empty
	 */
	HAL_I2C_IOCTL_CLEAR_CLKMNG
	
} HAL_I2C_CONTROL ;


/*------------------------------------------------------------------------------
   Configuration Structure
*/
     
/** The configuration structure is used to set up the I2C interface */
typedef struct HAL_I2C_CONFIG
{

	/** Specify the baud rate of communication (bps)
	*/
	unsigned int baudrate;

	/** Specify the address of device on the bus. The binary value should be 
     *  written as follows:
	 *  \li 7-bits address: 0000 0000 AAAA AAA0
	 *  \li 10-bits address: 1111 0AA0 AAAA AAAA
     * 
     *  Not used in master mode 
	 */
	unsigned int address;

    /** Specifiy the threshold of interruption of reception FIFO. This 
     *  threshold is comprised beetween one and eight characters. 
	 */
   	unsigned int fiforxth;

    /** Specify the specific options whatever the properties of communication. 
     * It's one or a combination of the following value:
     * @li HAL_I2C_FAST_MODE
     * @li HAL_I2C_TEN_BIT_ADDRESSING
     * @li HAL_I2C_AUTO_START_TX
     */
   	unsigned int exflags;

   	/** Specify the mode of communication. It's one of the following value: 
	 * @li HAL_I2C_MODE_MASTER 
	 * @li HAL_I2C_MODE_SLAVE
	 */
   	unsigned int mode;

} HAL_I2C_CONFIG;

/*----------------------------------------------------------------------------
 * Function declarations
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes a session with the I2C device and configures
 * the I2C interface. The configuration is contained into a dedicated structure. 
 *
 * @param[in] pparams		A pointer on I2C configuration structure allocated 
 *                          and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_i2c_init( HAL_I2C_CONFIG *pparams );


/**
 * The function ends the session with the I2C device and disables the I2C
 * interface.  
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_i2c_shutdown( void );


/**
 * The function configures the I2C interface. The configuration is contained 
 * into a dedicated structure. 
 *
 * @param[in] pparams       A pointer on I2C configuration structure allocated 
 *                          and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_i2c_set_config( HAL_I2C_CONFIG *pparams );


/**
 * The function performs a specific control on the I2C Interface.
 *
 * @param[in] control  		The control to be performed. 
 * 
 * @param[in] data          Any data required for the given control function: 
 *                          \li #HAL_I2C_IOCTL_FIFORX_THRESHOLD control: data 
 *                          filled with a decimal value between 1 and 8. 
 *                          \li other control: data not used. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_i2c_ioctl( HAL_I2C_CONTROL 	control, int data );


/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_I2C_EVENT_LOST 
 *                          \li #HAL_I2C_EVENT_BUSST 
 *                          \li #HAL_I2C_EVENT_COMEND 
 *                          \li #HAL_I2C_EVENT_RDYRD 
 *                          \li #HAL_I2C_EVENT_FFRX 
 *                          \li #HAL_I2C_EVENT_FFTXO 
 *                          \li #HAL_I2C_EVENT_FFTXH 
 * 
 * @param[in] handler       Pointer to the interrupt handler function.
 *                          Its declaration should support the parameters: 
 *                          \li \e event Occured event 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_i2c_attach( int event, void (*handler)(int event));


/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_I2C_EVENT_LOST 
 *                          \li #HAL_I2C_EVENT_BUSST 
 *                          \li #HAL_I2C_EVENT_COMEND 
 *                          \li #HAL_I2C_EVENT_RDYRD 
 *                          \li #HAL_I2C_EVENT_FFRX 
 *                          \li #HAL_I2C_EVENT_FFTXO 
 *                          \li #HAL_I2C_EVENT_FFTXH 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_i2c_detach( int event);

/**
 * The function retrieves the status and interrupt state of I2C module. 
 * 
 * @param[out] pstatus 		A pointer on a variable allocated by the caller and 
 * 							filled by the function with the status of I2C 
 * 							module. It's one or a combination of the following 
 * 							values :
 * 							\li #HAL_I2C_STATE_BUSY
 * 							\li #HAL_I2C_STATE_SLEEP	
 * 							\li #HAL_I2C_STATE_NOANS	
 * 							\li #HAL_I2C_STATE_FFREPY		
 * 							\li #HAL_I2C_STATE_FFRFULL		
 * 							\li #HAL_I2C_STATE_FFTEPY		
 * 							\li #HAL_I2C_STATE_FFTFULL
 * 							\li #HAL_I2C_STATE_LOST
 * 							\li #HAL_I2C_STATE_BUSST
 * 							\li #HAL_I2C_STATE_COMEND
 * 							\li #HAL_I2C_STATE_RDYRD
 * 							\li #HAL_I2C_STATE_FFRX
 * 							\li #HAL_I2C_STATE_FFTXH
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */   
int hal_i2c_get_status( unsigned short *pstatus );


/**
 * The function initializes a write operation and to write up to five bytes 
 * into the I2C device. 
 * 
 * @note \b Usage: To write more than 5 bytes, use hal_i2c_start_write() for 
 * the 5 first bytes, then use consecutive calls to hal_i2c_write() to complete 
 * the transmission. 
 * 
 * @param[in] address       The address of device on the bus
 *                          \li 7-bit address Pattern: 0000 0000 xxxx xxx0
 *                          \li 10-bit address Pattern: 1111 0xx0 xxxx xxxx
 * 
 * @param[in] pchar         A pointer on byte array allocated by the caller 
 *                          and filled with the data to be sent. 
 * 
 * @param[in,out] plength   A pointer on variable allocated and filled by the 
 *                          caller with the length of data to be sent. The 
 *                          function fills the variable with the length of data 
 *                          that have not been sent. This function cannot send 
 *                          more than 5 data.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_AGAIN       Try again later. Transmit FIFO not empty.
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */   
int hal_i2c_start_write( unsigned short address,
				   		 unsigned char *pchar, 
				   		 unsigned int  *plength );


/**
 * The function writes up to 8 data into the I2C device. 
 * 
 * @warning This function must not be used before initializing a write 
 * operation with hal_i2c_start_write(). 
 * 
 * @note \b Usage: To write more than 5 bytes, use hal_i2c_start_write() for 
 * the 5 first bytes, then use consecutive calls to hal_i2c_write() to complete 
 * the transmission. 
 * 
 * @param[in] pchar         A pointer on byte array allocated by the caller 
 * 							and filled with the data to be send. 
 * 
 * @param[in,out] plength	A pointer on variable allocated and filled by the 
 *                          caller with the length of data to be sent. The 
 *                          function fills the variable with the length of data 
 *                          that have not been sent. This function cannot send 
 *                          more than 8 data.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_i2c_write( unsigned char *pchar, unsigned int *plength );


/**
 * The function initializes a read operation, but does not allow to read any 
 * data. Data can be read with hal_i2c_read(). 
 * 
 * @param[in] address       The address of device on the bus
 *                          \li 7-bit address Pattern: 0000 0000 xxxx xxx0
 *                          \li 10-bit address Pattern: 1111 0xx0 xxxx xxxx
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_AGAIN       Try again later. Transmit FIFO not empty.
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  			
int hal_i2c_start_read( unsigned short address );


/**
 * The function reads up to 8 data from a I2C device. 
 * 
 * @warning This function must not be used before having initialized a read 
 * operation by calling hal_i2c_start_read(). 
 * 
 * @note \b Usage: To read more than 8 bytes, use hal_i2c_start_read(), then 
 * use consecutive calls to hal_i2c_read() to complete the reception. When 
 * completed the read operation must be ended by calling hal_i2c_stop_read(). 
 * 
 * @param[in] pchar         Pointer on an array allocated by the caller and 
 *                          filled by the function with the read data. 
 * 
 * @param[in,out] plength   Pointer on a variable allocated and filled by the 
 *                          caller with the number of data to be read. This 
 *                          pointer on variable is finally filled by the 
 *                          function with the number of data actually read. The 
 *                          of read data cannot be greater than 8. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_i2c_read( unsigned char *pchar, unsigned int *plength );


/**
 * The function stops any read operation. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_i2c_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_i2c_stop_read( void );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_i2c_handler_t)(int event);
 
__hal_defunc1(hal_i2c_init, HAL_I2C_CONFIG *, params);
__hal_defunc0(hal_i2c_shutdown, void);
__hal_defunc1(hal_i2c_set_config, HAL_I2C_CONFIG *, params);
__hal_defunc2(hal_i2c_ioctl, HAL_I2C_CONTROL, control, int, data);
__hal_defunc2(hal_i2c_attach, int, event, hal_i2c_handler_t, handler);
__hal_defunc1(hal_i2c_detach, int, event);
__hal_defunc1(hal_i2c_get_status, unsigned short *, status);
__hal_defunc3(hal_i2c_start_write, unsigned short, address, unsigned char *, pchar, unsigned int *, plength);
__hal_defunc2(hal_i2c_write, unsigned char *, pchar, unsigned int *, plength);
__hal_defunc1(hal_i2c_start_read, unsigned short, address);
__hal_defunc2(hal_i2c_read, unsigned char *, pchar, unsigned int *, plength);
__hal_defunc0(hal_i2c_stop_read, void);
        
__hal_deisr(hal_i2c_isr, void);
      
#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /*  __HAL_USIP_I2C_H__ */

	

