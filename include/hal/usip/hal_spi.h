/*============================================================================
 *
 *      hal_spi.h
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
 * Description:   This file contains the SPI Interface generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_SPI_H
#define HAL_USIP_SPI_H


/** 
 * 
 * @defgroup HAL_SPI HAL SPI Interface
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the SPI (Serial Peripheral Interface).
 * 
 * @section hal_spi Overview 
 * 
 * USIP® Professional provides a SPI port that is compliant with the Motorola 
 * standard. 
 * 
 * \b Features 
 * 
 * \li Programmable as either a master or slave interface 
 * \li Up to 7 slaves can be connected 
 * \li 2 FIFOs (RX, TX) 
 * \li Full and half duplex 
 * \li One-wire mode 
 * \li Programmable clock frequency 
 * \li Configurable clock polarity and clock phase (sampling options) 
 * \li Transfer status interrupts and flags 
 * 
 * @section spi_br Baudrate 
 * 
 * The following table gives an extensive list of the baudrates that can be 
 * generated in master mode. 
 * 
 * @htmlinclude baudrate.html 
 * 
 * The effective baudrate will be the greater baudrate below the value 
 * specified in #HAL_SPI_CONFIG configuration structure. 
 * 
 * \note The transmission speed in master mode is depending on the system 
 * clock frequency. This module should be re-configured if the system clock 
 * frequency is changed (see \link HAL_APM Advanced Power Management \endlink). 
 * 
 * @addtogroup HAL_SPI
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** Mode */
/** This configuration must be chosen to run in master mode */
#define		HAL_SPI_MODE_MASTER 			(1<<1)			
/** This configuration must be chosen to run in slave mode */
#define		HAL_SPI_MODE_SLAVE				(0<<1)

/** Extra Flags */
/** This extra flag must be set to select the one-wire mode.
 *  \n The SPI only uses one serial data pin (the MOSI pin) for the interface 
 *  with an external device. The pin direction (input/output) is commanded by 
 *  the READ bit in the Control Register 2. */
#define 	HAL_SPI_ONE_WIRE				(1<<2)	
/** This extra flag must be set to select the LSB first mode */
#define 	HAL_SPI_LSB_FIRST				(1<<8)	
/** This extra flag selects the clock polarity (sample data at rising or 
 *  falling edge of clock line) */
#define 	HAL_SPI_CLOCK_POLARITY			(1<<9)
/** This extra flag selects the clock phase (shift data change) */
#define 	HAL_SPI_CLOCK_PHASE				(1<<10)
/** This extra flag must be set to select the full duplex mode (if selected the 
 *  SPI interface can transmit a word and receive another one at the same time) 
 */
#define 	HAL_SPI_FULL_MODE				(1<<11)

/** Word size */
/** This configuration sets the word size to 16 bits */
#define 	HAL_SPI_WORD_SIZE_16			(0<<3)
/** This configuration sets the word size to 4 bits */
#define 	HAL_SPI_WORD_SIZE_4				(1<<3)
/** This configuration sets the word size to 8 bits */
#define 	HAL_SPI_WORD_SIZE_8				(2<<3)
/** This configuration sets the word size to 12 bits */
#define 	HAL_SPI_WORD_SIZE_12			(3<<3)
 
/** Slave device */
/** This configuration selects the slave device CS1 */
#define		HAL_SPI_CS_ONE					1
/** This configuration selects the slave device CS2 */
#define		HAL_SPI_CS_TWO					2
/** This configuration selects the slave device CS3 */
#define		HAL_SPI_CS_THREE				4


/** This state indicator is raised when a transfer is running */
#define 	HAL_SPI_STATE_BUSY			(1<<0)
/** This state indicator gives the SS pin state */
#define 	HAL_SPI_STATE_SSST			(1<<1)
/** This state indicator is raised when the receive FIFO is empty */
#define 	HAL_SPI_STATE_FFREPY		(1<<4)
/** This state indicator is raised when the receive FIFO is full */
#define 	HAL_SPI_STATE_FFRFULL		(1<<5)
/** This state indicator is raised when the transmit FIFO is empty */
#define 	HAL_SPI_STATE_FFTEPY		(1<<6)
/** This state indicator is raised when the transmit FIFO is full */
#define 	HAL_SPI_STATE_FFTFULL		(1<<7)

/** This state indicator is raised when a bus error occured */
#define 	HAL_SPI_STATE_BUSST			(1<<(0+8))
/** This state indicator is raised when a communication ends */
#define 	HAL_SPI_STATE_COMEND		(1<<(1+8))
/** This state indicator is raised when a size error occured */
#define 	HAL_SPI_STATE_SIZE			(1<<(2+8))
/** This state indicator is raised when a word is received */
#define 	HAL_SPI_STATE_FFRX			(1<<(4+8))
/** This state indicator is raised when the last word is to be transmitted */
#define 	HAL_SPI_STATE_FFTXO			(1<<(5+8))
/** This state indicator is raised when the transmit FIFO is half empty */
#define 	HAL_SPI_STATE_FFTXH			(1<<(6+8))


