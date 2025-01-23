################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPARK_BMS/CONFIG/Src/adc_cfg.c \
../SPARK_BMS/CONFIG/Src/bq76pl455_cfg.c \
../SPARK_BMS/CONFIG/Src/can_cfg.c \
../SPARK_BMS/CONFIG/Src/database_cfg.c \
../SPARK_BMS/CONFIG/Src/dma_cfg.c \
../SPARK_BMS/CONFIG/Src/gpio_cfg.c \
../SPARK_BMS/CONFIG/Src/i2c_cfg.c \
../SPARK_BMS/CONFIG/Src/nvic_cfg.c \
../SPARK_BMS/CONFIG/Src/rcc_cfg.c \
../SPARK_BMS/CONFIG/Src/rtc_cfg.c \
../SPARK_BMS/CONFIG/Src/spi_cfg.c \
../SPARK_BMS/CONFIG/Src/timer_cfg.c \
../SPARK_BMS/CONFIG/Src/uart_cfg.c \
../SPARK_BMS/CONFIG/Src/wwdg_cfg.c 

OBJS += \
./SPARK_BMS/CONFIG/Src/adc_cfg.o \
./SPARK_BMS/CONFIG/Src/bq76pl455_cfg.o \
./SPARK_BMS/CONFIG/Src/can_cfg.o \
./SPARK_BMS/CONFIG/Src/database_cfg.o \
./SPARK_BMS/CONFIG/Src/dma_cfg.o \
./SPARK_BMS/CONFIG/Src/gpio_cfg.o \
./SPARK_BMS/CONFIG/Src/i2c_cfg.o \
./SPARK_BMS/CONFIG/Src/nvic_cfg.o \
./SPARK_BMS/CONFIG/Src/rcc_cfg.o \
./SPARK_BMS/CONFIG/Src/rtc_cfg.o \
./SPARK_BMS/CONFIG/Src/spi_cfg.o \
./SPARK_BMS/CONFIG/Src/timer_cfg.o \
./SPARK_BMS/CONFIG/Src/uart_cfg.o \
./SPARK_BMS/CONFIG/Src/wwdg_cfg.o 

C_DEPS += \
./SPARK_BMS/CONFIG/Src/adc_cfg.d \
./SPARK_BMS/CONFIG/Src/bq76pl455_cfg.d \
./SPARK_BMS/CONFIG/Src/can_cfg.d \
./SPARK_BMS/CONFIG/Src/database_cfg.d \
./SPARK_BMS/CONFIG/Src/dma_cfg.d \
./SPARK_BMS/CONFIG/Src/gpio_cfg.d \
./SPARK_BMS/CONFIG/Src/i2c_cfg.d \
./SPARK_BMS/CONFIG/Src/nvic_cfg.d \
./SPARK_BMS/CONFIG/Src/rcc_cfg.d \
./SPARK_BMS/CONFIG/Src/rtc_cfg.d \
./SPARK_BMS/CONFIG/Src/spi_cfg.d \
./SPARK_BMS/CONFIG/Src/timer_cfg.d \
./SPARK_BMS/CONFIG/Src/uart_cfg.d \
./SPARK_BMS/CONFIG/Src/wwdg_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
SPARK_BMS/CONFIG/Src/%.o SPARK_BMS/CONFIG/Src/%.su SPARK_BMS/CONFIG/Src/%.cyclo: ../SPARK_BMS/CONFIG/Src/%.c SPARK_BMS/CONFIG/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/Mddlewares/Third_Party/FatFs/src" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/App" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/Target" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/APPLICATION/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/CONFIG/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/DRIVER/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/ENGINE/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/MODULE/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SPARK_BMS-2f-CONFIG-2f-Src

