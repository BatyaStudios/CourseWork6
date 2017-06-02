
XOPTS = -I"c:/ti/xdctools_3_32_00_06_core/packages/" -Dxdc_target_types__=C:/ti/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages/iar/targets/arm/std.h -Dxdc_target_name__=M4F

vpath % C:/ti/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages/ti/sysbios/
vpath %.c c:/ti/xdctools_3_32_00_06_core/packages/

XDC_ROOT  = c:/ti/xdctools_3_32_00_06_core/packages/

BIOS_ROOT = C:/ti/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages/ti/sysbios/

BIOS_DEFS =  -Dti_sysbios_BIOS_swiEnabled__D=TRUE -Dti_sysbios_BIOS_taskEnabled__D=TRUE -Dti_sysbios_BIOS_clockEnabled__D=TRUE -Dti_sysbios_BIOS_runtimeCreatesEnabled__D=TRUE -Dti_sysbios_knl_Task_moduleStateCheckFlag__D=FALSE -Dti_sysbios_knl_Task_objectCheckFlag__D=FALSE -Dti_sysbios_hal_Hwi_DISABLE_ALL_HOOKS -Dti_sysbios_knl_Swi_DISABLE_ALL_HOOKS -Dti_sysbios_BIOS_smpEnabled__D=FALSE -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_knl_Swi_numPriorities__D=16 -Dti_sysbios_knl_Task_deleteTerminatedTasks__D=FALSE -Dti_sysbios_knl_Task_numPriorities__D=16 -Dti_sysbios_knl_Task_checkStackFlag__D=TRUE -Dti_sysbios_knl_Task_initStackFlag__D=TRUE -Dti_sysbios_knl_Task_DISABLE_ALL_HOOKS -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_TIMER -Dti_sysbios_knl_Clock_TICK_MODE=ti_sysbios_knl_Clock_TickMode_PERIODIC -Dti_sysbios_hal_Core_delegate_getId=ti_sysbios_hal_CoreNull_getId__E -Dti_sysbios_hal_Core_delegate_interruptCore=ti_sysbios_hal_CoreNull_interruptCore__E -Dti_sysbios_hal_Core_delegate_lock=ti_sysbios_hal_CoreNull_lock__E -Dti_sysbios_hal_Core_delegate_unlock=ti_sysbios_hal_CoreNull_unlock__E -Dti_sysbios_hal_Core_numCores__D=1 -Dti_sysbios_hal_CoreNull_numCores__D=1 -Dti_sysbios_utils_Load_taskEnabled__D=FALSE -Dti_sysbios_utils_Load_swiEnabled__D=FALSE -Dti_sysbios_utils_Load_hwiEnabled__D=FALSE -Dti_sysbios_family_arm_m3_Hwi_dispatcherSwiSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherTaskSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherAutoNestingSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherIrpTrackingSupport__D=TRUE -Dti_sysbios_knl_Semaphore_supportsEvents__D=FALSE -Dti_sysbios_knl_Semaphore_supportsPriority__D=FALSE

BIOS_INC  = -I"C:/ti/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages/"

TARGET_INC = -I"C:/ti/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages/"

INCS = $(BIOS_INC) $(TARGET_INC)   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc/CMSIS   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/driverlib/MSP432P4xx  

CCOPTS    = --aeabi --cpu=Cortex-M4F --diag_suppress=Pa050,Go005 --endian=little -e --fpu=VFPv4_sp --thumb --silent  --mfc -Ohs  -Dti_sysbios_knl_Task_minimizeLatency__D=FALSE -Dti_sysbios_knl_Clock_stopCheckNext__D=FALSE -Dti_sysbios_family_arm_m3_Hwi_enableException__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_disablePriority__D=32U -Dti_sysbios_family_arm_m3_Hwi_numSparseInterrupts__D=0U  --dlib_config E:/Programs/IAR/ARM/arm/inc/c/DLib_Config_Normal.h

CC = LC_ALL=C  E:/Programs/IAR/ARM/arm/bin/iccarm $(CCOPTS)

ASM = LC_ALL=C  E:/Programs/IAR/ARM/arm/bin/iasmarm --cpu Cortex-M4F --endian little --fpu VFPv4_sp 

