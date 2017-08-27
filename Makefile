#
#  There exist several targets which are by default empty and which can be 
#  used for execution of your targets. These targets are usually executed 
#  before and after some main targets. They are: 
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:               called before 'help' target
#     .help-post:              called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#  
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage
#  
#  Targets .build-impl, .clean-impl, .clobber-impl, .all-impl, and
#  .help-impl are implemented in nbproject/makefile-impl.mk.
#
#  Available make variables:
#
#     CND_BASEDIR                base directory for relative paths
#     CND_DISTDIR                default top distribution directory (build artifacts)
#     CND_BUILDDIR               default top build directory (object files, ...)
#     CONF                       name of current configuration
#     CND_PLATFORM_${CONF}       platform name (current configuration)
#     CND_ARTIFACT_DIR_${CONF}   directory of build artifact (current configuration)
#     CND_ARTIFACT_NAME_${CONF}  name of build artifact (current configuration)
#     CND_ARTIFACT_PATH_${CONF}  path to build artifact (current configuration)
#     CND_PACKAGE_DIR_${CONF}    directory of package (current configuration)
#     CND_PACKAGE_NAME_${CONF}   name of package (current configuration)
#     CND_PACKAGE_PATH_${CONF}   path to package (current configuration)
#
# NOCDDL


#------------------+
# Variabels	   |
#------------------+ 
LAYOUT=release
#1- flash 2- sdram
MEMORY=flash
# 1- 5100 2- 3300
MODEL=5100
# 1- Normal 2- MultiApp 3- USB
MODE=Normal
#optimization 
OCFLAGS=-o
#Opend Debug On Machin
#1-Open 2-Close
DEBUGMODE=Close
#Output Format
#----------------------------------------------------------------------+
#srec, s3  Motorola   S-records,   using  S3  and  S7  (32-bit	       |
#          address) records; symbol output can be provided via	       |
#          S4 records, as supported by LSI PMON.		       |
#								       |
#s2        Same  as  above,  except  using  S2  and S8 (24-bit	       |
#	  address) records, to suit some PROM programmers.	       |
#								       |
#s1        Same as above,  except  using  S1  and  S9  (16-bit	       |
#          address) records.					       |
#								       |
#lsi       High  density  (radix  64) ASCII encoding for downloading   |
#          by the LSI PMON monitor; symbol  output  is supported.      |
#								       |
#idt       Binary  S-record  format  for  downloading  by  the	       |
#          IDT/sim monitor.					       |
#								       |
#stagbin   Proprietary binary format for  Stag  PROM  programmers.     |
#								       |
#bin       Raw  binary output, suitable for further conversion         |
#          by another user program.				       |
#----------------------------------------------------------------------+
FORMAT=srec
#------------------+
#  Library Path    |
#------------------+
BT_HDE = ../..
INCLUDE	= $(BT_HDE)/include
Bitel    = $(BT_HDE)/sdk
BUILD		= .
INSTALL		= .
LIBRARY	= $(BT_HDE)/lib
SCRIPT	= $(BT_HDE)/scripts/$(MODE)/$(MODEL)
BTDRIVER= $(BT_HDE)/Object

#-----------------+
# Static Library  |
#-----------------+

LIBC	= $(LIBRARY)/libc.a
LIBE	= $(LIBRARY)/libe.a
LIBM	= $(LIBRARY)/libm.a
LIBIC	= $(LIBRARY)/emvlib.a
LIBBitel   = $(Bitel)/Bitel_Bitel.a
LIBEMV  = $(LIBRARY)/emvlib.a
LIBEMVL2= $(LIBRARY)/emvl2.a

#-----------------+
# Shell Command   |
#-----------------+

MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib

#---------------------------+
# Compiler and Linker Flags |
#---------------------------+

AS         	= sde-gcc -xassembler-with-cpp
ASFLAGS    	= -march=4kec -mips32r2 -c -D_32_ -D_ASSEMBLER_ -EL -gstabs+

