################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
mrfi/mrfi.obj: ../mrfi/mrfi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="mrfi/mrfi.pp" --obj_directory="mrfi" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


