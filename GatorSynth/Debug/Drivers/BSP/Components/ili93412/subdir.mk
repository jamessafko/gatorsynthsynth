################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/ili93412/ili9341.c 

OBJS += \
./Drivers/BSP/Components/ili93412/ili9341.o 

C_DEPS += \
./Drivers/BSP/Components/ili93412/ili9341.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/ili93412/%.o: ../Drivers/BSP/Components/ili93412/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Inc" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/Components/Common2" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/Components/ili93412" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Middlewares/ST2/STemWin/inc" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/Components/stmpe811" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/STM32F429I-Discovery" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/CMSIS/Include" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


