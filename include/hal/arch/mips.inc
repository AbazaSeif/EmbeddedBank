/*=============================================================================
 *
 *	mips.inc
 *
 *	MIPS assembler header file
 *
 *=============================================================================
 *
 * Purpose:	MIPS definitions.
 *
 * Description:	This file contains various definitions and macros that are
 *              useful for writing assembly code for the MIPS CPU family.
 *		
 *
 *============================================================================*/
#ifndef _HAL_MIPS_INC_
#define _HAL_MIPS_INC_

/*-----------------------------------------------------------------------------
 * Standard MIPS register names:
 */ 
 
#define zero	        $0
#define z0		$0
#define AT		$1
#define v0		$2
#define v1		$3
#define a0		$4
#define a1		$5
#define a2		$6
#define a3		$7
#define t0		$8
#define t1		$9
#define t2		$10
#define t3		$11
#define t4		$12
#define t5		$13
#define t6		$14
#define t7		$15
#define s0		$16
#define s1		$17
#define s2		$18
#define s3		$19
#define s4		$20
#define s5		$21
#define s6		$22
#define s7		$23
#define t8		$24
#define t9		$25
#define k0		$26	/* kernel private register 0 */
#define k1		$27	/* kernel private register 1 */
#define gp		$28	/* global data pointer */
#define sp 		$29	/* stack-pointer */
#define fp		$30	/* frame-pointer */
#define ra		$31	/* return address */
#define pc		$pc	/* program counter */



/* Coprocessor 0 registers */
#define	index		$0	/* TLB entry index register */
#define random		$1	/* TLB random index register */
#define	tlblo0		$2	/* TLB even page entry register */
#define	tlblo1		$3	/* TLB odd page entry register */
#define config		$3	/* Configuration register */
#define	context		$4	/* TLB context register */
#define pagemask	$5	/* TLB page size mask */
#define pagegrain	$5	/* TLB page grain */
#define	wired		$6	/* TLB wired boundary */
#define cachectrl	$7	/* Cache control */
#define badvr		$8	/* Bad virtual address */
#define count		$9	/* Timer cycle count register */
#define	tlbhi		$10	/* TLB virtual address match register */
#define compare		$11	/* Timer compare register */
#define status		$12	/* Status register	*/
#define cause		$13	/* Exception cause */  
#define	epc		    $14	/* Exception pc value */
#define prid		$15	/* processor ID */
#define ebase		$15	/* EBase */
#define config0		$16	/* Config register 0 */
#define lladdr      $17 /* LLAdddr */
#define watchlo		$18	/* WatchLo register */
#define watchhi		$19	/* WatchHi register	*/	
#define xcontext    $20 /* XContext register */
#define debug    	$23 /* Debug register */
#define errctl      $26 /* Software test enable of way-select */
#define cache_err   $27 /* Cache Error and Status */
#define taglo       $28 /* TagLo */
#define taghi       $29 /* TagHi */
#define error_epc   $30 /* Error exception pc value */

#define C0_INDEX	$0		/* TLB Index */
#define C0_RANDOM	$1		/* TLB Random */
#define C0_ENTRYLO0	$2		/* TLB EntryLo0 */
#define C0_ENTRYLO1	$3		/* TLB EntryLo1 */
#define C0_CONTEXT	$4		/* Context */
#define C0_PAGEMASK	$5		/* TLB PageMask */
#define C0_WIRED	$6		/* TLB Wired */
#define C0_BADVADDR	$8		/* Bad Virtual Address */
#define C0_COUNT 	$9		/* Count */
#define C0_ENTRYHI	$10		/* TLB EntryHi */
#define C0_COMPARE	$11		/* Compare */
#define C0_STATUS	$12		/* Processor Status */
#define C0_CAUSE	$13		/* Exception Cause */
#define C0_EPC		$14		/* Exception PC */
#define C0_PRID		$15		/* Processor Revision Indentifier */
#define C0_CONFIG	$16		/* Config */
#define C0_CONFIG1	$16		/* Config1 */
#define C0_LLADDR	$17		/* LLAddr */
#define C0_WATCHLO	$18		/* WatchpointLo */
#define C0_WATCHHI	$19		/* WatchpointHi */
#define C0_DEBUG        $23		/* EJTAG Debug Register */
#define C0_DEPC         $24		/* Program counter at last EJTAG debug exception */
#define C0_PERFCNT      $25		/* Performance counter interface */
#define C0_ERRCTL	$26		/* ECC */
#define C0_CACHEERR	$27		/* CacheErr */
#define C0_TAGLO	$28		/* TagLo */
#define C0_DATALO	$28		/* DataLo */
#define C0_TAGHI	$29		/* TagHi */
#define C0_DATAHI	$29		/* DataHi */
#define C0_ERROREPC	$30		/* ErrorEPC */
#define C0_DESAVE	$31		/* EJTAG dbg exc. save register */



/*----------------------------------------------------------------------------*/

#define FUNC_START(name)	\
		.type name,@function;	\
		.set push;          \
        .global name;		\
        .ent   name;		\
        .set noreorder ;    \
name:

#define FUNC_END(name)		\
        .set pop;           \
        .end name		    \

/*----------------------------------------------------------------------------*/
#endif /* _HAL_MIPS_INC_ */