AR = LC_ALL=C  E:/Programs/IAR/ARM/arm/bin/iarchive 

DEL = c:/ti/xdctools_3_32_00_06_core/packages/../bin/rm -f
CP = c:/ti/xdctools_3_32_00_06_core/packages/../bin/cp -f

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asmrm4f $< ...
	@$(ASM) $(BIOS_DEFS) $(XOPTS) $(INCS) $<
endef

all: sysbios.arm4f

m3_Hwi_asm_iar.obj: family/arm/m3/Hwi_asm_iar.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -S -o m3_Hwi_asm_iar.obj
m3_Hwi_asm_switch_iar.obj: family/arm/m3/Hwi_asm_switch_iar.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -S -o m3_Hwi_asm_switch_iar.obj
m3_IntrinsicsSupport_asm_iar.obj: family/arm/m3/IntrinsicsSupport_asm_iar.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -S -o m3_IntrinsicsSupport_asm_iar.obj
m3_TaskSupport_asm_iar.obj: family/arm/m3/TaskSupport_asm_iar.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -S -o m3_TaskSupport_asm_iar.obj

BIOS.o: BIOS.c knl/Clock.c knl/Idle.c knl/Intrinsics.c knl/Event.c knl/Queue.c knl/Semaphore.c knl/Swi.c knl/Swi_andn.c knl/Task.c hal/Hwi.c hal/Hwi_stack.c hal/Hwi_startup.c family/arm/msp432/init/Boot.c family/arm/m3/Hwi.c family/arm/m3/TaskSupport.c family/arm/m3/Timer.c family/arm/m3/TimestampProvider.c gates/GateHwi.c gates/GateMutex.c heaps/HeapMem.c utils/Load.c utils/Load_CPU.c family/arm/msp432/Timer.c family/arm/msp432/ClockFreqs.c makefile
	@-$(call RM, BIOS.o)
	@echo clrm4f $< ...
	@$(CC) -o BIOS.o $(BIOS_DEFS) $(XOPTS) $(INCS) \
	$(BIOS_ROOT)BIOS.c \
	$(BIOS_ROOT)knl/Clock.c \
	$(BIOS_ROOT)knl/Idle.c \
	$(BIOS_ROOT)knl/Intrinsics.c \
	$(BIOS_ROOT)knl/Event.c \
	$(BIOS_ROOT)knl/Queue.c \
	$(BIOS_ROOT)knl/Semaphore.c \
	$(BIOS_ROOT)knl/Swi.c \
	$(BIOS_ROOT)knl/Swi_andn.c \
	$(BIOS_ROOT)knl/Task.c \
	$(BIOS_ROOT)hal/Hwi.c \
	$(BIOS_ROOT)hal/Hwi_stack.c \
	$(BIOS_ROOT)hal/Hwi_startup.c \
	$(BIOS_ROOT)family/arm/msp432/init/Boot.c \
	$(BIOS_ROOT)family/arm/m3/Hwi.c \
	$(BIOS_ROOT)family/arm/m3/TaskSupport.c \
	$(BIOS_ROOT)family/arm/m3/Timer.c \
	$(BIOS_ROOT)family/arm/m3/TimestampProvider.c \
	$(BIOS_ROOT)gates/GateHwi.c \
	$(BIOS_ROOT)gates/GateMutex.c \
	$(BIOS_ROOT)heaps/HeapMem.c \
	$(BIOS_ROOT)utils/Load.c \
	$(BIOS_ROOT)utils/Load_CPU.c \
	$(BIOS_ROOT)family/arm/msp432/Timer.c \
	$(BIOS_ROOT)family/arm/msp432/ClockFreqs.c \

sysbios.arm4f: BIOS.o m3_Hwi_asm_iar.obj m3_Hwi_asm_switch_iar.obj m3_IntrinsicsSupport_asm_iar.obj m3_TaskSupport_asm_iar.obj
	@echo arrm4f $^ ...
	@-$(call RM, $@)
	@$(AR) $@ $^


clean:
	@$(DEL) ..\makefile.libs
	@-$(call RM, *)

