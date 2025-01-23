################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SPARK_BMS/MODULE/Src/subdir.mk
-include SPARK_BMS/MODULE/Inc/subdir.mk
-include SPARK_BMS/ENGINE/Src/subdir.mk
-include SPARK_BMS/ENGINE/Inc/subdir.mk
-include SPARK_BMS/DRIVER/Src/subdir.mk
-include SPARK_BMS/DRIVER/Inc/subdir.mk
-include SPARK_BMS/CONFIG/Src/subdir.mk
-include SPARK_BMS/CONFIG/Inc/subdir.mk
-include SPARK_BMS/APPLICATION/Src/subdir.mk
-include SPARK_BMS/APPLICATION/Inc/subdir.mk
-include Mddlewares/Third_Party/FatFs/src/option/subdir.mk
-include Mddlewares/Third_Party/FatFs/src/subdir.mk
-include FATFS/Target/subdir.mk
-include FATFS/App/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ISL78600
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ISL78600.elf \

MAP_FILES += \
ISL78600.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ISL78600.list \

OBJCOPY_HEX += \
ISL78600.hex \

OBJCOPY_BIN += \
ISL78600.bin \


# All Target
all: main-build

# Main-build Target
main-build: ISL78600.elf secondary-outputs

# Tool invocations
ISL78600.elf ISL78600.map: $(OBJS) $(USER_OBJS) D:\BMS\ Firmware\Binani\ Tech\410V_8M_Binani_Tech_03_12_24_Testing\ISL78600\STM32L431RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ISL78600.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\BMS Firmware\Binani Tech\410V_8M_Binani_Tech_03_12_24_Testing\ISL78600\STM32L431RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ISL78600.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ISL78600.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ISL78600.list"
	@echo 'Finished building: $@'
	@echo ' '

ISL78600.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "ISL78600.hex"
	@echo 'Finished building: $@'
	@echo ' '

ISL78600.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ISL78600.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ISL78600.bin ISL78600.elf ISL78600.hex ISL78600.list ISL78600.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
