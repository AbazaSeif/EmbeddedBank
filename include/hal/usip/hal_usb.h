/*============================================================================
 *
 *      hal_usb.h
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
#ifndef HAL_USIP_USB_H
#define HAL_USIP_USB_H	

/**
 *  
 * @defgroup HAL_USB_Error_Codes USB Error Codes 
 * 
 * @ingroup HAL_USB 
 * 
 * @ingroup Error_Codes 
 * 
 * This chapter contains descriptions of all error codes used by the \link 
 * HAL_USB USB module \endlink of INNOVA CARD USIP® Professional Hardware 
 * Abstraction Layer. 
 * 
 * @{
 * 
 */


/** \showinitializer No error */
#define  ERR_USB_NO                           (0x00)
/** \showinitializer Failed to allocate memory for internal data structures */
#define  ERR_USB_ALLOC                        (0x81)
/** \showinitializer Incorrect component status requested */
#define  ERR_USB_BAD_STATUS                   (0x82)
/** \showinitializer The specified service was not previously registered */
#define  ERR_USB_CLOSED_SERVICE               (0x83)
/** \showinitializer Service was already registered */
#define  ERR_USB_OPEN_SERVICE                 (0x84)
/** \showinitializer A previously queued transfer on the specified endpoint is 
 * still in progress; wait until the transfer has been completed */
#define  ERR_USB_TRANSFER_IN_PROGRESS         (0x85)
/** \showinitializer Endpoint is stalled; no transfer can take place until the 
 * endpoint is unstalled */
#define  ERR_USB_ENDPOINT_STALLED             (0x86)
/** \showinitializer Could not allocate memory for the internal state 
 * structure */
#define  ERR_USB_ALLOC_STATE                  (0x87)
/** \showinitializer Could not allocate memory for the internal service 
 * structure */
#define  ERR_USB_ALLOC_SERVICE                (0x8C)
/** \showinitializer The internal control pipe handle is not valid */
#define  ERR_USB_INVALID_PIPE_HANDLE          (0x8F)
/** \showinitializer Required bandwidth could not be allocated */
#define  ERR_USB_OPEN_PIPE_FAILED             (0x90)
/** \showinitializer Initialization data conflicts: A_BUS_DROP and A_BUS_REQ 
 * inputs should not be set to TRUE at the same time */
#define  ERR_USB_INIT_DATA                    (0x91)
/** \showinitializer Failure: B-device is not in B_IDLE state */
#define  ERR_USB_SRP_REQ_INVALID_STATE        (0x92)
/** \showinitializer Transmit failed */
#define  ERR_USB_TX_FAILED                    (0x93)
/** \showinitializer Receive failed */
#define  ERR_USB_RX_FAILED                    (0x94)
/** \showinitializer Invalid number of endpoints for initialization */
#define  ERR_USB_INVALID_NUM_OF_ENDPOINTS     (0x99)


/** \showinitializer Device not found */
#define  ERR_USB_DEVICE_NOT_FOUND             (0xC0)
/** \showinitializer Device busy */
#define  ERR_USB_DEVICE_BUSY                  (0xC1)
/** \showinitializer Device class not found */
#define  ERR_USB_NO_DEVICE_CLASS              (0xC3)
/** \showinitializer Null pointer */
#define  ERR_USB_UNKNOWN_ERROR                (0xC4)
/** \showinitializer Invalid request type */
#define  ERR_USB_INVALID_BMREQ_TYPE           (0xC5)
/** \showinitializer Get memory failed */
#define  ERR_USB_GET_MEMORY_FAILED            (0xC6)
/** \showinitializer Invalid type of malloc memory */
#define  ERR_USB_INVALID_MEM_TYPE             (0xC7)
/** \showinitializer Decrsiptor not found */
#define  ERR_USB_NO_DESCRIPTOR                (0xC8)
/** \showinitializer Interface not found or No interface memory */
#define  ERR_USB_NO_INTERFACE                 (0xCA)
/** \showinitializer Invalid configuration number */
#define  ERR_USB_INVALID_CFIG_NUM             (0xCB)
/** \showinitializer Invalid address of class's instance list anchor */
#define  ERR_USB_INVALID_ANCHOR               (0xCC)


/* Error Codes for lower-layer */
/** \showinitializer Error Codes for lower-layer: Could not allocate memory for 
 * the internal transfer structure */
#define  ERR_USB_ALLOC_TR                     (0xA9)

/**  @} */

/** 
 * 
 * @defgroup HAL_USB HAL Universal Serial Bus On-The-Go (USB OTG) 
 * 
 * This chapter contains descriptions of the configuration structure and the 
 * functions available to access the Universal Serial Bus On-The-Go Stack. 
 * 
 * @section hal_usb Overview 
 * 
 * \image html usb_stack.png 
 * 
 * Readers can notice 3 applications in the above picture.
 * 
 * Those who are developing OTG applications will actually have to develop both 
 * device and host applications and write a central OTG application which will 
 * work with OTG API to decide the role host or device and load the appropriate 
 * device or host applications. 
 * 
 * Those who are making device only or host only applications will also have to 
 * write a central OTG application. 
 * 
 * Host part, OTG part and device part of the USB stack are represented by the 
 * blue, yellow and green colors. Next few sections explain each of the parts 
 * of the stack in more details. 
 * 
 * @section hal_usb_firewall Firewall Management 
 * 
 * USIP Professional provide a powerful USB firewall to prevent from any 
 * unauthorized access to system memory. 
 * 
 * About the Firewall feature refer to "USIP® Professional Datasheet": 
 *  \li section "USIP System Controller", description of Global Control 
 *  Register 1, and 
 *  \li section "USB 2.0 OTG", use of Buffer Descriptor Table. 
 * 
 * <b>Hardware Constraints</b> 
 * 
 * All data accessed by the USB interface must be allocated in the memory area 
 * authorized by the USB firewall.
 * 
 * The data accessed by the USB interface are: 
 * \li the Buffer Descriptor Table,
 * \li the Transfer Buffers (field ADDR[31..0] of the Buffer Descriptors)
 * 
 * The USB firewall authorizes access to a customizable memory range <b>within 
 * the internal SRAM</b>.
 * 
 * <b>HAL Behavior</b> 
 * 
 * The HAL sets by default the authorized memory for USB transfers to the whole 
 * internal SRAM memory. 
 * 
 * The HAL internaly manages the Buffer Descriptor Table within a USB dedicated 
 * heap memory. 
 * 
 * The authorized memory for USB transfers and the USB dedicated heap memmory 
 * can be customized using the function hal_usb_ioctl(). 
 * 
 * <b>User Code Constraints</b>
 * 
 * The user should finaly insure that all "buffer_ptr" parameters of the 
 * functions hal_usb_device_send_data() and hal_usb_device_recv_data() point 
 * memory areas within authorized memory. 
 * 
 * @{ 
 * 
 */

#define HAL_USB_IOCTL_ADDR_0         0
#define HAL_USB_IOCTL_ADDR_C         0x6
#define HAL_USB_IOCTL_ADDR_1FFFC     0xFFFE

/** The control parameter lets the Mips Core, the USB, the DMA and the noise 
 * generator have the same priority on the sstem bus. */
#define HAL_USB_IOCTL_PRIO_1_NO           0
/** The control parameter lets the Mips Core and the USB have a higher 
 * priority on the system bus than the DMA and the noise generator. */
#define HAL_USB_IOCTL_PRIO_1_CORE_USB     1
/** The control parameter lets the USB have a higher priority on the system 
 * bus than the Mips Core, the DMA and the noise generator. */
#define HAL_USB_IOCTL_PRIO_1_USB          2
/** The control parameter lets the USB have a higher priority on the system 
 * bus than the Mips Core. It also letes the Mips Core have a higher priority 
 * than the DMA and the noise generator. */
#define HAL_USB_IOCTL_PRIO_2_USB_1_CORE   3
/** The control parameter lets the Mips Core, the DMA and the noise generator 
 * have a higher priority on the system bus than the USB. */
#define HAL_USB_IOCTL_PRIO_1_CORE_DMA_NG  4

#define HAL_USB_IOCTL_SIZE_0            0
#define HAL_USB_IOCTL_SIZE_8k           1
#define HAL_USB_IOCTL_SIZE_16k          2
#define HAL_USB_IOCTL_SIZE_104k         0xD
#define HAL_USB_IOCTL_SIZE_112k         0xE
#define HAL_USB_IOCTL_SIZE_128k         0xF

/** The control function retrieves USB address field from GCR1 */
#define HAL_USB_IOCTL_GET_ADDR          0
/** The control function retrieves System Priority field from GCR1 */
#define HAL_USB_IOCTL_GET_PRIO          1
/** The control function retrieves USB size field from GCR1 */
#define HAL_USB_IOCTL_GET_SIZE          2
/** The control function sets USB address field to GCR1 */
#define HAL_USB_IOCTL_SET_ADDR          3
/** The control function sets System Priority field to GCR1 */
#define HAL_USB_IOCTL_SET_PRIO          4
/** The control function sets USB size field to GCR1 */
#define HAL_USB_IOCTL_SET_SIZE          5

/** The control function sets the base address of USB dedicated heap memory. 
 * \note This control is not permitted during USB use: after hal_usb_otg_init() 
 * and before hal_usb_otg_shutdown() */
#define HAL_USB_IOCTL_SET_HEAP_BASE     6
/** The control function sets the size of USB dedicated heap memory. 
 * \note This control is not permitted during USB use: after hal_usb_otg_init() 
 * and before hal_usb_otg_shutdown() */
#define HAL_USB_IOCTL_SET_HEAP_SIZE     7

/** 
 * The control function attaches the callback function when an access is 
 * attempted out of the internal memory area reserved for the USB interface 
 * transfers. 
 */
#define HAL_USB_IOCTL_ATTACH_OVERFLOW   8

/*----------------------------------------------------------------------------
 * OTG Defines 
 *---------------------------------------------------------------------------*/

