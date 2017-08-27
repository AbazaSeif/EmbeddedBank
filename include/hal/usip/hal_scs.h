/*============================================================================
 *
 *      hal_scs.h
 * 
 *      
 *
 *==========================================================================*/
/*============================================================================
 * 
 * Copyright (c) 2002-2007 Innova Card.
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
 * Description:   This file contains the Smart Card Interface generic functions.
 * 
 *==========================================================================*/
#ifndef _HAL_USIP_SCS_H_
#define _HAL_USIP_SCS_H_


/**
 *  
 * @defgroup HAL_SCS_Error_Codes Smart Card Slot Error Codes
 * 
 * @ingroup HAL_SCS 
 * @ingroup Error_Codes 
 * 
 * This chapter contains descriptions of all error codes used by the \link 
 * HAL_SCS Smart Card Slot Interface \endlink of INNOVA CARD USIP� Professional Hardware 
 * Abstraction Layer. 
 * 
 * @{
 * 
 */

/*----------------------------------------------------------------------------
 * Specific Smart Card Slot error codes declarations
 *---------------------------------------------------------------------------*/
/** This constant is used to reference SCIB 0 */
#define HAL_SCS_SCIB_0    0x00
/** This constant is used to reference SCIB 1 */
#define HAL_SCS_SCIB_1    0x01
/** This constant is used to reference SCIB 2 */
#define HAL_SCS_SCIB_2    0x02
/** This constant is used to unreference SCIBs */
#define HAL_SCS_NO_SCIB    0xff


/** \showinitializer Error code : Command aborted */
#define ERR_SCS_CMD_ABORTED           0xFF

/** \showinitializer Error code : Card mute. The card does not respond to the reset or
 * has interrupted an exchange and a time-out has occured */
#define ERR_SCS_CARD_MUTE           0xFE  

/** \showinitializer Error code : Parity error during an exchange with the card. */
#define ERR_SCS_PARITY              0xFD   

/** \showinitializer Error code : Card consuming too much current or is short-circuiting */
#define ERR_SCS_OVERRUN             0xFC  

/** \showinitializer Error code : Card absent. There is no card in the smart card interface. */
#define ERR_SCS_CARD_ABSENT         0x1  

/** \showinitializer Error code : Card powered down. A call to the #hal_scs_power_up() function
 * must be done prior to any other operation */
#define ERR_SCS_POWER_UP            0xFA  

/** Error code : Error in the card reset response */
#define ERR_SCS_INVALID_ATR         0xF8   

/** \showinitializer Error code : In the card reset response, the Check Character (TCK) 
 * is not correct */
#define ERR_SCS_BAD_ATR_TCK         0xF7

/** \showinitializer Error code : Protocol error */
#define ERR_SCS_PROTOCOL            0xF6

/** \showinitializer Error code : The first byte of command (CLA) is invalid */
#define ERR_SCS_CLASS_NOT_SUPPORTED 0xF5

/** \showinitializer Error code : The card sent an invalid procedure byte */
#define ERR_SCS_PROC_BYTE           0xF4

/** \showinitializer Error code : Speed (TA1 parameter) not supported */
#define ERR_SCS_INVALID_SPEED       0xD0

/** \showinitializer Error code : Function not implemented */
#define ERR_SCS_UNKNOW              0x02  

/** \showinitializer Error code : The card sent an invalid NAD (T=1) */
#define ERR_SCS_INVALID_NAD         0xC1  

/** \showinitializer Error code : Response too long for the buffer */
#define ERR_SCS_OVERFLOW            0x05

/**  @} */

