/*==========================================================================
 *
 *      at83c26.h
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
/*===========================================================================
 * 
 * Author(s):    Herve Abel (ABC independants) 
 * Contributors:  Yann Gaude
 * Date:          
 * Purpose:        
 * Description: This file contains the AT83C26 registers description.
 * 
 *==========================================================================*/
#ifndef _AT83C26_H_
#define _AT83C26_H_

//_____ I N C L U D E S ____________________________________________________

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//******************** READ COMMANDS: the number indicates the position of the byte in the buffer

// READ COMMAND after reset or number 2, 3, 4 write command
#define C26_R_SC1_STATUS		0
#define C26_R_SC1_CFG0			1
#define C26_R_SC1_CFG1			2
#define C26_R_SC1_CFG2			3
#define C26_R_SC1_CFG3			4
#define C26_R_SC1_CFG4			5
#define C26_R_SC1_INTERFACE		6
#define C26_R_TIMER_MSB			7
#define C26_R_TIMER_LSB			8
#define C26_R_CAPTURE_MSB		9
#define C26_R_CAPTURE_LSB		10

// READ COMMAND after number 6 write command
#define C26_R_STATUSB		0
#define C26_R_IO_SELECT		1
#define C26_R_INTERFACE_B	2
#define C26_R_ITDIS			3

// READ COMMAND after number 7 write command
#define C26_R_SC2_CFG0		0
#define C26_R_SC2_CFG1		1
#define C26_R_SC2_CFG2		2

// READ COMMAND after number 8 write command
#define C26_R_SC3_CFG0		0
#define C26_R_SC3_CFG2		1

// READ COMMAND after number 9 write command
#define C26_R_SC4_CFG0		0
#define C26_R_SC4_CFG2		1

// READ COMMAND after number 10 write command
#define C26_R_SC5_CFG0		0
#define C26_R_SC5_CFG2		1

// READ COMMAND after number 11 write command
#define C26_R_DCDCB		0
#define C26_R_LDO		1

// READ COMMAND after number 12 write command
#define C26_R_SLEW_CTRL_1		0
#define C26_R_SLEW_CTRL_2		1
#define C26_R_SLEW_CTRL_3		2

//******************** WRITE COMMANDS
//******************** the hexa number is the command number
//******************** the number indicates the position of the byte in the buffer

// WRITE COMMAND number 1
#define C26_W_GENERAL_CALL_RESET	0x06

// WRITE COMMAND number 2
#define C26_W_RESET	0xFF

// WRITE COMMAND number 3
#define C26_W_SC1_CFG0		0
#define C26_W_SC1_CFG1		1
#define C26_W_SC1_CFG2		2
#define C26_W_SC1_CFG3		3
#define C26_W_SC1_CFG4		4

// WRITE COMMAND number 4
#define C26_W_WRITE_TIMER	0xFC

#define C26_W_TIMER_MSB		1
#define C26_W_TIMER_LSB		2

// WRITE COMMAND number 5
#define C26_W_SC1_INTERFACE		0

// WRITE COMMAND number 6
#define C26_W_SC_DCDCB		0xF8

#define C26_W_IO_SELECT		1
#define C26_W_INTERFACE_B	2
#define C26_W_ITDIS			3

// WRITE COMMAND number 7
#define C26_W_SC2		0xF9

#define C26_W_SC2_CFG0		1
#define C26_W_SC2_CFG1		2
#define C26_W_SC2_CFG2		3

// WRITE COMMAND number 8
#define C26_W_SC3		0xFA

#define C26_W_SC3_CFG0		1
#define C26_W_SC3_CFG2		2

// WRITE COMMAND number 9
#define C26_W_SC4		0xFB

#define C26_W_SC4_CFG0		1
#define C26_W_SC4_CFG2		2

// WRITE COMMAND number 10
#define C26_W_SC5		0xFD

#define C26_W_SC5_CFG0		1
#define C26_W_SC5_CFG2		2

// WRITE COMMAND number 11
#define C26_W_DCDCB_CMD		0xFE

