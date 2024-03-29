################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_initialize_hardware.c \
../src/_write.c \
../src/rtoshook.c \
../src/stm32f4xx_hal_msp.c 

CPP_SRCS += \
../src/BlinkLed.cpp \
../src/LookUp.cpp \
../src/Timer.cpp \
../src/control.cpp \
../src/main.cpp \
../src/pid.cpp \
../src/sensor.cpp \
../src/testdata.cpp 

OBJS += \
./src/BlinkLed.o \
./src/LookUp.o \
./src/Timer.o \
./src/_initialize_hardware.o \
./src/_write.o \
./src/control.o \
./src/main.o \
./src/pid.o \
./src/rtoshook.o \
./src/sensor.o \
./src/stm32f4xx_hal_msp.o \
./src/testdata.o 

C_DEPS += \
./src/_initialize_hardware.d \
./src/_write.d \
./src/rtoshook.d \
./src/stm32f4xx_hal_msp.d 

CPP_DEPS += \
./src/BlinkLed.d \
./src/LookUp.d \
./src/Timer.d \
./src/control.d \
./src/main.d \
./src/pid.d \
./src/sensor.d \
./src/testdata.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"/home/daniel/eclipse-workspace/rtos/src/FreeRTOS/include" -I"/home/daniel/eclipse-workspace/rtos/src/FreeRTOS/portable/GCC/ARM_CM3" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"/home/daniel/eclipse-workspace/rtos/src/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/daniel/eclipse-workspace/rtos/src/FreeRTOS/include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/stm32f4xx_hal_msp.o: ../src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"/home/daniel/eclipse-workspace/rtos/src/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/daniel/eclipse-workspace/rtos/src/FreeRTOS/include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -Wno-missing-prototypes -Wno-missing-declarations -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/stm32f4xx_hal_msp.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


