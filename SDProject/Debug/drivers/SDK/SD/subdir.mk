################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/SDK/SD/fsl_sd.c \
../drivers/SDK/SD/fsl_sdhc.c \
../drivers/SDK/SD/fsl_sdmmc_common.c \
../drivers/SDK/SD/fsl_sdmmc_host.c \
../drivers/SDK/SD/sdmmc_config.c 

OBJS += \
./drivers/SDK/SD/fsl_sd.o \
./drivers/SDK/SD/fsl_sdhc.o \
./drivers/SDK/SD/fsl_sdmmc_common.o \
./drivers/SDK/SD/fsl_sdmmc_host.o \
./drivers/SDK/SD/sdmmc_config.o 

C_DEPS += \
./drivers/SDK/SD/fsl_sd.d \
./drivers/SDK/SD/fsl_sdhc.d \
./drivers/SDK/SD/fsl_sdmmc_common.d \
./drivers/SDK/SD/fsl_sdmmc_host.d \
./drivers/SDK/SD/sdmmc_config.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/SDK/SD/%.o: ../drivers/SDK/SD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DSD_ENABLE -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\source\equalizer" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\CMSIS" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\startup" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\drivers" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\drivers\HAL" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\drivers\MCAL" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\drivers\SDK" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\drivers\SDK\SD" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\component\id3" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\component\lists" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\component\helix" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\component\fatfs" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\component\fatfs\fsl_sd_disk" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\board" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\source" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\source\fft" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\source\fsm" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\source\file_manager" -I"C:\Users\malem\Desktop\TPF2\TPFinal\SDProject\device" -O3 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


