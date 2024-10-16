################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Logger/logger.c 

OBJS += \
./Src/Logger/logger.o 

C_DEPS += \
./Src/Logger/logger.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Logger/%.o Src/Logger/%.su Src/Logger/%.cyclo: ../Src/Logger/%.c Src/Logger/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F401xE -c -I../Inc -I"../$(ProjDirPath)/Headers/CMSIS/Include" -I"../$(ProjDirPath)/Headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Logger

clean-Src-2f-Logger:
	-$(RM) ./Src/Logger/logger.cyclo ./Src/Logger/logger.d ./Src/Logger/logger.o ./Src/Logger/logger.su

.PHONY: clean-Src-2f-Logger

