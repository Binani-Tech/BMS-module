################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPARK_BMS/MODULE/Src/adc_exp.c \
../SPARK_BMS/MODULE/Src/afe.c \
../SPARK_BMS/MODULE/Src/ble.c \
../SPARK_BMS/MODULE/Src/contactor.c \
../SPARK_BMS/MODULE/Src/crc.c \
../SPARK_BMS/MODULE/Src/current.c \
../SPARK_BMS/MODULE/Src/eeprom.c \
../SPARK_BMS/MODULE/Src/sd_card.c 

OBJS += \
./SPARK_BMS/MODULE/Src/adc_exp.o \
./SPARK_BMS/MODULE/Src/afe.o \
./SPARK_BMS/MODULE/Src/ble.o \
./SPARK_BMS/MODULE/Src/contactor.o \
./SPARK_BMS/MODULE/Src/crc.o \
./SPARK_BMS/MODULE/Src/current.o \
./SPARK_BMS/MODULE/Src/eeprom.o \
./SPARK_BMS/MODULE/Src/sd_card.o 

C_DEPS += \
./SPARK_BMS/MODULE/Src/adc_exp.d \
./SPARK_BMS/MODULE/Src/afe.d \
./SPARK_BMS/MODULE/Src/ble.d \
./SPARK_BMS/MODULE/Src/contactor.d \
./SPARK_BMS/MODULE/Src/crc.d \
./SPARK_BMS/MODULE/Src/current.d \
./SPARK_BMS/MODULE/Src/eeprom.d \
./SPARK_BMS/MODULE/Src/sd_card.d 


# Each subdirectory must supply rules for building sources it contributes
SPARK_BMS/MODULE/Src/%.o SPARK_BMS/MODULE/Src/%.su SPARK_BMS/MODULE/Src/%.cyclo: ../SPARK_BMS/MODULE/Src/%.c SPARK_BMS/MODULE/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/Mddlewares/Third_Party/FatFs/src" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/App" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/Target" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/APPLICATION/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/CONFIG/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/DRIVER/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/ENGINE/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/MODULE/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SPARK_BMS-2f-MODULE-2f-Src

clean-SPARK_BMS-2f-MODULE-2f-Src:
	-$(RM) ./SPARK_BMS/MODULE/Src/adc_exp.cyclo ./SPARK_BMS/MODULE/Src/adc_exp.d ./SPARK_BMS/MODULE/Src/adc_exp.o ./SPARK_BMS/MODULE/Src/adc_exp.su ./SPARK_BMS/MODULE/Src/afe.cyclo ./SPARK_BMS/MODULE/Src/afe.d ./SPARK_BMS/MODULE/Src/afe.o ./SPARK_BMS/MODULE/Src/afe.su ./SPARK_BMS/MODULE/Src/ble.cyclo ./SPARK_BMS/MODULE/Src/ble.d ./SPARK_BMS/MODULE/Src/ble.o ./SPARK_BMS/MODULE/Src/ble.su ./SPARK_BMS/MODULE/Src/contactor.cyclo ./SPARK_BMS/MODULE/Src/contactor.d ./SPARK_BMS/MODULE/Src/contactor.o ./SPARK_BMS/MODULE/Src/contactor.su ./SPARK_BMS/MODULE/Src/crc.cyclo ./SPARK_BMS/MODULE/Src/crc.d ./SPARK_BMS/MODULE/Src/crc.o ./SPARK_BMS/MODULE/Src/crc.su ./SPARK_BMS/MODULE/Src/current.cyclo ./SPARK_BMS/MODULE/Src/current.d ./SPARK_BMS/MODULE/Src/current.o ./SPARK_BMS/MODULE/Src/current.su ./SPARK_BMS/MODULE/Src/eeprom.cyclo ./SPARK_BMS/MODULE/Src/eeprom.d ./SPARK_BMS/MODULE/Src/eeprom.o ./SPARK_BMS/MODULE/Src/eeprom.su ./SPARK_BMS/MODULE/Src/sd_card.cyclo ./SPARK_BMS/MODULE/Src/sd_card.d ./SPARK_BMS/MODULE/Src/sd_card.o ./SPARK_BMS/MODULE/Src/sd_card.su

.PHONY: clean-SPARK_BMS-2f-MODULE-2f-Src

