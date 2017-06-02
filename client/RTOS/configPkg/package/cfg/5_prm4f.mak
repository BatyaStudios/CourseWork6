#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = iar.targets.arm.M4F{1,0,7.50,2
#
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/5_prm4f.orm4f.dep
package/cfg/5_prm4f.orm4f.dep: ;
endif

package/cfg/5_prm4f.orm4f: | .interfaces
package/cfg/5_prm4f.orm4f: package/cfg/5_prm4f.c package/cfg/5_prm4f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4f $< ...
	LC_ALL=C $(iar.targets.arm.M4F.rootDir)/bin/iccarm    -D NODEBUG   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc/CMSIS   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/driverlib/MSP432P4xx   -D__MSP432P401R__   -Dewarm   -DMSP432WARE   --silent --aeabi --cpu=Cortex-M4F --diag_suppress=Pa050,Go005 --endian=little -e --fpu=VFPv4_sp --thumb   -Dxdc_cfg__xheader__='"configPkg/package/cfg/5_prm4f.h"'  -Dxdc_target_name__=M4F -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_50_2 -Ohs --dlib_config $(iar.targets.arm.M4F.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/cfg/5_prm4f.srm4f: | .interfaces
package/cfg/5_prm4f.srm4f: package/cfg/5_prm4f.c package/cfg/5_prm4f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4f $< ...
	LC_ALL=C $(iar.targets.arm.M4F.rootDir)/bin/iccarm    -D NODEBUG   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc/CMSIS   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc   -Ic:/ti/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/driverlib/MSP432P4xx   -D__MSP432P401R__   -Dewarm   -DMSP432WARE   --silent --aeabi --cpu=Cortex-M4F --diag_suppress=Pa050,Go005 --endian=little -e --fpu=VFPv4_sp --thumb   -Dxdc_cfg__xheader__='"configPkg/package/cfg/5_prm4f.h"'  -Dxdc_target_name__=M4F -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_50_2 -Ohs --dlib_config $(iar.targets.arm.M4F.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

clean,rm4f ::
	-$(RM) package/cfg/5_prm4f.orm4f
	-$(RM) package/cfg/5_prm4f.srm4f

5.prm4f: package/cfg/5_prm4f.orm4f package/cfg/5_prm4f.mak

clean::
	-$(RM) package/cfg/5_prm4f.mak