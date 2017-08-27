/*==========================================================================
 *
 *      at83c26_lib.h
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
 * Description: This file is the include file of at83c26_lib.c
 * 
 *==========================================================================*/

#ifndef _AT83C26_LIB_H_
#define _AT83C26_LIB_H_

//_____ I N C L U D E S ____________________________________________________

//_____ M A C R O S ________________________________________________________

//! @defgroup dfc_driver DFC driver
//! Low level driver that permit the use of the DFC macro of the product.
//! @{

// Data Flow management
//


//_____ D E F I N I T I O N S ______________________________________________

#define CVCC_0_VOLT 	0
#define CVCC_1_8_VOLT 	1
#define CVCC_3_VOLT		2
#define CVCC_5_VOLT		3
#define TWI_READ		1
#define TWI_WRITE		0

#define READ_CMD1_LENGTH 7// HAL 11
#define READ_CMD2_LENGTH 4
#define READ_CMD3_LENGTH 3
#define READ_CMD4_LENGTH 2
#define READ_CMD5_LENGTH 2
#define READ_CMD6_LENGTH 2
#define READ_CMD7_LENGTH 2
#define READ_CMD8_LENGTH 3



//_____ F U N C T I O N S __________________________________________________

// READ functions based on read commands
void delay_us_atmel( unsigned int micro );
int c26_read_cmd1_sc1_statusb(unsigned char slave_adr, unsigned char *info);
int c26_read_command(unsigned char slave_adr, unsigned char *info, unsigned char cmd, int nbbytes );
int c26_write_command(unsigned char slave_adr, unsigned char *info, unsigned char cmd, int nbbytes );
// READ functions based on registers
//! Read command number 1.
//
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 11 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, READ_CMD1_LENGTH)
//! Read command number 2.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd2(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_SC_DCDCB, READ_CMD2_LENGTH)
//! Read command number 3.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd3(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_SC2, READ_CMD3_LENGTH)
//! Read command number 4.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd4(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_SC3, READ_CMD4_LENGTH)
//! Read command number 5.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd5(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_SC4, READ_CMD5_LENGTH)
//! Read command number 6.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd6(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_SC5, READ_CMD6_LENGTH)
//! Read command number 7.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd7(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_DCDCB_CMD, READ_CMD7_LENGTH)
//! Read command number 8.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd8(_a_,_b_)								c26_read_command(_a_, _b_, C26_W_SLEW_CTRL, READ_CMD8_LENGTH)
//! Read command number 1, up to SC1_STATUS
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_status(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 1)
//! Read command number 1, up to SC2_STATUS
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_statusb(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC_DCDCB, 1)
//! Read command number 1, up to SC1_CFG0.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_cfg0(_a_,_b_)						c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 2)
//! Read command number 1, up to SC1_CFG1.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_cfg1(_a_,_b_)						c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 3)
//! Read command number 1, up to SC1_CFG2.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_cfg2(_a_,_b_)						c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 4)
//! Read command number 1, up to SC1_CFG3.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 5 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_cfg3(_a_,_b_)						c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 5)
//! Read command number 1, up to SC1_CFG4.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 6 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_cfg4(_a_,_b_)						c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 6)
//! Read command number 1, up to SC1_INTERFACE.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 7 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_sc1_interface(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 7)
//! Read command number 1, up to SC1_TIMER_MSB.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 8 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_timer_msb(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 8)
//! Read command number 1, up to SC1_TIMER_LSB.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 9 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_timer_lsb(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 9)
//! Read command number 1, up to CAPTURE_MSB.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 10 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_capture_msb(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 10)
//! Read command number 1, up to CAPTURE_LSB.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on buffer read buffer (buffer size = 11 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd1_capture_lsb(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_WRITE_TIMER, 11)
//! Read command number 2, up to STATUSB.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd2_statusb(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC_DCDCB, 1)
//! Read command number 2, up to IO_SELECT.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd2_io_select(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_SC_DCDCB, 2)
//! Read command number 2, up to INTERFACE_B.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd2_interface_b(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_SC_DCDCB, 3)
//! Read command number 2, up to ITDIS.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd2_itdis(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC_DCDCB, 4)
//! Read command number 3, up to SC2_CFG0.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd3_sc2_cfg0(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC2, 1)
//! Read command number 3, up to SC2_CFG1.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd3_sc2_cfg1(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC2, 2)
//! Read command number 3, up to SC2_CFG2.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd3_sc2_cfg2(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC2, 3)
//! Read command number 4, up to SC3_CFG0.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd4_sc3_cfg0(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC3, 1)
//! Read command number 4, up to SC3_CFG2.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd4_sc3_cfg2(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC3, 2)
//! Read command number 5, up to SC4_CFG0.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd5_sc4_cfg0(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC4, 1)
//! Read command number 5, up to SC4_CFG2.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd5_sc4_cfg2(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC4, 2)
//! Read command number 6, up to SC5_CFG0.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd6_sc5_cfg0(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC5, 1)
//! Read command number 6, up to SC5_CFG2.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd6_sc5_cfg2(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_SC5, 2)
//! Read command number 7, up to DCDCB.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd7_dcdcb(_a_,_b_)					c26_read_command(_a_, _b_, C26_W_DCDCB_CMD, 1)
//! Read command number 7, up to LDO.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd7_ldo(_a_,_b_)						c26_read_command(_a_, _b_, C26_W_DCDCB_CMD, 2)
//! Read command number 8, up to SLEW_CTRL_1.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd8_slew_ctrl_1(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_SLEW_CTRL, 1)
//! Read command number 8, up to SLEW_CTRL_2.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd8_slew_ctrl_2(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_SLEW_CTRL, 2)
//! Read command number 8, up to SLEW_CTRL_3.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on read buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the read command is  valid.
//!      FALSE if the read command is not valid.
//!
#define	c26_read_cmd8_slew_ctrl_3(_a_,_b_)				c26_read_command(_a_, _b_, C26_W_SLEW_CTRL, 3)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WRITE functions based on write commands
//! WRITE command number 1.
//!
//! @param Slave_adr = I2C address.
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd1(_a_)									{unsigned char info[1]; \
																c26_write_command(0, info, C26_W_GENERAL_CALL_RESET, 1)}
