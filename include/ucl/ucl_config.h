/*============================================================================
 *
 *	ucl_config.h
 *
 *==========================================================================*/
/*============================================================================
 *
 * Copyright (c) 2002-2006 Innova Card.
 * All Rights Reserved. Do not disclose.
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
 * Purpose :
 *
 *==========================================================================*/
#ifndef _UCL_CONFIG_H_
#define _UCL_CONFIG_H_


/** <b>UCL Version String</b>.
 * Version 1.2.0
 * @ingroup UCL_CONFIG */
#define UCL_VERSION_STRING "1.2.0"

/** <b>UCL Stack default size</b>.
 * 8 Ko.
 * @ingroup UCL_CONFIG */
#define UCL_STACK_SIZE 1024
/** <b>UCL RSA key max size</b>.
 * 512 bytes: 4096 bits.
 * @ingroup UCL_CONFIG 
 */
#define UCL_RSA_KEY_MAXSIZE 512
/** <b>UCL RSA public exponent max size</b>.
 * 4 bytes: 32 bits.
 * @ingroup UCL_CONFIG */
#define UCL_RSA_PUBLIC_EXPONENT_MAXSIZE	4


#define UCL_API_VERSION_MAJOR	1
#define UCL_API_VERSION_MINOR	2
#define UCL_LIB_VERSION_MINOR	0
#define UCL_LIB_OPTIONS			0


#endif /*_UCL_CONFIG_H_*/
