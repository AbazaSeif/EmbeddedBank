
/*------------------------------------------------------------------------------
Author		: K.H LEE Bitel Co., Ltd.
File name	: COUNTRY.H
Purpose		: Country code of high speed modem

Revision history
Revision No.	Date				Contents
R1.00			21/May/2005 		First revison
------------------------------------------------------------------------------*/

#ifndef COUNTRY_H
#define COUNTRY_H

#ifdef __cplusplus
extern "C" {
#endif


#define CC_Argentina				0x07
#define CC_Australia				0x09
#define CC_Austria					0x0A
#define CC_Belgium					0x0F
#define CC_Brazil					0x16
#define CC_Bulgaria					0x1B
#define CC_Canada					0x20
#define CC_Chile					0x25
#define CC_China					0x26
#define CC_Colombia					0x27
#define CC_Croatia					0xFA
#define CC_Cyprus					0x2D
#define CC_CzechRepublic			0x2E
#define CC_Denmark					0x31
#define CC_Egypt					0x36
#define CC_Estonia					0xF9
#define CC_Finland					0x3C
#define CC_France					0x3D
#define CC_Germany					0x42
#define CC_Greece					0x46
#define CC_HongKong					0x50
#define CC_Hungary					0x51
#define CC_Iceland					0x52
#define CC_India					0x53
#define CC_Indonesia				0x54
#define CC_Ireland					0x57
#define CC_Israel					0x58
#define CC_Italy					0x59
#define CC_Japan					0x00
#define CC_Korea					0x61
#define CC_Kuwait					0x62
#define CC_Lebanon					0x64
#define CC_Luxembourg				0x69
#define CC_Malaysia					0x6C
#define CC_Mexico					0x73
#define CC_Morocco					0x77
#define CC_Netherlands				0x7B
#define CC_NewZealand				0x7E
#define CC_Norway					0x82
#define CC_Pakistan					0x84
#define CC_Philippines				0x89
#define CC_Poland					0x8A
#define CC_Portugal					0x8B
#define CC_Romania					0x8E
#define CC_Russia					0xB8
#define CC_SaudiArabia				0x98
#define CC_Senegal					0x99
#define CC_Singapore				0x9C
#define CC_Slovakia					0xFB
#define CC_Slovenia					0xFC
#define CC_SouthAfrica				0x9F
#define CC_Spain					0xA0
#define CC_SriLanka					0xA1
#define CC_Sweden					0xA5
#define CC_Switzerland				0xA6
#define CC_Taiwan					0xFE
#define CC_Thailand					0xA9
#define CC_Tunisia					0xAD
#define CC_Turkey					0xAE
#define CC_UK						0xB4
#define CC_UnitedArabEmirates		0xB3
#define CC_Uruguay					0xB7
#define CC_USA						0xB5	/* default */
#define CC_Reserved					0xFD
#define CC_EOT						0xFF


extern const unsigned char MODEM_COUNTRY_CODE[];


#ifdef __cplusplus
}
#endif

#endif	/* COUNTRY_H */

/* */
