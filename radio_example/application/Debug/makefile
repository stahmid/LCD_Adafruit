################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/msp430_4.3.3

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./mmc.obj" \
"./parser.obj" \
"./pff.obj" \
"./radio.obj" \
"./radio_methods.obj" \
"./usci_spi.obj" \
"./mrfi/mrfi.obj" \
"./bsp/bsp.obj" \
"../lnk_msp430f2274.cmd" \
-l"rts430.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include mrfi/subdir_vars.mk
-include bsp/subdir_vars.mk
-include subdir_rules.mk
-include mrfi/subdir_rules.mk
-include bsp/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
radio_example.out \

EXE_OUTPUTS__QUOTED += \
"radio_example.out" \

BIN_OUTPUTS += \
radio_example.hex \

BIN_OUTPUTS__QUOTED += \
"radio_example.hex" \


# All Target
all: radio_example.out

# Tool invocations
radio_example.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal -z -m"radio_example.map" --heap_size=80 --stack_size=80 -i"c:/ti/ccsv6/ccs_base/msp430/include" -i"c:/ti/ccsv6/msp430/include" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/lib" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --reread_libs --warn_sections --xml_link_info="radio_example_linkInfo.xml" --rom_model -o "radio_example.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

radio_example.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/hex430" --memwidth=8 --romwidth=8 -o "radio_example.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "mmc.pp" "parser.pp" "pff.pp" "radio.pp" "radio_methods.pp" "usci_spi.pp" "mrfi\mrfi.pp" "bsp\bsp.pp" 
	-$(RM) "main.obj" "mmc.obj" "parser.obj" "pff.obj" "radio.obj" "radio_methods.obj" "usci_spi.obj" "mrfi\mrfi.obj" "bsp\bsp.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

