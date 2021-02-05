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
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DSD_ENABLE -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Documentos\GitHub\TPFinal\SDProject" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\equalizer" -I"D:\Documentos\GitHub\TPFinal\SDProject\CMSIS" -I"D:\Documentos\GitHub\TPFinal\SDProject\startup" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\HAL" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\MCAL" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\SDK" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\SDK\SD" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\id3" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\lists" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\helix" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\fatfs" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Documentos\GitHub\TPFinal\SDProject\board" -I"D:\Documentos\GitHub\TPFinal\SDProject\source" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\fft" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\fsm" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\file_manager" -I"D:\Documentos\GitHub\TPFinal\SDProject\device" -O3 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


