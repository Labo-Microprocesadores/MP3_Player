################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/App.c \
../source/queue.c 

OBJS += \
./source/App.o \
./source/queue.o 

C_DEPS += \
./source/App.d \
./source/queue.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DSD_ENABLE -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -D__GNUC__ -D__REDLIB__ -DDEBUG -I"D:\Facultad\GitMicros\TPFinal\SDProject" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\audio_manager" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\equalizer" -I"D:\Facultad\GitMicros\TPFinal\SDProject\CMSIS" -I"D:\Facultad\GitMicros\TPFinal\SDProject\startup" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\HAL" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\MCAL" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\SDK" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\SDK\SD" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\id3" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\lists" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\helix" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\fatfs" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Facultad\GitMicros\TPFinal\SDProject\board" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\fft" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\fsm" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\file_manager" -I"D:\Facultad\GitMicros\TPFinal\SDProject\device" -O1 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


