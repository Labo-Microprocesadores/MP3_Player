################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\board" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\startup" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\source" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\drivers" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\device" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\CMSIS" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\utilities" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\component\serial_manager" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\component\lists" -I"D:\Facultad\GitMicros\TpFinal\SDTest\LCDProject\component\uart" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


