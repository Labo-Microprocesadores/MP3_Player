################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/serial_manager.c \
../component/serial_manager/serial_port_uart.c 

OBJS += \
./component/serial_manager/serial_manager.o \
./component/serial_manager/serial_port_uart.o 

C_DEPS += \
./component/serial_manager/serial_manager.d \
./component/serial_manager/serial_port_uart.d 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DSD_ENABLED -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\board" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\source" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\drivers" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\device" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\CMSIS" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\sdmmc\inc" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\sdmmc\host" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\sdmmc\osa" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\component\osa" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\component\lists" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\fatfs\source" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\fatfs\source\fsl_ram_disk" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\fatfs\source\fsl_sd_disk" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\utilities" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\component\serial_manager" -I"D:\Facultad\4to\Labo Micros\MCUProyects\SDTest\frdmk64f_sdcard_fatfs\component\uart" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


