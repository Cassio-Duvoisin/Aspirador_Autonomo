################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Analog.c \
../Core/Src/Button.c \
../Core/Src/Digital.c \
../Core/Src/LedMgr.c \
../Core/Src/Observer.c \
../Core/Src/PWM.c \
../Core/Src/SystemConfig.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/Analog.o \
./Core/Src/Button.o \
./Core/Src/Digital.o \
./Core/Src/LedMgr.o \
./Core/Src/Observer.o \
./Core/Src/PWM.o \
./Core/Src/SystemConfig.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/Analog.d \
./Core/Src/Button.d \
./Core/Src/Digital.d \
./Core/Src/LedMgr.d \
./Core/Src/Observer.d \
./Core/Src/PWM.d \
./Core/Src/SystemConfig.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Analog.cyclo ./Core/Src/Analog.d ./Core/Src/Analog.o ./Core/Src/Analog.su ./Core/Src/Button.cyclo ./Core/Src/Button.d ./Core/Src/Button.o ./Core/Src/Button.su ./Core/Src/Digital.cyclo ./Core/Src/Digital.d ./Core/Src/Digital.o ./Core/Src/Digital.su ./Core/Src/LedMgr.cyclo ./Core/Src/LedMgr.d ./Core/Src/LedMgr.o ./Core/Src/LedMgr.su ./Core/Src/Observer.cyclo ./Core/Src/Observer.d ./Core/Src/Observer.o ./Core/Src/Observer.su ./Core/Src/PWM.cyclo ./Core/Src/PWM.d ./Core/Src/PWM.o ./Core/Src/PWM.su ./Core/Src/SystemConfig.cyclo ./Core/Src/SystemConfig.d ./Core/Src/SystemConfig.o ./Core/Src/SystemConfig.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

