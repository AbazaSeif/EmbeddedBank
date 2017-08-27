/*============================================================================
 *
 *      hal_printer.h
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
 * Description:  This file contains the Thermal Printer Interface generic 
 *               functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_PRINTER_H
#define HAL_USIP_PRINTER_H

/**
 *  
 * @defgroup HAL_PRN HAL Thermal Printer Interface 
 * This chapter contains descriptions of the configuration structure and 
 * functions available to access the Thermal Printer Interface. 
 * 
 * @section hal_printer Overview 
 * 
 * USIP® Professional provides an interface to drive any thermal print head in 
 * serial mode. This interface includes the stepper motor control. 
 * 
 * The ADC module provided by USIP® Professional may be used to monitor the 
 * printer head temperature, the power supply, aso. 
 * 
 * @warning The Thermal Printer interface resources are partially shared with 
 * the @link HAL_PS2 PS/2 port @endlink. When the PS/2 ports is in use, the 
 * thermal printer interface cannot use more than 6 IO for the stepper motor. 
 * Otherwise it is is busy and its initialization fails. 
 * 
 * @warning The Thermal Printer interface resources are shared with the @link 
 * HAL_SPP Parallel @endlink interface. When the Parallel port is in use, the 
 * Thermal Printer interface is busy and its initialization fail. 
 * 
 * @section head Thermal Print Head 
 * 
 * This part of the module drives all signals needed to control a thermal print 
 * head. It supports thermal print heads up to 2048 dots/line. 
 * 
 * The thermal print head control consists of a shift register. The shift 
 * register width should be filled with the contents a line to be printed. 
 * Successives 32-bits writes in the shift register will complete the line to 
 * be printed. 
 * 
 * \b Features
 * 
 * \li Programmable shift register length up to 2048 dots per line 
 * \li Programmable clock frequency 
 * \li Programmable hold and setup times 
 * \li Interrupt generation when a of 32-bits transfer in the shift register 
 * has completed 
 *  
 * 
 * @section motor Stepper Motor Controller 
 * 
 * This part of the module drives all signals needed to control a stepper 
 * motor. 
 * 
 * A pseudo FIFO is implemented to suit to a large range of motors (bi-polar …) 
 * and applications (different phase mode functionalities, different numbers of 
 * steps per line…). The stepper motor control consists of filling this pseudo 
 * FIFO with the command sequences to change the motor position. 
 * 
 * \b Features
 * 
 * \li Programmable speed 
 * \li Up to 8 commands per sequence 
 * \li Interrupt generation at the end of the command sequence 
 * 
 * 
 * @addtogroup HAL_PRN
 * 
 * @{
 */
 

/*----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/

/** This status indicator is raised when data are sent */
#define HAL_PRINTER_STATUS_TRANSMIT_DONE (1<<2)
/** This status indicator is raised when steps are done */
#define HAL_PRINTER_STATUS_STEP_DONE     (1<<5)

/** This event indicator is raised when data are sent */
#define HAL_PRINTER_EVENT_TRANSMIT_DONE  0
/** This event indicator is raised when steps are done */
#define HAL_PRINTER_EVENT_STEP_DONE      1

/** Internal ring buffer depth */
#define HAL_PRINTER_INTERNAL_BUFFER_SIZE 32

/** Command code to set the latch setup time. */
#define HAL_PRINTER_IOCTL_SET_LATCHSETUP        0
/** Command code to set the data hold time. */
#define HAL_PRINTER_IOCTL_SET_DATAHOLD          1
/** Command code to set the data setup time. */
#define HAL_PRINTER_IOCTL_SET_DATASETUP         2
/** Command code to set the frequency. */
#define HAL_PRINTER_IOCTL_SET_FREQUENCY         3
/** Command code to set the number of dots per line. */
#define HAL_PRINTER_IOCTL_SET_DOTS              4
/** Command code to set the latch pulse width. */
#define HAL_PRINTER_IOCTL_SET_LATCHPULSE        5
/** Command code to set the strobe setup time. */
#define HAL_PRINTER_IOCTL_SET_STROBESETUP       6 
/** Command code to set the velocity. */
#define HAL_PRINTER_IOCTL_SET_VELOCITY          7
/** Command code to get the latch setup time. */
#define HAL_PRINTER_IOCTL_GET_LATCHSETUP        8
/** Command code to get the data hold time. */
#define HAL_PRINTER_IOCTL_GET_DATAHOLD          9
/** Command code to get the data setup time. */
#define HAL_PRINTER_IOCTL_GET_DATASETUP         10
/** Command code to get the frequency. */
#define HAL_PRINTER_IOCTL_GET_FREQUENCY         11 
/** Command code to get the number of dots per line. */ 
#define HAL_PRINTER_IOCTL_GET_DOTS              12
/** Command code to get the latch pulse width. */
#define HAL_PRINTER_IOCTL_GET_LATCHPULSE        13
/** Command code to get the strobe setup time. */
#define HAL_PRINTER_IOCTL_GET_STROBESETUP       14
/** Command code to set the velocity. */
#define HAL_PRINTER_IOCTL_GET_VELOCITY          15
/** Command code to clear the step done event. */
#define HAL_PRINTER_IOCTL_CLEAR_STEP_DONE       16
/** Command code to clear the transmit done event. */
#define HAL_PRINTER_IOCTL_CLEAR_TRANSMIT_DONE   17
/** Command code to start a "1 dot-line" sequence. */
#define HAL_PRINTER_IOCTL_START_STEPS           18
/** Command code to set the write pointer. */
#define HAL_PRINTER_IOCTL_SET_WRITE_POINTER     19
/** Command code to set the number of IO used for stepper. */
#define HAL_PRINTER_IOCTL_SET_STEP_DATA_WIDTH   20

