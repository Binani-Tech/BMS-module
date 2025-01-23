################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPARK_BMS/DRIVER/Src/adc.c \
../SPARK_BMS/DRIVER/Src/can.c \
../SPARK_BMS/DRIVER/Src/dma.c \
../SPARK_BMS/DRIVER/Src/fatfs_sd.c \
../SPARK_BMS/DRIVER/Src/gpio.c \
../SPARK_BMS/DRIVER/Src/i2c.c \
../SPARK_BMS/DRIVER/Src/nvic.c \
../SPARK_BMS/DRIVER/Src/rcc.c \
../SPARK_BMS/DRIVER/Src/rtc.c \
../SPARK_BMS/DRIVER/Src/spi.c \
../SPARK_BMS/DRIVER/Src/timer.c \
../SPARK_BMS/DRIVER/Src/uart.c 

OBJS += \
./SPARK_BMS/DRIVER/Src/adc.o \
./SPARK_BMS/DRIVER/Src/can.o \
./SPARK_BMS/DRIVER/Src/dma.o \
./SPARK_BMS/DRIVER/Src/fatfs_sd.o \
./SPARK_BMS/DRIVER/Src/gpio.o \
./SPARK_BMS/DRIVER/Src/i2c.o \
./SPARK_BMS/DRIVER/Src/nvic.o \
./SPARK_BMS/DRIVER/Src/rcc.o \
./SPARK_BMS/DRIVER/Src/rtc.o \
./SPARK_BMS/DRIVER/Src/spi.o \
./SPARK_BMS/DRIVER/Src/timer.o \
./SPARK_BMS/DRIVER/Src/uart.o 

C_DEPS += \
./SPARK_BMS/DRIVER/Src/adc.d \
./SPARK_BMS/DRIVER/Src/can.d \
./SPARK_BMS/DRIVER/Src/dma.d \
./SPARK_BMS/DRIVER/Src/fatfs_sd.d \
./SPARK_BMS/DRIVER/Src/gpio.d \
./SPARK_BMS/DRIVER/Src/i2c.d \
./SPARK_BMS/DRIVER/Src/nvic.d \
./SPARK_BMS/DRIVER/Src/rcc.d \
./SPARK_BMS/DRIVER/Src/rtc.d \
./SPARK_BMS/DRIVER/Src/spi.d \
./SPARK_BMS/DRIVER/Src/timer.d \
./SPARK_BMS/DRIVER/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
SPARK_BMS/DRIVER/Src/%.o SPARK_BMS/DRIVER/Src/%.su SPARK_BMS/DRIVER/Src/%.cyclo: ../SPARK_BMS/DRIVER/Src/%.c SPARK_BMS/DRIVER/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/Mddlewares/Third_Party/FatFs/src" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/App" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/Target" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/APPLICATION/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/CONFIG/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/DRIVER/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/ENGINE/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/MODULE/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SPARK_BMS-2f-DRIVER-2f-Src

clean-SPARK_BMS-2f-DRIVER-2f-Src:
	-$(RM) ./SPARK_BMS/DRIVER/Src/adc.cyclo ./SPARK_BMS/DRIVER/Src/adc.d ./SPARK_BMS/DRIVER/Src/adc.o ./SPARK_BMS/DRIVER/Src/adc.su ./SPARK_BMS/DRIVER/Src/can.cyclo ./SPARK_BMS/DRIVER/Src/can.d ./SPARK_BMS/DRIVER/Src/can.o ./SPARK_BMS/DRIVER/Src/can.su ./SPARK_BMS/DRIVER/Src/dma.cyclo ./SPARK_BMS/DRIVER/Src/dma.d ./SPARK_BMS/DRIVER/Src/dma.o ./SPARK_BMS/DRIVER/Src/dma.su ./SPARK_BMS/DRIVER/Src/fatfs_sd.cyclo ./SPARK_BMS/DRIVER/Src/fatfs_sd.d ./SPARK_BMS/DRIVER/Src/fatfs_sd.o ./SPARK_BMS/DRIVER/Src/fatfs_sd.su ./SPARK_BMS/DRIVER/Src/gpio.cyclo ./SPARK_BMS/DRIVER/Src/gpio.d ./SPARK_BMS/DRIVER/Src/gpio.o ./SPARK_BMS/DRIVER/Src/gpio.su ./SPARK_BMS/DRIVER/Src/i2c.cyclo ./SPARK_BMS/DRIVER/Src/i2c.d ./SPARK_BMS/DRIVER/Src/i2c.o ./SPARK_BMS/DRIVER/Src/i2c.su ./SPARK_BMS/DRIVER/Src/nvic.cyclo ./SPARK_BMS/DRIVER/Src/nvic.d ./SPARK_BMS/DRIVER/Src/nvic.o ./SPARK_BMS/DRIVER/Src/nvic.su ./SPARK_BMS/DRIVER/Src/rcc.cyclo ./SPARK_BMS/DRIVER/Src/rcc.d ./SPARK_BMS/DRIVER/Src/rcc.o ./SPARK_BMS/DRIVER/Src/rcc.su ./SPARK_BMS/DRIVER/Src/rtc.cyclo ./SPARK_BMS/DRIVER/Src/rtc.d ./SPARK_BMS/DRIVER/Src/rtc.o ./SPARK_BMS/DRIVER/Src/rtc.su ./SPARK_BMS/DRIVER/Src/spi.cyclo ./SPARK_BMS/DRIVER/Src/spi.d ./SPARK_BMS/DRIVER/Src/spi.o ./SPARK_BMS/DRIVER/Src/spi.su ./SPARK_BMS/DRIVER/Src/timer.cyclo ./SPARK_BMS/DRIVER/Src/timer.d ./SPARK_BMS/DRIVER/Src/timer.o ./SPARK_BMS/DRIVER/Src/timer.su ./SPARK_BMS/DRIVER/Src/uart.cyclo ./SPARK_BMS/DRIVER/Src/uart.d ./SPARK_BMS/DRIVER/Src/uart.o ./SPARK_BMS/DRIVER/Src/uart.su

.PHONY: clean-SPARK_BMS-2f-DRIVER-2f-Src

