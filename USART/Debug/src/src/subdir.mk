################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/src/SysTick.c \
../src/src/dma.c \
../src/src/exti.c \
../src/src/gpio.c \
../src/src/irq.c \
../src/src/memcpy.c \
../src/src/nvic.c \
../src/src/usart1.c 

OBJS += \
./src/src/SysTick.o \
./src/src/dma.o \
./src/src/exti.o \
./src/src/gpio.o \
./src/src/irq.o \
./src/src/memcpy.o \
./src/src/nvic.o \
./src/src/usart1.o 

C_DEPS += \
./src/src/SysTick.d \
./src/src/dma.d \
./src/src/exti.d \
./src/src/gpio.d \
./src/src/irq.d \
./src/src/memcpy.d \
./src/src/nvic.d \
./src/src/usart1.d 


# Each subdirectory must supply rules for building sources it contributes
src/src/%.o: ../src/src/%.c
	arm-atollic-eabi-gcc -c "$<" -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -DSTM32F42_43xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F429I_DISCO -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/ST/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/Common -I../Utilities/STM32F429I-Discovery -I"C:\Users\Shady\Atollic\TrueSTUDIO\STM32_workspace_9.3\USART\src\inc" -I"C:\Users\Shady\Atollic\TrueSTUDIO\STM32_workspace_9.3\USART\Libraries\System_stm32f4xx\inc" -O0 -ffunction-sections -fdata-sections -g -fstack-usage -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"