/** This event indicator is raised when a bus error interrupt occured */
#define HAL_SPI_EVENT_BUSST    0
/** This event indicator is raised when a communication end interrupt occured */
#define HAL_SPI_EVENT_COMEND   1
/** This event indicator is raised when a size error interrupt occured */
#define HAL_SPI_EVENT_SIZE     2
/** This event indicator is raised when a receive FIFO interrupt occured */
#define HAL_SPI_EVENT_FFRX     3
/** This event indicator is raised when a transmit FIFO interrupt occured 
 *  (one word)*/
#define HAL_SPI_EVENT_FFTXO    4
/** This event indicator is raised when a transmit FIFO interrupt occured 
 *  (four words) */
#define HAL_SPI_EVENT_FFTXH    5


/*----------------------------------------------------------------------------
 * Control Enumeration
 */

/** The control enumeration defines the type of control on the SPI interface 
 */
typedef enum {
	/** Specify the threshold of reception fifo */
	HAL_SPI_IOCTL_FIFORX_THRESHOLD,
	
	/** Specify the device to be select */
	HAL_SPI_IOCTL_SELECT_DEVICE,
	
	/** Specify the device to be unselect */
	HAL_SPI_IOCTL_UNSELECT_DEVICE,
	
	/** Acknowledge the occured interrupts */
	HAL_SPI_IOCTL_CLEAR_INTERRUPT,
	
	/** Disable the SPI module (the configuration is maintained) */
	HAL_SPI_IOCTL_DISABLE,
	
	/** Enable the SPI module */
	HAL_SPI_IOCTL_ENABLE,
	
	/** Set read direction in half duplex mode */
	HAL_SPI_IOCTL_HALF_READ,
	
	/** Set write direction in half duplex mode */
	HAL_SPI_IOCTL_HALF_WRITE,
	
	/** Start a transfer */
	HAL_SPI_IOCTL_START,
	
	/** Clear START bit (used after write transfer in half duplex mode) */
	HAL_SPI_IOCTL_CLEAR_START,
	
	/** Stop the current operation */
	HAL_SPI_IOCTL_STOP,
	
	/** Clear STOP bit */
	HAL_SPI_IOCTL_CLEAR_STOP,
	
	/** Reset the receive FIFO */
	HAL_SPI_IOCTL_RESET_RX_FIFO,
	
	/** Reset the transmit FIFO */
	HAL_SPI_IOCTL_RESET_TX_FIFO

} HAL_SPI_CONTROL ;


/*----------------------------------------------------------------------------
 * Configuration Structure
 */
     
/** The configuration structure is used to set up the SPI interface */
typedef struct HAL_SPI_CONFIG
{
	/** Specify the baud rate of communication.\n
     *  
	 */
	unsigned int baudrate;

	/** Specify the threshold of interruption of reception FIFO: beetween one 
	 * and eight words. 
	 */
   	unsigned int fiforxth;

	/** Specify the size in bits of word used during the exchange: 
	 *  #HAL_SPI_WORD_SIZE_16 , #HAL_SPI_WORD_SIZE_4 , #HAL_SPI_WORD_SIZE_8 or 
     *  #HAL_SPI_WORD_SIZE_12
	 */
   	unsigned int wordsize;

	/** Specify the specific options of the communication: an orred combination  
	 *  of the following values :
	 *  @li #HAL_SPI_ONE_WIRE
	 *  @li #HAL_SPI_LSB_FIRST
	 *  @li #HAL_SPI_CLOCK_POLARITY
	 *  @li #HAL_SPI_CLOCK_PHASE
	 *  @li #HAL_SPI_FULL_MODE
	 */
   	unsigned int exflags;
   	
   	
   	/** Specify the mode of communication #HAL_SPI_MODE_MASTER or 
   	 *  #HAL_SPI_MODE_SLAVE
	 */
   	unsigned int mode;

} HAL_SPI_CONFIG;


/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures the SPI interface. 
 * 
 * @param[in] pparams		A pointer on SPI configuration structure allocated 
 * 							and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_spi_init( HAL_SPI_CONFIG *pparams );


