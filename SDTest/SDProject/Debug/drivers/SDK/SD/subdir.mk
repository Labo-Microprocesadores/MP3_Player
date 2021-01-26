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
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\CMSIS" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\startup" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers\SDK" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers\SDK\SD" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\lists" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\fatfs" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\board" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\source" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\device" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\utilities" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


