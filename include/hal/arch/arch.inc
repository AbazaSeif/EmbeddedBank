/*=============================================================================
 *
 *	arch.inc
 *
 *	MIPS assembler header file
 *
 * Purpose:	Architecture definitions.
 *
 * Description:	This file contains various definitions and macros that are
 *              useful for writing assembly code for the MIPS CPU family.
 *		
 *
 *============================================================================*/
#ifndef __HAL_ARCH_INC__
#define __HAL_ARCH_INC__

	
/*-----------------------------------------------------------------------------	
 * Set up the value for the initial status register
 */
#ifndef HAL_INTC_MASK_DATA
#define HAL_INTC_MASK_DATA
#endif /* HAL_INTC_MASK_DATA */

#define INITIAL_SR_VAR 0x00000000

#define INITIAL_SR_PLF 0x00000000

/* Disable Coprocessor Usable bits, Turn off Reduce Power bit, 
 * Turn off reverse endian , Turn on BEV (not use in normal exception vectors), 
 * Clear TS, SR, NMI bits, Set Interrupt masks, Clear User Mode UM = 0, 
 * Clear ERL  ERL = 0, Clear EXL  EXL = 0, Set Interrupt Enable 
 */
#ifdef CONFIG_STARTUP_TYPE
#if (CONFIG_STARTUP_TYPE == CONFIG_STARTUP_MEMORY_ROM)
# define INITIAL_SR_ARCH 	0x0040ff03 
#else
# define INITIAL_SR_ARCH 	0x0000ff01 
# define HAL_INTC_MASK_DATA
#endif
#endif

#ifndef INITIAL_SR_ARCH
# define INITIAL_SR_ARCH 	0x0000ff01 
# define HAL_INTC_MASK_DATA
#endif
				
#define INITIAL_SR 	(INITIAL_SR_ARCH|INITIAL_SR_VAR|INITIAL_SR_PLF)

#define HAL_INITIAL_CONFIG0_K0_CACHING

/*-----------------------------------------------------------------------------
 * Setup the initial value for the config0 register
 */
#ifdef HAL_INITIAL_CONFIG0_K0_CACHING
# define INITIAL_CONFIG0	0x00000003 /* Set KSeg0 to cacheable */ 
#else
# define INITIAL_CONFIG0	0x00000002 /* Disable Kseg0 caching */
#endif


/*-----------------------------------------------------------------------------
 * MIPS interrupt saved state. This must match the layout of the
 * HAL_SavedRegisters in hal_arch.h. Do not change this without changing the
 * layout there, or viceversa.	
 */
 
/* Size of registers */ 
#define mips_regsize 	4

/* Size of registers that stay the same size in all implementations */
#define mips_regsize32	4

#define	mipsreg_hi	(mips_regsize*32)
#define	mipsreg_lo	(mipsreg_hi+mips_regsize)
#define mipsreg_vector	(mipsreg_lo+mips_regsize)

#define	mipsreg_sr	(mipsreg_vector+mips_regsize32)
#define	mipsreg_pc	(mipsreg_sr+mips_regsize32)
#define	mipsreg_cachectrl (mipsreg_pc+mips_regsize)
#define	mipsreg_cause	(mipsreg_cachectrl+mips_regsize32)
#define	mipsreg_badvr	(mipsreg_cause+mips_regsize32)
#define	mipsreg_prid	(mipsreg_badvr+mips_regsize)
#define	mipsreg_config	(mipsreg_prid+mips_regsize32)
#define	mipsreg_size	(mipsreg_config+mips_regsize32)

/* The following expression ensures that the decrement is always a
 * multiple of 16 bytes. This is a requirement of the MEABI used in
 * MIPS32/64 targets.
 */

#define mips_exception_decrement	((mipsreg_size*2)&~0xF)

/*-----------------------------------------------------------------------------
 * Minimal stack frame size uses to call functions from asm.
 */ 	
#define mips_stack_frame_size		32	# 4 (64 bit) args worth

/*-----------------------------------------------------------------------------
 * Load Address and Relocate. This macro is used in code that may be linked
 * to execute out of RAM but is actually executed from ROM. 
 */
	.macro	lar	reg,addr
	la	\reg,\addr
	.endm


