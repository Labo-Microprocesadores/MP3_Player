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
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\drivers\SDK" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\startup" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\osa" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\drivers\SDK\SD" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\fatfs\fsl_sd_disk" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\fatfs" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\board" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\source" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\drivers" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\device" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\CMSIS" -I"D:\Documentos\GitHub\TPFinal\SDTest\SDProject\component\lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