/**
 *  
 * @defgroup HAL_SCS HAL Smart Card Slot Interface
 * 
 * This chapter contains descriptions of the configuration structure, 
 * and functions available to access the Smart Card Interface.
 *
 *
 * @{
 * 
 * @section DESIGN_OVERVIEW Design overview
 * 
 * @subsection TRANSPARENT_MODE Transparent mode
 * The HAL Smart Card Slot Interface manages communication with ISO 7816 1-2-3 
 * asynchronous cards in transparent mode. 
 * Given the variety of customer needs, an upper layer can be necessary to 
 * manage specific cards and protocols by setting dynamically the communication
 * parameters.    
 * 
 * @subsection ANALOG_DEVICE_DRIVER Analog device driver
 * USIP embeds the digital part of a smart card interface.  
 * To complete the interface, customer should provide a physical interface 
 * control (the analog part). Its rule is to drive the card consumption.
 * The HAL Smart Card Slot Interface has been designed to handle a complete 
 * interface. 
 * So, customer has to provide the callback functions (hardware dependant) 
 * which will allow the HAL Smart Card Slot Interface to drive also, the analog 
 * interface.  The callback functions are registred through the implemetation
 * of the #HAL_SCS_DRIVER_IO structure used with the #hal_scs_init() function.
 *
 * @subsection CLOCK_SIGNAL Clock signal
 * To function, the Smart Card Interface needs a clock signal. USIP can provide 
 * it-self this clock signal. Several frequencies are available : 
 * 48MHz, 24MHz, 16MHz, 12MHz, 9.6MHz, 8MHz, 6.86MHz, 6MHz, 5.33MHz, 4.8MHz, 
 * 4.33MHz, 4MHz, 3.69MHz, 3.43MHz, 3.2MHz and 3MHz.
 * For specific needs, this clock can be provide by an external signal.
 * 
 * @subsection TIMER_CONSIDERATION Timer consideration
 * No internal timer of the microcontroller is used by the HAL Smart Card Slot 
 * Interface. 
 * All the timing issues (Work Waiting Time, Extra Guard Time, Character 
 * Waiting Time, Block Waiting Time, Block Guard Time, Block Waiting Time 
 * extension) are fully supported by the specific timers of the ISO UART 
 * whatever the baud rate is on the I/O line. 
 * 
 */


/*----------------------------------------------------------------------------
 * Constant definitions
 *---------------------------------------------------------------------------*/

/** Status incicator : Card not inserted */
#define HAL_SCS_STATUS_CARD_NOT_INSERTED        0x80

/** Status incicator : Card inserted */
#define HAL_SCS_STATUS_CARD_INSERTED            0x00

/** Status incicator : Card not powered */
#define HAL_SCS_STATUS_CARD_NOT_POWERED         0x04

/** Status incicator : Card powered */
#define HAL_SCS_STATUS_CARD_POWERED             0x00

/** Status incicator : Power supply = 5V */
#define HAL_SCS_STATUS_POWER_5V                 0x50

/** Status incicator : Power supply = 3V */
#define HAL_SCS_STATUS_POWER_3V                 0x30

/** Status incicator : Power supply = 1_8V */
#define HAL_SCS_STATUS_POWER_1_8V               0x18


/** Code for the reset command of the smart card interface */
#define HAL_SCS_IOCTL_RESET                             0

/** Code for the power up command of the smart card interface */
#define HAL_SCS_IOCTL_POWER_UP                          1

/** Code for the power down command of the smart card interface */
#define HAL_SCS_IOCTL_POWER_DOWN                        2 

/** Code for the chip select of the analog interface */
#define HAL_SCS_IOCTL_SELECT                            3

/** Code for the chip unselect of the analog interface */
#define HAL_SCS_IOCTL_UNSELECT                          4

/** Code for the check voltage command of the analog interface */
#define HAL_SCS_IOCTL_CHECK_VOLT_OK                     9

/** Code for the power configuration command of the analog interface */
#define HAL_SCS_IOCTL_CONFIG_POWER                      10

/** Code for the check card presence command of the analog interface */
#define HAL_SCS_IOCTL_CHECK_CARD_PRESENCE               11

/** Code to set up the speed communication parameter TA1 of ISO 7816-3 */
#define HAL_SCS_IOCTL_SET_SPEED                          15

/** Code to set up the guard time : parameter N of ISO 7816-3 */
#define HAL_SCS_IOCTL_SET_GUARD_TIME                    16

/** Code to set up the Waiting Time : parameter WI of ISO 7816-3*/
#define HAL_SCS_IOCTL_SET_WAITING_TIME                  17

/** Code to set up the Character Waiting Time */
#define HAL_SCS_IOCTL_SET_CWT                           23

/** Code to set up the Block Waiting Time */
#define HAL_SCS_IOCTL_SET_BWT                           24

#define HAL_SCS_IOCTL_GET_CWT                           26   

#define HAL_SCS_IOCTL_GET_BWT                           27

/** Code to attach handler on card moved event */
#define HAL_SCS_IOCTL_ATTACH_CARD_MOVED                 22

