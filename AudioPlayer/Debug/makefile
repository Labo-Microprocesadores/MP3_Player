################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/sdmmc/src/subdir.mk
-include drivers/sdmmc/host/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/lists/subdir.mk
-include component/fatfs/fsl_sd_disk/subdir.mk
-include component/fatfs/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: AudioPlayer.axf

# Tool invocations
AudioPlayer.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="AudioPlayer.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T AudioPlayer_Debug.ld -o "AudioPlayer.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) AudioPlayer.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "AudioPlayer.axf"; # arm-none-eabi-objcopy -v -O binary "AudioPlayer.axf" "AudioPlayer.bin" ; # checksum -p MK64FN1M0xxx12 -d "AudioPlayer.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
