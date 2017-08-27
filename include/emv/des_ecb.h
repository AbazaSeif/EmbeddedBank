/*---------------------------------------------------------------------------+
| Author:    RSBON
| File:      DES_ECB.H
| Purpose:   DES_ECB(암호화 관련) header file
| Changes:
|
| Date:      Author  Comment:
| ---------  ------  --------
| 26-Feb-02  RSBON   Created.
+---------------------------------------------------------------------------*/

#ifndef _DES_ECB_H
#define _DES_ECB_H

#define DEAmoDecS	0x00
#define DEAmoEncS	0x01
#define DEAmoDecT	0x30
#define DEAmoEncT	0x31

#ifndef U08
    #define U08 unsigned char
#endif

void stringcpy(U08 destination[], U08 source[], int max);
void straight_permutation(U08 lookup[], U08 destination[], int max);
void invert_permutation(U08 lookup[], U08 destination[], int max);
void expansion_permutation(U08 lookup[], U08 source[], U08 destination[]);
void xor(U08 destination[], U08 source[], int max);
void confusion(U08 destination[], U08 source[], int num);
void permuted_choice(U08 lookup[], U08 destination[], U08 source[], int max);
void shift_left_regs(U08 c_reg[], U08 d_reg[], int num);
void shift_right_regs(U08 c_reg[], U08 d_reg[], int num);
void des(U08 plaintext[], U08 origin_key[], int mode);
/*
void out_digit(U08 bin[], int max, int column);
int bit_to_hex (char *buf, char *retbuf);
int bit_to_hox (char *buf, char *retbuf);
int hex_to_bit (char *retbuf, int len);
*/
#endif