/*-----------------------------------------------------------------------------
 * CPU specific macros. These provide a common assembler interface to
 * operations that may have CPU specific implementations on different
 * variants of the architecture.		
 */	
	
	/* Initialize CPU */
	.macro	hal_cpu_init

	/* Initialize the register file */
	or		AT, zero, zero
	or		v0, zero, zero
	or		v1, zero, zero
	or		a0, zero, zero
	or		a1, zero, zero
	or		a2, zero, zero
	or		a3, zero, zero
	or		t0, zero, zero
	or		t1, zero, zero
	or		t2, zero, zero
	or		t3, zero, zero
	or		t4, zero, zero
	or		t5, zero, zero
	or		t6, zero, zero
	or		t7, zero, zero
	or		s0, zero, zero
	or		s1, zero, zero
	or		s2, zero, zero
	or		s3, zero, zero
	or		s4, zero, zero
	or		s5, zero, zero
	or		s6, zero, zero
	or		s7, zero, zero
	or		t8, zero, zero
	or		t9, zero, zero
	or		k0, zero, zero
	or		k1, zero, zero
	or		gp, zero, zero
	or		sp, zero, zero
	or		fp, zero, zero
	or		ra, zero, zero
	
	/* Initialize Misc. Cop0 state	 */
		
	/* Initialize/clear watchpoint registers */
	mtc0	zero, watchlo
	nop
	nop
	nop
	mtc0	zero, watchhi 
	nop
	nop
	nop
	
	/* zero cause reg */
	/* Clear WP bit to avoid watch exception upon user code entry */
	/* Clear IV bit - Interrupts go to general exception vector */
	/* Clear software interrupts */
	mtc0	zero, cause		
	nop
	
	/* initialize status register */
	la		v0, INITIAL_SR 		
	mtc0	v0, status
	nop
	nop
	nop
	/* Cache Initialization */
	la		v0, INITIAL_CONFIG0
	mtc0	v0, config0
	nop
	nop
	nop
	
	/* Clear the CountDM bit in the debug register */
	/* to stop counting while the CPU is in debug mode */
	mfc0	v0, debug
	lui		v1, 0xfdff
	ori		v1, v1, 0xffff
	and		v0, v0, v1
	mtc0    v0, debug
	
	/* Clear Count register */
	mtc0	zero, count

	/* Set compare to -1 to delay 1st count=compare */
	/* Also, clears timer interrupt */
	li		t2, -1
	mtc0	t2, compare
	
	.endm

	
	/* Enable interrupts */
	.macro hal_cpu_int_enable
	mfc0	v0, status
	la		v1, 0xfffffff9
	and		v0, v0, v1			/* clear EXL and ERL bits */	
	ori		v0, v0, 0x0001		/* set IE bit */
	mtc0	v0, status
	nop
	nop
	nop	
	.endm	
	
	/* Disable interrupts */
	.macro hal_cpu_int_disable
	mfc0	v0, status
	la		v1, 0xfffffffe 
	and		v0, v0, v1  		/* clear IE bit */
	mtc0	v0, status 
	nop
	nop
	nop
	.endm	
	

	/* Merge the interrupt enable state of the status register in */
	/* \sr with the current sr. */

#define HAL_SR_INT_MASK	0x00000007		// IE, EXL, ERL
			
	.macro	hal_cpu_int_merge sr
	mfc0	v0, status			# V0 = current SR
	la		v1, HAL_SR_INT_MASK		# V1 = SR interrupt bits mask
	and		\sr, \sr, v1			# Isolate interrupt bits of \sr
	nor		v1, v1, zero			# Invert mask
	and		v0, v0, v1			# V0 = current SR except int bits
	or		v0, v0, \sr			# V0 = New SR
	mtc0	v0, status			# Return to SR
	.endm

	/* Enable further exception processing, and disable */
	/* interrupt processing. */
	.macro hal_cpu_except_enable
	mfc0	v0, status
	la		v1, 0xFFFFFFF0
	and		v0, v0,v1		# clear EXL, ERL and IE bits	
	mtc0	v0, status
	nop
	nop
	nop
	.endm		
	
	/* Return from exception. */
	.macro	hal_cpu_eret pc,sr
    .set mips3
	ori     \sr, \sr, 2     /* prevent interrupts until eret */
	mtc0	\sr, status	  	/* put SR back */
	nop
	nop
	nop
	mvatc0	\pc,epc			/* put PC in EPC */
	nop
	nop
	nop
	sync					/* settle things down  */
	eret					/* return             */
	nop						/* just to be safe    */
    .set mips0
	.endm

	