CC              = sde-gcc
#If You want to Open Flag just add ( -D ) Options and Flag Name . Ex -DFLAGNAME
ifeq ($(DEBUGMODE),Open)
CFLAGS          = -march=4kec -mips32r2 -mno-float -EL -gdwarf-2  \
		-ffixed-14 -ffixed-15 -g -G0 -fomit-frame-pointer      \
		-Wimplicit -Wformat -D_32_ -c -mlong-calls -DDUBUG
else
CFLAGS          = -march=4kec -mips32r2 -mno-float -EL -gdwarf-2  \
		-ffixed-14 -ffixed-15 -G0 -fomit-frame-pointer      \
		-Wimplicit -Wformat -D_32_ -c -mlong-calls
endif

LD		= sde-ld
LDFLAG		= -EL -T $(SCRIPT)/ic$(MODEL)_$(MEMORY)_$(LAYOUT).S

GDB		= sde-insight
GDBFLAGS 	= -x $(SCRIPT)/ic$(MODEL)_$(MEMORY)_$(LAYOUT).ini

OBJCOPY	= sde-objcopy
OBJDUMP	= sde-objdump
OBJCONV	= sde-conv
OBJVER	= sde-strings

#
# Executable file name
#
PROGRAM	= Bitel_Hack_$(MODEL)_$(MEMORY)_$(MODE)

#
# Object file list
#
SRC     = $(wildcard ./*.c)
SRC1     = $(wildcard ./*.S)
OBJECTS = $(SRC:.c=.o) $(SRC1:.S=.o)

#
# Assembler compilation
#
%.o: %.S
	@mkdir -p $(BUILD)
	$(AS) $(ASFLAGS) $(patsubst %, -I%,$(INCLUDE)) $< \
	-o $(patsubst %, $(BUILD)/%, $@)
%.o: %.s
	@mkdir -p $(BUILD)
	$(AS) $(ASFLAGS) $(patsubst %, -I%,$(INCLUDE)) $< \
	-o $(patsubst %, $(BUILD)/%, $@)

#
# C compilation
#
%.o: %.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(patsubst %, -I%,$(INCLUDE) $(Bitel)) $^ \
	-o $(patsubst %, $(BUILD)/%, $@)



# build
build:  .build-post
	$(OBJCONV) -v -x 1,2,3, -f $(FORMAT) -o $(INSTALL)/$(PROGRAM).s19 $(INSTALL)/$(PROGRAM).elf

.build-pre: $(OBJECTS)  $(BTDRIVER)/btutils.o
	    $(LD) $(LDFLAG) -L $(BUILD)  \
	$(OCFLAGS) $(INSTALL)/$(PROGRAM).elf  -Map $(INSTALL)/$(PROGRAM).map  \
	--start-group $(FIRMWARE) $(LIBC) $(LIBE) $(LIBIC) $(LIBBitel) $(LIBEMV) $(LIBEMVL2) $(LIBM) \
	$(patsubst %, $(BUILD)/%, $(OBJECTS) $(BTDRIVER)/cstartup.o)  --end-group

.build-post: .build-pre
	$(OBJCONV) -v -l $(INSTALL)/$(PROGRAM).elf


debug: $(GDB) $(GDBFLAGS) $(INSTALL)/$(PROGRAM).elf

# clean
clean: .clean-post

.clean-pre:
# Add your pre 'clean' code here...

.clean-post:
	rm -f $(OBJECTS) $(INSTALL)/$(PROGRAM).elf $(INSTALL)/$(PROGRAM).map $(BUILD)/*.s19 $(BUILD)/*.bin

# clobber
clobber: .clobber-post

.clobber-pre:
# Add your pre 'clobber' code here...

.clobber-post: .clobber-impl
# Add your post 'clobber' code here...


# all
all: .all-post

.all-pre:
# Add your pre 'all' code here...

.all-post: .all-impl
# Add your post 'all' code here...


# help
help: .help-post

.help-pre:
# Add your pre 'help' code here...

.help-post: .help-impl
# Add your post 'help' code here...



# include project implementation makefile
include nbproject/Makefile-impl.mk

# include project make variables
include nbproject/Makefile-variables.mk