#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=TftDriver/spi.c TftDriver/TftDriver.c TftDriver/DefaultFonts.c TftDriver/bulb.c TftDriver/fan.c Pic32Ini.c UART.c main.c sensor.c bombilla.c ventilador.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/TftDriver/spi.o ${OBJECTDIR}/TftDriver/TftDriver.o ${OBJECTDIR}/TftDriver/DefaultFonts.o ${OBJECTDIR}/TftDriver/bulb.o ${OBJECTDIR}/TftDriver/fan.o ${OBJECTDIR}/Pic32Ini.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/main.o ${OBJECTDIR}/sensor.o ${OBJECTDIR}/bombilla.o ${OBJECTDIR}/ventilador.o
POSSIBLE_DEPFILES=${OBJECTDIR}/TftDriver/spi.o.d ${OBJECTDIR}/TftDriver/TftDriver.o.d ${OBJECTDIR}/TftDriver/DefaultFonts.o.d ${OBJECTDIR}/TftDriver/bulb.o.d ${OBJECTDIR}/TftDriver/fan.o.d ${OBJECTDIR}/Pic32Ini.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/sensor.o.d ${OBJECTDIR}/bombilla.o.d ${OBJECTDIR}/ventilador.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/TftDriver/spi.o ${OBJECTDIR}/TftDriver/TftDriver.o ${OBJECTDIR}/TftDriver/DefaultFonts.o ${OBJECTDIR}/TftDriver/bulb.o ${OBJECTDIR}/TftDriver/fan.o ${OBJECTDIR}/Pic32Ini.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/main.o ${OBJECTDIR}/sensor.o ${OBJECTDIR}/bombilla.o ${OBJECTDIR}/ventilador.o

