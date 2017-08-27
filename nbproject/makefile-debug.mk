#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=mips-mti-linux-gnu-gcc
CCC=mips-mti-linux-gnu-g++
CXX=mips-mti-linux-gnu-g++
FC=gfortran
AS=mips-mti-linux-gnu-as

# Macros
CND_PLATFORM=GNU_MIPS-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/APPPOS.o \
	${OBJECTDIR}/FLASH.o \
	${OBJECTDIR}/GSM.o \
	${OBJECTDIR}/HWTEST.o \
	${OBJECTDIR}/HtmlUtil.o \
	${OBJECTDIR}/KEY.o \
	${OBJECTDIR}/LCDMSG.o \
	${OBJECTDIR}/MODEM.o \
	${OBJECTDIR}/MSR.o \
	${OBJECTDIR}/PRINTER.o \
	${OBJECTDIR}/PRTMSG.o \
	${OBJECTDIR}/RS232.o \
	${OBJECTDIR}/RTC.o \
	${OBJECTDIR}/RefTable.o \
	${OBJECTDIR}/SCARD.o \
	${OBJECTDIR}/TMSDOWN.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/sFontLib.o \
	${OBJECTDIR}/timeconv.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fullproject

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fullproject: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fullproject ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/APPPOS.o: APPPOS.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/APPPOS.o APPPOS.c

${OBJECTDIR}/FLASH.o: FLASH.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FLASH.o FLASH.c

${OBJECTDIR}/GSM.o: GSM.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GSM.o GSM.c

${OBJECTDIR}/HWTEST.o: HWTEST.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HWTEST.o HWTEST.c

${OBJECTDIR}/HtmlUtil.o: HtmlUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HtmlUtil.o HtmlUtil.c

${OBJECTDIR}/KEY.o: KEY.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/KEY.o KEY.c

${OBJECTDIR}/LCDMSG.o: LCDMSG.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LCDMSG.o LCDMSG.c

${OBJECTDIR}/MODEM.o: MODEM.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MODEM.o MODEM.c

${OBJECTDIR}/MSR.o: MSR.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MSR.o MSR.c

${OBJECTDIR}/PRINTER.o: PRINTER.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PRINTER.o PRINTER.c

${OBJECTDIR}/PRTMSG.o: PRTMSG.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PRTMSG.o PRTMSG.c

${OBJECTDIR}/RS232.o: RS232.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RS232.o RS232.c

${OBJECTDIR}/RTC.o: RTC.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RTC.o RTC.c

${OBJECTDIR}/RefTable.o: RefTable.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RefTable.o RefTable.c

${OBJECTDIR}/SCARD.o: SCARD.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SCARD.o SCARD.c

${OBJECTDIR}/TMSDOWN.o: TMSDOWN.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TMSDOWN.o TMSDOWN.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/sFontLib.o: sFontLib.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sFontLib.o sFontLib.c

${OBJECTDIR}/timeconv.o: timeconv.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timeconv.o timeconv.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
