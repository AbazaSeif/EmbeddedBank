/*============================================================================
 *
 *	ucl_dh.h [20-mar-06]
 * 
 *==========================================================================*/
/*============================================================================
 * 
 * Copyright (c) 2002-2006 Innova Card. All Rights Reserved. Do not disclose.
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
#ifndef _UCL_DH_H_
#define _UCL_DH_H_

/** @file ucl_dh.h
 * @defgroup UCL_DH Diffie-Hellman
 * Diffie-Hellman Key Exchange Protocol.
 * 
 * @par Header:
 * @link ucl_dh.h ucl_dh.h @endlink
 * 
 * Diffie-Hellman key agreement provided the first practical solution to the 
 * key distribution problem, allowing two parties, never having met in advance 
 * or shared keying material, to establish a shared secret by exchanging 
 * messages over an open channel. The security rests on the intractability of
 * the Diffie-Hellman problem and the related problem of computing discrete
 * logarithms. @n
 * @n
 * The basic version provides protection in the form of secrecy of the 
 * resulting key from passive adversaries, but not from active adversaries 
 * capable of intercepting, modifying, or injecting messages. Neither party 
 * has assurances of the source identity of the incoming message or the 
 * identity of the party which may know the resulting key, i.e., entity 
 * authentication or key authentication.@n
 * @n
 * The Diffie-Hellman protocol, and those based on it, can be carried out in 
 * any group in which both the discrete logarithm problem is hard and 
 * exponentiation is efficient. The most common examples of such groups used in 
 * practice are the multiplicative group @f$ Z_{p}^\star @f$ of @f$ Z_p @f$, the 
 * analogous multiplicative group of @f$ F_{2^m} @f$, and the group of points 
 * defined by an elliptic curve over a finite field.@n
 * In our case, we choose the group @f$ Z_p @f$ where @a p is a large prime.@n
 * 
 * @n
 * <b>Protocol</b>:@n
 * The goal: @a A and @a B want to share a secret key @a K.@n
 * @a A and @a B use the public elements @a p and @a g where @a p (the 
 * modulus) is a large prime and @a g (the base) is an element of @f$ Z_p @f$.
 * @n
 * @n
 * @li @a A and @a B generate each a secret element @f$ s_A,\ s_B \in Z_p @f$.
 * @li @a A calculate and send @f$ m_A = g^{s_A} \ mod\ p @f$ to @a B
 * @li @a B calculate and send @f$ m_B = g^{s_B} \ mod\ p @f$ to @a A
 * @li then @f$ K = m_A^{s_B} \ mod\ p = m_B^{s_A} \ mod\ p@f$
 * 
 * @ingroup UCL_PKC
 */


/** <b>DH Context</b>.
 * 
 * @ingroup UCL_DH
 */
typedef struct ucl_dh_ctx {
	/** The module */
	u8 *module;
	/** The base */
	u8 *base;
	/** The secret */
	u8 *secret;
	/** Module (base and secret) length */
	u32 len;
	/** The precalculation context */
	void *ctx;
} ucl_dh_ctx_t;


#define UCL_MOD_EXP_METHOD_MONTY	1
#define UCL_MOD_EXP_METHOD_FBEM		2

#define UCL_BUFFER_TO_SMALL -1
#define UCL_DATA_TO_SMALL	-2

/** <b>Save the Diffie-Hellman Context</b>.
 * 
 * @param[out]	data	Pointer to a the saved context
 * @param[in]	datalen	Data byte length
 * @param[in]	dh_ctx	Pointer to a Diffie-Hellman context
 * 
 * @return Error code
 * 
 * @ingroup UCL_DH
 */
int ucl_dh_save_ctx(u8 *data, u32 datalen, ucl_dh_ctx_t dh_ctx);


/** <b>Restore the Diffie-Hellman Context</b>.
 * 
 * @param[out]	dh_ctx	Pointer to a Diffie-Hellman context
 * @param[in]	data	Pointer to a saved context
 * @param[in]	datalen	Data byte length
 * 
 * @return Error code
 * 
 * @ingroup UCL_DH
 */
int ucl_dh_restore_ctx(ucl_dh_ctx_t *dh_ctx, u8 *data, u32 datalen, 
	u32 *buffer, u32 size);


/** <b>Diffie-Hellman Initialization</b>.
 * Init the context.
 * The Diffie-Hellman protocol needs some pre-computations.
 * 
 * 
 * @param[out]	dh_ctx	Pointer to a Diffie-Hellman context
 * @param[in]	modulus	The modulus @a p
 * @param[in]	mlen	Module byte length
 * @param[in]	base	The base @a g
 * @param[in]	blen	Base byte length
 * @param[in]	buffer	Pointer to a buffer
 * @param[in]	size	Buffer 32-bits words length
 * 
 * @return Error code
 * 
 * @ingroup UCL_DH
 */
int ucl_dh_init(ucl_dh_ctx_t *dh_ctx, u32 *buffer, u32 size, int option);


/** <b>Diffie-Hellman Secret Generation</b>.
 * Generate a secret.
 * 
 * @param[out]	dh_ctx	Pointer to a Diffie-Hellman context
 * 
 * @return Error code
 * 
 * @ingroup UCL_DH
 */
int ucl_dh_gen_secret(ucl_dh_ctx_t *dh_ctx);


/** <b>Diffie-Hellman Message Generation</b>.
 * Generate the message from the secret.
 * 
 * @f$ m = g^x @f$
 * 
 * @param[out]	m		The message
 * @param[in]	dh_ctx	Pointer to a Diffie-Hellman context
 * 
 * @return Error code
 * 
 * @ingroup UCL_DH
 */
int ucl_dh_gen_mess(u8 *m, ucl_dh_ctx_t *dh_ctx);


/** <b>Diffie-Hellman Shared-Key Generation</b>.
 * Generate the key from the second parts message and the secret.
 * 
 * @f$ key = m^y @f$
 * 
 * @param[out]	key		The shared key
 * @param[in]	keylen	The key length
 * @param[in]	m		The second part message
 * @param[in]	dh_ctx	Pointer to a Diffie-Hellman context
 * 
 * @return Error code
 * 
 * @ingroup UCL_DH
 */
int ucl_dh_gen_key(u8 *key, u32 keylen, u8 *m, ucl_dh_ctx_t *dh_ctx);


#endif /*UCL_DH_H_*/
