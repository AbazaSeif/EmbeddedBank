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
 * Description: This file is the include file of at83c26_api.c.
 * 
 *==========================================================================*/
#ifndef _AT83C26_API_H_
#define _AT83C26_API_H_

//_____ I N C L U D E S ____________________________________________________
//_____ M A C R O S ________________________________________________________
//_____ D E F I N I T I O N S ______________________________________________
//_____ F U N C T I O N S __________________________________________________

int c26_check_int_signal();
int c26_it_sc1(unsigned char slave_adr);
int c26_it_sc2(unsigned char slave_adr);
int c26_it_sc3(unsigned char slave_adr);
int c26_it_sc4(unsigned char slave_adr);
int c26_it_sc5(unsigned char slave_adr);

int c26_general_init(unsigned char slave_adr);

/*1 full smart card and 4 SIM/SAM*/
int c26_config1_init(unsigned char slave_adr);

/*2 full smart card and 2 SIM/SAM*/
int c26_config2_init(unsigned char slave_adr);

/*1 full smart card, 1 smart card without CC4 and CC8 and 3 SIM/SAM*/
int c26_config3_init(unsigned char slave_adr);



/* DC/DC control function*/
int c26_dcdca_start(unsigned char slave_adr, unsigned char uc_voltage);
int c26_dcdcb_start(unsigned char slave_adr, unsigned char uc_voltage);

int c26_start_cvcc1(unsigned char slave_adr, unsigned char uc_voltage);
int c26_start_cvcc2(unsigned char slave_adr, unsigned char uc_voltage);
int c26_start_cvcc3(unsigned char slave_adr, unsigned char uc_voltage);
int c26_start_cvcc4(unsigned char slave_adr, unsigned char uc_voltage);
int c26_start_cvcc5(unsigned char slave_adr, unsigned char uc_voltage);

//! @}
#endif  // _AT83C26_API_H_
