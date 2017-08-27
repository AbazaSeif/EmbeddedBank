/*============================================================================
 *
 *      libemv.h
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
 * Contributors:  Yann Gaude
 * Date:          
 * Purpose:       
 * Description:   EMV Level 1 library
 * 
 *==========================================================================*/
#ifndef _LIB_EMV_H_
#define _LIB_EMV_H_


/*--------------------------------------------------------------------------*/

 
/**
 * @mainpage EMV Level 1 library Reference Manual
 * 
 * @section Overview Overview
 * This document contains descriptions of the configuration structure, 
 * and functions available to access the Smart Card Interface according to 
 * the EMV 2000 specification (Integrated Circuit Card Specification 
 * For Payment Systems - Version 4.0 December, 2000).
 * 
 * @section Detail Detailed description 
 * All functions and data structures have a complete description in the linked
 * @link LIBEMV1 section @endlink  
 * 
 * @section License License 
 * 
 * @htmlinclude license.html 
 * 
 * 
 * @section Reference Reference 
 * 
 * @htmlinclude reference.html 
 */
 
 /**
 * @defgroup LIBEMV1 EMV Level 1 library
 * @{
 */

#define	EMV_SCS_SCIB_0				0x00
#define	EMV_SCS_SCIB_1				0x01
#define	EMV_SCS_SCIB_2				0x02
#define	EMV_SCS_NO_SCIB				0xff

/** This event indicator is raised when all the response of Answer To Reset 
 * has been received */
#define EMV_EVENT_ATR_COMPLETED              0

/** This event indicator is raised when the Response APDU is received */
#define EMV_EVENT_DATA_RECEIVED             1

/** This event indicator is raised when all data has been sent */
#define EMV_EVENT_DATA_SENT                 2

/** This event indicator is raised when an error has occured */
#define EMV_EVENT_ERROR                     3


#define EMV_EVENT_COUNT             (EMV_EVENT_ERROR + 1)

#define EMV_MODE_MANAGE_PPS         0x01
#define EMV_MODE_T1_MANAGE_ABORT    0x10
#define EMV_MODE_T1_MANAGE_TIMEOUT  0x20
#define EMV_MODE_T1_MANAGE_RESYNC   0x40
#define EMV_MODE_T1_IFSD			0x80

 
/*----------------------------------------------------------------------------
 * Data and configuration structures
 *---------------------------------------------------------------------------*/

/** 
 * This structure is used to call-back the hardware dependent functions that 
 * drive the analog part of the smart card interface. 
 * The user must implement the init() and ioctl() hook functions.
 *   
 */



