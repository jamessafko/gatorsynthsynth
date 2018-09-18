################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bsp_driver_sd.c \
../Src/crc.c \
../Src/fatfs.c \
../Src/fmc.c \
../Src/gpio.c \
../Src/main.c \
../Src/sd_diskio.c \
../Src/sdio.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_TIM.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tim.c 

OBJS += \
./Src/bsp_driver_sd.o \
./Src/crc.o \
./Src/fatfs.o \
./Src/fmc.o \
./Src/gpio.o \
./Src/main.o \
./Src/sd_diskio.o \
./Src/sdio.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_TIM.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tim.o 

C_DEPS += \
./Src/bsp_driver_sd.d \
./Src/crc.d \
./Src/fatfs.d \
./Src/fmc.d \
./Src/gpio.d \
./Src/main.d \
./Src/sd_diskio.d \
./Src/sdio.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_TIM.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -DUSE_FULL_LL_DRIVER -I"/Users/jamessafko/Documents/ST workspace/gatorsynth_ground_up/Inc" -I"/Users/jamessafko/Documents/ST workspace/gatorsynth_ground_up/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/jamessafko/Documents/ST workspace/gatorsynth_ground_up/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/jamessafko/Documents/ST workspace/gatorsynth_ground_up/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/jamessafko/Documents/ST workspace/gatorsynth_ground_up/Drivers/CMSIS/Include" -I"/Users/jamessafko/Documents/ST workspace/gatorsynth_ground_up/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