/** Code to indicate a card withdrawn with consequenses a cancel of the current
 * operation.
 */
#define HAL_SCS_IOCTL_CARD_WITHDRAWN                    25

/** Code for the enable/disable the UART mode */
#define HAL_SCS_IOCTL_SET_MODE_AUTO                     28

/** Code for the direct driving of the Card IO signal */
#define HAL_SCS_IOCTL_SET_CARDIO                        12

/** Code for the direct driving of the Card Reset signal */
#define HAL_SCS_IOCTL_SET_CARDRESET                     13

/** Code for the direct driving of the Card Clock signal */
#define HAL_SCS_IOCTL_SET_CARDCLK                       14

/** Code for the direct driving of the Card C4 signal */
#define HAL_SCS_IOCTL_SET_CARDC4                        29

/** Code for the direct driving of the Card C8 signal */
#define HAL_SCS_IOCTL_SET_CARDC8                        30

/** Code for the direct driving of the Card Vcc signal */
#define HAL_SCS_IOCTL_SET_CARDVCC                       31

/** Code for the direct reading of the Card IO signal */
#define HAL_SCS_IOCTL_GET_CARDIO                        32

/** Code for the direct reading of the Card Reset signal */
#define HAL_SCS_IOCTL_GET_CARDRESET                     33

/** Code for the direct reading of the Card Clock signal */
#define HAL_SCS_IOCTL_GET_CARDCLK                       34

/** Code for the direct reading of the Card C4 signal */
#define HAL_SCS_IOCTL_GET_CARDC4                        35

/** Code for the direct reading of the Card C8 signal */
#define HAL_SCS_IOCTL_GET_CARDC8                        36

/** Code for the direct reading of the Card Vcc signal */
#define HAL_SCS_IOCTL_GET_CARDVCC                       37

/** Code for the card reset command from the analog interface */
#define HAL_SCS_IOCTL_CARD_RESET      38

/** Code asking for the number of the selected device  */
#define HAL_SCS_IOCTL_WHICHSELECTED      39

/* Code asking for the Automatic deactivation of the card */
#define HAL_SCS_IOCTL_AUTO_DEACTIVATION     40
/*  */

/** Power supply = 0V */
#define HAL_SCS_POWER_0V             0x00

/** Power supply = 1.8V */
#define HAL_SCS_POWER_1_8V           0x18

/** Power supply = 3V */
#define HAL_SCS_POWER_3V             0x30

/** Power supply = 5V */
#define HAL_SCS_POWER_5V             0x50

/** Smart card protocol: Asynchronous T=0 */
#define HAL_SCS_PROTOCOL_T0          0x00

/** Smart card protocol: Asynchronous T=1 */
#define HAL_SCS_PROTOCOL_T1          0x01

/** Smart card protocol: Synchronous */
#define HAL_SCS_PROTOCOL_SYNC        0x02


/** Internal Clock Frequency : 24MHz */
#define HAL_SCS_CLOCK_24MHz     0x1

/** Internal Clock Frequency : 16MHz */
#define HAL_SCS_CLOCK_16MHz     0x2

/** Internal Clock Frequency : 12MHz */
#define HAL_SCS_CLOCK_12MHz     0x3

/** Internal Clock Frequency : 9.6MHz */
#define HAL_SCS_CLOCK_9_6MHz    0x4

/** Internal Clock Frequency : 8MHz  */
#define HAL_SCS_CLOCK_8MHz      0x5

/** Internal Clock Frequency : 6.86MHz */
#define HAL_SCS_CLOCK_6_86MHz   0x6

/** Internal Clock Frequency : 6MHz */
#define HAL_SCS_CLOCK_6MHz      0x7

/** Internal Clock Frequency : 5.33MHz */
#define HAL_SCS_CLOCK_5_33MHz   0x8

/** Internal Clock Frequency : 4.8MHz */
#define HAL_SCS_CLOCK_4_8MHz    0x9

/** Internal Clock Frequency : 4.33MHz */
#define HAL_SCS_CLOCK_4_33MHz   0xA 

/** Internal Clock Frequency : 4MHz */
#define HAL_SCS_CLOCK_4MHz      0xB

/** Internal Clock Frequency : 3.69MHz */
#define HAL_SCS_CLOCK_3_69MHz   0xC