/** The configuration structure used to set up the Smart Card Interface */
typedef struct 
{

    
    /** Power supply. Possible values are :
     *      -#HAL_SCS_POWER_1_8V
     *      -#HAL_SCS_POWER_3V                   
     *      -#HAL_SCS_POWER_5V
     */
    unsigned int power;
    
    /** Smart card protocol. Possible values are :
     *      -#HAL_SCS_PROTOCOL_T0
     *      -#HAL_SCS_PROTOCOL_T1                   
     *      -#HAL_SCS_PROTOCOL_SYNC
     */
    unsigned int protocol;
        
    /** Smart Card Clock Frequency. Possible values are #HAL_SCS_CLOCK_EXTERNAL
     * or a combinaison between HAL_SCS_CLOCK_INTERNAL and 
     *  -#HAL_SCS_CLOCK_48MHz     
     *  -#HAL_SCS_CLOCK_24MHz     
     *  -#HAL_SCS_CLOCK_16MHz     
     *  -#HAL_SCS_CLOCK_12MHz     
     *  -#HAL_SCS_CLOCK_9_6MHz    
     *  -#HAL_SCS_CLOCK_8MHz      
     *  -#HAL_SCS_CLOCK_6_86MHz   
     *  -#HAL_SCS_CLOCK_6MHz      
     *  -#HAL_SCS_CLOCK_5_33MHz   
     *  -#HAL_SCS_CLOCK_4_8MHz    
     *  -#HAL_SCS_CLOCK_4_33MHz    
     *  -#HAL_SCS_CLOCK_4MHz      
     *  -#HAL_SCS_CLOCK_3_69MHz   
     *  -#HAL_SCS_CLOCK_3_43MHz   
     *  -#HAL_SCS_CLOCK_3_2MHz    
     *  -#HAL_SCS_CLOCK_3MHz
     */
    unsigned int clock;
    
    /** Valid pointer to the #HAL_SCS_DRIVER_IO structure (driver functions
     * which control the analog part of the interface) */
    HAL_SCS_DRIVER_IO *devio;

    /** SCIB number to associate with the device number : 
	* -#EMV_SCS_SCIB_0
	* -#EMV_SCS_SCIB_1
	* -#EMV_SCS_SCIB_2
	* -#EMV_SCS_NO_SCIB
	*/
	unsigned char	ucSCIB;

    /** Possible values are an OR combinaison :
     *      -#EMV_MODE_MANAGE_PPS
     *      -#EMV_MODE_MANAGE_RESYNC                   
     */
    unsigned int mode;
	/** Timer number to be used by EMV L1 library for timing issues. To be chosen from timer hal_timer_dev0 to hal_timer_dev3 */
    unsigned int timernum;
    
} EMV_SLOT_CONFIG;

/** The structure used to retrieve or to set up the communication parameters */
typedef struct 
{         

    /** Speed communication (parameter TA1 of ISO 7816-3) */
    unsigned char FIDI;    

    /** Extra Guard Time (parameter TC1 or N of ISO 7816-3) */
    unsigned char EGT;  

    /** 
     * If protocol T=0 is selected, the parameter indicates the Waiting 
     * Integer (parameter TC2 of ISO 7816-3 - the default value is 10) 
     * If the protocol T=1 is selected, the parameter indicates the 
     * Block and Character Waiting Time Integer (parameter TB3 of ISO 7816-3) 
     */
    unsigned char WI;   

     /** If the protocol T=1 is selected, the parameter indicates the 
      * Waiting Time Extention (the default value is 1). */
    unsigned char WTX;    
     
    /** If the protocol T=1 is selected, the parameter indicates the computing 
     * mode for EDC : HAL_SCS_EDC_LRC or HAL_SCS_EDC_CRC (The default value 
     * is an LRC) */ 
    unsigned char EDC;           
       
    /** The parameter indicates the selected protocol : 
     * EMV_PROTOCOL_T0 or EMV_PROTOCOL_T1 */
    unsigned char protocol;
   
    /** The power supply value */              
    unsigned char power;                   

    /** Convention used to transfer byte : 
     * EMV_CONV_DIRECT or EMV_CONV_INVERSE */
    unsigned char conv;  
    
    /** If the protocol T=1 is selected, the parameter indicates the Information
     * Field Size for the Card (parameter TA3 of ISO 7816-3). */
    unsigned char IFSC;
    /** Character Waiting Time for T=1 protocol */
    unsigned int cwt;
    /** Block Waiting Time for T=1 protocol, Work Waiting Time for T=0 protocol, Reception window for Power Up sequence */
    unsigned int bwt;
    
} emv_slot_info_t;



