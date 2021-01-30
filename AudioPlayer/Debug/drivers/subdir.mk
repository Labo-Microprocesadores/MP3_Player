################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/file_system_manager.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_dac.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_edma.c \
../drivers/fsl_gpio.c \
../drivers/fsl_pdb.c \
../drivers/fsl_sdhc.c \
../drivers/fsl_smc.c \
../drivers/memory_manager.c 

OBJS += \
./drivers/file_system_manager.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_dac.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_gpio.o \
./drivers/fsl_pdb.o \
./drivers/fsl_sdhc.o \
./drivers/fsl_smc.o \
./drivers/memory_manager.o 

C_DEPS += \
./drivers/file_system_manager.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_dac.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_gpio.d \
./drivers/fsl_pdb.d \
./drivers/fsl_sdhc.d \
./drivers/fsl_smc.d \
./drivers/memory_manager.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DSD_ENABLED -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\board" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\component\fatfs" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\drivers\sdmmc" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\source" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\drivers" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\utilities" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\component\lists" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\CMSIS" -I"D:\Facultad\GitMicros\TpFinal\AudioPlayer\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