clean-SPARK_BMS-2f-CONFIG-2f-Src:
	-$(RM) ./SPARK_BMS/CONFIG/Src/adc_cfg.cyclo ./SPARK_BMS/CONFIG/Src/adc_cfg.d ./SPARK_BMS/CONFIG/Src/adc_cfg.o ./SPARK_BMS/CONFIG/Src/adc_cfg.su ./SPARK_BMS/CONFIG/Src/bq76pl455_cfg.cyclo ./SPARK_BMS/CONFIG/Src/bq76pl455_cfg.d ./SPARK_BMS/CONFIG/Src/bq76pl455_cfg.o ./SPARK_BMS/CONFIG/Src/bq76pl455_cfg.su ./SPARK_BMS/CONFIG/Src/can_cfg.cyclo ./SPARK_BMS/CONFIG/Src/can_cfg.d ./SPARK_BMS/CONFIG/Src/can_cfg.o ./SPARK_BMS/CONFIG/Src/can_cfg.su ./SPARK_BMS/CONFIG/Src/database_cfg.cyclo ./SPARK_BMS/CONFIG/Src/database_cfg.d ./SPARK_BMS/CONFIG/Src/database_cfg.o ./SPARK_BMS/CONFIG/Src/database_cfg.su ./SPARK_BMS/CONFIG/Src/dma_cfg.cyclo ./SPARK_BMS/CONFIG/Src/dma_cfg.d ./SPARK_BMS/CONFIG/Src/dma_cfg.o ./SPARK_BMS/CONFIG/Src/dma_cfg.su ./SPARK_BMS/CONFIG/Src/gpio_cfg.cyclo ./SPARK_BMS/CONFIG/Src/gpio_cfg.d ./SPARK_BMS/CONFIG/Src/gpio_cfg.o ./SPARK_BMS/CONFIG/Src/gpio_cfg.su ./SPARK_BMS/CONFIG/Src/i2c_cfg.cyclo ./SPARK_BMS/CONFIG/Src/i2c_cfg.d ./SPARK_BMS/CONFIG/Src/i2c_cfg.o ./SPARK_BMS/CONFIG/Src/i2c_cfg.su ./SPARK_BMS/CONFIG/Src/nvic_cfg.cyclo ./SPARK_BMS/CONFIG/Src/nvic_cfg.d ./SPARK_BMS/CONFIG/Src/nvic_cfg.o ./SPARK_BMS/CONFIG/Src/nvic_cfg.su ./SPARK_BMS/CONFIG/Src/rcc_cfg.cyclo ./SPARK_BMS/CONFIG/Src/rcc_cfg.d ./SPARK_BMS/CONFIG/Src/rcc_cfg.o ./SPARK_BMS/CONFIG/Src/rcc_cfg.su ./SPARK_BMS/CONFIG/Src/rtc_cfg.cyclo ./SPARK_BMS/CONFIG/Src/rtc_cfg.d ./SPARK_BMS/CONFIG/Src/rtc_cfg.o ./SPARK_BMS/CONFIG/Src/rtc_cfg.su ./SPARK_BMS/CONFIG/Src/spi_cfg.cyclo ./SPARK_BMS/CONFIG/Src/spi_cfg.d ./SPARK_BMS/CONFIG/Src/spi_cfg.o ./SPARK_BMS/CONFIG/Src/spi_cfg.su ./SPARK_BMS/CONFIG/Src/timer_cfg.cyclo ./SPARK_BMS/CONFIG/Src/timer_cfg.d ./SPARK_BMS/CONFIG/Src/timer_cfg.o ./SPARK_BMS/CONFIG/Src/timer_cfg.su ./SPARK_BMS/CONFIG/Src/uart_cfg.cyclo ./SPARK_BMS/CONFIG/Src/uart_cfg.d ./SPARK_BMS/CONFIG/Src/uart_cfg.o ./SPARK_BMS/CONFIG/Src/uart_cfg.su ./SPARK_BMS/CONFIG/Src/wwdg_cfg.cyclo ./SPARK_BMS/CONFIG/Src/wwdg_cfg.d ./SPARK_BMS/CONFIG/Src/wwdg_cfg.o ./SPARK_BMS/CONFIG/Src/wwdg_cfg.su

.PHONY: clean-SPARK_BMS-2f-CONFIG-2f-Src

