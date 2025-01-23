################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPARK_BMS/APPLICATION/Src/balancing.c \
../SPARK_BMS/APPLICATION/Src/bq76pl455.c \
../SPARK_BMS/APPLICATION/Src/fault_cfg.c \
../SPARK_BMS/APPLICATION/Src/fault_monitor.c \
../SPARK_BMS/APPLICATION/Src/shortcircuit.c \
../SPARK_BMS/APPLICATION/Src/soc.c 

OBJS += \
./SPARK_BMS/APPLICATION/Src/balancing.o \
./SPARK_BMS/APPLICATION/Src/bq76pl455.o \
./SPARK_BMS/APPLICATION/Src/fault_cfg.o \
./SPARK_BMS/APPLICATION/Src/fault_monitor.o \
./SPARK_BMS/APPLICATION/Src/shortcircuit.o \
./SPARK_BMS/APPLICATION/Src/soc.o 

C_DEPS += \
./SPARK_BMS/APPLICATION/Src/balancing.d \
./SPARK_BMS/APPLICATION/Src/bq76pl455.d \
./SPARK_BMS/APPLICATION/Src/fault_cfg.d \
./SPARK_BMS/APPLICATION/Src/fault_monitor.d \
./SPARK_BMS/APPLICATION/Src/shortcircuit.d \
./SPARK_BMS/APPLICATION/Src/soc.d 


# Each subdirectory must supply rules for building sources it contributes
SPARK_BMS/APPLICATION/Src/%.o SPARK_BMS/APPLICATION/Src/%.su SPARK_BMS/APPLICATION/Src/%.cyclo: ../SPARK_BMS/APPLICATION/Src/%.c SPARK_BMS/APPLICATION/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/Mddlewares/Third_Party/FatFs/src" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/App" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/Target" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/APPLICATION/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/CONFIG/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/DRIVER/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/ENGINE/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/MODULE/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SPARK_BMS-2f-APPLICATION-2f-Src

clean-SPARK_BMS-2f-APPLICATION-2f-Src:
	-$(RM) ./SPARK_BMS/APPLICATION/Src/balancing.cyclo ./SPARK_BMS/APPLICATION/Src/balancing.d ./SPARK_BMS/APPLICATION/Src/balancing.o ./SPARK_BMS/APPLICATION/Src/balancing.su ./SPARK_BMS/APPLICATION/Src/bq76pl455.cyclo ./SPARK_BMS/APPLICATION/Src/bq76pl455.d ./SPARK_BMS/APPLICATION/Src/bq76pl455.o ./SPARK_BMS/APPLICATION/Src/bq76pl455.su ./SPARK_BMS/APPLICATION/Src/fault_cfg.cyclo ./SPARK_BMS/APPLICATION/Src/fault_cfg.d ./SPARK_BMS/APPLICATION/Src/fault_cfg.o ./SPARK_BMS/APPLICATION/Src/fault_cfg.su ./SPARK_BMS/APPLICATION/Src/fault_monitor.cyclo ./SPARK_BMS/APPLICATION/Src/fault_monitor.d ./SPARK_BMS/APPLICATION/Src/fault_monitor.o ./SPARK_BMS/APPLICATION/Src/fault_monitor.su ./SPARK_BMS/APPLICATION/Src/shortcircuit.cyclo ./SPARK_BMS/APPLICATION/Src/shortcircuit.d ./SPARK_BMS/APPLICATION/Src/shortcircuit.o ./SPARK_BMS/APPLICATION/Src/shortcircuit.su ./SPARK_BMS/APPLICATION/Src/soc.cyclo ./SPARK_BMS/APPLICATION/Src/soc.d ./SPARK_BMS/APPLICATION/Src/soc.o ./SPARK_BMS/APPLICATION/Src/soc.su

.PHONY: clean-SPARK_BMS-2f-APPLICATION-2f-Src