/*-----------------------------------------------------------------------------
 * Default MIPS interrupt decoding macros. This uses the basic interrupt
 * support provided by CP0 in the cause and status registers. 
 */
 
	/* initialize all interrupts to disabled */
	.macro	hal_cpu_int_init
	mfc0	v0, status
	nop
	lui		v1, 0xFFFF
	ori		v1, v1, 0x00FF
	and		v0, v0, v1		/* clear the IntMask bits */
	mtc0	v0, status
	nop
	nop
	nop
	.endm

	.macro	hal_cpu_int_decode vnum
	mfc0	v1, status		/* get status register (interrupt mask) */
	nop						/* delay slot */
	mfc0	v0, cause		/* get cause register */
	nop						/* delay slot */
	move	\vnum, v0		
	and		v0, v0, v1		/* apply interrupt mask */
	
	nor		v1, v0, v0
	and		\vnum, v1
	mtc0	\vnum, cause
	nop
	nop
	nop
	mfc0	\vnum, cause		

	srl		v0, v0, 10		/* shift interrupt bits down */
	andi	v0, v0, 0x7f	/* isolate 6 interrupt bits */
	la		v1, hal_cpu_int_translation_table
	add		v0, v0, v1		/* index into table */ 
	lb		\vnum, 0(v0)	/* pick up vector number */
	
	.endm
    
    .macro	hal_cpu_int_mask vnum
#ifdef HAL_INTC_MASK_DATA
	move	v0, \vnum		/* get back the prioritary group */
	la		v1, hal_cpu_int_mask_table
	add		v0, v0, v1
	lb		v1, 0(v0)		/* go and search the corresponding mask */
#else
	move	v0, \vnum
	addi	v0, v0, 1
	move	v1, zero
	1:
	sll 	v1, v1, 1
	addi	v1, v1, 1
	addi	v0, v0, -1
	bne 	zero, v0, 1b 
#endif
	sll 	v1, v1, 10
	nor		v1, v1
	mfc0	v0, status		/* get status register (interrupt mask) */
	nop
	and		v0, v1 			/* mask interrupts */
	mtc0	v0, status
	nop
	.endm
    
	.macro	hal_intc_decode_data
hal_cpu_int_translation_table:	
#ifdef HAL_INTC_MASK_DATA
	.byte	6, 0, 1, 1
#else
	.byte	0, 0, 1, 1
#endif
	.byte	2, 2, 2, 2
	.byte	3, 3, 3, 3
	.byte	3, 3, 3, 3
	.byte	4, 4, 4, 4
	.byte	4, 4, 4, 4
	.byte	4, 4, 4, 4
	.byte	4, 4, 4, 4
	.byte	5, 5, 5, 5
	.byte	5, 5, 5, 5
	.byte	5, 5, 5, 5
	.byte	5, 5, 5, 5
	.byte	5, 5, 5, 5
	.byte	5, 5, 5, 5
	.byte	5, 5, 5, 5
	.byte	5, 5, 5, 5
	.endm

	.macro	hal_intc_mask_data
//#ifdef HAL_INTC_MASK_DATA
hal_cpu_int_mask_table:	
	.byte	0x01, 0x03, 0x07, 0x0f
	.byte	0x1f, 0x3f, 0x00, 0x00
//#endif
	.endm

/*------------------------------------------------------------------------------
 * Register save and restore macros. These expect a pointer to a CPU save state
 * area in the register \ptr. The GPR indicated by \reg will be saved into its
 * slot in that structure.
 */
	.macro sgpr reg,ptr
	sw	$\reg,(\reg*4)(\ptr)
	.endm

	.macro lgpr reg,ptr
	lw	$\reg,(\reg*4)(\ptr)
	.endm

	.macro slo reg,ptr
	sw	\reg,(mipsreg_lo)(\ptr)
	.endm

	.macro shi reg,ptr
	sw	\reg,(mipsreg_hi)(\ptr)
	.endm

	.macro llo reg,ptr
	lw	\reg,(mipsreg_lo)(\ptr)
	.endm

	.macro lhi reg,ptr
	lw	\reg,(mipsreg_hi)(\ptr)
	.endm

	.macro ssp reg,ptr
	sw	\reg,(29*4)(\ptr)
	.endm

	.macro lsp reg,ptr
	lw	\reg,(29*4)(\ptr)
	.endm

	.macro sva reg,val
	sw	\reg,\val
	.endm

	.macro lva reg,val
	lw	\reg,\val
	.endm

	.macro mvafc0 gpr,cpr
	mfc0	\gpr,\cpr
	.endm

	.macro mvatc0 gpr,cpr
	mtc0	\gpr,\cpr
	.endm

	.macro lpc reg,ptr
	lw	\reg,(mipsreg_pc)(\ptr)
	.endm

	.macro spc reg,ptr
	sw	\reg,(mipsreg_pc)(\ptr)
	.endm