/**
 * Set to TRUE by the host part of the OTG application if A-device has enabled 
 * HNP on the HNP-capable B-device; FALSE otherwise.
 */                             
#define  HAL_USB_OTG_STATUS_A_SET_B_HNP_ENABLE (0x01)

/**
 * Set to TRUE by the device part of the OTG application if HNP-capable B-device 
 * has been enabled by the A-device to do HNP; FALSE otherwise.
 */
#define  HAL_USB_OTG_STATUS_B_HNP_ENABLE       (0x02)

/** Application running on A-device has requested control of the bus. */
#define  HAL_USB_OTG_STATUS_A_BUS_REQ          (0x03)

/**
 * The B-device bus request input is set to TRUE for as long as the application 
 * running on the B-device requests control of the bus; otherwise, the input is 
 * set to FALSE.
 */
#define  HAL_USB_OTG_STATUS_B_BUS_REQ          (0x04) 

/**
 * This variable can be used by the A-device application to turn on the VBUS.
 */                                      
#define  HAL_USB_OTG_STATUS_A_VBUS_ON          (0x05)   

/**
 * This parameter is not available to #hal_usb_otg_get_status(). 
 * The variable is used by the B-device OTG application to start SRP (session 
 * request protocol). SRP can be requested only in B_IDLE state.
 */ 
#define  HAL_USB_OTG_STATUS_B_SRP_REQ          (0x06)

/**
 * The B-device connect variable is set to TRUE by the A-device application 
 * (in the callback function that is registered by the host application) when 
 * a connect event is detected.
 */
#define  HAL_USB_OTG_STATUS_B_CONN             (0x08)   

/**
 * The B-device bus suspend variable is set to TRUE by the device part of 
 * the OTG application when the A-device detects that the B-device has 
 * suspended the bus.
 */
#define  HAL_USB_OTG_STATUS_B_BUS_SUSPEND      (0x09)

/**
 * The A-device bus suspend variable is set to TRUE by the device part of the 
 * OTG application when the B-device detects that the A-device has suspended 
 * the bus.
 */
#define  HAL_USB_OTG_STATUS_A_BUS_SUSPEND      (0x0A)
 
/**
 * The A-device bus resume variable is set to TRUE when the B-device detects 
 * that the A-device is signaling a resume (K-state) on the bus. This feature 
 * is currently not supported.
 */
#define  HAL_USB_OTG_STATUS_A_BUS_RESUME       (0x0C)

/**
 * The A-device connect variable is set to TRUE by the B-device application 
 * (in the callback function that is registered by the host application) when 
 * a connect event is detected by the dual-role B-device.
 */
#define  HAL_USB_OTG_STATUS_A_CONN             (0x0D) 

/** 
 * Get the internal OTG state 
 */
#define  HAL_USB_OTG_STATE              (0x0E)

/**
 * The A-device bus suspend request variable is set to TRUE by the host part of 
 * the OTG application when the A-device has enabled HNP on the HNP-capable 
 * B-device and is ready to suspend the bus.
 */
#define  HAL_USB_OTG_STATUS_A_BUS_SUSPEND_REQ  (0x0F)

/**
 * The B-device bus resume variable is set to TRUE when the A-device detects 
 * that the B-device is signaling a resume (K-state) on the bus.
 */
#define  HAL_USB_OTG_STATUS_B_BUS_RESUME       (0x10)

/* no action require with this change */
/**
 * The A-device bus drop input is set to TRUE when the application running on 
 * the A-device needs to power down the bus; otherwise, the input is set to 
 * FALSE. When HAL_USB_OTG_STATUS_A_BUS_DROP is TRUE, the #HAL_USB_OTG_STATUS_A_BUS_REQ 
 * input must be FALSE.
 */ 
#define  HAL_USB_OTG_STATUS_A_BUS_DROP         (0x11)

/** The device is in Host mode. */
#define  HAL_USB_OTG_STATUS_HOST_ACTIVE        (0x12)

/** The device is in Peripheral mode. */
#define  HAL_USB_OTG_STATUS_DEVICE_ACTIVE      (0x13)


/* OTG HNP/SRP states */
/** Starting state for OTG state machine */
#define    HAL_USB_OTG_STATE_OTG_START                          (0)
/** OTG state machine: A-device is idle */
#define    HAL_USB_OTG_STATE_A_IDLE                             (1)
/** OTG state machine: A-device waits for the voltage on the VBus to rise */
#define    HAL_USB_OTG_STATE_A_WAIT_VRISE                       (2)
/** OTG state machine: A-device waits for the B-device to signal a connection */
#define    HAL_USB_OTG_STATE_A_WAIT_BCON                        (3)
/** OTG state machine: A-device is host */
#define    HAL_USB_OTG_STATE_A_HOST                             (4)
/** OTG state machine: A-device has requested Bus suspend */
#define    HAL_USB_OTG_STATE_A_SUSPEND                          (5)
/** OTG state machine: A-device is peripheral */
#define    HAL_USB_OTG_STATE_A_PERIPHERAL                       (6)
/** OTG state machine: A-device waits for the voltage on the VBus to drop */
#define    HAL_USB_OTG_STATE_A_WAIT_VFALL                       (7)
/** OTG state machine: B-device is idle */
#define    HAL_USB_OTG_STATE_B_IDLE                             (8)
/** OTG state machine: B-device attempts to initiate a session via SRP */
#define    HAL_USB_OTG_STATE_B_SRP_INIT                         (9)
/** OTG state machine: B-device is peripheral */
#define    HAL_USB_OTG_STATE_B_PERIPHERAL                       (10)
/** OTG state machine: B-device waits for the A-device to signal a connection */
#define    HAL_USB_OTG_STATE_B_WAIT_ACON                        (11)
/** OTG state machine: B-device is host */
#define    HAL_USB_OTG_STATE_B_HOST                             (12)

/*
 * State returned by the OTG state machine. The application should identify 
 * these events and take action according to the event. 
 */

/** The event is raised when the system becomes a USB host.\n 
 * A-device: 
 *      \li at USB OTG initialization 
 *      \li when leaving A PERIPHERAL state to A_IDLE or A WAIT BCON state\n 
 * B-device: when entering B WAIT ACON state */
#define  HAL_USB_OTG_EVENT_HOST_UP                    (0x01)

/** The event is raised when the system becomes a USB device.\n 
 * A-device: when entering A PERIPHERAL state\n 
 * B-device: 
 *      \li at USB OTG initialization 
 *      \li when leaving B HOST or B WAIT ACON state to enter B IDLE or 
 *      B PERIPHERAL state */
#define  HAL_USB_OTG_EVENT_DEVICE_UP                  (0x02)

/** The event is raised when the system is not a USB host anymore.\n 
 * A-device side: when entering A PERIPHERAL state\n 
 * B-device side: when leaving B HOST or B WAIT ACON state to enter B IDLE or 
 *      B PERIPHERAL state */
#define  HAL_USB_OTG_EVENT_HOST_DOWN                  (0x03)

/** The event is raised when the system is not a USB device anymore.\n 
 * A-device: when leaving A PERIPHERAL state to A_IDLE or A WAIT BCON state\n 
 * B-device: when entering B WAIT ACON state */
#define  HAL_USB_OTG_EVENT_DEVICE_DOWN                (0x04)

/** The event is raised when the B-device is entering B SRP INIT state */
#define  HAL_USB_OTG_EVENT_SRP_ACTIVE                 (0x05)
/** The event is raised when the B-device cannot detect any answer from 
 * A-device at the end of SRP */
#define  HAL_USB_OTG_EVENT_SRP_FAIL                   (0x06)

/** The event is raised when the A-device detects an over current condition 
 * (a_vbus_vld false) when A WAIT_VRISE timed out */
#define  HAL_USB_OTG_EVENT_OVER_CURRENT               (0x08)
/** The event is raised when the A-device detects a A WAIT BCON time out */
#define  HAL_USB_OTG_EVENT_NO_CONNECTION              (0x09)
/** The event is raised when the B-device detects a B ASE0 BRST time out */
#define  HAL_USB_OTG_EVENT_HNP_FAILED                 (0x0A)


/*----------------------------------------------------------------------------
 * OTG Configuration structure
 */

/** OTG configuration structure */
typedef struct HAL_USB_OTG_CONFIG
{
   /** A-device bus drop: TRUE when the Application running on the A-device 
    * needs to power down the bus, FALSE otherwise. When this input is TRUE, 
    * then the A_BUS_REQ input must be FALSE. */
   int              A_BUS_DROP;
   /** A-device bus request: TRUE during the time that the application running 
    * on the A-device wants to use the bus. */
   int              A_BUS_REQ;
   /** B-device bus request: TRUE during the time that the application running 
    * on the B-device wants to use the bus. */
   int              B_BUS_REQ;
   /** Callback function that will be called when one of the following OTG 
    * events occurs: 
    * \li #HAL_USB_OTG_EVENT_HOST_UP 
    * \li #HAL_USB_OTG_EVENT_DEVICE_UP 
    * \li #HAL_USB_OTG_EVENT_HOST_DOWN 
    * \li #HAL_USB_OTG_EVENT_DEVICE_DOWN 
    * \li #HAL_USB_OTG_EVENT_SRP_ACTIVE 
    * \li #HAL_USB_OTG_EVENT_SRP_FAIL 
    * \li #HAL_USB_OTG_EVENT_OVER_CURRENT 
    * \li #HAL_USB_OTG_EVENT_NO_CONNECTION 
    * \li #HAL_USB_OTG_EVENT_HNP_FAILED */
   void (*handler)( unsigned int event );
} HAL_USB_OTG_CONFIG;


/*----------------------------------------------------------------------------
 * Device Defines 
 *---------------------------------------------------------------------------*/

/** Direction of transfer: receive */
#define HAL_USB_RECV         	0
/** Direction of transfer: send */
#define HAL_USB_SEND         	1