/**
 * The function disables the SPI interface. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_spi_shutdown( void );


/**
 * The function configures the SPI interface. 
 * 
 * @param[in] pparams		A pointer on SPI configuration structure allocated 
 * 							and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_spi_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_spi_set_config( HAL_SPI_CONFIG *pparams );
							  

/**
 * The function performs a specific control on the SPI Interface.
 *
 * @param[in] control       The control to be performed.
 * 
 * @param[in] data			Any data required for the given control function.
 *                          \li #HAL_SPI_IOCTL_FIFORX_THRESHOLD control: data is 
 *                          filled with a decimal value bounded between 1 and 8 
 * 							\li #HAL_SPI_IOCTL_SELECT_DEVICE control: data is 
 *                          filled with #HAL_SPI_CS_ONE, #HAL_SPI_CS_TWO or 
 *                          #HAL_SPI_CS_THREE 
 * 							\li #HAL_SPI_IOCTL_UNSELECT_DEVICE control: data is 
 *                          filled with #HAL_SPI_CS_ONE, #HAL_SPI_CS_TWO or 
 *                          #HAL_SPI_CS_THREE 
 *                          \note Parameter data not checked if not required
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_spi_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 */
int hal_spi_ioctl( HAL_SPI_CONTROL control, int data );


/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_SPI_EVENT_BUSST 
 *                          \li #HAL_SPI_EVENT_COMEND 
 *                          \li #HAL_SPI_EVENT_SIZE 
 *                          \li #HAL_SPI_EVENT_FFRX 
 *                          \li #HAL_SPI_EVENT_FFTXO 
 *                          \li #HAL_SPI_EVENT_FFTXH 
 * 
 * @param[in] handler       Pointer to the interrupt handler function.
 *                          Its declaration should support the parameters:
 *                          \li \e event Occured event
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_spi_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_spi_attach( int event, void (*handler)(int));


/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_SPI_EVENT_BUSST 
 *                          \li #HAL_SPI_EVENT_COMEND 
 *                          \li #HAL_SPI_EVENT_SIZE 
 *                          \li #HAL_SPI_EVENT_FFRX 
 *                          \li #HAL_SPI_EVENT_FFTXO 
 *                          \li #HAL_SPI_EVENT_FFTXH 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_spi_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_spi_detach( int event);

/**
 * The function is used to retrieve the status of SPI module. 
 *                          
 * @param[out] pstatus      A pointer on a variable allocated by the caller 
 *                          and filled by the function with the state of SPI 
 *                          module. It is a combination of the following 
 *                          values :
 *                          \li #HAL_SPI_STATE_BUSY
 *                          \li #HAL_SPI_STATE_SSST
 *                          \li #HAL_SPI_STATE_FFREPY
 *                          \li #HAL_SPI_STATE_FFRFULL
 *                          \li #HAL_SPI_STATE_FFTEPY
 *                          \li #HAL_SPI_STATE_FFTFULL
 *                          \li #HAL_SPI_STATE_BUSST
 *                          \li #HAL_SPI_STATE_COMEND
 *                          \li #HAL_SPI_STATE_SIZE
 *                          \li #HAL_SPI_STATE_FFRX
 *                          \li #HAL_SPI_STATE_FFTXO
 *                          \li #HAL_SPI_STATE_FFTXH
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_spi_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */   
int hal_spi_get_status( unsigned int *pstatus);


/**
 * The function performs a write operation on the SPI device. 
 * The function allows to write up to eight characters in one time.
 * 
 * @param[in] pdata         A pointer on an array allocated and filled by the 
 * 							caller with the data to be sent. 
 * 							
 * @param[in,out] plength  	A pointer allocated and filled by the caller 
 * 							with the length of the data to be written. 
 *                          The function will decrease this value according to 
 *                          the data that have been sent. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_spi_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    							  
int hal_spi_write( unsigned char *pdata, unsigned int *plength );


/**
 * The function performs a read operation on the SPI device. 
 * The function allows to read up to eight data in one time. 
 * 
 * @param[out] pdata        A pointer on an array allocated by the caller 
 * 							and filled by the function with the read data. 
 * 
 * @param[in,out] plength   A pointer allocated and filled by the caller 
 * 							with the length of the data to be read. 
 * 							The function sets this value with the length of 
 *                          data actually read. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_spi_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */    				
int hal_spi_read( unsigned char *pdata, unsigned int *plength );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_spi_handler_t)(int);

__hal_defunc1(hal_spi_init, HAL_SPI_CONFIG *, params);
__hal_defunc0(hal_spi_shutdown, void);
__hal_defunc1(hal_spi_set_config, HAL_SPI_CONFIG *, params);
__hal_defunc2(hal_spi_ioctl, HAL_SPI_CONTROL, control, int, data);
__hal_defunc2(hal_spi_attach, int, event, hal_spi_handler_t, handler);
__hal_defunc1(hal_spi_detach, int, event);
__hal_defunc1(hal_spi_get_status, unsigned int *, status);
__hal_defunc2(hal_spi_write, unsigned char *, data, unsigned int *, length);
__hal_defunc2(hal_spi_read, unsigned char *, data, unsigned int *, length);

__hal_deisr(hal_spi_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /*  HAL_USIP_SPI_H */

