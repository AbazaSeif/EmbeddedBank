/*============================================================================
 *
 *      hal_uart.h
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
 * Author(s):     Arnaud Corria 
 * Contributors:  Stephane Royo
 * Date:          
 * Purpose:       
 * Description:   This file contains the UART Interface generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_UART_H
#define HAL_USIP_UART_H


/**
 *  
 * @defgroup HAL_UART HAL UART Interface
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the UART Interface (Universal Asynchronous 
 * Receiver Transmitter).
 * 
 * @section Overview Overview 
 * 
 * USIP® Professional provides up to 4 UARTs. Furthermore one of them 
 * can be setup as an IrDA Interface and another one provides modem management. 
 * 
 * The first UART is dedicated to IrDA (Infrared Data Association). It provides 
 * a serial InfraRed protocol. 
 * 
 * The second UART is dedicated to modem management. An external modem 
 * component can be connected directly to USIP® through this UART thanks to a 
 * complete set of modem signals (RTS/CTS/DSR/DTR/DCD/RI). 
 * 
 * The two last ones are basic 16C550 compatible UARTs.
 * 
 * \b Features
 * 
 * \li Programmable baud rate generator up to 6Mbps
 * \li 5, 6, 7 or 8 data bits
 * \li 1 or 2 stop bits
 * \li Odd parity, even parity or no parity
 * \li Receive and transmiut FIFOs with programmable trigger level
 * \li Interrupts generation
 * \li Modem control signals (only for the “modem” UART): CTS, RTS, DSR, DTR, 
 * RI and DCD
 * 
 * \note The transmission baud rate is depending on the system clock frequency. 
 * This module should be re-configured if the system clock frequency is changed 
 * (see \link HAL_APM Advanced Power Management \endlink). 
 * 
 * @addtogroup HAL_UART
 * 
 * @{
 */


/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/
 
/** Set the parity to No Parity */
#define HAL_UART_PARITY_NONE   0x00
/** Set the parity to Even Parity */
#define HAL_UART_PARITY_EVEN   0x01
/** Set the parity to Odd Parity */
#define HAL_UART_PARITY_ODD    0x03

/** Set the stop bit length to 1 stop bit */
#define HAL_UART_STOP_BIT_1    0x00
/** Set the stop bit length to 2 stop bits */
#define HAL_UART_STOP_BIT_2    0x01

/** Set the data length to 8 bits */
#define HAL_UART_DATA_BITS_8   0x00
/** Set the data length to 7 bits */
#define HAL_UART_DATA_BITS_7   0x02
/** Set the data length to 6 bits */
#define HAL_UART_DATA_BITS_6   0x01
/** Set the data length to 5 bits */
#define HAL_UART_DATA_BITS_5   0x03

/** Set the IRDA rate at 1/4 clock period */
#define HAL_UART_FLAG_IRDA_RATE_1_4  (1<<3)
/** Set the IRDA rate at 3/16 clock period */
#define HAL_UART_FLAG_IRDA_RATE_3_16 (0)
/** Set the IrDA output active low 
 *  according to the external transceiver used */
#define HAL_UART_FLAG_IRDA_ACTIVE_LOW (1<<5)
/** Set the IrDA output active high 
 *  according to the external transceiver used */
#define HAL_UART_FLAG_IRDA_ACTIVE_HIGH (0)

/**
 * Enable CTS handshaking. The handler lowers the CTS line before begining 
 * the data transmission.
 */
#define HAL_UART_FLAG_IN_CTS_FLOW    (1<<3)
/**
 * Enable RTS handshaking. The handler lowers the RTS line when the
 * input buffer is more than three-quarters full.
 */
#define HAL_UART_FLAG_IN_RTS_FLOW    (2<<3)

/** Set the UART mode to No Specific Mode */
#define HAL_UART_MODE_NONE          0x00
/** 
 * Set the UART mode to IrDa 
 * @note This mode is only available on the device identified by hal_uart_dev0   
 */
#define HAL_UART_MODE_IRDA          0x02
/** 
 * Set the UART mode to Data Terminal Equipment (DTE)
 * @note This mode is only available on the device identified by hal_uart_dev1  
 */