/** Event indicator attached to endpoint 0 */
#define  HAL_USB_ENDPOINT0                  (0x00)
/** Event indicator attached to endpoint 1 */
#define  HAL_USB_ENDPOINT1                  (0x01)
/** Event indicator attached to endpoint 2 */
#define  HAL_USB_ENDPOINT2                  (0x02)
/** Event indicator attached to endpoint 2 */
#define  HAL_USB_ENDPOINT3                  (0x03)
/** The device event is raised when the bus is reset */
#define  HAL_USB_DEVICE_EVENT_BUS_RESET            (0x10)
/** The device event is raised when a Start of Frame token is received */
#define  HAL_USB_DEVICE_EVENT_SOF                  (0x12)
/** The device event is raised when a Resume signaling is detected
 * \note When not in suspend mode this event should be detached */
#define  HAL_USB_DEVICE_EVENT_RESUME               (0x13)
/** The device event is raised when a Suspend signaling is detected */
#define  HAL_USB_DEVICE_EVENT_SLEEP                (0x14)
/** The device event is raised when any error occured in the USB interface */
#define  HAL_USB_DEVICE_EVENT_ERROR                (0x16)
/** The device event is raised when a stall handshake has been sent */
#define  HAL_USB_DEVICE_EVENT_STALL                (0x17)


/** Endpoint type: Control endpoint */
#define  HAL_USB_ENDPOINT_CONTROL             (0)
/** Endpoint type: Isochronous endpoint */
#define  HAL_USB_ENDPOINT_ISOCHRONOUS         (1)
/** Endpoint type: Bulk endpoint */
#define  HAL_USB_ENDPOINT_BULK                (2)
/** Endpoint type: Interrupt endpoint */
#define  HAL_USB_ENDPOINT_INTERRUPT           (3)

/** Endpoint initialization flag: 
 * If the last data packet transferred is the maximum packet size for the 
 * endpoint, terminate the transfer with a zerolength packet. */
#define  HAL_USB_DEVICE_ZERO_TERMINATE          (0x0)
/** Endpoint initialization flag: 
 * If the last data packet transferred is the maximum packet size for the 
 * endpoint, do not terminate the transfer with a zero-length packet. */
#define  HAL_USB_DEVICE_DONT_ZERO_TERMINATE     (0x1)

/* possible values of XD->bStatus */
/** Status of the transfer\n 
 *  Host side: No transfer is queued or completed\n 
 *  Device side: Endpoint is idle */
#define  HAL_USB_TRANSFER_STATUS_IDLE                     (0)
/** Status of the transfer\n 
 *  Device side: Transfer successfully initiated (queued in the hardware but 
 * not in progress yet) */
#define  HAL_USB_TRANSFER_STATUS_PENDING         (2)
/** Status of the transfer\n 
 *  Host/Device side: Transfer is queued in the hardware and is in progress 
 * (at least one packet already transfered) */
#define  HAL_USB_TRANSFER_STATUS_IN_PROGRESS     (3)
/** Status of the transfer\n 
 *  Device side: Endpoint is disabled */
#define  HAL_USB_TRANSFER_STATUS_DISABLED                 (5)
/** Status of the transfer\n 
 *  Device side: Endpoint is stalled */
#define  HAL_USB_TRANSFER_STATUS_STALLED                  (6)
/** Status of the transfer\n 
 *  Host side: Transfer is queued, but is not in progress */
#define  HAL_USB_TRANSFER_STATUS_QUEUED          (7)


/* Informational Request/Set Types */
/** Device Get/Set status request type: Device state */
#define  HAL_USB_DEVICE_STATE          (0x01)
/** Device Get/Set status request type: Interface number */
#define  HAL_USB_DEVICE_INTERFACE             (0x02)
/** Device Get/Set status request type: Device address */
#define  HAL_USB_DEVICE_ADDRESS               (0x03)
/** Device Get/Set status request type: Device configuration */
#define  HAL_USB_DEVICE_CURRENT_CONFIG        (0x04)
/** Device Get/Set status request type: Current value of SOF counter */
#define  HAL_USB_DEVICE_SOF_COUNT             (0x05)
/** Device Get/Set status request type: Device status */
#define  HAL_USB_DEVICE_STATUS                (0x06)
//#define  HAL_USB_DEVICE_TEST_MODE             (0x07)
/** Device Get/Set status request type: Endpoint status */
#define  HAL_USB_DEVICE_ENDPOINT              (0x10)
#define  HAL_USB_DEVICE_ENDPOINT_NUMBER_MASK  (0x0F)

/* Device state */
#define  HAL_USB_DEVICE_STATE_UNKNOWN                   (0xff)
/** Device state: The device state is POWERED when it is initialized */
#define  HAL_USB_DEVICE_STATE_POWERED                   (0x03)
/** Device state: The device state is DEFAULT when the bus is reset */
#define  HAL_USB_DEVICE_STATE_DEFAULT                   (0x02)
/** Device state: The device state is ADDRESS when an address is assigned */
#define  HAL_USB_DEVICE_STATE_ADDRESS                   (0x01)
/** Device state: The device state is CONFIG when a configuration is set */
#define  HAL_USB_DEVICE_STATE_CONFIG                    (0x00)
/** Device state: The device state is SUSPEND when the bus is suspended */
#define  HAL_USB_DEVICE_STATE_SUSPEND                   (0x80)

/** Device status mask: The device is self-powered */
#define  HAL_USB_DEVICE_SELF_POWERED                    (0x01)
/** Device status mask: The device has remote wakeup enabled and can wake the 
 * host up during suspend */
#define  HAL_USB_DEVICE_REMOTE_WAKEUP                   (0x02)

/** Endpoint status: The endpoint is stalled */
#define  HAL_USB_ENDPOINT_STALLED                  (0x00)
/** Endpoint status: The endpoint is halted */
#define  HAL_USB_ENDPOINT_HALTED                   (0x01)


/*----------------------------------------------------------------------------
 * Host Defines 
 *---------------------------------------------------------------------------*/

/* Event codes for attach/detach etc. callback */
/** Event raised when the device instance is attached */
#define  HAL_USB_ATTACH_EVENT        1   /* device attach */
/** Event raised when the device instance is detached */
#define  HAL_USB_DETACH_EVENT        2   /* device detach */
/** Event raised when the device instance is reconfigured */
#define  HAL_USB_CONFIG_EVENT        3   /* device reconfigured */
/** Event raised when the device instance interface is selected */
#define  HAL_USB_INTF_EVENT          4   /* device interface selected */


/* Available host event types */
/** The host event is raised when the host has been resumed */
#define HAL_USB_HOST_EVENT_RESUME           (0x01)
/** The host event is raised when a device has been connected to the bus */
#define HAL_USB_HOST_EVENT_ATTACH           (0x04)
/** The host event is  raised when a device has been disconnected from the 
 * bus */
#define HAL_USB_HOST_EVENT_DETACH           (0x05)
/** The host event is  raised when a stall handshake has been detected */
#define  HAL_USB_HOST_EVENT_STALL           (0x06)


/* Bus Control values */
/** Bus Control: make the bus idle */
#define  HAL_USB_CONTROL_NO_OPERATION                    (0x00)
/** Bus Control: reset the bus */
#define  HAL_USB_CONTROL_ASSERT_BUS_RESET                (0x01)
/** Bus Control: bring the bus out of reset mode */
#define  HAL_USB_CONTROL_DEASSERT_BUS_RESET              (0x02)
/** Bus Control: if the bus is suspended, resume operation */
#define  HAL_USB_CONTROL_ASSERT_RESUME                   (0x03)
/** Bus Control: bring the bus out of resume mode */
#define  HAL_USB_CONTROL_DEASSERT_RESUME                 (0x04)
/** Bus Control: do not generate start-of-frame tokens */
#define  HAL_USB_CONTROL_SUSPEND_SOF                     (0x05)
/** Bus Control: generate and transmit start-of-frame tokens */
#define  HAL_USB_CONTROL_RESUME_SOF                      (0x06)


/* Pipe Types */
/** Pipe Type: Isochronous pipe */
#define  HAL_USB_PIPE_ISOCHRONOUS                (0x01)
/** Pipe Type: Interrupt pipe */
#define  HAL_USB_PIPE_INTERRUPT                  (0x02)
/** Pipe Type: Control pipe */
#define  HAL_USB_PIPE_CONTROL                    (0x03)
/** Pipe Type: Bulk pipe */
#define  HAL_USB_PIPE_BULK                       (0x04)


/* Descriptor Types */
/** Descriptor Type: Device Descriptor */
#define  HAL_USB_DESCRIPTOR_TYPE_DEVICE         0x1
/** Descriptor Type: Configuration Descriptor */
#define  HAL_USB_DESCRIPTOR_TYPE_CONFIG         0x2
/** Descriptor Type: String Descriptor */
#define  HAL_USB_DESCRIPTOR_TYPE_STRING         0x3
/** Descriptor Type: Interface Descriptor */
#define  HAL_USB_DESCRIPTOR_TYPE_INTERFACE      0x4
/** Descriptor Type: Endpoint Descriptor */
#define  HAL_USB_DESCRIPTOR_TYPE_ENDPOINT       0x5
//#define  HAL_USB_DESCRIPTOR_TYPE_QUALIFIER      0x6
//#define  HAL_USB_DESCRIPTOR_TYPE_OTHER_SPEED    0x7
//#define  HAL_USB_DESCRIPTOR_TYPE_INTF_POWER     0x8
/** Descriptor Type: OTG Descriptor */
#define  HAL_USB_DESCRIPTOR_TYPE_OTG            0x9