/*----------------------------------------------------------------------------
 * Function declarations
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


#ifdef CONFIG_LIBROM_NOT_INLINED

#define emv_get_status  hal_scs_get_status
#define emv_power_down  hal_scs_power_down 

/**
 * The function initializes the EMV level 1 library and must be called before
 * any other library function.
 * 
 * @param[in] devnum   The identifier of the Smart Card Interface.
 * 
 * @param[in] params   Pointer to an initialized configuration structure.
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
int emv_init( int devnum, EMV_SLOT_CONFIG *params );

/**
 * The function shutdowns the EMV level 1 library.
 * 
 * @param[in] devnum   The identifier of the Smart Card Interface.
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
int emv_shutdown( int devnum );
 
/** 
 * The function provides the current state of a Smart Card Interface. 
 * It returns information indicating :
 *  \li The power supply value
 *  \li Card presence
 *  \li The card power status 
 * 
 * @param[in]  devnum   The identifier of the Smart Card Interface.
 * 
 * @param[out] status   Receives the current state of the Smart Card Interface. 
 *                      Upon success, it receives a combinaison of the following 
 *                      state indicators: 
 *                          \li #HAL_SCS_STATUS_POWER_5V 
 *                          \li #HAL_SCS_STATUS_POWER_3V             
 *                          \li #HAL_SCS_STATUS_CARD_NOT_POWERED     
 *                          \li #HAL_SCS_STATUS_CARD_POWERED         
 *                          \li #HAL_SCS_STATUS_CARD_NOT_INSERTED    
 *                          \li #HAL_SCS_STATUS_CARD_INSERTED        
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */  
int emv_get_status( int devnum, int *status );

/** 
 * The function configures a Smart Card Interface and selects the working 
 * clock for the interface.
 * 
 * @param[in] devnum    The identifier of the Smart Card Interface.
 * 
 * @param[in] params    Pointer to an initialized configuration structure.
 * 
 * @retval -ERR_NO      No error 
 * @retval -ERR_NODEV   No such device. Try another identifier 
 *                      See #hal_scs_devices). 
 * @retval -ERR_NXIO    Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL   Invalid parameter 
 * @retval Other        See \link Error_Codes Error Codes \endlink
 * 
 */
int emv_set_config( int devnum, EMV_SLOT_CONFIG *params );

/**
 * The function powers up and resets a card. During the card 
 * Answer To Reset (ATR), the function performs a check using EMV criteria. 
 * If the reset response is EMV-compliant, the communication settings are 
 * changed, else the card is rejected.  
 * 
 * @param[in]  devnum   The identifier of the Smart Card Interface.
 * 
 * @param[out] atr      Valid pointer to the card Answer To Reset (ATR).
 * 
 * @param[out] length   Valid pointer to the length of the Answer To Reset.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL       Invalid parameter
 * @retval -ERR_ALREADY     Operation already pending
 * @retval  ERR_SCS_CARD_ABSENT     Card absent
 * @retval  ERR_SCS_INVALID_ATR     Bad Answer To Reset
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 * 
 */
int emv_power_up( int devnum, unsigned char *atr, unsigned int *length );

/**
 * The function powers down a card.
 * 
 * @param[in] devnum        The identifier of the Smart Card Interface.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
//int emv_power_down( int devnum );

/**
 * The function is used to retreive the working communication parameters.
 * 
 * @param[in]  devnum       The identifier of the Smart Card Interface.
 * 
 * @param[out] slot_info    Valid pointer to an initialized #EMV1_SLOT_INFO 
 *                          structure. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL       Invalid parameter
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
//int emv_get_slot_info( int devnum, emv_slot_info_t *slot_info );

/**
 * The function is used to set the working communication parameters.
 * 
 * @param[in]  devnum       The identifier of the Smart Card Interface.
 * 
 * @param[in] slot_info     Valid pointer to an initialized #EMV1_SLOT_INFO 
 *                          structure.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL       Invalid parameter
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
//int emv_set_slot_info( int devnum, emv_slot_info_t *slot_info );


                           
/**
 * The function sends a command Application Protocol Data Unit (APDU) to a card, 
 * and retreives the response APDU, plus the status words SW1 SW2. 
 * 
 * The transportation of the APDU in T=0 protocol or T=1 protocol is done 
 * according to EMV criteria.
 * 
 * @param[in]     devnum    The identifier of the Smart Card Interface.
 * 
 * @param[in]   apdu     		Valid pointer to the send buffer
  * @param[in]	apdu_length		APDU command length
 * @param[out]  response     	Valid pointer to the card response
 * 
 * @param[in,out] response_length    Valid pointer to the size of response buffer, 
 *                          		updated with the number of bytes available 
 *                          		in the response buffer.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #emv_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 * 
 */                        
