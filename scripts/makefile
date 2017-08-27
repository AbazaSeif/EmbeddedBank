#==============================================================================
#
#    makefile
#
#==============================================================================
#==============================================================================

#
# Memory Layout
#
#LAYOUT	= debug
#LAYOUT	= xdebug
LAYOUT	= release

#
# some usefull variables
#

BT_HDE = .
INCLUDE = $(BT_HDE)
INCLUDE_INC	= $(BT_HDE)/include
INCLUDE_LIB = $(BT_HDE)/include/lib
INCLUDE_EMV = $(BT_HDE)/include/emv
BT_DRV  = $(BT_HDE)/btlib/bt_driver
BUILD		= .
INSTALL		= .
LIBRARY	= $(BT_HDE)/lib
SCRIPT	= $(BT_HDE)/scripts

LIBATOF	= $(LIBRARY)/atoflib.a
LIBC	= $(LIBRARY)/libc.a
LIBE	= $(LIBRARY)/libe.a
LIBBTIC	= $(LIBRARY)/emvlib.a
LIBBTUSB = $(LIBRARY)/usblib.a
LIBEMVL2 = $(LIBRARY)/emvl2.a

COMPILERPATH = /opt/mips-sde/mips-sde/06.61/bin/
SDECC = $(COMPILERPATH)sde-gcc
LD    = $(COMPILERPATH)sde-ld
GDB   = $(COMPILERPATH)sde-insight
OBJCOPY	= $(COMPILERPATH)sde-objcopy
OBJDUMP	= $(COMPILERPATH)sde-objdump
OBJCONV	= $(COMPILERPATH)sde-conv
OBJVER	= $(COMPILERPATH)sde-strings


AS         = $(SDECC) -xassembler-with-cpp
ASFLAGS    = -march=4kec -mips32r2 -c -D_32_ -D_ASSEMBLER_ -EL -gstabs+


CC         = $(SDECC)
CFLAGS     = -march=4kec -mips32r2 -mno-float -EL -gdwarf-2  \
		-ffixed-14 -ffixed-15 -G0 -fomit-frame-pointer -fsigned-char      \
		-Wimplicit -Wformat -D_32_ -c -mlong-calls


#
# Flash version
#
LDFLAG	= -EL -T $(SCRIPT)/ic5100_pm_flash_$(LAYOUT).ld

#
# SDRAM version
#
#LDFLAG	= -EL -T $(SCRIPT)/ic5100_PM_sdram_$(LAYOUT).ld


GDBFLAGS = -x $(SCRIPT)/ic5100_flash_$(LAYOUT).ini


#
# Executable file name
#
#
# Flash version
#
PROGRAM	= Full_Application_$(LAYOUT)

#
# SDRAM version
#
#PROGRAM	= IC5100_PM_SDRAM_$(LAYOUT)

#
# Object file list
#
#SRC     = $(wildcard ./*.c)
SRC     = $(wildcard ./*.c ./src/lib/*.c ./src/emv/*.c)
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
	$(CC) $(CFLAGS) $(patsubst %, -I%,$(INCLUDE) $(INCLUDE_INC) $(INCLUDE_LIB) $(INCLUDE_EMV)) $^ \
	-o $(patsubst %, $(BUILD)/%, $@)


#all: $(OBJECTS) $(BT_DRV)/btutils.o
#	 $(LD) $(LDFLAG) -L $(BUILD) -L $(BT_DRV) \
#	-o $(INSTALL)/$(PROGRAM).elf  -Map $(INSTALL)/$(PROGRAM).map  \
#	--start-group $(FIRMWARE) $(LIBATOF) $(LIBC) $(LIBE) $(LIBBTIC) \
#	$(LIBBTUSB) \
#	$(patsubst %, $(BUILD)/%, $(OBJECTS) $(BT_DRV)/cstartup.o $(BT_DRV)/btutils.o \
#	$(BT_DRV)/asmutil.o $(BT_DRV)/prtutil.o $(BT_DRV)/prtfont.o \
#	$(BT_DRV)/CryptoLib.o $(BT_DRV)/ppdrv.o )  --end-group

all: $(OBJECTS) $(BT_DRV)/btutils.o
	 $(LD) $(LDFLAG) -L $(BUILD) -L $(BT_DRV) \
	-o $(INSTALL)/$(PROGRAM).elf  -Map $(INSTALL)/$(PROGRAM).map  \
	--start-group $(FIRMWARE) $(LIBATOF) $(LIBC) $(LIBE) $(LIBBTIC) \
	$(LIBBTUSB) $(LIBEMVL2) \
	$(patsubst %, $(BUILD)/%, $(OBJECTS) $(BT_DRV)/cstartup.o $(BT_DRV)/btutils.o \
	$(BT_DRV)/asmutil.o $(BT_DRV)/prtutil.o $(BT_DRV)/prtfont.o \
	$(BT_DRV)/cryptolib.o $(BT_DRV)/ppdrv.o \
	./btlib/lib/beeplib.o ./btlib/lib/btsclib.o ./btlib/lib/commlib.o \
	./btlib/lib/country.o ./btlib/lib/frmwri.o ./btlib/lib/gsmlib.o \
	./btlib/lib/iconlib.o ./btlib/lib/keylib.o ./btlib/lib/lcdlib.o \
	./btlib/lib/libc.o ./btlib/lib/magtek_msr.o ./btlib/lib/memlib.o \
	./btlib/lib/msrlib.o ./btlib/lib/printf.o \
	./btlib/lib/prtbitellogo.o ./btlib/lib/prtpmlogo.o \
	./btlib/lib/rtclib.o ./btlib/lib/sysinfo.o ./btlib/lib/timerlib.o \
	./btlib/lib/tmslib.o ./btlib/lib/unzip.o ./btlib/lib/utillib.o \
	)  --end-group
	$(OBJCONV) -v -l $(INSTALL)/$(PROGRAM).elf
ifeq ($(LAYOUT),release)
	$(OBJCONV) -v -x 2,3,4,5,6 -o $(INSTALL)/$(PROGRAM).s19 $(INSTALL)/$(PROGRAM).elf
endif

debug:
	$(GDB) $(GDBFLAGS) $(INSTALL)/$(PROGRAM).elf


clean:
	rm -f $(OBJECTS) $(BUILD)/hallib.o $(INSTALL)/$(PROGRAM).elf $(INSTALL)/$(PROGRAM).map

# EOF #