/* Descriptor Sizes */
/** Device Descriptor Size */
#define HAL_USB_DESCRIPTOR_SIZE_DEVICE          18
/** Configuration Descriptor Size */
#define HAL_USB_DESCRIPTOR_SIZE_CONFIG          9
/** Interface Descriptor Size */
#define HAL_USB_DESCRIPTOR_SIZE_INTERFACE       9
/** Endpoint Descriptor Size */
#define HAL_USB_DESCRIPTOR_SIZE_ENDPOINT        7
/** OTG Descriptor Size */
#define HAL_USB_DESCRIPTOR_SIZE_OTG             3

/* Descriptor Attributes */
/** OTG Descriptor Attribute: Supports SRP */
#define  HAL_USB_OTG_SRP_SUPPORT   (0x01)
/** OTG Descriptor Attribute: Supports HNP */
#define  HAL_USB_OTG_HNP_SUPPORT   (0x02)


/** The recipient of the request is a device */
#define  HAL_USB_HOST_CH9_DEVICE    0x00
/** The recipient of the request is an interface */
#define  HAL_USB_HOST_CH9_INTERFACE 0x01
/** The recipient of the request is an endpoint */
#define  HAL_USB_HOST_CH9_ENDPOINT  0x02


/** Setup packet */
typedef struct
{
   /** Request type */
   unsigned char    REQUESTTYPE;
   /** Request */
   unsigned char    REQUEST;
   /** Value */
   unsigned short    VALUE;
   /** Index */
   unsigned short    INDEX;
   /** Number of bytes to transfer if there is a data phase */
   unsigned short    LENGTH;
} HAL_USB_SETUP, *HAL_USB_SETUP_PTR;


/** class-related data  */
typedef void *hal_usb_interface_handle;             
/** Chapter 9 descriptor */
typedef void *hal_usb_interface_descriptor_handle;  
/** pipe or pipe-bundle */
typedef void *hal_usb_pipe_handle;                  
/** item on host's list */
typedef void *hal_usb_device_instance_handle;       
/** interface info.     */
typedef void * hal_usb_class_intf_handle;            
typedef void * hal_usb_class_handle;
typedef unsigned int hal_usb_descriptor_type;


/** Information for one class or device driver */
typedef struct hal_usb_driver_info
{
   /** Vendor ID per USB-IF */
   unsigned char         idVendor[2];
   /** Product ID per manufacturer */
   unsigned char         idProduct[2];
   /** Class code, if 0 see interface */
   unsigned char         bDeviceClass;
   /** Sub-Class code, 0 if class = 0 */
   unsigned char         bDeviceSubClass;
   /** Protocol, if 0 see interface */
   unsigned char         bDeviceProtocol;
   /* Alignment padding */
   unsigned char         reserved;
   /** Function to call when above information matches the one in device’s 
    *  descriptors occurs. Parameters:
    *  \li Device instance handle 
    *  \li Interface descriptor handle 
    *  \li Event causing callback; one of #HAL_USB_ATTACH_EVENT, 
    *  #HAL_USB_DETACH_EVENT, #HAL_USB_CONFIG_EVENT or #HAL_USB_INTF_EVENT */
   void  (* attach_call) ( hal_usb_device_instance_handle,
                           hal_usb_interface_descriptor_handle,
                           unsigned int );
    
} HAL_USB_HOST_DRIVER_INFO, * HAL_USB_HOST_DRIVER_INFO_PTR;


/** Pipe configuration structure */
typedef struct
{
    /** Instance on list of all devices that owns pipe */
    void *DEV_INSTANCE;
    /** Interval for polling pipe for data transfer */
    unsigned int INTERVAL;
    /** Pipe's maximum packet size for sending or receiving */
    unsigned int MAX_PACKET_SIZE;
    /** 
     * The maximum number of NAK responses tolerated. 
     * MUST be zero for interrupt For USB 1.1, after count NAKs/frame, 
     * transaction is deferred to next frame. 
     */
    unsigned int NAK_COUNT;
    /** The frame # to start xfer   */
    unsigned int FIRST_FRAME;
    /** Microframe # to start xfer  */
    unsigned int FIRST_UFRAME;
    /** 
     * After all data transferred, should we terminate the transfer with 
     * a zero length packet if the last packet size == MAX_PACKET_SIZE? 
     */
    unsigned int FLAGS;
    /** The device's address 1-127  */
    unsigned char DEVICE_ADDRESS;
    /** The endpoint number         */
    unsigned char ENDPOINT_NUMBER;
    /** Transfert direction; #HAL_USB_RECV or #HAL_USB_SEND */
    unsigned char DIRECTION;
    /** Pipe type; #HAL_USB_PIPE_CONTROL, #HAL_USB_PIPE_INTERRUPT, 
     * #HAL_USB_PIPE_BULK or #HAL_USB_PIPE_ISOCHRONOUS */
    unsigned char PIPETYPE;
    /** Number of transaction per frame, only high-speed high-bandwidth pipes */
    unsigned char TRS_PER_UFRAME;

} HAL_USB_PIPE_CONFIG;


/** Transfer parameters structure */
typedef struct
{
    /** Transfer number on this pipe */
    unsigned int TR_INDEX;
    /** 
     * address of buffer containing the data to be transmitted (including OUT 
     * data phase of control transfers) 
     */
    unsigned char *TX_BUFFER;
    /** address of buffer to receive data */
    unsigned char *RX_BUFFER;
    /** 
     * length of data to transmit.  For control transfers, the length of data 
     * for the data phase 
     */
    unsigned int TX_LENGTH;
    /** 
     * length of data to be received. For control transfers, this indicates 
     * the length of data for the data phase 
     */
    unsigned int RX_LENGTH;
    /** 
     * The callback function to be invoked when a transfer is completed or 
     * an error is to be reported. The transaction callback parameters are 
     * respectively: 
     * \li the pipe handle, 
     * \li the parameter specified by higher level, 
     * \li a pointer to buffer containing data (TX or RX), 
     * \li the length of data transferred 
     * \li the status, preferably ERR_NO or HAL_STATUS_USB_DONE etc. 
     */
    void (* CALLBACK)(hal_usb_pipe_handle,
                      void *,
                      unsigned char *,
                      unsigned int,
                      unsigned int);
    /** 
     * The second parameter to be passed into the callback function when 
     * it is invoked. 
     */
    void *CALLBACK_PARAM;
    /** 
     * address of buffer containing the setup packet to send. 
     * Relevant for control pipes only 
     */
    unsigned char *DEV_REQ_PTR;

} HAL_USB_TRANSFER_PARAMS;


/** Device Descriptor */
typedef struct HAL_USB_DEVICE_DESCRIPTOR
{
    unsigned char  bLength __attribute__((packed));
    unsigned char  bDescriptorType __attribute__((packed));
    unsigned short bcdUSB __attribute__((packed));
    unsigned char  bDeviceClass __attribute__((packed));
    unsigned char  bDeviceSubClass __attribute__((packed));
    unsigned char  bDeviceProtocol __attribute__((packed));
    unsigned char  bMaxPacketSize0 __attribute__((packed));
    unsigned short idVendor __attribute__((packed));
    unsigned short idProduct __attribute__((packed));
    unsigned short bcdDevice __attribute__((packed));
    unsigned char  iManufacturer __attribute__((packed));
    unsigned char  iProduct __attribute__((packed));
    unsigned char  iSerialNumber __attribute__((packed));
    unsigned char  bNumConfigurations __attribute__((packed));
} HAL_USB_DEVICE_DESCRIPTOR;

/** Endpoint Descriptor */
typedef struct HAL_USB_ENDPOINT_DESCRIPTOR
{
    unsigned char  bLength __attribute__((packed));
    unsigned char  bDescriptorType __attribute__((packed));
    unsigned char  bEndpointAddress __attribute__((packed));
    unsigned char  bmAttributes __attribute__((packed));
    unsigned short wMaxPacketSize __attribute__((packed));
    unsigned char  bInterval __attribute__((packed));
} HAL_USB_ENDPOINT_DESCRIPTOR;

/** Configuration Descriptor */
typedef struct HAL_USB_CONFIGURATION_DESCRIPTOR
{
    unsigned char  bLength __attribute__((packed));
    unsigned char  bDescriptorType __attribute__((packed));
    unsigned short wTotalLength __attribute__((packed));
    unsigned char  bNumInterfaces __attribute__((packed));
    unsigned char  bConfigurationValue __attribute__((packed));
    unsigned char  iConfiguration __attribute__((packed));
    unsigned char  bmAttributes __attribute__((packed));
    unsigned char  MaxPower __attribute__((packed));
} HAL_USB_CONFIGURATION_DESCRIPTOR;

/** Interface Descriptor */
typedef struct HAL_USB_INTERFACE_DESCRIPTOR
{
    unsigned char bLength __attribute__((packed));
    unsigned char bDescriptorType __attribute__((packed));
    unsigned char bInterfaceNumber __attribute__((packed));
    unsigned char bAlternateSetting __attribute__((packed));
    unsigned char bNumEndpoints __attribute__((packed));
    unsigned char bInterfaceClass __attribute__((packed));
    unsigned char bInterfaceSubClass __attribute__((packed));
    unsigned char bInterfaceProtocol __attribute__((packed));
    unsigned char iInterface __attribute__((packed));
} HAL_USB_INTERFACE_DESCRIPTOR;

/** String Descriptor */
typedef struct HAL_USB_STRING_DESCRIPTOR
{
    unsigned char bLength __attribute__((packed));
    unsigned char bDescriptorType __attribute__((packed));
    unsigned char bString[40] __attribute__((packed));
} HAL_USB_STRING_DESCRIPTOR;

/** OTG Descriptor */
typedef struct HAL_USB_OTG_DESCRIPTOR
{
   /** Descriptor size in bytes = 3 */
   unsigned char   bLength;          
   /** OTG type = 9 */
   unsigned char   bDescriptorType;  
   /** OTG characteristics: #HAL_USB_OTG_SRP_SUPPORT and/or 
    * #HAL_USB_OTG_HNP_SUPPORT */
   unsigned char   bmAttributes;     
} HAL_USB_OTG_DESCRIPTOR;  

