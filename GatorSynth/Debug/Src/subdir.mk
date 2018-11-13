################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GUIConf2.c \
../Src/STemwin_wrapper2.c \
../Src/adc.c \
../Src/bsp_driver_sd.c \
../Src/crc.c \
../Src/dma.c \
../Src/dma2d.c \
../Src/fatfs.c \
../Src/fmc.c \
../Src/gpio.c \
../Src/gs_GUI.c \
../Src/i2c.c \
../Src/ltdc.c \
../Src/main.c \
../Src/sai.c \
../Src/sd_diskio.c \
../Src/sdio.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_TIM.c \
../Src/stm32f4xx_it.c \
../Src/synthesis.c \
../Src/system_stm32f4xx.c \
../Src/tim.c 

OBJS += \
./Src/GUIConf2.o \
./Src/STemwin_wrapper2.o \
./Src/adc.o \
./Src/bsp_driver_sd.o \
./Src/crc.o \
./Src/dma.o \
./Src/dma2d.o \
./Src/fatfs.o \
./Src/fmc.o \
./Src/gpio.o \
./Src/gs_GUI.o \
./Src/i2c.o \
./Src/ltdc.o \
./Src/main.o \
./Src/sai.o \
./Src/sd_diskio.o \
./Src/sdio.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_TIM.o \
./Src/stm32f4xx_it.o \
./Src/synthesis.o \
./Src/system_stm32f4xx.o \
./Src/tim.o 

C_DEPS += \
./Src/GUIConf2.d \
./Src/STemwin_wrapper2.d \
./Src/adc.d \
./Src/bsp_driver_sd.d \
./Src/crc.d \
./Src/dma.d \
./Src/dma2d.d \
./Src/fatfs.d \
./Src/fmc.d \
./Src/gpio.d \
./Src/gs_GUI.d \
./Src/i2c.d \
./Src/ltdc.d \
./Src/main.d \
./Src/sai.d \
./Src/sd_diskio.d \
./Src/sdio.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_TIM.d \
./Src/stm32f4xx_it.d \
./Src/synthesis.d \
./Src/system_stm32f4xx.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Inc" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/Components/Common2" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/Components/ili93412" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Middlewares/ST2/STemWin/inc" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/Components/stmpe811" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/BSP/STM32F429I-Discovery" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Drivers/CMSIS/Include" -I"/Users/jamessafko/Documents/ST workspace/GatorSynth/Middlewares/Third_Party/FatFs/src"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


