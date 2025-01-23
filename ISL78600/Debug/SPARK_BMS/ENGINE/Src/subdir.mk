################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPARK_BMS/ENGINE/Src/database.c \
../SPARK_BMS/ENGINE/Src/fault_manager.c 

OBJS += \
./SPARK_BMS/ENGINE/Src/database.o \
./SPARK_BMS/ENGINE/Src/fault_manager.o 

C_DEPS += \
./SPARK_BMS/ENGINE/Src/database.d \
./SPARK_BMS/ENGINE/Src/fault_manager.d 


# Each subdirectory must supply rules for building sources it contributes
SPARK_BMS/ENGINE/Src/%.o SPARK_BMS/ENGINE/Src/%.su SPARK_BMS/ENGINE/Src/%.cyclo: ../SPARK_BMS/ENGINE/Src/%.c SPARK_BMS/ENGINE/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/Mddlewares/Third_Party/FatFs/src" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/App" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/Target" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/APPLICATION/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/CONFIG/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/DRIVER/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/ENGINE/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/MODULE/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SPARK_BMS-2f-ENGINE-2f-Src

clean-SPARK_BMS-2f-ENGINE-2f-Src:
	-$(RM) ./SPARK_BMS/ENGINE/Src/database.cyclo ./SPARK_BMS/ENGINE/Src/database.d ./SPARK_BMS/ENGINE/Src/database.o ./SPARK_BMS/ENGINE/Src/database.su ./SPARK_BMS/ENGINE/Src/fault_manager.cyclo ./SPARK_BMS/ENGINE/Src/fault_manager.d ./SPARK_BMS/ENGINE/Src/fault_manager.o ./SPARK_BMS/ENGINE/Src/fault_manager.su

.PHONY: clean-SPARK_BMS-2f-ENGINE-2f-Src

