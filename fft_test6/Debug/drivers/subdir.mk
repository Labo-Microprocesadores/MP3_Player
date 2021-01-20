################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_dspi.c \
../drivers/fsl_dspi_cmsis.c \
../drivers/fsl_dspi_edma.c \
../drivers/fsl_edma.c \
../drivers/fsl_enet.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_dspi.o \
./drivers/fsl_dspi_cmsis.o \
./drivers/fsl_dspi_edma.o \
./drivers/fsl_edma.o \
./drivers/fsl_enet.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_dspi.d \
./drivers/fsl_dspi_cmsis.d \
./drivers/fsl_dspi_edma.d \
./drivers/fsl_edma.d \
./drivers/fsl_enet.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Facultad\GitMicros\TpFinal\fft_test6\board" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\source" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\CMSIS_driver" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\drivers" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\utilities" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\component\serial_manager" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\component\uart" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\mdio" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\component\lists" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\phy" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\CMSIS" -I"D:\Facultad\GitMicros\TpFinal\fft_test6\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