/**
 * The following struct is for storing a class's validity-check 
 * code with the pointer to the data.  The address of one such 
 * struct is passed as a pointer to select-interface calls, 
 * where values for that interface get initialized.  Then the 
 * struct should be passed to class calls using the interface. 
 */
typedef struct hal_usb_class_call_struct
{
   hal_usb_class_intf_handle    class_intf_handle;
   unsigned int                 code_key;
}  HAL_USB_CLASS_CALL_STRUCT, * HAL_USB_CLASS_CALL_STRUCT_PTR;


/*----------------------------------------------------------------------------
 * Other Defines 
 *---------------------------------------------------------------------------*/


/* Bus Speed */
#define  HAL_USB_SPEED_FULL                      (0)
#define  HAL_USB_SPEED_LOW                       (1)
#define  HAL_USB_SPEED_HIGH                      (2)


/** Standard Device Request: Halt feature (allows the host to stall and clear 
 * an endpoint) */
#define  HAL_USB_FEATURE_ENDPOINT_HALT        0
/** Standard Endpoint Request: Remote wakeup feature */
#define  HAL_USB_FEATURE_REMOTE_WAKEUP        1
/** Standard Endpoint Request: Test mode feature */
#define  HAL_USB_FEATURE_TEST_MODE            2


//
// Macro Definition
//
#define HAL_USB_ENDPOINT_DIRECTION_OUT(endpoint)      (endpoint) 
#define HAL_USB_ENDPOINT_DIRECTION_IN(endpoint)       (0x80|endpoint)


/*----------------------------------------------------------------------------
 * Configuration structure
 */


//
// USB power descriptor added to core specification
//

/*#define HAL_USB_SUPPORT_D0_COMMAND      0x01UCHAR
#define HAL_USB_SUPPORT_D1_COMMAND      0x02
#define HAL_USB_SUPPORT_D2_COMMAND      0x04
#define HAL_USB_SUPPORT_D3_COMMAND      0x08

#define HAL_USB_SUPPORT_D1_WAKEUP       0x10
#define HAL_USB_SUPPORT_D2_WAKEUP       0x20
*/
/*
typedef struct HAL_USB_POWER_DESCRIPTOR {
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bCapabilitiesFlags;
    unsigned short EventNotification;
    unsigned short D1LatencyTime;
    unsigned short D2LatencyTime;
    unsigned short D3LatencyTime;
    unsigned char PowerUnit;
    unsigned short D0PowerConsumption;
    unsigned short D1PowerConsumption;
    unsigned short D2PowerConsumption;
} HAL_USB_POWER_DESCRIPTOR __attribute__((aligned(1))), *PHAL_USB_POWER_DESCRIPTOR;


typedef struct HAL_USB_COMMON_DESCRIPTOR {
    unsigned char bLength;
    unsigned char bDescriptorType;
} HAL_USB_COMMON_DESCRIPTOR, *HAL_PUSB_COMMON_DESCRIPTOR;

*/


//#define  HAL_USB_TEST_MODE_TEST_PACKET        (0x0400)
//
//



