/*============================================================================
 *
 *	ucl_des_ofb.h
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
#ifndef _UCL_DES_OFB_H_
#define _UCL_DES_OFB_H_

#include "ucl_des.h"

/** @file ucl_des_ofb.h
 * @defgroup UCL_DES_OFB DES OFB
 * Encrypt/Decrypt with DES in 64-bit OFB (Output Feedback) mode.
 * 
 * @par Header:
 * @link ucl_des_ofb.h ucl_des_ofb.h @endlink
 *
 * @ingroup UCL_OFB
 */


/*============================================================================*/
/** <b>DES-OFB</b>.
 * Complete Process.
 *
 * @pre	@li The byte length must be a multiple of 8.
 *		@li Input and Output Data have the same length.
 * 		@li The key length is 8 bytes.
 *
 * @param[out]	dataOut 		Pointer to the output data
 * @param[in]	dataIn			Pointer to the input data
 * @param[in]	key				Pointer to the DES Key
 * @param[in]	IV				Pointer to the initialization vector
 * @param[in]	data_byteLen	Data byte length
 * @param[in]	mode			The mode (Encryption/Decryption):
 *									@li #UCL_CIPHER_ENCRYPT
 *									@li #UCL_CIPHER_DECRYPT
 *
 * @return	Error code
 *
 * @retval	#UCL_OK				if no error occurred
 * @retval	#UCL_INVALID_INPUT	if one of the input is the pointer NULL
 * @retval	#UCL_INVALID_OUTPUT 	if one of the output is the pointer NULL
 * @retval	#UCL_INVALID_ARG		if @p data_byteLen is not a multiple of 8
 *
 *
 * @see UCL_DES
 *
 * @ingroup UCL_DES_OFB
 */
int ucl_des_ofb(u8 *dataOut, u8 *dataIn, u8 *key, u8 *IV,
	u32 data_byteLen, int mode);


/*============================================================================*/
/** <b>DES-OFB Init</b>.
 * Initialize DES OFB Context.
 *
 * @pre	The key length is 8 bytes.
 *
 * @param[out]	ctx		Pointer to the context
 * @param[in]	key		Pointer to the DES Key
 * @param[in]	IV		Pointer to the initialization vector
 * @param[in]	mode	The mode (Encryption/Decryption) :
 *							@li #UCL_CIPHER_ENCRYPT
 *							@li #UCL_CIPHER_DECRYPT
 *
 * @return	Error code
 *
 * @retval	#UCL_OK				if no error occurred
 * @retval	#UCL_INVALID_INPUT	if the input is the pointer #NULL
 * @retval	#UCL_INVALID_OUTPUT 	if the output is the pointer #NULL
 * @retval	#UCL_INVALID_MODE	if the mode is not one of those described
 *
 * @ingroup UCL_DES_OFB
 */
int ucl_des_ofb_init(ucl_des_ctx_t *ctx, u8 *key, u8 *IV,
	int mode);


/*============================================================================*/
/** <b>DES-OFB Core</b>.
 * Process the Data.
 *
 * @pre	@li The byte length must be a multiple of 8.
 *	@li Input and output data have the same length.
 *
 * @param[out]		dataOut			Pointer to the procesed data
 * @param[in,out]	ctx				Pointer to the context
 * @param[in]		dataIn			Pointer to the data
 * @param[in]		data_byteLen	Data byte length
 *
 * @return	Error code
 *
 * @retval	#UCL_OK				if no error occurred
 * @retval	#UCL_INVALID_INPUT	if one of the input is the pointer #NULL
 * @retval	#UCL_INVALID_OUTPUT 	if the output is the pointer #NULL
 * @retval	#UCL_INVALID_ARG		if the byte length is not a multiple of 8
 *
 * @ingroup UCL_DES_OFB
 */
int ucl_des_ofb_core(u8 *dataOut,ucl_des_ctx_t *ctx,
	u8 *dataIn, u32 data_byteLen);


/*============================================================================*/
/** <b>DES-OFB Finish</b>.
 * Zeroize the context.
 *
 * @param[out,in]	ctx		Pointer to the context
 *
 * @return	Error code
 *
 * @retval	#UCL_OK							if no error occurred
 * @retval	#UCL_INVALID_OUTPUT 	if the output is the pointer #NULL
 *
 * @ingroup UCL_DES_OFB
 */
int ucl_des_ofb_finish(ucl_des_ctx_t *ctx);


#endif /* _UCL_DES_OFB_H_ */