# Source Files
SOURCEFILES=TftDriver/spi.c TftDriver/TftDriver.c TftDriver/DefaultFonts.c TftDriver/bulb.c TftDriver/fan.c Pic32Ini.c UART.c main.c sensor.c bombilla.c ventilador.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX230F064D
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/TftDriver/spi.o: TftDriver/spi.c  .generated_files/flags/default/5904773ce323ffa45aecdd094f5ed65c45910ad5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/spi.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/spi.o.d" -o ${OBJECTDIR}/TftDriver/spi.o TftDriver/spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/TftDriver.o: TftDriver/TftDriver.c  .generated_files/flags/default/eb794a71caf4d3da9c926a498edcf21d5a9231d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/TftDriver.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/TftDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/TftDriver.o.d" -o ${OBJECTDIR}/TftDriver/TftDriver.o TftDriver/TftDriver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/DefaultFonts.o: TftDriver/DefaultFonts.c  .generated_files/flags/default/a00b40d0dae2f51632dbb7b5523650e19943512a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/DefaultFonts.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/DefaultFonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/DefaultFonts.o.d" -o ${OBJECTDIR}/TftDriver/DefaultFonts.o TftDriver/DefaultFonts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/bulb.o: TftDriver/bulb.c  .generated_files/flags/default/671bed654a30a5cb8a3311abb1ac22661dbf46af .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/bulb.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/bulb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/bulb.o.d" -o ${OBJECTDIR}/TftDriver/bulb.o TftDriver/bulb.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/fan.o: TftDriver/fan.c  .generated_files/flags/default/f2ccf3b39789a4b92ae61ffd2c7476b749af36a7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/fan.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/fan.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/fan.o.d" -o ${OBJECTDIR}/TftDriver/fan.o TftDriver/fan.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Pic32Ini.o: Pic32Ini.c  .generated_files/flags/default/cac003e412236fa40891f09456e0a9af061da8f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pic32Ini.o.d 
	@${RM} ${OBJECTDIR}/Pic32Ini.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Pic32Ini.o.d" -o ${OBJECTDIR}/Pic32Ini.o Pic32Ini.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/UART.o: UART.c  .generated_files/flags/default/799f714f22e5696e61dc3639adf44aa60d029957 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/UART.o.d" -o ${OBJECTDIR}/UART.o UART.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/a61e380a9e9785eb56fe5464ac6e2f935d0fcc50 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensor.o: sensor.c  .generated_files/flags/default/56915645895477d0f19f5833ca33df6569859f46 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensor.o.d 
	@${RM} ${OBJECTDIR}/sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/sensor.o.d" -o ${OBJECTDIR}/sensor.o sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bombilla.o: bombilla.c  .generated_files/flags/default/bc788b80abe9e45be33817dab60f1049fa38b7a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bombilla.o.d 
	@${RM} ${OBJECTDIR}/bombilla.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bombilla.o.d" -o ${OBJECTDIR}/bombilla.o bombilla.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ventilador.o: ventilador.c  .generated_files/flags/default/56e483543afb852d712c17fe1f80942d82dd7c86 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ventilador.o.d 
	@${RM} ${OBJECTDIR}/ventilador.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/ventilador.o.d" -o ${OBJECTDIR}/ventilador.o ventilador.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/TftDriver/spi.o: TftDriver/spi.c  .generated_files/flags/default/a138d8fd23bf8954a27b2191c5c25638669ec918 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/spi.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/spi.o.d" -o ${OBJECTDIR}/TftDriver/spi.o TftDriver/spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/TftDriver.o: TftDriver/TftDriver.c  .generated_files/flags/default/ee311da3ff8cddaa3e47bc1e4c3bdd04ff8f83d6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/TftDriver.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/TftDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/TftDriver.o.d" -o ${OBJECTDIR}/TftDriver/TftDriver.o TftDriver/TftDriver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/DefaultFonts.o: TftDriver/DefaultFonts.c  .generated_files/flags/default/806041ecb1f0bf6f5396634ad427e4b7d57385e8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/DefaultFonts.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/DefaultFonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/DefaultFonts.o.d" -o ${OBJECTDIR}/TftDriver/DefaultFonts.o TftDriver/DefaultFonts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/bulb.o: TftDriver/bulb.c  .generated_files/flags/default/a4f3d58b9e0234248c394feaeb8bb801b53cbb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/bulb.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/bulb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/bulb.o.d" -o ${OBJECTDIR}/TftDriver/bulb.o TftDriver/bulb.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TftDriver/fan.o: TftDriver/fan.c  .generated_files/flags/default/bfe258cb9d65a9fe00087d9842a1df9624c50e0b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/TftDriver" 
	@${RM} ${OBJECTDIR}/TftDriver/fan.o.d 
	@${RM} ${OBJECTDIR}/TftDriver/fan.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/TftDriver/fan.o.d" -o ${OBJECTDIR}/TftDriver/fan.o TftDriver/fan.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Pic32Ini.o: Pic32Ini.c  .generated_files/flags/default/b9dd77751ed5e776bd56379ea4bb801def1b1dc3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Pic32Ini.o.d 
	@${RM} ${OBJECTDIR}/Pic32Ini.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Pic32Ini.o.d" -o ${OBJECTDIR}/Pic32Ini.o Pic32Ini.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/UART.o: UART.c  .generated_files/flags/default/166dfb0dd265046d93ad7046b517a81fa76bf67a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/UART.o.d" -o ${OBJECTDIR}/UART.o UART.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/919ba14cec0e72abb464786621d5ad9e7b90d38a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensor.o: sensor.c  .generated_files/flags/default/7c1a3db4fab19a8c86c89a5557f3dbd08318d7b8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensor.o.d 
	@${RM} ${OBJECTDIR}/sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/sensor.o.d" -o ${OBJECTDIR}/sensor.o sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bombilla.o: bombilla.c  .generated_files/flags/default/75e9bab49cdb79822abef14a936e2660aac76d95 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bombilla.o.d 
	@${RM} ${OBJECTDIR}/bombilla.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bombilla.o.d" -o ${OBJECTDIR}/bombilla.o bombilla.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ventilador.o: ventilador.c  .generated_files/flags/default/547762fbc357155798dbf3a24ed1241be0decf28 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ventilador.o.d 
	@${RM} ${OBJECTDIR}/ventilador.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/ventilador.o.d" -o ${OBJECTDIR}/ventilador.o ventilador.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/proyecto.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
