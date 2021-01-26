################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/board.c \
../source/clock_config.c \
../source/dac_continuous_pdb_edma.c \
../source/pin_mux.c \
../source/semihost_hardfault.c 

OBJS += \
./source/board.o \
./source/clock_config.o \
./source/dac_continuous_pdb_edma.o \
./source/pin_mux.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/board.d \
./source/clock_config.d \
./source/dac_continuous_pdb_edma.d \
./source/pin_mux.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\malem\Desktop\TPFinal\DACTest2\board" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\source" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\drivers" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\utilities" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\component\serial_manager" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\component\uart" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\component\lists" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\CMSIS" -I"C:\Users\malem\Desktop\TPFinal\DACTest2\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