/** This indicator may be used to mark the next position */
#define HAL_PRINTER_POSITION_NEXT (-1)

/*----------------------------------------------------------------------------
 * Configuration Structure
 */

/** The configuration structure used to set up the Thermal Printer Interface */
typedef struct HAL_PRINTER_CONFIG
{
   /** Specify the Number of dots per line (i.e the shift register length). 
    *  This number is up to 2048 dots. */ 
   unsigned int dots;   
   
   /** Specify the Clock frequency in Hz (max. system clock divided by 2) */
   unsigned int frequency;
     
   /** Specify the Data set up time in ns */
   unsigned int datasetup; 
   
   /** Specify the Data hold time in ns */
   unsigned int datahold; 
   
   /** Specify the Latch set up time in ns */
   unsigned int latchsetup; 
    
   /** Specify the Latch pulse width time in ns */
   unsigned int latchpulse;
    
   /** Specify the Strobe set up time in ns */
   unsigned int strobesetup;
      
   /** Specify the Step duration in ns */   
   unsigned int velocity;   
     
   /** Specify the Number of required steps to perform motion */
   unsigned int steps;
   
} HAL_PRINTER_CONFIG;


/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures the Thermal Printer Interface. 
 * 
 * @warning The thermal printer shares its clock and hardware reset with the 
 * GPIOs, parallel and PS/2 interfaces. It is not actually reset nor activated 
 * if any of these interfaces is already in use. 
 * 
 * @param[in] params        Pointer on a Thermal Printer configuration 
 *                          structure allocated and filled by the caller. 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_BUSY        Resource busy. Shared resources are already in use. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_init( HAL_PRINTER_CONFIG *params );

/**
 * The function disables the Thermal Printer Interface. 
 *  
 * @warning The thermal printer shares its clock and hardware reset with the 
 * GPIO, parallel and PS/2 interfaces. It is not actually disabled if any of 
 * these interfaces is still in use. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_shutdown( void );

/** 
 * The function configures the Thermal Printer Interface. 
 * 
 * @param[in] params        Pointer on a Thermal Printer configuration 
 *                          structure allocated and filled by the caller. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_set_config( HAL_PRINTER_CONFIG *params );

/** 
 * The function provides the current state of the Thermal Printer Interface.
 * 
 * @param[out] status       Pointer on a variable allocated by the caller and 
 *                          filled by the function with the current state of 
 *                          the Thermal Printer Interface. Upon success, it 
 *                          receives an orred combination of the following 
 *                          state indicators: 
 *                          \li #HAL_PRINTER_STATUS_TRANSMIT_DONE
 *                          \li #HAL_PRINTER_STATUS_STEP_DONE
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_get_status( unsigned int *status );

/**
 * The function performs Thermal Printer Interface specific control functions.
 * 
 * @param[in] cmd           Requested control function. 
 *                          \li #HAL_PRINTER_IOCTL_SET_LATCHSETUP
 *                          \li #HAL_PRINTER_IOCTL_SET_DATAHOLD
 *                          \li #HAL_PRINTER_IOCTL_SET_DATASETUP
 *                          \li #HAL_PRINTER_IOCTL_SET_FREQUENCY
 *                          \li #HAL_PRINTER_IOCTL_SET_DOTS
 *                          \li #HAL_PRINTER_IOCTL_SET_LATCHPULSE
 *                          \li #HAL_PRINTER_IOCTL_SET_STROBESETUP
 *                          \li #HAL_PRINTER_IOCTL_SET_VELOCITY
 *                          \li #HAL_PRINTER_IOCTL_GET_LATCHSETUP
 *                          \li #HAL_PRINTER_IOCTL_GET_DATAHOLD
 *                          \li #HAL_PRINTER_IOCTL_GET_DATASETUP
 *                          \li #HAL_PRINTER_IOCTL_GET_FREQUENCY
 *                          \li #HAL_PRINTER_IOCTL_GET_DOTS
 *                          \li #HAL_PRINTER_IOCTL_GET_LATCHPULSE
 *                          \li #HAL_PRINTER_IOCTL_GET_STROBESETUP
 *                          \li #HAL_PRINTER_IOCTL_GET_VELOCITY
 *                          \li #HAL_PRINTER_IOCTL_CLEAR_STEP_DONE
 *                          \li #HAL_PRINTER_IOCTL_CLEAR_TRANSMIT_DONE
 *                          \li #HAL_PRINTER_IOCTL_START_STEPS
 *                          \li #HAL_PRINTER_IOCTL_SET_WRITE_POINTER
 * 
 * @param[in,out] data      Pointer on a variable filled by the caller with 
 *                          data requested for the control or filled by the 
 *                          function with data retrieved from the control. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_BUSY        Resource busy. Shared resources are already in use. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_ioctl( int cmd, void *data );

/** 
 * The function writes a data to the Thermal Printer Head. 
 * 
 * @param[in] data          The data to be written. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_head_write( unsigned int data );

/** 
 * The function stores data to be written to the Thermal Printer Motor, 
 * into the internal ring buffer. Data are strored sequentialy by several calls
 * to this function. All data are finaly sent to the Thermal Printer Motor by 
 * calling hal_printer_motor_step(). 
 * 
 * @param[in] data          Data to be written. 
 * 
 * @param[in] position      Data position in the internal ring buffer. 
 *                          If the value is #HAL_PRINTER_POSITION_NEXT, the 
 *                          STEP data value will be written at the next 
 *                          position. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 * @note The buffer depth is of 8 elements. The write pointer on the internal 
 * ring buffer is reset after a step sequence. 
 * 
 */