/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The function performs USB specific control functions. 
 *
 * @param[in] cmd           Requested control function. One of: 
 *                              \li #HAL_USB_IOCTL_SET_ADDR 
 *                              \li #HAL_USB_IOCTL_GET_ADDR 
 *                              \li #HAL_USB_IOCTL_SET_SIZE 
 *                              \li #HAL_USB_IOCTL_GET_SIZE 
 *                              \li #HAL_USB_IOCTL_SET_PRIO 
 *                              \li #HAL_USB_IOCTL_GET_PRIO 
 *                              \li #HAL_USB_IOCTL_SET_HEAP_BASE 
 *                              \li #HAL_USB_IOCTL_SET_HEAP_SIZE 
 *                              \li #HAL_USB_IOCTL_ATTACH_OVERFLOW 
 * 
 * @param[in,out] data      Points to a buffer that contains any data required 
 *                          for the given control function or receives data 
 *                          from that function: 
 *                              \li #HAL_USB_IOCTL_SET_ADDR / 
 *                                  #HAL_USB_IOCTL_GET_ADDR : 
 *                                  Offset of allowed area in internal SRAM 
 *                              \li #HAL_USB_IOCTL_SET_SIZE / 
 *                                  #HAL_USB_IOCTL_GET_SIZE : 
 *                                  Size of allowed area (number of 8kB pages) 
 *                              \li #HAL_USB_IOCTL_SET_PRIO / 
 *                                  #HAL_USB_IOCTL_GET_PRIO : 
 *                                  System Priority (#HAL_USB_IOCTL_PRIO_1_NO, 
 *                                  #HAL_USB_IOCTL_PRIO_1_CORE_USB, 
 *                                  #HAL_USB_IOCTL_PRIO_1_USB, 
 *                                  #HAL_USB_IOCTL_PRIO_2_USB_1_CORE or 
 *                                  #HAL_USB_IOCTL_PRIO_1_CORE_DMA_NG) 
 *                              \li #HAL_USB_IOCTL_ATTACH_OVERFLOW : 
 *                                  address of the callback function\n
 *                                  void (*handler)( void );\n
 *                                  The event is detached if data null pointer 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval -ERR_NOTTY       Inappropriate ioctl for device 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_ioctl(int cmd, int *data);

/*----------------------------------------------------------------------------
 * OTG Functions 
 *---------------------------------------------------------------------------*/
#define HAL_USB_OTG_FUNCTIONS

/**
 * The function resets and activates the USB hardware then initializes the USB 
 * OTG stack and and its interface. 
 * 
 * @param[in] params        Pointer on a USB OTG configuration structure 
 *                          allocated and filled by the caller. 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_otg_init( HAL_USB_OTG_CONFIG *params );

/**
 * The function shutdowns the initialized USB OTG device and disables the USB 
 * hardware. 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_otg_shutdown( void );

/**
 * The function sets the status of the specified type (OTG parameter).
 * 
 * @param[in] type          Parameter to set; one of:
 *                              \li #HAL_USB_OTG_STATUS_A_SET_B_HNP_ENABLE 
 *                              \li #HAL_USB_OTG_STATUS_B_HNP_ENABLE 
 *                              \li #HAL_USB_OTG_STATUS_A_BUS_REQ 
 *                              \li #HAL_USB_OTG_STATUS_B_BUS_REQ 
 *                              \li #HAL_USB_OTG_STATUS_A_VBUS_ON 
 *                              \li #HAL_USB_OTG_STATUS_B_SRP_REQ 
 *                              \li #HAL_USB_OTG_STATUS_B_CONN 
 *                              \li #HAL_USB_OTG_STATUS_B_BUS_SUSPEND 
 *                              \li #HAL_USB_OTG_STATUS_A_BUS_SUSPEND 
 *                              \li #HAL_USB_OTG_STATUS_A_BUS_RESUME 
 *                              \li #HAL_USB_OTG_STATUS_A_CONN 
 *                              \li #HAL_USB_OTG_STATUS_A_BUS_SUSPEND_REQ 
 *                              \li #HAL_USB_OTG_STATUS_B_BUS_RESUME 
 * 
 * @param[in] status        Value to assign to specified parameter: TRUE or 
 *                          FALSE.
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_otg_set_status( unsigned char type, int status );

/**
 * The function gets the value of a specified OTG parameter.
 * 
 * @param[in]   type        Parameter to get, any one of the following values, 
 *                              \li #HAL_USB_OTG_STATUS_A_SET_B_HNP_ENABLE 
 *                              \li #HAL_USB_OTG_STATUS_B_HNP_ENABLE 
 *                              \li #HAL_USB_OTG_STATUS_A_BUS_REQ 
 *                              \li #HAL_USB_OTG_STATUS_B_BUS_REQ 
 *                              \li #HAL_USB_OTG_STATUS_B_CONN 
 *                              \li #HAL_USB_OTG_STATUS_B_BUS_SUSPEND 
 *                              \li #HAL_USB_OTG_STATUS_A_BUS_SUSPEND 
 *                              \li #HAL_USB_OTG_STATUS_A_BUS_RESUME 
 *                              \li #HAL_USB_OTG_STATUS_A_CONN 
 *                              \li #HAL_USB_OTG_STATE 
 *                              \li #HAL_USB_OTG_STATUS_B_BUS_RESUME 
 * 
 * @param[out]  status      Pointer to the status of the requested type.\n 
 *                          When type is any type but HAL_USB_OTG_STATE, status 
 *                          points to TRUE or FALSE.\n 
 *                          When type is HAL_USB_OTG_STATE, status points to 
 *                          one the following values: 
 *                              \li #HAL_USB_OTG_STATE_OTG_START 
 *                              \li #HAL_USB_OTG_STATE_A_IDLE 
 *                              \li #HAL_USB_OTG_STATE_A_WAIT_VRISE 
 *                              \li #HAL_USB_OTG_STATE_A_WAIT_BCON 
 *                              \li #HAL_USB_OTG_STATE_A_HOST 
 *                              \li #HAL_USB_OTG_STATE_A_SUSPEND 
 *                              \li #HAL_USB_OTG_STATE_A_PERIPHERAL 
 *                              \li #HAL_USB_OTG_STATE_A_WAIT_VFALL 
 *                              \li #HAL_USB_OTG_STATE_B_IDLE 
 *                              \li #HAL_USB_OTG_STATE_B_SRP_INIT 
 *                              \li #HAL_USB_OTG_STATE_B_PERIPHERAL 
 *                              \li #HAL_USB_OTG_STATE_B_WAIT_ACON  
 *                              \li #HAL_USB_OTG_STATE_B_HOST 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 * @see For more information on USB_OTG_STATE and the possible values of status,
 * see On-The-Go Supplement to the USB 2.0 Specification Revision 1.0 
 * (December 18, 2001).
 * 
 */
int hal_usb_otg_get_status( unsigned char type, unsigned int *status );

/*----------------------------------------------------------------------------
 * Device Functions 
 *---------------------------------------------------------------------------*/
#define HAL_USB_DEVICE_FUNCTIONS

/**
 * The function initializes the USB device controller: 
 * \li Activation and reset of USB device controller 
 * \li Memory allocation for transfer queues: the USB device controller can 
 * enqueue on transfer per endpoint and per direction. 
 * \li Initialization of the USB device state machine 
 * 
 * @param[in] endpoints     Number of bi-directional endpoints to initialize 
 *                          (endpoint 0 included) 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_init( unsigned char endpoints );


/**
 * The function is useful if the services of the USB Device controller are no 
 * longer required or if the USB Device controller needs to be configured as 
 * a host. 
 * 
 * The function does the following: 
 *  -# terminates all transactions 
 *  -# unregisters all the services 
 *  -# disconnects the device from the USB bus 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_shutdown( void );

/**
 * The function enqueues the received request. 
 * 
 * To check whether the transaction was complete, the application can call
 * hal_usb_device_get_transfer_status() or use the callback function 
 * registered for the endpoint. 
 * 
 * Do not call hal_usb_device_recv_data() to receive a setup packet. 
 * 
 * \warning Memory management: The data to receive are directly written by the 
 * USB hardware in the specified buffer. In order to prevent from buffer 
 * overflow, the user should insure that the specified buffer is wide enough to 
 * receive the whole transfer that the host may send. 
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] buffer_ptr    Pointer to the buffer into which to receive data 
 *
 * @param[in] size          Number of bytes to receive 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_recv_data( unsigned char endpoint_number,
                              unsigned char *buffer_ptr,
                              unsigned int size );


/**
 * The function sends the data on the specified endpoint. The function actually 
 * enqueues the send request and returns. 
 * 
 * To check whether the transaction was complete, the application can call 
 * hal_usb_device_get_transfer_status() or use the callback function registered 
 * for the endpoint. 
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] buffer_ptr    Pointer to the buffer to send 
 * 
 * @param[in] size          Number of bytes to send 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_send_data( unsigned char endpoint_number,
                              unsigned char *buffer_ptr,
                              unsigned int size );
 
 
/**
 * The function checks whether the transfer on the specified endpoint and 
 * direction is active. If it is not active, the function changes the status to 
 * idle and returns. If the transfer is active, the function terminates all the
 * transfers queued on the endpoint and sets the status to idle. 
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] direction     Direction of transfer; one of:
 *                              \li #HAL_USB_RECV 
 *                              \li #HAL_USB_SEND 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_cancel_transfer( unsigned char endpoint_number, 
                                    unsigned char direction );
  
/**
 * The function registers the callback function for an event or endpoint. 
 * 
 * The callback function is called at the end of each phase of a Control 
 * transfer; that is, after: 
 *      \li a setup packet is received 
 *      \li data phase is complete 
 *      \li the status phase is complete 
 * 
 * For all other transfers, the callback function is called only at the end 
 * of the transfer.
 * 
 * @param[in] event_endpoint  Endpoint (0 through 15) or event to service: 
 *                          \li #HAL_USB_ENDPOINT0 
 *                          \li #HAL_USB_ENDPOINT1 
 *                          \li #HAL_USB_ENDPOINT2 
 *                          \li #HAL_USB_ENDPOINT3 
 *                          \li ... 
 *                          \li #HAL_USB_DEVICE_EVENT_BUS_RESET 
 *                          \li #HAL_USB_DEVICE_EVENT_SOF 
 *                          \li #HAL_USB_DEVICE_EVENT_RESUME 
 *                          \li #HAL_USB_DEVICE_EVENT_SLEEP 
 *                          \li #HAL_USB_DEVICE_EVENT_ERROR 
 *                          \li #HAL_USB_DEVICE_EVENT_STALL 
 * 
 * @param[in] handler       Pointer to the service's callback function. 
 *                          Parameters: 
 *                          \li is_setup_pkt: Setup packet indication; one of 
 *                          TRUE, FALSE 
 *                          \li direction: Direction of transfer; one of 
 *                          #HAL_USB_RECV, #HAL_USB_SEND 
 *                          \li buffer_ptr: Pointer to the data 
 *                          \li length: Number of bytes in the buffer 
 *                          \li errors: Any errors (see Error Interrupt Status 
 *                          and Enable Registers in USIP datasheet) 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_attach( unsigned char event_endpoint, 
                           void (*handler)( unsigned int is_setup_pkt,
                                            unsigned char direction, 
                                            unsigned char *buffer_ptr,
                                            unsigned int length,
                                            unsigned char errors) );

/**
 * The function unregisters the callback function that is used to process 
 * the event or endpoint. As a result, that type of event or endpoint cannot be 
 * serviced by a callback function. 
 * 
 * Before calling the function, the application must disable the endpoint with 
 * hal_usb_device_deinit_endpoint(). 
 * 
 * @param[in] event_endpoint Endpoint (0 through 15) or event: 
 *                          \li #HAL_USB_ENDPOINT0 
 *                          \li #HAL_USB_ENDPOINT1 
 *                          \li #HAL_USB_ENDPOINT2 
 *                          \li #HAL_USB_ENDPOINT3 
 *                          \li ... 
 *                          \li #HAL_USB_DEVICE_EVENT_BUS_RESET 
 *                          \li #HAL_USB_DEVICE_EVENT_SOF 
 *                          \li #HAL_USB_DEVICE_EVENT_RESUME 
 *                          \li #HAL_USB_DEVICE_EVENT_SLEEP 
 *                          \li #HAL_USB_DEVICE_EVENT_ERROR 
 *                          \li #HAL_USB_DEVICE_EVENT_STALL 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 * @see #hal_usb_device_attach() 
 * 
 */
int hal_usb_device_detach( unsigned char event_endpoint );

/**
 * The function initializes the specified endpoint.
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] max_packet_size Maximum packet size (in bytes) for the endpoint 
 * 
 * @param[in] direction     Direction of transfer; one of: 
 *                              \li #HAL_USB_RECV 
 *                              \li #HAL_USB_SEND 
 * 
 * @param[in] endpoint_type Type of endpoint; one of: 
 *                              \li #HAL_USB_ENDPOINT_BULK 
 *                              \li #HAL_USB_ENDPOINT_CONTROL 
 *                              \li #HAL_USB_ENDPOINT_INTERRUPT 
 *                              \li #HAL_USB_ENDPOINT_ISOCHRONOUS 
 * 
 * @param[in] flag          One of: 
 *                              \li #HAL_USB_DEVICE_ZERO_TERMINATE 
 *                              \li #HAL_USB_DEVICE_DONT_ZERO_TERMINATE 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_init_endpoint( unsigned char endpoint_number,
                                  unsigned short max_packet_size,
                                  unsigned char direction,
                                  unsigned char endpoint_type,
                                  unsigned char flag );

/**
 * The function resets the data structures specific to the specified endpoint 
 * and disables the endpoint in the specified direction.
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] direction     Direction of transfer; one of: 
 *                              \li #HAL_USB_RECV 
 *                              \li #HAL_USB_SEND 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 *
 */
int hal_usb_device_deinit_endpoint( unsigned char endpoint_number, 
                                    unsigned char direction );

/**
 * The function stalls the endpoint in the specified direction. 
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] direction     Direction of transfer; one of: 
 *                              \li #HAL_USB_RECV 
 *                              \li #HAL_USB_SEND 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_stall_endpoint( unsigned char endpoint_number, 
                                   unsigned char direction );
   
/**
 * The function unstalls the endpoint in the specified direction. 
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] direction     Direction of transfer; one of: 
 *                              \li #HAL_USB_RECV 
 *                              \li #HAL_USB_SEND 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_unstall_endpoint( unsigned char endpoint_number, 
                                     unsigned char direction );
 
/**
 * The function sends a resume signal on the USB bus for remote wakeup. 
 * 
 */
void hal_usb_device_assert_resume( void );

/**
 * The function gets the status of the transfer on the specified endpoint. It 
 * reads the status and also checks whether the transfer is active. 
 * 
 * To check whether a receive or send transfer was complete, the application 
 * can call hal_usb_device_get_transfer_status() or use the callback function 
 * registered for the endpoint. 
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[in] direction     Direction of transfer; one of: 
 *                              \li #HAL_USB_RECV 
 *                              \li #HAL_USB_SEND 
 * 
 * @param[out] status       Transfer status; one of: 
 *                              \li #HAL_USB_TRANSFER_STATUS_IDLE 
 *                              \li #HAL_USB_TRANSFER_STATUS_PENDING 
 *                              \li #HAL_USB_TRANSFER_STATUS_IN_PROGRESS 
 *                              \li #HAL_USB_TRANSFER_STATUS_DISABLED 
 *                              \li #HAL_USB_TRANSFER_STATUS_STALLED 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_get_transfer_status( unsigned char endpoint_number, 
                                        unsigned char direction,
                                        int *status );

/**
 * The function gets the status of the specified component for the GET STATUS 
 * device request. This function must be used by the GET STATUS device response 
 * function. 
 * 
 * @param[in] component     Component status; one of: 
 *                              \li #HAL_USB_DEVICE_STATE 
 *                              \li #HAL_USB_DEVICE_ADDRESS 
 *                              \li #HAL_USB_DEVICE_CURRENT_CONFIG 
 *                              \li #HAL_USB_DEVICE_STATUS 
 *                              \li #HAL_USB_DEVICE_ENDPOINT orred with the 
 *                              endpoint number 
 *                              \li #HAL_USB_DEVICE_INTERFACE 
 *                              \li #HAL_USB_DEVICE_SOF_COUNT 
 * 
 * @param[out] status       Requested status 
 *                              \li #HAL_USB_DEVICE_STATE: one of 
 *                                      #HAL_USB_DEVICE_STATE_POWERED, 
 *                                      #HAL_USB_DEVICE_STATE_DEFAULT, 
 *                                      #HAL_USB_DEVICE_STATE_ADDRESS, 
 *                                      #HAL_USB_DEVICE_STATE_CONFIG or 
 *                                      #HAL_USB_DEVICE_STATE_SUSPEND 
 *                              \li #HAL_USB_DEVICE_STATUS: a combination of 
 *                                      #HAL_USB_DEVICE_SELF_POWERED and 
 *                                      #HAL_USB_DEVICE_REMOTE_WAKEUP 
 *                              \li #HAL_USB_DEVICE_ENDPOINT: 
 *                                      #HAL_USB_ENDPOINT_STALLED or 
 *                                      #HAL_USB_ENDPOINT_HALTED 
 *                              \li Other components: the requested value 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 *
 */
int hal_usb_device_get_status( unsigned char component, 
                               unsigned short *status );

/**
 * The function sets the status of the specified component for the SET STATUS 
 * device request. This function must be used by the SET STATUS device response 
 * function. 
 * 
 * @param[in] component     The component status. one of: 
 *                              \li #HAL_USB_DEVICE_STATE 
 *                              \li #HAL_USB_DEVICE_ADDRESS 
 *                              \li #HAL_USB_DEVICE_CURRENT_CONFIG 
 *                              \li #HAL_USB_DEVICE_STATUS 
 *                              \li #HAL_USB_DEVICE_ENDPOINT orred with 
 *                                  the endpoint number 
 *                              \li #HAL_USB_DEVICE_INTERFACE 
 *                              \li #HAL_USB_DEVICE_SOF_COUNT 
 * 
 * @param[in] setting       Status to set 
 *                              \li #HAL_USB_DEVICE_STATE: one of 
 *                                      #HAL_USB_DEVICE_STATE_POWERED, 
 *                                      #HAL_USB_DEVICE_STATE_DEFAULT, 
 *                                      #HAL_USB_DEVICE_STATE_ADDRESS, 
 *                                      #HAL_USB_DEVICE_STATE_CONFIG or 
 *                                      #HAL_USB_DEVICE_STATE_SUSPEND 
 *                              \li #HAL_USB_DEVICE_STATUS: a combination of 
 *                                      #HAL_USB_DEVICE_SELF_POWERED and 
 *                                      #HAL_USB_DEVICE_REMOTE_WAKEUP 
 *                              \li #HAL_USB_DEVICE_ENDPOINT: 
 *                                      #HAL_USB_ENDPOINT_STALLED or 
 *                                      #HAL_USB_ENDPOINT_HALTED 
 *                              \li Other components: the value to set 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_device_set_status( unsigned char component, 
                               unsigned short setting );
   
/**
 * The function reads the setup data for an endpoint. 
 * 
 * To be called only after the callback function for the endpoint notifies 
 * the application that a setup packet has been received. 
 * 
 * @param[in] endpoint_number Endpoint number 
 * 
 * @param[out] buff_ptr     Buffer for receiving Setup packet 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 *
 */
int hal_usb_device_read_setup_data( unsigned char endpoint_number, 
                                    unsigned char *buff_ptr );

/*----------------------------------------------------------------------------
 * Host Functions 
 *---------------------------------------------------------------------------*/
#define HAL_USB_HOST_FUNCTIONS

/**
 * The function initialized the USB Host controller interface data structures 
 * and the controller interface. 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_init( void );

/**
 * The function registers a driver for a device with a particular vendor ID, 
 * product ID, class, subclass and protocol code. 
 * 
 * @param[in] info_table_ptr Device info table (see #HAL_USB_HOST_DRIVER_INFO) 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_driver_info_register( void *info_table_ptr );

/**
 * The function registers a callback function for a specified event. 
 * 
 * @param[in] type          The type of event to service; one of: 
 *                          \li #HAL_USB_HOST_EVENT_ATTACH 
 *                          \li #HAL_USB_HOST_EVENT_DETACH 
 *                          \li #HAL_USB_HOST_EVENT_RESUME 
 *                          \li #HAL_USB_HOST_EVENT_STALL 
 * 
 * @param[in] handler       Pointer to the event's callback function. 
 *                          Event-specific parameter: 
 *                          \li #HAL_USB_HOST_EVENT_ATTACH: speed 
 *                          \li Others: 0 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_attach( unsigned char type, void(*handler)(unsigned int) );

/**
 * The function controls the bus operations. 
 * 
 * @param[in] control       Operation to be performed on the bus; one of: 
 *                          \li #HAL_USB_CONTROL_ASSERT_BUS_RESET 
 *                          \li #HAL_USB_CONTROL_ASSERT_RESUME 
 *                          \li #HAL_USB_CONTROL_DEASSERT_BUS_RESET 
 *                          \li #HAL_USB_CONTROL_DEASSERT_RESUME 
 *                          \li #HAL_USB_CONTROL_NO_OPERATION 
 *                          \li #HAL_USB_CONTROL_RESUME_SOF 
 *                          \li #HAL_USB_CONTROL_SUSPEND_SOF 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_bus_control( unsigned char control );

/**
 * The function opens a pipe between the host and the device endpoint. 
 * 
 * @param[in] pipe_init_params Pipe initialization parameters 
 * 
 * @param[out] pipe_handle  Pointer to the pipe handle 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_open_pipe( HAL_USB_PIPE_CONFIG *pipe_init_params, 
                            hal_usb_pipe_handle *pipe_handle );

/**
 * The function sends a Setup packet to a control pipe. 
 * 
 * @param[in] pipe_handle   Pipe handle 
 * 
 * @param[in] tr_params_ptr Transfer parameters 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */ 
int hal_usb_host_send_setup( hal_usb_pipe_handle pipe_handle,
                             HAL_USB_TRANSFER_PARAMS *tr_params_ptr );

/**
 * The function sends data on a pipe. (non-blocking) 
 * 
 * The function causes a block of data to be made available for transmission to 
 * the USB host controller. 
 * 
 * @param[in] pipe_handle   Pipe handle 
 * 
 * @param[in] tr_params_ptr Transfer parameters 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_send_data( hal_usb_pipe_handle pipe_handle,
                            HAL_USB_TRANSFER_PARAMS *tr_params_ptr );

/**
 * The function receives data on a pipe. (non-blocking) 
 * 
 * The function causes a buffer to be made available for data received from the 
 * USB host controller. 
 * 
 * @param[in] pipe_handle   Pipe handle 
 * 
 * @param[in] tr_params_ptr Transfer parameters 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_recv_data( hal_usb_pipe_handle pipe_handle,
                            HAL_USB_TRANSFER_PARAMS *tr_params_ptr );

/**
 * The function gets the status of a transfer on a pipe. 
 * 
 * @param[in] pipe_handle   Pipe handle 
 * 
 * @param[in] tr_number     Transfer number 
 * 
 * @param[out] tr_status_ptr Transfer status; one of 
 *                          \li #HAL_USB_TRANSFER_STATUS_IDLE
 *                          \li #HAL_USB_TRANSFER_STATUS_IN_PROGRESS
 *                          \li #HAL_USB_TRANSFER_STATUS_QUEUED
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_get_transfer_status( hal_usb_pipe_handle pipe_handle,
                                      unsigned int tr_number,
                                      int *tr_status_ptr );

/**
 * The function cancels the specified transfer on the pipe. (non-blocking) 
 * 
 * @param[in] pipe_handle   Pipe_handle 
 * 
 * @param[in] tr_number     Transfer number for this pipe 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_cancel_transfer( hal_usb_pipe_handle pipe_handle,
                                  unsigned int tr_number );

/**
 * The function closes the specified pipe functions and removes the pipe from 
 * the open pipe list. 
 * 
 * @param[in] pipe_handle   Pipe_handle 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_close_pipe( hal_usb_pipe_handle pipe_handle );

/**
 * The function closes all pipes and removes them from the open pipe list. 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int  hal_usb_host_close_all_pipes( void );

/**
 * The function unregisters a callback routine for a specified event. 
 * 
 * @param[in] type          The type of event; one of: 
 *                          \li #HAL_USB_HOST_EVENT_ATTACH 
 *                          \li #HAL_USB_HOST_EVENT_DETACH 
 *                          \li #HAL_USB_HOST_EVENT_RESUME 
 *                          \li #HAL_USB_HOST_EVENT_STALL 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_detach( unsigned char type );
   
/**
 * The function shuts down the USB Host controller. 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_host_shutdown( void );

/**
 * The function finds a specific pipe for the specified interface. 
 * 
 * @param[in] device_handle Device handle 
 * 
 * @param[in] intf_handle   Interface handle 
 * 
 * @param[in] pipe_type     Pipe type, one of: 
 *                              \li #HAL_USB_PIPE_ISOCHRONOUS 
 *                              \li #HAL_USB_PIPE_INTERRUPT 
 *                              \li #HAL_USB_PIPE_CONTROL 
 *                              \li #HAL_USB_PIPE_BULK 
 * 
 * @param[in] pipe_direction Pipe direction (ignored for control pipe); one 
 *                          of #HAL_USB_RECV or #HAL_USB_SEND.
 * 
 * @param[out] pipe_handle  Pipe handle (NULL if not found) 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int 
hal_usb_hostdev_find_pipe_handle( hal_usb_device_instance_handle device_handle,
                              hal_usb_interface_descriptor_handle intf_handle,
                              unsigned char pipe_type,
                              unsigned char pipe_direction, 
                              hal_usb_pipe_handle *pipe_handle );

/**
 * The function gets a buffer for the device operation. 
 * 
 * Applications should use this function to get buffers and other work areas 
 * that stay allocated until the device is detached. When the device is 
 * detached, these are all freed by the host system software. 
 * 
 * @param[in] device_handle Device handle 
 * 
 * @param[in] buffer_size   Buffer size to get 
 * 
 * @param[out] buffer_ptr   Pointer to the buffer, or NULL 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_hostdev_get_buffer( hal_usb_device_instance_handle device_handle,
                                unsigned int buffer_size, 
                                unsigned char **buffer_ptr );

/**
 * The function gets a descriptor. 
 * 
 * When the host detects a newly attached device, the host system software 
 * reads the device and configuration (which includes interface and endpoint 
 * descriptors) descriptors.\n 
 * The application can request these descriptors by calling this function 
 * instead of issuing a device framework function request to get the descriptor 
 * from the device. 
 * 
 * @param[in] device_handle Device handle 
 * 
 * @param[in] desc_type     Type of descriptor to get; one of: 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_DEVICE 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_CONFIG 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_STRING 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_INTERFACE 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_ENDPOINT 
 * 
 * @param[in] desc_index    Descriptor index, or 0 
 * 
 * @param[in] intf_alt      Interface alternate, or 0 
 * 
 * @param[out] descriptor   Handle of the descriptor, or NULL 
 *                          (See #HAL_USB_DEVICE_DESCRIPTOR, 
 *                          #HAL_USB_ENDPOINT_DESCRIPTOR,
 *                          #HAL_USB_CONFIGURATION_DESCRIPTOR, 
 *                          #HAL_USB_INTERFACE_DESCRIPTOR and 
 *                          #HAL_USB_STRING_DESCRIPTOR) 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int 
hal_usb_hostdev_get_descriptor( hal_usb_device_instance_handle device_handle,
                                hal_usb_descriptor_type desc_type,
                                unsigned char desc_index,
                                unsigned char intf_alt,
                                void **descriptor );

/**
 * The function selects the specified configuration for the device. 
 * 
 * The function tears down an old configuration, and set up a new configuration 
 * with the same or different index. 
 * 
 * @param[in] device_handle Device handle 
 * 
 * @param[in] config_number Configuration number 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int hal_usb_hostdev_select_config( hal_usb_device_instance_handle device_handle,
                                   unsigned char config_number );

/**
 * The function selects the specified configuration for the device. 
 * 
 * The function tears down old interface, and sets up a new one with the same 
 * or different index/alternate. For each interface, only one of its alternates 
 * can be selected per USB spec.  Also per spec, an endpoint can be in only one 
 * interface (though it may exist in several alternates of that interface). 
 * 
 * @param[in] device_handle Device handle 
 * 
 * @param[in] intf_handle   Interface to be selected 
 * 
 * @param[out] class_intf_ptr Initialized class-specific interface struct (see 
 *                          #HAL_USB_CLASS_CALL_STRUCT) 
 * 
 * @retval ERR_USB_NO       No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
int 
hal_usb_hostdev_select_interface( hal_usb_device_instance_handle device_handle,
                              hal_usb_interface_descriptor_handle intf_handle,
                              void *class_intf_ptr );



/**
 * The function get the current status of the specified recipient. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] type          Recipient of the command: 
 *                              \li #HAL_USB_HOST_CH9_DEVICE 
 *                              \li #HAL_USB_HOST_CH9_INTERFACE 
 *                              \li #HAL_USB_HOST_CH9_ENDPOINT 
 * 
 * @param[in] number        Interface or endpoint number (should be 0 if 
 *                          device request type) 
 * 
 * @param[out] status       Requested status: 
 *                              \li If device request, a combination of 
 *                              #HAL_USB_DEVICE_SELF_POWERED or 
 *                              #HAL_USB_DEVICE_REMOTE_WAKEUP 
 *                              \li If endpoint request, 
 *                              #HAL_USB_ENDPOINT_HALTED or 
 *                              #HAL_USB_ENDPOINT_STALLED 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int 
hal_usb_host_ch9_get_status( hal_usb_device_instance_handle device_handle,
                             unsigned char type,
                             unsigned char number,
                             unsigned char *status );

/**
 * The function clears a specific feature. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] type          Request type: 
 *                              \li #HAL_USB_HOST_CH9_DEVICE 
 *                              \li #HAL_USB_HOST_CH9_INTERFACE 
 *                              \li #HAL_USB_HOST_CH9_ENDPOINT 
 * 
 * @param[in] number        Interface or endpoint number (should be 0 if 
 *                          device request type) 
 * 
 * @param[in] feature       Feature selection: 
 *                              \li If device request, 
 *                              #HAL_USB_FEATURE_REMOTE_WAKEUP or 
 *                              #HAL_USB_FEATURE_TEST_MODE 
 *                              \li If endpoint request, 
 *                              #HAL_USB_FEATURE_ENDPOINT_HALT 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int 
hal_usb_host_ch9_clear_feature( hal_usb_device_instance_handle device_handle,
                                unsigned char type,
                                unsigned char number,
                                unsigned short feature);

/**
 * The function sets a specific feature. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] type          Request type: 
 *                              \li #HAL_USB_HOST_CH9_DEVICE 
 *                              \li #HAL_USB_HOST_CH9_INTERFACE 
 *                              \li #HAL_USB_HOST_CH9_ENDPOINT 
 * 
 * @param[in] number        Interface or endpoint number (should be 0 if 
 *                          device request type) 
 * 
 * @param[in] feature       Feature selection: 
 *                              \li If device request, 
 *                              #HAL_USB_FEATURE_REMOTE_WAKEUP or 
 *                              #HAL_USB_FEATURE_TEST_MODE 
 *                              \li If endpoint request, 
 *                              #HAL_USB_FEATURE_ENDPOINT_HALT 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int 
hal_usb_host_ch9_set_feature( hal_usb_device_instance_handle device_handle,
                              unsigned char type,
                              unsigned char number,
                              unsigned short feature);

/**
 * The function sets the device address for all future device accesses. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int 
hal_usb_host_ch9_set_address( hal_usb_device_instance_handle device_handle );

/**
 * The function gets a descriptor from a device. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] type          Descriptor type: 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_DEVICE 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_CONFIG 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_STRING 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_INTERFACE 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_ENDPOINT 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_OTG 
 * 
 * @param[in] language      Language ID or 0 
 * 
 * @param[in] length        Buffer length 
 * 
 * @param[out] buffer       Descriptor buffer 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int hal_usb_host_ch9_get_descriptor( hal_usb_device_instance_handle device_handle,
                                                unsigned short type,
                                                unsigned short language,
                                                unsigned short length,
                                                unsigned char *buffer );

/**
 * The function updates existing descriptor, or add new descriptors to a 
 * device. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] type          Descriptor type: 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_DEVICE 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_CONFIG 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_STRING 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_INTERFACE 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_ENDPOINT 
 *                              \li #HAL_USB_DESCRIPTOR_TYPE_OTG 
 * 
 * @param[in] language      Language ID or 0 
 * 
 * @param[in] length        Buffer length 
 * 
 * @param[out] buffer       Descriptor buffer 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int hal_usb_host_ch9_set_descriptor( hal_usb_device_instance_handle device_handle,
                                                unsigned short type,
                                                unsigned short language,
                                                unsigned short length,
                                                unsigned char *buffer );

/**
 * The function gets the current configuration value. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[out] buffer       Configuration value 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int hal_usb_host_ch9_get_configuration( 
                                hal_usb_device_instance_handle device_handle,
                                unsigned char *buffer );

/**
 * The function sets the current configuration value. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] config        Configuration value 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int hal_usb_host_ch9_set_configuration( 
                                hal_usb_device_instance_handle device_handle,
                                unsigned short config );

/**
 * The function gets the currently selected alternate setting for the specified 
 * interface. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] intf          Interface index 
 * 
 * @param[out] buffer       Alternate setting buffer 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int 
hal_usb_host_ch9_get_interface( hal_usb_device_instance_handle device_handle,
                                unsigned char intf,
                                unsigned char *buffer );

/**
 * The function selects an alternate setting for an interface. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] alternate     Alternate setting 
 * 
 * @param[in] intf          Interface index 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int 
hal_usb_host_ch9_set_interface( hal_usb_device_instance_handle device_handle,
                                unsigned char alternate,
                                unsigned char intf );

/**
 * The function sets and reports an endpoint's synchronization frame. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] interface     Interface 
 * 
 * @param[out] buffer       Synch frame buffer 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int 
hal_usb_host_ch9_synch_frame( hal_usb_device_instance_handle device_handle,
                              unsigned char interface,
                              unsigned char *buffer);

/**
 * The function registers a callback function for notification of standard 
 * device framework (chapter 9) command completion. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] callback      Callback upon completion. The transaction callback 
 *                          parameters are respectively: 
 *                              \li the pipe handle 
 *                              \li the parameter specified by higher level 
 *                              \li a pointer to buffer containing data (TX or 
 *                              RX) 
 *                              \li the length of data transferred 
 *                              \li the status 
 * 
 * @param[in] param         User provided callback parameter (parameter to pass 
 *                          back to the callback function) 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int hal_usb_host_register_ch9_callback(
                                hal_usb_device_instance_handle device_handle,
                                void(*callback)(void*,
                                                void*,
                                                unsigned char*,
                                                unsigned int,
                                                unsigned int),
                                void *param );

/**
 * The function issues a class or vendor specific control request. 
 *  
 * @param[in] device_handle Device handle 
 * 
 * @param[in] devreq        Device request to send 
 * 
 * @param[in] buff_ptr      Buffer to send/receive 
 * 
 * @param[in] callback      Callback upon completion 
 * 
 * @param[in] param         User provided callback parameter (parameter to pass 
 *                          back to the callback function) 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link HAL_USB_Error_Codes Error Codes \endlink 
 * 
 */
unsigned int hal_usb_hostdev_cntrl_request(
                                hal_usb_device_instance_handle device_handle,
                                HAL_USB_SETUP_PTR devreq,
                                unsigned char *buff_ptr,
                                void(*callback)(void*,
                                                void*,
                                                unsigned char*,
                                                unsigned int,
                                                unsigned int),
                                void *param );

#ifdef __cplusplus
}
#endif

/**  @} */

#endif  /* HAL_USIP_USB_H */