int emv_transmit( int devnum, unsigned char	*apdu, 
						unsigned int	apdu_length, 
						unsigned char	*response, 
						unsigned int	*response_length );
          

/**
 * The function registers an interrupt handler for a type of event.
 *
 * @param[in] devnum    The identifier of the Smart Card Interface. 
 * @param[in] event     Event type. Possible values are the following: 
 *                          \li #EMV_EVENT_ATR_RECEIVED
 *                          \li #EMV_EVENT_DATA_RECEIVED
 *                          \li #EMV_EVENT_DATA_SENT
 *                          \li #EMV_EVENT_ERROR
 * 
 * @param[in] handler   Pointer to the interrupt handler function.
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #emv_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
int emv_attach( int devnum, int event, void (*handler)(int, int) );


/**
 * The function unregisters an interrupt handler that is used to process 
 * a particular event.
 *
 * @param[in] devnum     The identifier of the Smart Card Interface. 
 * @param[in] event      Event type. Possible values are the following: 
 *                          \li #EMV_EVENT_ATR_RECEIVED
 *                          \li #EMV_EVENT_DATA_RECEIVED
 *                          \li #EMV_EVENT_DATA_SENT
 *                          \li #EMV_EVENT_ERROR
 *  
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #emv_devices). 
 * @retval -ERR_NXIO        Device not configured. Use emv_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_ALREADY     Operation already done
 * @retval Other            See \link Error_Codes Error Codes \endlink  
 * 
 */
int emv_detach( int devnum, int event );

/**
 * The function is used to cancel the current smart card transaction.
 *
 * @param[in] devnum    The identifier of the Smart Card Interface. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
int emv_cancel( int devnum );


/**
 * The function is used to retrieve the last status error (usefull with 
 * asynchronous operations).
 *
 * @param[in] devnum    The identifier of the Smart Card Interface. 
 * @param[out]  err     Valid pointer to the last error. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NODEV       No such device. Try another identifier 
 *                          (See #hal_scs_devices). 
 * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink
 * 
 */
int emv_get_last_error( int devnum, int *err );


#else 

typedef void (*emv_handler_t)(int, int);

__emv_defunc2(emv_init, int, devnum, EMV_SLOT_CONFIG *, params);
__emv_defunc1(emv_shutdown, int, devnum);  
__emv_defunc2(emv_get_status, int, devnum, int *, status);
__emv_defunc2(emv_set_config, int, devnum, EMV_SLOT_CONFIG *, params);
__emv_defunc3(emv_power_up, int, devnum, 
                                  unsigned char *, atr, 
                                  unsigned int *, length);
__emv_defunc1(emv_power_down, int, devnum);
__emv_defunc2(emv_set_slot_info, int, devnum, 
                                       emv_slot_info_t *, slot_info);
__emv_defunc2(emv_get_slot_info, int, devnum, 
                                       emv_slot_info_t *, slot_info);                  
__emv_defunc5(emv_transmit, int, devnum, 
                                  unsigned char *, apdu, 
                                  unsigned int, apdu_length, 
                                  unsigned char *, response, 
                                  unsigned int *, response_length);
__emv_defunc3(emv_attach, int, devnum, int, event, 
                                     emv_handler_t, handler);
__emv_defunc2(emv_detach, int, devnum, int, event);
__emv_defunc1(emv_cancel, int, devnum);
__emv_defunc2(emv_get_last_error, int, devnum, int *, err);

#endif  /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif /* C++ */

/** @} */


#endif /* _LIB_EMV_H_ */
