################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GUIConf2.c \
../Src/GUI_App2.c \
../Src/STemwin_wrapper2.c \
../Src/codec.c \
../Src/crc.c \
../Src/dma2d.c \
../Src/fmc.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/ltdc.c \
../Src/main.c \
../Src/menu1DLG.c \
../Src/menu2DLG.c \
../Src/sai.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_TIM.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/GUIConf2.o \
./Src/GUI_App2.o \
./Src/STemwin_wrapper2.o \
./Src/codec.o \
./Src/crc.o \
./Src/dma2d.o \
./Src/fmc.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/ltdc.o \
./Src/main.o \
./Src/menu1DLG.o \
./Src/menu2DLG.o \
./Src/sai.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_TIM.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/GUIConf2.d \
./Src/GUI_App2.d \
./Src/STemwin_wrapper2.d \
./Src/codec.d \
./Src/crc.d \
./Src/dma2d.d \
./Src/fmc.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/ltdc.d \
./Src/main.d \
./Src/menu1DLG.d \
./Src/menu2DLG.d \
./Src/sai.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_TIM.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/Users/jamessafko/Documents/ST workspace/mreh/Inc" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/BSP/Components/Common2" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/BSP/Components/ili93412" -I"/Users/jamessafko/Documents/ST workspace/mreh/Middlewares/ST2/STemWin/inc" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/BSP/Components/stmpe811" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/BSP/STM32F429I-Discovery" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/jamessafko/Documents/ST workspace/mreh/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

