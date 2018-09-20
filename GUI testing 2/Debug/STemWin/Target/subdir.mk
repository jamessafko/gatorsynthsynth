################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STemWin/Target/GUIConf.c \
../STemWin/Target/LCDConf_stm32f429i_disco_MB1075.c 

OBJS += \
./STemWin/Target/GUIConf.o \
./STemWin/Target/LCDConf_stm32f429i_disco_MB1075.o 

C_DEPS += \
./STemWin/Target/GUIConf.d \
./STemWin/Target/LCDConf_stm32f429i_disco_MB1075.d 


# Each subdirectory must supply rules for building sources it contributes
STemWin/Target/%.o: ../STemWin/Target/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Inc" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/STemWin/Target" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Drivers/BSP/Components/ili9341" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Middlewares/ST/STemWin/inc" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Drivers/BSP/Components/Common" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Drivers/BSP/STM32F429I-Discovery" -I"/Users/jamessafko/Documents/ST workspace/GUI testing 2/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


