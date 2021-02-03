################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/hardware.c \
../startup/main.c \
../startup/semihost_hardfault.c \
../startup/startup_mk64f12.c 

OBJS += \
./startup/hardware.o \
./startup/main.o \
./startup/semihost_hardfault.o \
./startup/startup_mk64f12.o 

C_DEPS += \
./startup/hardware.d \
./startup/main.d \
./startup/semihost_hardfault.d \
./startup/startup_mk64f12.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DSD_ENABLE -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\CMSIS" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\startup" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers\HAL" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers\MCAL" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers\SDK" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\drivers\SDK\SD" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\id3" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\lists" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\helix" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\fatfs" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\board" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\source" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\source\fft" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\source\fsm" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\source\file_manager" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\device" -I"D:\Facultad\GitMicros\TpFinal\SDTest\SDProject\utilities" -O3 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