#define C26_W_DCDCB		1
#define C26_W_LD0		2

// WRITE COMMAND number 12
#define C26_W_SLEW_CTRL		0xF7

#define C26_W_SLEW_CTRL_1	1
#define C26_W_SLEW_CTRL_2	2
#define C26_W_SLEW_CTRL_3	3

//******************** REGISTERS MASKS

// SC1_CFG0 register
#define MSK_SC1_CFG0_RFU10XXXXXX	0x80
#define MSK_SC1_CFG0_ATRERR1		0x20
#define MSK_SC1_CFG0_INSERT1		0x10
#define MSK_SC1_CFG0_ICARDERR1		0x08
#define MSK_SC1_CFG0_VCARDERR1		0x04
#define MSK_SC1_CFG0_VCARD11		0x02
#define MSK_SC1_CFG0_VCARD10		0x01

// SC1_CFG1 register

#define MSK_SC1_CFG1_ART1		0x40
#define MSK_SC1_CFG1_SHUTDOWNA	0x20
#define MSK_SC1_CFG1_CARDDET1	0x10
#define MSK_SC1_CFG1_PULLUP1	0x08
#define MSK_SC1_CFG1_CDS12		0x04
#define MSK_SC1_CFG1_CDS11		0x02
#define MSK_SC1_CFG1_CDS10		0x01

// SC1_CFG2 register

#define MSK_SC1_CFG2_CLK_DCDCA	0x80
#define MSK_SC1_CFG2_DCK2		0x40
#define MSK_SC1_CFG2_DCK1		0x20
#define MSK_SC1_CFG2_DCK0		0x10

#define MSK_SC1_CFG2_CKS12		0x04
#define MSK_SC1_CFG2_CKS11		0x02
#define MSK_SC1_CFG2_CKS10		0x01

// SC1_CFG3 register

#define MSK_SC1_CFG3_ICCADJA	0x10

// SC1_CFG4 register

#define MSK_SC1_CFG4_DEMBOOSTA1	0x40
#define MSK_SC1_CFG4_DEMBOOSTA0	0x20
#define MSK_SC1_CFG4_STEPREGA	0x10
#define MSK_SC1_CFG4_INT_PULLUP	0x80

// SC1_INTERFACE register

#define MSK_SC1_INTERFACE_IODIS1	0x40
#define MSK_SC1_INTERFACE_CKSTOP1	0x20
#define MSK_SC1_INTERFACE_CARDRST1	0x10
#define MSK_SC1_INTERFACE_CARDC81	0x08
#define MSK_SC1_INTERFACE_CARDC41	0x04
#define MSK_SC1_INTERFACE_CARDCK1	0x02
#define MSK_SC1_INTERFACE_CARDIO1	0x01

// SC1_STATUS register

#define MSK_SC1_STATUS_CC81			0x80
#define MSK_SC1_STATUS_CC41			0x40
#define MSK_SC1_STATUS_CARDIN1		0x20
#define MSK_SC1_STATUS_VCARD_OK1	0x10

#define MSK_SC1_STATUS_VCARD_INT1	0x04
#define MSK_SC1_STATUS_CRST1		0x02
#define MSK_SC1_STATUS_CIO1			0x01

// SC2_CFG0 register

#define MSK_SC2_CFG0_VCARD_INT2		0x80
#define MSK_SC2_CFG0_VCARD_OK2		0x40
#define MSK_SC2_CFG0_ATRERR2		0x20
#define MSK_SC2_CFG0_INSERT2		0x10
#define MSK_SC2_CFG0_ICARDERR2		0x08
#define MSK_SC2_CFG0_VCARDERR2		0x04
#define MSK_SC2_CFG0_VCARD21		0x02
#define MSK_SC2_CFG0_VCARD20		0x01

// SC2_CFG1 register

#define MSK_SC2_CFG1_SC2_FULL	0x20
#define MSK_SC2_CFG1_CARDDET2	0x10
#define MSK_SC2_CFG1_PULLUP2	0x08
#define MSK_SC2_CFG1_CDS22		0x04
#define MSK_SC2_CFG1_CDS21		0x02
#define MSK_SC2_CFG1_CDS20		0x01

