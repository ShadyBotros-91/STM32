################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Libraries/System_stm32f4xx/src/startup_stm32f429x.s 

C_SRCS += \
../Libraries/System_stm32f4xx/src/stm32f4xx_it.c \
../Libraries/System_stm32f4xx/src/system_stm32f4xx.c 

OBJS += \
./Libraries/System_stm32f4xx/src/startup_stm32f429x.o \
./Libraries/System_stm32f4xx/src/stm32f4xx_it.o \
./Libraries/System_stm32f4xx/src/system_stm32f4xx.o 

C_DEPS += \
./Libraries/System_stm32f4xx/src/stm32f4xx_it.d \
./Libraries/System_stm32f4xx/src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/System_stm32f4xx/src/%.o: ../Libraries/System_stm32f4xx/src/%.s
	arm-atollic-eabi-gcc -c -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F42_43xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F429I_DISCO -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/ST/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/Common -I../Utilities/STM32F429I-Discovery -I"C:\Users\Shady\Atollic\TrueSTUDIO\STM32_workspace_9.3\USART\src\inc" -I"C:\Users\Shady\Atollic\TrueSTUDIO\STM32_workspace_9.3\USART\Libraries\System_stm32f4xx\inc" -g -Wa,--warn -x assembler-with-cpp -specs=nano.specs -o "$@" "$<"
Libraries/System_stm32f4xx/src/%.o: ../Libraries/System_stm32f4xx/src/%.c
	arm-atollic-eabi-gcc -c "$<" -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -DSTM32F42_43xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F429I_DISCO -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/ST/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/Common -I../Utilities/STM32F429I-Discovery -I"C:\Users\Shady\Atollic\TrueSTUDIO\STM32_workspace_9.3\USART\src\inc" -I"C:\Users\Shady\Atollic\TrueSTUDIO\STM32_workspace_9.3\USART\Libraries\System_stm32f4xx\inc" -O0 -ffunction-sections -fdata-sections -g -fstack-usage -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"

