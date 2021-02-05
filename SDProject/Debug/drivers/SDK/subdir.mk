################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/SDK/clock_config.c \
../drivers/SDK/fsl_clock.c \
../drivers/SDK/fsl_common.c \
../drivers/SDK/fsl_dac.c \
../drivers/SDK/fsl_dmamux.c \
../drivers/SDK/fsl_dspi.c \
../drivers/SDK/fsl_edma.c \
../drivers/SDK/fsl_pdb.c \
../drivers/SDK/fsl_pmc.c \
../drivers/SDK/fsl_rcm.c \
../drivers/SDK/fsl_smc.c \
../drivers/SDK/fsl_sysmpu.c \
../drivers/SDK/power_mode_switch.c 

OBJS += \
./drivers/SDK/clock_config.o \
./drivers/SDK/fsl_clock.o \
./drivers/SDK/fsl_common.o \
./drivers/SDK/fsl_dac.o \
./drivers/SDK/fsl_dmamux.o \
./drivers/SDK/fsl_dspi.o \
./drivers/SDK/fsl_edma.o \
./drivers/SDK/fsl_pdb.o \
./drivers/SDK/fsl_pmc.o \
./drivers/SDK/fsl_rcm.o \
./drivers/SDK/fsl_smc.o \
./drivers/SDK/fsl_sysmpu.o \
./drivers/SDK/power_mode_switch.o 

C_DEPS += \
./drivers/SDK/clock_config.d \
./drivers/SDK/fsl_clock.d \
./drivers/SDK/fsl_common.d \
./drivers/SDK/fsl_dac.d \
./drivers/SDK/fsl_dmamux.d \
./drivers/SDK/fsl_dspi.d \
./drivers/SDK/fsl_edma.d \
./drivers/SDK/fsl_pdb.d \
./drivers/SDK/fsl_pmc.d \
./drivers/SDK/fsl_rcm.d \
./drivers/SDK/fsl_smc.d \
./drivers/SDK/fsl_sysmpu.d \
./drivers/SDK/power_mode_switch.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/SDK/%.o: ../drivers/SDK/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DSD_ENABLE -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Documentos\GitHub\TPFinal\SDProject" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\equalizer" -I"D:\Documentos\GitHub\TPFinal\SDProject\CMSIS" -I"D:\Documentos\GitHub\TPFinal\SDProject\startup" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\HAL" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\MCAL" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\SDK" -I"D:\Documentos\GitHub\TPFinal\SDProject\drivers\SDK\SD" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\id3" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\lists" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\helix" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\fatfs" -I"D:\Documentos\GitHub\TPFinal\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Documentos\GitHub\TPFinal\SDProject\board" -I"D:\Documentos\GitHub\TPFinal\SDProject\source" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\fft" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\fsm" -I"D:\Documentos\GitHub\TPFinal\SDProject\source\file_manager" -I"D:\Documentos\GitHub\TPFinal\SDProject\device" -O3 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