// SC2_CFG2 register

#define MSK_SC2_CFG2_ART2	0x80

#define MSK_SC2_CFG2_CARDRST2	0x20
#define MSK_SC2_CFG2_CARDCK2	0x10
#define MSK_SC2_CFG2_CKSTOP2	0x08
#define MSK_SC2_CFG2_CKS22		0x04
#define MSK_SC2_CFG2_CKS21		0x02
#define MSK_SC2_CFG2_CKS20		0x01

// SC3_CFG0 register

#define MSK_SC3_CFG0_VCARD_INT3		0x80
#define MSK_SC3_CFG0_VCARD_OK3		0x40
#define MSK_SC3_CFG0_ATRERR3		0x20

#define MSK_SC3_CFG0_ICARDERR3		0x08
#define MSK_SC3_CFG0_VCARDERR3		0x04
#define MSK_SC3_CFG0_VCARD31		0x02
#define MSK_SC3_CFG0_VCARD30		0x01

// SC3_CFG2 register

#define MSK_SC3_CFG2_ART3	0x80

#define MSK_SC3_CFG2_CARDRST3	0x20
#define MSK_SC3_CFG2_CARDCK3	0x10
#define MSK_SC3_CFG2_CKSTOP3	0x08
#define MSK_SC3_CFG2_CKS32		0x04
#define MSK_SC3_CFG2_CKS31		0x02
#define MSK_SC3_CFG2_CKS30		0x01

// SC4_CFG0 register

#define MSK_SC4_CFG0_VCARD_INT4		0x80
#define MSK_SC4_CFG0_VCARD_OK4		0x40
#define MSK_SC4_CFG0_ATRERR4		0x20

#define MSK_SC4_CFG0_ICARDERR4		0x08
#define MSK_SC4_CFG0_VCARDERR4		0x04
#define MSK_SC4_CFG0_VCARD41		0x02
#define MSK_SC4_CFG0_VCARD40		0x01

// SC4_CFG2 register

#define MSK_SC4_CFG2_ART4	0x80

#define MSK_SC4_CFG2_CARDRST4	0x20
#define MSK_SC4_CFG2_CARDCK4	0x10
#define MSK_SC4_CFG2_CKSTOP4	0x08
#define MSK_SC4_CFG2_CKS42		0x04
#define MSK_SC4_CFG2_CKS41		0x02
#define MSK_SC4_CFG2_CKS40		0x01

// SC5_CFG0 register

#define MSK_SC5_CFG0_VCARD_INT5		0x80
#define MSK_SC5_CFG0_VCARD_OK5		0x40
#define MSK_SC5_CFG0_ATRERR5		0x20

#define MSK_SC5_CFG0_ICARDERR5		0x08
#define MSK_SC5_CFG0_VCARDERR5		0x04
#define MSK_SC5_CFG0_VCARD51		0x02
#define MSK_SC5_CFG0_VCARD50		0x01

// SC5_CFG2 register

#define MSK_SC5_CFG2_ART5	0x80

#define MSK_SC5_CFG2_CARDRST5	0x20
#define MSK_SC5_CFG2_CARDCK5	0x10
#define MSK_SC5_CFG2_CKSTOP5	0x08
#define MSK_SC5_CFG2_CKS52		0x04
#define MSK_SC5_CFG2_CKS51		0x02
#define MSK_SC5_CFG2_CKS50		0x01

// IO_SELECT register
#define MSK_IO_SELECT_IOSEL5	0x04
#define MSK_IO_SELECT_IOSEL4	0x03
#define MSK_IO_SELECT_IOSEL3	0x02
#define MSK_IO_SELECT_IOSEL2	0x01
#define MSK_IO_SELECT_IOSEL1	0x00

#define MSK_IO_SELECT_IOSEL_DEFAULT		MSK_IO_SELECT_IOSEL1

// INTERFACEB register

