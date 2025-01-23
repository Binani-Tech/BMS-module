################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mddlewares/Third_Party/FatFs/src/diskio.c \
../Mddlewares/Third_Party/FatFs/src/ff.c \
../Mddlewares/Third_Party/FatFs/src/ff_gen_drv.c 

OBJS += \
./Mddlewares/Third_Party/FatFs/src/diskio.o \
./Mddlewares/Third_Party/FatFs/src/ff.o \
./Mddlewares/Third_Party/FatFs/src/ff_gen_drv.o 

C_DEPS += \
./Mddlewares/Third_Party/FatFs/src/diskio.d \
./Mddlewares/Third_Party/FatFs/src/ff.d \
./Mddlewares/Third_Party/FatFs/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Mddlewares/Third_Party/FatFs/src/%.o Mddlewares/Third_Party/FatFs/src/%.su Mddlewares/Third_Party/FatFs/src/%.cyclo: ../Mddlewares/Third_Party/FatFs/src/%.c Mddlewares/Third_Party/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/Mddlewares/Third_Party/FatFs/src" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/App" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/FATFS/Target" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/APPLICATION/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/CONFIG/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/DRIVER/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/ENGINE/Inc" -I"D:/BMS Firmware/Binani Tech/410V_8M_Binani_Tech_03_12_24_Testing/ISL78600/SPARK_BMS/MODULE/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Mddlewares-2f-Third_Party-2f-FatFs-2f-src

clean-Mddlewares-2f-Third_Party-2f-FatFs-2f-src:
	-$(RM) ./Mddlewares/Third_Party/FatFs/src/diskio.cyclo ./Mddlewares/Third_Party/FatFs/src/diskio.d ./Mddlewares/Third_Party/FatFs/src/diskio.o ./Mddlewares/Third_Party/FatFs/src/diskio.su ./Mddlewares/Third_Party/FatFs/src/ff.cyclo ./Mddlewares/Third_Party/FatFs/src/ff.d ./Mddlewares/Third_Party/FatFs/src/ff.o ./Mddlewares/Third_Party/FatFs/src/ff.su ./Mddlewares/Third_Party/FatFs/src/ff_gen_drv.cyclo ./Mddlewares/Third_Party/FatFs/src/ff_gen_drv.d ./Mddlewares/Third_Party/FatFs/src/ff_gen_drv.o ./Mddlewares/Third_Party/FatFs/src/ff_gen_drv.su

.PHONY: clean-Mddlewares-2f-Third_Party-2f-FatFs-2f-src

