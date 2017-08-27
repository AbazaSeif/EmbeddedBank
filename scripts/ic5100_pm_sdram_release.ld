/*===========================================================================
 *
 *  mlt_usip_debug.ld
 *
 *===========================================================================
 *
 * This is a sample linker command file specifying how the object files
 * in a build might be linked and located. Combined with the other
 * linker command files provided with the compiler, it provides a base
 * to build your own file for your particular system.
 *
 * For a description of the different statements in this file, please
 * refer to the LD section of the User's Guide.
 *
 *===========================================================================*/
 
OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(mips)
ENTRY(int_vector)	

 
MEMORY
{
 	sdram(rwx)	: ORIGIN = 0x20000000, LENGTH = 16M
	flash(rwx)	: ORIGIN = 0x40000000, LENGTH = 16M
}

SECTIONS
{
	.com.vect.r 0x20000000 :
	{
		KEEP(* (.cstartup))
	} > sdram
	
	.usr.text :
	{
		_stext = .;	_ftext = .;
		
		/**********************************************************************
									static area
		**********************************************************************/
		/*---------------------------------------------------------------------
			OS and device drivers (asmutil.o, prtutil.o, and prtfont.o)
		---------------------------------------------------------------------*/
		*(.lib.prog)
		*(.lib.text)
		
		/*---------------------------------------------------------------------
			Libraries for Paymaster
		---------------------------------------------------------------------*/
		*(.prtpmlogo.text)
		*(.prtbitellogo.text)
		*(.des_ecb.prog)
		*(.des_ecb.text)
		
		*(.btsclib.prog)
		*(.btsclib.text)
		
		*(.sysinfo.prog)
		*(.memlib.prog)
		*(.beeplib.prog)
		*(.rtclib.prog)
		*(.rtclib.text)
		*(.timerlib.prog)
		*(.msrlib.prog)
		*(.commlib.prog)
		*(.commlib.text)
		*(.lcdlib.prog)
		*(.lcdlib.text)
		*(.keylib.prog)
		*(.country.text)
		*(.hsmodem.prog)
		*(.hsmodem.text)
		*(.unzip.prog)
		*(.unzip.text)
		*(.tnmslib.prog)
		*(.tnmslib.text)
		
		/**********************************************************************
									dynamic area
		**********************************************************************/
		*(.reftable)
		
		hal*(.text .rodata*)
		emv*(.text .rodata*)
		at83*(.text .rodata*)
		sc_at83*(.text .rodata*)
		
		*(.text)
		*(.rodata*)
	} > sdram
	_etext = .; PROVIDE (etext = .);
}

SECTIONS
{
	/* Flash working buffer */
	.flash.buffer 0x20800000:
	{
		. += 0x20000;
	} > sdram
	
	.com.text :
	{
		__com_ram_start = .;
		*(.text.ram)
	} > sdram
	
	__com_ram_end = .;
	__com_rom_start = LOADADDR(.com.text);
	
	.lib.bss ALIGN(4) :
	{ 
		__lib_bss_start = .;
		
		*(.lib.ram)
		
		*(.des_ecb.ram)
		
		*(.btsclib.ram)
		
		*(.memlib.ram)
		*(.beeplib.ram)
		*(.commlib.ram)
		*(.lcdlib.ram)
		*(.keylib.ram)
		*(.hsmodem.ram)
		*(.unzip.ram)
		*(.tnmslib.ram)
	} > sdram
	
	.emv.bss :
	{
		hal*(.bss COMMON .sbss .scommon)
		emv*(.sbss .scommon .bss COMMON)
		sc_at83*(.bss COMMON .sbss .scommon)
		*(SORT(.sys_table*emv*))
		*(SORT(.sys_table*))
	} > sdram

	__lib_bss_end = .;	
	
	.usr.sbss ALIGN(4) :
	{
		__usr_bss_start = .; _fbss = .;
		*(.sbss .scommon)
	} > sdram
	
	.usr.bss ALIGN(4):
	{
		*(.bss COMMON)
	} > sdram
	
	__usr_bss_end = .;	
	__usr_end = . ;
		
	.ram.heap :
	{
		__ram_heap_start = .;
		/* Allocate room for heap */
		. += 128K;
		__ram_heap_end = .;
	} > sdram
		
	.usr.data : AT( ALIGN(LOADADDR(.usr.text) + SIZEOF(.usr.text),16) )
	{
		__usr_ram_start = .; _fdata = . ;
		*(.data .sdata)
		*(.lit4 .lit8)
		KEEP(*( SORT (.dev*))) ;
		_edata  = ABSOLUTE(.);
	} > sdram
	
	__usr_ram_end = .;
	__usr_rom_start = LOADADDR(.usr.data);
	
	PROVIDE(edata = .);
}

SECTIONS
{
	/* Must reside in uncached internal RAM */
	__com_bss_start = 0xa0008000;
    .com.bss __com_bss_start : 
    {
/*		. += 32K ;*/ 
    	*(.bss.usb)
		. = ALIGN(32);	    
    }

	__com_bss_end = .;
	. = __com_bss_end & 0xdFFFFFFF;

	/* Must reside in uncached internal RAM */
	.hal.heap 0xa001c500 :
	{
		__hal_heap_start = .;
		/* Allocate room for heap */
		. += 8K;
		__hal_heap_end = .;
	}
}