#define HAL_UART_MODE_MODEM_DTE     0x02
/** 
 * Set the UART mode to Data Communication Equipment (DCE) 
 * @note This mode is only available on the device identified by hal_uart_dev1  
 */
#define HAL_UART_MODE_MODEM_DCE     0x22

/** Set the baud rate to 1200 bit/s */
#define HAL_UART_BAUDRATE_1200      1200
/** Set the baud rate to 2400 bit/s */
#define HAL_UART_BAUDRATE_2400      2400
/** Set the baud rate to 4800 bit/s */
#define HAL_UART_BAUDRATE_4800      4800
/** Set the baud rate to 9600 bit/s */
#define HAL_UART_BAUDRATE_9600      9600
/** Set the baud rate to 19200 bit/s */
#define HAL_UART_BAUDRATE_19200     19200
/** Set the baud rate to 38400 bit/s */
#define HAL_UART_BAUDRATE_38400     38400
/** Set the baud rate to 57600 bit/s */
#define HAL_UART_BAUDRATE_57600     57600
/** Set the baud rate to 115200 bit/s */
#define HAL_UART_BAUDRATE_115200    115200
/** Set the baud rate to 128000 bit/s */
#define HAL_UART_BAUDRATE_128000    128000
/** Set the baud rate to 230400 bit/s */
#define HAL_UART_BAUDRATE_230400    230400
/** Set the baud rate to 921600 bit/s */
#define HAL_UART_BAUDRATE_921600    921600

/** This state indicator is raised when a frame error interrupt has occured 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_FRAME_ERROR         (1<<0)
/** This state indicator is raised when a false start interrupt has occured 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_START_ERROR         (1<<1)
/** This state indicator is raised when a parity error interrupt has occured 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_PARITY_ERROR        (1<<2)
/** This state indicator is raised when a MODEM signal interrupt has occured 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_MODEM_LINE_CHANGED  (1<<3) 
/** This state indicator is raised when an interrupt has occured 
 * on the FIFO of transmission 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_TX_FIFO             (1<<4)
/** This state indicator is raised when the reception FIFO full interrupt has 
 *  occured 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_RX_FIFO_FULL        (1<<5)
/** This state indicator is raised when the reception FIFO half full interrupt 
 *  has occured 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_RX_FIFO_HALF        (1<<6)
/** This state indicator is raised when the reception FIFO interrupt has occured 
 *  @note This indicator is still raised while the status is not read even if 
 *  the cause disappeared */
#define HAL_UART_STATUS_INTR_RX_FIFO_ONE         (1<<7)

/** This state indicator is raised when the reception FIFO is empty */
#define HAL_UART_STATUS_RX_FIFO_EMPTY       (1<<8)
/** This state indicator is raised when the reception FIFO is full */
#define HAL_UART_STATUS_RX_FIFO_FULL        (1<<9)
/** This state indicator is raised when the transmission FIFO is empty */
#define HAL_UART_STATUS_TX_FIFO_EMPTY       (1<<10)
/** This state indicator is raised when the transmission FIFO is full */
#define HAL_UART_STATUS_TX_FIFO_FULL        (1<<11) 
/** This state indicator is raised when the UART is receiving data */
#define HAL_UART_STATUS_RX_BUSY             (1<<12)
/** This state indicator is raised when the UART is transmitting data */
#define HAL_UART_STATUS_TX_BUSY             (1<<13)

/** Specific State in modem configuration : CTS value changed */
#define HAL_UART_STATUS_CTS_CHANGED         (1<<16)
/** Specific State in modem configuration : DSR value changed */
#define HAL_UART_STATUS_DSR_CHANGED         (1<<17)
/** Specific State in modem configuration : DCD value changed */
#define HAL_UART_STATUS_DCD_CHANGED         (1<<18)
/** Specific State in modem configuration : RI value changed */
#define HAL_UART_STATUS_RI_CHANGED          (1<<19)
/** Specific State in modem configuration : RTS value changed */
#define HAL_UART_STATUS_RTS_CHANGED         (1<<20)
/** Specific State in modem configuration : DTR value changed */
#define HAL_UART_STATUS_DTR_CHANGED         (1<<21)