#define MSK_INTERFACEB_CARDC82		0x40
#define MSK_INTERFACEB_CARDIO5		0x20
#define MSK_INTERFACEB_CARDIO4		0x10
#define MSK_INTERFACEB_CARDIO3_CARDC42		0x08
#define MSK_INTERFACEB_CARDIO2		0x04
#define MSK_INTERFACEB_DEMBOOSTB1	0x02
#define MSK_INTERFACEB_DEMBOOSTB0	0x01

// STATUSB register

#define MSK_STATUSB_CARDIN2		0x40
#define MSK_STATUSB_CIO5		0x20
#define MSK_STATUSB_CIO4		0x10
#define MSK_STATUSB_CRST3_CC82	0x08
#define MSK_STATUSB_CIO3_CC42	0x04
#define MSK_STATUSB_CRST2		0x02
#define MSK_STATUSB_CIO2		0x01

// ITDIS register

#define MSK_ITDIS_IODIS5		0x80
#define MSK_ITDIS_IODIS4		0x40
#define MSK_ITDIS_IODIS3		0x20
#define MSK_ITDIS_IODIS2		0x10
#define MSK_ITDIS_ITDIS5		0x08
#define MSK_ITDIS_ITDIS4		0x04
#define MSK_ITDIS_ITDIS3		0x02
#define MSK_ITDIS_ITDIS2		0x01

#define MSK_ITDIS_MASK_ALL		0xff

// DCDCB register

#define MSK_DCDCB_SHUTDOWNB		0x80
#define MSK_DCDCB_VDCB_INT		0x40
#define MSK_DCDCB_VDCB_OK		0x20
#define MSK_DCDCB_CLK_DCDCB		0x10
#define MSK_DCDCB_ICCADJB		0x08
#define MSK_DCDCB_STEPREGB		0x04
#define MSK_DCDCB_VDCB1			0x02
#define MSK_DCDCB_VDCB0			0x01

// LDO register

#define MSK_LDO_IPLUS5		0x80
#define MSK_LDO_IPLUS4		0x40
#define MSK_LDO_IPLUS3		0x20
#define MSK_LDO_IPLUS2		0x10
#define MSK_LDO_IERR_DIS5	0x08
#define MSK_LDO_IERR_DIS4	0x04
#define MSK_LDO_IERR_DIS3	0x02
#define MSK_LDO_IERR_DIS2	0x01

// SLEW_CTRL_1 register

#define MSK_SLCTRL1_CCLK2_CTRL1		0x80
#define MSK_SLCTRL1_CCLK2_CTRL0		0x40
#define MSK_SLCTRL1_CIO2_CTRL1		0x20
#define MSK_SLCTRL1_CIO2_CTRL0		0x10
#define MSK_SLCTRL1_CCLK1_CTRL1		0x08
#define MSK_SLCTRL1_CCLK1_CTRL0		0x04
#define MSK_SLCTRL1_CIO1_CTRL1		0x02
#define MSK_SLCTRL1_CIO1_CTRL0		0x01

// SLEW_CTRL_2 register

#define MSK_SLCTRL2_CCLK4_CTRL1		0x80
#define MSK_SLCTRL2_CCLK4_CTRL0		0x40
#define MSK_SLCTRL2_CIO4_CTRL1		0x20
#define MSK_SLCTRL2_CIO4_CTRL0		0x10
#define MSK_SLCTRL2_CCLK3_CTRL1		0x08
#define MSK_SLCTRL2_CCLK3_CTRL0		0x04
#define MSK_SLCTRL2_CIO3_CTRL1		0x02
#define MSK_SLCTRL2_CIO3_CTRL0		0x01

// SLEW_CTRL_3 register

#define MSK_SLCTRL3_CCLK5_CTRL1		0x08
#define MSK_SLCTRL3_CCLK5_CTRL0		0x04
#define MSK_SLCTRL3_CIO5_CTRL1		0x02
#define MSK_SLCTRL3_CIO5_CTRL0		0x01

//_____ F U N C T I O N S __________________________________________________

/*  */
#define	K_NO_DEVICE_SELECTED		0xff

//! @}
#endif  // _AT83C26_H_
