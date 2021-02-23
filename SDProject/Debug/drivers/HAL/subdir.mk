################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/HAL/AudioPlayer.c \
../drivers/HAL/LCD_GDM1602A.c \
../drivers/HAL/SPI_wrapper.c \
../drivers/HAL/Timer.c \
../drivers/HAL/button.c \
../drivers/HAL/decoder.c \
../drivers/HAL/encoder.c \
../drivers/HAL/esp_comunication.c \
../drivers/HAL/matrix_display.c \
../drivers/HAL/memory_manager.c \
../drivers/HAL/time_service.c 

OBJS += \
./drivers/HAL/AudioPlayer.o \
./drivers/HAL/LCD_GDM1602A.o \
./drivers/HAL/SPI_wrapper.o \
./drivers/HAL/Timer.o \
./drivers/HAL/button.o \
./drivers/HAL/decoder.o \
./drivers/HAL/encoder.o \
./drivers/HAL/esp_comunication.o \
./drivers/HAL/matrix_display.o \
./drivers/HAL/memory_manager.o \
./drivers/HAL/time_service.o 

C_DEPS += \
./drivers/HAL/AudioPlayer.d \
./drivers/HAL/LCD_GDM1602A.d \
./drivers/HAL/SPI_wrapper.d \
./drivers/HAL/Timer.d \
./drivers/HAL/button.d \
./drivers/HAL/decoder.d \
./drivers/HAL/encoder.d \
./drivers/HAL/esp_comunication.d \
./drivers/HAL/matrix_display.d \
./drivers/HAL/memory_manager.d \
./drivers/HAL/time_service.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/HAL/%.o: ../drivers/HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DSD_ENABLE -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -D__GNUC__ -D__REDLIB__ -DDEBUG -I"D:\Facultad\GitMicros\TPFinal\SDProject" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\audio_manager" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\equalizer" -I"D:\Facultad\GitMicros\TPFinal\SDProject\CMSIS" -I"D:\Facultad\GitMicros\TPFinal\SDProject\startup" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\HAL" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\MCAL" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\SDK" -I"D:\Facultad\GitMicros\TPFinal\SDProject\drivers\SDK\SD" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\id3" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\lists" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\helix" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\fatfs" -I"D:\Facultad\GitMicros\TPFinal\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Facultad\GitMicros\TPFinal\SDProject\board" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\fft" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\fsm" -I"D:\Facultad\GitMicros\TPFinal\SDProject\source\file_manager" -I"D:\Facultad\GitMicros\TPFinal\SDProject\device" -O1 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