/** Internal Clock Frequency : 3.43MHz */
#define HAL_SCS_CLOCK_3_43MHz   0xD

/** Internal Clock Frequency : 3.2MHz */
#define HAL_SCS_CLOCK_3_2MHz    0xE

/** Internal Clock Frequency : 3MHz */
#define HAL_SCS_CLOCK_3MHz      0xF

/** This indicator is used to specify that the external clock entry is the main 
 * working clock for the interface.  */
#define HAL_SCS_CLOCK_EXTERNAL  0x10

/** This indicator is used to specify That the main working clock for the smart 
 * card interface must be generated internally.
 */
#define HAL_SCS_CLOCK_INTERNAL  0

/** Convention used to code data bytes : Direct convention */
#define HAL_SCS_CONV_DIRECT    0

/** Convention used to code data bytes : Direct inverse */
#define HAL_SCS_CONV_INVERSE   1



/** This event indicator is raised when all the response of Answer To Reset 
 * has been received */
#define HAL_SCS_EVENT_ATR_RECEIVED                  0

/** This event indicator is raised when the Response APDU is received */
#define HAL_SCS_EVENT_DATA_RECEIVED                 1

/** This event indicator is raised when all data has been sent */
#define HAL_SCS_EVENT_DATA_SENT                     2

/** This event indicator is raised when an error has occured */
#define HAL_SCS_EVENT_ERROR                         3

/** This event indicator is raised when the TS byte of the Answer To Reset 
 * has been received */
#define HAL_SCS_EVENT_ATR_TS_RECEIVED               4

/** This event indicator is raised when the a waiting time extension 
 * has been received */
#define HAL_SCS_EVENT_WAITING_TIME_EXTENSION        5

/** This event indicator is raised when the a character
 *  has been received while BGT is on */
#define HAL_SCS_EVENT_COLLISION_BGT     6

/** This event indicator is raised when the a character
 *  has been received while parity treatment is done */
#define HAL_SCS_EVENT_COLLISION_PARITY    7

/** This event indicator is raised when the a character
 *  has been received for other cases */
#define HAL_SCS_EVENT_COLLISION_OTHER    8
#define HAL_SCS_EVENT_MAX       HAL_SCS_EVENT_COLLISION_BGT

//#define HAL_SCS_EVENT_COUNT             (HAL_SCS_EVENT_WAITING_TIME_EXTENSION+1)
#define HAL_SCS_EVENT_COUNT             (HAL_SCS_EVENT_MAX + 1)

/** In T=1 protocol, the epilogue field is an LRC */
#define HAL_SCS_EDC_LRC     0

/** In T=1 protocol, the epilogue field is an CRC */
#define HAL_SCS_EDC_CRC     1


/*----------------------------------------------------------------------------
 * Device indentifiers
 *---------------------------------------------------------------------------*/

/** The device enumeration defines the Smart Card Slot identifiers 
 */
enum hal_scs_devices {
    /** Identifier of the first Smart Card Slot */
    hal_scs_dev0 = 0,
    /** Identifier of the second Smart Card Slot */
    hal_scs_dev1,
    /** Identifier of the third Smart Card Slot */
    hal_scs_dev2,
    /** Identifier of the fourth Smart Card Slot */
    hal_scs_dev3,
    /** Identifier of the fifth Smart Card Slot */
    hal_scs_dev4,
    /** Identifier of the sixth Smart Card Slot */
    hal_scs_dev5,
    /** This constant is used to fix the number of available Smart Card Slots */
    hal_scs_devices_count
};


/*----------------------------------------------------------------------------
 * Data and configuration structures
 *---------------------------------------------------------------------------*/

/** 
 * This structure is used to call-back the hardware dependent functions that 
 * drive the analog part of the smart card interface. 
 * The user must implement the init() and ioctl() hook functions.
 *   
 */
