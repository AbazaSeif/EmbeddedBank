
/*======================================================================*/
/*																		*/
/*								KEYDEF.H								*/
/*																		*/
/*======================================================================*/

#ifndef KEYDEF_H
#define KEYDEF_H

#ifdef __cplusplus
extern "C" {
#endif


// Common key
#define BTKEY_0						0x00
#define BTKEY_1						0x01
#define BTKEY_2						0x02
#define BTKEY_3						0x03
#define BTKEY_4						0x04
#define BTKEY_5						0x05
#define BTKEY_6						0x06
#define BTKEY_7						0x07
#define BTKEY_8						0x08
#define BTKEY_9						0x09
#define BTKEY_ASTERISK				0x0A
#define BTKEY_SHARP					0x0B

#define BTKEY_CANCEL				0x12
#define BTKEY_CLEAR					0x11
#define BTKEY_ENTER					0x13

#define BTKEY_NULL					0xFF

// IC3100PE
#define BTKEY_UPARROW_IC3100PE		0x0C
#define BTKEY_REPRINT_IC3100PE		0x10
#define BTKEY_SFUNC_IC3100PE		0x14

#define BTKEY_F1_IC3100PE			0x0D
#define BTKEY_F2_IC3100PE			0x0E
#define BTKEY_F3_IC3100PE			0x0F

// IC3300P
#define BTKEY_F1_IC3300P			0x0D
#define BTKEY_F2_IC3300P			0x0E
#define BTKEY_F3_IC3300P			0x0F
#define BTKEY_F4_IC3300P			0x14

// IC5100P
#define BTKEY_SFUNC_IC5100P			0x0F
#define BTKEY_FCN_IC5100P			0x0C
#define BTKEY_UPARROW_IC5100P		0x0D

// IC6000P
#define BTKEY_A_IC6000P				0x14
#define BTKEY_B_IC6000P				0x10
#define BTKEY_C_IC6000P				0x0C
#define BTKEY_D_IC6000P				0x0D


#ifdef __cplusplus
}
#endif

#endif	/* KEYDEF_H */

/* */
