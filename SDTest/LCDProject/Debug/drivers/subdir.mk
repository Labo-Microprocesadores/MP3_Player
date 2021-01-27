################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/LCD_GDM1602A.c \
../drivers/SPI_wrapper.c \
../drivers/SysTick.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_dspi.c 

OBJS += \
./drivers/LCD_GDM1602A.o \
./drivers/SPI_wrapper.o \
./drivers/SysTick.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_dspi.o 

C_DEPS += \
./drivers/LCD_GDM1602A.d \
./drivers/SPI_wrapper.d \
./drivers/SysTick.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_dspi.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\board" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\startup" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\source" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\drivers" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\device" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\CMSIS" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\utilities" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\component\lists" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


