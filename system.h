
/*======================================================================*/
/*																		*/
/*								SYSTEM.H								*/
/*																		*/
/*======================================================================*/

#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif


//#define SDRAM_VERSION				// SDRAM only

#define MIPS_LITTLE

#define IC3100PE			0x3101	// IC3100PE only
#define IC3300P				0x3300	// IC3300P only
#define IC5100P				0x5100	// IC5100P only
#define IC6000P				0x6000	// IC6000P only
#define UNKNOWN_MODEL		0xFFFF	// unknown model

#define USER_DEBUG				// for user debug

//#define ERASE_DATA_ROM_OPTION		// for erase POS setup information & transaction log

//#define TEST_CARD					// for test card
//#define SAVE_TEST_TRXN_LOG		// for save test transaction log
//#define AUTO_MODEM_TEST			// for automatic modem test


#ifdef __cplusplus
}
#endif

#endif	/* SYSTEM_H */

/* */