typedef struct {
    /** 
     * The init() function initializes the analog interface. 
     * The call to the function is done during the hal_scs_init() function.
     */
    int (*init)(int devnum);

    /** 
     * The ioctl() function is the main entry point to perform the analog 
     * interface control. 
     * The function takes as parameter the \c cmd argument which can be :
     *  -#HAL_SCS_IOCTL_RESET                             
     *  -#HAL_SCS_IOCTL_POWER_UP                          
     *  -#HAL_SCS_IOCTL_POWER_DOWN                       
     *  -#HAL_SCS_IOCTL_SELECT                            
     *  -#HAL_SCS_IOCTL_UNSELECT                            
     *  -#HAL_SCS_IOCTL_CHECK_VOLT_OK                     
     *  -#HAL_SCS_IOCTL_CONFIG_POWER                      
     *  -#HAL_SCS_IOCTL_CHECK_CARD_PRESENCE               
     *  -#HAL_SCS_IOCTL_SET_CARDIO                        
     *  -#HAL_SCS_IOCTL_SET_CARDRESET                     
     *  -#HAL_SCS_IOCTL_SET_CARDCLK 
     * 
     * The \c param argument is used to pass specific parameter to the specified 
     * command \c cmd.
     * 
     */
    int (*ioctl)(int devnum, int cmd, void *param);

} HAL_SCS_DRIVER_IO;

/** The configuration structure used to set up the Smart Card Interface */
typedef struct {
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
     * -#HAL_SCS_SCIB_0
     * -#HAL_SCS_SCIB_1
     * -#HAL_SCS_SCIB_2
     * -#HAL_SCS_NO_SCIB
     */
    unsigned char ucSCIB;

} HAL_SCS_CONFIG;

/** The structure used to retrieve or to set up the communication parameters */
typedef struct {
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
     * mode for EDC : #HAL_SCS_EDC_LRC or #HAL_SCS_EDC_CRC (The default value 
     * is an LRC) */
    unsigned char EDC;

    /** The parameter indicates the selected protocol : 
     * #HAL_SCS_PROTOCOL_T0 or #HAL_SCS_PROTOCOL_T1 */
    unsigned char protocol;

    /** The power supply value */
    unsigned char power;

    /** Convention used to transfer byte : 
     * #HAL_SCS_CONV_DIRECT or #HAL_SCS_CONV_INVERSE */
    unsigned char conv;

} hal_scs_slot_info_t;