/** Set the modem control line CTS */
#define HAL_UART_IOCTL_SET_CTS          1
/** Set the modem control line DSR */
#define HAL_UART_IOCTL_SET_DSR          2
/** Set the modem control line DCD */
#define HAL_UART_IOCTL_SET_DCD          3
/** Set the modem control line RI */
#define HAL_UART_IOCTL_SET_RI           4
/** Set the modem control line RTS */
#define HAL_UART_IOCTL_SET_RTS          5
/** Set the modem control line DTR */
#define HAL_UART_IOCTL_SET_DTR          6

/** Clear the modem control line CTS */
#define HAL_UART_IOCTL_CLEAR_CTS        7
/** Clear the modem control line DSR */
#define HAL_UART_IOCTL_CLEAR_DSR        8
/** Clear the modem control line DCD */
#define HAL_UART_IOCTL_CLEAR_DCD        9
/** Clear the modem control line RI */
#define HAL_UART_IOCTL_CLEAR_RI         10 
/** Clear the modem control line RTS */
#define HAL_UART_IOCTL_CLEAR_RTS        11
/** Clear the modem control line DTR */
#define HAL_UART_IOCTL_CLEAR_DTR        12

/** Get the modem control line CTS state */
#define HAL_UART_IOCTL_GET_CTS          13
/** Get the modem control line DSR state */
#define HAL_UART_IOCTL_GET_DSR          14
/** Get the modem control line DCD state */
#define HAL_UART_IOCTL_GET_DCD          15
/** Get the modem control line RI state */
#define HAL_UART_IOCTL_GET_RI           16
/** Get the modem control line RTS state */
#define HAL_UART_IOCTL_GET_RTS          17
/** Get the modem control line DTR state */
#define HAL_UART_IOCTL_GET_DTR          18

/** Set the baudrate parameter  */
#define HAL_UART_IOCTL_SET_BAUDRATE     19


/** This event indicator is raised when a frame error interrupt occured */
#define HAL_UART_EVENT_FRAME_ERROR          0
/** This event indicator is raised when a false start interrupt occured */
#define HAL_UART_EVENT_START_ERROR          1
/** This event indicator is raised when a parity error interrupt occured */
#define HAL_UART_EVENT_PARITY_ERROR         2
/** This event indicator is raised when the TX FIFO empty interrupt occured */
#define HAL_UART_EVENT_TX_FIFO_EMPTY        3
/** This event indicator is raised when the RX FIFO full interrupt occured */
#define HAL_UART_EVENT_RX_FIFO_FULL         4
/** This event indicator is raised when the RX FIFO half interrupt occured */
#define HAL_UART_EVENT_RX_FIFO_HALF         5  
/** This event indicator is raised when the RX FIFO one interrupt occured */
#define HAL_UART_EVENT_RX_FIFO_ONE          6

/** This event is raised when the CTS modem line changed */
#define HAL_UART_EVENT_CTS_CHANGED          7
/** This event is raised when the DSR modem line changedmodem line changed */
#define HAL_UART_EVENT_DSR_CHANGED          8
/** This event is raised when the DCD modem line changed */
#define HAL_UART_EVENT_DCD_CHANGED          9
/** This event is raised when the RI modem line changed */
#define HAL_UART_EVENT_RI_CHANGED           10
/** This event is raised when the RTS modem line changed */
#define HAL_UART_EVENT_RTS_CHANGED          11
/** This event is raised when the DTR modem line changed */
#define HAL_UART_EVENT_DTR_CHANGED          12


/*----------------------------------------------------------------------------
 * Device Enumeration
 */

/** The device enumeration defines the UART identifiers 
 */
enum hal_uart_devices 
{
    /** Identifier of the UART with IrDa capabilities */
    hal_uart_dev0 = 0, 
    /** Identifier of the UART with Modem capabilities */
    hal_uart_dev1,
    /** Identifier of the third UART */
    hal_uart_dev2,
    /** Identifier of the fourth UART */
    hal_uart_dev3,
    /** This constant is used to fix the number of available UART devices */
    hal_uart_devices_count
};

#define HAL_UART_FIFO_SIZE  8


/*----------------------------------------------------------------------------
 * Configuration Structure
 */
     
