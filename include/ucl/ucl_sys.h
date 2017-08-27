/*============================================================================
 *
 *	ucl_sys.h
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
#ifndef _UCL_SYS_H_
#define _UCL_SYS_H_

/** @file ucl_sys.h
 * @defgroup UCL_SYSTEM UCL System
 * UCL System Functions.
 * 
 * @par Header:
 * @link ucl_sys.h ucl_sys.h @endlink
 *
 */

/*============================================================================*/
/** <b>Get UCL Version</b>.
 *	Get the USIP&reg; Cryptographic Library Version number.
 * The version format is "X.Y.Z build BUILDNUMBER", where:
 * @li @p X is the major version number.
 * @li @p Y is the minor version number.
 * @li @p Z is the correction version number.
 * @li @p BUILDNUMBER is the 8 hexadecimals form build number.
 * 
 * @note If @p Y is incremented that implies an API modification.
 *
 * @return	Pointer to the version description string
 *
 * @ingroup UCL_SYSTEM
 */
const char *ucl_get_version(void);


/*============================================================================*/
/** <b>Get UCL Build number</b>.
 *	Get the 40 hexadecimals form build number.
 *
 * @return	Pointer to the build number string
 *
 * @ingroup UCL_SYSTEM
 */
const char *ucl_get_build(void);


/*============================================================================*/
/** <b>UCL Init</b>.
 * USIP&reg; Cryptographic Library Initialisation.
 *
 * @warning This function must be processed before any use of the UCL.
 *
 * The initialization includes modules initialization and
 * integrity verification. @n
 * @n
 * <b>Integrity tests</b>. @n
 * @li RSA primitives
 * @li Ciphers primitives
 * @li Hash functions
 *
 * <b>Modules Initialization</b>.
 * @li UCL Stack, by default the UCL Stack is initialized with a buffer length
 * equal to #UCL_STACK_SIZE
 * @li USIP TRNG Interface
 * @li USIP AES Interface
 * 
 * @param[in]	buffer		Buffer for the UCL Stack
 * @param[in]	bufferlen	buffer 32-bits words length
 *
 * @return #UCL_OK or Error vector
 * 
 * The error vector is a combination (xor) of the folowing values:
 * @li 0x80000000	USIP TRNG Interface is disabled
 * @li 0x40000000	USIP AES Interface is disabled or compromised
 * 
 * @li 0x00000001	DES Error
 * @li 0x00000002	TDES Error
 * 
 * @li 0x00000020	SHA1 Error
 * @li 0x00000040	SHA256 Error
 * @li 0x00000040	HDES Error
 * 
 * @li 0x00001000	RSA Encryption Error
 * @li 0x00002000	RSA CRT Decryption Error
 * @li 0x00004000	RSA Decryption Error
 * 
 *
 * @ingroup UCL_SYSTEM
 */
int ucl_init(u32 *buffer, u32 bufferlen);


#endif /* _UCL_SYS_H_ */
