################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/SDK/fsl_adc16.c \
../drivers/SDK/fsl_clock.c \
../drivers/SDK/fsl_common.c \
../drivers/SDK/fsl_gpio.c \
../drivers/SDK/fsl_i2c.c \
../drivers/SDK/fsl_smc.c \
../drivers/SDK/fsl_sysmpu.c \
../drivers/SDK/fsl_uart.c 

OBJS += \
./drivers/SDK/fsl_adc16.o \
./drivers/SDK/fsl_clock.o \
./drivers/SDK/fsl_common.o \
./drivers/SDK/fsl_gpio.o \
./drivers/SDK/fsl_i2c.o \
./drivers/SDK/fsl_smc.o \
./drivers/SDK/fsl_sysmpu.o \
./drivers/SDK/fsl_uart.o 

C_DEPS += \
./drivers/SDK/fsl_adc16.d \
./drivers/SDK/fsl_clock.d \
./drivers/SDK/fsl_common.d \
./drivers/SDK/fsl_gpio.d \
./drivers/SDK/fsl_i2c.d \
./drivers/SDK/fsl_smc.d \
./drivers/SDK/fsl_sysmpu.d \
./drivers/SDK/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/SDK/%.o: ../drivers/SDK/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\drivers\SDK" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\startup" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\osa" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\drivers\SDK\SD" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\fatfs" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\board" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\source" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\drivers" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\device" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\CMSIS" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


