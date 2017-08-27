/*============================================================================
 *
 *      sc_at83c26.h
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
 * Description: Driver for the at83c26 smart card analog interface.
 * 
 *==========================================================================*/
#ifndef SC_AT83C26_H
#define SC_AT83C26_H

#define I2C_ADDR_AT83C26 0x42 /*A2 = 0, A1 = 0*/
//#define I2C_ADDR_AT83C26 0x46 /*A2 = 0, A1 = 1*/ 
//#define I2C_ADDR_AT83C26 0x4A /*A2 = 1, A1 = 0*/
//#define I2C_ADDR_AT83C26 0x4E /*A2 = 1, A1 = 1*/



#define START_DEVICE_SMARTCARD			1
#define SMARTCARD1						START_DEVICE_SMARTCARD + 0
#define SMARTCARD2						START_DEVICE_SMARTCARD + 1
#define SMARTCARD3						START_DEVICE_SMARTCARD + 2
#define SMARTCARD4						START_DEVICE_SMARTCARD + 3
#define SMARTCARD5						START_DEVICE_SMARTCARD + 4

#define AT83C26_SC1						1
#define AT83C26_SC2						2
#define AT83C26_SC3						3
#define AT83C26_SC4						4
#define AT83C26_SC5						5

#define ERR_C26_START					0x01000000							
#define ERR_C26_NO_DEVICE			    1+ ERR_C26_START
#define ERR_C26_POWER			    	2+ ERR_C26_START

#define AT83C26_IOCTL_RESET             0
#define AT83C26_IOCTL_POWER_UP          1
#define AT83C26_IOCTL_POWER_DOWN        2
#define AT83C26_IOCTL_SELECT            3
#define AT83C26_IOCTL_UNSELECT          4

#define AT83C26_IOCTL_SET_A0            5             
#define AT83C26_IOCTL_SET_A1            6            
#define AT83C26_IOCTL_SET_PGM           7           
#define AT83C26_IOCTL_SET_STATUS        8       
#define AT83C26_IOCTL_SET_IT            9           
#define AT83C26_IOCTL_SET_PRWON         10     
#define AT83C26_IOCTL_SET_CHIPSELECT    11

#define AT83C26_IOCTL_GET_A0            12         
#define AT83C26_IOCTL_GET_A1            13       
#define AT83C26_IOCTL_GET_PGM           14    
#define AT83C26_IOCTL_GET_STATUS        15
#define AT83C26_IOCTL_GET_IT            16    
#define AT83C26_IOCTL_GET_PRWON         17
#define AT83C26_IOCTL_GET_CHIPSELECT    18


extern HAL_SCS_DRIVER_IO const at83c26_io;

#endif  /* SC_AT83C26_H */