/** The configuration structure is used to set up an UART Interface */
typedef struct HAL_UART_CONFIG
{
    /** Specifies the baud rate of serial link, it's value can be 
     * one of the following standard value or anyother value 
     * @li #HAL_UART_BAUDRATE_1200
     * @li #HAL_UART_BAUDRATE_2400
     * @li #HAL_UART_BAUDRATE_4800
     * @li #HAL_UART_BAUDRATE_9600
     * @li #HAL_UART_BAUDRATE_19200
     * @li #HAL_UART_BAUDRATE_38400
     * @li #HAL_UART_BAUDRATE_57600
     * @li #HAL_UART_BAUDRATE_115200
     */
    unsigned int baudrate;
    
    /** Specifies the size of data. It's one of the following value :
     * @li #HAL_UART_DATA_BITS_5
     * @li #HAL_UART_DATA_BITS_6
     * @li #HAL_UART_DATA_BITS_7
     * @li #HAL_UART_DATA_BITS_8 
     */
    unsigned int bytesize;
       
    /** Specifies the parity. It's one of the following value:
     * @li #HAL_UART_PARITY_NONE
     * @li #HAL_UART_PARITY_EVEN
     * @li #HAL_UART_PARITY_ODD
     */
    unsigned int parity;
     
    /** Specifies the number of stop bits. It's one of the following value : 
     * @li #HAL_UART_STOP_BIT_1
     * @li #HAL_UART_STOP_BIT_2
     * 
     * \note If the byte size is equals to 5 bits, so the #HAL_UART_STOP_BIT_2
     * value correspond to 1,5 stop bits  
     */
    unsigned int stopbits;
       
    /** Specifies the mode of communication or more exactly the protocol
     * of communication. It's one of the following value :
     * @li #HAL_UART_MODE_NONE
     * @li #HAL_UART_MODE_IRDA
     * @li #HAL_UART_MODE_MODEM_DTE
     * @li #HAL_UART_MODE_MODEM_DCE
     * 
     * \note 
     * The mode HAL_UART_MODE_IRDA is only available on the UART Interface 
     * identified by #hal_uart_dev0
     * \note 
     * The modes HAL_UART_MODE_MODEM_DTE and HAL_UART_MODE_MODEM_DCE are only 
     * available on UART Interface identified by #hal_uart_dev1. 
     */
    unsigned int mode;
    
    /** Specifies the options of special modes. 
     * For IRDA mode, orred combination of the following values: 
     * @li #HAL_UART_FLAG_IRDA_ACTIVE_LOW 
     * @li #HAL_UART_FLAG_IRDA_ACTIVE_HIGH 
     * @li #HAL_UART_FLAG_IRDA_RATE_1_4 
     * @li #HAL_UART_FLAG_IRDA_RATE_3_16 
     * 
     * For MODEM mode, orred combination of the following values: 
     * @li #HAL_UART_FLAG_IN_CTS_FLOW
     * @li #HAL_UART_FLAG_IN_RTS_FLOW
     * 
     * The default value is #HAL_UART_MODE_NONE. 
     * Otherwise, in normal mode flags has not effect.
     */
    unsigned int flags;
    
} HAL_UART_CONFIG;


/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function initializes and configures a particular UART Interface. The 
 * interface is identified by its ID and its configuration is contained into a 
 * dedicated structure. 
 *
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 *                            
 * @param[in] params        Points on a UART configuration structure allocated 
 *                          and filled by the caller. 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_init( int devnum, HAL_UART_CONFIG *params ); 