/*----------------------------------------------------------------------------
 * Function declarations
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


#ifdef CONFIG_LIBROM_NOT_INLINED

    /**
     * The function initializes a Smart Card Interface.
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
    int hal_scs_init(int devnum, HAL_SCS_CONFIG *params);


    /**
     * The function shutdowns a Smart Card Interface.
     * 
     * @param[in] devnum   The identifier of the Smart Card Interface.
     *  
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_shutdown(int devnum);

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
     *  
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_get_status(int devnum, int *status);

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
     * @retval -ERR_NXIO    Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL   Invalid parameter 
     * @retval Other        See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_set_config(int devnum, HAL_SCS_CONFIG *params);

    /**
     * The function powers up and resets an asynchronous card. During the card 
     * Answer To Reset (ATR), the function performs a check for the T0 and TDi 
     * bytes to compute the number of bytes that must be received.
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
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter
     * @retval -ERR_ALREADY     Operation already pending
     * @retval  ERR_SCS_CARD_ABSENT Card absent
     * @retval  ERR_SCS_BAD_ATR     Bad Answer To Reset
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     * 
     */
    int hal_scs_power_up(int devnum, unsigned char *atr, unsigned int *length);


    /**
     * The function powers down a card.
     * 
     * @param[in] devnum        The identifier of the Smart Card Interface.
     * 
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_power_down(int devnum);


    /**
     * The function is used to retreive the working communication parameters.
     * 
     * @param[in]  devnum       The identifier of the Smart Card Interface.
     * 
     * @param[out] slot_info    Valid pointer to an initialized #hal_scs_slot_info_t 
     *                          structure. 
     * 
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_get_slot_info(int devnum, hal_scs_slot_info_t *slot_info);


    /**
     * The function is used to set the working communication parameters.
     * 
     * @param[in]  devnum       The identifier of the Smart Card Interface.
     * 
     * @param[in] slot_info     Valid pointer to an initialized #hal_scs_slot_info_t 
     *                          structure.
     * 
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_set_slot_info(int devnum, hal_scs_slot_info_t *slot_info);

    /**
     * The function sends a T=0 ingoing command to the card , and retreives the 
     * response status word SW1 SW2. This command can send up to 255 bytes.
     * 
     * @param[in]   devnum  The identifier of the Smart Card Interface.
     * 
     * @param[in]   c_tpdu   Valid pointer to a TPDU command buffer 
     *                      {CLA,INS,P1,P2,Lc, DATA }.
     * 
     * @param[out]  r_tpdu   Valid pointer to the card response SW1 SW2.
     *
     * @param[in,out] r_length    Valid pointer to the size of response buffer, 
     *                          updated with the number of bytes available 
     *                          in the response buffer.
     * 
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_t0_in(int devnum, unsigned char *c_tpdu,
            unsigned char *r_tpdu, int *r_length);


    /**
     * The function sends a T=0 outgoing command to a card, 
     * and retreives the response card, plus the status word SW1 SW2.
     * 
     * @param[in]    devnum  The identifier of the Smart Card Interface.
     * 
     * @param[in]    c_tpdu   Valid pointer to a TPDU command buffer 
     *                          {CLA,INS,P1,P2,Le}.
     * 
     * @param[out]   r_tpdu   Valid pointer to the card response
     * 
     * @param[in,out] r_length    Valid pointer to the size of response buffer, 
     *                          updated with the number of bytes available 
     *                          in the response buffer.
     * 
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_t0_out(int devnum, unsigned char *c_tpdu,
            unsigned char *r_tpdu, int *r_length);


    /**
     * This function may be used when for T=1 protocol exchanges when the 
     * application layer provides the complete T=1 frame including prologue, 
     * information and epilogue fields. The frame is passed to this function from 
     * address frame_in and is assumed to be \c len length. The function will send 
     * this frame to the smart card without any verification and will return 
     * the length of the received frame from the card.
     * 
     * @param[in]   devnum      The identifier of the Smart Card Interface.
     * 
     * @param[in]   frame_in    Valid pointer to the send buffer
     * 
     * @param[in]   length_in   The size buffer frame_in.
     * 
     * @param[out]  frame_out   Valid pointer to the card response
     * 
     * @param[in,out] length_out in   : Valid pointer to the size buffer frame_out,
     *                          out  : Valid pointer to the length of the frame_out.
     *
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     * 
     */
    int hal_scs_t1_block(int devnum,
            unsigned char *frame_in,
            int length_in,
            unsigned char *frame_out,
            int *length_out);

    /**
     * The function sends a Protocol Parameter Selection (PPS) to a card, 
     * and retreives the response card.
     * 
     * @param[in]   devnum  The identifier of the Smart Card Interface.
     * 
     * @param[in]   pps_request    Valid pointer to the send buffer
     * 
     * @param[in]   size_request    size buffer in
     * 
     * @param[out]  pps_response       Valid pointer to the card response
     * 
     * @param[in,out] size_response in   : Valid pointer to the size buffer dataOut,
     *                          out : Valid pointer to the length of the response.
     * 
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     *
     */
    int hal_scs_pps_exchange(int devnum,
            unsigned char *pps_request,
            int size_request,
            unsigned char *pps_response,
            int *size_response);


    /**
     * The function performs Smart Card Interface specific control functions.
     * 
     * @param[in]   devnum  The identifier of the Smart Card Interface.
     * 
     * @param[in]     cmd   Requested control function. Possible values are:
     *                          \li #HAL_SCS_IOCTL_RESET                             
     *                          \li #HAL_SCS_IOCTL_POWER_UP                          
     *                          \li #HAL_SCS_IOCTL_POWER_DOWN                       
     *                          \li #HAL_SCS_IOCTL_SELECT                            
     *                          \li #HAL_SCS_IOCTL_UNSELECT                             
     *                          \li #HAL_SCS_IOCTL_CHECK_VOLT_OK                     
     *                          \li #HAL_SCS_IOCTL_CONFIG_POWER                      
     *                          \li #HAL_SCS_IOCTL_CHECK_CARD_PRESENCE               
     *                          \li #HAL_SCS_IOCTL_SET_CARDIO                        
     *                          \li #HAL_SCS_IOCTL_SET_CARDRESET                     
     *                          \li #HAL_SCS_IOCTL_SET_CARDCLK 
     *                          \li #HAL_SCS_IOCTL_SET_SPEED
     *                          \li #HAL_SCS_IOCTL_SET_GUARD_TIME
     *                          \li #HAL_SCS_IOCTL_SET_WAITING_TIME
     *                          \li #HAL_SCS_IOCTL_CARD_WITHDRAWN
     * 
     * @param[in,out] param  Points to a buffer that contains any data required for 
     *                      the given control function or receives data from 
     *                      that function.
     *
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_INVAL       Invalid parameter
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_ioctl(int devnum, int cmd, void *param);

    /**
     * The function registers an interrupt handler for a type of event.
     *
     * @param[in] devnum    The identifier of the Smart Card Interface. 
     * @param[in] event     Event type. Possible values are the following: 
     *                          \li #HAL_SCS_EVENT_ATR_RECEIVED
     *                          \li #HAL_SCS_EVENT_DATA_RECEIVED
     *                          \li #HAL_SCS_EVENT_DATA_SENT
     *                          \li #HAL_SCS_EVENT_ERROR
     * 
     * @param[in] handler   Pointer to the interrupt handler function.
     * 
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter 
     * @retval Other            See \link Error_Codes Error Codes \endlink
     * 
     */
    int hal_scs_attach(int devnum, int event, void (*handler)(int, int));

    /**
     * The function unregisters an interrupt handler that is used to process 
     * a particular event.
     *
     * @param[in] devnum     The identifier of the Smart Card Interface. 
     * @param[in] event      Event type. Possible values are the following: 
     *                          \li #HAL_SCS_EVENT_ATR_RECEIVED
     *                          \li #HAL_SCS_EVENT_DATA_RECEIVED
     *                          \li #HAL_SCS_EVENT_DATA_SENT
     *                          \li #HAL_SCS_EVENT_ERROR
     *  
     * @retval -ERR_NO          No error 
     * @retval -ERR_NODEV       No such device. Try another identifier 
     *                          (See #hal_scs_devices). 
     * @retval -ERR_NXIO        Device not configured. Use hal_scs_init() first. 
     * @retval -ERR_INVAL       Invalid parameter 
     * @retval -ERR_ALREADY     Operation already done
     * @retval Other            See \link Error_Codes Error Codes \endlink  
     * 
     */
    int hal_scs_detach(int devnum, int event);


    /**
     * The function is used to cancel a smart card transaction during 
     * an asynchrounous operation.
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
    int hal_scs_cancel(int devnum);

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
    int hal_scs_get_last_error(int devnum, int *err);

#else

#include "hal_sys.h"

    typedef void (*hal_scs_handler_t)(int, int);

    __hal_defunc2(hal_scs_init, int, devnum, HAL_SCS_CONFIG *, params);
    __hal_defunc1(hal_scs_shutdown, int, devnum);
    __hal_defunc2(hal_scs_get_status, int, devnum, int *, status);
    __hal_defunc2(hal_scs_set_config, int, devnum, HAL_SCS_CONFIG *, params);
    __hal_defunc3(hal_scs_power_up, int, devnum, unsigned char *, atr, unsigned int *, length);
    __hal_defunc1(hal_scs_power_down, int, devnum);
    __hal_defunc2(hal_scs_get_slot_info, int, devnum, hal_scs_slot_info_t *, slot_info);
    __hal_defunc2(hal_scs_set_slot_info, int, devnum, hal_scs_slot_info_t *, slot_info);
    __hal_defunc4(hal_scs_t0_in, int, devnum, unsigned char *, c_tpdu,
            unsigned char *, r_tpdu, int *, r_length);
    __hal_defunc4(hal_scs_t0_out, int, devnum, unsigned char *, c_tpdu,
            unsigned char *, r_tpdu, int *, r_length);
    __hal_defunc5(hal_scs_t1_block, int, devnum, unsigned char *, frame_in,
            int, length_in, unsigned char *, frame_out, int *, length_out);
    __hal_defunc5(hal_scs_pps_exchange, int, devnum, unsigned char *, pps_request,
            int, size_request, unsigned char *, pps_response, int *, size_response);
    __hal_defunc3(hal_scs_ioctl, int, devnum, int, cmd, void *, param);
    __hal_defunc3(hal_scs_attach, int, devnum, int, event, hal_scs_handler_t, handler);
    __hal_defunc2(hal_scs_detach, int, devnum, int, event);
    __hal_defunc1(hal_scs_cancel, int, devnum);
    __hal_defunc2(hal_scs_get_last_error, int, devnum, int *, err);

    __hal_deisr(hal_scs_isr0, void);
    __hal_deisr(hal_scs_isr1, void);
    __hal_deisr(hal_scs_isr2, void);

#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _HAL_USIP_SCS_H_ */