int hal_printer_motor_write( unsigned char data, int position );

/** 
 * The function starts a sequence of Thermal Printer Motor steps. 
 * 
 * The number of steps was fixed in the configuration structure. The sequence 
 * was previously defined by sucessive calls to #hal_printer_motor_write(). 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 * @note After calling the function, the write pointer of the internal ring 
 * buffer is reset. 
 *   
 */ 
int hal_printer_motor_step( void );

/** 
 * The function gets the position of the Thermal Printer Motor. 
 *
 * @param[out] position     Position where the step sequence has stopped. 
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *  
 */ 
int hal_printer_motor_get_position( int *position );

/** 
 * The function sets the position of the Thermal Printer Motor.
 *
 * @param[in] position      Position where the next step sequence will be 
 *                          started.
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *  
 */ 
int hal_printer_motor_set_position( int position );

/**
 * The function registers an interrupt handler for a type of event. 
 * 
 * @param[in] event         Event type. Available values are the following: 
 *                          \li #HAL_PRINTER_EVENT_TRANSMIT_DONE 
 *                          \li #HAL_PRINTER_EVENT_STEP_DONE 
 * 
 * @param[in] handler       Pointer on the interrupt handler function. 
 *                          Its declaration should support the parameter:
 *                          \li \e event Occured event 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_attach( int event, void (*handler)(int) );

/**
 * The function unregisters an interrupt handler that is used to process a 
 * particular event. 
 * 
 * @param[in] event         Event type. Available values are the following: 
 *                          \li #HAL_PRINTER_EVENT_TRANSMIT_DONE 
 *                          \li #HAL_PRINTER_EVENT_STEP_DONE 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_printer_init() 
 *                          first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_ALREADY     Operation already in progress 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_printer_detach( int event );

#else 

#include <hal/usip/hal_sys.h>

typedef void (*hal_printer_handler_t)(int);

__hal_defunc1(hal_printer_init, HAL_PRINTER_CONFIG *, params);
__hal_defunc0(hal_printer_shutdown, void);
__hal_defunc1(hal_printer_set_config, HAL_PRINTER_CONFIG *, params);
__hal_defunc1(hal_printer_get_status, unsigned int *, status);
__hal_defunc2(hal_printer_ioctl, int, cmd, void *, data);
__hal_defunc1(hal_printer_head_write, unsigned int, data);
__hal_defunc2(hal_printer_motor_write, unsigned char, data, int, position);
__hal_defunc0(hal_printer_motor_step, void);
__hal_defunc1(hal_printer_motor_get_position, int *, position);
__hal_defunc1(hal_printer_motor_set_position, int, position);
__hal_defunc2(hal_printer_attach, int, event, hal_printer_handler_t, handler);
__hal_defunc1(hal_printer_detach, int, event);

__hal_deisr(hal_printer_isr, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/**  @} */

#endif  /* HAL_USIP_PRINTER_H */

