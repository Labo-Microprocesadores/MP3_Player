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
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\board" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\startup" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\source" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\drivers" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\device" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\CMSIS" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\utilities" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\component\lists" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

