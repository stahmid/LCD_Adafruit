################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mmc.obj: ../mmc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="mmc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

parser.obj: ../parser.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="parser.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pff.obj: ../pff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="pff.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

radio.obj: ../radio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="radio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

radio_methods.obj: ../radio_methods.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="radio_methods.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usci_spi.obj: ../usci_spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -Ooff --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/drivers" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/common" --include_path="C:/Users/Manish Patel/workspace_v6_0/radio_example/radio_example/drivers/mrfi/radios/family1" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="usci_spi.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


