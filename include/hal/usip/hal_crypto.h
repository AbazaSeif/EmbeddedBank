/*============================================================================
 *
 *      hal_crypto.h
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
 * Description: This file contains the AES Cryptographic Interface 
 *              generic functions.
 * 
 *==========================================================================*/
#ifndef HAL_USIP_CRYPTO_H
#define HAL_USIP_CRYPTO_H

/**
 * @defgroup HAL_CRYPTO HAL Cryptographic Interface
 * This chapter contains descriptions of the functions available to access 
 * the AES hardware accelerator Interface. 
 * 
 * @section HAL_CRYPTO_OVERVIEW Overview 
 * 
 * USIP® Professional provides a AES hardware accelerator Interface that may be 
 * used for AES-128 encryption and decryption of application data. 
 * 
 * @addtogroup HAL_CRYPTO
 * 
 * @{
 */
 

/*----------------------------------------------------------------------------
 *   Functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
 
#ifdef CONFIG_LIBROM_NOT_INLINED

/**
 * The function resets, activates and configures an AES 128-bit key accelerator. 
 * 
 * @warning The cryptographic interface shares its clock and hardware reset 
 * with the UMC. It is not actually reset nor activated if any external memory 
 * bank is already in use. 
 * 
 * @param[in] key           Pointer allocated and filled by the caller with the 
 *                          128-bit AES key. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */
int hal_crypto_init( void *key );

/**
 * The function disables the Cryptographic Interface and erases the previous 
 * key. 
 * 
 * @warning The cryptographic interface shares its clock and hardware reset 
 * with the UMC. It is not actually disabled if any external memory bank is 
 * still in use. 
 * 
 * @retval -ERR_NO          No error 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_crypto_shutdown( void );

/**
 * The function configures an AES 128-bit key. 
 * 
 * @param[in] key           Pointer allocated and filled by the caller with the 
 *                          128-bit AES key. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_crypto_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 *
 */
int hal_crypto_set_key( void *key );

/**
 * The function decrypts an AES enciphered message. 
 *  
 * @param[in]  ciphertext   A pointer to the 128 bit ciphered text. 
 * @param[out] plaintext    A pointer to the 128 bit plain text. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_crypto_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_crypto_decrypt( void *ciphertext, void *plaintext );

/**
 * The function encrypts a message with the AES algorithm. 
 * 
 * @param[in]  plaintext    A pointer to the 128 bit plain text. 
 * @param[out] ciphertext   A pointer to the 128 bit ciphered text. 
 * 
 * @retval -ERR_NO          No error 
 * @retval -ERR_NXIO        Device not configured. Use hal_crypto_init() first. 
 * @retval -ERR_INVAL       Invalid parameter 
 * @retval Other            See \link Error_Codes Error Codes \endlink 
 * 
 */
int hal_crypto_encrypt( void *plaintext, void *ciphertext );

#else

#include <hal/usip/hal_sys.h>

__hal_defunc1(hal_crypto_init, void *, key);
__hal_defunc0(hal_crypto_shutdown, void);
__hal_defunc1(hal_crypto_set_key, void *, key);
__hal_defunc2(hal_crypto_decrypt, void *, ciphertext, void *, plaintext);
__hal_defunc2(hal_crypto_encrypt, void *, plaintext, void *, ciphertext);
                
#endif /* CONFIG_LIBROM_NOT_INLINED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* HAL_USIP_CRYPTO_H */