/*------------------------------------------------------------------------------
 * MMU macros.
 */	
	
	.macro	hal_mmu_init	
	
	mfc0	t3, config0 		/* Determine if we have a TLB */
	sll		t3, 22
	srl		t3, 29
	li		t7, 0x1				/* MT = 1  => TLB */	
	bne		t3, t7, 15f
	nop

	mfc0	t2, config0, 1     
	sll		t3, t2, 1
	srl		t3, 26				/* Number of TLB entries (-1) */

	mtc0	zero, tlblo0		/* EntryLo0 */
	mtc0	zero, tlblo1		/* EntryLo1 */
	mtc0	zero, pagemask		/* PageMask */
	mtc0	zero, wired		    /* Wired    */
	
	lui		t4, 0x8000

	1:	
	mtc0	t3, index			/* Index register */
	mtc0	t4, tlbhi			/* EntryHi */
	nop						
	nop
	tlbwi
	add		t4, (2<<13)			/* Add 8K to the address to avoid   */
								/* TLB conflict with previous entry */
	bne		t3, zero, 1b
	add		t3, -1
	 
	15:	
	.endm
	

/*------------------------------------------------------------------------------
 * MEMC macros.
 */
 	
	.macro	hal_memc_init
	.endm
	
	
/*------------------------------------------------------------------------------
 * Cache macros.
 */	

	.macro	hal_cache_init
	
	mfc0	v0, config0			/* disable Kseg0 caching in config0 register */
	nop
	nop	
	la		v1, 0xfffffff8
	and		v0, v0, v1
	ori		v0, v0, 2
	mtc0	v0, config0
	nop
	nop
	nop
	
	mfc0	t2, config0, 1		/* Determine how big the I$ is */
	sll		t3, t2, 10			/* Isolate I$ Line Size */
	srl		t3, 29
	
	beq		t3, zero, 10f 		/* Skip ahead if No I$ */
	nop

	li	 	t6, 2
	sllv	t3, t6, t3  		/* Now have I$ line size in bytes */
	move	s0, t3

	sll		t4, t2, 7
	srl		t4, 29
	li		t6, 64
	sllv	t4, t6, t4			/* I$ Sets per way */

	sll		t5, t2, 13
	srl		t5, 29				/* I$ Assoc (-1) */
	add		t5, 1
	mul		t4, t4, t5			/* Total number of sets */
	move	s1, t4
	mul		s2, t4, t3    		/* number of bytes */

	lui		t6, 0x8000			/* Get a KSeg0 address for cacheops */
	
	mtc0	zero, errctl		/* least-recently */
	mtc0	zero, taglo			/* Clear TagLo/TagHi registers */
	/* mtc0	zero, taghi */

	move	t7, t4	
	1:	
	cache	0x8, 0(t6)			/* Index Store Tag Cache Op */
								/* Will invalidate the tag entry, 
								   clear the lock bit,
	   							   and clear the LRU bit */
	add		t7, -1				/* Decrement set counter */
	bne		t7, zero, 1b
	add		t6, t3 				/* Get next line address */
								
	10:							/* Now the I$ has been flushed */
								/* go through and invalidate the D$ */							
	sll		t3, t2, 19			/* Isolate D$ Line Size */
	srl		t3, 29
	
	beq		t3, zero, 10f 		/* Skip ahead if No D$ */
	nop
	
	li	 	t6, 2
	sllv 	t3, t6, t3			/* Now have D$ line size in bytes */
	move 	s3, t3
	
	sll		t4, t2, 16
	srl		t4, 29
	li		t6, 64
	sllv	t4, t6, t4			/* D$ Sets per way */
	
	sll		t5, t2, 22
	srl		t5, 29				/* D$ Assoc (-1) */
	add		t5, 1
	mul		t4, t4, t5			/* Get total number of sets */
	move 	s4, t4
	mul 	s5, t4, t3    		/* number of bytes */
		
	lui		t6, 0x8000			/* Get a KSeg0 address for cacheops */
	
	mtc0	zero, taglo			/* Clear TagLo/TagHi registers */
	/* mtc0	zero, taghi */
	
	move	t7, t4				/* Index Store Tag Cache Op */
	1:							/* Will invalidate the tag entry, 
								   clear the lock bit,
	   							   and clear the LRU bit */
	cache	0x9, 0(t6)
	add		t7, -1				/* Decrement set counter */
	bne		t7, zero, 1b
	add		t6, t3				/* Get next line address */
	
	10:	
	nop

	.endm

	.macro	hal_cache_enabled
	
	mfc0	v0, config0			
	nop
	nop	
	la		v1, 0xfffffff8
	and		v0, v0, v1
	ori		v0, v0, 3
	mtc0	v0, config0
	nop

	.endm
	
/*------------------------------------------------------------------------------
 * Diagnostics macros.
 */
 	
	.macro	hal_diag_init
	.endm

	.macro	hal_diag_excpt_start
	.endm

	.macro	hal_diag_intr_start
	.endm

	.macro	hal_diag_restore
	.endm
	

/*------------------------------------------------------------------------------
 * Timer initialization.
 */
 	
	.macro	hal_timer_init
	.endm
	


/*----------------------------------------------------------------------------*/
#endif /* __HAL_ARCH_INC__ */