/**
 * The function terminates the use of a particular UART interface. 
 *
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_shutdown( int devnum );

/**
 * The function configures a particular UART Interface. The interface 
 * is identified by its ID and its configuration is contained into a structure. 
 *
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 *                            
 * @param[in] params        Points on a UART configuration structure allocated 
 *                          and filled by the caller. 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_uart_init() first. 
 * @retval -ERR_AGAIN       Try again later 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_set_config( int devnum, HAL_UART_CONFIG *params );

                    
/**
 * The function is used to retrieve the state of an UART Interface.
 * 
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 * 
 * @param[out] status       A pointer allocated by the caller and filled by the 
 *                          function with the current status of UART Interface.  
 *                          \n It is one or a combination of the following values: 
 *                          \li #HAL_UART_STATUS_INTR_FRAME_ERROR
 *                          \li #HAL_UART_STATUS_INTR_START_ERROR
 *                          \li #HAL_UART_STATUS_INTR_PARITY_ERROR
 *                          \li #HAL_UART_STATUS_INTR_MODEM_LINE_CHANGED
 *                          \li #HAL_UART_STATUS_INTR_TX_FIFO
 *                          \li #HAL_UART_STATUS_INTR_RX_FIFO_FULL
 *                          \li #HAL_UART_STATUS_INTR_RX_FIFO_HALF
 *                          \li #HAL_UART_STATUS_INTR_RX_FIFO_ONE
 *                          \li #HAL_UART_STATUS_RX_FIFO_EMPTY
 *                          \li #HAL_UART_STATUS_RX_FIFO_FULL
 *                          \li #HAL_UART_STATUS_TX_FIFO_EMPTY
 *                          \li #HAL_UART_STATUS_TX_FIFO_FULL
 *                          \li #HAL_UART_STATUS_RX_BUSY
 *                          \li #HAL_UART_STATUS_TX_BUSY
 *                          \n If the device has Modem capability, the result 
 *                          may also be combined with the following values: 
 *                          \li #HAL_UART_STATUS_CTS_CHANGED
 *                          \li #HAL_UART_STATUS_DSR_CHANGED
 *                          \li #HAL_UART_STATUS_DCD_CHANGED
 *                          \li #HAL_UART_STATUS_RI_CHANGED
 *                          \li #HAL_UART_STATUS_RTS_CHANGED
 *                          \li #HAL_UART_STATUS_DTR_CHANGED
 *
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_uart_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */   
int hal_uart_get_status( int devnum, int *status );

                     
/** 
 * The function sends a character to the output buffer of an UART Interface. 
 * 
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 *                            
 * @param[in] data          The data to be send.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_uart_init() first. 
 * @retval -ERR_AGAIN       Try again later. Transmit FIFO is full. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_write( int devnum, unsigned char data );

/** 
 * The function reads a character into the input buffer of an UART Interface. 
 * 
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 * 
 * @param[out] data         A pointer allocated by the caller and filled by the 
 *                          function with the read data.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_uart_init() first. 
 * @retval -ERR_AGAIN       Try again later. Receive FIFO is empty. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_read( int devnum, unsigned char *data );

/**
 * The function registers an interrupt handler for a type of event.
 * 
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_UART_EVENT_FRAME_ERROR          
 *                          \li #HAL_UART_EVENT_START_ERROR          
 *                          \li #HAL_UART_EVENT_PARITY_ERROR         
 *                          \li #HAL_UART_EVENT_TX_FIFO_EMPTY
 *                          \li #HAL_UART_EVENT_RX_FIFO_FULL        
 *                          \li #HAL_UART_EVENT_RX_FIFO_HALF         
 *                          \li #HAL_UART_EVENT_RX_FIFO_ONE         
 *                          \li #HAL_UART_EVENT_CTS_CHANGED         
 *                          \li #HAL_UART_EVENT_DSR_CHANGED         
 *                          \li #HAL_UART_EVENT_DCD_CHANGED          
 *                          \li #HAL_UART_EVENT_RI_CHANGED           
 *                          \li #HAL_UART_EVENT_RTS_CHANGED          
 *                          \li #HAL_UART_EVENT_DTR_CHANGED
 * 
 * @param[in] handler       Pointer on the interrupt handler function.
 *                          Its declaration should support the parameters:
 *                          \li \e devnum Device identifier
 *                          \li \e event Occured event
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_uart_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_attach( int devnum, int event, void (*handler)(int devnum, int event) );

/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 * 
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 * 
 * @param[in] event         Event type. Possible values are the following: 
 *                          \li #HAL_UART_EVENT_FRAME_ERROR          
 *                          \li #HAL_UART_EVENT_START_ERROR          
 *                          \li #HAL_UART_EVENT_PARITY_ERROR         
 *                          \li #HAL_UART_EVENT_TX_FIFO_EMPTY
 *                          \li #HAL_UART_EVENT_RX_FIFO_FULL        
 *                          \li #HAL_UART_EVENT_RX_FIFO_HALF         
 *                          \li #HAL_UART_EVENT_RX_FIFO_ONE         
 *                          \li #HAL_UART_EVENT_CTS_CHANGED         
 *                          \li #HAL_UART_EVENT_DSR_CHANGED         
 *                          \li #HAL_UART_EVENT_DCD_CHANGED          
 *                          \li #HAL_UART_EVENT_RI_CHANGED           
 *                          \li #HAL_UART_EVENT_RTS_CHANGED          
 *                          \li #HAL_UART_EVENT_DTR_CHANGED
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NXIO        Device not configured. Use hal_uart_init() first. 
 * @retval -ERR_ALREADY     Operation already in progress
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_detach( int devnum, int event );

/**
 * The function allows to assert and deassert the modem control lines according 
 * to control parameter.
 *
 * @param[in] devnum        The UART Interface identifier (#hal_uart_devices 
 *                          gives a list of all UART device identifiers) 
 * 
 * @param[in] cmd           The control to be performed. It can be either
 *                          \li one or combination of set control,
 *                          \li one or a combination of clear control,
 *                          \n or
 *                          \li one or a combination of get control.
 * 
 *                          But the control cannot be a combination of set, 
 *                          clear and/or get control.
 *                          \n Set Control List :
 *                          \li #HAL_UART_IOCTL_SET_CTS
 *                          \li #HAL_UART_IOCTL_SET_DSR
 *                          \li #HAL_UART_IOCTL_SET_DCD
 *                          \li #HAL_UART_IOCTL_SET_RI
 *                          \li #HAL_UART_IOCTL_SET_RTS
 *                          \li #HAL_UART_IOCTL_SET_DTR
 * 
 *                          Clear Control List :
 *                          \li #HAL_UART_IOCTL_CLEAR_CTS
 *                          \li #HAL_UART_IOCTL_CLEAR_DSR
 *                          \li #HAL_UART_IOCTL_CLEAR_DCD
 *                          \li #HAL_UART_IOCTL_CLEAR_RI
 *                          \li #HAL_UART_IOCTL_CLEAR_RTS
 *                          \li #HAL_UART_IOCTL_CLEAR_DTR
 * 
 *                          Get Control List :
 *                          \li #HAL_UART_IOCTL_GET_CTS
 *                          \li #HAL_UART_IOCTL_GET_DSR
 *                          \li #HAL_UART_IOCTL_GET_DCD
 *                          \li #HAL_UART_IOCTL_GET_RI
 *                          \li #HAL_UART_IOCTL_GET_RTS
 *                          \li #HAL_UART_IOCTL_GET_DTR
 * 
 * @param[out] param        Pointer allocated by the caller and filled by the 
 *                          control function. This parameter is only used to 
 *                          get modem lines states. It is not checked in case 
 *                          of set or clear function.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_uart_devices). 
 * @retval -ERR_NOTTY       Inappropriate ioctl for device 
 * @retval -ERR_NXIO        Device not configured. Use hal_uart_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_uart_ioctl( int devnum, int cmd, int *param  );

#else

#include <hal/usip/hal_sys.h>

typedef void (*hal_uart_handler_t)(int devnum, int event);

__hal_defunc2(hal_uart_init, int, devnum, HAL_UART_CONFIG *, params);
__hal_defunc1(hal_uart_shutdown, int, devnum);
__hal_defunc2(hal_uart_set_config, int, devnum, HAL_UART_CONFIG *, params);
__hal_defunc2(hal_uart_get_status, int, devnum, int *, status);
__hal_defunc2(hal_uart_write, int, devnum, unsigned char, data);
__hal_defunc2(hal_uart_read, int, devnum, unsigned char *, data);
__hal_defunc3(hal_uart_attach, int, devnum, int, event, hal_uart_handler_t, handler);
__hal_defunc2(hal_uart_detach, int, devnum, int, event);
__hal_defunc3(hal_uart_ioctl, int, devnum, int, cmd, int *, param);

__hal_deisr(hal_uart_isr0, void);  
__hal_deisr(hal_uart_isr1, void);
__hal_deisr(hal_uart_isr2, void);
__hal_deisr(hal_uart_isr3, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif


/**  @} */

#endif  /* HAL_USIP_UART_H */
	