//! WRITE command number 2.
//!
//! @param Slave_adr = I2C address.
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd2(_a_)									{unsigned char info[1]; \
																c26_write_command(_a_, info, C26_W_RESET, 1)}
//! WRITE command number 3.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 5 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd3(_a_, _b_)							c26_write_command(_a_, _b_, _b_[0], 5)
//! WRITE command number 4.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd4(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_WRITE_TIMER, 3)
//! WRITE command number 5.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd5(_a_, _b_)							c26_write_command(_a_, _b_, _b_[0], 1)
//! WRITE command number 6.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd6(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_SC_DCDCB, 4)
//! WRITE command number 7.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd7(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_SC2, 4)
//! WRITE command number 8.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd8(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_SC3, 3)
//! WRITE command number 9.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd9(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_SC4, 3)
//! WRITE command number 10.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd10(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_SC5, 3)
//! WRITE command number 11.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd11(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_DCDCB_CMD, 3)
//! WRITE command number 12.
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd12(_a_, _b_)							c26_write_command(_a_, _b_, C26_W_SLEW_CTRL, 4)
//! Write command number 3 (only 1 byte).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
//!
#define	c26_write_cmd3_sc1_cfg0(_a_, _b_)							c26_write_command(_a_, _b_, _b_[0], 1)
//! Write command number 3 (only 2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
//!
#define	c26_write_cmd3_sc1_cfg1(_a_, _b_)							c26_write_command(_a_, _b_, _b_[0], 2)
//! Write command number 3 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
//!
#define	c26_write_cmd3_sc1_cfg2(_a_, _b_)							c26_write_command(_a_, _b_, _b_[0], 3)
//! Write command number 3 (4 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
//!
#define	c26_write_cmd3_sc1_cfg3(_a_, _b_)							(_b_[0] |= 0x80; \
																		_b_[0] &= (~0x40); \
																		c26_write_command(_a_, _b_, _b_[0], 4))
//! Write command number 3 (5 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 5 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
//!
#define	c26_write_cmd3_sc1_cfg4(_a_, _b_)							(_b_[0] |= 0x80; \
																		_b_[0] &= (~0x40); \
																		c26_write_command(_a_, _b_, _b_[0], 5))
//WRITE command number 4
//! WRITE command number 4  (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd4_timer_msb(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_WRITE_TIMER, 2)
//! WRITE command number 4  (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define c26_write_cmd4_timer_lsb(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_WRITE_TIMER, 3)
//WRITE command number 5
//! WRITE command number 5 (1 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 1 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd5_sc1_interface(_a_,_b_)				c26_write_command(_a_, _b_, _b_[0], 1)
//WRITE command number 6
//! WRITE command number 6 (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd6_io_select(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC_DCDCB, 2)
//! WRITE command number 6 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd6_interface_b(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC_DCDCB, 3)
//! WRITE command number 6 (4 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd6_itdis(_a_,_b_)						c26_write_command(_a_, _b_, C26_W_SC_DCDCB, 4)
//WRITE command number 7
//! WRITE command number 7 (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd7_sc2_cfg0(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC2, 2)
//! WRITE command number 7 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd7_sc2_cfg1(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC2, 3)
//! WRITE command number 7 (4 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd7_sc2_cfg2(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC2, 4)
//WRITE command number 8
//! WRITE command number 8 (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd8_sc3_cfg0(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC3, 2)
//! WRITE command number 8 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd8_sc3_cfg2(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC3, 3)
//WRITE command number 9
//WRITE command number 9

//! WRITE command number 9 (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd9_sc4_cfg0(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC4, 2)
//! WRITE command number 9 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd9_sc4_cfg2(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC4, 3)
//WRITE command number 10
//! WRITE command number 10 (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd10_sc5_cfg0(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC5, 2)
//! WRITE command number 10 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd10_sc5_cfg2(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_SC5, 3)
//WRITE command number 11
//WRITE command number 11

//! WRITE command number 11 (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd11_dcb_dcdcb(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_DCDCB_CMD, 3)
//! WRITE command number 11 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd11_dcb_ldo(_a_,_b_)					c26_write_command(_a_, _b_, C26_W_DCDCB_CMD, 3)
//WRITE command number 12
//WRITE command number 12

//! WRITE command number 12 (2 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 2 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd12_slctrl_slewctrl_1(_a_,_b_)			c26_write_command(_a_, _b_, C26_W_SLEW_CTRL, 2)
//! WRITE command number 12 (3 bytes).
//!
//! @param Slave_adr = I2C address.
//! @param *info  = pointer on write buffer (buffer size = 3 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd12_slctrl_slewctrl_2(_a_,_b_)			c26_write_command(_a_, _b_, C26_W_SLEW_CTRL, 3)
//! WRITE command number 12 (4 bytes).
//!
//! @param Slave_adr = I2C address
//! @param *info  = pointer on write buffer (buffer size = 4 bytes).
//!
//! @return a boolean:
//!      TRUE  if the write command is  valid.
//!      FALSE if the write command is not valid.
#define	c26_write_cmd12_slctrl_slewctrl_3(_a_,_b_)			c26_write_command(_a_, _b_, C26_W_SLEW_CTRL, 4)
//! @}
#endif  // _AT83C26_LIB_H_
